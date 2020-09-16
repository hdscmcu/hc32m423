/**
 *******************************************************************************
 * @file  hc32m423_tmr4.h
 * @brief This file contains all the functions prototypes of the TMR4(Timer4)
 *        driver library.
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
#ifndef __HC32M423_TMR4_H__
#define __HC32M423_TMR4_H__

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
 * @addtogroup DDL_TMR4
 * @{
 */

#if (DDL_TMR4_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR4_Global_Types TMR4 Global Types
 * @{
 */

/**
 * @brief TMR4 Counter(CNT) function initialization configuration
 */
typedef struct
{

    uint16_t u16ClockSrc;       /*!< TMR4 counter clock source.
                                     This parameter can be a value of @ref TMR4_CNT_Clock_Source */
    uint16_t u16ClockDiv;       /*!< TMR4 counter PCLK clock division. The clock division is valid when clock source is PCLK
                                     This parameter can be a value of @ref TMR4_CNT_Clock_Division */
    uint16_t u16CountMode;      /*!< TMR4 counter mode.
                                     This parameter can be a value of @ref TMR4_CNT_Mode */
    uint16_t u16PeriodValue;    /*!< TMR4 counter period value.
                                     This parameter can be a value of half-word */
} stc_tmr4_cnt_init_t;

/**
 * @brief The configuration of OCO high channel OCMR field (OUH/OVH/OWH)
 */
typedef struct
{
    uint16_t OCFDCH : 1;    /*!< OCMRxh b0 High channel's OCF status when high channel match occurs at the condition of CNT is counting down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */
    uint16_t OCFPKH : 1;    /*!< OCMRxh b1 High channel's OCF status when high channel match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */
    uint16_t OCFUCH : 1;    /*!< OCMRxh b2 High channel's OCF status when high channel match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */
    uint16_t OCFZRH : 1;    /*!< OCMRxh b3 High channel's OCF status when high channel match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */
    uint16_t OPDCH  : 2;    /*!< OCMRxh b5~b4 High channel's OP output status when high channel match occurs at the condition of CNT is counting down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint16_t OPPKH  : 2;    /*!< OCMRxh b7~b6 High channel's OP output status when high channel match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint16_t OPUCH  : 2;    /*!< OCMRxh b9~b8 High channel's OP output status when high channel match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint16_t OPZRH  : 2;    /*!< OCMRxh b11~b10 High channel's OP output status when high channel match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint16_t OPNPKH : 2;    /*!< OCMRxh b13~b12 High channel's OP output status when high channel match doesn't occur at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint16_t OPNZRH : 2;    /*!< OCMRxh b15~b14 High channel's OP output status when high channel match doesn't occur at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
} stc_tmr4_oco_ocmrh_field_t;

/**
 * @brief The configuration of OCO high channel(OUH/OVH/OWH)
 */
typedef struct
{
    union
    {
        uint16_t OCMRx;                     /*!< OCMRxH(x=U/V/W) register */
        stc_tmr4_oco_ocmrh_field_t OCMRx_f; /*!< OCMRxH(x=U/V/W) register struct field bit
                                                 This details refer @ref stc_tmr4_oco_ocmrh_field_t */
    };
} stc_oco_high_ch_compare_mode_t;

/**
 * @brief The configuration of OCO low channel OCMR field (OUL/OVL/OWL)
 */
typedef struct
{
    uint32_t OCFDCL  : 1;   /*!< OCMRxl b0 Low channel's OCF status when low channel match occurs at the condition of CNT is counting down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */
    uint32_t OCFPKL  : 1;   /*!< OCMRxl b1 Low channel's OCF status when low channel match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */
    uint32_t OCFUCL  : 1;   /*!< OCMRxl b2 Low channel's OCF status when low channel match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */
    uint32_t OCFZRL  : 1;   /*!< OCMRxl b3 Low channel's OCF status when low channel match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_OCF_State */
    uint32_t OPDCL   : 2;   /*!< OCMRxl b5~b4 Low channel's OP output status when high channel not match and low channel match occurs at the condition of CNT is counting down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t OPPKL   : 2;   /*!< OCMRxl b7~b6 Low channel's OP output status when high channel not match and low channel match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t OPUCL   : 2;   /*!< OCMRxl b9~b8 Low channel's OP output status when high channel not match and low channel match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t OPZRL   : 2;   /*!< OCMRxl b11~b10 Low channel's OP output status when high channel not match and low channel match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t OPNPKL  : 2;   /*!< OCMRxl b13~b12 Low channel's OP output status when high channel not match and low channel not match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t OPNZRL  : 2;   /*!< OCMRxl b15~b14 Low channel's OP output status when high channel not match and low channel not match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t EOPNDCL : 2;   /*!< OCMRxl b17~b16 Low channel's OP output status when high channel match and low channel not match occurs at the condition of CNT is coutning down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t EOPNUCL : 2;   /*!< OCMRxl b19~b18 Low channel's OP output status when high channel match and low channel not match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t EOPDCL  : 2;   /*!< OCMRxl b21~b20 Low channel's OP output status when high channel and low channel match occurs at the condition of CNT is counting down
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t EOPPKL  : 2;   /*!< OCMRxl b23~b22 Low channel's OP output status when high channel and low channel match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t EOPUCL  : 2;   /*!< OCMRxl b25~b24 Low channel's OP output status when high channel and low channel match occurs at the condition of CNT is counting up
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t EOPZRL  : 2;   /*!< OCMRxl b27~b26 Low channel's OP output status when high channel and low channel match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t EOPNPKL : 2;   /*!< OCMRxl b29~b28 Low channel's OP output status when high channel match and low channel not match occurs at the condition of CNT count=Peak
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
    uint32_t EOPNZRL : 2;   /*!< OCMRxl b31~b30 Low channel's OP output status when high channel match and low channel not match occurs at the condition of CNT count=0x0000
                                 This parameter can be a value of @ref TMR4_OCO_Cnt_Match_Output_Polarity */
} stc_tmr4_oco_ocmrl_field_t;

/**
 ** \brief The configuration of OCO low channel(OUL/OVL/OWL)
 */
typedef struct
{
    union
    {
        uint32_t OCMRx;                     /*!< OCMRxL(x=U/V/W) register */
        stc_tmr4_oco_ocmrl_field_t OCMRx_f; /*!< OCMRxL(x=U/V/W) register struct field bit
                                                 This details refer @ref stc_tmr4_oco_ocmrl_field_t */
    };
} stc_oco_low_ch_compare_mode_t;

/**
 * @brief TMR4 Output Compare(OCO) initialization configuration
 */
typedef struct
{
    uint16_t u16CompareValue;           /*!< TMR4 OCO compare match value.
                                             This parameter can be a value of half-word. */
    uint16_t u16OcoInvalidPolarity;     /*!< Port output polarity when OCO is disabled.
                                             This parameter can be a value of @ref TMR4_OCO_Invalid_Output_Polarity. */
    uint16_t u16CompareModeBufCond;     /*!< Register OCMR buffer transfer condition.
                                             This parameter can be a value of @ref TMR4_OCO_Buffer_Transfer_Condition. */
    uint16_t u16CompareValueBufCond;    /*!< Register OCCR buffer transfer condition.
                                             This parameter can be a value of @ref TMR4_OCO_Buffer_Transfer_Condition. */
    uint16_t u16BufLinkTransferObject;  /*!< Enable the specified object(OCMR/OCCR) register buffer linked transfer with the CNT interrupt mask counter.
                                             This parameter can be a value of @ref TMR4_OCO_Buffer_Object. */
} stc_tmr4_oco_init_t;

/**
 * @brief TMR4 PWM initialization configuration
 */
typedef struct
{
    uint16_t u16Mode;                   /*!< Select PWM mode
                                             This parameter can be a value of @ref TMR4_PWM_Mode */
    uint16_t u16ClockDiv;               /*!< PCLK clock division of PWM timer. The PCLK division function is valid when clock source is PCLK
                                             This parameter can be a value of @ref TMR4_PWM_Clock_Division */
    uint16_t u16Polarity;               /*!< TMR4 PWM polarity
                                             This parameter can be a value of @ref TMR4_PWM_Polarity */
    uint32_t u32OXHPortOutMode;         /*!< TIM4_<t>_OxH(x=U/V/W) port output mode
                                             This parameter can be a value of @ref TMR4_PWM_Port_Output_Mode */
    uint32_t u32OXLPortOutMode;         /*!< TIM4_<t>_OxL(x=U/V/W) port output mode
                                             This parameter can be a value of @ref TMR4_PWM_Port_Output_Mode */
    uint32_t u32OXHAbnormalPolarity;    /*!< TIM4_<t>_OxH(x=U/V/W) abnormal polarity.
                                             This parameter can be a value of @ref TMR4_PWM_Abnormal_Polarity */
    uint32_t u32OXLAbnormalPolarity;    /*!< TIM4_<t>_OxL(x=U/V/W) abnormal polarity.
                                             This parameter can be a value of @ref TMR4_PWM_Abnormal_Polarity */
} stc_tmr4_pwm_init_t;

/**
 * @brief TMR4 Special-Event(SEVT) initialization configuration
 */
typedef struct
{
    uint16_t u16Mode;                               /*!< TMR4 SEVT mode
                                                         This parameter can be a value of @ref TMR4_SEVT_Mode */
    uint16_t u16CompareValue;                       /*!< TMR4 SEVT compare match value.
                                                         This parameter can be a value of half-word */
    uint16_t u16OutputEvent;                        /*!< TMR4 SEVT output event
                                                         This parameter can be a value of @ref TMR4_SEVT_Output_Event */
    uint16_t u16CountCompareType;                   /*!< Enable the specified count compare match type when match with SCCR&SCMR and TMR4 CNT count up
                                                         This parameter can be a value of @ref TMR4_SEVT_Count_Compare_Type */
    uint16_t u16BufCond;                            /*!< TMR4 SEVT buffer transfer condition
                                                         This parameter can be a value of @ref TMR4_SEVT_Buffer_Transfer_Condition */
    uint16_t u16MaskTimes;                          /*!< TMR4 SEVT mask times
                                                         This parameter can be a value of @ref TMR4_SEVT_Mask_Times */
    uint16_t u16MaskCompareType;                    /*!< Enable the specified type perform to compare with the CNT zero/peak interrupt mask times
                                                         This parameter can be a value of @ref TMR4_SEVT_Mask_Compare_Type */
    en_functional_state_t enBufLinkTransferState;   /*!< Enable or disable the buffer linked transfer with the CNT interrupt mask counter
                                                         This parameter can be a value of @ref en_functional_state_t */
} stc_tmr4_sevt_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR4_Global_Macros TMR4 Global Macros
 * @{
 */

/**
 * @defgroup TMR4_CNT_Macros TMR4 Counter Macros
 * @{
 */

/** @defgroup TMR4_CNT_Clock_Division TMR4 Counter Clock Division
 * @{
 */
#define TMR4_CNT_CLK_DIV1                   (0U)                        /*!< PCLK      */
#define TMR4_CNT_CLK_DIV2                   (1U << TMR4_CCSR_CKDIV_POS) /*!< PCLK/2    */
#define TMR4_CNT_CLK_DIV4                   (2U << TMR4_CCSR_CKDIV_POS) /*!< PCLK/4    */
#define TMR4_CNT_CLK_DIV8                   (3U << TMR4_CCSR_CKDIV_POS) /*!< PCLK/8    */
#define TMR4_CNT_CLK_DIV16                  (4U << TMR4_CCSR_CKDIV_POS) /*!< PCLK/16   */
#define TMR4_CNT_CLK_DIV32                  (5U << TMR4_CCSR_CKDIV_POS) /*!< PCLK/32   */
#define TMR4_CNT_CLK_DIV64                  (6U << TMR4_CCSR_CKDIV_POS) /*!< PCLK/64   */
#define TMR4_CNT_CLK_DIV128                 (7U << TMR4_CCSR_CKDIV_POS) /*!< PCLK/128  */
#define TMR4_CNT_CLK_DIV256                 (8U << TMR4_CCSR_CKDIV_POS) /*!< PCLK/256  */
#define TMR4_CNT_CLK_DIV512                 (9U << TMR4_CCSR_CKDIV_POS) /*!< PCLK/512  */
#define TMR4_CNT_CLK_DIV1024                (10U << TMR4_CCSR_CKDIV_POS)/*!< PCLK/1024 */
/**
 * @}
 */

/**
 * @defgroup TMR4_CNT_Mode TMR4 Counter Mode
 * @{
 */
#define TMR4_CNT_MD_SAWTOOTH                (0U)
#define TMR4_CNT_MD_TRIANGLE                (TMR4_CCSR_MODE)
/**
 * @}
 */

/**
 * @defgroup TMR4_CNT_Flag TMR4 Counter Flag
 * @{
 */
#define TMR4_CNT_FLAG_PEAK                  (TMR4_CCSR_IRQPF)
#define TMR4_CNT_FLAG_ZERO                  (TMR4_CCSR_IRQZF)
#define TMR4_CNT_FLAG_ALL                   (TMR4_CNT_FLAG_PEAK | TMR4_CNT_FLAG_ZERO)
/**
 * @}
 */

/**
 * @defgroup TMR4_CNT_Interrupt TMR4 Counter Interrupt
 * @{
 */
#define TMR4_CNT_INT_PEAK                   (TMR4_CCSR_IRQPEN)
#define TMR4_CNT_INT_ZERO                   (TMR4_CCSR_IRQZEN)
#define TMR4_CNT_INT_ALL                    (TMR4_CNT_INT_PEAK | TMR4_CNT_INT_ZERO)
/**
 * @}
 */

/**
 * @defgroup TMR4_CNT_Clock_Source TMR4 Counter Clock Source
 * @{
 */
#define TMR4_CNT_PCLK                       (0U)
#define TMR4_CNT_EXTCLK                     (TMR4_CCSR_ECKEN)
/**
 * @}
 */

/** @defgroup TMR4_CNT_Interrupt_Mask_Times TMR4 Counter Interrupt Mask Times
 * @{
 */
#define TMR4_CNT_INT_MASK0                  (0U)    /*!< Counter interrupt flag is always set(not masked) for every counter count at "0x0000" */
#define TMR4_CNT_INT_MASK1                  (1U)    /*!< Counter interrupt flag is set once for 2 for every counter counts at "0x0000" (skiping 1 count) */
#define TMR4_CNT_INT_MASK2                  (2U)    /*!< Counter interrupt flag is set once for 3 for every counter counts at "0x0000" (skiping 2 count) */
#define TMR4_CNT_INT_MASK3                  (3U)    /*!< Counter interrupt flag is set once for 4 for every counter counts at "0x0000" (skiping 3 count) */
#define TMR4_CNT_INT_MASK4                  (4U)    /*!< Counter interrupt flag is set once for 5 for every counter counts at "0x0000" (skiping 4 count) */
#define TMR4_CNT_INT_MASK5                  (5U)    /*!< Counter interrupt flag is set once for 6 for every counter counts at "0x0000" (skiping 5 count) */
#define TMR4_CNT_INT_MASK6                  (6U)    /*!< Counter interrupt flag is set once for 7 for every counter counts at "0x0000" (skiping 6 count) */
#define TMR4_CNT_INT_MASK7                  (7U)    /*!< Counter interrupt flag is set once for 8 for every counter counts at "0x0000" (skiping 7 count) */
#define TMR4_CNT_INT_MASK8                  (8U)    /*!< Counter interrupt flag is set once for 9 for every counter counts at "0x0000" (skiping 8 count) */
#define TMR4_CNT_INT_MASK9                  (9U)    /*!< Counter interrupt flag is set once for 10 for every counter counts at "0x0000" (skiping 9 count) */
#define TMR4_CNT_INT_MASK10                 (10U)   /*!< Counter interrupt flag is set once for 11 for every counter counts at "0x0000" (skiping 10 count) */
#define TMR4_CNT_INT_MASK11                 (11U)   /*!< Counter interrupt flag is set once for 12 for every counter counts at "0x0000" (skiping 11 count) */
#define TMR4_CNT_INT_MASK12                 (12U)   /*!< Counter interrupt flag is set once for 13 for every counter counts at "0x0000" (skiping 12 count) */
#define TMR4_CNT_INT_MASK13                 (13U)   /*!< Counter interrupt flag is set once for 14 for every counter counts at "0x0000" (skiping 13 count) */
#define TMR4_CNT_INT_MASK14                 (14U)   /*!< Counter interrupt flag is set once for 15 for every counter counts at "0x0000" (skiping 14 count) */
#define TMR4_CNT_INT_MASK15                 (15U)   /*!< Counter interrupt flag is set once for 16 for every counter counts at "0x0000" (skiping 15 count) */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup TMR4_OCO_Macros TMR4 Output Compare Macros
 * @{
 */

/** @defgroup TMR4_OCO_Channel TMR4 OCO Channel
 * @{
 */
#define TMR4_OCO_CH_UH                      (0UL)  /*!< TMR4 OCO channel:UH */
#define TMR4_OCO_CH_UL                      (1UL)  /*!< TMR4 OCO channel:UL */
#define TMR4_OCO_CH_VH                      (2UL)  /*!< TMR4 OCO channel:VH */
#define TMR4_OCO_CH_VL                      (3UL)  /*!< TMR4 OCO channel:VL */
#define TMR4_OCO_CH_WH                      (4UL)  /*!< TMR4 OCO channel:WH */
#define TMR4_OCO_CH_WL                      (5UL)  /*!< TMR4 OCO channel:WL */
/**
 * @}
 */

/**
 * @defgroup TMR4_OCO_Invalid_Output_Polarity TMR4 OCO Invalid Output Polarity
 * @{
 */
#define TMR4_OCO_INVD_LOW                   (0U)              /*!< TMR4 OCO Output low level when OCO is invalid */
#define TMR4_OCO_INVD_HIGH                  (TMR4_OCSR_OCPH)  /*!< TMR4 OCO Output high level when OCO is invalid */
/**
 * @}
 */

/** @defgroup TMR4_OCO_Buffer_Object TMR4 OCO Buffer Object
 * @{
 */
#define TMR4_OCO_BUF_CMP_VALUE              (0x01U) /*!< The register OCCR buffer function index */
#define TMR4_OCO_BUF_CMP_MD                 (0x02U) /*!< The register OCMR buffer function index */
/**
 * @}
 */

/** @defgroup TMR4_OCO_Buffer_Transfer_Condition TMR4 OCO OCCR Buffer Transfer Condition
 * @{
 */
#define TMR4_OCO_BUF_COND_IMMED             (0U)    /*!< Buffer transfer is made when writing to the OCCR/OCMR register. */
#define TMR4_OCO_BUF_COND_UDF               (1U)    /*!< Buffer transfer is made when counter underflow occur */
#define TMR4_OCO_BUF_COND_OVF               (2U)    /*!< Buffer transfer is made when counter overflow occur */
#define TMR4_OCO_BUF_COND_UDF_OVF           (3U)    /*!< Buffer transfer is made when counter underflow or overflow occur */
/**
 * @}
 */

/** @defgroup TMR4_OCO_Cnt_Match_OCF_State TMR4 OCO Cnt Match OCF State
 * @{
 */
#define TMR4_OCO_OCF_HOLD                   (0U)                /*!< Hold OCF when the TMR4 OCO count match */
#define TMR4_OCO_OCF_SET                    (TMR4_OCMRH_OCFDCH) /*!< Set OCF when the TMR4 OCO count match */
/**
 * @}
 */

/** @defgroup TMR4_OCO_Cnt_Match_Output_Polarity TMR4 OCO Cnt Match Output Polarity
 * @{
 */
#define TMR4_OCO_HOLD                       (0U)    /*!< Hold output when the TMR4 OCO count match */
#define TMR4_OCO_HIGH                       (1U)    /*!< Output high when the TMR4 OCO count match */
#define TMR4_OCO_LOW                        (2U)    /*!< Output low when the TMR4 OCO count match */
#define TMR4_OCO_INVT                       (3U)    /*!< Invert output when the TMR4 OCO count match */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Macros TMR4 PWM Macros
 * @{
 */

/** @defgroup TMR4_PWM_Channel TMR4 PWM Channel
 * @{
 */
#define TMR4_PWM_CH_U                       (0UL)   /*!< TMR4 PWM couple channel: U */
#define TMR4_PWM_CH_V                       (1UL)   /*!< TMR4 PWM couple channel: V */
#define TMR4_PWM_CH_W                       (2UL)   /*!< TMR4 PWM couple channel: W */
/**
 * @}
 */

/** @defgroup TMR4_PWM_Port TMR4 PWM Port
 * @{
 */
#define TMR4_PWM_PORT_OUH                   (0UL)   /*!< TMR4 PWM port: TIM4_<t>_OUH */
#define TMR4_PWM_PORT_OUL                   (1UL)   /*!< TMR4 PWM port: TIM4_<t>_OUL */
#define TMR4_PWM_PORT_OVH                   (2UL)   /*!< TMR4 PWM port: TIM4_<t>_OVH */
#define TMR4_PWM_PORT_OVL                   (3UL)   /*!< TMR4 PWM port: TIM4_<t>_OVL */
#define TMR4_PWM_PORT_OWH                   (4UL)   /*!< TMR4 PWM port: TIM4_<t>_OWH */
#define TMR4_PWM_PORT_OWL                   (5UL)   /*!< TMR4 PWM port: TIM4_<t>_OWL */
/**
 * @}
 */

/** @defgroup TMR4_PWM_Clock_Division TMR4 PWM Clock Division
 * @{
 */
#define TMR4_PWM_CLK_DIV1                   (0U)                        /*!< PCLK     */
#define TMR4_PWM_CLK_DIV2                   (1U << TMR4_POCR_DIVCK_POS) /*!< PCLK/2   */
#define TMR4_PWM_CLK_DIV4                   (2U << TMR4_POCR_DIVCK_POS) /*!< PCLK/8   */
#define TMR4_PWM_CLK_DIV8                   (3U << TMR4_POCR_DIVCK_POS) /*!< PCLK/8   */
#define TMR4_PWM_CLK_DIV16                  (4U << TMR4_POCR_DIVCK_POS) /*!< PCLK/16  */
#define TMR4_PWM_CLK_DIV32                  (5U << TMR4_POCR_DIVCK_POS) /*!< PCLK/32  */
#define TMR4_PWM_CLK_DIV64                  (6U << TMR4_POCR_DIVCK_POS) /*!< PCLK/64  */
#define TMR4_PWM_CLK_DIV128                 (7U << TMR4_POCR_DIVCK_POS) /*!< PCLK/128 */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Mode TMR4 PWM Mode
 * @{
 */
#define TMR4_PWM_MD_THROUGH                 (0U)                /*!< Through mode */
#define TMR4_PWM_MD_DEAD_TIMER              (TMR4_POCR_PWMMD_0) /*!< Dead timer mode */
#define TMR4_PWM_MD_DEAD_TIMER_FILTER       (TMR4_POCR_PWMMD_1) /*!< Dead timer filter mode */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Polarity TMR4 PWM OCO Polarity
 * @{
 */
#define TMR4_PWM_OXH_HOLD_OXL_HOLD          (0U)                /*!< Output PWML and PWMH signals without changing the level */
#define TMR4_PWM_OXH_INVT_OXL_INVT          (TMR4_POCR_LVLS_0)  /*!< Output both PWML and PWMH signals reversed */
#define TMR4_PWM_OXH_INVT_OXL_HOLD          (TMR4_POCR_LVLS_1)  /*!< Output the PWMH signal reversed, outputs the PWML signal without changing the level. */
#define TMR4_PWM_OXH_HOLD_OXL_INVT          (TMR4_POCR_LVLS)    /*!< Output the PWMH signal without changing the level, Outputs the PWML signal reversed. */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Port_Output_Mode TMR4 PWM Port Mode
 * @{
 */
#define TMR4_PWM_PORT_OUTPUT_OS             (0UL)   /*!< TIM4_<t>_Oxy(x=U/V/W, y=H/L) output polarity by specified register TMR4_PSCR.OSxy */
#define TMR4_PWM_PORT_OUTPUT_OSUH           (0UL)   /*!< TIM4_<t>_OUH output polarity by specified register TMR4_PSCR.OSUH */
#define TMR4_PWM_PORT_OUTPUT_OSUL           (0UL)   /*!< TIM4_<t>_OUL output polarity by specified register TMR4_PSCR.OSUL */
#define TMR4_PWM_PORT_OUTPUT_OSVH           (0UL)   /*!< TIM4_<t>_OVH output polarity by specified register TMR4_PSCR.OSVH */
#define TMR4_PWM_PORT_OUTPUT_OSVL           (0UL)   /*!< TIM4_<t>_OVL output polarity by specified register TMR4_PSCR.OSVL */
#define TMR4_PWM_PORT_OUTPUT_OSWH           (0UL)   /*!< TIM4_<t>_OWH output polarity by specified register TMR4_PSCR.OSWH */
#define TMR4_PWM_PORT_OUTPUT_OSWL           (0UL)   /*!< TIM4_<t>_OWL output polarity by specified register TMR4_PSCR.OSWL */
#define TMR4_PWM_PORT_OUTPUT_NORMAL         (TMR4_PSCR_OEUH)    /*!< TIM4_<t>_Oxy output normal PWM */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Abnormal_Polarity TMR4 PWM Abnormal Polarity
 * @{
 */
#define TMR4_PWM_ABNORMAL_POLARITY_NORMAL   (0UL)   /*!< TIM4_<t>_Oxy(x=U/V/W, y=H/L) output normal as below condition:1.EMB 2.MOE=0 3.MOE=1&OExy=0 */
#define TMR4_PWM_ABNORMAL_POLARITY_HIZ      (1UL)   /*!< TIM4_<t>_Oxy(x=U/V/W, y=H/L) output Hi-z as below condition:1.EMB 2.MOE=0 3.MOE=1&OExy=0 */
#define TMR4_PWM_ABNORMAL_POLARITY_LOW      (2UL)   /*!< TIM4_<t>_Oxy(x=U/V/W, y=H/L) output low level as below condition:1.EMB 2.MOE=0 3.MOE=1&OExy=0 */
#define TMR4_PWM_ABNORMAL_POLARITY_HIGH     (3UL)   /*!< TIM4_<t>_Oxy(x=U/V/W, y=H/L) output high level as below condition:1.EMB 2.MOE=0 3.MOE=1&OExy=0 */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Dead_Time_Register_Index TMR4 PWM Dead Time Register Index
 * @{
 */
#define TMR4_PWM_PDAR_IDX                   (0UL)   /*!< TMR4_PDARn(n=U/V/W) */
#define TMR4_PWM_PDBR_IDX                   (1UL)   /*!< TMR4_PDBRn(n=U/V/W) */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_EMB_Release_Mode TMR4 PWM EMB Release Mode
 * @{
 */
#define TMR4_PWM_EMB_RELEASE_MD_SW_MOE      (0UL)           /*!< The MOE bit can only be set to 1 by software to restore the PWM normal output. */
#define TMR4_PWM_EMB_RELEASE_MD_HW_MOE      (TMR4_PSCR_AOE) /*!< The MOE bit is automatically set to 1 by hardware to restore the PWM normal output. */
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_OE_Bit_Effect_Time TMR4 PWM Reister TMR4_PSCR.OE Bit Effect Time
 * @{
 */
#define TMR4_PWM_OE_EFFECT_IMMED            (TMR4_PSCR_ODT_0)   /*!< TMR4 PWM reister TMR4_PSCR.OE bit immediate effect */
#define TMR4_PWM_OE_EFFECT_CNT_UDF          (TMR4_PSCR_ODT_1)   /*!< TMR4 PWM reister TMR4_PSCR.OE bit effect when TMR4 counter underflow */
#define TMR4_PWM_OE_EFFECT_CNT_OVF          (TMR4_PSCR_ODT)     /*!< TMR4 PWM reister TMR4_PSCR.OE bit effect when TMR4 counter overflow */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup TMR4_SEVT_Macros TMR4 Special Event Macros
 * @{
 */

/** @defgroup TMR4_SEVT_Channel TMR4 SEVT Channel
 * @{
 */
#define TMR4_SEVT_CH_UH                     (0UL)   /*!< TMR4 SEVT channel:UH */
#define TMR4_SEVT_CH_UL                     (1UL)   /*!< TMR4 SEVT channel:UL */
#define TMR4_SEVT_CH_VH                     (2UL)   /*!< TMR4 SEVT channel:VH */
#define TMR4_SEVT_CH_VL                     (3UL)   /*!< TMR4 SEVT channel:VL */
#define TMR4_SEVT_CH_WH                     (4UL)   /*!< TMR4 SEVT channel:WH */
#define TMR4_SEVT_CH_WL                     (5UL)   /*!< TMR4 SEVT channel:WL */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Count_Compare_Type TMR4 SEVT Count Compare Type
 * @{
 */
#define TMR4_SEVT_CNT_CMP_UP                (TMR4_SCSR_UEN) /*!< Start event when match with SCCR&SCMR and TMR4 CNT count up */
#define TMR4_SEVT_CNT_CMP_DOWN              (TMR4_SCSR_DEN) /*!< Start event operate when match with SCCR&SCMR and TMR4 CNT count down */
#define TMR4_SEVT_CNT_CMP_ZERO              (TMR4_SCSR_ZEN) /*!< Start event operate when match with SCCR&SCMR and TMR4 CNT count zero */
#define TMR4_SEVT_CNT_CMP_PEAK              (TMR4_SCSR_PEN) /*!< Start event operate when match with SCCR&SCMR and TMR4 CNT count peak */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Mask_Compare_Type TMR4 SEVT Mask Compare Type
 * @{
 */
#define TMR4_SEVT_MASK_CMP_UDF              (TMR4_SCMR_MZCE)    /*!< Compare with the CNT zero interrupt mask counter */
#define TMR4_SEVT_MASK_CMP_OVF              (TMR4_SCMR_MPCE)    /*!< Compare with the CNT peak interrupt mask counter */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Buffer_Transfer_Condition TMR4 SEVT Buffer Transfer Condition
 * @{
 */
#define TMR4_SEVT_BUF_COND_IMMED            (0U)                /*!< Register SCCR&SCMR buffer transfer when writing to the SCCR&SCMR register */
#define TMR4_SEVT_BUF_COND_UDF              (TMR4_SCSR_BUFEN_0) /*!< Register SCCR&SCMR buffer transfer when counter underflow occur */
#define TMR4_SEVT_BUF_COND_OVF              (TMR4_SCSR_BUFEN_1) /*!< Register SCCR&SCMR buffer transfer when counter overflow occur */
#define TMR4_SEVT_BUF_COND_UDF_OVF          (TMR4_SCSR_BUFEN)   /*!< Register SCCR&SCMR buffer transfer when counter underflow or overflow occur */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Mode TMR4 SEVT Mode
 * @{
 */
#define TMR4_SEVT_MD_CMP                    (0U)                /*!< TMR4 SEVT compare mode */
#define TMR4_SEVT_MD_DELAY                  (TMR4_SCSR_EVTMS)   /*!< TMR4 SEVT delay mode */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Delay_Object TMR4 SEVT Delay Object
 * @{
 */
#define TMR4_SEVT_DELAY_OCCRXH              (0U)                /*!< TMR4 SEVT delay object: OCCRxh(x=u/v/w) */
#define TMR4_SEVT_DELAY_OCCRXL              (TMR4_SCSR_EVTDS)   /*!< TMR4 SEVT delay object: OCCRxl(x=u/v/w) */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Mask_Times TMR4 SEVT Mask Times
 * @{
 */
#define TMR4_SEVT_MASK0                     (0U)                        /*!< Mask 0 time */
#define TMR4_SEVT_MASK1                     (1U << TMR4_SCMR_AMC_POS)   /*!< Mask 1 times */
#define TMR4_SEVT_MASK2                     (2U << TMR4_SCMR_AMC_POS)   /*!< Mask 2 times */
#define TMR4_SEVT_MASK3                     (3U << TMR4_SCMR_AMC_POS)   /*!< Mask 3 times */
#define TMR4_SEVT_MASK4                     (4U << TMR4_SCMR_AMC_POS)   /*!< Mask 4 times */
#define TMR4_SEVT_MASK5                     (5U << TMR4_SCMR_AMC_POS)   /*!< Mask 5 times */
#define TMR4_SEVT_MASK6                     (6U << TMR4_SCMR_AMC_POS)   /*!< Mask 6 times */
#define TMR4_SEVT_MASK7                     (7U << TMR4_SCMR_AMC_POS)   /*!< Mask 7 times */
#define TMR4_SEVT_MASK8                     (8U << TMR4_SCMR_AMC_POS)   /*!< Mask 8 times */
#define TMR4_SEVT_MASK9                     (9U << TMR4_SCMR_AMC_POS)   /*!< Mask 9 times */
#define TMR4_SEVT_MASK10                    (10U << TMR4_SCMR_AMC_POS)  /*!< Mask 10 times */
#define TMR4_SEVT_MASK11                    (11U << TMR4_SCMR_AMC_POS)  /*!< Mask 11 times */
#define TMR4_SEVT_MASK12                    (12U << TMR4_SCMR_AMC_POS)  /*!< Mask 12 times */
#define TMR4_SEVT_MASK13                    (13U << TMR4_SCMR_AMC_POS)  /*!< Mask 13 times */
#define TMR4_SEVT_MASK14                    (14U << TMR4_SCMR_AMC_POS)  /*!< Mask 14 times */
#define TMR4_SEVT_MASK15                    (15U << TMR4_SCMR_AMC_POS)  /*!< Mask 15 times */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Output_Event TMR4 SEVT Output Event
 * @{
 */
#define TMR4_SEVT_OUTPUT_EVT0               (0U)                        /*!< TMR4 SEVT output special event 0 */
#define TMR4_SEVT_OUTPUT_EVT1               (1U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 SEVT output special event 1 */
#define TMR4_SEVT_OUTPUT_EVT2               (2U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 SEVT output special event 2 */
#define TMR4_SEVT_OUTPUT_EVT3               (3U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 SEVT output special event 3 */
#define TMR4_SEVT_OUTPUT_EVT4               (4U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 SEVT output special event 4 */
#define TMR4_SEVT_OUTPUT_EVT5               (5U << TMR4_SCSR_EVTOS_POS) /*!< TMR4 SEVT output special event 5 */
/**
 * @}
 */

/** @defgroup TMR4_SEVT_Output_Event_Signal TMR4 SEVT Output Event Signal
 * @{
 */
#define TMR4_SEVT_OUTPUT_NONE               (0U)                        /*!< Disable output event signal of TMR4 Special-EVT */
#define TMR4_SEVT_OUTPUT_EVT0_SIGNAL        (1U << TMR4_SCER_EVTRS_POS) /*!< Output the specified event 0 signal of TMR4 Special-EVT */
#define TMR4_SEVT_OUTPUT_EVT1_SIGNAL        (2U << TMR4_SCER_EVTRS_POS) /*!< Output the specified event 1 signal of TMR4 Special-EVT */
#define TMR4_SEVT_OUTPUT_EVT2_SIGNAL        (3U << TMR4_SCER_EVTRS_POS) /*!< Output the specified event 2 signal of TMR4 Special-EVT */
#define TMR4_SEVT_OUTPUT_EVT3_SIGNAL        (4U << TMR4_SCER_EVTRS_POS) /*!< Output the specified event 3 signal of TMR4 Special-EVT */
#define TMR4_SEVT_OUTPUT_EVT4_SIGNAL        (5U << TMR4_SCER_EVTRS_POS) /*!< Output the specified event 4 signal of TMR4 Special-EVT */
#define TMR4_SEVT_OUTPUT_EVT5_SIGNAL        (6U << TMR4_SCER_EVTRS_POS) /*!< Output the specified event 5 signal of TMR4 Special-EVT */
/**
 * @}
 */

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
 * @addtogroup TMR4_Global_Functions
 * @{
 */

/**
 * @addtogroup TMR4_CNT_Global_Functions
 * @{
 */
en_result_t TMR4_CNT_Init(CM_TMR4_TypeDef *TMR4x,
                                const stc_tmr4_cnt_init_t *pstcCntInit);
en_result_t TMR4_CNT_StructInit(stc_tmr4_cnt_init_t *pstcCntInit);
void TMR4_CNT_DeInit(CM_TMR4_TypeDef *TMR4x);
void TMR4_CNT_SetClockSrc(CM_TMR4_TypeDef *TMR4x, uint16_t u16Src);
void TMR4_CNT_SetClockDiv(CM_TMR4_TypeDef *TMR4x, uint16_t u16Div);
uint16_t TMR4_CNT_GetPeriodValue(const CM_TMR4_TypeDef *TMR4x);
void TMR4_CNT_SetCountMode(CM_TMR4_TypeDef *TMR4x, uint16_t u16Mode);
void TMR4_CNT_SetPeriodValue(CM_TMR4_TypeDef *TMR4x, uint16_t u16Value);
void TMR4_CNT_ClearCountValue(CM_TMR4_TypeDef *TMR4x);
uint16_t TMR4_CNT_GetCountValue(const CM_TMR4_TypeDef *TMR4x);
void TMR4_CNT_SetCountValue(CM_TMR4_TypeDef *TMR4x, uint16_t u16Value);
void TMR4_CNT_Start(CM_TMR4_TypeDef *TMR4x);
void TMR4_CNT_Stop(CM_TMR4_TypeDef *TMR4x);
void TMR4_CNT_ClearStatus(CM_TMR4_TypeDef *TMR4x, uint16_t u16Flag);
en_flag_status_t TMR4_CNT_GetStatus(const CM_TMR4_TypeDef *TMR4x,
                                        uint16_t u16Flag);
void TMR4_CNT_PeriodBufCmd(CM_TMR4_TypeDef *TMR4x,
                            en_functional_state_t enNewState);
void TMR4_CNT_PortOutputCmd(CM_TMR4_TypeDef *TMR4x,
                                    en_functional_state_t enNewState);
void TMR4_CNT_IntCmd(CM_TMR4_TypeDef *TMR4x,
                            uint16_t u16IntType,
                            en_functional_state_t enNewState);
uint16_t TMR4_CNT_GetIntMaskTimes(const CM_TMR4_TypeDef *TMR4x,
                                        uint16_t u16IntType);
void TMR4_CNT_SetIntMaskTimes(CM_TMR4_TypeDef *TMR4x,
                                        uint16_t u16IntType,
                                        uint16_t u16MaskTimes);
uint16_t TMR4_CNT_GetCurrentIntMaskTimes(const CM_TMR4_TypeDef *TMR4x,
                                        uint16_t u16IntType);
/**
 * @}
 */

/**
 * @addtogroup TMR4_OCO_Global_Functions
 * @{
 */
en_result_t TMR4_OCO_Init(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            const stc_tmr4_oco_init_t *pstcOcoInit);
en_result_t TMR4_OCO_StructInit(stc_tmr4_oco_init_t *pstcOcoInit);
void TMR4_OCO_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_OCO_ClearStatus(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
en_flag_status_t TMR4_OCO_GetStatus(const CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch);
uint16_t TMR4_OCO_GetCompareValue(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_OCO_SetCompareValue(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16Value);
void TMR4_OCO_Cmd(CM_TMR4_TypeDef *TMR4x,
                    uint32_t u32Ch,
                    en_functional_state_t enNewState);
void TMR4_OCO_IntCmd(CM_TMR4_TypeDef *TMR4x,
                        uint32_t u32Ch,
                        en_functional_state_t enNewState);
void TMR4_OCO_ExtendControlCmd(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                en_functional_state_t enNewState);
void TMR4_OCO_CompareBufLinkTransferCmd(CM_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16Object,
                                        en_functional_state_t enNewState);
uint16_t TMR4_OCO_GetPolarity(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_OCO_SetOcoInvalidPolarity(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16Polarity);
void TMR4_OCO_SetCompareBufCond(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Object,
                                uint16_t u16BufCond);
uint16_t TMR4_OCO_GetHighChCompareMode(const CM_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch);
en_result_t TMR4_OCO_SetHighChCompareMode(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_oco_high_ch_compare_mode_t *pstcMode);
uint32_t TMR4_OCO_GetLowChCompareMode(const CM_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch);
en_result_t TMR4_OCO_SetLowChCompareMode(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_oco_low_ch_compare_mode_t *pstcMode);
/**
 * @}
 */

/**
 * @addtogroup TMR4_PWM_Global_Functions
 * @{
 */
en_result_t TMR4_PWM_Init(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            const stc_tmr4_pwm_init_t *pstcPwmInit);
en_result_t TMR4_PWM_StructInit(stc_tmr4_pwm_init_t *pstcPwmInit);
void TMR4_PWM_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_PWM_SetClockDiv(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Div);
void TMR4_PWM_SetPolarity(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            uint16_t u16Polarity);
void TMR4_PWM_SetAbnormalPolarity(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32PwmPort,
                                    uint32_t u32Polarity);
void TMR4_PWM_StartReloadTimer(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_PWM_StopReloadTimer(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_PWM_IntCmd(CM_TMR4_TypeDef *TMR4x,
                        uint32_t u32Ch,
                        en_functional_state_t enNewState);
en_flag_status_t TMR4_PWM_GetStatus(const CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch);
void TMR4_PWM_ClearStatus(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch);
void TMR4_PWM_SetOEEffectTime(CM_TMR4_TypeDef *TMR4x, uint32_t u32Time);
void TMR4_PWM_SetEmbReleaseMode(CM_TMR4_TypeDef *TMR4x, uint32_t u32Mode);
void TMR4_PWM_MasterOutputCmd(CM_TMR4_TypeDef *TMR4x,
                                        en_functional_state_t enNewState);
void TMR4_PWM_SetPortOutputMode(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32PwmPort,
                                uint32_t u32Mode);
void TMR4_PWM_SetFilterCountValue(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16Value);
void TMR4_PWM_SetDeadTimeValue(CM_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint32_t u32DeadTimeIndex,
                                        uint16_t u16Value);
uint16_t TMR4_PWM_GetDeadTimeValue(const CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint32_t u32DeadTimeIndex);
/**
 * @}
 */

/**
 * @addtogroup TMR4_SEVT_Global_Functions
 * @{
 */
en_result_t TMR4_SEVT_Init(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            const stc_tmr4_sevt_init_t *pstcSevtInit);
en_result_t TMR4_SEVT_StructInit(stc_tmr4_sevt_init_t *pstcSevtInit);
void TMR4_SEVT_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_SEVT_SetDelayObject(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Object);
void TMR4_SEVT_SetMaskTimes(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            uint16_t u16MaskTimes);
uint16_t TMR4_SEVT_GetMaskTimes(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_SEVT_SetCompareValue(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Value);
uint16_t TMR4_SEVT_GetCompareValue(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch);
void TMR4_SEVT_SetOutpuEvent(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Event);
void TMR4_SEVT_SetOutputEventSignal(CM_TMR4_TypeDef *TMR4x, uint16_t u16Signal);
void TMR4_SEVT_SetCompareBufCond(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16BufCond);
void TMR4_SEVT_CountCompareCondCmd(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16Type,
                                    en_functional_state_t enNewState);
void TMR4_SEVT_MaskCompareCmd(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16MaskType,
                                    en_functional_state_t enNewState);
/**
 * @}
 */

/**
 * @}
 */

#endif /* DDL_TMR4_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_TMR4_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
