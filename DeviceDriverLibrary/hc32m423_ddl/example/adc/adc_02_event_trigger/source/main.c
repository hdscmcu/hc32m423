/**
 *******************************************************************************
 * @file  adc/adc_02_event_trigger/source/main.c
 * @brief Main program ADC event trigger for the Device Driver Library.
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
 * @addtogroup ADC_Event_Trigger
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*
 * Function control of ADC.
 * Defines the following macro as non-zero to enable the corresponding function.
 */
#define ADC_USE_INTERRUPT                   (1U)

/*
 * ADC unit instance for this example.
 * 'ADC_UNIT' can only be defined as CM_ADC.
 */
#define ADC_UNIT                            (CM_ADC)
#define ADC_PERIPH_CLK                      (CLK_FCG_ADC)

/* Definitions of interrupt. */
#if (ADC_USE_INTERRUPT > 0U)
    #define ADC_SA_IRQn                     (ADC_EOCA_IRQn)
    #define ADC_SB_IRQn                     (ADC_EOCB_IRQn)
    #define ADC_SA_IRQ_PRI                  (DDL_IRQ_PRI03)
    #define ADC_SB_IRQ_PRI                  (DDL_IRQ_PRI04)
#endif

/*
 * Specifies the ADC channels according to the application.
 * NOTE!!! Sequence A and sequence B CANNOT contain the same channel.
 */
#define ADC_SA_CH                           (ADC_CH7)
#define ADC_SA_CH_CNT                       (1U)

#define ADC_SB_CH                           (ADC_CH0 | ADC_CH1)
#define ADC_SB_CH_CNT                       (2U)

/* Check if sequence A and sequence B contain the same channel. */
#if ((ADC_SA_CH & ADC_SB_CH) != 0U)
#error "Sequence A and sequence B contain the same channel!"
#endif

/* Sampling time of ADC channels. */
/*                                        ADC_CH7 */
#define ADC_SA_SPL_TIME                     { 30 }
/*                                        ADC_CH0   ADC_CH1 */
#define ADC_SB_SPL_TIME                     { 35,       35 }

/*
 * Add the channels which were included in sequence A or sequence B to average channel if needed.
 * The average channels will be sampled a specified number of times(specified by 'ADC_AVG_CNT'),\
 *   and the final ADC value is the average of the specified number of samples.
 * Define 'ADC_AVG_CH' as 0 to disable average channel.
 */
#define ADC_AVG_CNT                         ((uint16_t)ADC_AVG_CNT16)
#define ADC_AVG_CH                          (ADC_SA_CH | ADC_SB_CH)

/*
 * Trigger source definitions.
 * Set event 'EVT_TMR0_1_GCMA' to trigger sequence A every second.
 * Set pin ADTRG(PA4) to trigger sequence B. Make a falling edge on ADTRG and hold the low level \
 *   at least 1.5 cycles of PCLK4 to trigger sequence B.
 * Both sequences can be set triggered by event or the falling edge of pin ADTRG.
 * Only the falling edge of pin ADTRG and the low level of pin ADTRG must be held at least 1.5 cycles of PCLK4 can trigger ADC start sampling.
 * ADTRG: PA4, PB4.
 *
 * NOTE!!! Sequence B CAN only be started by event or the falling edge of pin ADTRGx(x is ADC unit number, x=1, 2, 3).
 */
#define ADC_SA_TRIG_SRC_TYPE                (ADC_TRIG_SRC_EVT0)
#define ADC_SA_TRIG_SRC_EVT                 (EVT_TMR0_1_GCMA)

#define ADC_SB_TRIG_SRC_TYPE                (ADC_TRIG_SRC_ADTRG)
#define ADC_SB_TRIG_SRC_PORT                (GPIO_PORT_A)
#define ADC_SB_TRIG_SRC_PIN                 (GPIO_PIN_4)
#define ADC_SB_TRIG_PIN_FUNC                (GPIO_FUNC_1_ADTRG)

/* Debug printing definition. */
#if (DDL_PRINT_ENABLE == DDL_ON)
#define DBG         (void)printf
#else
#define DBG(...)
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);

static void AdcConfig(void);
static void AdcClockConfig(void);
static void AdcInitConfig(void);
static void AdcChConfig(void);
#if (ADC_USE_INTERRUPT > 0U)
    static void AdcIrqConfig(void);
#endif
static void AdcTriggerConfig(void);
static void AdcStartTrigger(void);

static void AdcSetChPinAnalogMode(uint32_t u32Ch);
static void AdcSetPinAnalogMode(uint32_t u32ChNum);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint16_t m_au16AdcSaVal[ADC_SA_CH_CNT];
static uint16_t m_au16AdcSbVal[ADC_SB_CH_CNT];

#if (ADC_USE_INTERRUPT > 0U)
    static uint32_t m_u32AdcIrqFlag = 0U;
#endif /* #if (ADC_USE_INTERRUPT > 0U) */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of adc_02_event_trigger project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* MCU Peripheral registers write unprotected. */
    Peripheral_WE();
#if (DDL_PRINT_ENABLE == DDL_ON)
    /* Initializes UART for debug printing. Baudrate is 115200. */
    (void)DDL_PrintfInit();
#endif /* #if (DDL_PRINT_ENABLE == DDL_ON) */
    /* Configures ADC. */
    AdcConfig();
    /* MCU Peripheral registers write protected. */
    Peripheral_WP();
    /* Start the trigger-source peripheral. */
    AdcStartTrigger();

    /***************** Configuration end, application start **************/

    for (;;)
    {
        /*
         * Timer0 triggers sequence A one time every second.
         * Make a falling edge on the specified pin ADTRGx and hold the low level \
         *   at least 1.5 cycles of PCLK4 to trigger sequence B.
         */
#if (ADC_USE_INTERRUPT > 0U)
        if ((m_u32AdcIrqFlag & ADC_SEQ_FLAG_EOCA) != 0U)
        {
            DBG("ADC sequence A is triggered by Timer0 every second.\n");
            m_u32AdcIrqFlag &= (uint32_t)(~ADC_SEQ_FLAG_EOCA);
        }
        if ((m_u32AdcIrqFlag & ADC_SEQ_FLAG_EOCB) != 0U)
        {
            DBG("ADC sequence B is triggered by the falling edge of the specified pin ADTRGx.\n");
            m_u32AdcIrqFlag &= (uint32_t)(~ADC_SEQ_FLAG_EOCB);
        }
#else
        if (ADC_SeqGetStatus(ADC_UNIT, ADC_SEQ_FLAG_EOCA) == Set)
        {
            ADC_SeqClearStatus(ADC_UNIT, ADC_SEQ_FLAG_EOCA);
            ADC_GetChData(ADC_UNIT, ADC_SA_CH, m_au16AdcSaVal, ADC_SA_CH_CNT);
            DBG("ADC sequence A is triggered by Timer0 every second.\n");
        }

        if (ADC_SeqGetStatus(ADC_UNIT, ADC_SEQ_FLAG_EOCB) == Set)
        {
            ADC_SeqClearStatus(ADC_UNIT, ADC_SEQ_FLAG_EOCB);
            ADC_GetChData(ADC_UNIT, ADC_SB_CH, m_au16AdcSbVal, ADC_SB_CH_CNT);
            DBG("ADC sequence B is triggered by the falling edge of the specified pin ADTRGx.\n");
        }
#endif
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
    PWC_Unlock(PWC_UNLOCK_CODE_0);
    /* Unlock all EFM registers */
    /* EFM_Unlock(); */
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
    PWC_Lock(PWC_UNLOCK_CODE_0);
    /* Lock all EFM registers */
    /* EFM_Lock(); */
}

/**
 * @brief  ADC configuration, including clock configuration, initial configuration
 *         channel configuration, interrupt configuration and trigger source configuration.
 * @param  None
 * @retval None
 */
static void AdcConfig(void)
{
    AdcClockConfig();
    AdcInitConfig();
    AdcChConfig();
#if (ADC_USE_INTERRUPT > 0U)
    AdcIrqConfig();
#endif
    AdcTriggerConfig();
}

/**
 * @brief  Configures ADC clock.
 * @param  None
 * @retval None
 */
static void AdcClockConfig(void)
{
	/* ADC clock: PCLK4/n, n=1,2,3,...,8; max 32MHz. */
	CLK_SetADCClockDiv(CLK_ADCCLK_PCLK4_DIV4);
}

/**
 * @brief  Initializes ADC.
 * @param  None
 * @retval None
 */
static void AdcInitConfig(void)
{
    stc_adc_init_t stcAdcInit;

    /* Set a default value. */
    (void)ADC_StructInit(&stcAdcInit);

    /* 1. Modify the default value depends on the application. */
    stcAdcInit.u16ScanMode    = ADC_MD_SA_SB_SSHOT;
    stcAdcInit.u16SAResumePos = ADC_SA_RESUME_POS_INT_CH;

    /* 2. Enable ADC peripheral clock. */
    CLK_FcgPeriphClockCmd(ADC_PERIPH_CLK, Enable);

    /* 3. Initializes ADC. */
    (void)ADC_Init(ADC_UNIT, &stcAdcInit);
}

/**
 * @brief  Configures ADC channel(s).
 * @param  None
 * @retval None
 */
static void AdcChConfig(void)
{
    const uint8_t au8AdcSASplTime[] = ADC_SA_SPL_TIME;
    const uint8_t au8AdcSBSplTime[] = ADC_SB_SPL_TIME;

    /* 1. Set the ADC pin to analog input mode. */
    AdcSetChPinAnalogMode(ADC_SA_CH | ADC_SB_CH);

    /* 2. Enable the ADC channels. */
    (void)ADC_ChCmd(ADC_UNIT, ADC_SEQ_A, \
                    ADC_SA_CH, au8AdcSASplTime, \
                    Enable);

    (void)ADC_ChCmd(ADC_UNIT, ADC_SEQ_B, \
                    ADC_SB_CH, au8AdcSBSplTime, \
                    Enable);

    /* 3. Set the number of averaging sampling and enable the channel, if needed. */
#if (defined ADC_AVG_CH) && (ADC_AVG_CH != 0U)
    ADC_SetAverageCount(ADC_UNIT, ADC_AVG_CNT);
    ADC_AverageChCmd(ADC_UNIT, ADC_AVG_CH, Enable);
#endif
}

/**
 * @brief  Trigger source configuration. Specify trigger source for sequence A and sequence B.
 * @param  None
 * @retval None
 */
static void AdcTriggerConfig(void)
{
    stc_adc_trigger_config_t stcTrigCfg;
    stc_tmr0_init_t stcTmr0Init;

    /*
     * If select an event as the trigger source of sequence A or sequence B, \
     *   the AOS function must be enabled at first.
     */
    CLK_FcgPeriphClockCmd(CLK_FCG_AOS, Enable);

    /*
     * Configures the trigger source of sequence A.
     * An event that generated by other peripheral is configured as the trigger source of sequence A.
     * Sequence A is triggered by Timer0 every second.
     */
    (void)TMR0_StructInit(&stcTmr0Init);
    stcTmr0Init.u32ClockSrc = TMR0_SYNC_CLK_PCLK;
    stcTmr0Init.u32ClockDiv = TMR0_CLK_DIV512;
    stcTmr0Init.u16PeriodValue = 15625U - 1U;
    CLK_FcgPeriphClockCmd(CLK_FCG_TMR0_1, Enable);
    (void)TMR0_Init(CM_TMR0_1, TMR0_CH_A, &stcTmr0Init);

    (void)ADC_TriggerSrcStructInit(&stcTrigCfg);
    stcTrigCfg.u16TriggerSrc = ADC_SA_TRIG_SRC_TYPE;
    stcTrigCfg.enEvent0      = ADC_SA_TRIG_SRC_EVT;
    (void)ADC_TriggerSrcConfig(ADC_UNIT, ADC_SEQ_A, &stcTrigCfg);
    ADC_TriggerSrcCmd(ADC_UNIT, ADC_SEQ_A, Enable);

    /*
     * Configures the trigger source of sequence B.
     * One of ADTRGx(x is the ADC unit number, x=1, 2, 3) pins is configured to trigger sequence B.
     * Make a falling edge on ADTRGx and hold the low level at least 1.5 PCLK4 cycles to trigger sequence B.
     */
    stcTrigCfg.u16TriggerSrc = ADC_SB_TRIG_SRC_TYPE;
    GPIO_SetFunc(ADC_SB_TRIG_SRC_PORT, \
                 ADC_SB_TRIG_SRC_PIN,  \
                 ADC_SB_TRIG_PIN_FUNC);
    (void)ADC_TriggerSrcConfig(ADC_UNIT, ADC_SEQ_B, &stcTrigCfg);
    ADC_TriggerSrcCmd(ADC_UNIT, ADC_SEQ_B, Enable);
}

/**
 * @brief  Start the peripheral which is used to generate the trigger source to trigger ADC.
 * @param  None
 * @retval None
 */
static void AdcStartTrigger(void)
{
    /* For sequence A. Start the peripheral anywhere you want. */
    TMR0_Start(CM_TMR0_1, TMR0_CH_A);

    /*
     * For sequence B. Make a falling edge on the specified ADTRGx pin and hold the low level \
     *   at least 1.5 PCLK4 cycles to trigger sequence B.
     */
}

#if (ADC_USE_INTERRUPT > 0U)
/**
 * @brief  Interrupt configuration.
 * @param  None
 * @retval None
 */
static void AdcIrqConfig(void)
{
    stc_irq_signin_config_t stcCfg;

    /* Configures interrupt of sequence A. */
    stcCfg.enIRQn = ADC_SA_IRQn;
    (void)INTC_IrqSignIn(&stcCfg);
    NVIC_ClearPendingIRQ(stcCfg.enIRQn);
    NVIC_SetPriority(stcCfg.enIRQn, ADC_SA_IRQ_PRI);
    NVIC_EnableIRQ(stcCfg.enIRQn);

    /* Configures interrupt of sequence B. */
    stcCfg.enIRQn = ADC_SB_IRQn;
    (void)INTC_IrqSignIn(&stcCfg);
    NVIC_ClearPendingIRQ(stcCfg.enIRQn);
    NVIC_SetPriority(stcCfg.enIRQn, ADC_SB_IRQ_PRI);
    NVIC_EnableIRQ(stcCfg.enIRQn);

    /* Enable the interrupts of both sequences. */
    ADC_SeqIntCmd(ADC_UNIT, ADC_SEQ_A, Enable);
    ADC_SeqIntCmd(ADC_UNIT, ADC_SEQ_B, Enable);
}

/**
 * @brief  Sequence A IRQ handler.
 * @param  None
 * @retval None
 */
void ADC_SeqA_IrqHandler(void)
{
    ADC_SeqClearStatus(ADC_UNIT, ADC_SEQ_FLAG_EOCA);
    (void)ADC_GetChData(ADC_UNIT, ADC_SA_CH, m_au16AdcSaVal, ADC_SA_CH_CNT);
    m_u32AdcIrqFlag |= ADC_SEQ_FLAG_EOCA;
}

/**
 * @brief  Sequence B IRQ handler.
 * @param  None
 * @retval None
 */
void ADC_SeqB_IrqHandler(void)
{
    ADC_SeqClearStatus(ADC_UNIT, ADC_SEQ_FLAG_EOCB);
    (void)ADC_GetChData(ADC_UNIT, ADC_SB_CH, m_au16AdcSbVal, ADC_SB_CH_CNT);
    m_u32AdcIrqFlag |= ADC_SEQ_FLAG_EOCB;
}
#endif /* #if (ADC_USE_INTERRUPT > 0U) */

/**
 * @brief  Set the pin(s) corresponding to the specified channel(s) to analog mode.
 * @param  [in]  u32Ch                  The specified channel(s).
 * @retval None
 */
static void AdcSetChPinAnalogMode(uint32_t u32Ch)
{
    uint32_t u32ChNum = 0UL;

    u32Ch &= ADC_CH_ALL;

    while (u32Ch != 0UL)
    {
        if ((u32Ch & 0x1UL) != 0UL)
        {
            AdcSetPinAnalogMode(u32ChNum);
        }

        u32Ch >>= 1U;
        u32ChNum++;
    }
}

/**
 * @brief  Set specified ADC pin to analog mode.
 * @param  [in]  u32ChNum               The ADC channel number.
 *                                      This parameter can be a value of @ref ADC_Channel_Number
 * @retval None
 */
static void AdcSetPinAnalogMode(uint32_t u32ChNum)
{
    uint8_t u8Port = GPIO_PORT_4;
    uint8_t u8Pin  = GPIO_PIN_0;
    uint8_t u8Flag = 1U;

    switch (u32ChNum)
    {
    case ADC_CH_NUM0:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_0;
        break;

    case ADC_CH_NUM1:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_1;
        break;

    case ADC_CH_NUM2:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_2;
        break;

    case ADC_CH_NUM3:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_3;
        break;

    case ADC_CH_NUM4:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_4;
        break;

    case ADC_CH_NUM5:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_5;
        break;

    case ADC_CH_NUM6:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_6;
        break;

    case ADC_CH_NUM7:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_7;
        break;

    case ADC_CH_NUM8:
        u8Port = GPIO_PORT_1;
        u8Pin  = GPIO_PIN_1;
        break;

    case ADC_CH_NUM9:
        u8Port = GPIO_PORT_1;
        u8Pin  = GPIO_PIN_0;
        break;

    default:
        u8Flag = 0U;
        break;
    }

    if (u8Flag != 0U)
    {
        GPIO_SetFunc(u8Port, u8Pin, GPIO_FUNC_1_ANA);
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
