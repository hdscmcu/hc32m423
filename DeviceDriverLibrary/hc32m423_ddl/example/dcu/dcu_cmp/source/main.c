/**
 *******************************************************************************
 * @file  dcu/dcu_cmp/source/main.c
 * @brief This example demonstrates DCU cmp function.
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
 * @addtogroup DCU_Cmp
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* DCU unit && Function clock gate definition */
#define DCU_UNIT                        (CM_DCU)

/* Function clock gate definition */
#define FUNC_CLK_GATE                   (CLK_FCG_DCU)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static void DCU_IrqCallback(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static __IO uint32_t m_u32CmpFlag = 0UL;

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
 * @brief  DCU irq callback function.
 * @param  None
 * @retval None
 */
static void DCU_IrqCallback(void)
{
    if (Set == DCU_GetStatus(DCU_UNIT, DCU_FLAG_DATA0_LT_DATA2))
    {
        m_u32CmpFlag |= DCU_FLAG_DATA0_LT_DATA2;
    }

    if (Set == DCU_GetStatus(DCU_UNIT, DCU_FLAG_DATA0_EQ_DATA2))
    {
        m_u32CmpFlag |= DCU_FLAG_DATA0_EQ_DATA2;
    }

    if (Set == DCU_GetStatus(DCU_UNIT, DCU_FLAG_DATA0_GT_DATA2))
    {
        m_u32CmpFlag |= DCU_FLAG_DATA0_GT_DATA2;
    }

    if (Set == DCU_GetStatus(DCU_UNIT, DCU_FLAG_DATA0_LT_DATA1))
    {
        m_u32CmpFlag |= DCU_FLAG_DATA0_LT_DATA1;
    }

    if (Set == DCU_GetStatus(DCU_UNIT, DCU_FLAG_DATA0_EQ_DATA1))
    {
        m_u32CmpFlag |= DCU_FLAG_DATA0_EQ_DATA1;
    }

    if (Set == DCU_GetStatus(DCU_UNIT, DCU_FLAG_DATA0_GT_DATA1))
    {
        m_u32CmpFlag |= DCU_FLAG_DATA0_GT_DATA1;
    }

    DCU_ClearStatus(DCU_UNIT, DCU_FLAG_ALL);
}

/**
 * @brief  Main function of DCU compare project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_dcu_init_t stcDcuInit;
    en_result_t enTestResult = Ok;
    stc_irq_signin_config_t stcIrqConfig;
    const uint8_t au8Data0Value[5] = {0x00U, 0x22U, 0x44U, 0x66U, 0x88};
    const uint8_t au8Data1Value[5] = {0x00U, 0x11U, 0x55U, 0x77U, 0x77};
    const uint8_t au8Data2Value[5] = {0x00U, 0x11U, 0x55U, 0x55U, 0x00};

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
    stcDcuInit.u32Mode = DCU_MD_CMP;
    (void)DCU_Init(DCU_UNIT, &stcDcuInit);

    /* Set DCU IRQ */
    stcIrqConfig.enIRQn = INT000_IRQn;
    stcIrqConfig.enIntSrc = INT_DCU;
    stcIrqConfig.pfnCallback = &DCU_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqConfig);
    NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
    NVIC_EnableIRQ(stcIrqConfig.enIRQn);

    /* Enable the DCU interrupt function */
    DCU_GlobalIntCmd(DCU_UNIT, Enable);

    /* Initialize DCU */
    DCU_IntCmd(DCU_UNIT, DCU_CATEGORY_CMP_NON_WIN, DUC_INT_CMP_NON_WIN_ALL, Enable);

    /* DATA0 = DATA1  &&  DATA0 = DATA2 */
    DCU_WriteData8(DCU_UNIT, DCU_DATA1_IDX, au8Data1Value[0]);
    DCU_WriteData8(DCU_UNIT, DCU_DATA2_IDX, au8Data2Value[0]);
    DCU_WriteData8(DCU_UNIT, DCU_DATA0_IDX, au8Data0Value[0]);
    if (m_u32CmpFlag != (DCU_FLAG_DATA0_EQ_DATA1 | DCU_FLAG_DATA0_EQ_DATA2))
    {
        enTestResult = Error;
    }

    /* DATA0 > DATA1  &&  DATA0 > DATA2 */
    m_u32CmpFlag = 0UL;
    DCU_WriteData8(DCU_UNIT, DCU_DATA1_IDX, au8Data1Value[1]);
    DCU_WriteData8(DCU_UNIT, DCU_DATA2_IDX, au8Data2Value[1]);
    DCU_WriteData8(DCU_UNIT, DCU_DATA0_IDX, au8Data0Value[1]);
    if (m_u32CmpFlag != (DCU_FLAG_DATA0_GT_DATA1 | DCU_FLAG_DATA0_GT_DATA2))
    {
        enTestResult = Error;
    }

    /* DATA0 < DATA1  &&  DATA0 < DATA2 */
    m_u32CmpFlag = 0UL;
    DCU_WriteData8(DCU_UNIT, DCU_DATA1_IDX, au8Data1Value[2]);
    DCU_WriteData8(DCU_UNIT, DCU_DATA2_IDX, au8Data2Value[2]);
    DCU_WriteData8(DCU_UNIT, DCU_DATA0_IDX, au8Data0Value[2]);
    if (m_u32CmpFlag != (DCU_FLAG_DATA0_LT_DATA1 | DCU_FLAG_DATA0_LT_DATA2))
    {
        enTestResult = Error;
    }

    DCU_IntCmd(DCU_UNIT, DCU_CATEGORY_CMP_NON_WIN, DUC_INT_CMP_NON_WIN_ALL, Disable);

    /* Inside window: DATA2 <= DATA0 <= DATA1 */
    m_u32CmpFlag = 0UL;
    DCU_IntCmd(DCU_UNIT, DCU_CATEGORY_CMP_WIN, DCU_INT_CMP_WIN_INSIDE, Enable);
    DCU_WriteData8(DCU_UNIT, DCU_DATA1_IDX, au8Data1Value[3]);
    DCU_WriteData8(DCU_UNIT, DCU_DATA2_IDX, au8Data2Value[3]);
    DCU_WriteData8(DCU_UNIT, DCU_DATA0_IDX, au8Data0Value[3]);
    DCU_IntCmd(DCU_UNIT, DCU_CATEGORY_CMP_WIN, DCU_INT_CMP_WIN_INSIDE, Disable);
    if (m_u32CmpFlag != (DCU_FLAG_DATA0_LT_DATA1 | DCU_FLAG_DATA0_GT_DATA2))
    {
        enTestResult = Error;
    }

    /* Outside window: DATA0 > DATA2 and DATA0 > DATA1 */
    m_u32CmpFlag = 0UL;
    DCU_IntCmd(DCU_UNIT, DCU_CATEGORY_CMP_WIN, DCU_INT_CMP_WIN_OUTSIDE, Enable);
    DCU_WriteData8(DCU_UNIT, DCU_DATA1_IDX, au8Data1Value[4]);
    DCU_WriteData8(DCU_UNIT, DCU_DATA2_IDX, au8Data2Value[4]);
    DCU_WriteData8(DCU_UNIT, DCU_DATA0_IDX, au8Data0Value[4]);
    if (m_u32CmpFlag != (DCU_FLAG_DATA0_GT_DATA1 | DCU_FLAG_DATA0_GT_DATA2))
    {
        enTestResult = Error;
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
