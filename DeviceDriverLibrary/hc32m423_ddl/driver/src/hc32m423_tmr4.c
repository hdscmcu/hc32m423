/**
 *******************************************************************************
 * @file  hc32m423_tmr4.c
 * @brief This file provides firmware functions to manage the TMR4(Timer4)
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
#include "hc32m423_tmr4.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TMR4 TMR4
 * @brief TMR4 Driver Library
 * @{
 */

#if (DDL_TMR4_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR4_Local_Macros TMR4 Local Macros
 * @{
 */

/**
 * @defgroup TMR4_Check_Parameters_Validity TMR4 Check Parameters Validity
 * @{
 */

#define IS_TMR4_UNIT(x)                         ((x) == CM_TMR4)

#define IS_TMR4_CNT_CLK_DIV(x)                                                 \
(   ((x) == TMR4_CNT_CLK_DIV1)                  ||                             \
    ((x) == TMR4_CNT_CLK_DIV2)                  ||                             \
    ((x) == TMR4_CNT_CLK_DIV4)                  ||                             \
    ((x) == TMR4_CNT_CLK_DIV8)                  ||                             \
    ((x) == TMR4_CNT_CLK_DIV16)                 ||                             \
    ((x) == TMR4_CNT_CLK_DIV32)                 ||                             \
    ((x) == TMR4_CNT_CLK_DIV64)                 ||                             \
    ((x) == TMR4_CNT_CLK_DIV128)                ||                             \
    ((x) == TMR4_CNT_CLK_DIV256)                ||                             \
    ((x) == TMR4_CNT_CLK_DIV512)                ||                             \
    ((x) == TMR4_CNT_CLK_DIV1024))

#define IS_TMR4_CNT_MD(x)                                                      \
(   ((x) == TMR4_CNT_MD_SAWTOOTH)               ||                             \
    ((x) == TMR4_CNT_MD_TRIANGLE))

#define IS_TMR4_CNT_CLK_SRC(x)                                                 \
(   ((x) == TMR4_CNT_PCLK)                      ||                             \
    ((x) == TMR4_CNT_EXTCLK))

#define IS_TMR4_CNT_INT_MASKTIMES(x)                                           \
(   ((x) == TMR4_CNT_INT_MASK0)                 ||                             \
    ((x) == TMR4_CNT_INT_MASK1)                 ||                             \
    ((x) == TMR4_CNT_INT_MASK2)                 ||                             \
    ((x) == TMR4_CNT_INT_MASK3)                 ||                             \
    ((x) == TMR4_CNT_INT_MASK4)                 ||                             \
    ((x) == TMR4_CNT_INT_MASK5)                 ||                             \
    ((x) == TMR4_CNT_INT_MASK6)                 ||                             \
    ((x) == TMR4_CNT_INT_MASK7)                 ||                             \
    ((x) == TMR4_CNT_INT_MASK8)                 ||                             \
    ((x) == TMR4_CNT_INT_MASK9)                 ||                             \
    ((x) == TMR4_CNT_INT_MASK10)                ||                             \
    ((x) == TMR4_CNT_INT_MASK11)                ||                             \
    ((x) == TMR4_CNT_INT_MASK12)                ||                             \
    ((x) == TMR4_CNT_INT_MASK13)                ||                             \
    ((x) == TMR4_CNT_INT_MASK14)                ||                             \
    ((x) == TMR4_CNT_INT_MASK15))

#define IS_TMR4_CNT_INT(x)                                                     \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR4_CNT_INT_ALL) == TMR4_CNT_INT_ALL))

#define IS_TMR4_CNT_FLAG(x)                                                    \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR4_CNT_FLAG_ALL) == TMR4_CNT_FLAG_ALL))

#define IS_TMR4_OCO_CH(x)                                                      \
(   ((x) == TMR4_OCO_CH_UH)                     ||                             \
    ((x) == TMR4_OCO_CH_UL)                     ||                             \
    ((x) == TMR4_OCO_CH_VH)                     ||                             \
    ((x) == TMR4_OCO_CH_VL)                     ||                             \
    ((x) == TMR4_OCO_CH_WH)                     ||                             \
    ((x) == TMR4_OCO_CH_WL))

#define IS_TMR4_OCO_HIGH_CH(x)                                                 \
(   ((x) == TMR4_OCO_CH_UH)                     ||                             \
    ((x) == TMR4_OCO_CH_VH)                     ||                             \
    ((x) == TMR4_OCO_CH_WH))

#define IS_TMR4_OCO_LOW_CH(x)                                                  \
(   ((x) == TMR4_OCO_CH_UL)                     ||                             \
    ((x) == TMR4_OCO_CH_VL)                     ||                             \
    ((x) == TMR4_OCO_CH_WL))

#define IS_TMR4_OCO_BUF_OBJECT(x)                                              \
(   ((x) != 0U)                                 ||                             \
    (((x) | TMR4_OCO_BUF_OBJECT_MASK) == TMR4_OCO_BUF_OBJECT_MASK))

#define IS_TMR4_OCO_BUF_COND(x)                                                \
(   ((x) == TMR4_OCO_BUF_COND_IMMED)            ||                             \
    ((x) == TMR4_OCO_BUF_COND_UDF)              ||                             \
    ((x) == TMR4_OCO_BUF_COND_OVF)              ||                             \
    ((x) == TMR4_OCO_BUF_COND_UDF_OVF))

#define IS_TMR4_OCO_INVD_POLARITY(x)                                           \
(   ((x) == TMR4_OCO_INVD_LOW)                  ||                             \
    ((x) == TMR4_OCO_INVD_HIGH))

#define IS_TMR4_OCO_POLARITY(x)                                                \
(   ((x) == TMR4_OCO_HOLD)                      ||                             \
    ((x) == TMR4_OCO_HIGH)                      ||                             \
    ((x) == TMR4_OCO_LOW)                       ||                             \
    ((x) == TMR4_OCO_INVT))

#define IS_TMR4_OCO_OCF_SEL(x)                                                 \
(   ((x) == TMR4_OCO_OCF_HOLD)                  ||                             \
    ((x) == TMR4_OCO_OCF_SET))

#define IS_TMR4_PWM_CH(x)                                                      \
(   ((x) == TMR4_PWM_CH_U)                      ||                             \
    ((x) == TMR4_PWM_CH_V)                      ||                             \
    ((x) == TMR4_PWM_CH_W))

#define IS_TMR4_PWM_PORT(x)                                                    \
(   ((x) == TMR4_PWM_PORT_OUH)                  ||                             \
    ((x) == TMR4_PWM_PORT_OUL)                  ||                             \
    ((x) == TMR4_PWM_PORT_OVH)                  ||                             \
    ((x) == TMR4_PWM_PORT_OVL)                  ||                             \
    ((x) == TMR4_PWM_PORT_OWH)                  ||                             \
    ((x) == TMR4_PWM_PORT_OWL))

#define IS_TMR4_PWM_MD(x)                                                      \
(   ((x) == TMR4_PWM_MD_THROUGH)                ||                             \
    ((x) == TMR4_PWM_MD_DEAD_TIMER)             ||                             \
    ((x) == TMR4_PWM_MD_DEAD_TIMER_FILTER))

#define IS_TMR4_PWM_EMB_RELEASE_MD(x)                                          \
(   ((x) == TMR4_PWM_EMB_RELEASE_MD_SW_MOE)     ||                             \
    ((x) == TMR4_PWM_EMB_RELEASE_MD_HW_MOE))

#define IS_TMR4_PWM_POLARITY(x)                                                \
(   ((x) == TMR4_PWM_OXH_HOLD_OXL_HOLD)         ||                             \
    ((x) == TMR4_PWM_OXH_INVT_OXL_HOLD)         ||                             \
    ((x) == TMR4_PWM_OXH_HOLD_OXL_INVT)         ||                             \
    ((x) == TMR4_PWM_OXH_INVT_OXL_INVT))

#define IS_TMR4_PWM_CLK_DIV(x)                                                 \
(   ((x) == TMR4_PWM_CLK_DIV1)                  ||                             \
    ((x) == TMR4_PWM_CLK_DIV2)                  ||                             \
    ((x) == TMR4_PWM_CLK_DIV4)                  ||                             \
    ((x) == TMR4_PWM_CLK_DIV8)                  ||                             \
    ((x) == TMR4_PWM_CLK_DIV16)                 ||                             \
    ((x) == TMR4_PWM_CLK_DIV32)                 ||                             \
    ((x) == TMR4_PWM_CLK_DIV64)                 ||                             \
    ((x) == TMR4_PWM_CLK_DIV128))

#define IS_TMR4_PWM_ABNORMAL_POLARITY(x)                                       \
(   ((x) == TMR4_PWM_ABNORMAL_POLARITY_NORMAL)  ||                             \
    ((x) == TMR4_PWM_ABNORMAL_POLARITY_HIZ)     ||                             \
    ((x) == TMR4_PWM_ABNORMAL_POLARITY_LOW)     ||                             \
    ((x) == TMR4_PWM_ABNORMAL_POLARITY_HIGH))

#define IS_TMR4_PWM_DEADTIME_REG_IDX(x)                                        \
(   ((x) == TMR4_PWM_PDAR_IDX)                  ||                             \
    ((x) == TMR4_PWM_PDBR_IDX))

#define IS_TMR4_PWM_OE_EFFECT(x)                                               \
(   ((x) == TMR4_PWM_OE_EFFECT_IMMED)           ||                             \
    ((x) == TMR4_PWM_OE_EFFECT_CNT_UDF)         ||                             \
    ((x) == TMR4_PWM_OE_EFFECT_CNT_OVF))

#define IS_TMR4_PWM_PORT_MODE(x)                                               \
(   ((x) == TMR4_PWM_PORT_OUTPUT_OS)            ||                             \
    ((x) == TMR4_PWM_PORT_OUTPUT_NORMAL))

#define IS_TMR4_SEVT_CH(x)                                                     \
(   ((x) == TMR4_SEVT_CH_UH)                    ||                             \
    ((x) == TMR4_SEVT_CH_UL)                    ||                             \
    ((x) == TMR4_SEVT_CH_VH)                    ||                             \
    ((x) == TMR4_SEVT_CH_VL)                    ||                             \
    ((x) == TMR4_SEVT_CH_WH)                    ||                             \
    ((x) == TMR4_SEVT_CH_WL))

#define IS_TMR4_SEVT_CNT_CMP_TYPE(x)                                           \
(   ((x) != 0U)                                 ||                             \
    (((x) | TMR4_SEVT_CNT_CMP_TYPE_MASK) == TMR4_SEVT_CNT_CMP_TYPE_MASK))

#define IS_TMR4_SEVT_MASK_CMP_TYPE(x)                                          \
(   ((x) != 0U)                                 ||                             \
    (((x) | TMR4_SEVT_MASK_CMP_TYPE_MASK) == TMR4_SEVT_MASK_CMP_TYPE_MASK))

#define IS_TMR4_SEVT_DELAY_OBJECT(x)                                           \
(   ((x) == TMR4_SEVT_DELAY_OCCRXH)             ||                             \
    ((x) == TMR4_SEVT_DELAY_OCCRXL))

#define IS_TMR4_SEVT_MD(x)                                                     \
(   ((x) == TMR4_SEVT_MD_DELAY)                 ||                             \
    ((x) == TMR4_SEVT_MD_CMP))

#define IS_TMR4_SEVT_MASK(x)                                                   \
(   ((x) == TMR4_SEVT_MASK0)                    ||                             \
    ((x) == TMR4_SEVT_MASK1)                    ||                             \
    ((x) == TMR4_SEVT_MASK2)                    ||                             \
    ((x) == TMR4_SEVT_MASK3)                    ||                             \
    ((x) == TMR4_SEVT_MASK4)                    ||                             \
    ((x) == TMR4_SEVT_MASK5)                    ||                             \
    ((x) == TMR4_SEVT_MASK6)                    ||                             \
    ((x) == TMR4_SEVT_MASK7)                    ||                             \
    ((x) == TMR4_SEVT_MASK8)                    ||                             \
    ((x) == TMR4_SEVT_MASK9)                    ||                             \
    ((x) == TMR4_SEVT_MASK10)                   ||                             \
    ((x) == TMR4_SEVT_MASK11)                   ||                             \
    ((x) == TMR4_SEVT_MASK12)                   ||                             \
    ((x) == TMR4_SEVT_MASK13)                   ||                             \
    ((x) == TMR4_SEVT_MASK14)                   ||                             \
    ((x) == TMR4_SEVT_MASK15))

#define IS_TMR4_SEVT_OUTPUT_EVT(x)                                             \
(   ((x) == TMR4_SEVT_OUTPUT_EVT0)              ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT1)              ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT2)              ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT3)              ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT4)              ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT5))

#define IS_TMR4_SEVT_BUF_COND(x)                                               \
(   ((x) == TMR4_SEVT_BUF_COND_IMMED)           ||                             \
    ((x) == TMR4_SEVT_BUF_COND_OVF)             ||                             \
    ((x) == TMR4_SEVT_BUF_COND_UDF)             ||                             \
    ((x) == TMR4_SEVT_BUF_COND_UDF_OVF))

#define IS_TMR4_SEVT_OUTPUT_SIGNAL(x)                                          \
(   ((x) == TMR4_SEVT_OUTPUT_NONE)              ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT0_SIGNAL)       ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT1_SIGNAL)       ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT2_SIGNAL)       ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT3_SIGNAL)       ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT4_SIGNAL)       ||                             \
    ((x) == TMR4_SEVT_OUTPUT_EVT5_SIGNAL))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCO_Buffer_Object_Mask TMR4 OCO Buffer Object Mask
 * @{
 */
#define TMR4_OCO_BUF_OBJECT_MASK            (TMR4_OCO_BUF_CMP_VALUE |          \
                                             TMR4_OCO_BUF_CMP_MD)
/**
 * @}
 */

/**
 * @defgroup TMR4_SEVT_Count_Compare_Type_Mask TMR4 SEVT Count Compare Type Mask
 * @{
 */
#define TMR4_SEVT_CNT_CMP_TYPE_MASK         (TMR4_SEVT_CNT_CMP_UP   |          \
                                             TMR4_SEVT_CNT_CMP_DOWN |          \
                                             TMR4_SEVT_CNT_CMP_ZERO |          \
                                             TMR4_SEVT_CNT_CMP_PEAK)
/**
 * @}
 */

/**
 * @defgroup TMR4_SEVT_Mask_Compare_Type_Mask TMR4 SEVT Mask Compare Type Mask
 * @{
 */
#define TMR4_SEVT_MASK_CMP_TYPE_MASK        (TMR4_SEVT_MASK_CMP_UDF |          \
                                             TMR4_SEVT_MASK_CMP_OVF)
/**
 * @}
 */

/**
 * @defgroup TMR4_Register_Address Get TMR4 register address
 * @{
 */
#define TMR4_REG_ADDR(_REG_)            ((uint32_t)(&(_REG_)))
/**
 * @}
 */

/**
 * @defgroup TMR4_Register_Shift_Bits Get register value shift bit
 * @{
 */
#define SHIFT_1BIT(_CH_)                ((uint16_t)((_CH_) % 2UL))
#define SHIFT_2BIT(_CH_)                ((uint16_t)(((_CH_) % 2UL) << 1UL))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCO_Register TMR4 OCO Register
 * @brief Get the specified OCO register address of the specified TMR4 unit
 * @note  The parameter _CH_ value is TMR4_OCO_xy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_OCCRx(_UNITx_, _CH_)       ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->OCCRUH) + (((uint32_t)(_CH_)) << 2UL)))
#define TMR4_OCMRx(_UNITx_, _CH_)       ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->OCMRHUH) + (((uint32_t)(_CH_)) << 2UL)))
#define TMR4_OCERx(_UNITx_, _CH_)       ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->OCERU) + ((((uint32_t)(_CH_)) & 0x06UL) << 1UL)))
#define TMR4_OCSRx(_UNITx_, _CH_)       ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->OCSRU) + ((((uint32_t)(_CH_)) & 0x06UL) << 1UL)))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCSR_Bit_Mask TMR4_OCSR Bit Mask
 * @brief Get the specified TMR4_OCSR register bis value of the specified TMR4 OCO channel
 * @note  The parameter _CH_ value is TMR4_OCO_CH_xy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_OCSR_OCEx_MASK(_CH_)       ((uint16_t)(((uint16_t)TMR4_OCSR_OCEH) << SHIFT_1BIT(_CH_)))
#define TMR4_OCSR_OCPx_MASK(_CH_)       ((uint16_t)(((uint16_t)TMR4_OCSR_OCPH) << SHIFT_1BIT(_CH_)))
#define TMR4_OCSR_OCIEx_MASK(_CH_)      ((uint16_t)(((uint16_t)TMR4_OCSR_OCIEH) << SHIFT_1BIT(_CH_)))
#define TMR4_OCSR_OCFx_MASK(_CH_)       ((uint16_t)(((uint16_t)TMR4_OCSR_OCFH) << SHIFT_1BIT(_CH_)))
#define TMR4_OCSR_MASK(_CH_)                                                   \
(   (uint16_t)((uint16_t)(TMR4_OCSR_OCEH | TMR4_OCSR_OCPH | TMR4_OCSR_OCIEH | TMR4_OCSR_OCFH)) << SHIFT_1BIT(_CH_))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCSR_Bit TMR4_OCSR Bit
 * @brief Get the specified TMR4_OCSR register bis value of the specified TMR4 OCO channel
 * @note  The parameter _CH_ value is TMR4_OCO_CH_xy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_OCSR_OCEx(_CH_, _OCEx_)     ((uint16_t)(((uint16_t)_OCEx_) << (SHIFT_1BIT(_CH_) + TMR4_OCSR_OCEH_POS)))
#define TMR4_OCSR_OCPx(_CH_, _OCPx_)     ((uint16_t)(((uint16_t)_OCPx_) << SHIFT_1BIT(_CH_)))
#define TMR4_OCSR_OCIEx(_CH_, _OCIEx_)   ((uint16_t)(((uint16_t)_OCIEx_) << SHIFT_1BIT(_CH_)))
#define TMR4_OCSR_OCFx(_CH_, _OCFx_)     ((uint16_t)(((uint16_t)_OCFx_) << SHIFT_1BIT(_CH_)))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCER_Bit_Mask TMR4_OCER Bit Mask
 * @brief Get the specified TMR4_OCER register bis value of the specified TMR4 OCO channel
 * @note  The parameter _CH_ value is TMR4_OCO_CH_xy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_OCER_CxBUFEN_MASK(_CH_)      ((uint16_t)(((uint16_t)TMR4_OCER_CHBUFEN) << SHIFT_2BIT(_CH_)))
#define TMR4_OCER_MxBUFEN_MASK(_CH_)      ((uint16_t)(((uint16_t)TMR4_OCER_MHBUFEN) << SHIFT_2BIT(_CH_)))
#define TMR4_OCER_LMCx_MASK(_CH_)         ((uint16_t)(((uint16_t)TMR4_OCER_LMCH) << SHIFT_1BIT(_CH_)))
#define TMR4_OCER_LMMx_MASK(_CH_)         ((uint16_t)(((uint16_t)TMR4_OCER_LMMH) << SHIFT_1BIT(_CH_)))
#define TMR4_OCER_MCECx_MASK(_CH_)        ((uint16_t)(((uint16_t)TMR4_OCER_MCECH) << SHIFT_1BIT(_CH_)))
#define TMR4_OCER_MASK(_CH_)                                                   \
(   (uint16_t)(((uint16_t)(TMR4_OCER_CHBUFEN | TMR4_OCER_MHBUFEN)) << SHIFT_2BIT(_CH_)) | \
    (uint16_t)(((uint16_t)(TMR4_OCER_LMCH | TMR4_OCER_LMMH | TMR4_OCER_MCECH)) << SHIFT_2BIT(_CH_)))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCER_Bit TMR4_OCER Bit
 * @brief Get the specified TMR4_OCER register bis value of the specified TMR4 OCO channel
 * @note  The parameter _CH_ value is TMR4_OCO_CH_xy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_OCER_CxBUFEN(_CH_, _CxBUFEN_)  ((uint16_t)((_CxBUFEN_) << (SHIFT_2BIT(_CH_) + TMR4_OCER_CHBUFEN_POS)))
#define TMR4_OCER_MxBUFEN(_CH_, _MxBUFEN_)  ((uint16_t)((_MxBUFEN_) << (SHIFT_2BIT(_CH_) + TMR4_OCER_MHBUFEN_POS)))
#define TMR4_OCER_LMCx(_CH_, _LMCx_)        ((uint16_t)((uint16_t)(_LMCx_) << (SHIFT_1BIT(_CH_) + TMR4_OCER_LMCH_POS)))
#define TMR4_OCER_LMMx(_CH_, _LMMx_)        ((uint16_t)((uint16_t)(_LMMx_) << (SHIFT_1BIT(_CH_) + TMR4_OCER_LMMH_POS)))
#define TMR4_OCER_MCECx(_CH_, _MCECx_)      ((uint16_t)((uint16_t)(_MCECx_) << (SHIFT_1BIT(_CH_) + TMR4_OCER_MCECH_POS)))
/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Register TMR4 PWM Register
 * @brief Get the specified PWM register address of the specified TMR4 unit
 * @note The parameter _CH_ value is TMR4_PWM_CH_x (x=U/V/W)
 * @{
 */
#define TMR4_RCSRx(_UNITx_)             ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->RCSR)))
#define TMR4_POCRx(_UNITx_, _CH_)       ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->POCRU) + ((_CH_) << 2UL)))
#define TMR4_PFSRx(_UNITx_, _CH_)       ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->PFSRU) + ((_CH_) << 3UL)))
#define TMR4_PDRx(_UNITx_, _CH_, _IDX_) ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->PDARU) + ((_CH_) << 3UL) + ((_IDX_) << 1UL)))
/**
 * @}
 */

/**
 * @defgroup TMR4_RCSR_Bit_Mask TMR4_RCSR Bit Mask
 * @brief Get the specified TMR4_RCSR register bis value of the specified TMR4 PWM channel
 * @note The parameter _CH_ value is TMR4_PWM_CH_x (x=U/V/W)
 * @{
 */
#define TMR4_RCSR_RTIDx_MASK(_CH_)  ((uint16_t)(((uint16_t)TMR4_RCSR_RTIDU) << (_CH_)))
#define TMR4_RCSR_RTIFx_MASK(_CH_)  ((uint16_t)(((uint16_t)TMR4_RCSR_RTIFU) << ((_CH_) << 2UL)))
#define TMR4_RCSR_RTICx_MASK(_CH_)  ((uint16_t)(((uint16_t)TMR4_RCSR_RTICU) << ((_CH_) << 2UL)))
#define TMR4_RCSR_RTEx_MASK(_CH_)   ((uint16_t)(((uint16_t)TMR4_RCSR_RTEU) << ((_CH_) << 2UL)))
#define TMR4_RCSR_RTSx_MASK(_CH_)   ((uint16_t)(((uint16_t)TMR4_RCSR_RTSU) << ((_CH_) << 2UL)))
/**
 * @}
 */

/**
 * @defgroup TMR4_PSCR_Bit_Mask TMR4_PSCR Bit Mask
 * @brief Get the specified TMR4_PSCR register bis value of the specified TMR4 PWM port channel
 * @note  The parameter _PORT_ value is TMR4_PWM_PORT_Oxy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_PSCR_OExy_MASK(_PORT_)     (TMR4_PSCR_OEUH << (_PORT_))
#define TMR4_PSCR_OSxy_MASK(_PORT_)     (TMR4_PSCR_OSUH << ((_PORT_) << 1UL))
/**
 * @}
 */

/**
 * @defgroup TMR4_PSCR_Bit TMR4_PSCR Bit
 * @brief Get the specified TMR4_PSCR register bis value of the specified TMR4 PWM port channel
 * @note  The parameter PORT value is TMR4_PWM_PORT_Oxy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_PSCR_OExy(_PORT_, _OExy_)  ((_OExy_) << (_PORT_))
#define TMR4_PSCR_OSxy(_PORT_, _OSxy_)  ((_OSxy_) << (((_PORT_) << 1UL) + TMR4_PSCR_OSUH_POS))
/**
 * @}
 */

/**
 * @defgroup TMR4_SEVT_Register TMR4 SEVT Register
 * @brief Get the specified SEVT register address of the specified TMR4 unit
 * @note  The parameter _CH_ value is TMR4_SEVT_CH_xy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_SCCRx(_UNITx_, _CH_)       ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->SCCRUH) + ((_CH_) << 2UL)))
#define TMR4_SCSRx(_UNITx_, _CH_)       ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->SCSRUH) + ((_CH_) << 2UL)))
#define TMR4_SCMRx(_UNITx_, _CH_)       ((__IO uint16_t *)(TMR4_REG_ADDR((_UNITx_)->SCMRUH) + ((_CH_) << 2UL)))
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
 * @defgroup TMR4_Global_Functions TMR4 Global Functions
 * @{
 */

/**
 * @defgroup TMR4_CNT_Global_Functions TMR4 Counter Global Functions
 * @{
 */

/**
 * @brief  Initialize TMR4 counter.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] pstcCntInit         Pointer to a @ref stc_tmr4_cnt_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcCntInit is NULL
 */
en_result_t TMR4_CNT_Init(CM_TMR4_TypeDef *TMR4x,
                                const stc_tmr4_cnt_init_t *pstcCntInit)
{
    uint16_t u16Value;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcCntInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
        DDL_ASSERT(IS_TMR4_CNT_CLK_SRC(pstcCntInit->u16ClockSrc));
        DDL_ASSERT(IS_TMR4_CNT_CLK_DIV(pstcCntInit->u16ClockDiv));
        DDL_ASSERT(IS_TMR4_CNT_MD(pstcCntInit->u16CountMode));

        /* Set TMR4_CCSR */
        u16Value = (pstcCntInit->u16ClockDiv  | \
                    pstcCntInit->u16ClockSrc  | \
                    pstcCntInit->u16CountMode | \
                    TMR4_CCSR_CLEAR | \
                    TMR4_CCSR_STOP);
        WRITE_REG16(TMR4x->CCSR, u16Value);

        /* Set TMR4_CVPR: default value */
        WRITE_REG16(TMR4x->CVPR, 0x0000U);

        /* Set TMR4 period */
        WRITE_REG16(TMR4x->CPSR, pstcCntInit->u16PeriodValue);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr4_cnt_init_t to default values
 * @param  [out] pstcCntInit        Pointer to a @ref stc_tmr4_cnt_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcCntInit is NULL
 */
en_result_t TMR4_CNT_StructInit(stc_tmr4_cnt_init_t *pstcCntInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcCntInit)
    {
        pstcCntInit->u16PeriodValue = 0xFFFFU;
        pstcCntInit->u16CountMode = TMR4_CNT_MD_SAWTOOTH;
        pstcCntInit->u16ClockSrc = TMR4_CNT_PCLK;
        pstcCntInit->u16ClockDiv = TMR4_CNT_CLK_DIV1;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize TMR4 counter function
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @retval None
 */
void TMR4_CNT_DeInit(CM_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    /* Configures the registers to reset value. */
    WRITE_REG16(TMR4x->CCSR, 0x0040U);
    WRITE_REG16(TMR4x->CPSR, 0xFFFFU);
    WRITE_REG16(TMR4x->CVPR, 0x0000U);
}

/**
 * @brief Set TMR4 counter clock source
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16Src              TMR4 CNT clock source
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_PCLK:    Uses the internal clock (PCLK) as counter's count clock
 *           @arg TMR4_CNT_EXTCLK:  Uses an external input clock (EXCK) as counter's count clock
 * @retval None
 * @note   The PCLK division function is valid when clock source is PCLK
 */
void TMR4_CNT_SetClockSrc(CM_TMR4_TypeDef *TMR4x, uint16_t u16Src)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CNT_CLK_SRC(u16Src));

    /* Set external clock enable bit */
    MODIFY_REG16(TMR4x->CCSR, TMR4_CCSR_ECKEN, u16Src);
}

/**
 * @brief  Set TMR4 counter clock division
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16Div              TMR4 clock division
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_CLK_DIV1:    PCLK
 *           @arg TMR4_CNT_CLK_DIV2:    PCLK/2
 *           @arg TMR4_CNT_CLK_DIV4:    PCLK/4
 *           @arg TMR4_CNT_CLK_DIV8:    PCLK/8
 *           @arg TMR4_CNT_CLK_DIV16:   PCLK/16
 *           @arg TMR4_CNT_CLK_DIV32:   PCLK/32
 *           @arg TMR4_CNT_CLK_DIV64:   PCLK/64
 *           @arg TMR4_CNT_CLK_DIV128:  PCLK/128
 *           @arg TMR4_CNT_CLK_DIV256:  PCLK/256
 *           @arg TMR4_CNT_CLK_DIV512:  PCLK/512
 *           @arg TMR4_CNT_CLK_DIV1024: PCLK/1024
 * @retval None
 * @note   The PCLK division function is valid when clock source is PCLK
 */
void TMR4_CNT_SetClockDiv(CM_TMR4_TypeDef *TMR4x, uint16_t u16Div)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CNT_CLK_DIV(u16Div));

    MODIFY_REG16(TMR4x->CCSR, TMR4_CCSR_CKDIV, u16Div);
}

/**
 * @brief  Get the period value of the TMR4 counter.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @retval The period value of the TMR4 counter
 */
uint16_t TMR4_CNT_GetPeriodValue(const CM_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    return READ_REG16(TMR4x->CPSR);
}

/**
 * @brief Set TMR4 counter count mode
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16Mode             TMR4 counter count mode
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_MD_SAWTOOTH: TMR4 count mode sawtooth wave
 *           @arg TMR4_CNT_MD_TRIANGLE: TMR4 count mode triangular
 * @retval None
 */
void TMR4_CNT_SetCountMode(CM_TMR4_TypeDef *TMR4x, uint16_t u16Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CNT_MD(u16Mode));

    /* Set external clock enable bit */
    MODIFY_REG16(TMR4x->CCSR, TMR4_CCSR_MODE, u16Mode);
}

/**
 * @brief  Set the period value of the TMR4 counter.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16Value            The period value of the TMR4 counter
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_CNT_SetPeriodValue(CM_TMR4_TypeDef *TMR4x, uint16_t u16Value)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    WRITE_REG16(TMR4x->CPSR, u16Value);
}

/**
 * @brief  Clear TMR4 counter count value
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @retval None
 */
void TMR4_CNT_ClearCountValue(CM_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    SET_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_CLEAR);
}

/**
 * @brief  Get the count value of the TMR4 counter.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @retval The count value of the TMR4 counter
 */
uint16_t TMR4_CNT_GetCountValue(const CM_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    return READ_REG16(TMR4x->CNTR);
}

/**
 * @brief  Set the count value of the TMR4 counter.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16Value            The count value of the TMR4 counter
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_CNT_SetCountValue(CM_TMR4_TypeDef *TMR4x, uint16_t u16Value)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    WRITE_REG16(TMR4x->CNTR, u16Value);
}

/**
 * @brief Start TMR4 counter
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @retval None
 */
void TMR4_CNT_Start(CM_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    CLEAR_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_STOP);
}

/**
 * @brief  Stop TMR4 counter
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @retval None
 */
void TMR4_CNT_Stop(CM_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));

    SET_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_STOP);
}

/**
 * @brief  Clear TMR4 counter flag
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16Flag             TMR4 counter flag
 *         This parameter can be any composed value of the following values:
 *           @arg TMR4_CNT_FLAG_PEAK: Overflow interrupt
 *           @arg TMR4_CNT_FLAG_ZERO: Underflow interrupt
 * @retval None
 */
void TMR4_CNT_ClearStatus(CM_TMR4_TypeDef *TMR4x, uint16_t u16Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CNT_FLAG(u16Flag));

    CLEAR_REG16_BIT(TMR4x->CCSR, u16Flag);
}

/**
 * @brief  Get TMR4 counter flag
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16Flag             TMR4 flag
 *         This parameter can be any composed value of the following values:
 *           @arg TMR4_CNT_FLAG_PEAK: Overflow flag
 *           @arg TMR4_CNT_FLAG_ZERO: Underflow flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set:   Any bit of the composed flag is set.
 *           - Reset: All bit of the composed flag is reset.
 */
en_flag_status_t TMR4_CNT_GetStatus(const CM_TMR4_TypeDef *TMR4x,
                                        uint16_t u16Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CNT_FLAG(u16Flag));

    return (READ_REG16_BIT(TMR4x->CCSR, u16Flag) == 0U) ? Reset : Set;
}

/**
 * @brief  Enable or disable the TMR4 counter period buffer function.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the TMR4 counter period buffer function.
 *           @arg Disable:          Disable the TMR4 counter period buffer function.
 * @retval None
 */
void TMR4_CNT_PeriodBufCmd(CM_TMR4_TypeDef *TMR4x,
                            en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_BUFEN);
    }
    else
    {
        CLEAR_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_BUFEN);
    }
}

/**
 * @brief  Enable or disable port output TMR4 count direction signal
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable port output TMR4 count direction signal
 *           @arg Disable:          Disable port output TMR4 count direction signal
 * @retval None
 */
void TMR4_CNT_PortOutputCmd(CM_TMR4_TypeDef *TMR4x,
                                    en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMR4x->SCER, TMR4_SCER_PCTS);
    }
    else
    {
        CLEAR_REG16_BIT(TMR4x->SCER, TMR4_SCER_PCTS);
    }
}

/**
 * @brief  Enable or disable the specified TMR4 counter interrupt
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16IntType          TMR4 interrupt source
 *         This parameter can be any composed value of the following values:
 *           @arg TMR4_CNT_INT_PEAK: Overflow interrupt
 *           @arg TMR4_CNT_INT_ZERO: Underflow interrupt
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified TMR4 counter interrupt
 *           @arg Disable:          Disable the specified TMR4 counter interrupt
 * @retval None
 */
void TMR4_CNT_IntCmd(CM_TMR4_TypeDef *TMR4x,
                            uint16_t u16IntType,
                            en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CNT_INT(u16IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMR4x->CCSR, u16IntType);
    }
    else
    {
        CLEAR_REG16_BIT(TMR4x->CCSR, u16IntType);
    }
}

/**
 * @brief  Get TMR4 CNT interrupt mask times
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16IntType          TMR4 interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_INT_PEAK:   Overflow interrupt
 *           @arg TMR4_CNT_INT_ZERO:   Underflow interrupt
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_CNT_INT_MASK0:  Counter interrupt flag is always set(not masked) for every counter count at "0x0000" or peak
 *           @arg TMR4_CNT_INT_MASK1:  Counter interrupt flag is set once for 2 every counter counts at "0x0000" or peak (skiping 1 count)
 *           @arg TMR4_CNT_INT_MASK2:  Counter interrupt flag is set once for 3 every counter counts at "0x0000" or peak (skiping 2 count)
 *           @arg TMR4_CNT_INT_MASK3:  Counter interrupt flag is set once for 4 every counter counts at "0x0000" or peak (skiping 3 count)
 *           @arg TMR4_CNT_INT_MASK4:  Counter interrupt flag is set once for 5 every counter counts at "0x0000" or peak (skiping 4 count)
 *           @arg TMR4_CNT_INT_MASK5:  Counter interrupt flag is set once for 6 every counter counts at "0x0000" or peak (skiping 5 count)
 *           @arg TMR4_CNT_INT_MASK6:  Counter interrupt flag is set once for 7 every counter counts at "0x0000" or peak (skiping 6 count)
 *           @arg TMR4_CNT_INT_MASK7:  Counter interrupt flag is set once for 8 every counter counts at "0x0000" or peak (skiping 7 count)
 *           @arg TMR4_CNT_INT_MASK8:  Counter interrupt flag is set once for 9 every counter counts at "0x0000" or peak (skiping 8 count)
 *           @arg TMR4_CNT_INT_MASK9:  Counter interrupt flag is set once for 10 every counter counts at "0x0000" or peak (skiping 9 count)
 *           @arg TMR4_CNT_INT_MASK10: Counter interrupt flag is set once for 11 every counter counts at "0x0000" or peak (skiping 10 count)
 *           @arg TMR4_CNT_INT_MASK11: Counter interrupt flag is set once for 12 every counter counts at "0x0000" or peak (skiping 11 count)
 *           @arg TMR4_CNT_INT_MASK12: Counter interrupt flag is set once for 13 every counter counts at "0x0000" or peak (skiping 12 count)
 *           @arg TMR4_CNT_INT_MASK13: Counter interrupt flag is set once for 14 every counter counts at "0x0000" or peak (skiping 13 count)
 *           @arg TMR4_CNT_INT_MASK14: Counter interrupt flag is set once for 15 every counter counts at "0x0000" or peak (skiping 14 count)
 *           @arg TMR4_CNT_INT_MASK15: Counter interrupt flag is set once for 16 every counter counts at "0x0000" or peak (skiping 15 count)
 */
uint16_t TMR4_CNT_GetIntMaskTimes(const CM_TMR4_TypeDef *TMR4x,
                                        uint16_t u16IntType)
{
    uint16_t u16MaskTimes;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CNT_INT(u16IntType));

    if (TMR4_CNT_INT_ZERO == u16IntType)
    {
        u16MaskTimes = (READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_ZIM) >> TMR4_CVPR_ZIM_POS);
    }
    else
    {
        u16MaskTimes = (READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_PIM) >> TMR4_CVPR_PIM_POS);
    }

    return u16MaskTimes;
}

/**
 * @brief  Set TMR4 counter interrupt mask times
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16IntType          TMR4 interrupt source
 *         This parameter can be any composed value of the following values:
 *           @arg TMR4_CNT_INT_PEAK:   Overflow interrupt
 *           @arg TMR4_CNT_INT_ZERO:   Underflow interrupt
 * @param [in] u16MaskTimes         TMR4 counter interrupt mask times
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_INT_MASK0:  Counter interrupt flag is always set(not masked) for every counter count at "0x0000" or peak
 *           @arg TMR4_CNT_INT_MASK1:  Counter interrupt flag is set once for 2 every counter counts at "0x0000" or peak (skiping 1 count)
 *           @arg TMR4_CNT_INT_MASK2:  Counter interrupt flag is set once for 3 every counter counts at "0x0000" or peak (skiping 2 count)
 *           @arg TMR4_CNT_INT_MASK3:  Counter interrupt flag is set once for 4 every counter counts at "0x0000" or peak (skiping 3 count)
 *           @arg TMR4_CNT_INT_MASK4:  Counter interrupt flag is set once for 5 every counter counts at "0x0000" or peak (skiping 4 count)
 *           @arg TMR4_CNT_INT_MASK5:  Counter interrupt flag is set once for 6 every counter counts at "0x0000" or peak (skiping 5 count)
 *           @arg TMR4_CNT_INT_MASK6:  Counter interrupt flag is set once for 7 every counter counts at "0x0000" or peak (skiping 6 count)
 *           @arg TMR4_CNT_INT_MASK7:  Counter interrupt flag is set once for 8 every counter counts at "0x0000" or peak (skiping 7 count)
 *           @arg TMR4_CNT_INT_MASK8:  Counter interrupt flag is set once for 9 every counter counts at "0x0000" or peak (skiping 8 count)
 *           @arg TMR4_CNT_INT_MASK9:  Counter interrupt flag is set once for 10 every counter counts at "0x0000" or peak (skiping 9 count)
 *           @arg TMR4_CNT_INT_MASK10: Counter interrupt flag is set once for 11 every counter counts at "0x0000" or peak (skiping 10 count)
 *           @arg TMR4_CNT_INT_MASK11: Counter interrupt flag is set once for 12 every counter counts at "0x0000" or peak (skiping 11 count)
 *           @arg TMR4_CNT_INT_MASK12: Counter interrupt flag is set once for 13 every counter counts at "0x0000" or peak (skiping 12 count)
 *           @arg TMR4_CNT_INT_MASK13: Counter interrupt flag is set once for 14 every counter counts at "0x0000" or peak (skiping 13 count)
 *           @arg TMR4_CNT_INT_MASK14: Counter interrupt flag is set once for 15 every counter counts at "0x0000" or peak (skiping 14 count)
 *           @arg TMR4_CNT_INT_MASK15: Counter interrupt flag is set once for 16 every counter counts at "0x0000" or peak (skiping 15 count)
 * @retval None
 */
void TMR4_CNT_SetIntMaskTimes(CM_TMR4_TypeDef *TMR4x,
                                        uint16_t u16IntType,
                                        uint16_t u16MaskTimes)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CNT_INT(u16IntType));
    DDL_ASSERT(IS_TMR4_CNT_INT_MASKTIMES(u16MaskTimes));

    if (TMR4_CNT_INT_ZERO == (u16IntType & TMR4_CNT_INT_ZERO))
    {
        MODIFY_REG16(TMR4x->CVPR, TMR4_CVPR_ZIM, (u16MaskTimes << TMR4_CVPR_ZIM_POS));
    }

    if (TMR4_CNT_INT_PEAK == (u16IntType & TMR4_CNT_INT_PEAK))
    {
        MODIFY_REG16(TMR4x->CVPR, TMR4_CVPR_PIM, (u16MaskTimes << TMR4_CVPR_PIM_POS));
    }
}

/**
 * @brief  Get TMR4 CNT current interrupt mask times
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16IntType          TMR4 interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_INT_PEAK:   Overflow interrupt
 *           @arg TMR4_CNT_INT_ZERO:   Underflow interrupt
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_CNT_INT_MASK0:  Counter interrupt flag is always set(not masked) for every counter count at "0x0000" or peak
 *           @arg TMR4_CNT_INT_MASK1:  Counter interrupt flag is set once for 2 every counter counts at "0x0000" or peak (skiping 1 count)
 *           @arg TMR4_CNT_INT_MASK2:  Counter interrupt flag is set once for 3 every counter counts at "0x0000" or peak (skiping 2 count)
 *           @arg TMR4_CNT_INT_MASK3:  Counter interrupt flag is set once for 4 every counter counts at "0x0000" or peak (skiping 3 count)
 *           @arg TMR4_CNT_INT_MASK4:  Counter interrupt flag is set once for 5 every counter counts at "0x0000" or peak (skiping 4 count)
 *           @arg TMR4_CNT_INT_MASK5:  Counter interrupt flag is set once for 6 every counter counts at "0x0000" or peak (skiping 5 count)
 *           @arg TMR4_CNT_INT_MASK6:  Counter interrupt flag is set once for 7 every counter counts at "0x0000" or peak (skiping 6 count)
 *           @arg TMR4_CNT_INT_MASK7:  Counter interrupt flag is set once for 8 every counter counts at "0x0000" or peak (skiping 7 count)
 *           @arg TMR4_CNT_INT_MASK8:  Counter interrupt flag is set once for 9 every counter counts at "0x0000" or peak (skiping 8 count)
 *           @arg TMR4_CNT_INT_MASK9:  Counter interrupt flag is set once for 10 every counter counts at "0x0000" or peak (skiping 9 count)
 *           @arg TMR4_CNT_INT_MASK10: Counter interrupt flag is set once for 11 every counter counts at "0x0000" or peak (skiping 10 count)
 *           @arg TMR4_CNT_INT_MASK11: Counter interrupt flag is set once for 12 every counter counts at "0x0000" or peak (skiping 11 count)
 *           @arg TMR4_CNT_INT_MASK12: Counter interrupt flag is set once for 13 every counter counts at "0x0000" or peak (skiping 12 count)
 *           @arg TMR4_CNT_INT_MASK13: Counter interrupt flag is set once for 14 every counter counts at "0x0000" or peak (skiping 13 count)
 *           @arg TMR4_CNT_INT_MASK14: Counter interrupt flag is set once for 15 every counter counts at "0x0000" or peak (skiping 14 count)
 *           @arg TMR4_CNT_INT_MASK15: Counter interrupt flag is set once for 16 every counter counts at "0x0000" or peak (skiping 15 count)
 */
uint16_t TMR4_CNT_GetCurrentIntMaskTimes(const CM_TMR4_TypeDef *TMR4x,
                                        uint16_t u16IntType)
{
    uint16_t u16MaskTimes;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_CNT_INT(u16IntType));

    if (TMR4_CNT_INT_ZERO == u16IntType)
    {
        u16MaskTimes = (READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_ZIC) >> TMR4_CVPR_ZIC_POS);
    }
    else
    {
        u16MaskTimes = (READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_PIC) >> TMR4_CVPR_PIC_POS);
    }

    return u16MaskTimes;
}

/**
 * @}
 */

/**
 * @defgroup TMR4_OCO_Global_Functions TMR4 OCO Global Functions
 * @{
 */

/**
 * @brief  Initialize TMR4 OCO
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @param  [in] pstcOcoInit         Pointer to a @ref stc_tmr4_oco_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcOcoInit is NULL
 */
en_result_t TMR4_OCO_Init(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            const stc_tmr4_oco_init_t *pstcOcoInit)
{
    uint16_t u16Value;
    __IO uint16_t *TMR4_OCER;
    __IO uint16_t *TMR4_OCSR;
    __IO uint16_t *TMR4_OCCR;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcOcoInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
        DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));
        DDL_ASSERT(IS_TMR4_OCO_INVD_POLARITY(pstcOcoInit->u16OcoInvalidPolarity));
        DDL_ASSERT(IS_TMR4_OCO_BUF_COND(pstcOcoInit->u16CompareModeBufCond));
        DDL_ASSERT(IS_TMR4_OCO_BUF_COND(pstcOcoInit->u16CompareValueBufCond));
        DDL_ASSERT(IS_TMR4_OCO_BUF_OBJECT(pstcOcoInit->u16BufLinkTransferObject));

        /* Get pointer of current channel OCO register address */
        TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);
        TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);
        TMR4_OCCR = TMR4_OCCRx(TMR4x, u32Ch);

        /* Set output polarity when OCO is disabled. */
        MODIFY_REG16(*TMR4_OCSR, TMR4_OCSR_MASK(u32Ch), TMR4_OCSR_OCPx(u32Ch, pstcOcoInit->u16OcoInvalidPolarity));

        /* Set OCMR&&OCCR buffer function */
        u16Value = (TMR4_OCER_MxBUFEN(u32Ch, pstcOcoInit->u16CompareModeBufCond) | \
                    TMR4_OCER_CxBUFEN(u32Ch, pstcOcoInit->u16CompareValueBufCond));
        if (TMR4_OCO_BUF_CMP_VALUE == (pstcOcoInit->u16BufLinkTransferObject & TMR4_OCO_BUF_CMP_VALUE))
        {
            u16Value |= TMR4_OCER_LMCx_MASK(u32Ch);
        }

        if (TMR4_OCO_BUF_CMP_MD == (pstcOcoInit->u16BufLinkTransferObject & TMR4_OCO_BUF_CMP_MD))
        {
            u16Value |= TMR4_OCER_LMMx_MASK(u32Ch);
        }

        MODIFY_REG16(*TMR4_OCER, TMR4_OCER_MASK(u32Ch), u16Value);

        /* Set OCO compare value */
        WRITE_REG16(*TMR4_OCCR, pstcOcoInit->u16CompareValue);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr4_oco_init_t to default values
 * @param  [out] pstcOcoInit        Pointer to a @ref stc_tmr4_oco_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcOcoInit is NULL
 */
en_result_t TMR4_OCO_StructInit(stc_tmr4_oco_init_t *pstcOcoInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcOcoInit)
    {
        pstcOcoInit->u16CompareValue = 0U;
        pstcOcoInit->u16OcoInvalidPolarity = TMR4_OCO_INVD_LOW;
        pstcOcoInit->u16CompareModeBufCond = TMR4_OCO_BUF_COND_IMMED;
        pstcOcoInit->u16CompareValueBufCond = TMR4_OCO_BUF_COND_IMMED;
        pstcOcoInit->u16BufLinkTransferObject = 0U;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initialize TMR4 OCO
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @retval None
 */
void TMR4_OCO_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *TMR4_OCER;
    __IO uint16_t *TMR4_OCSR;
    __IO uint16_t *TMR4_OCCR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);
    TMR4_OCCR = TMR4_OCCRx(TMR4x, u32Ch);

    /* Clear bits: port output valid && OP level && interrupt */
    CLEAR_REG16_BIT(*TMR4_OCSR, TMR4_OCSR_MASK(u32Ch));

    /* Clear bits: OCMR&&OCCR buffer */
    CLEAR_REG16_BIT(*TMR4_OCER, TMR4_OCER_MASK(u32Ch));

    /* Set OCO compare match value */
    WRITE_REG16(*TMR4_OCCR, 0x0000U);
}

/**
 * @brief  Clear the TMR4 OCO interrupt function
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @retval None
 */
void TMR4_OCO_ClearStatus(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    /* Clear OCSR count compare flag */
    CLEAR_REG16_BIT(*TMR4_OCSR, TMR4_OCSR_OCFx_MASK(u32Ch));
}

/**
 * @brief  Set the TMR4 OCO flag status
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @retval An en_flag_status_t enumeration value:
 *           - Set:   OCO flag is set.
 *           - Reset: OCO flag is reset.
 */
en_flag_status_t TMR4_OCO_GetStatus(const CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch)
{
    __I uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    return ((READ_REG16_BIT(*TMR4_OCSR, TMR4_OCSR_OCFx_MASK(u32Ch)) == 0U) ? Reset : Set);
}

/**
 * @brief  Get TMR4 OCO OCCR compare value
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @retval The compare value of the TMR4 OCO OCCR register
 */
uint16_t TMR4_OCO_GetCompareValue(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __I uint16_t *TMR4_OCCR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCCR = TMR4_OCCRx(TMR4x, u32Ch);

    return READ_REG16(*TMR4_OCCR);
}

/**
 * @brief  Set TMR4 OCO compare value
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @param  [in] u16Value            The compare value of the TMR4 OCO OCCR register
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_OCO_SetCompareValue(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16Value)
{
    __IO uint16_t *TMR4_OCCR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCCR = TMR4_OCCRx(TMR4x, u32Ch);

    WRITE_REG16(*TMR4_OCCR, u16Value);
}

/**
 * @brief  Enable or disable the TMR4 OCO low channel mode
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the extension control function.
 *           @arg Disable:          Disable the extension control function.
 * @retval None
 */
void TMR4_OCO_Cmd(CM_TMR4_TypeDef *TMR4x,
                    uint32_t u32Ch,
                    en_functional_state_t enNewState)
{
    __IO uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    /* Set OCSR port output compare */
    MODIFY_REG16(*TMR4_OCSR, \
                 TMR4_OCSR_OCEx_MASK(u32Ch), \
                 TMR4_OCSR_OCEx(u32Ch, enNewState));
}

/**
 * @brief  Enable or disable the TMR4 OCO interrupt function.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the TMR4 OCO interrupt function.
 *           @arg Disable:          Disable the TMR4 OCO interrupt function.
 * @retval None
 */
void TMR4_OCO_IntCmd(CM_TMR4_TypeDef *TMR4x,
                        uint32_t u32Ch,
                        en_functional_state_t enNewState)
{
    __IO uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    if (Enable == enNewState)
    {
        SET_REG16_BIT(*TMR4_OCSR, TMR4_OCSR_OCIEx_MASK(u32Ch));
    }
    else
    {
        CLEAR_REG16_BIT(*TMR4_OCSR, TMR4_OCSR_OCIEx_MASK(u32Ch));
    }
}

/**
 * @brief  Extend the matching conditions of TMR4 OCO channel
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the extension control function.
 *           @arg Disable:          Disable the extension control function.
 * @retval None
 */
void TMR4_OCO_ExtendControlCmd(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                en_functional_state_t enNewState)
{
    __IO uint16_t *TMR4_OCER;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get pointer of current channel OCO register address */
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);

    /* Set OCER register: Extend match function */
    MODIFY_REG16(*TMR4_OCER, \
                 TMR4_OCER_MCECx_MASK(u32Ch), \
                 TMR4_OCER_MCECx(u32Ch, enNewState));
}

/**
 * @brief  Set TMR4 OCO OCCR buffer link transfer function
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @param  [in] u16Object           TMR4 OCO register buffer: OCCR/OCMR
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_BUF_CMP_VALUE: The register OCCR buffer function
 *           @arg TMR4_OCO_BUF_CMP_MD: The register OCMR buffer function
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the OCMR/OCMR register buffer function.
 *           @arg Disable:          Disable the OCMR/OCMR register buffer function.
 * @retval None
 */
void TMR4_OCO_CompareBufLinkTransferCmd(CM_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16Object,
                                        en_functional_state_t enNewState)
{
    __IO uint16_t *TMR4_OCER;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_OCO_BUF_OBJECT(u16Object));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get pointer of current channel OCO register address */
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);

    if (TMR4_OCO_BUF_CMP_VALUE == (u16Object & TMR4_OCO_BUF_CMP_VALUE))
    {
        /* Set OCER register: OCCR link transfer function */
        MODIFY_REG16(*TMR4_OCER, \
                     TMR4_OCER_LMCx_MASK(u32Ch), \
                     TMR4_OCER_LMCx(u32Ch, enNewState));
    }

    if (TMR4_OCO_BUF_CMP_MD == (u16Object & TMR4_OCO_BUF_CMP_MD))
    {
        /* Set OCER register: OCMR link transfer function */
        MODIFY_REG16(*TMR4_OCER, \
                     TMR4_OCER_LMMx_MASK(u32Ch), \
                     TMR4_OCER_LMMx(u32Ch, enNewState));
    }
}

/**
 * @brief  Get TMR4 OCO output current polarity
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_OCO_INVD_LOW:     TMR4 OCO output low level when OCO is invalid
 *           @arg TMR4_OCO_INVD_OP_HIGH: TMR4 OCO output high level when OCO is invalid
 */
uint16_t TMR4_OCO_GetPolarity(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __I uint16_t *TMR4_OCSR;
    uint16_t u16Polarity;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    /* Get OCSR register: OCO output polarity */
    u16Polarity = READ_REG16_BIT(*TMR4_OCSR, TMR4_OCSR_OCPx_MASK(u32Ch));
    return (u16Polarity >> SHIFT_1BIT(u32Ch));
}

/**
 * @brief  Set TMR4 OCO invalid output polarity
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @param  [in] u16Polarity         TMR4 OCO invalid output polarity.
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_INVD_LOW:     TMR4 OCO output low level when OCO is invalid
 *           @arg TMR4_OCO_INVD_OP_HIGH: TMR4 OCO output high level when OCO is invalid
 * @retval None
 */
void TMR4_OCO_SetOcoInvalidPolarity(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16Polarity)
{
    __IO uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_OCO_INVD_POLARITY(u16Polarity));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    /* Set OCSR register: OCO invalid output polarity */
    MODIFY_REG16(*TMR4_OCSR, \
                 TMR4_OCSR_OCPx_MASK(u32Ch), \
                 TMR4_OCSR_OCPx(u32Ch, u16Polarity));
}

/**
 * @brief  Set TMR4 OCO OCCR/OCMR buffer transfer condition
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @param  [in] u16Object           TMR4 OCO register buffer type: OCCR/OCMR
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_BUF_CMP_VALUE: The register OCCR buffer function
 *           @arg TMR4_OCO_BUF_CMP_MD: The register OCMR buffer function
 * @param  [in] u16BufCond          TMR4 OCO OCCR/OCMR buffer transfer condition
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_BUF_COND_IMMED: Buffer transfer is made when writing to the OCCR/OCMR register.
 *           @arg TMR4_OCO_BUF_COND_UDF: Buffer transfer is made when counter underflow occur.
 *           @arg TMR4_OCO_BUF_COND_OVF: Buffer transfer is made when counter overflow occur.
 *           @arg TMR4_OCO_BUF_COND_UDF_OVF: Buffer transfer is made when counter underflow or overflow occur.
 * @retval None
 */
void TMR4_OCO_SetCompareBufCond(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Object,
                                uint16_t u16BufCond)
{
    __IO uint16_t *TMR4_OCER;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_OCO_BUF_OBJECT(u16Object));
    DDL_ASSERT(IS_TMR4_OCO_BUF_COND(u16BufCond));

    /* Get pointer of current channel OCO register address */
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);

    if (TMR4_OCO_BUF_CMP_VALUE == (u16Object & TMR4_OCO_BUF_CMP_VALUE))
    {
        /* Set OCER register: OCCR buffer mode */
        MODIFY_REG16(*TMR4_OCER, \
                     TMR4_OCER_CxBUFEN_MASK(u32Ch), \
                     TMR4_OCER_CxBUFEN(u32Ch, u16BufCond));
    }

    if (TMR4_OCO_BUF_CMP_MD == (u16Object & TMR4_OCO_BUF_CMP_MD))
    {
        /* Set OCER register: OCMR buffer mode */
        MODIFY_REG16(*TMR4_OCER, \
                     TMR4_OCER_MxBUFEN_MASK(u32Ch), \
                     TMR4_OCER_MxBUFEN(u32Ch, u16BufCond));
    }
}

/**
 * @brief  Get the TMR4 OCO high channel mode
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel.
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 * @retval The TMR4 OCO high channel mode
 * @note   The function only can get low channel mode:TMR4_OCO_CH_xH(x = U/V/W)
 */
uint16_t TMR4_OCO_GetHighChCompareMode(const CM_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch)
{
    __I uint16_t *TMR4_OCMRxH;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_HIGH_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCMRxH = TMR4_OCMRx(TMR4x, u32Ch);
    return READ_REG16(*TMR4_OCMRxH);
}

/**
 * @brief  Set the TMR4 OCO high channel mode
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel.
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UH:   TMR4 OCO channel - UH
 *           @arg TMR4_OCO_CH_VH:   TMR4 OCO channel - VH
 *           @arg TMR4_OCO_CH_WH:   TMR4 OCO channel - WH
 * @param  [in] pstcMode            Pointer to a @ref stc_oco_high_ch_compare_mode_t structure of the TMR4 OCO high channel mode
 * @retval An en_result_t enumeration value:
 *           - Ok: Set successfully
 *           - ErrorInvalidParameter: pstcMode is NULL
 * @note   The function only can set low channel mode:TMR4_OCO_CH_xH(x = U/V/W)
 */
en_result_t TMR4_OCO_SetHighChCompareMode(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_oco_high_ch_compare_mode_t *pstcMode)
{
    __IO uint16_t *TMR4_OCMRxH;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check pointer */
    if (NULL != pstcMode)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
        DDL_ASSERT(IS_TMR4_OCO_HIGH_CH(u32Ch));

        /* Get pointer of current channel OCO register address */
        TMR4_OCMRxH = TMR4_OCMRx(TMR4x, u32Ch);

        WRITE_REG16(*TMR4_OCMRxH, pstcMode->OCMRx);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get the TMR4 OCO low channel mode
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel.
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @retval The TMR4 OCO low channel mode
 * @note   The function only can get low channel mode:TMR4_OCO_CH_xL(x = U/V/W)
 */
uint32_t TMR4_OCO_GetLowChCompareMode(const CM_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch)
{
    __I uint32_t *TMR4_OCMRxL;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_OCO_LOW_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCMRxL = (__IO uint32_t*)((uint32_t)TMR4_OCMRx(TMR4x, u32Ch));
    return READ_REG32(*TMR4_OCMRxL);
}

/**
 * @brief  Set the TMR4 OCO low channel mode
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 OCO channel.
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_CH_UL:   TMR4 OCO channel - UL
 *           @arg TMR4_OCO_CH_VL:   TMR4 OCO channel - VL
 *           @arg TMR4_OCO_CH_WL:   TMR4 OCO channel - WL
 * @param  [in] pstcMode            Pointer to a @ref stc_oco_low_ch_compare_mode_t structure of the TMR4 OCO low channel mode
 * @retval An en_result_t enumeration value:
 *           - Ok: Set successfully
 *           - ErrorInvalidParameter: pstcMode is NULL
 * @note   The function only can set low channel mode:TMR4_OCO_CH_xL(x = U/V/W)
 */
en_result_t TMR4_OCO_SetLowChCompareMode(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_oco_low_ch_compare_mode_t *pstcMode)
{
    __IO uint32_t *TMR4_OCMRxL;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check pointer */
    if (NULL != pstcMode)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
        DDL_ASSERT(IS_TMR4_OCO_LOW_CH(u32Ch));

        /* Get pointer of current channel OCO register address */
        TMR4_OCMRxL = (__IO uint32_t*)((uint32_t)TMR4_OCMRx(TMR4x, u32Ch));

        WRITE_REG32(*TMR4_OCMRxL, pstcMode->OCMRx);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Global_Functions TMR4 PWM Global Functions
 * @{
 */

/**
 * @brief  Initialize TMR4 PWM
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @param  [in] pstcPwmInit         Pointer to a @ref stc_tmr4_pwm_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcPwmInit is NULL
 */
en_result_t TMR4_PWM_Init(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            const stc_tmr4_pwm_init_t *pstcPwmInit)
{
    uint16_t u16Value;
    uint32_t u32PSCRValue;
    uint32_t u32PSCRMask;
    __IO uint16_t *TMR4_POCR;
    __IO uint16_t *TMR4_RCSR;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcPwmInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
        DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
        DDL_ASSERT(IS_TMR4_PWM_MD(pstcPwmInit->u16Mode));
        DDL_ASSERT(IS_TMR4_PWM_CLK_DIV(pstcPwmInit->u16ClockDiv));
        DDL_ASSERT(IS_TMR4_PWM_POLARITY(pstcPwmInit->u16Polarity));
        DDL_ASSERT(IS_TMR4_PWM_PORT_MODE(pstcPwmInit->u32OXHPortOutMode));
        DDL_ASSERT(IS_TMR4_PWM_PORT_MODE(pstcPwmInit->u32OXLPortOutMode));
        DDL_ASSERT(IS_TMR4_PWM_ABNORMAL_POLARITY(pstcPwmInit->u32OXHAbnormalPolarity));
        DDL_ASSERT(IS_TMR4_PWM_ABNORMAL_POLARITY(pstcPwmInit->u32OXLAbnormalPolarity));

        /* Get pointer of current channel PWM register address */
        TMR4_POCR = TMR4_POCRx(TMR4x, u32Ch);
        TMR4_RCSR = TMR4_RCSRx(TMR4x);

        /* Set POCR register */
        u16Value = (pstcPwmInit->u16Mode | \
                    pstcPwmInit->u16ClockDiv | \
                    pstcPwmInit->u16Polarity);
        WRITE_REG16(*TMR4_POCR, u16Value);

        /* Set RCSR register */
        u16Value = (TMR4_RCSR_RTSx_MASK(u32Ch) | \
                    TMR4_RCSR_RTIDx_MASK(u32Ch) | \
                    TMR4_RCSR_RTICx_MASK(u32Ch));
        MODIFY_REG16(*TMR4_RCSR, TMR4_RCSR_RTEx_MASK(u32Ch), u16Value);

        /* Set PSCR register: PWM port state */
        u32PSCRMask = (((TMR4_PSCR_OEUH | TMR4_PSCR_OEUL) << (u32Ch * 2UL)) | \
                       ((TMR4_PSCR_OSUH | TMR4_PSCR_OSUL) << (u32Ch * 4UL)));
        u32PSCRValue = ((pstcPwmInit->u32OXHPortOutMode << (u32Ch * 2UL)) | \
                        (pstcPwmInit->u32OXLPortOutMode << ((u32Ch * 2UL) + 1UL)) | \
                        (pstcPwmInit->u32OXHAbnormalPolarity << ((u32Ch * 4UL) + TMR4_PSCR_OSUH_POS)) | \
                        (pstcPwmInit->u32OXLAbnormalPolarity << ((u32Ch * 4UL) + TMR4_PSCR_OSUL_POS)));
        MODIFY_REG32(TMR4x->PSCR, u32PSCRMask, u32PSCRValue);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr4_pwm_init_t to default values
 * @param  [out] pstcPwmInit        Pointer to a @ref stc_tmr4_pwm_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcPwmInit is NULL
 */
en_result_t TMR4_PWM_StructInit(stc_tmr4_pwm_init_t *pstcPwmInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcPwmInit)
    {
        pstcPwmInit->u16Mode = TMR4_PWM_MD_THROUGH;
        pstcPwmInit->u16ClockDiv = TMR4_PWM_CLK_DIV1;
        pstcPwmInit->u16Polarity = TMR4_PWM_OXH_HOLD_OXL_HOLD;
        pstcPwmInit->u32OXHPortOutMode = TMR4_PWM_PORT_OUTPUT_OS;
        pstcPwmInit->u32OXLPortOutMode = TMR4_PWM_PORT_OUTPUT_OS;
        pstcPwmInit->u32OXHAbnormalPolarity = TMR4_PWM_ABNORMAL_POLARITY_NORMAL;
        pstcPwmInit->u32OXLAbnormalPolarity = TMR4_PWM_ABNORMAL_POLARITY_NORMAL;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initialize TMR4 PWM
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @retval None
 */
void TMR4_PWM_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *TMR4_POCR;
    __IO uint16_t *TMR4_RCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));

    /* Get pointer of current channel PWM register address */
    TMR4_POCR = TMR4_POCRx(TMR4x, u32Ch);
    TMR4_RCSR = TMR4_RCSRx(TMR4x);

    /* Set POCR register */
    WRITE_REG16(*TMR4_POCR, (TMR4_PWM_CLK_DIV1 | \
                             TMR4_PWM_MD_THROUGH | \
                             TMR4_PWM_OXH_HOLD_OXL_HOLD));

    /* Set RCSR register */
    MODIFY_REG16(*TMR4_RCSR,
                  TMR4_RCSR_RTEx_MASK(u32Ch), \
                  (TMR4_RCSR_RTIDx_MASK(u32Ch) | \
                   TMR4_RCSR_RTSx_MASK(u32Ch) | \
                   TMR4_RCSR_RTICx_MASK(u32Ch)));
}

/**
 * @brief  Set TMR4 PWM clock division
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @param  [in] u16Div              TMR4 PWM PCLK clock division
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CLK_DIV1:   PCLK
 *           @arg TMR4_PWM_CLK_DIV2:   PCLK/2
 *           @arg TMR4_PWM_CLK_DIV4:   PCLK/4
 *           @arg TMR4_PWM_CLK_DIV8:   PCLK/8
 *           @arg TMR4_PWM_CLK_DIV16:  PCLK/16
 *           @arg TMR4_PWM_CLK_DIV32:  PCLK/32
 *           @arg TMR4_PWM_CLK_DIV64:  PCLK/64
 *           @arg TMR4_PWM_CLK_DIV128: PCLK/128
 * @retval None
 * @note   The PCLK division function is valid when clock source is PCLK
 */
void TMR4_PWM_SetClockDiv(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Div)
{
    __IO uint16_t *TMR4_POCR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_PWM_CLK_DIV(u16Div));

    /* Get pointer of current channel PWM register address */
    TMR4_POCR = TMR4_POCRx(TMR4x, u32Ch);

    MODIFY_REG16(*TMR4_POCR, TMR4_POCR_DIVCK, u16Div);
}

/**
 * @brief  Set TMR4 PWM output polarity.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @param  [in] u16Polarity         TMR4 PWM output polarity
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_OXH_HOLD_OXL_HOLD:     Output PWML and PWMH signals without changing the level
 *           @arg TMR4_PWM_OXH_INVERT_OXL_INVERT: Output both PWML and PWMH signals reversed
 *           @arg TMR4_PWM_OXH_INVERT_OXL_HOLD:   Output the PWMH signal reversed, outputs the PWML signal without changing the level
 *           @arg TMR4_PWM_OXH_HOLD_OXL_INVERT:   Output the PWMH signal without changing the level, Outputs the PWML signal reversed
 * @retval None
 */
void TMR4_PWM_SetPolarity(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            uint16_t u16Polarity)
{
    __IO uint16_t *TMR4_POCR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_PWM_POLARITY(u16Polarity));

    /* Get pointer of current channel PWM register address */
    TMR4_POCR = TMR4_POCRx(TMR4x, u32Ch);

    MODIFY_REG16(*TMR4_POCR, TMR4_POCR_LVLS, u16Polarity);
}

/**
 * @brief TMR4 PWM port output polarity when below conditions occur:1.EMB 2.MOE=0 3.MOE=1&OExy=0
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32PwmPort          TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_PORT_OUH: TMR4 PWM port - TIM4_<t>_OUH
 *           @arg TMR4_PWM_PORT_OUL: TMR4 PWM port - TIM4_<t>_OUL
 *           @arg TMR4_PWM_PORT_OVH: TMR4 PWM port - TIM4_<t>_OVH
 *           @arg TMR4_PWM_PORT_OVL: TMR4 PWM port - TIM4_<t>_OVL
 *           @arg TMR4_PWM_PORT_OWH: TMR4 PWM port - TIM4_<t>_OWH
 *           @arg TMR4_PWM_PORT_OWL: TMR4 PWM port - TIM4_<t>_OWL
 * @param  [in] u32Polarity         TMR4 PWM output polarity
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_ABNORMAL_POLARITY_NORMAL: TIM4_<t>_Oxy(x=U/V/W, y=H/L) output normal
 *           @arg TMR4_PWM_ABNORMAL_POLARITY_HIZ: TIM4_<t>_Oxy(x=U/V/W, y=H/L) output Hi-z
 *           @arg TMR4_PWM_ABNORMAL_POLARITY_LOW: TIM4_<t>_Oxy(x=U/V/W, y=H/L) output low level
 *           @arg TMR4_PWM_ABNORMAL_POLARITY_HIGH: TIM4_<t>_Oxy(x=U/V/W, y=H/L) output high level
 * @retval None
 */
void TMR4_PWM_SetAbnormalPolarity(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32PwmPort,
                                    uint32_t u32Polarity)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_PORT(u32PwmPort));
    DDL_ASSERT(IS_TMR4_PWM_ABNORMAL_POLARITY(u32Polarity));

    MODIFY_REG32(TMR4x->PSCR, \
                 TMR4_PSCR_OSxy_MASK(u32PwmPort), \
                 TMR4_PSCR_OSxy(u32PwmPort, u32Polarity));
}

/**
 * @brief  Start TMR4 PWM reload-timer
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @retval None
 */
void TMR4_PWM_StartReloadTimer(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));

    SET_REG16_BIT(TMR4x->RCSR, TMR4_RCSR_RTEx_MASK(u32Ch));
}

/**
 * @brief  Stop TMR4 PWM reload-timer
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @retval None
 */
void TMR4_PWM_StopReloadTimer(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));

    SET_REG16_BIT(TMR4x->RCSR, TMR4_RCSR_RTSx_MASK(u32Ch));
}

/**
 * @brief  Enable or disable the TMR4 PWM interrupt function.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the TMR4 PWM interrupt function.
 *           @arg Disable:          Disable the TMR4 PWM interrupt function.
 * @retval None
 */
void TMR4_PWM_IntCmd(CM_TMR4_TypeDef *TMR4x,
                        uint32_t u32Ch,
                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        CLEAR_REG16_BIT(TMR4x->RCSR, TMR4_RCSR_RTIDx_MASK(u32Ch));
    }
    else
    {
        SET_REG16_BIT(TMR4x->RCSR, TMR4_RCSR_RTIDx_MASK(u32Ch));
    }
}

/**
 * @brief  Get PWM reload-timer interrupt flag
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @retval An en_flag_status_t enumeration value:
 *           - Set:   PWM reload-timer flag is set.
 *           - Reset: PWM reload-timer flag is reset.
 */
en_flag_status_t TMR4_PWM_GetStatus(const CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch)
{
    __I uint16_t *TMR4_RCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));

    /* Get pointer of current channel PWM register address */
    TMR4_RCSR = TMR4_RCSRx(TMR4x);

    return ((READ_REG16_BIT(*TMR4_RCSR, TMR4_RCSR_RTIFx_MASK(u32Ch)) == 0U) ? Reset : Set);
}

/**
 * @brief  Clear PWM reload-timer interrupt flag
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @retval None
 */
void TMR4_PWM_ClearStatus(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));

    SET_REG16_BIT(TMR4x->RCSR, TMR4_RCSR_RTICx_MASK(u32Ch));
}

/**
 * @brief Set TMR4 PWM reister TMR4_PSCR.OE bit effect time
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Time             Effect time
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_OE_EFFECT_IMMED: TMR4 PWM reister TMR4_PSCR.OE bit immediate effect immediate
 *           @arg TMR4_PWM_OE_EFFECT_CNT_UDF: TMR4 PWM reister TMR4_PSCR.OE bit effect when TMR4 counter underflow
 *           @arg TMR4_PWM_OE_EFFECT_CNT_OVF: TMR4 PWM reister TMR4_PSCR.OE bit effect when TMR4 counter overflow
 * @retval None
 */
void TMR4_PWM_SetOEEffectTime(CM_TMR4_TypeDef *TMR4x, uint32_t u32Time)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_OE_EFFECT(u32Time));

    MODIFY_REG32(TMR4x->PSCR, TMR4_PSCR_ODT, u32Time);
}

/**
 * @brief Set the TMR4 PWM EMB release mode.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Mode             The function new state
 *           @arg TMR4_PWM_EMB_RELEASE_MD_SW_MOE: The MOE bit can only be set to 1 by software to restore the PWM normal output.
 *           @arg TMR4_PWM_EMB_RELEASE_MD_HW_MOE: The MOE bit is automatically set to 1 by hardware to restore the PWM normal output.
 * @retval None
 */
void TMR4_PWM_SetEmbReleaseMode(CM_TMR4_TypeDef *TMR4x, uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_EMB_RELEASE_MD(u32Mode));

    MODIFY_REG32(TMR4x->PSCR, TMR4_PSCR_AOE, u32Mode);
}

/**
 * @brief Enable or disable the TMR4 PWM master output function.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the TMR4 PWM master output function.
 *           @arg Disable:          Disable the TMR4 PWM master output function.
 * @retval None
 */
void TMR4_PWM_MasterOutputCmd(CM_TMR4_TypeDef *TMR4x,
                                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_MOE);
    }
    else
    {
        CLEAR_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_MOE);
    }
}

/**
 * @brief  Set TMR4 PWM port output mode
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32PwmPort          TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_PORT_OUH: TMR4 PWM port - TIM4_<t>_OUH
 *           @arg TMR4_PWM_PORT_OUL: TMR4 PWM port - TIM4_<t>_OUL
 *           @arg TMR4_PWM_PORT_OVH: TMR4 PWM port - TIM4_<t>_OVH
 *           @arg TMR4_PWM_PORT_OVL: TMR4 PWM port - TIM4_<t>_OVL
 *           @arg TMR4_PWM_PORT_OWH: TMR4 PWM port - TIM4_<t>_OWH
 *           @arg TMR4_PWM_PORT_OWL: TMR4 PWM port - TIM4_<t>_OWL
 * @param  [in] u32Mode             The PWM port output mode
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_PORT_OUTPUT_OS: TIM4_<t>_Oxy(x=U/V/W,y=H/L) output polarity by specified OSxy
 *           @arg TMR4_PWM_PORT_OUTPUT_NORMAL: TIM4_<t>_Oxy(x=U/V/W,y=H/L) output normal PWM
 * @retval None
 */
void TMR4_PWM_SetPortOutputMode(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32PwmPort,
                                uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_PORT(u32PwmPort));
    DDL_ASSERT(IS_TMR4_PWM_PORT_MODE(u32Mode));

    MODIFY_REG32(TMR4x->PSCR, \
                 TMR4_PSCR_OExy_MASK(u32PwmPort), \
                 TMR4_PSCR_OExy(u32PwmPort, u32Mode));
}

/**
 * @brief  Set TMR4 PWM filter count value
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @param  [in] u16Value            TMR4 PWM filter count value
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_PWM_SetFilterCountValue(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16Value)
{
    __IO uint16_t *TMR4_PFSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));

    /* Get pointer of current channel PWM register address */
    TMR4_PFSR = TMR4_PFSRx(TMR4x, u32Ch);

    WRITE_REG16(*TMR4_PFSR, u16Value);
}

/**
 * @brief  Set TMR4 PWM dead time count
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @param  [in] u32DeadTimeIndex    TMR4 PWM dead time register index
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_PDAR_IDX: TMR4_PDARn(n=U/V/W)
 *           @arg TMR4_PWM_PDBR_IDX: TMR4_PDBRn(n=U/V/W)
 * @param  [in] u16Value            TMR4 PWM dead time register value
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_PWM_SetDeadTimeValue(CM_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint32_t u32DeadTimeIndex,
                                        uint16_t u16Value)
{
    __IO uint16_t *TMR4_PDR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_PWM_DEADTIME_REG_IDX(u32DeadTimeIndex));

    /* Get pointer of current channel PWM register address */
    TMR4_PDR = TMR4_PDRx(TMR4x, u32Ch, u32DeadTimeIndex);

    WRITE_REG16(*TMR4_PDR, u16Value);
}

/**
 * @brief  Get TMR4 PWM dead time count
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_CH_U:    TMR4 PWM couple channel - U
 *           @arg TMR4_PWM_CH_V:    TMR4 PWM couple channel - V
 *           @arg TMR4_PWM_CH_W:    TMR4 PWM couple channel - W
 * @param  [in] u32DeadTimeIndex    TMR4 PWM dead time register index
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_PDAR_IDX: TMR4_PDARn(n=U/V/W)
 *           @arg TMR4_PWM_PDBR_IDX: TMR4_PDBRn(n=U/V/W)
 * @retval TMR4 PWM dead time register value
 */
uint16_t TMR4_PWM_GetDeadTimeValue(const CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint32_t u32DeadTimeIndex)
{
    __I uint16_t *TMR4_PDR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_PWM_DEADTIME_REG_IDX(u32DeadTimeIndex));

    /* Get pointer of current channel PWM register address */
    TMR4_PDR = TMR4_PDRx(TMR4x, u32Ch, u32DeadTimeIndex);

    return READ_REG16(*TMR4_PDR);
}

/**
 * @}
 */

/**
 * @defgroup TMR4_SEVT_Global_Functions TMR4 SEVT Global Functions
 * @{
 */

/**
 * @brief  Initialize TMR4 SEVT
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @param  [in] pstcSevtInit        Pointer to a @ref stc_tmr4_sevt_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcSevtInit is NULL
 */
en_result_t TMR4_SEVT_Init(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            const stc_tmr4_sevt_init_t *pstcSevtInit)
{
    uint16_t u16Value;
    __IO uint16_t *TMR4_SCCR;
    __IO uint16_t *TMR4_SCSR;
    __IO uint16_t *TMR4_SCMR;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcSevtInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
        DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));
        DDL_ASSERT(IS_TMR4_SEVT_MD(pstcSevtInit->u16Mode));
        DDL_ASSERT(IS_TMR4_SEVT_OUTPUT_EVT(pstcSevtInit->u16OutputEvent));
        DDL_ASSERT(IS_TMR4_SEVT_CNT_CMP_TYPE(pstcSevtInit->u16CountCompareType));
        DDL_ASSERT(IS_TMR4_SEVT_BUF_COND(pstcSevtInit->u16BufCond));
        DDL_ASSERT(IS_TMR4_SEVT_MASK(pstcSevtInit->u16MaskTimes));
        DDL_ASSERT(IS_TMR4_SEVT_MASK_CMP_TYPE(pstcSevtInit->u16MaskCompareType));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcSevtInit->enBufLinkTransferState));

        /* Get actual address of register list of current channel */
        TMR4_SCCR = TMR4_SCCRx(TMR4x, u32Ch);
        TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);
        TMR4_SCMR = TMR4_SCMRx(TMR4x, u32Ch);

        /* Set SCSR register */
        u16Value = (pstcSevtInit->u16Mode | \
                    pstcSevtInit->u16BufCond | \
                    pstcSevtInit->u16OutputEvent | \
                    pstcSevtInit->u16CountCompareType | \
                    ((Enable == pstcSevtInit->enBufLinkTransferState) ? TMR4_SCSR_LMC : (uint16_t)0U));
        WRITE_REG16(*TMR4_SCSR, u16Value);

        /* Set SCMR register */
        u16Value = (0xFF00U | \
                    pstcSevtInit->u16MaskTimes | \
                    pstcSevtInit->u16MaskCompareType);
        WRITE_REG16(*TMR4_SCMR, u16Value);

        /* Set SCCR register: compare value */
        WRITE_REG16(*TMR4_SCCR, pstcSevtInit->u16CompareValue);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr4_pwm_init_t to default values
 * @param  [out] pstcSevtInit       Pointer to a @ref stc_tmr4_pwm_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcSevtInit is NULL
 */
en_result_t TMR4_SEVT_StructInit(stc_tmr4_sevt_init_t *pstcSevtInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcSevtInit)
    {
        pstcSevtInit->u16Mode = TMR4_SEVT_MD_CMP;
        pstcSevtInit->u16CompareValue = 0U;
        pstcSevtInit->u16OutputEvent = TMR4_SEVT_OUTPUT_EVT0;
        pstcSevtInit->u16CountCompareType = 0U;
        pstcSevtInit->u16BufCond = TMR4_SEVT_BUF_COND_IMMED;
        pstcSevtInit->u16MaskTimes = TMR4_SEVT_MASK0;
        pstcSevtInit->u16MaskCompareType = 0U;
        pstcSevtInit->enBufLinkTransferState = Disable;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initialize TMR4 PWM
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @retval None
 */
void TMR4_SEVT_DeInit(CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *TMR4_SCCR;
    __IO uint16_t *TMR4_SCSR;
    __IO uint16_t *TMR4_SCMR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    TMR4_SCCR = TMR4_SCCRx(TMR4x, u32Ch);
    TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);
    TMR4_SCMR = TMR4_SCMRx(TMR4x, u32Ch);

    /* Configure default parameter */
    WRITE_REG16(*TMR4_SCCR, 0x0U);
    WRITE_REG16(*TMR4_SCSR, 0x0000U);
    WRITE_REG16(*TMR4_SCMR, 0xFF00U);
}

/**
 * @brief  Set TMR4 SEVT delay object
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @param  [in] u16Object           TMR4 SEVT delay object
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_DELAY_OCCRXH: TMR4 SEVT delay object - OCCRxh
 *           @arg TMR4_SEVT_DELAY_OCCRXL: TMR4 SEVT delay object - OCCRxl
 * @retval None
 */
void TMR4_SEVT_SetDelayObject(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Object)
{
    __IO uint16_t *TMR4_SCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_SEVT_DELAY_OBJECT(u16Object));

    /* Get actual address of register list of current channel */
    TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);

    /* Set SCSR register */
    MODIFY_REG16(*TMR4_SCSR, TMR4_SCSR_EVTDS, u16Object);
}

/**
 * @brief  Set TMR4 SEVT trigger event.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @param  [in] u16MaskTimes        Mask times
 *           @arg TMR4_SEVT_MASK0:  Mask 0 times
 *           @arg TMR4_SEVT_MASK1:  Mask 1 times
 *           @arg TMR4_SEVT_MASK2:  Mask 2 times
 *           @arg TMR4_SEVT_MASK3:  Mask 3 times
 *           @arg TMR4_SEVT_MASK4:  Mask 4 times
 *           @arg TMR4_SEVT_MASK5:  Mask 5 times
 *           @arg TMR4_SEVT_MASK6:  Mask 6 times
 *           @arg TMR4_SEVT_MASK7:  Mask 7 times
 *           @arg TMR4_SEVT_MASK8:  Mask 8 times
 *           @arg TMR4_SEVT_MASK9:  Mask 9 times
 *           @arg TMR4_SEVT_MASK10: Mask 10 times
 *           @arg TMR4_SEVT_MASK11: Mask 11 times
 *           @arg TMR4_SEVT_MASK12: Mask 12 times
 *           @arg TMR4_SEVT_MASK13: Mask 13 times
 *           @arg TMR4_SEVT_MASK14: Mask 14 times
 *           @arg TMR4_SEVT_MASK15: Mask 15 times
 * @retval None
 */
void TMR4_SEVT_SetMaskTimes(CM_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            uint16_t u16MaskTimes)
{
    __IO uint16_t *TMR4_SCMR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_SEVT_MASK(u16MaskTimes));

    /* Get actual address of register list of current channel */
    TMR4_SCMR = TMR4_SCMRx(TMR4x, u32Ch);

    /* Set SCMR register */
    MODIFY_REG16(*TMR4_SCMR, TMR4_SCMR_AMC, u16MaskTimes);
}

/**
 * @brief  Get TMR4 SEVT SCCR register value
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_SEVT_MASK0:  Mask 0 times
 *           @arg TMR4_SEVT_MASK1:  Mask 1 times
 *           @arg TMR4_SEVT_MASK2:  Mask 2 times
 *           @arg TMR4_SEVT_MASK3:  Mask 3 times
 *           @arg TMR4_SEVT_MASK4:  Mask 4 times
 *           @arg TMR4_SEVT_MASK5:  Mask 5 times
 *           @arg TMR4_SEVT_MASK6:  Mask 6 times
 *           @arg TMR4_SEVT_MASK7:  Mask 7 times
 *           @arg TMR4_SEVT_MASK8:  Mask 8 times
 *           @arg TMR4_SEVT_MASK9:  Mask 9 times
 *           @arg TMR4_SEVT_MASK10: Mask 10 times
 *           @arg TMR4_SEVT_MASK11: Mask 11 times
 *           @arg TMR4_SEVT_MASK12: Mask 12 times
 *           @arg TMR4_SEVT_MASK13: Mask 13 times
 *           @arg TMR4_SEVT_MASK14: Mask 14 times
 *           @arg TMR4_SEVT_MASK15: Mask 15 times
 */
uint16_t TMR4_SEVT_GetMaskTimes(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __I uint16_t *TMR4_SCMR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    TMR4_SCMR = TMR4_SCMRx(TMR4x, u32Ch);

    return READ_REG16_BIT(*TMR4_SCMR, TMR4_SCMR_AMC);
}

/**
 * @brief  Set TMR4 SEVT compare value
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @param  [in] u16Value            SCCR register value
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_SEVT_SetCompareValue(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Value)
{
    __IO uint16_t *TMR4_SCCR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    TMR4_SCCR = TMR4_SCCRx(TMR4x, u32Ch);

    /* Set SCCR register */
    WRITE_REG16(*TMR4_SCCR, u16Value);
}

/**
 * @brief  Get TMR4 SEVT compare value
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @retval SCCR register value
 */
uint16_t TMR4_SEVT_GetCompareValue(const CM_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __I uint16_t *TMR4_SCCR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    TMR4_SCCR = TMR4_SCCRx(TMR4x, u32Ch);

    return READ_REG16(*TMR4_SCCR);
}

/**
 * @brief  Set TMR4 SEVT output event
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @param  [in] u16Event            TMR4 SEVT output event
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_OUTPUT_EVT0: TMR4 SEVT output special event 0
 *           @arg TMR4_SEVT_OUTPUT_EVT1: TMR4 SEVT output special event 1
 *           @arg TMR4_SEVT_OUTPUT_EVT2: TMR4 SEVT output special event 2
 *           @arg TMR4_SEVT_OUTPUT_EVT3: TMR4 SEVT output special event 3
 *           @arg TMR4_SEVT_OUTPUT_EVT4: TMR4 SEVT output special event 4
 *           @arg TMR4_SEVT_OUTPUT_EVT5: TMR4 SEVT output special event 5
 * @retval None
 */
void TMR4_SEVT_SetOutpuEvent(CM_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Event)
{
    __IO uint16_t *TMR4_SCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_SEVT_OUTPUT_EVT(u16Event));

    /* Get actual address of register list of current channel */
    TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);

    /* Set SCSR register */
    MODIFY_REG16(*TMR4_SCSR, TMR4_SCSR_EVTOS, u16Event);
}

/**
 * @brief  Set TMR4 SEVT event signal output to port
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u16Signal           TMR4 SEVT event signal selection
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_OUTPUT_NONE: Disable output event signal of TMR4 SEVT
 *           @arg TMR4_SEVT_OUTPUT_EVT0_SIGNAL: Output the specified event 0 signal of TMR4 SEVT
 *           @arg TMR4_SEVT_OUTPUT_EVT1_SIGNAL: Output the specified event 1 signal of TMR4 SEVT
 *           @arg TMR4_SEVT_OUTPUT_EVT2_SIGNAL: Output the specified event 2 signal of TMR4 SEVT
 *           @arg TMR4_SEVT_OUTPUT_EVT3_SIGNAL: Output the specified event 3 signal of TMR4 SEVT
 *           @arg TMR4_SEVT_OUTPUT_EVT4_SIGNAL: Output the specified event 4 signal of TMR4 SEVT
 *           @arg TMR4_SEVT_OUTPUT_EVT5_SIGNAL: Output the specified event 5 signal of TMR4 SEVT
 * @retval None
 */
void TMR4_SEVT_SetOutputEventSignal(CM_TMR4_TypeDef *TMR4x, uint16_t u16Signal)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_OUTPUT_SIGNAL(u16Signal));

    MODIFY_REG16(TMR4x->SCER, TMR4_SCER_EVTRS, u16Signal);
}

/**
 * @brief  Set the SCCR&SCMR buffer transfer condition
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @param  [in] u16BufCond         The buffer transfer condition
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_BUF_COND_IMMED: Register SCCR&SCMR buffer transfer when writing to the SCCR&SCMR register
 *           @arg TMR4_SEVT_BUF_COND_UDF: Register SCCR&SCMR buffer transfer when counter underflow occur
 *           @arg TMR4_SEVT_BUF_COND_OVF: Register SCCR&SCMR buffer transfer when counter overflow occur
 *           @arg TMR4_SEVT_BUF_COND_UDFOVF: Register SCCR&SCMR buffer transfer when counter underflow or overflow occur
 * @retval None
 */
void TMR4_SEVT_SetCompareBufCond(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16BufCond)
{
    __IO uint16_t *TMR4_SCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_SEVT_BUF_COND(u16BufCond));

    /* Get actual address of register list of current channel */
    TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);

    MODIFY_REG16(*TMR4_SCSR, TMR4_SCSR_BUFEN, u16BufCond);
}

/**
 * @brief  Enable or disable the specified count compare type of TMR4 SEVT
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @param  [in] u16Type             The specified count compare type of TMR4 SEVT
 *         This parameter can be any composed value of the following values:
 *           @arg TMR4_SEVT_CNT_CMP_UP: Start event operate when match with SCCR&SCMR and TMR4 CNT count up
 *           @arg TMR4_SEVT_CNT_CMP_DOWN: Start event operate when match with SCCR&SCMR and TMR4 CNT count down
 *           @arg TMR4_SEVT_CNT_CMP_ZERO: Start event operate when match with SCCR&SCMR and TMR4 CNT count zero
 *           @arg TMR4_SEVT_CNT_CMP_PEAK: Start event operate when match with SCCR&SCMR and TMR4 CNT count peak
 * @param  [in] enNewState         The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified count compare condition of TMR4 SEVT.
 *           @arg Disable:          Disable the specified count compare condition of TMR4 SEVT.
 * @retval None
 */
void TMR4_SEVT_CountCompareCondCmd(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16Type,
                                    en_functional_state_t enNewState)
{
    __IO uint16_t *TMR4_SCSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_SEVT_CNT_CMP_TYPE(u16Type));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get actual address of register list of current channel */
    TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);

    if (Enable == enNewState)
    {
        SET_REG16_BIT(*TMR4_SCSR, u16Type);
    }
    else
    {
        CLEAR_REG16_BIT(*TMR4_SCSR, u16Type);
    }
}

/**
 * @brief  Enable or disable the specified mask compare type of TMR4 SEVT.
 * @param  [in] TMR4x               Pointer to TMR4 instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMR4:          TMR4 unit instance register base
 * @param  [in] u32Ch               TMR4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_CH_UH:  TMR4 SEVT channel - UH
 *           @arg TMR4_SEVT_CH_UL:  TMR4 SEVT channel - UL
 *           @arg TMR4_SEVT_CH_VH:  TMR4 SEVT channel - VH
 *           @arg TMR4_SEVT_CH_VL:  TMR4 SEVT channel - VL
 *           @arg TMR4_SEVT_CH_WH:  TMR4 SEVT channel - WH
 *           @arg TMR4_SEVT_CH_WL:  TMR4 SEVT channel - WL
 * @param  [in] u16MaskType         The specified mask compare type of TMR4 SEVT
 *         This parameter can be any composed value of the following values:
 *           @arg TMR4_SEVT_MASK_CMP_UDF: Compare with the CNT zero interrupt mask counter
 *           @arg TMR4_SEVT_MASK_CMP_OVF: Compare with the CNT peak interrupt mask counter
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified mask compare type of TMR4 SEVT.
 *           @arg Disable:          Disable the specified mask compare type of TMR4 SEVT.
 * @retval None
 */
void TMR4_SEVT_MaskCompareCmd(CM_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16MaskType,
                                    en_functional_state_t enNewState)
{
    __IO uint16_t *TMR4_SCMR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR4_UNIT(TMR4x));
    DDL_ASSERT(IS_TMR4_SEVT_CH(u32Ch));
    DDL_ASSERT(IS_TMR4_SEVT_MASK_CMP_TYPE(u16MaskType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get actual address of register list of current channel */
    TMR4_SCMR = TMR4_SCMRx(TMR4x, u32Ch);

    if (Enable == enNewState)
    {
        SET_REG16_BIT(*TMR4_SCMR, u16MaskType);
    }
    else
    {
        CLEAR_REG16_BIT(*TMR4_SCMR, u16MaskType);
    }
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
