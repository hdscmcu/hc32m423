/**
 *******************************************************************************
 * @file  hc32m423_adc.c
 * @brief This file provides firmware functions to manage the Analog-to-Digital
 *        Converter(ADC).
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
#include "hc32m423_adc.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_ADC ADC
 * @brief Analog-to-Digital Converter Driver Library
 * @{
 */

#if (DDL_ADC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ADC_Local_Macros ADC Local Macros
 * @{
 */
/**
 * @defgroup ADC_Configuration_Bit_Mask ADC Configuration Bit Mask
 * @{
 */
#define ADC_TRIG_SRC_MASK                   (ADC_TRGSR_TRGSELA)
/**
 * @}
 */

/**
 * @defgroup ADC_Check_Parameters_Validity ADC check parameters validity
 * @{
 */
/*!< Parameter validity check for ADC unit. */
#define IS_ADC_UNIT(x)                                                         \
(   ((x) == CM_ADC))

/*!< Parameter validity check for ADC sequence. */
#define IS_ADC_SEQ(x)                                                          \
(   ((x) == ADC_SEQ_A)                      ||                                 \
    ((x) == ADC_SEQ_B))

/*!< Parameter validity check for ADC scan mode. */
#define IS_ADC_SCAN_MD(x)                                                      \
(   ((x) == ADC_MD_SA_SSHOT)                ||                                 \
    ((x) == ADC_MD_SA_CONT)                 ||                                 \
    ((x) == ADC_MD_SA_SB_SSHOT)             ||                                 \
    ((x) == ADC_MD_SA_CONT_SB_SSHOT))

/*!< Parameter validity check for ADC resolution. */
#define IS_ADC_RESOLUTION(x)                                                   \
(   ((x) == ADC_RESOLUTION_8BIT)            ||                                 \
    ((x) == ADC_RESOLUTION_10BIT)           ||                                 \
    ((x) == ADC_RESOLUTION_12BIT))

/*!< Parameter validity check for ADC trigger source. */
#define IS_ADC_TRIG_SRC(x)                                                     \
(   ((x) == ADC_TRIG_SRC_ADTRG)             ||                                 \
    ((x) == ADC_TRIG_SRC_EVT0)              ||                                 \
    ((x) == ADC_TRIG_SRC_EVT1)              ||                                 \
    ((x) == ADC_TRIG_SRC_EVT0_EVT1))

/*!< Parameter validity check for ADC automatically clear command. */
#define IS_ADC_AUTO_CLR(x)                                                     \
(   ((x) == ADC_AUTO_CLR_DISABLE)           ||                                 \
    ((x) == ADC_AUTO_CLR_ENABLE))

/*!< Parameter validity check for ADC data alignment. */
#define IS_ADC_DATA_ALIGN(x)                                                   \
(   ((x) == ADC_DATA_ALIGN_RIGHT)           ||                                 \
    ((x) == ADC_DATA_ALIGN_LEFT))

/*!< Parameter validity check for ADC sequence A resume position. */
#define IS_ADC_SA_RESUME_POS(x)                                                \
(   ((x) == ADC_SA_RESUME_POS_INT_CH)       ||                                 \
    ((x) == ADC_SA_RESUME_POS_FIRST_CH))

/*!< Parameter validity check for ADC channel number. */
#define IS_ADC_CH_NUM(x)                                                       \
(   (x) <= ADC_CH_NUM_MAX)

/*!< Parameter validity check for ADC sampling time. */
#define IS_ADC_SPL_TIME(x)                                                     \
(   ((x) >= 5U))

/*!< Parameter validity check for ADC average count. */
#define IS_ADC_AVG_CNT(x)                                                      \
(   ((x) == ADC_AVG_CNT2)                   ||                                 \
    ((x) == ADC_AVG_CNT4)                   ||                                 \
    ((x) == ADC_AVG_CNT8)                   ||                                 \
    ((x) == ADC_AVG_CNT16)                  ||                                 \
    ((x) == ADC_AVG_CNT32)                  ||                                 \
    ((x) == ADC_AVG_CNT64)                  ||                                 \
    ((x) == ADC_AVG_CNT128)                 ||                                 \
    ((x) == ADC_AVG_CNT256))

/*!< Parameter validity check for ADC extended channel analog source. */
#define IS_ADC_EXT_CH_SRC(x)                                                   \
(   ((x) == ADC_EXT_CH_SRC_ADC_PIN)         ||                                 \
    ((x) == ADC_EXT_CH_SRC_INTERNAL))

/*!< Parameter validity check for ADC bit mask. */
#define IS_ADC_BIT_MASK(x, mask)                                               \
(   ((x) != 0U)                             &&                                 \
    (((x) | (mask)) == (mask)))

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Functions ADC Global Functions
 * @{
 */

/**
 * @brief  Initializes the ADC peripheral according to the specified parameters
 *         in the structure stc_adc_init.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  pstcAdcInit            Pointer to a stc_adc_init_t structure value that
 *                                      contains the configuration information for the ADC.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcAdcInit == NULL.
 */
en_result_t ADC_Init(CM_ADC_TypeDef *ADCx, const stc_adc_init_t *pstcAdcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcAdcInit != NULL)
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));
        DDL_ASSERT(IS_ADC_SCAN_MD(pstcAdcInit->u16ScanMode));
        DDL_ASSERT(IS_ADC_RESOLUTION(pstcAdcInit->u16Resolution));
        DDL_ASSERT(IS_ADC_AUTO_CLR(pstcAdcInit->u16AutoClear));
        DDL_ASSERT(IS_ADC_DATA_ALIGN(pstcAdcInit->u16DataAlign));
        DDL_ASSERT(IS_ADC_SA_RESUME_POS(pstcAdcInit->u16SAResumePos));

        /* Configures scan convert mode, resolution, data automatically cleared cmd
           and data alignment. */
        WRITE_REG16(ADCx->CR0, \
                    (pstcAdcInit->u16ScanMode   | \
                     pstcAdcInit->u16Resolution | \
                     pstcAdcInit->u16AutoClear  | \
                     pstcAdcInit->u16DataAlign));

        /* Configures the channel sequence A restart from. */
        WRITE_REG16(ADCx->CR1, pstcAdcInit->u16SAResumePos);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes the ADC peripheral. Reset the registers.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @retval None
 */
void ADC_DeInit(CM_ADC_TypeDef *ADCx)
{
    uint8_t i;
    uint32_t u32SSTRAddr;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));

    /* Stop the ADC. */
    ADC_Stop(ADCx);

    /* Set the registers to reset value. */
    WRITE_REG16(ADCx->CR0, 0x0U);
    WRITE_REG16(ADCx->CR1, 0x0U);
    WRITE_REG16(ADCx->TRGSR, 0x0U);
    WRITE_REG16(ADCx->CHSELRA0, 0x0U);
    WRITE_REG16(ADCx->CHSELRB0, 0x0U);
    WRITE_REG16(ADCx->AVCHSELR0, 0x0U);
    WRITE_REG8(ADCx->EXCHSELR, 0x0U);
    WRITE_REG16(ADCx->SHCR, 0x0U);
    WRITE_REG8(ADCx->ICR, 0x3U);

    u32SSTRAddr = (uint32_t)&ADCx->SSTR0;
    for (i=0U; i<ADC_CH_CNT; i++)
    {
        RW_MEM8(u32SSTRAddr) = 0x0BU;
        u32SSTRAddr++;
    }
}

/**
 * @brief  Set a default value for the ADC initialization structure.
 * @param  [in]  pstcAdcInit            Pointer to a stc_adc_init_t structure that
 *                                      contains configuration information.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcAdcInit == NULL.
 */
en_result_t ADC_StructInit(stc_adc_init_t *pstcAdcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcAdcInit != NULL)
    {
        pstcAdcInit->u16ScanMode    = ADC_MD_SA_SSHOT;
        pstcAdcInit->u16Resolution  = ADC_RESOLUTION_12BIT;
        pstcAdcInit->u16AutoClear   = ADC_AUTO_CLR_DISABLE;
        pstcAdcInit->u16DataAlign   = ADC_DATA_ALIGN_RIGHT;
        pstcAdcInit->u16SAResumePos = ADC_SA_RESUME_POS_INT_CH;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Speficies scan convert mode.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u16Mode                ADC san convert mode.
 *                                      This parameter can be a value of @ref ADC_Scan_Convert_Mode.
 *   @arg  ADC_MD_SA_SSHOT:             Sequence A single shot.
 *   @arg  ADC_MD_SA_CONT:              Sequence A continuous.
 *   @arg  ADC_MD_SA_SB_SSHOT:          Sequence A and B both single shot.
 *   @arg  ADC_MD_SA_CONT_SB_SSHOT:     Sequence A continuous and sequence B single shot.
 * @retval None
 */
void ADC_SetScanMode(CM_ADC_TypeDef *ADCx, uint16_t u16Mode)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SCAN_MD(u16Mode));
    MODIFY_REG16(ADCx->CR0, ADC_CR0_MS, u16Mode);
}

/**
 * @brief  Enable or disable specified sequence's channels.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u32Seq                 The sequence that it's specified channels will be enabled or disabled.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   Sequence A.
 *   @arg  ADC_SEQ_B:                   Sequence B.
 * @param  [in]  u32Ch                  The ADC channels.
 *                                      This parameter can be values of @ref ADC_Channel
 *   @arg  ADC_CH0 ~ ADC_CH9
 * @param  [in]  au8SampleTime:         Pointer to an uint8_t type array which contains sampling time of the specified channels.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified sequence's specified channels.
 *   @arg  Disable:                     Disable the specified sequence's specified channels.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       au8SampleTime == NULL.
 * @note   Sequence A and Sequence B CAN NOT include the same channel!
 */
en_result_t ADC_ChCmd(CM_ADC_TypeDef *ADCx,            \
                      uint32_t u32Seq, uint32_t u32Ch, \
                      const uint8_t au8SampleTime[],   \
                      en_functional_state_t enNewState)
{
    uint8_t i = 0U;
    uint8_t j = 0U;
    uint32_t u32CHSELAddr;
    uint32_t u32SSTRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (au8SampleTime != NULL)
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));
        DDL_ASSERT(IS_ADC_SEQ(u32Seq));
        DDL_ASSERT(IS_ADC_BIT_MASK(u32Ch, ADC_CH_ALL));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u32CHSELAddr = (uint32_t)&ADCx->CHSELRA0 + (u32Seq * 4U);
        u32SSTRAddr  = (uint32_t)&ADCx->SSTR0;

        if (enNewState == Enable)
        {
            RW_MEM16(u32CHSELAddr) |= (uint16_t)u32Ch;

            while (u32Ch != 0UL)
            {
                if ((u32Ch & 0x1UL) != 0UL)
                {
                    DDL_ASSERT(IS_ADC_SPL_TIME(au8SampleTime[j]));
                    RW_MEM8(u32SSTRAddr+i) = au8SampleTime[j];
                    j++;
                }
                i++;
                u32Ch >>= 1U;
            }
        }
        else
        {
            RW_MEM16(u32CHSELAddr) &= (uint16_t)(~u32Ch);
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specifies average count for average channels.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u16Count               The average count to be set for the specified ADC unit.
 *                                      This parameter can be a value of @ref ADC_Average_Count
 *   @arg  ADC_AVG_CNT2
 *   @arg  ADC_AVG_CNT4
 *   @arg  ADC_AVG_CNT8
 *   @arg  ADC_AVG_CNT16
 *   @arg  ADC_AVG_CNT32
 *   @arg  ADC_AVG_CNT64
 *   @arg  ADC_AVG_CNT128
 *   @arg  ADC_AVG_CNT256
 * @retval None
 */
void ADC_SetAverageCount(CM_ADC_TypeDef *ADCx, uint16_t u16Count)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_AVG_CNT(u16Count));

    MODIFY_REG16(ADCx->CR0, ADC_CR0_AVCNT, u16Count);
}

/**
 * @brief  Enable or disable the specified average channels.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u32Ch             The ADC channels.
 *                                      This parameter can be values of @ref ADC_Channel
 *   @arg  ADC_CH0 ~ ADC_CH9
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified average channels.
 *   @arg  Disable:                     Disable the specified average channels.
 * @retval None
 */
void ADC_AverageChCmd(CM_ADC_TypeDef *ADCx, uint32_t u32Ch, \
                      en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG16_BIT(ADCx->AVCHSELR0, u32Ch);
    }
    else
    {
        CLEAR_REG16_BIT(ADCx->AVCHSELR0, u32Ch);
    }
}

/**
 * @brief  Specifies analog input source for extended channel.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u8Src                  The specified analog input source for extended channel(channel 8).
 *                                      This parameter can be a value of @ref ADC_Extend_Channel_Source
 *   @arg  ADC_EXT_CH_SRC_ADC_PIN:      Specifies the pin P11(ADC_IN8) as the extended channel analog input source.
 *   @arg  ADC_EXT_CH_SRC_INTERNAL:     Specifies the internal analog source as the extended channel analog input source.
 * @retval None.
 */
void ADC_SetExtendChSrc(CM_ADC_TypeDef *ADCx, uint8_t u8Src)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_EXT_CH_SRC(u8Src));

    WRITE_REG8(ADCx->EXCHSELR, u8Src);
}

/**
 * @brief  Set a default value for trigger source configuration structure.
 * @param  [in]  pstcCfg                Pointer to a stc_adc_trigger_config_t structure that
 *                                      contains configuration information.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t ADC_TriggerSrcStructInit(stc_adc_trigger_config_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        pstcCfg->u16TriggerSrc = ADC_TRIG_SRC_ADTRG;
        pstcCfg->enEvent0      = EVT_MAX;
        pstcCfg->enEvent1      = EVT_MAX;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Configures trigger source for the specified sequence.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u32Seq                 The sequence to be configured.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   Sequence A.
 *   @arg  ADC_SEQ_B:                   Sequence B.
 * @param  [in]  pstcCfg                Pointer to a stc_adc_trigger_config_t structure that contains
 *                                      the configuration information of the trigger source.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t ADC_TriggerSrcConfig(CM_ADC_TypeDef *ADCx, uint32_t u32Seq, \
                                 const stc_adc_trigger_config_t *pstcCfg)
{
    uint8_t u8Offset  = ADC_TRGSR_TRGSELA_POS;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));
        DDL_ASSERT(IS_ADC_SEQ(u32Seq));
        DDL_ASSERT(IS_ADC_TRIG_SRC(pstcCfg->u16TriggerSrc));

        if (u32Seq == ADC_SEQ_B)
        {
            u8Offset = ADC_TRGSR_TRGSELB_POS;
        }

        switch (pstcCfg->u16TriggerSrc)
        {
            case ADC_TRIG_SRC_EVT0:
                WRITE_REG32(CM_AOS->ADC_ITRGSELR0, pstcCfg->enEvent0);
                break;

            case ADC_TRIG_SRC_EVT1:
                WRITE_REG32(CM_AOS->ADC_ITRGSELR1, pstcCfg->enEvent1);
                break;

            case ADC_TRIG_SRC_EVT0_EVT1:
                WRITE_REG32(CM_AOS->ADC_ITRGSELR0, pstcCfg->enEvent0);
                WRITE_REG32(CM_AOS->ADC_ITRGSELR1, pstcCfg->enEvent1);
                break;

            default:
                break;
        }

        MODIFY_REG16(ADCx->TRGSR, \
                     ((uint32_t)ADC_TRIG_SRC_MASK << u8Offset), \
                     ((uint32_t)pstcCfg->u16TriggerSrc << u8Offset));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the trigger source of the specified sequence.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u32Seq                 The sequence to be configured.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   Sequence A.
 *   @arg  ADC_SEQ_B:                   Sequence B.
 * @param  [in]  enNewState             An en_functional_state_t enumeration value.
 *   @arg  Enable:                      Enable the trigger source of the specified sequence.
 *   @arg  Disable:                     Disable the trigger source of the specified sequence.
 * @retval None
 */
void ADC_TriggerSrcCmd(CM_ADC_TypeDef *ADCx, uint32_t u32Seq, en_functional_state_t enNewState)
{
    const uint16_t au16TRGEN[] = {ADC_TRGSR_TRGENA, ADC_TRGSR_TRGENB};

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SEQ(u32Seq));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG16_BIT(ADCx->TRGSR, au16TRGEN[u32Seq]);
    }
    else
    {
        CLEAR_REG16_BIT(ADCx->TRGSR, au16TRGEN[u32Seq]);
    }
}

/**
 * @brief  Enable or disable the interrupt of the specified sequence.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u32Seq                 The sequence to be configured.
 *                                      This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:                   Sequence A.
 *   @arg  ADC_SEQ_B:                   Sequence B.
 * @param  [in]  enNewState             An en_functional_state_t enumeration value.
 *   @arg  Enable:                      Enable the interrupt of the specified sequence.
 *   @arg  Disable:                     Disable the interrupt of the specified sequence.
 * @retval None
 */
void ADC_SeqIntCmd(CM_ADC_TypeDef *ADCx, uint32_t u32Seq, en_functional_state_t enNewState)
{
    const uint8_t au8EOCIEN[] = {ADC_ICR_EOCAIEN, ADC_ICR_EOCBIEN};

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_SEQ(u32Seq));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG8_BIT(ADCx->ICR, au8EOCIEN[u32Seq]);
    }
    else
    {
        CLEAR_REG8_BIT(ADCx->ICR, au8EOCIEN[u32Seq]);
    }
}

/**
 * @brief  Get the specified flag's status.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u8Flag                 Status flag.
 *                                      This parameter can be valueS of @ref ADC_Sequence_Status_Flag
 *   @arg  ADC_SEQ_FLAG_EOCA:           Status flag of the end of conversion of sequence A.
 *   @arg  ADC_SEQ_FLAG_EOCB:           Status flag of the end of conversion of sequence B.
 *   @arg  ADC_SEQ_FLAG_NESTED:         Status flag of sequence A was interrupted by sequence B.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg  Set:                         At least one of the specified flags is set.
 *   @arg  Reset:                       The specified flags are not set.
 */
en_flag_status_t ADC_SeqGetStatus(const CM_ADC_TypeDef *ADCx, uint8_t u8Flag)
{
    en_flag_status_t enRet = Reset;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_BIT_MASK(u8Flag, ADC_SEQ_FLAG_ALL));

    if (READ_REG8_BIT(ADCx->ISR, u8Flag) != 0U)
    {
        enRet = Set;
    }

    return enRet;
}

/**
 * @brief  Clear the specifed flags.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u8Flag                 Status flag.
 *                                      This parameter can be values of @ref ADC_Sequence_Status_Flag
 *   @arg  ADC_SEQ_FLAG_EOCA:           Status flag of the end of conversion of sequence A.
 *   @arg  ADC_SEQ_FLAG_EOCB:           Status flag of the end of conversion of sequence B.
 *   @arg  ADC_SEQ_FLAG_NESTED:         Status flag of sequence A was interrupted by sequence B.
 * @retval None
 */
void ADC_SeqClearStatus(CM_ADC_TypeDef *ADCx, uint8_t u8Flag)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));

    SET_REG8_BIT(ADCx->ISCLRR, (u8Flag & ADC_SEQ_FLAG_ALL));
}

/**
 * @brief  Specifies the sample time(ADCLK cycles) of sample-hold.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u8CycleCount           Number of ADCLK cycles for sample-hold. \
 *                                      It should be more than 0.4 microseconds.
 * @retval None
 */
void ADC_SH_SetSampleTime(CM_ADC_TypeDef *ADCx, uint8_t u8CycleCount)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    MODIFY_REG16(ADCx->SHCR, ADC_SHCR_SHT, u8CycleCount);
}

/**
 * @brief  Enable or disable sample-hold channels.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u32Ch             ADC channels.
 *                                      This parameter be values of the following of @ref ADC_Channel
 *   @arg  ADC_CH0:                     Channel 0 of ADC.
 *   @arg  ADC_CH1:                     Channel 1 of ADC.
 *   @arg  ADC_CH2:                     Channel 2 of ADC.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified sample-hold channels.
 *   @arg  Disable:                     Disable the specified sample-hold channels.
 * @retval None
 */
void ADC_SH_ChCmd(CM_ADC_TypeDef *ADCx, uint32_t u32Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_BIT_MASK(u32Ch, ADC_CH0|ADC_CH1|ADC_CH2));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Ch <<= ADC_SHCR_SHSEL_POS;
    if (enNewState == Enable)
    {
        SET_REG16_BIT(ADCx->SHCR, u32Ch);
    }
    else
    {
        CLEAR_REG16_BIT(ADCx->SHCR, u32Ch);
    }
}

/**
 * @brief  Enable or disable continuous sampling.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  enNewState:            An en_functional_state_t value.
 *   @arg  Enable:                      Enable continuous sampling.
 *   @arg  Disable:                     Disable continuous sampling.
 * @retval None
 */
void ADC_ContinuousSampleCmd(CM_ADC_TypeDef *ADCx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG16_BIT(ADCx->SHCR, ADC_SHCR_SHMD);
    }
    else
    {
        CLEAR_REG16_BIT(ADCx->SHCR, ADC_SHCR_SHMD);
    }
}

/**
 * @brief  Basic usage of ADC sampling. Start ADC converting and get the ADC values of \
 *         the channels enabled in sequence A.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [out]  au16Value             Pointer to an uint16_t type memory which the ADC values to be stored.
 *                                      The location of the value store depends on the parameter u32Len.
 *                                      u32Len >= ADC_CH_CNT, all of the ADC data registers will be read:
 *                                      au16Value[0] = value of Channel 0,
 *                                      au16Value[1] = value of Channel 1,
 *                                      au16Value[2] = value of Channel 2,
 *                                                  ...
 *                                      u32Len < ADC_CH_CNT, only the value of the enabled channels will be read:
 *                                      au16Value[0] = value of the 1st enabled channel,
 *                                      au16Value[1] = value of the 2nd enabled channel,
 *                                      au16Value[2] = value of the 3rd enabled channel,
 * @param  [in]  u32Len                 The length of the ADC value to be got.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -au16Value == NULL.
 *                                     -u32Len == 0.
 *                                     -u32Timeout == 0.
 *                                     -The base address of 'pu16AdcVal' is not 2-byte aligned.
 */
en_result_t ADC_PollingSeqA(CM_ADC_TypeDef *ADCx, uint16_t au16Value[], \
                            uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t u32Ch;
    en_result_t enRet = ErrorInvalidParameter;

    if ((au16Value != NULL) && \
        (u32Len != 0U) && \
        IS_ADDRESS_ALIGN_HALFWORD(&au16Value[0U]))
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));
        /* Start ADC.*/
        SET_REG8_BIT(ADCx->STR, ADC_STR_STRT);
        /* Check timeout. */
        enRet = Ok;
        while (READ_REG8_BIT(ADCx->ISR, ADC_ISR_EOCAF) == 0U)
        {
            if (u32Timeout == 0UL)
            {
                CLEAR_REG8_BIT(ADCx->STR, ADC_STR_STRT);
                enRet = ErrorTimeout;
                break;
            }
            u32Timeout--;
        }

        if (enRet == Ok)
        {
            if (u32Len < ADC_CH_CNT)
            {
                u32Ch = READ_REG16(ADCx->CHSELRA0);
                (void)ADC_GetChData(ADCx, u32Ch, au16Value, u32Len);
            }
            else
            {
                (void)ADC_GetAllData(ADCx, au16Value, ADC_CH_CNT);
            }
            SET_REG8_BIT(ADCx->ISCLRR, ADC_ISCLRR_CLREOCAF);
        }
    }

    return enRet;
}

/**
 * @brief  Get all of the channels' value.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [out]  au16Value             Pointer to an uint16_t type memory which the ADC values to be stored.
 *                                      au16Value[0] = value of Channel 0,
 *                                      au16Value[1] = value of Channel 1,
 *                                      au16Value[2] = value of Channel 2,
 * @param  [in]  u32Len                 The length of the ADC value to be got.
 *                                      It CAN NOT be less than the number of channels of the ADC unit.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -au16Value == NULL.
 *                                     -The base address of 'au16Value' is not 2-byte aligned.
 */
en_result_t ADC_GetAllData(const CM_ADC_TypeDef *ADCx, uint16_t au16Value[], uint32_t u32Len)
{
    uint8_t i;
    uint32_t u32DRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if ((au16Value != NULL)    && \
        (u32Len >= ADC_CH_CNT) && \
        IS_ADDRESS_ALIGN_HALFWORD(&au16Value[0U]))
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));

        u32DRAddr = (uint32_t)&ADCx->DR0;
        for (i=0U; i<ADC_CH_CNT; i++)
        {
            au16Value[i] = RW_MEM16(u32DRAddr);
            u32DRAddr += 2U;
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get the specified channels' values.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in] u32Ch                   The channels' ADC values will be read.
 *                                      This parameter can be a value of @ref ADC_Channel
 *   @arg  ADC_CH0 ~ ADC_CH9
 * @param  [out]  au16Value             Pointer to an uint16_t type memory which the ADC values to be stored.
 *                                      au16Value[0] = value of the 1st enabled channel,
 *                                      au16Value[1] = value of the 2nd enabled channel,
 *                                      au16Value[2] = value of the 3rd enabled channel,
 * @param  [in]  u32Len                 The length of the ADC value to be read.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -u32Ch == 0.
 *                                     -au16Value == NULL.
 *                                     -u32Len == 0.
 *                                     -The base address of 'au16Value' is not 2-byte aligned.
 */
en_result_t ADC_GetChData(const CM_ADC_TypeDef *ADCx, uint32_t u32Ch, \
                          uint16_t au16Value[], uint32_t u32Len)
{
    uint8_t  j = 0U;
    uint32_t i = 0U;
    uint32_t u32DRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if ((u32Ch != 0U)       && \
        (au16Value != NULL) && \
        (u32Len != 0U)      && \
        IS_ADDRESS_ALIGN_HALFWORD(&au16Value[0U]))
    {
        DDL_ASSERT(IS_ADC_UNIT(ADCx));
        DDL_ASSERT(IS_ADC_BIT_MASK(u32Ch, ADC_CH_ALL));

        u32DRAddr = (uint32_t)&ADCx->DR0;
        while ((u32Ch != 0U) && (u32Len != 0U))
        {
            if ((u32Ch & 0x1UL) != 0U)
            {
                au16Value[j] = RW_MEM16(u32DRAddr + (i * 2U));
                j++;
                u32Len--;
            }
            u32Ch >>= 1U;
            i++;
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get a specified channel's value.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @param  [in]  u32ChNum          The index number of ADC channel.
 *                                      This parameter can be a value of @ref ADC_Channel_Number
 *   @arg  ADC_CH_NUM0
 *   @arg  ADC_CH_NUM1
 *   @arg  ADC_CH_NUM2
 *   @arg  ADC_CH_NUM3
 *   @arg  ADC_CH_NUM4
 *   @arg  ADC_CH_NUM5
 *   @arg  ADC_CH_NUM6
 *   @arg  ADC_CH_NUM7
 *   @arg  ADC_CH_NUM8
 *   @arg  ADC_CH_NUM9
 * @retval An uint16_t type value between 0 ~ 4095.
 */
uint16_t ADC_GetValue(const CM_ADC_TypeDef *ADCx, uint32_t u32ChNum)
{
    uint32_t u32DRAddr;

    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    DDL_ASSERT(IS_ADC_CH_NUM(u32ChNum));

    u32DRAddr = (uint32_t)&ADCx->DR0 + (u32ChNum * 2U);
    return RW_MEM16(u32DRAddr);
}

/**
 * @brief  Start the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @retval None
 * @note   Only start sequence A. Sequence B can only be start by trigger source.
 */
void ADC_Start(CM_ADC_TypeDef *ADCx)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    SET_REG8_BIT(ADCx->STR, ADC_STR_STRT);
}

/**
 * @brief  Stop the specified ADC unit.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_ADC1:                     ADC unit 1 instance register base.
 * @retval None
 * @note   Only stop sequence A. Sequence B stop automatically after sampling.
 */
void ADC_Stop(CM_ADC_TypeDef *ADCx)
{
    DDL_ASSERT(IS_ADC_UNIT(ADCx));
    CLEAR_REG8_BIT(ADCx->STR, ADC_STR_STRT);
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
