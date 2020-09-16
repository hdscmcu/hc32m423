/**
 *******************************************************************************
 * @file  timer4/timer4_pwm_reload_timer/source/main.c
 * @brief This example demonstrates how to use the reload timer mode function of
 *        Timer4 PWM function.
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
 * @addtogroup TMR4_PWM_Reload_Timer_Mode
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* TMR4 unit && fcg definition */
#define TMR4_UNIT                       (CM_TMR4)
#define TMR4_FUNC_CLK_GATE              (CLK_FCG_TMR4)

/* TMR4 PWM Channel && reload value definition */
#define TMR4_PWM_CH                     (TMR4_PWM_CH_U)
#define TMR4_PWM_RT_VALUE(div)          ((uint16_t)(Tmr4PclkFreq() / (1UL << (uint32_t)(div)) / 32UL)) /* Period_Value(31.25ms) */

/* TMR4 PWM interrupt source definition */
#define TMR4_PWM_RLO_INT_SRC            (INT_TMR4_RLOU)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static uint32_t Tmr4PclkFreq(void);
static void TMR4_PwmReloadTimer_IrqCallback(void);

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
 * @brief  Get TMR4 PCLK frequency.
 * @param  None
 * @retval None
 */
static uint32_t Tmr4PclkFreq(void)
{
    stc_clock_freq_t stcClockFreq;

    (void)CLK_GetClockFreq(&stcClockFreq);
    return stcClockFreq.u32Pclk1Freq;
}

/**
 * @brief  TMR4 PWM reload timer interrupt handler callback.
 * @param  None
 * @retval None
 */
static void TMR4_PwmReloadTimer_IrqCallback(void)
{
    static uint8_t u8IrqCnt = 0U;

    u8IrqCnt++;

    if (u8IrqCnt >= 16U)
    {
        u8IrqCnt = 0U;
        BSP_LED_Toggle(LED_GREEN);
    }

    TMR4_PWM_ClearStatus(TMR4_UNIT, TMR4_PWM_CH);
}

/**
 * @brief  Main function of TMR4 PWM reload timer mode
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_tmr4_pwm_init_t stcTmr4PwmInit;
    stc_irq_signin_config_t stcIrqConfig;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize clock. */
    BSP_CLK_Init();

    /* Initialize LED. */
    BSP_LED_Init();

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(TMR4_FUNC_CLK_GATE, Enable);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Initialize TMR4 PWM */
    (void)TMR4_PWM_StructInit(&stcTmr4PwmInit);
    stcTmr4PwmInit.u16ClockDiv = TMR4_PWM_CLK_DIV128;
    stcTmr4PwmInit.u16Mode = TMR4_PWM_MD_DEAD_TIMER;
    (void)TMR4_PWM_Init(TMR4_UNIT, TMR4_PWM_CH, &stcTmr4PwmInit);
    TMR4_PWM_SetFilterCountValue(TMR4_UNIT, TMR4_PWM_CH, TMR4_PWM_RT_VALUE(stcTmr4PwmInit.u16ClockDiv));
    TMR4_PWM_IntCmd(TMR4_UNIT, TMR4_PWM_CH, Enable);

    /* Register IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = INT000_IRQn;
    stcIrqConfig.enIntSrc = TMR4_PWM_RLO_INT_SRC;
    stcIrqConfig.pfnCallback = &TMR4_PwmReloadTimer_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqConfig);
    NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
    NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(stcIrqConfig.enIRQn);

    /* Start pwm count */
    TMR4_PWM_StartReloadTimer(TMR4_UNIT, TMR4_PWM_CH);

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
