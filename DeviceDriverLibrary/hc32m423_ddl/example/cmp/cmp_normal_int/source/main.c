/**
 *******************************************************************************
 * @file  cmp/cmp_normal_int/source/main.c
 * @brief Main program of CMP for the Device Driver Library.
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
 * @addtogroup CMP_Normal_Int
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CMP_TEST_UNIT                   (CM_CMP1)
#define TEST_CMP_IRQ                    (CMP1_IRQn)

/* Define port and pin for CMP */
/* VCOUT1*/
#define CMP_VCOUT1_PORT                 (GPIO_PORT_2)
#define CMP_VCOUT1_PIN                  (GPIO_PIN_4)
/* IVCMP1_0 */
#define IVCMP1_0_PORT                   (GPIO_PORT_4)
#define IVCMP1_0_PIN                    (GPIO_PIN_0)
/* IREF1 */
//#define IREF1_PORT                      (GPIO_PORT_1)
//#define IREF1_PIN                       (GPIO_PIN_1)

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
    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1|PWC_UNLOCK_CODE_2);
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
    //GPIO_Lock();
    /* Lock PWC, CLK, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1|PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Main function of cmp_normal_int project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_cmp_init_t stcCmpInit;

    /* Register write unprotected for some required peripherals. */
    Peripheral_WE();
    /* System clock Init */
    BSP_CLK_Init();
    /* LED init */
    BSP_LED_Init();

    /* Port function configuration */
    GPIO_SetFunc(CMP_VCOUT1_PORT, CMP_VCOUT1_PIN, GPIO_FUNC_1_VCOUT);
    GPIO_SetFunc(IVCMP1_0_PORT, IVCMP1_0_PIN, GPIO_FUNC_1_ANA);
    //GPIO_SetFunc(IREF1_PORT, IREF1_PIN, GPIO_FUNC_1_ANA);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(CLK_FCG_CMP, Enable);

    /* Clear structure */
    (void)CMP_StructInit(&stcCmpInit);
    /* De-initialize CMP unit */
    CMP_DeInit(CMP_TEST_UNIT);

    /* Configuration for normal compare function */
    stcCmpInit.u8CompareVoltage = CMP_CMP_VOLT_IVCMPx_0;
    stcCmpInit.u8RefVoltage = CMP_REF_VOLT_DAC;
    stcCmpInit.u8OutDetectEdges = CMP_DETECT_EDGE_BOTH;
    stcCmpInit.u8OutFilter = CMP_OUT_FILTER_CLK_DIV32;
    stcCmpInit.u8OutPolarity = CMP_OUT_POLARITY_NORMAL;
    (void)CMP_NormalModeInit(CMP_TEST_UNIT, &stcCmpInit);

    /* 8 bit DAC config and command */
    CMP_DAC_RightAlignWriteData(0x7FU);
    CMP_DAC_SetAlign(CMP_DAC_ALIGN_RIGHT);
    CMP_DAC_Cmd(Enable);
    DDL_DelayMS(5U);

    /* Enable interrupt if need */
    CMP_IntCmd(CMP_TEST_UNIT, Enable);

    /* Enable VCOUT if need */
    //CMP_VCOUTCmd(CMP_TEST_UNIT, Enable);

    /* Enable CMP output */
    CMP_OutputCmd(CMP_TEST_UNIT, Enable);

    /*NVIC configuration for interrupt */
    NVIC_ClearPendingIRQ(TEST_CMP_IRQ);
    NVIC_SetPriority(TEST_CMP_IRQ, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(TEST_CMP_IRQ);

    Peripheral_WP();
    /* Configuration finished */
    for(;;)
    {
        ;
    }
}

/**
 * @brief  CMP interrupt call back
 * @param  None
 * @retval None
 */
void CMP1_IrqHandler(void)
{
    en_flag_status_t stdflag;
    stdflag = CMP_GetCompareResult(CMP_TEST_UNIT);

    (Set == stdflag) ? BSP_LED_On(LED_BLUE) : BSP_LED_Off(LED_BLUE);
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
