/**
 *******************************************************************************
 * @file  timerb/timerb_input_capture/source/main.c
 * @brief This example demonstrates TMRB input capture function.
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
 * @addtogroup TMRB_Input_Capture
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief  Buffer structure definition
 */
typedef struct
{
    uint16_t u16Capacity;
    uint16_t u16Index;
    uint16_t au16Buf[50];
} stc_buffer_t;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* EXTINT channel/IRQn definition */
#define EXTINT_CH                       (EXTINT_CH05)
#define EXTINT_INT                      (INT_PORT_EIRQ5)
#define EXTINT_IRQn                     (INT000_IRQn)

/* EXTINT Port/Pin definition */
#define EXTINT_PORT                     (GPIO_PORT_0)
#define EXTINT_PIN                      (GPIO_PIN_2)

/* TMRB unit & interrupt number & counter period definition */
#define TMRB_UNIT                       (CM_TMRB)
#define TMRB_CNT_1S_VALUE(div)          ((TmrbPclkFreq() / (uint32_t)(div))) /* Period_Value(1000ms) */
#define TMRB_INT_SRC                    (INT_TMRB_CMP)
#define TMRB_IRQn                       (INT001_IRQn)
#define TMRB_EVT_SRC                    (EVT_PORT_EIRQ5)

/* TMRB input capture channel definition */
#define TMRB_ODD_CH                     (TMRB_CH1)
#define TMRB_ODD_CH_FLAG                (TMRB_FLAG_CMP1)
#define TMRB_ODD_CH_INT                 (TMRB_INT_CMP1)

#define TMRB_EVEN_CH                    (TMRB_CH2)
#define TMRB_EVEN_CH_FLAG               (TMRB_FLAG_CMP2)
#define TMRB_EVEN_CH_INT                (TMRB_INT_CMP2)

/* TMRB PWM channel definition */
#define TMRB_PWM_CH                     (TMRB_CH3)

/* TMRB TIMB_t_PWM1 Port/Pin definition */
#define TIMB_1_PWM1_PORT                (GPIO_PORT_7)     /* P72: TIMB_1_PWM1 */
#define TIMB_1_PWM1_PIN                 (GPIO_PIN_2)
#define TIMB_1_PWM1_GPIO_FUNC           (GPIO_FUNC_3_TIMB1_PWM1)

#define TIMB_1_PWM2_PORT                (GPIO_PORT_7)     /* P75: TIMB_1_PWM2 */
#define TIMB_1_PWM2_PIN                 (GPIO_PIN_5)
#define TIMB_1_PWM2_GPIO_FUNC           (GPIO_FUNC_3_TIMB1_PWM2)

#define TIMB_1_PWM3_PORT                (GPIO_PORT_7)     /* P71: TIMB_1_PWM3 */
#define TIMB_1_PWM3_PIN                 (GPIO_PIN_1)
#define TIMB_1_PWM3_GPIO_FUNC           (GPIO_FUNC_3_TIMB1_PWM3)

/* Function clock gate definition */
#define FUNC_CLK_GATE                   (CLK_FCG_TMRB | CLK_FCG_AOS)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static void ExtintConfig(void);
static void EXTINT_IrqCallback(void);
static uint32_t TmrbPclkFreq(void);
static void TMRB_CmpIrqCallback(void);
static void BufferWrite(stc_buffer_t *pstcBuf, uint16_t u16Data);

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
 * @brief  Configure EXTINT.
 * @param  None
 * @retval None
 */
static void ExtintConfig(void)
{
    stc_gpio_init_t stcGpioInit;
    stc_extint_init_t stcExtintInit;
    stc_irq_signin_config_t stcIrqConfig;

    /* External interrupt port initialize */
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExtInt = PIN_EXTINT_ON;
    (void)GPIO_Init(EXTINT_PORT, EXTINT_PIN, &stcGpioInit);

    /* EXTINT Channel configure */
    (void)EXTINT_StructInit(&stcExtintInit);
    stcExtintInit.u32ExtIntFilterA = EXTINT_FILTER_A_ON;
    stcExtintInit.u32ExtIntFilterAClock = EXTINT_FILTER_A_CLK_DIV8;
    stcExtintInit.u32ExtIntLevel = EXTINT_TRIG_FALLING;
    (void)EXTINT_Init(EXTINT_CH, &stcExtintInit);

    /* Register IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = EXTINT_IRQn;
    stcIrqConfig.enIntSrc = EXTINT_INT;
    stcIrqConfig.pfnCallback = &EXTINT_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqConfig);
    NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
    NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(stcIrqConfig.enIRQn);
}

/**
 * @brief  External interrupt ISR
 * @param  None
 * @retval None
 */
static void EXTINT_IrqCallback(void)
{
   if (Set == EXTINT_GetExtIntStatus(EXTINT_CH))
   {
        EXTINT_ClearExtIntStatus(EXTINT_CH);
        BSP_LED_On(LED_GREEN);
   }
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
 * @brief  TMRB unit compare match IRQ callback
 * @param  None
 * @retval None
 */
static void TMRB_CmpIrqCallback(void)
{
    static stc_buffer_t m_stcEvenUnitCmpBuf= {
        .u16Index = 0U,
        .u16Capacity = (sizeof(m_stcEvenUnitCmpBuf.au16Buf)/2U),
    };

    static stc_buffer_t m_stcOddUnitCmpBuf = {
        .u16Index = 0U,
        .u16Capacity = (sizeof(m_stcOddUnitCmpBuf.au16Buf)/2U),
    };

    if (Set == TMRB_GetStatus(TMRB_UNIT, TMRB_ODD_CH_FLAG))
    {
        BufferWrite(&m_stcOddUnitCmpBuf, TMRB_GetCompareValue(TMRB_UNIT, TMRB_ODD_CH));
        TMRB_ClearStatus(TMRB_UNIT, TMRB_ODD_CH_FLAG);
    }

    if (Set == TMRB_GetStatus(TMRB_UNIT, TMRB_EVEN_CH_FLAG))
    {
        BufferWrite(&m_stcEvenUnitCmpBuf, TMRB_GetCompareValue(TMRB_UNIT, TMRB_EVEN_CH));
        TMRB_ClearStatus(TMRB_UNIT, TMRB_EVEN_CH_FLAG);
    }
}

/**
 * @brief  Push data into buffer.
 * @param  [in] pstcBuf              Pointer to a @ref stc_buffer_t structure
 * @param  [in] u16Data                 Data to write into buffer
 * @retval None
 */
static void BufferWrite(stc_buffer_t *pstcBuf, uint16_t u16Data)
{
    if (pstcBuf->u16Index >= pstcBuf->u16Capacity)
    {
        pstcBuf->u16Index = 0U;
    }

    pstcBuf->au16Buf[pstcBuf->u16Index] = u16Data;

    pstcBuf->u16Index++;
}

/**
 * @brief  Main function of TMRB input capture project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_irq_signin_config_t stcIrqConfig;
    stc_tmrb_init_t stcTmrbInit;
    stc_tmrb_pwm_init_t stcTmrbPwmInit;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize system clock. */
    BSP_CLK_Init();

    /* Initialize LED. */
    BSP_LED_Init();

    /* Configure EXTINT. */
    ExtintConfig();

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNC_CLK_GATE, Enable);

    /* Configure TIM_<t>_PWM. */
    GPIO_SetFunc(TIMB_1_PWM1_PORT, TIMB_1_PWM1_PIN, TIMB_1_PWM1_GPIO_FUNC);
    GPIO_SetFunc(TIMB_1_PWM2_PORT, TIMB_1_PWM2_PIN, TIMB_1_PWM2_GPIO_FUNC);
    GPIO_SetFunc(TIMB_1_PWM3_PORT, TIMB_1_PWM3_PIN, TIMB_1_PWM3_GPIO_FUNC);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Initialize TMRB unit. */
    stcTmrbInit.u16ClockDiv = TMRB_CLK_DIV1024;
    stcTmrbInit.u16CountMode = TMRB_MD_SAWTOOTH;
    stcTmrbInit.u16CountDir = TMRB_DIR_UP;
    stcTmrbInit.u16PeriodValue = (uint16_t)(TMRB_CNT_1S_VALUE(1024UL)/2UL);
    (void)TMRB_Init(TMRB_UNIT, &stcTmrbInit);

    /* Initialize TMRB output compare function . */
    stcTmrbPwmInit.u16CompareValue = (stcTmrbInit.u16PeriodValue/2U);
    stcTmrbPwmInit.u16StartPolarity = TMRB_PWM_HIGH;
    stcTmrbPwmInit.u16StopPolarity = TMRB_PWM_HIGH;
    stcTmrbPwmInit.u16MatchPolarity = TMRB_PWM_INVT;
    stcTmrbPwmInit.u16PeriodPolarity = TMRB_PWM_INVT;
    (void)TMRB_PWM_Init(TMRB_UNIT, TMRB_PWM_CH, &stcTmrbPwmInit);

    /* Enable PWM port output */
    TMRB_PWM_Cmd(TMRB_UNIT, TMRB_PWM_CH, Enable);

   /* Configure TMRB odd channel input capture function. */
    TMRB_IntCmd(TMRB_UNIT, TMRB_ODD_CH_INT, Enable);
    TMRB_SetFunc(TMRB_UNIT, TMRB_ODD_CH, TMRB_FUNC_CAPT);
    TMRB_HWCaptureCondCmd(TMRB_UNIT, TMRB_ODD_CH, TMRB_CAPT_COND_PWMF, Enable);

    /* Configure TMRB even channel input capture function. */
    TMRB_IntCmd(TMRB_UNIT, TMRB_EVEN_CH_INT, Enable);
    TMRB_SetFunc(TMRB_UNIT, TMRB_EVEN_CH, TMRB_FUNC_CAPT);
    TMRB_HWCaptureCondCmd(TMRB_UNIT, TMRB_EVEN_CH, TMRB_CAPT_COND_PWMF, Enable);

    /* Register IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = TMRB_IRQn;
    stcIrqConfig.enIntSrc = TMRB_INT_SRC;
    stcIrqConfig.pfnCallback = &TMRB_CmpIrqCallback;
    (void)INTC_IrqSignIn(&stcIrqConfig);
    NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
    NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(stcIrqConfig.enIRQn);

    /* Set trigger source. */
    TMRB_SetTriggerSrc(TMRB_UNIT, TMRB_EVT_SRC);

    /* Set TMRB start count condition. */
    TMRB_HWStartCondCmd(TMRB_UNIT, TMRB_START_COND_EVT, Enable);

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
