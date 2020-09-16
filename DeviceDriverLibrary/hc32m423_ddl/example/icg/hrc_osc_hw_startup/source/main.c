/**
 *******************************************************************************
 * @file  icg/hrc_osc_hw_startup/source/main.c
 * @brief Main program of ICG HRC Frequency for the Device Driver Library.
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
 * @addtogroup ICG_HRC_Frequency
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Clock output Port/Pin definition */
#define MCO_PORT                        (GPIO_PORT_7)
#define MCO_PIN                         (GPIO_PIN_0)

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
 * @brief  Clock output config.
 * @param  None
 * @retval None
 */
static void Clock_OutputConfig(void)
{
    /* Configure clock output pin */
    GPIO_SetFunc(MCO_PORT, MCO_PIN, GPIO_FUNC_1_MCO);

    /* Configure clock output system clock */
    CLK_MCOConfig(CLK_MCO_SRC_HRC, CLK_MCO_DIV1);
    /* MCO output enable */
    CLK_MCOCmd(Enable);
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
    PWC_Unlock(PWC_UNLOCK_CODE_0);
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
 * @brief  Main function of ICG HRC Frequency.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /**
     ***************************************************************************
     @brief Modify hc32m423_icg.h file of define
     @verbatim
     #define ICG0_RB_HRC_FRQSEL                 ICG_HRC_16M
     #define ICG0_RB_HRC_STOP                   ICG_HRC_RST_OSCILLATE
     @endverbatim
     ***************************************************************************
     */
    /* Peripheral registers write unprotected */
    Peripheral_WE();
    /* Configure BSP */
    BSP_LED_Init();
    /* Configure UART */
    (void)DDL_PrintfInit();
    /* Configure clock output */
    Clock_OutputConfig();
    /* Peripheral registers write protected */
    Peripheral_WP();

    for (;;)
    {
        BSP_LED_Toggle(LED_RED);
        DDL_DelayMS(1000UL);
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
