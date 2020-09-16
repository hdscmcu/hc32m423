/**
 *******************************************************************************
 * @file  dcu/dcu_hw_sub/source/main.c
 * @brief This example demonstrates DCU hardware signal trigger DCU sub function.
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
 * @addtogroup DCU_HW_Sub
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* DCU unit definition */
#define DCU_UNIT                        (CM_DCU)

/* DCU hardware trigger source */
#define DCU_EVT_SRC                     (EVT_AOS_STRG)

/* Function clock gate definition */
#define FUNC_CLK_GATE                   (CLK_FCG_DCU | CLK_FCG_AOS)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);

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
    /* Unlock PWC, CLK registers, @ref PWC_REG_Write_Unlock_Code for details */
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
    /* Lock PWC, CLK registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Main function of DCU sub project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t i;
    stc_dcu_init_t stcDcuInit;
    en_result_t enTestResult = Ok;
    uint32_t au32Data0Value[4];
    uint32_t au32Data2Value[4];
    const uint32_t au32Data1Value[4] = {0x00000000, 0x22222222, 0x22222222, 0x22222222};
    const uint32_t u32CalcTimes = ARRAY_SZ(au32Data1Value);

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize system clock. */
    BSP_CLK_Init();

    /* Initialize LED. */
    BSP_LED_Init();

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNC_CLK_GATE, Enable);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Initialize DCU */
    (void)DCU_StructInit(&stcDcuInit);
    stcDcuInit.u32Mode = DCU_MD_HW_SUB;
    stcDcuInit.u32DataWidth = DCU_DATA_WIDTH_32BIT;
    (void)DCU_Init(DCU_UNIT, &stcDcuInit);

    /* Set the event trigger source. */
    DCU_SetTriggerSrc(DCU_UNIT, DCU_EVT_SRC);

    /* Set DCU_DATA0 value */
    DCU_WriteData32(DCU_UNIT, DCU_DATA0_IDX, 0x88888888UL);

    for (i = 0UL; i < u32CalcTimes; i++)
    {
        DCU_WriteData32(DCU_UNIT, DCU_DATA1_IDX, au32Data1Value[i]);

        /* Start soft trigger event */
        AOS_SW_Trigger();

        au32Data0Value[i] = DCU_ReadData32(DCU_UNIT, DCU_DATA0_IDX);
        au32Data2Value[i] = DCU_ReadData32(DCU_UNIT, DCU_DATA2_IDX);

        /* Compare DCU regisger DATA0 && DATA2 value: DATA0 value == 2 * DATA2 value */
        if (au32Data0Value[i] != (2UL * au32Data2Value[i]))
        {
            enTestResult = Error;
            break;
        }
    }

    if (Ok == enTestResult)
    {
        BSP_LED_On(LED_GREEN);  /* Test pass && meet the expected */
    }
    else
    {
        BSP_LED_On(LED_RED);    /* Test fail && don't meet the expected */
    }

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
