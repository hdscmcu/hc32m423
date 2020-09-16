/**
 *******************************************************************************
 * @file  timera/timera_base_timer/source/main.c
 * @brief Main program of Timera Base Count for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-15       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ddl.h"

/**
 * @addtogroup HC32M423_DDL_Examples
 * @{
 */

/**
 * @addtogroup TMRA_Base_Timer
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Timera unit definition */
#define TMRA_UNIT1                      (CM_TMRA_1)
#define TMRA_UNIT1_CLK                  (CLK_FCG_TMRA_1)
#define TMRA_UNIT1_CLK_DIV              (256U)
#define TMRA_UNIT1_INT_FREQ             (100U)
/* Period value = 10ms */
#define TMRA_UNIT1_PERIOD_VALUE         ((uint16_t)(HCLK_VALUE/TMRA_UNIT1_CLK_DIV/TMRA_UNIT1_INT_FREQ) - 1U)

#define TMRA_UNIT2                      (CM_TMRA_2)
#define TMRA_UNIT2_CLK                  (CLK_FCG_TMRA_2)
#define TMRA_UNIT2_CLK_DIV              (256U)
#define TMRA_UNIT2_INT_FREQ             (100U)
/* Period value = 10ms */
#define TMRA_UNIT2_PERIOD_VALUE         ((uint16_t)(HCLK_VALUE/TMRA_UNIT2_CLK_DIV/TMRA_UNIT2_INT_FREQ) - 1U)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Overflow interrupt callback for Timera unit1.
 * @param  None
 * @retval None
 */
void TMRA_1_Ovf_IrqHandler(void)
{
    static uint8_t u8Unit1Cnt = 0U;

    u8Unit1Cnt++;
    if (u8Unit1Cnt >= TMRA_UNIT1_INT_FREQ)  /* 1s */
    {
        u8Unit1Cnt = 0U;
        BSP_LED_Toggle(LED_RED);
    }
    TMRA_ClearStatus(TMRA_UNIT1, TMRA_FLAG_OVF);
}

/**
 * @brief  Underflow interrupt callback for Timera unit2.
 * @param  None
 * @retval None
 */
void TMRA_2_Udf_IrqHandler(void)
{
    static uint8_t u8Unit2Cnt = 0U;

    u8Unit2Cnt++;
    if (u8Unit2Cnt >= TMRA_UNIT2_INT_FREQ)  /* 1s */
    {
        u8Unit2Cnt = 0U;
        BSP_LED_Toggle(LED_GREEN);
    }
    TMRA_ClearStatus(TMRA_UNIT2, TMRA_FLAG_UDF);
}

/**
 * @brief  Configure Timera function.
 * @param  None
 * @retval None
 */
static void TMRA_Config(void)
{
    stc_tmra_init_t stcTmraInit;

    /* Configure peripheral clock */
    CLK_FcgPeriphClockCmd((TMRA_UNIT1_CLK | TMRA_UNIT2_CLK), Enable);

    (void)TMRA_StructInit(&stcTmraInit);
    /* Configure structure of timera unit1 */
    stcTmraInit.u16ClockDiv    = TMRA_CLK_DIV256;
    stcTmraInit.u16CountMode   = TMRA_MD_SAWTOOTH;
    stcTmraInit.u16CountDir    = TMRA_DIR_UP;
    stcTmraInit.u16PeriodValue = TMRA_UNIT1_PERIOD_VALUE;
    (void)TMRA_Init(TMRA_UNIT1, &stcTmraInit);
    TMRA_IntCmd(TMRA_UNIT1, TMRA_INT_OVF, Enable);
    /* Configure interrupt of timera unit1 */
    NVIC_ClearPendingIRQ(TMRA_1_OVF_IRQn);
    NVIC_SetPriority(TMRA_1_OVF_IRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(TMRA_1_OVF_IRQn);

    /* Configure structure of timera unit2 */
    stcTmraInit.u16CountDir    = TMRA_DIR_DOWN;
    stcTmraInit.u16PeriodValue = TMRA_UNIT2_PERIOD_VALUE;
    (void)TMRA_Init(TMRA_UNIT2, &stcTmraInit);
    TMRA_IntCmd(TMRA_UNIT2, TMRA_INT_UDF, Enable);
    /* Configure interrupt of timera unit2 */
    NVIC_ClearPendingIRQ(TMRA_2_UDF_IRQn);
    NVIC_SetPriority(TMRA_2_UDF_IRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(TMRA_2_UDF_IRQn);

    /* Enable the sync start function of timera unit2 */
    TMRA_SyncStartCmd(TMRA_UNIT2, Enable);
}

/**
 * @brief  MCU Peripheral registers write unprotected.
 * @param  None
 * @retval None
 * @note Comment/uncomment each API depending on APP requires.
 */
static void Peripheral_WE(void)
{
    /* Unlock GPIO register: PSPCR, PCCR, PINAER, PCRxy, PFSRxy */
    GPIO_Unlock();
    /* Unlock PWC, CLK, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
    /* Unlock all EFM registers */
    EFM_Unlock();
}

/**
 * @brief  MCU Peripheral registers write protected.
 * @param  None
 * @retval None
 * @note Comment/uncomment each API depending on APP requires.
 */
static void Peripheral_WP(void)
{
    /* Lock GPIO register: PSPCR, PCCR, PINAER, PCRxy, PFSRxy */
    GPIO_Lock();
    /* Lock PWC, CLK, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
//    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Main function of Timera Base Timer.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Peripheral registers write unprotected */
    Peripheral_WE();
    /* Configure BSP */
    BSP_CLK_Init();
    BSP_LED_Init();
    /* Configure UART */
    (void)DDL_PrintfInit();
    /* Configure Timera */
    TMRA_Config();
    /* Peripheral registers write protected */
    Peripheral_WP();
    /* Start unit1 of timera and sync start unit2 of timera */
    TMRA_Start(TMRA_UNIT1);

    for (;;)
    {
    }
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
