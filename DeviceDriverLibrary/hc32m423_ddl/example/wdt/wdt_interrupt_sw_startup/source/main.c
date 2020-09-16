/**
 *******************************************************************************
 * @file  wdt/wdt_interrupt_sw_startup/source/main.c
 * @brief Main program of WDT Interrupt for the Device Driver Library.
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
 * @addtogroup WDT_Interrupt
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* KEY1(SW1) EXTINT5 Port/Pin definition */
#define KEY1_INT_CH                             (EXTINT_CH05)
#define KEY1_INT_PORT                           (GPIO_PORT_0)
#define KEY1_INT_PIN                            (GPIO_PIN_2)
#define KEY1_INT_SRC                            (INT_PORT_EIRQ5)
#define KEY1_INT_IRQn                           (EXTINT_PORT_EIRQ5_IRQn)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8ExIntCnt = 0U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  WDT interrupt callback function.
 * @param  None
 * @retval None
 */
void WDT_IrqHandler(void)
{
    en_flag_status_t enFlagSta;

    enFlagSta = WDT_GetStatus(WDT_FLAG_UDF);
    /* WDT underflow interrupt */
    if (Set == enFlagSta)
    {
        (void)WDT_ClearStatus(WDT_FLAG_UDF);
        /* Normal mode */
        if (0U == u8ExIntCnt)
        {
            BSP_LED_Toggle(LED_RED);
        }
        /* Sleep mode */
        else
        {
            BSP_LED_Toggle(LED_GREEN);
        }
    }
    WDT_Feed();
}

/**
 * @brief  KEY1(SW1) External interrupt Ch.5 ISR
 * @param  None
 * @retval None
 */
void ExtInt05_SWInt13_IrqHandler(void)
{
    if (Set == EXTINT_GetExtIntStatus(KEY1_INT_CH))
    {
        u8ExIntCnt++;
        if (u8ExIntCnt >= 2U)
        {
            u8ExIntCnt = 0U;
        }
        BSP_LED_Off(LED_RED);
        BSP_LED_Off(LED_GREEN);
        EXTINT_ClearExtIntStatus(KEY1_INT_CH);
    }
}

/**
 * @brief  KEY1(SW1) initialize.
 * @param  None
 * @retval None
 */
static void KEY1_Init(void)
{
    stc_extint_init_t stcExtIntInit;
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    /* KEY1 initialize */
    stcGpioInit.u16ExtInt = PIN_EXTINT_ON;
    (void)GPIO_Init(KEY1_INT_PORT, KEY1_INT_PIN, &stcGpioInit);

    /* EXTINT Channel configure */
    stcExtIntInit.u32ExtIntFilterA      = EXTINT_FILTER_A_ON;
    stcExtIntInit.u32ExtIntFilterAClock = EXTINT_FILTER_A_CLK_DIV1;
    stcExtIntInit.u32ExtIntLevel        = EXTINT_TRIG_FALLING;
    (void)EXTINT_Init(KEY1_INT_CH, &stcExtIntInit);

    /* NVIC configure */
    /* IRQ013_Handler, fixed entry for EXTINT5(KEY1) */
    NVIC_ClearPendingIRQ(KEY1_INT_IRQn);
    NVIC_SetPriority(KEY1_INT_IRQn, DDL_IRQ_PRI14);
    NVIC_EnableIRQ(KEY1_INT_IRQn);
}

/**
 * @brief  WDT configuration.
 * @param  None
 * @retval None
 */
static void WDT_Config(void)
{
    stc_wdt_init_t stcWdtInit;

    /* WDT configure */
    stcWdtInit.u32CountPeriod   = WDT_CNT_PERIOD65536;
    stcWdtInit.u32ClockDiv      = WDT_CLK_DIV1024;
    stcWdtInit.u32RefreshRange  = WDT_RANGE_0TO100PCT;
    stcWdtInit.u32LPMCount      = WDT_LPM_CNT_CONTINUE;
    stcWdtInit.u32ExceptionType = WDT_EXP_TYPE_INT;
    (void)WDT_Init(&stcWdtInit);

    /* NVIC configure */
    NVIC_ClearPendingIRQ(WDT_IRQn);
    NVIC_SetPriority(WDT_IRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(WDT_IRQn);
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
 * @brief  Main function of WDT Interrupt.
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
    /* Configure KEY1 */
    KEY1_Init();
    /* Configure UART */
    (void)DDL_PrintfInit();
    /* WDT configuration */
    WDT_Config();
    /* First feed the dog to start WDT */
    WDT_Feed();
    /* Peripheral registers write protected */
    Peripheral_WP();

    for (;;)
    {
        /* Sleep mode */
        if (1U == u8ExIntCnt)
        {
            PWC_EnterSleepMode();
        }
        else
        {
            /* Reserved */
        }
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
