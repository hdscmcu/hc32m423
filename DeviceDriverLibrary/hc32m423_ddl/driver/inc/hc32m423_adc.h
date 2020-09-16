/**
 *******************************************************************************
 * @file  hc32m423_adc.h
 * @brief This file contains all the functions prototypes of the ADC driver
 *        library.
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
#ifndef __HC32M423_ADC_H__
#define __HC32M423_ADC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_ADC
 * @{
 */

#if (DDL_ADC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Types ADC Global Types
 * @{
 */

/**
 * @brief Structure definition of ADC initialization.
 */
typedef struct
{
    uint16_t u16ScanMode;       /*!< Configures the scan convert mode of ADC.
                                     This parameter can be a value of @ref ADC_Scan_Convert_Mode */
    uint16_t u16Resolution;     /*!< Configures the ADC resolution.
                                     This parameter can be a value of @ref ADC_Resolution */
    uint16_t u16AutoClear;      /*!< Configures whether the ADC data register is
                                     automatically cleared after the data is read.
                                     This parameter can be a value of @ref ADC_Data_Auto_Clear_Cmd */
    uint16_t u16DataAlign;      /*!< Specifies ADC data alignment to right or to left.
                                     This parameter can be a value of @ref ADC_Data_Alignment */
    uint16_t u16SAResumePos;    /*!< Specifies the resume channel position of sequence A.
                                     Sequence A can be interrupted by sequence B. After the
                                     the ending of sequence B, sequence A resumes from the
                                     specified channel position.
                                     This parameter can be a value of @ref ADC_Sequence_A_Resume_Channel_Position */
} stc_adc_init_t;

/**
 * @brief Structure definition of ADC trigger source configuration.
 */
typedef struct
{
    uint16_t u16TriggerSrc;     /*!< Specifies the trigger source type for the specified sequence.
                                     This parameter can be a value of @ref ADC_Trigger_Source_Type */
    en_event_src_t enEvent0;    /*!< An @ref en_event_src_t enumeration value. */
    en_event_src_t enEvent1;    /*!< An @ref en_event_src_t enumeration value. */
} stc_adc_trigger_config_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Macros ADC Global Macros
 * @{
 */

/**
 * @defgroup ADC_Sequence ADC Sequence
 * @{
 */
#define ADC_SEQ_A                       (0U)
#define ADC_SEQ_B                       (1U)
/**
 * @}
 */

/**
 * @defgroup ADC_Scan_Convert_Mode ADC Scan Convert Mode
 * @{
 */
#define ADC_MD_SA_SSHOT                 (0x0U)              /*!< Sequence A single shot. */
#define ADC_MD_SA_CONT                  (ADC_CR0_MS_0)      /*!< Sequence A continuous. */
#define ADC_MD_SA_SB_SSHOT              (ADC_CR0_MS_1)      /*!< Sequence A and B both single shot. */
#define ADC_MD_SA_CONT_SB_SSHOT         (ADC_CR0_MS)        /*!< Sequence A continuous and sequence B single shot. */
/**
 * @}
 */

/**
 * @defgroup ADC_Resolution ADC Resolution
 * @{
 */
#define ADC_RESOLUTION_12BIT            (0x0U)              /*!< Resolution is 12 bit. */
#define ADC_RESOLUTION_10BIT            (ADC_CR0_ACCSEL_0)  /*!< Resolution is 10 bit. */
#define ADC_RESOLUTION_8BIT             (ADC_CR0_ACCSEL_1)  /*!< Resolution is 8 bit. */
/**
 * @}
 */

/**
 * @defgroup ADC_Data_Auto_Clear_Cmd ADC Data Auto Clear Cmd
 * @{
 */
#define ADC_AUTO_CLR_DISABLE            (0x0U)
#define ADC_AUTO_CLR_ENABLE             (ADC_CR0_CLREN)     /*!< ADC data register is automatically cleared after the data is read. */
/**
 * @}
 */

/**
 * @defgroup ADC_Data_Alignment ADC Data Alignment
 * @{
 */
#define ADC_DATA_ALIGN_RIGHT            (0x0U)
#define ADC_DATA_ALIGN_LEFT             (ADC_CR0_DFMT)
/**
 * @}
 */

/**
 * @defgroup ADC_Average_Count ADC Average Count
 * @{
 */
#define ADC_AVG_CNT2                    (0x0U)
#define ADC_AVG_CNT4                    (0x1UL << ADC_CR0_AVCNT_POS)
#define ADC_AVG_CNT8                    (0x2UL << ADC_CR0_AVCNT_POS)
#define ADC_AVG_CNT16                   (0x3UL << ADC_CR0_AVCNT_POS)
#define ADC_AVG_CNT32                   (0x4UL << ADC_CR0_AVCNT_POS)
#define ADC_AVG_CNT64                   (0x5UL << ADC_CR0_AVCNT_POS)
#define ADC_AVG_CNT128                  (0x6UL << ADC_CR0_AVCNT_POS)
#define ADC_AVG_CNT256                  (0x7UL << ADC_CR0_AVCNT_POS)
/**
 * @}
 */

/**
 * @defgroup ADC_Sequence_A_Resume_Channel_Position ADC Sequence A Resume Channel Position
 * @{
 */
#define ADC_SA_RESUME_POS_INT_CH        (0x0U)                      /*!< Resumes from the interrupt channel of the sequence. */
#define ADC_SA_RESUME_POS_FIRST_CH      (ADC_CR1_RSCHSEL)           /*!< Resumes from the first channel of the sequence. */
/**
 * @}
 */

/**
 * @defgroup ADC_Trigger_Source_Type ADC Trigger Source Type
 * @{
 */
#define ADC_TRIG_SRC_ADTRG              (0x0U)                      /*!< The trigger source is the falling edge(the low level of the should \
                                                                         hold at least 1.5*PCLK cycle) of external pin ADTRGx(x=1, 2, 3). */
#define ADC_TRIG_SRC_EVT0               (ADC_TRGSR_TRGSELA_0)       /*!< The trigger source is a internal event from other peripheral. \
                                                                         Only one event can be configured to trigger ADC. */
#define ADC_TRIG_SRC_EVT1               (ADC_TRGSR_TRGSELA_1)       /*!< The trigger source is a internal event from other peripheral. \
                                                                         Only one event can be configured to trigger ADC. */
#define ADC_TRIG_SRC_EVT0_EVT1          (ADC_TRGSR_TRGSELA)         /*!< The trigger source are two internal events from other peripheral(s). \
                                                                         Two events can be configured to trigger ADC and one of which can trigger the ADC. */
/**
 * @}
 */

/**
 * @defgroup ADC_Extend_Channel_Source ADC Extend Channel Source
 * @{
 */
#define ADC_EXT_CH_SRC_ADC_PIN          (0x0U)                      /*!< The input source of the extended channel is analog input pin. */
#define ADC_EXT_CH_SRC_INTERNAL         (ADC_EXCHSELR_EXCHSEL)      /*!< The input source of the extended channel is internal analog signal. */
/**
 * @}
 */

/**
 * @defgroup ADC_Sequence_Status_Flag ADC Sequence Status Flag
 * @{
 */
#define ADC_SEQ_FLAG_EOCA           (ADC_ISR_EOCAF)                 /*!< Status flag of the end of conversion of sequence A. */
#define ADC_SEQ_FLAG_EOCB           (ADC_ISR_EOCBF)                 /*!< Status flag of the end of conversion of sequence B. */
#define ADC_SEQ_FLAG_NESTED         (ADC_ISR_SASTPDF)               /*!< Status flag of sequence A was interrupted by sequence B. */

#define ADC_SEQ_FLAG_ALL            (ADC_SEQ_FLAG_EOCA | \
                                     ADC_SEQ_FLAG_EOCB | \
                                     ADC_SEQ_FLAG_NESTED)
/**
 * @}
 */

/**
 * @defgroup ADC_Channel_Number ADC Channel Number
 * @{
 */
#define ADC_CH_NUM0                 (0U)          /*!< Corresponds to pin P40 */
#define ADC_CH_NUM1                 (1U)          /*!< Corresponds to pin P41 */
#define ADC_CH_NUM2                 (2U)          /*!< Corresponds to pin P42 */
#define ADC_CH_NUM3                 (3U)          /*!< Corresponds to pin P43 */
#define ADC_CH_NUM4                 (4U)          /*!< Corresponds to pin P44 */
#define ADC_CH_NUM5                 (5U)          /*!< Corresponds to pin P45 */
#define ADC_CH_NUM6                 (6U)          /*!< Corresponds to pin P46 */
#define ADC_CH_NUM7                 (7U)          /*!< Corresponds to pin P47 */
#define ADC_CH_NUM8                 (8U)          /*!< Corresponds to pin P11 */
#define ADC_CH_NUM9                 (9U)          /*!< Corresponds to pin P10 */
#define ADC_CH_NUM_MAX              (ADC_CH_NUM9)
/**
 * @}
 */

/**
 * @defgroup ADC_Channel_Count ADC Channel Count
 * @{
 */
#define ADC_CH_CNT                  (10U)
/**
 * @}
 */

/**
 * @defgroup ADC_Channel ADC Common Channels
 * @{
 */
#define ADC_CH0                     (0x1UL << ADC_CH_NUM0)
#define ADC_CH1                     (0x1UL << ADC_CH_NUM1)
#define ADC_CH2                     (0x1UL << ADC_CH_NUM2)
#define ADC_CH3                     (0x1UL << ADC_CH_NUM3)
#define ADC_CH4                     (0x1UL << ADC_CH_NUM4)
#define ADC_CH5                     (0x1UL << ADC_CH_NUM5)
#define ADC_CH6                     (0x1UL << ADC_CH_NUM6)
#define ADC_CH7                     (0x1UL << ADC_CH_NUM7)
#define ADC_CH8                     (0x1UL << ADC_CH_NUM8)
#define ADC_CH9                     (0x1UL << ADC_CH_NUM9)
#define ADC_EXT_CH                  (ADC_CH8)
#define ADC_CH_ALL                  (0x03FFU)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup ADC_Global_Functions
 * @{
 */

en_result_t ADC_Init(CM_ADC_TypeDef *ADCx, const stc_adc_init_t *pstcAdcInit);
void ADC_DeInit(CM_ADC_TypeDef *ADCx);

en_result_t ADC_StructInit(stc_adc_init_t *pstcAdcInit);

void ADC_SetScanMode(CM_ADC_TypeDef *ADCx, uint16_t u16Mode);
en_result_t ADC_ChCmd(CM_ADC_TypeDef *ADCx,            \
                      uint32_t u32Seq, uint32_t u32Ch, \
                      const uint8_t au8SampleTime[],   \
                      en_functional_state_t enNewState);

void ADC_SetAverageCount(CM_ADC_TypeDef *ADCx, uint16_t u16Count);
void ADC_AverageChCmd(CM_ADC_TypeDef *ADCx, uint32_t u32Ch, \
                      en_functional_state_t enNewState);
void ADC_SetExtendChSrc(CM_ADC_TypeDef *ADCx, uint8_t u8Src);

en_result_t ADC_TriggerSrcStructInit(stc_adc_trigger_config_t *pstcCfg);
en_result_t ADC_TriggerSrcConfig(CM_ADC_TypeDef *ADCx, uint32_t u32Seq, \
                                 const stc_adc_trigger_config_t *pstcCfg);
void ADC_TriggerSrcCmd(CM_ADC_TypeDef *ADCx, uint32_t u32Seq, en_functional_state_t enNewState);

void ADC_SeqIntCmd(CM_ADC_TypeDef *ADCx, uint32_t u32Seq, en_functional_state_t enNewState);
en_flag_status_t ADC_SeqGetStatus(const CM_ADC_TypeDef *ADCx, uint8_t u8Flag);
void ADC_SeqClearStatus(CM_ADC_TypeDef *ADCx, uint8_t u8Flag);

void ADC_SH_SetSampleTime(CM_ADC_TypeDef *ADCx, uint8_t u8CycleCount);
void ADC_SH_ChCmd(CM_ADC_TypeDef *ADCx, uint32_t u32Ch, en_functional_state_t enNewState);
void ADC_ContinuousSampleCmd(CM_ADC_TypeDef *ADCx, en_functional_state_t enNewState);

en_result_t ADC_PollingSeqA(CM_ADC_TypeDef *ADCx, uint16_t au16Value[], \
                            uint32_t u32Len, uint32_t u32Timeout);
en_result_t ADC_GetAllData(const CM_ADC_TypeDef *ADCx, uint16_t au16Value[], uint32_t u32Len);
en_result_t ADC_GetChData(const CM_ADC_TypeDef *ADCx, uint32_t u32Ch, \
                          uint16_t au16Value[], uint32_t u32Len);
uint16_t ADC_GetValue(const CM_ADC_TypeDef *ADCx, uint32_t u32ChNum);

void ADC_Start(CM_ADC_TypeDef *ADCx);
void ADC_Stop(CM_ADC_TypeDef *ADCx);

/**
 * @}
 */

#endif /* DDL_ADC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_ADC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
