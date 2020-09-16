/**
 *******************************************************************************
 * @file  timer4/timer4_sevt_delay_trigger/source/main.c
 * @brief This example demonstrates how to use the delay trigger function of
 *        Timer4 SEVT function.
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
 * @addtogroup TMR4_SEVT_Delay_Trigger
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* TMR4 unit && Counter period value definition */
#define TMR4_UNIT                       (CM_TMR4)
#define TMR4_CNT_PERIOD_VALUE(div)      ((uint16_t)((Tmr4PclkFreq() /  (1UL << (uint32_t)(div)) / 4UL))) /* Period_Value(250ms) */

/* TMR4 SEVT port: TIM4_1_ADSM */
#define TMR4_SEVT_PORT                  (GPIO_PORT_0)
#define TMR4_SEVT_PIN                   (GPIO_PIN_2)

/* TMR4 OCO Channel definition */
#define TMR4_OCO_CH                     (TMR4_OCO_CH_UH)

/* TMR4 SEVT channel definition */
#define TMR4_SEVT_CH                    (TMR4_SEVT_CH_UL)

/* TMR4 SEVT delay object definition */
#define TMR4_SEVT_DELAY_OBJECT          (TMR4_SEVT_DELAY_OCCRXH)

/* ADC port & channel */
#define ADC_PORT                        (GPIO_PORT_4)
#define ADC_PIN                         (GPIO_PIN_7)
#define ADC_CH                          (ADC_CH7)

/* Function clock gate definition */
#define FUNC_CLK_GATE                   (CLK_FCG_ADC | CLK_FCG_AOS | CLK_FCG_TMR4)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static uint32_t Tmr4PclkFreq(void);
static void AdcConfig(void);
static void AdcInitConfig(void);
static void AdcChConfig(void);
static void AdcTriggerConfig(void);

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
 * @brief  ADC configuration, including initial configuration,
 *         channel configuration and trigger source configuration.
 * @param  None
 * @retval None
 */
static void AdcConfig(void)
{
    AdcInitConfig();
    AdcChConfig();
    AdcTriggerConfig();
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
    (void)ADC_Init(CM_ADC, &stcAdcInit);
}

/**
 * @brief  Configures ADC channel.
 * @param  None
 * @retval None
 */
static void AdcChConfig(void)
{
    const uint8_t au8SampleTime[] = {30};

    /* 1. Set the ADC pin to analog input mode. */
    GPIO_SetFunc(ADC_PORT, ADC_PIN, GPIO_FUNC_1_ADST);

    /* 2. Enable the ADC channels. */
    (void)ADC_ChCmd(CM_ADC, ADC_SEQ_A, ADC_CH, au8SampleTime, Enable);
}

/**
 * @brief  Configures ADC trigger.
 * @param  None
 * @retval None
 */
static void AdcTriggerConfig(void)
{
    stc_adc_trigger_config_t stcTriggerConfig;

    /* Configures the trigger source of sequence A. */
    (void)ADC_TriggerSrcStructInit(&stcTriggerConfig);
    stcTriggerConfig.enEvent0 = EVT_TMR4_SCMUH;
    stcTriggerConfig.u16TriggerSrc = ADC_TRIG_SRC_EVT0;
    (void)ADC_TriggerSrcConfig(CM_ADC, ADC_SEQ_A, &stcTriggerConfig);
    (void)ADC_TriggerSrcCmd(CM_ADC, ADC_SEQ_A, Enable);
}

/**
 * @brief  Main function of TMR4 SEVT delay trigger
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    static uint16_t m_u16AdcValue = 0U;
    stc_tmr4_cnt_init_t stcTmr4CntInit;
    stc_tmr4_oco_init_t stcTmr4OcoInit;
    stc_tmr4_sevt_init_t stcTmr4SevtInit;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize clock. */
    BSP_CLK_Init();

    /* Initialize UART for debug print function. */
    (void)DDL_PrintfInit();

    /* Configure TMR4 SEVT port*/
    GPIO_SetFunc(TMR4_SEVT_PORT, TMR4_SEVT_PIN, GPIO_FUNC_2_TIM4);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNC_CLK_GATE, Enable);

    /* Configure ADC. */
    AdcConfig();

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /************************* Configure TMR4 counter *************************/
    (void)TMR4_CNT_StructInit(&stcTmr4CntInit);
    stcTmr4CntInit.u16ClockDiv = TMR4_CNT_CLK_DIV1024;
    stcTmr4CntInit.u16PeriodValue = TMR4_CNT_PERIOD_VALUE(stcTmr4CntInit.u16ClockDiv);
    (void)TMR4_CNT_Init(TMR4_UNIT, &stcTmr4CntInit);

    /************************* Configure TMR4 OCO *****************************/
    /* TMR4 OCO: initialize */
    (void)TMR4_OCO_StructInit(&stcTmr4OcoInit);
    stcTmr4OcoInit.u16CompareValue = stcTmr4CntInit.u16PeriodValue/4U;
    (void)TMR4_OCO_Init(TMR4_UNIT, TMR4_OCO_CH, &stcTmr4OcoInit);

    /* TMR4 OCO: enable */
    TMR4_OCO_Cmd(TMR4_UNIT, TMR4_OCO_CH, Enable);

    /************************* Configure TMR4 SEVT ****************************/
    /* TMR4 SEVT: initialize */
    (void)TMR4_SEVT_StructInit(&stcTmr4SevtInit);
    stcTmr4SevtInit.u16CountCompareType = TMR4_SEVT_CNT_CMP_UP;
    stcTmr4SevtInit.u16OutputEvent = TMR4_SEVT_OUTPUT_EVT0;
    stcTmr4SevtInit.u16Mode = TMR4_SEVT_MD_DELAY;
    stcTmr4SevtInit.u16CompareValue = (stcTmr4CntInit.u16PeriodValue/4U);
    (void)TMR4_SEVT_Init(TMR4_UNIT, TMR4_SEVT_CH, &stcTmr4SevtInit);

    /* TMR4 SEVT: set delay object */
    TMR4_SEVT_SetDelayObject(TMR4_UNIT, TMR4_SEVT_CH, TMR4_SEVT_DELAY_OCCRXH);

    /* TMR4 SEVT: set output signal */
    TMR4_SEVT_SetOutputEventSignal(TMR4_UNIT, TMR4_SEVT_OUTPUT_EVT0_SIGNAL);

    /* Start TMR4 counter. */
    TMR4_CNT_Start(TMR4_UNIT);

    for (;;)
    {
        if (Set == ADC_SeqGetStatus(CM_ADC, ADC_SEQ_FLAG_EOCA))
        {
            (void)ADC_GetChData(CM_ADC, ADC_CH, &m_u16AdcValue, 1UL);
            ADC_SeqClearStatus(CM_ADC, ADC_SEQ_FLAG_EOCA);

            (void)printf("ADC sample value: %d\r\n", m_u16AdcValue);
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
