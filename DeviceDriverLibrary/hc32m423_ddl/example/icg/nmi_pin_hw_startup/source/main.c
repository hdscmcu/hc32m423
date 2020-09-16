/**
 *******************************************************************************
 * @file  icg/nmi_pin_hw_startup/source/main.c
 * @brief Main program of ICG NMI Interrupt for the Device Driver Library.
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
 * @addtogroup ICG_NMI_Interrupt
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

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
 * @brief  NMI interrupt callback function.
 * @param  None
 * @retval None
 */
static void NMI_IrqCallback(void)
{
    /* NMI Pin */
    if (Set == NMI_GetNmiStatus(INTC_NMIFR_NMIFR))
    {
        NMI_ClearNmiStatus(INTC_NMIFR_NMIFR);
        BSP_LED_Toggle(LED_RED);
    }
}

/**
 * @brief  NMI configuration.
 * @param  None
 * @retval None
 */
static void NMI_Config(void)
{
    stc_nmi_init_t stcNmiInit;

    /* NMI Pin interrupt configure */
    (void)NMI_StructInit(&stcNmiInit);
    stcNmiInit.u32NmiSrc      = NMI_SRC_NMI_PIN;
    stcNmiInit.pfnNmiCallback = &NMI_IrqCallback;
    (void)NMI_Init(&stcNmiInit);
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
 * @brief  Main function of ICG NMI Interrupt.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /**
     ***************************************************************************
     @brief Modify hc32m423_icg.h file of define
     @verbatim
     #define ICG0_RB_NMI_FCLK                   ICG_NMI_PIN_FILTER_CLK_DIV64
     #define ICG0_RB_NMI_FEN                    ICG_NMI_PIN_FILTER_ENABLE
     #define ICG0_RB_NMI_TRG                    ICG_NMI_PIN_TRIG_EDGE_FALLING
     #define ICG0_RB_NMI_EN                     ICG_NMI_PIN_INT_ENABLE
     #define ICG0_RB_NMI_ICGEN                  ICG_NMI_PIN_RST_ENABLE
     @endverbatim
    ***************************************************************************
    */
    /* Peripheral registers write unprotected */
    Peripheral_WE();
    /* Configure BSP */
    BSP_LED_Init();
    /* Configure UART */
    (void)DDL_PrintfInit();
    /* Configure NMI */
    NMI_Config();
    /* Peripheral registers write protected */
    Peripheral_WP();

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
