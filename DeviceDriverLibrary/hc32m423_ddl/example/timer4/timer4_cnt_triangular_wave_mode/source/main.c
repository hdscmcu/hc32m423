/**
 *******************************************************************************
 * @file  timer4/timer4_cnt_triangular_wave_mode/source/main.c
 * @brief This example demonstrates Timer4 Counter triangular wave mode.
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
 * @addtogroup TMR4_Counter_Triangular_Wave_Mode
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* TMR4 unit && fcg & counter period value && interrupt number definition */
#define TMR4_UNIT                       (CM_TMR4)
#define TMR4_FUNC_CLK_GATE              (CLK_FCG_TMR4)
#define TMR4_CNT_1S_VALUE(div)          (Tmr4PclkFreq() / (1UL << (uint32_t)(div))) /* Period_Value(1000ms) */
#define TMR4_CNT_OVF_INT_SRC            (INT_TMR4_GOVF)
#define TMR4_CNT_OVF_IRQn               (INT000_IRQn)

/* TIM4_<t>_PCT port/pin definition */
#define TIM4_PCT_PORT                   (GPIO_PORT_3)   /* TIM4_PCT: P33 */
#define TIM4_PCT_PIN                    (GPIO_PIN_3)
#define TIM4_PCT_GPIO_FUNC              (GPIO_FUNC_2)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static uint32_t Tmr4PclkFreq(void);
static void TMR4_PeakMatch_IrqCallback(void);

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

/** * @brief  Get TMR4 PCLK frequency.
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
 * @brief  TMR4 Counter peak match interrupt handler callback.
 * @param  None
 * @retval None
 */
static void TMR4_PeakMatch_IrqCallback(void)
{
    BSP_LED_Toggle(LED_GREEN);
    TMR4_CNT_ClearStatus(TMR4_UNIT, TMR4_CNT_FLAG_PEAK);
}

/**
 * @brief  Main function of TMR4 counter triangular wave mode project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_tmr4_cnt_init_t stcTmr4CntInit;
    stc_irq_signin_config_t stcIrqConfig;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize clock. */
    BSP_CLK_Init();
    CLK_ClockDiv(CLK_CATE_ALL, (CLK_PCLK1_DIV32 | CLK_PCLK4_DIV2  | CLK_HCLK_DIV1));

    /* Initialize LED. */
    BSP_LED_Init();

    /* Configure TIM4_<t>_PCT */
    GPIO_SetFunc(TIM4_PCT_PORT, TIM4_PCT_PIN, TIM4_PCT_GPIO_FUNC);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(TMR4_FUNC_CLK_GATE, Enable);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Initialize TMR4 Counter */
    (void)TMR4_CNT_StructInit(&stcTmr4CntInit);
    stcTmr4CntInit.u16CountMode = TMR4_CNT_MD_TRIANGLE;
    stcTmr4CntInit.u16ClockSrc = TMR4_CNT_PCLK;
    stcTmr4CntInit.u16ClockDiv = TMR4_CNT_CLK_DIV1;
    stcTmr4CntInit.u16PeriodValue = (uint16_t)(TMR4_CNT_1S_VALUE(stcTmr4CntInit.u16ClockDiv)/ (8UL * ((uint32_t)TMR4_CNT_INT_MASK15 + 1UL)));
    (void)TMR4_CNT_Init(TMR4_UNIT, &stcTmr4CntInit);

    /* Enable the peak interrupt */
    TMR4_CNT_IntCmd(TMR4_UNIT, TMR4_CNT_INT_PEAK, Enable);

    /* Set TMR4 counter interrupt mask times */
    TMR4_CNT_SetIntMaskTimes(TMR4_UNIT, TMR4_CNT_INT_PEAK, TMR4_CNT_INT_MASK15);

    /* Register IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = TMR4_CNT_OVF_IRQn;
    stcIrqConfig.enIntSrc = TMR4_CNT_OVF_INT_SRC;
    stcIrqConfig.pfnCallback = &TMR4_PeakMatch_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqConfig);
    NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
    NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(stcIrqConfig.enIRQn);

    /* Enable port output TMR4 count direction signal. */
    TMR4_CNT_PortOutputCmd(TMR4_UNIT, Enable);

    /* Start TMR4 counter. */
    TMR4_CNT_Start(TMR4_UNIT);

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
