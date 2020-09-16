/**
 *******************************************************************************
 * @file  dcu/dcu_hw_add/source/main.c
 * @brief This example demonstrates DCU hardware signal trigger DCU add function.
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
 * @addtogroup DCU_HW_Add
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

/* DCU hardware trigger source definition */
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
    uint16_t au16Data0Value[4];
    uint16_t au16Data2Value[4];
    const uint16_t au16Data1Value[4] = {0x0000, 0x2222, 0x4444, 0x8888};
    const uint32_t u32CalcTimes = ARRAY_SZ(au16Data1Value);

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
    stcDcuInit.u32Mode = DCU_MD_HW_ADD;
    stcDcuInit.u32DataWidth = DCU_DATA_WIDTH_16BIT;
    (void)DCU_Init(DCU_UNIT, &stcDcuInit);

    /* Set the event trigger source. */
    DCU_SetTriggerSrc(DCU_UNIT, DCU_EVT_SRC);

    for (i = 0UL; i < u32CalcTimes; i++)
    {
        DCU_WriteData16(DCU_UNIT, DCU_DATA1_IDX, au16Data1Value[i]);

        /* Start soft trigger event */
        AOS_SW_Trigger();

        au16Data0Value[i] = DCU_ReadData16(DCU_UNIT, DCU_DATA0_IDX);
        au16Data2Value[i] = DCU_ReadData16(DCU_UNIT, DCU_DATA2_IDX);

        /* Compare DCU regisger DATA0 && DATA2 value: DATA0 value == 2 * DATA2 value */
        if (au16Data0Value[i] != (2U * au16Data2Value[i]))
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
