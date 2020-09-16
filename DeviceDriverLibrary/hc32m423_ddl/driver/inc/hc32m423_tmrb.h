/**
 *******************************************************************************
 * @file  hc32m423_tmrb.h
 * @brief This file contains all the functions prototypes of the TMRB(TimerB)
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
#ifndef __HC32M423_TMRB_H__
#define __HC32M423_TMRB_H__

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
 * @addtogroup DDL_TMRB
 * @{
 */

#if (DDL_TMRB_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMRB_Global_Types TMRB Global Types
 * @{
 */

/**
 * @brief TMRB initialization structure definition
 */
typedef struct
{
    uint16_t u16ClockDiv;               /*!< TMRB Count clock division select.
                                             This parameter can be a value of @ref TMRB_Clock_Division */
    uint16_t u16CountMode;              /*!< TMRB count mode.
                                             This parameter can be a value of @ref TMRB_Count_Mode */
    uint16_t u16CountDir;               /*!< TMRB count direction.
                                             This parameter can be a value of @ref TMRB_Count_Direction */
    uint16_t u16PeriodValue;            /*!< TMRB period value.
                                             This parameter can be a value of half-word */
} stc_tmrb_init_t;

/**
 * @brief TMRB PWM initialization structure definition
 */
typedef struct
{
    uint16_t u16CompareValue;   /*!< TMRB compare value.
                                     This parameter can be a value of half-word */
    uint16_t u16StartPolarity;  /*!< TIMB_<t>_PWMn(t=1,n=1~4) output polarity when start count.
                                     This parameter can be a value of @ref TMRB_PWM_Polarity */
    uint16_t u16StopPolarity;   /*!< TIMB_<t>_PWMn(t=1,n=1~4) output polarity when stop count
                                     This parameter can be a value of @ref TMRB_PWM_Polarity */
    uint16_t u16MatchPolarity;  /*!< TIMB_<t>_PWMn(t=1,n=1~4) output polarity when compare value match
                                     This parameter can be a value of @ref TMRB_PWM_Polarity */
    uint16_t u16PeriodPolarity; /*!< TIMB_<t>_PWMn(t=1,n=1~4) output polarity when period value match
                                     This parameter can be a value of @ref TMRB_PWM_Polarity */
} stc_tmrb_pwm_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMRB_Global_Macros TMRB Global Macros
 * @{
 */

/**
 * @defgroup TMRB_Channel TMRB Channel
 * @note TMRB channel 5&6 don't support PWM
 * @{
 */
#define TMRB_CH1                            (0UL)
#define TMRB_CH2                            (1UL)
#define TMRB_CH3                            (2UL)
#define TMRB_CH4                            (3UL)
#define TMRB_CH5                            (4UL)
#define TMRB_CH6                            (5UL)
/**
 * @}
 */

/**
 * @defgroup TMRB_Function_Mode TMRB Function Mode
 * @{
 */
#define TMRB_FUNC_CMP                       (0x0000U)           /*!< Output comare function */
#define TMRB_FUNC_CAPT                      (TMRB_CCONR_CAPMD)  /*!< Input capture function */
/**
 * @}
 */

/**
 * @defgroup TMRB_Flag TMRB Flag
 * @{
 */
#define TMRB_FLAG_OVF                       (TMRB_BCSTR_OVFF)
#define TMRB_FLAG_UDF                       (TMRB_BCSTR_UDFF)
#define TMRB_FLAG_CMP1                      (TMRB_STFLR_CMPF1)
#define TMRB_FLAG_CMP2                      (TMRB_STFLR_CMPF2)
#define TMRB_FLAG_CMP3                      (TMRB_STFLR_CMPF3)
#define TMRB_FLAG_CMP4                      (TMRB_STFLR_CMPF4)
#define TMRB_FLAG_CMP5                      (TMRB_STFLR_CMPF5)
#define TMRB_FLAG_CMP6                      (TMRB_STFLR_CMPF6)
#define TMRB_FLAG_ALL                       (TMRB_CNT_FLAG_MASK |              \
                                             TMRB_CMP_FLAG_MASK)
/**
 * @}
 */

/**
 * @defgroup TMRB_Interrupt_definition TMRB Interrupts Definition
 * @{
 */
#define TMRB_INT_OVF                        (TMRB_BCSTR_INENOVF)
#define TMRB_INT_UDF                        (TMRB_BCSTR_INENUDF)
#define TMRB_INT_CMP1                       (TMRB_ICONR_ITEN1)
#define TMRB_INT_CMP2                       (TMRB_ICONR_ITEN2)
#define TMRB_INT_CMP3                       (TMRB_ICONR_ITEN3)
#define TMRB_INT_CMP4                       (TMRB_ICONR_ITEN4)
#define TMRB_INT_CMP5                       (TMRB_ICONR_ITEN5)
#define TMRB_INT_CMP6                       (TMRB_ICONR_ITEN6)
#define TMRB_INT_ALL                        (TMRB_CNT_INT_MASK |               \
                                             TMRB_CMP_INT_MASK)
/**
 * @}
 */

/**
 * @defgroup TMRB_Event TMRB Event
 * @{
 */
#define TMRB_EVT_CMP1                       (TMRB_ECONR_ETEN1)
#define TMRB_EVT_CMP2                       (TMRB_ECONR_ETEN2)
#define TMRB_EVT_CMP3                       (TMRB_ECONR_ETEN3)
#define TMRB_EVT_CMP4                       (TMRB_ECONR_ETEN4)
#define TMRB_EVT_CMP5                       (TMRB_ECONR_ETEN5)
#define TMRB_EVT_CMP6                       (TMRB_ECONR_ETEN6)
#define TMRB_EVT_ALL                        (TMRB_EVT_CMP1 |                   \
                                             TMRB_EVT_CMP2 |                   \
                                             TMRB_EVT_CMP3 |                   \
                                             TMRB_EVT_CMP4 |                   \
                                             TMRB_EVT_CMP5 |                   \
                                             TMRB_EVT_CMP6)
/**
 * @}
 */

/**
 * @defgroup TMRB_Count_Mode TMRB Count Mode
 * @{
 */
#define TMRB_MD_SAWTOOTH                    (0x0000U)
#define TMRB_MD_TRIANGLE                    (TMRB_BCSTR_MODE)
/**
 * @}
 */

/**
 * @defgroup TMRB_Count_Direction TMRB Count Direction
 * @{
 */
#define TMRB_DIR_DOWN                       (0x0000U)
#define TMRB_DIR_UP                         (TMRB_BCSTR_DIR)
/**
 * @}
 */

/**
 * @defgroup TMRB_Compare_Buffer_Condition TMRB Compare Buffer Condition
 * @{
 */
#define TMRB_BUF_COND_INVD                  (0x0000U)               /* Don't transfer buffer value */
#define TMRB_BUF_COND_PEAK                  (TMRB_BCONR_BSE0)       /* Transfer buffer value when TMRB count peak */
#define TMRB_BUF_COND_VALLEY                (TMRB_BCONR_BSE1)       /* Transfer buffer value when TMRB count valley */
#define TMRB_BUF_COND_PEAK_VALLEY           (TMRB_BUF_COND_PEAK | \
                                             TMRB_BUF_COND_VALLEY)  /* Transfer buffer value when TMRB count peak or valley */
/**
 * @}
 */

/**
 * @defgroup TMRB_Clock_Division TMRB Clock Division
 * @{
 */
#define TMRB_CLK_DIV1                       (0U << TMRB_BCSTR_CKDIV_POS)    /*!< PCLK      */
#define TMRB_CLK_DIV2                       (1U << TMRB_BCSTR_CKDIV_POS)    /*!< PCLK/2    */
#define TMRB_CLK_DIV4                       (2U << TMRB_BCSTR_CKDIV_POS)    /*!< PCLK/4    */
#define TMRB_CLK_DIV8                       (3U << TMRB_BCSTR_CKDIV_POS)    /*!< PCLK/8    */
#define TMRB_CLK_DIV16                      (4U << TMRB_BCSTR_CKDIV_POS)    /*!< PCLK/16   */
#define TMRB_CLK_DIV32                      (5U << TMRB_BCSTR_CKDIV_POS)    /*!< PCLK/32   */
#define TMRB_CLK_DIV64                      (6U << TMRB_BCSTR_CKDIV_POS)    /*!< PCLK/64   */
#define TMRB_CLK_DIV128                     (7U << TMRB_BCSTR_CKDIV_POS)    /*!< PCLK/128  */
#define TMRB_CLK_DIV256                     (8U << TMRB_BCSTR_CKDIV_POS)    /*!< PCLK/256  */
#define TMRB_CLK_DIV512                     (9U << TMRB_BCSTR_CKDIV_POS)    /*!< PCLK/512  */
#define TMRB_CLK_DIV1024                    (10U << TMRB_BCSTR_CKDIV_POS)   /*!< PCLK/1024 */
/**
 * @}
 */

/**
 * @defgroup TMRB_Hardware_Start_Count_Condition TMRB Hardware Start Count Condition
 * @note TIMB_<t>_PWM1 _<t>_ is unit number,range 1
 * @{
 */
#define TMRB_START_COND_PWM1R               (TMRB_HCONR_HSTA0)  /*!< Start count when detect the rising edge on TIMB_1_PWM1 */
#define TMRB_START_COND_PWM1F               (TMRB_HCONR_HSTA1)  /*!< Start count when detect the falling edge on TIMB_1_PWM1 */
#define TMRB_START_COND_EVT                 (TMRB_HCONR_HSTA2)  /*!< Start count when detect the timer TMRB_HTSSR specified event */
#define TMRB_START_COND_ALL                 (TMRB_START_COND_PWM1R |           \
                                             TMRB_START_COND_PWM1F |           \
                                             TMRB_START_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMRB_Hardware_Stop_Count_Condition TMRB Hardware Stop Count Condition
 * @note TIMB_<t>_PWM1 _<t>_ is unit number,range 1
 * @{
 */
#define TMRB_STOP_COND_PWM1R                (TMRB_HCONR_HSTP0)  /*!< Stop count when detect the rising edge on TIMB_1_PWM1 */
#define TMRB_STOP_COND_PWM1F                (TMRB_HCONR_HSTP1)  /*!< Stop count when detect the falling edge on TIMB_1_PWM1 */
#define TMRB_STOP_COND_EVT                  (TMRB_HCONR_HSTP2)  /*!< Stop count when detect the timer TMRB_HTSSR specified event */
#define TMRB_STOP_COND_ALL                  (TMRB_START_COND_PWM1R |           \
                                             TMRB_START_COND_PWM1F |           \
                                             TMRB_START_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMRB_Hardware_Clear_Count_Condition TMRB Hardware Clear Count Condition
 * @{
 */
#define TMRB_CLR_COND_PWM1R                 (TMRB_HCONR_HCLE0)  /*!< Clear count value when detect the rising edge on TIMB_1_PWM1 */
#define TMRB_CLR_COND_PWM1F                 (TMRB_HCONR_HCLE1)  /*!< Clear count value when detect the falling edge on TIMB_1_PWM1 */
#define TMRB_CLR_COND_EVT                   (TMRB_HCONR_HCLE2)  /*!< Clear count value when detect the timer TMRB_HTSSR specified event */
#define TMRB_CLR_COND_PWM3R                 (TMRB_HCONR_HCLE5)  /*!< Clear count value when detect the rising edge on TIMB_1_PWM3 */
#define TMRB_CLR_COND_PWM3F                 (TMRB_HCONR_HCLE6)  /*!< Clear count value when detect the falling edge on TIMB_1_PWM3 */
#define TMRB_CLR_COND_ALL                   (TMRB_CLR_COND_PWM1R |             \
                                             TMRB_CLR_COND_PWM1F |             \
                                             TMRB_CLR_COND_PWM3R |             \
                                             TMRB_CLR_COND_PWM3F |             \
                                             TMRB_CLR_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMRB_Hardware_Count_Up_Condition TMRB Hardware Count Up Condition
 * @note TIMB_<t>_PWM1 _<t>_ is unit number,range 1
 * @{
 */
#define TMRB_CNT_UP_COND_PWM1R              (TMRB_HCUPR_HCUP8)  /*!< Count up when detect the rising edge on TIMB_1_PWM1 */
#define TMRB_CNT_UP_COND_PWM1F              (TMRB_HCUPR_HCUP9)  /*!< Count up when detect the falling edge on TIMB_1_PWM1 */
#define TMRB_CNT_UP_COND_EVT                (TMRB_HCUPR_HCUP10) /*!< Count up value when detect the timer TMRB_HTSSR specified event */
#define TMRB_CNT_UP_COND_ALL                (TMRB_CNT_UP_COND_PWM1R |          \
                                             TMRB_CNT_UP_COND_PWM1F |          \
                                             TMRB_CNT_UP_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMRB_Hardware_Count_Down_Condition TMRB Hardware Count Down Condition
 * @{
 */
#define TMRB_CNT_DOWN_COND_PWM1R            (TMRB_HCDOR_HCDO8)  /*!< Count down when detect the rising edge on TIMB_1_PWM1 */
#define TMRB_CNT_DOWN_COND_PWM1F            (TMRB_HCDOR_HCDO9)  /*!< Count down when detect the falling edge on TIMB_1_PWM1 */
#define TMRB_CNT_DOWN_COND_EVT              (TMRB_HCDOR_HCDO10) /*!< Count down value when detect the timer TMRB_HTSSR specified event */
#define TMRB_CNT_DOWN_COND_ALL              (TMRB_CNT_DOWN_COND_PWM1R |        \
                                             TMRB_CNT_DOWN_COND_PWM1F |        \
                                             TMRB_CNT_DOWN_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMRB_Hardware_Input_Capture_Condition TMRB Hardware Input Capture Condition
 * @{
 */
#define TMRB_CAPT_COND_PWMR                 (TMRB_CCONR_HICP0)  /*!< Trigger capture when detect the rising edge on TIMB_<t>_PWMn(n=1~4) */
#define TMRB_CAPT_COND_PWMF                 (TMRB_CCONR_HICP1)  /*!< Trigger capture when detect the falling edge on TIMB_<t>_PWMn(n=1~4) */
#define TMRB_CAPT_COND_EVT                  (TMRB_CCONR_HICP2)  /*!< Trigger capture when detect the timer TMRB_HTSSR specified event */
#define TMRB_CAPT_COND_ALL                  (TMRB_CAPT_COND_PWMR |            \
                                             TMRB_CAPT_COND_PWMF |            \
                                             TMRB_CAPT_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMRB_Input_Capture_Noise_Filter_Clock_Division TMRB Input Capture Noise Filter Clock Division
 * @{
 */
#define TMRB_FILTER_CLK_DIV1                (0U)                    /*!< PCLK          */
#define TMRB_FILTER_CLK_DIV4                (TMRB_CCONR_NOFICKCP_0) /*!< PCLK/4        */
#define TMRB_FILTER_CLK_DIV16               (TMRB_CCONR_NOFICKCP_1) /*!< PCLK/16       */
#define TMRB_FILTER_CLK_DIV64               (TMRB_CCONR_NOFIENCP)   /*!< PCLK/64       */
/**
 * @}
 */

/**
 * @defgroup TMRB_PWM_Macros TMRB PWM Macros
 * @{
 */

/**
 * @defgroup TMRB_PWM_Count_State TMRB PWM Count State
 * @{
 */
#define TMRB_PWM_CNT_START                  (TMRB_PCONR_STAC_POS)
#define TMRB_PWM_CNT_STOP                   (TMRB_PCONR_STPC_POS)
#define TMRB_PWM_CNT_MATCH                  (TMRB_PCONR_CMPC_POS)
#define TMRB_PWM_CNT_PERIOD                 (TMRB_PCONR_PERC_POS)
/**
 * @}
 */

/**
 * @defgroup TMRB_PWM_Polarity TMRB PWM Polarity
 * @{
 */
#define TMRB_PWM_LOW                        (0U)    /*!< TIM_<t>_PWMn(t=1,n=1~4) output low level */
#define TMRB_PWM_HIGH                       (1U)    /*!< TIM_<t>_PWMn(t=1,n=1~4) output high level */
#define TMRB_PWM_HOLD                       (2U)    /*!< TIM_<t>_PWMn(t=1,n=1~4) output hold level */
#define TMRB_PWM_INVT                       (3U)    /*!< TIM_<t>_PWMn(t=1,n=1~4) output inverted level */
/**
 * @}
 */

/**
 * @defgroup TMRB_PWM_Force_Output_Polarity TMRB Output Compare Force Output Polarity
 * @{
 */
#define TMRB_PWM_FORCE_INVD                 (0x0000U)           /*!< Invalid */
#define TMRB_PWM_FORCE_LOW                  (TMRB_PCONR_FORC_1) /*!< Force TIM_<t>_PWMn(t=1,n=1~4) output low level */
#define TMRB_PWM_FORCE_HIGH                 (TMRB_PCONR_FORC)   /*!< Force TIM_<t>_PWMn(t=1,n=1~4) force output high level */
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
 * @addtogroup TMRB_Global_Functions
 * @{
 */

en_result_t TMRB_Init(CM_TMRB_TypeDef *TMRBx,
                        const stc_tmrb_init_t *pstcTmrbInit);
en_result_t TMRB_StructInit(stc_tmrb_init_t *pstcTmrbInit);
void TMRB_DeInit(CM_TMRB_TypeDef *TMRBx);
uint16_t TMRB_GetCountValue(const CM_TMRB_TypeDef *TMRBx);
void TMRB_SetCountValue(CM_TMRB_TypeDef *TMRBx, uint16_t u16Value);
uint16_t TMRB_GetPeriodValue(const CM_TMRB_TypeDef *TMRBx);
void TMRB_SetPeriodValue(CM_TMRB_TypeDef *TMRBx, uint16_t u16Value);
uint16_t TMRB_GetCompareValue(const CM_TMRB_TypeDef *TMRBx, uint32_t u32Ch);
void TMRB_SetCompareValue(CM_TMRB_TypeDef *TMRBx,
                                uint32_t u32Ch,
                                uint16_t u16Value);
void TMRB_Start(CM_TMRB_TypeDef *TMRBx);
void TMRB_Stop(CM_TMRB_TypeDef *TMRBx);
en_flag_status_t TMRB_GetStatus(const CM_TMRB_TypeDef *TMRBx, uint16_t u16Flag);
void TMRB_ClearStatus(CM_TMRB_TypeDef *TMRBx, uint16_t u16Flag);
void TMRB_SetClockDiv(CM_TMRB_TypeDef *TMRBx, uint16_t u16Div);
void TMRB_SetCountDir(CM_TMRB_TypeDef *TMRBx, uint16_t u16Dir);
uint16_t TMRB_GetCountDir(const CM_TMRB_TypeDef *TMRBx);
void TMRB_SetCountMode(CM_TMRB_TypeDef *TMRBx, uint16_t u16Mode);
void TMRB_IntCmd(CM_TMRB_TypeDef *TMRBx,
                    uint16_t u16IntType,
                    en_functional_state_t enNewState);
void TMRB_EventCmd(CM_TMRB_TypeDef *TMRBx,
                        uint32_t u32Ch,
                        en_functional_state_t enNewState);
void TMRB_MxEventCmd(CM_TMRB_TypeDef *TMRBx,
                            uint32_t u32MxCh,
                            en_functional_state_t enNewState);
void TMRB_SetFunc(CM_TMRB_TypeDef *TMRBx, uint32_t u32Ch, uint16_t u16Func);
void TMRB_ReloadCmd(CM_TMRB_TypeDef *TMRBx,
                        en_functional_state_t enNewState);
void TMRB_SetTriggerSrc(const CM_TMRB_TypeDef *TMRBx,
                        en_event_src_t enEventSrc);
void TMRB_HWStartCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState);
void TMRB_HWStopCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState);
void TMRB_HWClearCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState);
void TMRB_HWCountUpCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState);
void TMRB_HWCountDownCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState);
void TMRB_HWCaptureCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint32_t u32Ch,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState);
void TMRB_FilterCmd(CM_TMRB_TypeDef *TMRBx,
                    uint32_t u32Ch,
                    en_functional_state_t enNewState);
void TMRB_SetFilterClockDiv(CM_TMRB_TypeDef *TMRBx,
                                    uint32_t u32Ch,
                                    uint16_t u16Div);
void TMRB_CompareBufCmd(CM_TMRB_TypeDef *TMRBx,
                            uint32_t u32Ch,
                            en_functional_state_t enNewState);
 void TMRB_SetCompareBufCond(CM_TMRB_TypeDef *TMRBx,
                                    uint32_t u32Ch,
                                    uint16_t u16BufCond);

/**
 * @addtogroup TMRB_PWM_Global_Functions
 * @{
 */
en_result_t TMRB_PWM_Init(CM_TMRB_TypeDef *TMRBx,
                            uint32_t u32Ch,
                            const stc_tmrb_pwm_init_t *pstcPwmInit);
en_result_t TMRB_PWM_StructInit(stc_tmrb_pwm_init_t *pstcPwmInit);
void TMRB_PWM_DeInit(CM_TMRB_TypeDef *TMRBx, uint32_t u32Ch);
void TMRB_PWM_Cmd(CM_TMRB_TypeDef *TMRBx,
                        uint32_t u32Ch,
                        en_functional_state_t enNewState);
void TMRB_PWM_SetPolarity(CM_TMRB_TypeDef *TMRBx,
                          uint32_t u32Ch,
                          uint16_t u16CountState,
                          uint16_t u16Polarity);
void TMRB_PWM_SetForcePolarity(CM_TMRB_TypeDef *TMRBx,
                          uint32_t u32Ch,
                          uint16_t u16Polarity);

/**
 * @}
 */

/**
 * @}
 */

#endif /* DDL_TMRB_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_TMRB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
