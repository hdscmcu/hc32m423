/**
 *******************************************************************************
 * @file  pwc/pwc_lvd/source/main.c
 * @brief Main program of PWC for the Device Driver Library.
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
 * @addtogroup PWC_Lvd
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define DELAY_TIME      (5000U)

#define LVD_UNIT        (PWC_LVD1)
#define LVD_IRQn        (LVD1_IRQn)
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

void PWC_LVD1_IrqHandler(void)
{
    PWC_LVD_ClearDetectFlag(LVD_UNIT);
    if(PWC_LVD_CMP_VCC_GREATER_LVD == PWC_LVD_GetCompareResult(LVD_UNIT))
    {
        BSP_LED_Off(LED_RED);
        BSP_LED_On(LED_GREEN);
    }
    else
    {
        BSP_LED_On(LED_RED);
        BSP_LED_Off(LED_GREEN);
    }
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
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Main function of CLK project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_pwc_lvd_init_t  stcPwcLvdInit;

    /* Register write unprotected for some required peripherals. */
    Peripheral_WE();
    /* LED init */
    BSP_LED_Init();

    /* Config LVD */
    stcPwcLvdInit.u32CompareOutput = PWC_LVD_CMP_OUTPUT_ENABLE;
    stcPwcLvdInit.u32ExtInput = PWC_LVD2_EXT_INPUT_DISABLE;
    stcPwcLvdInit.u32FilterEnable = PWC_LVD_FILTER_ENABLE;
    stcPwcLvdInit.u32FilterClock = PWC_LVD_FILTER_CLK_DIV4;
    stcPwcLvdInit.u32ThresholdVoltage = PWC_LVD_THRESHOLD_LVL3;
    stcPwcLvdInit.u32ExceptionType = PWC_LVD_EXP_TYPE_INT;
    stcPwcLvdInit.u32IntMode = PWC_LVD_INT_NORMAL;
    stcPwcLvdInit.u32LvdDetectEdge = PWC_LVD_EDGE_BOTH;

    if(Ok != PWC_LVD_Init(LVD_UNIT, &stcPwcLvdInit))
    {
        /* PWC initail failed */
        BSP_LED_On(LED_RED);
        Peripheral_WP();
        for(;;)
        {
            ;
        }
    }

    /* Enable LVD */
    PWC_LVD_Cmd(LVD_UNIT, Enable);
    /* Enable cmp result output */
    PWC_LVD_IntResetCmd(LVD_UNIT, Enable);

    /* NVIC configure */
    NVIC_ClearPendingIRQ(LVD_IRQn);
    NVIC_SetPriority(LVD_IRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(LVD_IRQn);

    WRITE_REG32(CM_DBGC->MCUSTPCTL, 0x03UL);

    BSP_LED_On(LED_GREEN);
    Peripheral_WP();

    for(;;)
    {
        ;
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
