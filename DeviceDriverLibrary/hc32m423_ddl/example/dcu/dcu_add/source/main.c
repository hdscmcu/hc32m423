/**
 *******************************************************************************
 * @file  dcu/dcu_add/source/main.c
 * @brief This example demonstrates DCU add function.
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
 * @addtogroup DCU_Add
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
static __IO uint32_t m_u32AddOverflowCnt = 0UL;

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
    if (Set == DCU_GetStatus(DCU_UNIT, DCU_FLAG_CARRY))
    {
        m_u32AddOverflowCnt++;
        DCU_ClearStatus(DCU_UNIT, DCU_FLAG_CARRY);
    }
}

/**
 * @brief  Main function of DCU add project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t i;
    stc_dcu_init_t stcDcuInit;
    en_result_t enTestResult = Ok;
    stc_irq_signin_config_t stcIrqConfig;
    uint32_t u32SumData0 = 0UL;
    uint32_t u32SumData1 = 0UL;
    uint16_t au16Data0Value[4];
    uint16_t au16Data2Value[4];
    const uint16_t au16Data1Value[4] = {0x0000U, 0x2222U, 0x4444U, 0x8888U};
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
    stcDcuInit.u32Mode = DCU_MD_ADD;
    stcDcuInit.u32DataWidth = DCU_DATA_WIDTH_16BIT;
    (void)DCU_Init(DCU_UNIT, &stcDcuInit);

    /* Enable the specified DCU interrupt */
    DCU_IntCmd(DCU_UNIT, DCU_CATEGORY_OP, DCU_INT_OP_CARRY, Enable);

    /* Enable the DCU interrupt function */
    DCU_GlobalIntCmd(DCU_UNIT, Enable);

    /* Set DCU IRQ */
    stcIrqConfig.enIRQn = INT000_IRQn;
    stcIrqConfig.enIntSrc = INT_DCU;
    stcIrqConfig.pfnCallback = &DCU_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqConfig);
    NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
    NVIC_EnableIRQ(stcIrqConfig.enIRQn);

    for (i = 0UL; i < u32CalcTimes; i++)
    {
        u32SumData1 += (uint32_t)au16Data1Value[i];
        DCU_WriteData16(DCU_UNIT, DCU_DATA1_IDX, au16Data1Value[i]);

        au16Data0Value[i] = DCU_ReadData16(DCU_UNIT, DCU_DATA0_IDX);
        au16Data2Value[i] = DCU_ReadData16(DCU_UNIT, DCU_DATA2_IDX);

        /* Compare DCU regisger DATA0 && DATA2 value: DATA0 value == 2 * DATA2 value */
        if (au16Data0Value[i] != (2U * au16Data2Value[i]))
        {
            enTestResult = Error;
            break;
        }
    }

    DCU_WriteData16(DCU_UNIT, DCU_DATA1_IDX, 0x2222U);
    u32SumData1 += 0x2222UL;

    u32SumData0 += (uint32_t)DCU_ReadData16(DCU_UNIT, DCU_DATA0_IDX) + (m_u32AddOverflowCnt * 0x10000UL);

    /* Compare : DATA0 value + 0x10000 == DATA1 sum value */
    if (u32SumData0 != u32SumData1)
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
