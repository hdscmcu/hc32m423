/**
 *******************************************************************************
 * @file  adc/adc_05_extended_channel/source/main.c
 * @brief Main program ADC extended channel for the Device Driver Library.
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
 * @addtogroup ADC_Extended_Channel
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Internal analog source definition. */
#define ADC_INTERN_SRC_TEMPERATURE_SENSOR   (1U)
#define ADC_INTERN_SRC_REF_VOL              (2U)
#define ADC_INTERN_SRC_DAC                  (3U)

#define ADC_INTERN_SRC_SEL                  (ADC_INTERN_SRC_REF_VOL)

#if (ADC_INTERN_SRC_SEL == ADC_INTERN_SRC_TEMPERATURE_SENSOR)
    /* Internal temperature sensor. */
    #define ADC_INTERN_SRC                  (PWC_MON_PWR_TSENSOR)
#elif (ADC_INTERN_SRC_SEL == ADC_INTERN_SRC_REF_VOL)
    /* Internal reference voltage. */
    #define ADC_INTERN_SRC                  (PWC_MON_PWR_IREF)
#endif

/*
 * ADC unit instance for this example.
 * 'ADC_UNIT' can only be defined as CM_ADC.
 */
#define ADC_UNIT                            (CM_ADC)
#define ADC_PERIPH_CLK                      (CLK_FCG_ADC)

/* ADC channels definition for this example. */
#define ADC_SA_CH                           (ADC_EXT_CH)
#define ADC_SA_CH_CNT                       (1U)

/* ADC channel sampling time.               ADC_EXT_CH */
#define ADC_SA_SPL_TIME                     { 25 }

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

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint16_t m_au16AdcSaVal[ADC_SA_CH_CNT];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of adc_05_extended_channel project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    __UNUSED float32_t f32Vol;
    /* The default system clock source is MRC(8MHz). */

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
        (void)ADC_PollingSeqA(ADC_UNIT, m_au16AdcSaVal, ADC_SA_CH_CNT, ADC_TIMEOUT_VALUE);
        f32Vol = ADC_CALC_VOL(m_au16AdcSaVal[0U]);
#if (ADC_INTERN_SRC == PWC_MON_PWR_IREF)
        DBG("Internal reference voltage is %.3fV.\n", f32Vol);
#else
        /* temperature = 25 - (((adc_voltage - 1.03) * 1000) / 3.5) */
        f32Vol = 25.f - ((f32Vol - 1.03f) * 1000.f) / 3.5f;
        DBG("Internal temperature is %.3f.\n", f32Vol);
#endif /* #if (ADC_INTERN_SRC == PWC_MON_PWR_IREF) */
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
    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
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
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
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

    /* 1. Modify the default value depends on the application. It is not needed in this example. */

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

    /* 1. Set the ADC pin to analog input mode. */
    /* Not needed in this example. */

    /* 2. Enable the ADC channels. */
    (void)ADC_ChCmd(ADC_UNIT, ADC_SEQ_A, \
                    ADC_SA_CH, au8AdcSASplTime, \
                    Enable);
#if (ADC_INTERN_SRC_SEL == ADC_INTERN_SRC_TEMPERATURE_SENSOR) || \
    (ADC_INTERN_SRC_SEL == ADC_INTERN_SRC_REF_VOL)
    /* 3. Select internal analog source for ADC extended channel. */
    ADC_SetExtendChSrc(ADC_UNIT, ADC_EXT_CH_SRC_INTERNAL);

    /* 4. Configure PWR monitor and enable it. */
    PWC_MonitorPwrSelect(ADC_INTERN_SRC);
    PWC_MonitorPowerCmd(Enable);

    CLK_FcgPeriphClockCmd(CLK_FCG_CMP, Enable);
    CMP_DAC_ConnectADCCmd(Disable);
#else
    /* 3. Select internal DAC as input source of extended channel. */
    ADC_SetExtendChSrc(ADC_UNIT, ADC_EXT_CH_SRC_ADC_PIN);
    /* 4. Enable DAC to ADC. */
    CLK_FcgPeriphClockCmd(CLK_FCG_CMP, Enable);
    CMP_DAC_ConnectADCCmd(Enable);
#endif
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
