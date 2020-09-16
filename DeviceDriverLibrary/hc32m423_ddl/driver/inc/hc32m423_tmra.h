/**
 *******************************************************************************
 * @file  hc32m423_tmra.h
 * @brief This file contains all the functions prototypes of the TMRA(TimerA)
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
#ifndef __HC32M423_TMRA_H__
#define __HC32M423_TMRA_H__

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
 * @addtogroup DDL_TMRA
 * @{
 */

#if (DDL_TMRA_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMRA_Global_Types TMRA Global Types
 * @{
 */

/**
 * @brief TMRA initialization structure definition
 * @note  'u16ClockDiv', 'u16CountMode' and 'u16CountDir' are only valid when the clock source is PCLK1.
 */
typedef struct
{
    uint16_t u16ClockDiv;               /*!< Specifies the division factor of clock source.
                                             This parameter can be a value of @ref TMRA_Clock_Division */
    uint16_t u16CountMode;              /*!< Specifies the mode of counting.
                                             This parameter can be a value of @ref TMRA_Count_Mode */
    uint16_t u16CountDir;               /*!< Specifies the direction of counting.
                                             This parameter can be a value of @ref TMRA_Count_Direction */
    uint16_t u16PeriodValue;            /*!< Specifies the period value.
                                             This parameter can be a number between 0U and 0xFFFFU */
} stc_tmra_init_t;

/**
 * @brief TMRA output compare initialization structure definition
 */
typedef struct
{
    uint16_t u16CompareValue;           /*!< Specifies the compare value.
                                             This parameter can be a number between 0U and 0xFFFFU */
    uint16_t u16StartPolarity;          /*!< Specifies the polarity when the TMRA start counting.
                                             This parameter can be a value of @ref TMRA_PWM_Polarity */
    uint16_t u16StopPolarity;           /*!< Specifies the polarity when the TMRA stop counting.
                                             This parameter can be a value of @ref TMRA_PWM_Polarity */
    uint16_t u16MatchPolarity;          /*!< Specifies the polarity when the TMRA counting matches the channel compare value.
                                             This parameter can be a value of @ref TMRA_PWM_Polarity */
    uint16_t u16PeriodPolarity;         /*!< Specifies the polarity when the TMRA counting matches the period value.
                                             This parameter can be a value of @ref TMRA_PWM_Polarity */
} stc_tmra_pwm_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMRA_Global_Macros TMRA Global Macros
 * @{
 */

/**
 * @defgroup TMRA_Channel TMRA Channel
 * @note     TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @{
 */
#define TMRA_CH1                                (0UL)   /*!< Channel 1 of TMRA. */
#define TMRA_CH2                                (1UL)   /*!< Channel 2 of TMRA. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Clock_Division TMRA Clock Division
 * @{
 */
#define TMRA_CLK_DIV1                           (0U)                              /*!< The clock source of TMRA is PCLK1.      */
#define TMRA_CLK_DIV2                           (0x01U << TMRA_BCSTR_CKDIV_POS)   /*!< The clock source of TMRA is PCLK1/2.    */
#define TMRA_CLK_DIV4                           (0x02U << TMRA_BCSTR_CKDIV_POS)   /*!< The clock source of TMRA is PCLK1/4.    */
#define TMRA_CLK_DIV8                           (0x03U << TMRA_BCSTR_CKDIV_POS)   /*!< The clock source of TMRA is PCLK1/8.    */
#define TMRA_CLK_DIV16                          (0x04U << TMRA_BCSTR_CKDIV_POS)   /*!< The clock source of TMRA is PCLK1/16.   */
#define TMRA_CLK_DIV32                          (0x05U << TMRA_BCSTR_CKDIV_POS)   /*!< The clock source of TMRA is PCLK1/32.   */
#define TMRA_CLK_DIV64                          (0x06U << TMRA_BCSTR_CKDIV_POS)   /*!< The clock source of TMRA is PCLK1/64.   */
#define TMRA_CLK_DIV128                         (0x07U << TMRA_BCSTR_CKDIV_POS)   /*!< The clock source of TMRA is PCLK1/128.  */
#define TMRA_CLK_DIV256                         (0x08U << TMRA_BCSTR_CKDIV_POS)   /*!< The clock source of TMRA is PCLK1/256.  */
#define TMRA_CLK_DIV512                         (0x09U << TMRA_BCSTR_CKDIV_POS)   /*!< The clock source of TMRA is PCLK1/512.  */
#define TMRA_CLK_DIV1024                        (0x0AU << TMRA_BCSTR_CKDIV_POS)   /*!< The clock source of TMRA is PCLK1/1024. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Mode TMRA Counting Mode
 * @{
 */
#define TMRA_MD_SAWTOOTH                        (0U)                /*!< Count mode is sawtooth wave. */
#define TMRA_MD_TRIANGLE                        (TMRA_BCSTR_MODE)   /*!< Count mode is triangle wave. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Direction TMRA Counting Direction
 * @{
 */
#define TMRA_DIR_DOWN                           (0U)              /*!< TMRA count down. */
#define TMRA_DIR_UP                             (TMRA_BCSTR_DIR)  /*!< TMRA count up.   */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Up_Condition TMRA Count Up Condition
 * @note     PCLK1 is automatically disabled when any of the following conditions take effect.
 * @note     Symmetric units: uint 1 and 2; uint 3 and 4.
 * @note     'TMRA_CNT_UP_COND_CLKAL_CLKBR', 'TMRA_CNT_UP_COND_CLKAL_CLKBF', 'TMRA_CNT_UP_COND_CLKAH_CLKBR',
 *           'TMRA_CNT_UP_COND_CLKAH_CLKBF', 'TMRA_CNT_UP_COND_CLKBH_CLKAR' and 'TMRA_CNT_UP_COND_CLKBH_CLKAF'
 *           are only valid when the TMRA unit is unit3 or unit4.
 * @{
 */
#define TMRA_CNT_UP_COND_CLKAL_CLKBR            (TMRA_HCUPR_HCUP0)    /*!< When CLKA is low, a rising edge is sampled on CLKB, the counter register counts up.   */
#define TMRA_CNT_UP_COND_CLKAL_CLKBF            (TMRA_HCUPR_HCUP1)    /*!< When CLKA is low, a falling edge is sampled on CLKB, the counter register counts up.  */
#define TMRA_CNT_UP_COND_CLKAH_CLKBR            (TMRA_HCUPR_HCUP2)    /*!< When CLKA is high, a rising edge is sampled on CLKB, the counter register counts up.  */
#define TMRA_CNT_UP_COND_CLKAH_CLKBF            (TMRA_HCUPR_HCUP3)    /*!< When CLKA is high, a falling edge is sampled on CLKB, the counter register counts up. */
#define TMRA_CNT_UP_COND_CLKBL_CLKAR            (TMRA_HCUPR_HCUP4)    /*!< When CLKB is low, a rising edge is sampled on CLKA, the counter register counts up.   */
#define TMRA_CNT_UP_COND_CLKBL_CLKAF            (TMRA_HCUPR_HCUP5)    /*!< When CLKB is low, a falling edge is sampled on CLKA, the counter register counts up.  */
#define TMRA_CNT_UP_COND_CLKBH_CLKAR            (TMRA_HCUPR_HCUP6)    /*!< When CLKB is high, a rising edge is sampled on CLKA, the counter register counts up.  */
#define TMRA_CNT_UP_COND_CLKBH_CLKAF            (TMRA_HCUPR_HCUP7)    /*!< When CLKB is high, a falling edge is sampled on CLKA, the counter register counts up. */
#define TMRA_CNT_UP_COND_TRIGR                  (TMRA_HCUPR_HCUP8)    /*!< When a rising edge occurred on TRIG, the counter register counts up.                  */
#define TMRA_CNT_UP_COND_TRIGF                  (TMRA_HCUPR_HCUP9)    /*!< When a falling edge occurred on TRIG, the counter register counts up.                 */
#define TMRA_CNT_UP_COND_EVT                    (TMRA_HCUPR_HCUP10)   /*!< When the event specified by TMRA_HTSSR occurred, the counter register counts up.      */
#define TMRA_CNT_UP_COND_SYM_OVF                (TMRA_HCUPR_HCUP11)   /*!< When the symmetric unit overflow, the counter register counts up.                     */
#define TMRA_CNT_UP_COND_SYM_UDF                (TMRA_HCUPR_HCUP12)   /*!< When the symmetric unit underflow, the counter register counts up.                    */
#define TMRA_CNT_UP_COND_ALL                    (0x1FFFU)
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Down_Condition TMRA Count Down Condition
 * @note     PCLK1 is automatically disabled when any of the following conditions take effect.
 * @note     Symmetric units: uint 1 and 2; uint 3 and 4.
 * @note     'TMRA_CNT_DOWN_COND_CLKAL_CLKBR', 'TMRA_CNT_DOWN_COND_CLKAL_CLKBF', 'TMRA_CNT_DOWN_COND_CLKAH_CLKBR',
 *           'TMRA_CNT_DOWN_COND_CLKAH_CLKBF', 'TMRA_CNT_DOWN_COND_CLKBH_CLKAR' and 'TMRA_CNT_DOWN_COND_CLKBH_CLKAF'
 *           are only valid when the TMRA unit is unit3 or unit4.
 * @{
 */
#define TMRA_CNT_DOWN_COND_CLKAL_CLKBR          (TMRA_HCDOR_HCDO0)    /*!< When CLKA is low, a rising edge is sampled on CLKB, the counter register counts down.   */
#define TMRA_CNT_DOWN_COND_CLKAL_CLKBF          (TMRA_HCDOR_HCDO1)    /*!< When CLKA is low, a falling edge is sampled on CLKB, the counter register counts down.  */
#define TMRA_CNT_DOWN_COND_CLKAH_CLKBR          (TMRA_HCDOR_HCDO2)    /*!< When CLKA is high, a rising edge is sampled on CLKB, the counter register counts down.  */
#define TMRA_CNT_DOWN_COND_CLKAH_CLKBF          (TMRA_HCDOR_HCDO3)    /*!< When CLKA is high, a falling edge is sampled on CLKB, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_CLKBL_CLKAR          (TMRA_HCDOR_HCDO4)    /*!< When CLKB is low, a rising edge is sampled on CLKA, the counter register counts down.   */
#define TMRA_CNT_DOWN_COND_CLKBL_CLKAF          (TMRA_HCDOR_HCDO5)    /*!< When CLKB is low, a falling edge is sampled on CLKA, the counter register counts down.  */
#define TMRA_CNT_DOWN_COND_CLKBH_CLKAR          (TMRA_HCDOR_HCDO6)    /*!< When CLKB is high, a rising edge is sampled on CLKA, the counter register counts down.  */
#define TMRA_CNT_DOWN_COND_CLKBH_CLKAF          (TMRA_HCDOR_HCDO7)    /*!< When CLKB is high, a falling edge is sampled on CLKA, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_TRIGR                (TMRA_HCDOR_HCDO8)    /*!< When a rising edge occurred on TRIG, the counter register counts down.                  */
#define TMRA_CNT_DOWN_COND_TRIGF                (TMRA_HCDOR_HCDO9)    /*!< When a falling edge occurred on TRIG, the counter register counts down.                 */
#define TMRA_CNT_DOWN_COND_EVT                  (TMRA_HCDOR_HCDO10)   /*!< When the event specified by TMRA_HTSSR occurred, the counter register counts down.      */
#define TMRA_CNT_DOWN_COND_SYM_OVF              (TMRA_HCDOR_HCDO11)   /*!< When the symmetric unit overflow, the counter register counts down.                     */
#define TMRA_CNT_DOWN_COND_SYM_UDF              (TMRA_HCDOR_HCDO12)   /*!< When the symmetric unit underflow, the counter register counts down.                    */
#define TMRA_CNT_DOWN_COND_ALL                  (0x1FFFU)
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Count_State TMRA PWM Count State
 * @{
 */
#define TMRA_PWM_CNT_START                      (TMRA_PCONR_STAC_POS)   /*!< The TMRA start counting.                             */
#define TMRA_PWM_CNT_STOP                       (TMRA_PCONR_STPC_POS)   /*!< The TMRA stop counting.                              */
#define TMRA_PWM_CNT_MATCH                      (TMRA_PCONR_CMPC_POS)   /*!< The TMRA counting matches the channel compare value. */
#define TMRA_PWM_CNT_PERIOD                     (TMRA_PCONR_PERC_POS)   /*!< The TMRA counting matches the period value.          */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Polarity TMRA PWM Polarity
 * @note     'TMRA_PWM_INVT' is only valid when the PWM count state is u16MatchPolarity or u16PeriodPolarity.
 * @{
 */
#define TMRA_PWM_LOW                            (0U)                  /*!< PWM output low.                         */
#define TMRA_PWM_HIGH                           (TMRA_PCONR_STAC_0)   /*!< PWM output high.                        */
#define TMRA_PWM_HOLD                           (TMRA_PCONR_STAC_1)   /*!< PWM output hold the current polarity.   */
#define TMRA_PWM_INVT                           (TMRA_PCONR_STAC)     /*!< PWM output invert the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Force_Polarity TMRA PWM Force Polarity
 * @{
 */
#define TMRA_PWM_FORCE_INVD                     (0U)                  /*!< Force polarity is invalid. */
#define TMRA_PWM_FORCE_LOW                      (TMRA_PCONR_FORC_1)   /*!< Force the PWM output low at the beginning of the next cycle. \
                                                                           The beginning of the next cycle: overflow position or underflow position of sawtooth wave; valley position of triangle wave. */
#define TMRA_PWM_FORCE_HIGH                     (TMRA_PCONR_FORC)     /*!< Force the PWM output high at the beginning of the next cycle. \
                                                                           The beginning of the next cycle: overflow position or underflow position of sawtooth wave; valley position of triangle wave. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Buffer_Transfer_Condition TMRA Buffer Transfer Condition
 * @note     The function is only valid when the TMRA unit is unit3 or unit4.
 * @{
 */
#define TMRA_BUF_COND_OVF_UDF_CLR               (0U)                                              /*!< This configuration value applies to non-triangular wave counting mode. \
                                                                                                       When counting overflow or underflow or counting register was cleared, transfer CMPARm(m=2) to CMPARn(n=1). */
#define TMRA_BUF_COND_PEAK                      (TMRA_BCONR_BSE0)                                 /*!< In triangle wave count mode, when count reached peak, transfer CMPARm(m=2) to CMPARn(n=1).                 */
#define TMRA_BUF_COND_VALLEY                    (TMRA_BCONR_BSE1)                                 /*!< In triangle wave count mode, when count reached valley, transfer CMPARm(m=2) to CMPARn(n=1).               */
#define TMRA_BUF_COND_PEAK_VALLEY               ((uint16_t)(TMRA_BCONR_BSE1 | TMRA_BCONR_BSE0))   /*!< In triangle wave count mode, when count reached peak or valley, transfer CMPARm(m=2) to CMPARn(n=1).       */
/**
 * @}
 */

/**
 * @defgroup TMRA_Input_Pin TMRA Input Pin
 * @note     'TMRA_PIN_PWM2' and 'TMRA_PIN_CLKB' are only valid when the TMRA unit is unit3 or unit4.
 * @{
 */
#define TMRA_PIN_PWM1                           (0x0000UL)  /*!< Pin TIMA_<t>_PWM1. */
#define TMRA_PIN_PWM2                           (0x0001UL)  /*!< Pin TIMA_<t>_PWM2. */
#define TMRA_PIN_CLKB                           (0x0100UL)  /*!< Pin TIMA_<t>_CLKB. */
#define TMRA_PIN_CLKA                           (0x0200UL)  /*!< Pin TIMA_<t>_CLKA. */
#define TMRA_PIN_TRIG                           (0x0400UL)  /*!< Pin TIMA_<t>_TRIG. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Filter_Clock_Division TMRA Filter Clock Division
 * @{
 */
#define TMRA_FILTER_CLK_DIV1                    (0U)                      /*!< The filter clock is PCLK/1.  */
#define TMRA_FILTER_CLK_DIV4                    (TMRA_FCONR_NOFICKCB_0)   /*!< The filter clock is PCLK/4.  */
#define TMRA_FILTER_CLK_DIV16                   (TMRA_FCONR_NOFICKCB_1)   /*!< The filter clock is PCLK/16. */
#define TMRA_FILTER_CLK_DIV64                   (TMRA_FCONR_NOFICKCB)     /*!< The filter clock is PCLK/64. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Function_Mode TMRA Function Mode
 * @{
 */
#define TMRA_FUNC_CMP                           (0U)                /*!< The function mode of TMRA is comparison ouput. */
#define TMRA_FUNC_CAPT                          (TMRA_CCONR_CAPMD)  /*!< The function mode of TMRA is capture the input. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Input_Capture_Condition TMRA Input Capture Condition
 * @{
 */
#define TMRA_CAPT_COND_PWMR                     (TMRA_CCONR_HICP0)  /*!< The condition of capture is a rising edge is sampled on pin TIMA_<t>_PWMn.  */
#define TMRA_CAPT_COND_PWMF                     (TMRA_CCONR_HICP1)  /*!< The condition of capture is a falling edge is sampled on pin TIMA_<t>_PWMn. */
#define TMRA_CAPT_COND_EVT                      (TMRA_CCONR_HICP2)  /*!< The condition of capture is the specified event occurred.                   */
#define TMRA_CAPT_COND_ALL                      ((uint16_t)(TMRA_CCONR_HICP2 | TMRA_CCONR_HICP1 | TMRA_CCONR_HICP0))
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Start_Condition TMRA Hardware Start Condition
 * @{
 */
#define TMRA_START_COND_TRIGR                   (TMRA_HCONR_HSTA0)  /*!< The condition is that a rising edge is sampled on TRIG of the current TMRA unit.   */
#define TMRA_START_COND_TRIGF                   (TMRA_HCONR_HSTA1)  /*!< The condition is that a falling edge is sampled on TRIG of the current TMRA unit.  */
#define TMRA_START_COND_EVT                     (TMRA_HCONR_HSTA2)  /*!< The condition is that the event which is set in register TMRA_HTSSR0 has occurred. */
#define TMRA_START_COND_ALL                     ((uint16_t)(TMRA_HCONR_HSTA2 | TMRA_HCONR_HSTA1 | TMRA_HCONR_HSTA0))
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Stop_Condition TMRA Hardware Stop Condition
 * @{
 */
#define TMRA_STOP_COND_TRIGR                    (TMRA_HCONR_HSTP0)  /*!< The condition is that a rising edge is sampled on pin TRIG of the current TMRA unit.  */
#define TMRA_STOP_COND_TRIGF                    (TMRA_HCONR_HSTP1)  /*!< The condition is that a falling edge is sampled on pin TRIG of the current TMRA unit. */
#define TMRA_STOP_COND_EVT                      (TMRA_HCONR_HSTP2)  /*!< The condition is that the event which is set in register TMRA_HTSSR0 has occurred.    */
#define TMRA_STOP_COND_ALL                      ((uint16_t)(TMRA_HCONR_HSTP2 | TMRA_HCONR_HSTP1 | TMRA_HCONR_HSTP0))
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Clear_Condition TMRA Hardware Clear Condition
 * @note     Symmetric units: uint 1 and 2; uint 3 and 4.
 * @{
 */
#define TMRA_CLR_COND_TRIGR                     (TMRA_HCONR_HCLE0)  /*!< The condition is that a rising edge is sampled on TRIG of the current TMRA unit.   */
#define TMRA_CLR_COND_TRIGF                     (TMRA_HCONR_HCLE1)  /*!< The condition is that a falling edge is sampled on TRIG of the current TMRA unit.  */
#define TMRA_CLR_COND_EVT                       (TMRA_HCONR_HCLE2)  /*!< The condition is that the event which is set in register TMRA_HTSSR0 has occurred. */
#define TMRA_CLR_COND_SYM_TRIGR                 (TMRA_HCONR_HCLE3)  /*!< The condition is that a rising edge is sampled on TRIG of the symmetric unit.      */
#define TMRA_CLR_COND_SYM_TRIGF                 (TMRA_HCONR_HCLE4)  /*!< The condition is that a falling edge is sampled on TRIG of the symmetric unit.     */
#define TMRA_CLR_COND_ALL                       ((uint16_t)(TMRA_HCONR_HCLE4 | TMRA_HCONR_HCLE3 | TMRA_HCONR_HCLE2 | \
                                                 TMRA_HCONR_HCLE1 | TMRA_HCONR_HCLE0))
/**
 * @}
 */

/**
 * @defgroup TMRA_Flag TMRA Flag
 * @note     'TMRA_FLAG_CMP2' is only valid when the TMRA unit is unit3 or unit4.
 * @{
 */
#define TMRA_FLAG_OVF                           (TMRA_BCSTR_OVFF)   /*!< The flag of counting overflow.                               */
#define TMRA_FLAG_UDF                           (TMRA_BCSTR_UDFF)   /*!< The flag of counting underflow.                              */
#define TMRA_FLAG_CMP1                          (TMRA_STFLR_CMPF1)  /*!< The flag of compare-match or capture completed of channel 1. */
#define TMRA_FLAG_CMP2                          (TMRA_STFLR_CMPF2)  /*!< The flag of compare-match or capture completed of channel 2. */
#define TMRA_FLAG_ALL                           ((uint16_t)(TMRA_BCSTR_OVFF | TMRA_BCSTR_UDFF | TMRA_STFLR_CMPF1 | TMRA_STFLR_CMPF2))
/**
 * @}
 */

/**
 * @defgroup TMRA_Interrupt TMRA Interrupt
 * @note     'TMRA_INT_CMP2' is only valid when the TMRA unit is unit3 or unit4.
 * @{
 */
#define TMRA_INT_OVF                            (TMRA_BCSTR_INENOVF)  /*!< The interrupt of counting overflow. */
#define TMRA_INT_UDF                            (TMRA_BCSTR_INENUDF)  /*!< The interrupt of counting underflow. */
#define TMRA_INT_CMP1                           (TMRA_ICONR_ITEN1)    /*!< The interrupt of compare-match or capture completed of channel 1. */
#define TMRA_INT_CMP2                           (TMRA_ICONR_ITEN2)    /*!< The interrupt of compare-match or capture completed of channel 2. */
#define TMRA_INT_ALL                            ((uint16_t)(TMRA_BCSTR_INENOVF | TMRA_BCSTR_INENUDF | TMRA_ICONR_ITEN1 | TMRA_ICONR_ITEN2))
/**
 * @}
 */

/**
 * @defgroup TMRA_Event TMRA Event
 * @note     'TMRA_EVT_CMP2' is only valid when the TMRA unit is unit3 or unit4.
 * @{
 */
#define TMRA_EVT_CMP1                           (TMRA_ECONR_ETEN1)  /*!< The event of compare-match or capture completed of channel 1. */
#define TMRA_EVT_CMP2                           (TMRA_ECONR_ETEN2)  /*!< The event of compare-match or capture completed of channel 2. */
#define TMRA_EVT_ALL                            ((uint16_t)(TMRA_ECONR_ETEN1 | TMRA_ECONR_ETEN2))
/**
 * @}
 */

/**
 * @defgroup TMRA_Event_Usage TMRA Event Usage
 * @{
 */
#define TMRA_EVT_USAGE_CNT                      (0U)  /*!< The specified event is used for counting.  */
#define TMRA_EVT_USAGE_CAPT                     (1U)  /*!< The specified event is used for capturing. */
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
 * @addtogroup TMRA_Global_Functions
 * @{
 */

/* Initialization and configuration TMRA base functions */
void TMRA_DeInit(CM_TMRA_TypeDef *TMRAx);
en_result_t TMRA_Init(CM_TMRA_TypeDef *TMRAx, const stc_tmra_init_t *pstcTmraInit);
en_result_t TMRA_StructInit(stc_tmra_init_t *pstcTmraInit);
void TMRA_SetCountValue(CM_TMRA_TypeDef *TMRAx, uint16_t u16Value);
uint16_t TMRA_GetCountValue(const CM_TMRA_TypeDef *TMRAx);
void TMRA_SetPeriodValue(CM_TMRA_TypeDef *TMRAx, uint16_t u16Value);
uint16_t TMRA_GetPeriodValue(const CM_TMRA_TypeDef *TMRAx);
void TMRA_SetCompareValue(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Value);
uint16_t TMRA_GetCompareValue(const CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch);
void TMRA_SetClockDiv(CM_TMRA_TypeDef *TMRAx, uint16_t u16Div);
void TMRA_SetCountDir(CM_TMRA_TypeDef *TMRAx, uint16_t u16Dir);
uint16_t TMRA_GetCountDir(const CM_TMRA_TypeDef *TMRAx);
void TMRA_SetCountMode(CM_TMRA_TypeDef *TMRAx, uint16_t u16Mode);
void TMRA_ReloadCmd(CM_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState);
void TMRA_SyncStartCmd(CM_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState);
void TMRA_Start(CM_TMRA_TypeDef *TMRAx);
void TMRA_Stop(CM_TMRA_TypeDef *TMRAx);

void TMRA_HWCountUpCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState);
void TMRA_HWCountDownCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState);
void TMRA_HWStartCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState);
void TMRA_HWStopCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState);
void TMRA_HWClearCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState);

void TMRA_SetFunc(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Func);
void TMRA_HWCaptureCondCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Cond, en_functional_state_t enNewState);
void TMRA_SetFilterClockDiv(CM_TMRA_TypeDef *TMRAx, uint32_t u32Pin, uint16_t u16Div);
void TMRA_FilterCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Pin, en_functional_state_t enNewState);

void TMRA_SetCompareBufCond(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond);
void TMRA_CompareBufCmd(CM_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState);

/* Initialization and configuration TMRA PWM functions */
void TMRA_PWM_DeInit(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch);
en_result_t TMRA_PWM_Init(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, const stc_tmra_pwm_init_t *pstcPwmInit);
en_result_t TMRA_PWM_StructInit(stc_tmra_pwm_init_t *pstcPwmInit);
void TMRA_PWM_SetPolarity(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16CountState, uint16_t u16Polarity);
void TMRA_PWM_SetForcePolarity(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Polarity);
void TMRA_PWM_Cmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, en_functional_state_t enNewState);

/* Interrupts, Events and flags management functions */
void TMRA_SetTriggerSrc(uint8_t u8EventUsage, en_event_src_t enEventSrc);
void TMRA_EventCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, en_functional_state_t enNewState);
void TMRA_MxEventCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16MxCh, en_functional_state_t enNewState);
void TMRA_IntCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16IntType, en_functional_state_t enNewState);
en_flag_status_t TMRA_GetStatus(const CM_TMRA_TypeDef *TMRAx, uint16_t u16Flag);
void TMRA_ClearStatus(CM_TMRA_TypeDef *TMRAx, uint16_t u16Flag);

/**
 * @}
 */

#endif /* DDL_TMRA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_TMRA_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
