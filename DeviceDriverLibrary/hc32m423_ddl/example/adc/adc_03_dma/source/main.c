/**
 *******************************************************************************
 * @file  adc/adc_03_dma/source/main.c
 * @brief Main program ADC DMA for the Device Driver Library.
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
 * @addtogroup ADC_DMA
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

/*
 * Specifies the ADC channels according to the application.
 * NOTE!!! Sequence A and sequence B CANNOT contain the same channel.
 */
#define ADC_SA_CH                           (ADC_CH2 | ADC_CH3 | ADC_CH7)

#define ADC_SA_CH_NUM_MIN                   (2U)
#define ADC_SA_CH_NUM_MAX                   (7U)

/* Sampling time of ADC channels. */
/*                                        ADC_CH2    ADC_CH3   ADC_CH5 */
#define ADC_SA_SPL_TIME                     { 30,       30,       35 }

/*
 * Add the channels which were included in sequence A or sequence B to average channel if needed.
 * The average channels will be sampled a specified number of times(specified by 'ADC_AVG_CNT'),\
 *   and the final ADC value is the average of the specified number of samples.
 * Define 'ADC_AVG_CH' as 0 to disable average channel.
 */
#define ADC_AVG_CNT                         ((uint16_t)ADC_AVG_CNT8)
#define ADC_AVG_CH                          (ADC_SA_CH)

/*
 * Trigger source definitions.
 * Set pin ADTRG1(PE7) to trigger sequence A. Make a falling edge on ADTRG1 and hold the low level \
 *   at least 1.5 cycles of PCLK4 to trigger sequence A.
 * Both sequences can be set triggered by event or the falling edge of pin ADTRGx(x is ADC unit number, x=1, 2, 3).
 * Only the falling edge of pin ADTRGx and the low level of pin ADTRGx must be held at least 1.5 cycles of PCLK4 can trigger ADC start sampling.
 * ADTRG: PA4, PB4.
 */
#define ADC_SA_TRIG_SRC_TYPE                (ADC_TRIG_SRC_ADTRG)
#define ADC_SA_TRIG_SRC_PORT                (GPIO_PORT_A)
#define ADC_SA_TRIG_SRC_PIN                 (GPIO_PIN_4)
#define ADC_SA_TRIG_PIN_FUNC                (GPIO_FUNC_1_ADTRG)

/*
 * Definitions of DMA.
 * 'ADC_DMA_BLOCK_SIZE': 1~1024, inclusive. 1~16 for ADC1 and ADC2; 1~20 for ADC3.
 * 'ADC_DMA_TRANS_COUNT': 0~65535, inclusive. 0: always transmit.
 */
#define ADC_DMA_UNIT                        (CM_DMA)
#define ADC_DAM_PERIPH_CLK                  (CLK_FCG_DMA)
#define ADC_DMA_CH                          (DMA_CH0)

#define ADC_DMA_TRANS_CNT                   (1UL)
#define ADC_DMA_BLOCK_SIZE                  (ADC_SA_CH_NUM_MAX - ADC_SA_CH_NUM_MIN + 1U)
#define ADC_DMA_DATA_WIDTH                  (DMA_DATA_WIDTH_16BIT)
#define ADC_DMA_SRC_ADDR                    ((uint32_t)(&ADC_UNIT->DR2))
#define ADC_DMA_DEST_ADDR                   ((uint32_t)(&m_au16AdcVal[0U]))
#define ADC_DMA_LLP_MD                      (DMA_LLP_WAIT)
#define ADC_DMA_LLP_POS                     (DMA_CH0CTL0_LLP_POS - 4U)
#define ADC_DMA_TRIG_SRC                    (EVT_ADC_EOCA)
#define ADC_DMA_INT_TYPE                    (DMA_INT_TC0)
#define ADC_DMA_IRQn                        (DMA_TC0_IRQn)
#define ADC_DMA_INT_PRIO                    (DDL_IRQ_PRI03)
#define ADC_DMA_FLAG                        (DMA_INT_TC0)
#define APP_DAM_IRQ_HANDLER                 (DMA_TC0_IrqHandler)

#define ADC_DMA_LLP_MASK                    (DMA_CH0CTL0_LLP)

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
static void AdcDmaConfig(void);
static void AdcDmaIrqConfig(void);
static void AdcTriggerConfig(void);

static void AdcSetChPinAnalogMode(uint32_t u32Ch);
static void AdcSetPinAnalogMode(uint32_t u32ChNum);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint16_t m_au16AdcVal[ADC_DMA_BLOCK_SIZE];
static uint32_t m_u32AdcValUpdated = 0U;


#if defined (__ICCARM__)
_Pragma("data_alignment=16")
static stc_dma_llp_descriptor_t m_stcLlpDesc;
#else
static stc_dma_llp_descriptor_t m_stcLlpDesc __ALIGNED(16);
#endif

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of adc_03_dma project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
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
        /*
         * Make a falling edge on the specified pin ADTRG and hold the low level \
         *   at least 1.5 cycles of PCLK4 to trigger sequence A.
         */
        /* Check ADC sequence A. */
        if ((m_u32AdcValUpdated & ADC_SEQ_FLAG_EOCA) != 0U)
        {
            m_u32AdcValUpdated = 0U;
            DBG("Sequence A DMA block transfer completed.\n");
            /* User code: Use the ADC value of sequence A. */
        }
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
 *         channel configuration, DMA configuration and trigger source configuration.
 * @param  None
 * @retval None
 */
static void AdcConfig(void)
{
    AdcClockConfig();
    AdcInitConfig();
    AdcChConfig();
    AdcDmaConfig();
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

    /* 1. Modify the default value depends on the application. Not needed here. */

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
    AdcSetChPinAnalogMode(ADC_SA_CH);

    /* 2. Enable the ADC channels. */
    (void)ADC_ChCmd(ADC_UNIT, ADC_SEQ_A, \
                    ADC_SA_CH, au8AdcSASplTime, \
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

    /*
     * Configures the trigger source of sequence A.
     * One of ADTRGx(x is the ADC unit number, x=1, 2, 3) pins is configured to trigger sequence A.
     * Make a falling edge on ADTRGx and hold the low level at least 1.5 PCLK4 cycles to trigger sequence A.
     */
    (void)ADC_TriggerSrcStructInit(&stcTrigCfg);
    stcTrigCfg.u16TriggerSrc = ADC_SA_TRIG_SRC_TYPE;
    GPIO_SetFunc(ADC_SA_TRIG_SRC_PORT, \
                 ADC_SA_TRIG_SRC_PIN,  \
                 ADC_SA_TRIG_PIN_FUNC);
    (void)ADC_TriggerSrcConfig(ADC_UNIT, ADC_SEQ_A, &stcTrigCfg);
    ADC_TriggerSrcCmd(ADC_UNIT, ADC_SEQ_A, Enable);
}

/**
 * @brief  DMA configuration.
 * @param  None
 * @retval None
 */
static void AdcDmaConfig(void)
{
    stc_dma_init_t stcDmaInit;
    stc_dma_llp_init_t stcDmaLlpInit;

    /* Descriptor 0 */
    m_stcLlpDesc.SARx    = ADC_DMA_SRC_ADDR;
    m_stcLlpDesc.DARx    = ADC_DMA_DEST_ADDR;
    m_stcLlpDesc.CHxCTL0 = ADC_DMA_BLOCK_SIZE | \
                           (ADC_DMA_TRANS_CNT << DMA_CH0CTL0_CNT_POS) | \
                           (((uint32_t)&m_stcLlpDesc << ADC_DMA_LLP_POS) & ADC_DMA_LLP_MASK) | \
                           DMA_LLP_ENABLE | \
                           ADC_DMA_LLP_MD | \
                           ADC_DMA_DATA_WIDTH;
    m_stcLlpDesc.CHxCTL1 = DMA_SRC_ADDR_MD_INC  | \
                           DMA_DEST_ADDR_MD_INC | \
                           DMA_LLP_ADDR_RAM;

    (void)DMA_LlpStructInit(&stcDmaLlpInit);
    stcDmaLlpInit.u32Llp       = DMA_LLP_ENABLE;
    stcDmaLlpInit.u32LlpMode   = ADC_DMA_LLP_MD;
    stcDmaLlpInit.u32LlpAddr   = (uint32_t)&m_stcLlpDesc;

    /* Config DMA */
    stcDmaInit.u32SrcAddr      = ADC_DMA_SRC_ADDR;
    stcDmaInit.u32DestAddr     = ADC_DMA_DEST_ADDR;
    stcDmaInit.u32DataWidth    = ADC_DMA_DATA_WIDTH;
    stcDmaInit.u32BlockSize    = ADC_DMA_BLOCK_SIZE;
    stcDmaInit.u32TransCount   = ADC_DMA_TRANS_CNT;
    stcDmaInit.u32SrcAddrMode  = DMA_SRC_ADDR_MD_INC;
    stcDmaInit.u32DestAddrMode = DMA_DEST_ADDR_MD_INC;

    CLK_FcgPeriphClockCmd(ADC_DAM_PERIPH_CLK, Enable);
    (void)DMA_LlpInit(ADC_DMA_UNIT, ADC_DMA_CH, &stcDmaLlpInit);
    (void)DMA_Init(ADC_DMA_UNIT, ADC_DMA_CH, &stcDmaInit);

    /* Enable AOS clock */
    CLK_FcgPeriphClockCmd(CLK_FCG_AOS, Enable);
    /* Set DMA trigger source */
    DMA_SetTriggerSrc(ADC_DMA_UNIT, ADC_DMA_CH, ADC_DMA_TRIG_SRC);
    DMA_ClearTransIntStatus(ADC_DMA_UNIT, ADC_DMA_FLAG);

    AdcDmaIrqConfig();
    /* Enable DMA channel. */
    DMA_ChCmd(ADC_DMA_UNIT, ADC_DMA_CH, Enable);
    /* Enable DMA. */
    DMA_Cmd(ADC_DMA_UNIT, Enable);
}

/**
 * @brief  Interrupt configuration.
 * @param  None
 * @retval None
 */
static void AdcDmaIrqConfig(void)
{
    stc_irq_signin_config_t stcCfg;

    stcCfg.enIRQn = ADC_DMA_IRQn;
    (void)INTC_IrqSignIn(&stcCfg);

    NVIC_ClearPendingIRQ(ADC_DMA_IRQn);
    NVIC_SetPriority(ADC_DMA_IRQn, ADC_DMA_INT_PRIO);
    NVIC_EnableIRQ(ADC_DMA_IRQn);

    DMA_TransIntCmd(ADC_DMA_UNIT, ADC_DMA_INT_TYPE, Enable);
}

/**
 * @brief  DMA IRQ handler.
 * @param  None
 * @retval None
 */
void APP_DAM_IRQ_HANDLER(void)
{
    DMA_ClearTransIntStatus(ADC_DMA_UNIT, ADC_DMA_FLAG);
    m_u32AdcValUpdated |= ADC_SEQ_FLAG_EOCA;
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
