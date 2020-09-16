/**
 *******************************************************************************
 * @file  timerb/timerb_base_timer/source/main.c
 * @brief This example demonstrates TMRB base count function.
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
 * @addtogroup TMRB_Base_Timer
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* TMRB unit && interrupt number && counter period value definition */
#define TMRB_UNIT                       (CM_TMRB)
#define TMRB_CNT_OVF_INT_SRC            (INT_TMRB_OVF)
#define TMRB_CNT_OVF_IRQn               (INT000_IRQn)
#define TMRB_CNT_1S_VALUE(div)          ((TmrbPclkFreq() / (uint32_t)(div))) /* Period_Value(1000ms) */

/* TMRB TIMB_1_PWMn(n=1/3 Port/Pin definition */
#define TMRB_1_PWM1_PORT                (GPIO_PORT_7)     /* P72: TIMB_1_PWM1 */
#define TMRB_1_PWM1_PIN                 (GPIO_PIN_2)
#define TMRB_1_PWM1_GPIO_FUNC           (GPIO_FUNC_3_TIMB1)

#define TMRB_1_PWM3_PORT                (GPIO_PORT_7)     /* P71: TIMB_1_PWM3 */
#define TMRB_1_PWM3_PIN                 (GPIO_PIN_1)
#define TMRB_1_PWM3_GPIO_FUNC           (GPIO_FUNC_3_TIMB1)

/* Function clock gate definition */
#define FUNC_CLK_GATE                   (CLK_FCG_TMRB)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static void TMRB_Overflow_IrqCallback(void);

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
 * @brief  Get TMRB PCLK frequency.
 * @param  None
 * @retval None
 */
static uint32_t TmrbPclkFreq(void)
{
    stc_clock_freq_t stcClockFreq;

    (void)CLK_GetClockFreq(&stcClockFreq);
    return stcClockFreq.u32Pclk1Freq;
}

/**
 * @brief  TMRB unit overflow IRQ callback.
 * @param  None
 * @retval None
 */
static void TMRB_Overflow_IrqCallback(void)
{
    BSP_LED_Toggle(LED_GREEN);

    TMRB_ClearStatus(TMRB_UNIT, TMRB_FLAG_OVF);
}

/**
 * @brief  Main function of TMRB base timer project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_tmrb_init_t stcTmrbInit;
    stc_irq_signin_config_t stcIrqConfig;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize system clock. */
    BSP_CLK_Init();

    /* Initialize LED. */
    BSP_LED_Init();

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNC_CLK_GATE, Enable);

    /* Configure TIM_<t>_PWM1/TIM_<t>_PWM3. */
    GPIO_SetFunc(TMRB_1_PWM1_PORT, TMRB_1_PWM1_PIN, TMRB_1_PWM1_GPIO_FUNC);
    GPIO_SetFunc(TMRB_1_PWM3_PORT, TMRB_1_PWM3_PIN, TMRB_1_PWM3_GPIO_FUNC);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Initialize TMRB. */
    (void)TMRB_StructInit(&stcTmrbInit);
    stcTmrbInit.u16CountDir = TMRB_DIR_UP;
    stcTmrbInit.u16ClockDiv = TMRB_CLK_DIV1024;
    stcTmrbInit.u16PeriodValue = (uint16_t)(TMRB_CNT_1S_VALUE(1024UL)/2UL);
    (void)TMRB_Init(TMRB_UNIT, &stcTmrbInit);
    TMRB_IntCmd(TMRB_UNIT, TMRB_INT_OVF, Enable);

    /* Start count when detect the rising edge on TIMB_1_PWM1 */
    TMRB_HWStartCondCmd(TMRB_UNIT, TMRB_START_COND_PWM1R, Enable);

    /* Clear count value when detect the rising or failing edge on TIMB_1_PWM3 */
    TMRB_HWClearCondCmd(TMRB_UNIT, (TMRB_CLR_COND_PWM3R | TMRB_CLR_COND_PWM3F), Enable);

    /* Register IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = TMRB_CNT_OVF_IRQn;
    stcIrqConfig.enIntSrc = TMRB_CNT_OVF_INT_SRC;
    stcIrqConfig.pfnCallback = &TMRB_Overflow_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqConfig);
    NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
    NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(stcIrqConfig.enIRQn);

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
