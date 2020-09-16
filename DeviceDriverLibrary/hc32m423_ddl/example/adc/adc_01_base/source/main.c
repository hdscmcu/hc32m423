/**
 *******************************************************************************
 * @file  adc/adc_01_base/source/main.c
 * @brief Main program ADC base for the Device Driver Library.
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
 * @addtogroup ADC_Base
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*
 * ADC unit instance for this example.
 * 'ADC_UNIT' can only be defined as CM_ADC.
 */
#define ADC_UNIT                            (CM_ADC)
#define ADC_PERIPH_CLK                      (CLK_FCG_ADC)

/* Specify the ADC channels according to the application. */
#define ADC_SA_CH                           (ADC_CH1 | ADC_CH2 | ADC_CH7)
#define ADC_SA_CH_CNT                       (3U)

/* Sampling time of ADC channels. */
/*                                         ADC_CH1, ADC_CH2, ADC_CH7 */
#define ADC_SA_SPL_TIME                     { 30,      30,      35 }

/*
 * Add the channels which were included in sequence A(or sequence B, there is only sequence \
 *   A in this example that defined as 'ADC_SA_CH') to average channel if needed.
 * The average channels will be sampled a specified number of times(specified by 'ADC_AVG_CNT'),\
 *   and the final ADC value is the average of the specified number of samples.
 * Define 'ADC_AVG_CH' as 0 to disable average channel.
 */
#define ADC_AVG_CNT                         ((uint16_t)ADC_AVG_CNT8)
#define ADC_AVG_CH                          (ADC_SA_CH)

/* ADC reference voltage. The voltage of pin VREFH. */
#define ADC_VREF                            (3.319f)

/* ADC accuracy(according to the resolution of ADC). */
#define ADC_ACCURACY                        (1UL << 12U)

/* Calculate the voltage. */
#define ADC_CALC_VOL(adcVal)                ((float)(adcVal) * ADC_VREF) / ((float)ADC_ACCURACY)

/* Timeout value definitions. */
#define ADC_TIMEOUT_VALUE                   (1000U)

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

static void AdcSetChPinAnalogMode(uint32_t u32Ch);
static void AdcSetPinAnalogMode(uint32_t u32ChNum);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint16_t m_au16AdcSaValue[ADC_SA_CH_CNT];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of adc_01_base project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    __UNUSED float32_t f32Voltage;

    /* The default system clock is MRC(8MHz). */

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

    /***************** Configuration end, application start **************/

    for (;;)
    {
        (void)ADC_PollingSeqA(ADC_UNIT, m_au16AdcSaValue, ADC_SA_CH_CNT, ADC_TIMEOUT_VALUE);
        f32Voltage = ADC_CALC_VOL(m_au16AdcSaValue[2U]);
#if (DDL_PRINT_ENABLE == DDL_ON)
        DBG("The ADC value of potentiometer is %u, voltage is %.3f.\n", \
             m_au16AdcSaValue[2U], f32Voltage);
#endif /* #if (DDL_PRINT_ENABLE == DDL_ON) */
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
 *         and channel configuration.
 * @param  None
 * @retval None
 */
static void AdcConfig(void)
{
    AdcClockConfig();
    AdcInitConfig();
    AdcChConfig();
}

/**
 * @brief  Configures ADC clock.
 *         The clock of ADC: HRC32MHz / 2 = 16MHz.
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

    /* User configurations. e.g. */
    /* stcAdcInit.u16Resolution = ADC_RESOLUTION_10BIT; */

    /* 1. Enable ADC peripheral. */
    CLK_FcgPeriphClockCmd(ADC_PERIPH_CLK, Enable);

    /* 2. Initializes ADC. */
    (void)ADC_Init(ADC_UNIT, &stcAdcInit);
}

/**
 * @brief  Configures ADC channel(s).
 * @param  None
 * @retval None
 */
static void AdcChConfig(void)
{
    const uint8_t au8SampleTime[] = ADC_SA_SPL_TIME;

    /* 1. Set the ADC pin to analog input mode. */
    AdcSetChPinAnalogMode(ADC_SA_CH);

    /* 2. Enable the ADC channels. */
    (void)ADC_ChCmd(ADC_UNIT,             \
                    ADC_SEQ_A, ADC_SA_CH, \
                    au8SampleTime,        \
                    Enable);

    /* 3. Set the number of averaging sampling and enable the channel, if needed. */
#if (defined ADC_AVG_CH) && (ADC_AVG_CH != 0U)
    ADC_SetAverageCount(ADC_UNIT, ADC_AVG_CNT);
    ADC_AverageChCmd(ADC_UNIT, ADC_AVG_CH, Enable);
#endif
}

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
