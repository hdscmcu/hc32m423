/**
 *******************************************************************************
 * @file  hc32m423_emb.h
 * @brief This file contains all the functions prototypes of the EMB
 *        (Emergency Brake) driver library.
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
#ifndef __HC32M423_EMB_H__
#define __HC32M423_EMB_H__

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
 * @addtogroup DDL_EMB
 * @{
 */

#if (DDL_EMB_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EMB_Global_Types EMB Global Types
 * @{
 */

/**
 * @brief EMB monitor EMB port configuration
 */
typedef struct
{
    uint32_t u32Port;           /*!< Enable or disable EMB detect port in control function
                                     This parameter can be a value of EMB_Portx_Selection(x=0~2) */
    uint32_t u32PortLevel;      /*!< EMB detect port level
                                     This parameter can be a value of EMB_Detect_Portx_Level(x=0~2) */
    uint32_t u32PortFilterDiv;  /*!< EMB port filter division
                                     This parameter can be a value of EMB_Portx_Filter_Clock_Division(x=0~2) */
} stc_emb_monitor_port_t;

/**
 * @brief EMB monitor TMR4 or TMR6 PWM configuration
 */
typedef struct
{
    uint32_t u32Pwm;        /*!< Enable or disable EMB detect TMR4 PWM x channel same phase function
                                 This parameter can be a value of EMB_TMR4_PWM_x_Selection(x=U/V/W) */
    uint32_t u32PwmLevel;   /*!< Detect TMR4 PWM x channel polarity level
                                 This parameter can be a value of EMB_Detect_TMR4_PWM_x_Level(x=U/V/W) */
} stc_emb_monitor_tmr_pwm_t;

/**
 * @brief EMB control TMR4 initialization configuration
 */
typedef struct
{
    uint32_t u32Cmp1;                       /*!< Enable or disable EMB detect CMP1 result function
                                                 This parameter can be a value of @ref EMB_CMP1_Selection */
    uint32_t u32Cmp2;                       /*!< Enable or disable EMB detect CMP2 result function
                                                 This parameter can be a value of @ref EMB_CMP2_Selection */
    uint32_t u32Cmp3;                       /*!< Enable or disable EMB detect CMP3 result function
                                                 This parameter can be a value of @ref EMB_CMP3_Selection */
    uint32_t u32Osc;                        /*!< EMB detect OSC failure function
                                                 This parameter can be a value of @ref EMB_OSC_Stop_Selection */
    stc_emb_monitor_port_t    stcPort0;     /*!< EMB detect port EMBIN1 function
                                                 This parameter details refer @ref stc_emb_monitor_port_t structure */
    stc_emb_monitor_port_t    stcPort1;     /*!< EMB detect port EMBIN1 function
                                                 This parameter details refer @ref stc_emb_monitor_port_t structure */
    stc_emb_monitor_port_t    stcPort2;     /*!< EMB detect port EMBIN1 function
                                                 This parameter details refer @ref stc_emb_monitor_port_t structure */
    stc_emb_monitor_tmr_pwm_t stcTmr4PwmU;  /*!< EMB detect TMR4 PWM function
                                                 This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
    stc_emb_monitor_tmr_pwm_t stcTmr4PwmV;  /*!< EMB detect TMR4 PWM function
                                                 This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
    stc_emb_monitor_tmr_pwm_t stcTmr4PwmW;  /*!< EMB detect TMR4 PWM function
                                                 This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
} stc_emb_tmr4_init_t;

/**
 * @brief EMB control TMRB initialization configuration
 */
typedef struct
{
    uint32_t u32Cmp1;                   /*!< Enable or disable EMB detect CMP1 result function
                                             This parameter can be a value of @ref EMB_CMP1_Selection */
    uint32_t u32Cmp2;                   /*!< Enable or disable EMB detect CMP2 result function
                                             This parameter can be a value of @ref EMB_CMP2_Selection */
    uint32_t u32Cmp3;                   /*!< Enable or disable EMB detect CMP3 result function
                                             This parameter can be a value of @ref EMB_CMP3_Selection */
    uint32_t u32Osc;                    /*!< EMB detect OSC failure function
                                             This parameter can be a value of @ref EMB_OSC_Stop_Selection */
    stc_emb_monitor_port_t stcPort0;    /*!< EMB detect port EMBIN1 function
                                             This parameter details refer @ref stc_emb_monitor_port_t structure */
    stc_emb_monitor_port_t stcPort1;    /*!< EMB detect port EMBIN1 function
                                             This parameter details refer @ref stc_emb_monitor_port_t structure */
    stc_emb_monitor_port_t stcPort2;    /*!< EMB detect port EMBIN1 function
                                             This parameter details refer @ref stc_emb_monitor_port_t structure */
    uint32_t u32EmbPolarity;            /*!< PWM polarity when EMB occur
                                             This parameter can be a value of @ref EMB_Group_TMRB_PWM_Polarity */
} stc_emb_tmrb_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EMB_Global_Macros EMB Global Macros
 * @{
 */

/**
 * @defgroup EMB_CMP1_Selection EMB CMP1 Selection
 * @{
 */
#define EMB_CMP1_DISABLE                    (0UL)
#define EMB_CMP1_ENABLE                     (EMB_CTL_CMPEN_0)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP2_Selection EMB CMP2 Selection
 * @{
 */
#define EMB_CMP2_DISABLE                    (0UL)
#define EMB_CMP2_ENABLE                     (EMB_CTL_CMPEN_1)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP3_Selection EMB CMP3 Selection
 * @{
 */
#define EMB_CMP3_DISABLE                    (0UL)
#define EMB_CMP3_ENABLE                     (EMB_CTL_CMPEN_2)
/**
 * @}
 */

/**
 * @defgroup EMB_OSC_Stop_Selection EMB OSC Stop Selection
 * @{
 */
#define EMB_OSC_DISABLE                     (0UL)
#define EMB_OSC_ENABLE                      (EMB_CTL_OSCSTPEN)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR4_PWM_W_Selection EMB TMR4 PWM W Selection
 * @{
 */
#define EMB_TMR4_PWM_W_DISABLE              (0UL)
#define EMB_TMR4_PWM_W_ENABLE               (EMB_CTL_PWMSEN0)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR4_PWM_V_Selection EMB TMR4 PWM V Selection
 * @{
 */
#define EMB_TMR4_PWM_V_DISABLE              (0UL)
#define EMB_TMR4_PWM_V_ENABLE               (EMB_CTL_PWMSEN1)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR4_PWM_U_Selection EMB TMR4 PWM U Selection
 * @{
 */
#define EMB_TMR4_PWM_U_DISABLE              (0UL)
#define EMB_TMR4_PWM_U_ENABLE               (EMB_CTL_PWMSEN2)
/**
 * @}
 */

/**
 * @defgroup EMB_Port0_Selection EMB Port0 Selection
 * @{
 */
#define EMB_PORT0_DISABLE                   (0UL)
#define EMB_PORT0_ENABLE                    (EMB_CTL_PORTINEN0)
/**
 * @}
 */

/**
 * @defgroup EMB_Port1_Selection EMB Port1 Selection
 * @{
 */
#define EMB_PORT1_DISABLE                   (0UL)
#define EMB_PORT1_ENABLE                    (EMB_CTL_PORTINEN1)
/**
 * @}
 */

/**
 * @defgroup EMB_Port2_Selection EMB Port2 Selection
 * @{
 */
#define EMB_PORT2_DISABLE                   (0UL)
#define EMB_PORT2_ENABLE                    (EMB_CTL_PORTINEN2)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port0_Level EMB Detect Port0 Level
 * @{
 */
#define EMB_DETECT_PORT0_LEVEL_HIGH         (0UL)
#define EMB_DETECT_PORT0_LEVEL_LOW          (EMB_CTL_INVSEL0)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port1_Level EMB Detect Port1 Level
 * @{
 */
#define EMB_DETECT_PORT1_LEVEL_HIGH         (0UL)
#define EMB_DETECT_PORT1_LEVEL_LOW          (EMB_CTL_INVSEL1)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port2_Level EMB Detect Port2 Level
 * @{
 */
#define EMB_DETECT_PORT2_LEVEL_HIGH         (0UL)
#define EMB_DETECT_PORT2_LEVEL_LOW          (EMB_CTL_INVSEL2)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR4_PWM_W_Level EMB Detect TMR4 PWM W Level
 * @{
 */
#define EMB_DETECT_TMR4_PWM_W_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR4_PWM_W_BOTH_HIGH     (EMB_PWMLV_PWMLV_0)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR4_PWM_V_Level EMB Detect TMR4 PWM V Level
 * @{
 */
#define EMB_DETECT_TMR4_PWM_V_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR4_PWM_V_BOTH_HIGH     (EMB_PWMLV_PWMLV_1)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR4_PWM_U_Level EMB Detect TMR4 PWM U Level
 * @{
 */
#define EMB_DETECT_TMR4_PWM_U_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR4_PWM_U_BOTH_HIGH     (EMB_PWMLV_PWMLV_2)
/**
 * @}
 */

/** @defgroup EMB_Port0_Filter_Clock_Division EMB Port0 Filter Clock Division
 * @{
 */
#define EMB_PORT0_FILTER_NONE               (0UL)
#define EMB_PORT0_FILTER_CLK_DIV1           (EMB_CTL_NFEN0)
#define EMB_PORT0_FILTER_CLK_DIV8           (EMB_CTL_NFEN0 | EMB_CTL_NFSEL0_0)
#define EMB_PORT0_FILTER_CLK_DIV32          (EMB_CTL_NFEN0 | EMB_CTL_NFSEL0_1)
#define EMB_PORT0_FILTER_CLK_DIV128         (EMB_CTL_NFEN0 | EMB_CTL_NFSEL0)
/**
 * @}
 */

/** @defgroup EMB_Port1_Filter_Clock_Division EMB Port1 Filter Clock Division
 * @{
 */
#define EMB_PORT1_FILTER_NONE               (0UL)
#define EMB_PORT1_FILTER_CLK_DIV1           (EMB_CTL_NFEN1)
#define EMB_PORT1_FILTER_CLK_DIV8           (EMB_CTL_NFEN1 | EMB_CTL_NFSEL1_0)
#define EMB_PORT1_FILTER_CLK_DIV32          (EMB_CTL_NFEN1 | EMB_CTL_NFSEL1_1)
#define EMB_PORT1_FILTER_CLK_DIV128         (EMB_CTL_NFEN1 | EMB_CTL_NFSEL1)
/**
 * @}
 */

/** @defgroup EMB_Port2_Filter_Clock_Division EMB Port2 Filter Clock Division
 * @{
 */
#define EMB_PORT2_FILTER_NONE               (0UL)
#define EMB_PORT2_FILTER_CLK_DIV1           (EMB_CTL_NFEN2)
#define EMB_PORT2_FILTER_CLK_DIV8           (EMB_CTL_NFEN2 | EMB_CTL_NFSEL2_0)
#define EMB_PORT2_FILTER_CLK_DIV32          (EMB_CTL_NFEN2 | EMB_CTL_NFSEL2_1)
#define EMB_PORT2_FILTER_CLK_DIV128         (EMB_CTL_NFEN2 | EMB_CTL_NFSEL2)
/**
 * @}
 */

/**
 * @defgroup EMB_Flag EMB Flag
 * @{
 */
#define EMB_FLAG_PWMS                       (EMB_STAT_PWMSF)
#define EMB_FLAG_CMP                        (EMB_STAT_CMPF)
#define EMB_FLAG_OSC                        (EMB_STAT_OSF)
#define EMB_FLAG_PORT0                      (EMB_STAT_PORTINF0)
#define EMB_FLAG_PORT1                      (EMB_STAT_PORTINF1)
#define EMB_FLAG_PORT2                      (EMB_STAT_PORTINF2)
#define EMB_STAT_PWMS                       (EMB_STAT_PWMST)
#define EMB_STAT_PORT0                      (EMB_STAT_PORTINST0)
#define EMB_STAT_PORT1                      (EMB_STAT_PORTINST1)
#define EMB_STAT_PORT2                      (EMB_STAT_PORTINST2)
#define EMB_TMR4_STAT_ALL                   (EMB_FLAG_PWMS  |                  \
                                             EMB_FLAG_CMP   |                  \
                                             EMB_FLAG_OSC   |                  \
                                             EMB_FLAG_PORT0 |                  \
                                             EMB_FLAG_PORT1 |                  \
                                             EMB_FLAG_PORT2 |                  \
                                             EMB_STAT_PWMS  |                  \
                                             EMB_STAT_PORT0 |                  \
                                             EMB_STAT_PORT1 |                  \
                                             EMB_STAT_PORT2)
#define EMB_TMRB_STAT_ALL                   (EMB_FLAG_CMP   |                  \
                                             EMB_FLAG_OSC   |                  \
                                             EMB_FLAG_PORT0 |                  \
                                             EMB_FLAG_PORT1 |                  \
                                             EMB_FLAG_PORT2 |                  \
                                             EMB_STAT_PORT0 |                 \
                                             EMB_STAT_PORT1 |                 \
                                             EMB_STAT_PORT2)
/**
 * @}
 */

/**
 * @defgroup EMB_Interrupt EMB Interrupt
 * @{
 */
#define EMB_INT_PWMS                        (EMB_INTEN_PWMSINTEN)
#define EMB_INT_CMP                         (EMB_INTEN_CMPINTEN)
#define EMB_INT_OSC                         (EMB_INTEN_OSINTEN)
#define EMB_INT_PORT0                       (EMB_INTEN_PORTININTEN0)
#define EMB_INT_PORT1                       (EMB_INTEN_PORTININTEN1)
#define EMB_INT_PORT2                       (EMB_INTEN_PORTININTEN2)
#define EMB_TMR4_INT_ALL                    (EMB_INT_PWMS  |                   \
                                             EMB_INT_CMP   |                   \
                                             EMB_INT_OSC   |                   \
                                             EMB_INT_PORT0 |                   \
                                             EMB_INT_PORT1 |                   \
                                             EMB_INT_PORT2)
#define EMB_TMRB_INT_ALL                    (EMB_INT_CMP   |                   \
                                             EMB_INT_OSC   |                   \
                                             EMB_INT_PORT0 |                   \
                                             EMB_INT_PORT1 |                   \
                                             EMB_INT_PORT2)
/**
 * @}
 */

/**
 * @defgroup EMB_Group_TMRB_PWM_Polarity EMB Group1 TMRB PWM Polarity
 * @{
 */
#define EMB_TMRB_PWM_NORMAL                 (0UL)               /*!< TIMB_1_PWMn(n=1~4) output normal */
#define EMB_TMRB_PWM_HIZ                    (EMB_ECSR_EMBVAL_0) /*!< TIMB_1_PWMn(n=1~4) output Hi-z */
#define EMB_TMRB_PWM_LOW                    (EMB_ECSR_EMBVAL_1) /*!< TIMB_1_PWMn(n=1~4) output low level */
#define EMB_TMRB_PWM_HIGH                   (EMB_ECSR_EMBVAL)   /*!< TIMB_1_PWMn(n=1~4) output high level */
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
 * @addtogroup EMB_Global_Functions
 * @{
 */
en_result_t EMB_Tmr4Init(CM_EMB_TypeDef *EMBx,
                            const stc_emb_tmr4_init_t *pstcEmbTmr4Init);
en_result_t EMB_Tmr4StructInit(stc_emb_tmr4_init_t *pstcEmbTmr4Init);
en_result_t EMB_TmrbInit(CM_EMB_TypeDef *EMBx,
                            const stc_emb_tmrb_init_t *pstcEmbTmrbInit);
en_result_t EMB_TmrbStructInit(stc_emb_tmrb_init_t *pstcEmbTmrbInit);
void EMB_DeInit(CM_EMB_TypeDef *EMBx);
void EMB_IntCmd(CM_EMB_TypeDef *EMBx,
                    uint32_t u32IntType,
                    en_functional_state_t enNewState);
void EMB_ClearStatus(CM_EMB_TypeDef *EMBx, uint32_t u32Flag);
en_flag_status_t EMB_GetStatus(const CM_EMB_TypeDef *EMBx, uint32_t u32Flag);
void EMB_SWBrake(CM_EMB_TypeDef *EMBx, en_functional_state_t enNewState);
void EMB_SetTmrbPwmPolarity(CM_EMB_TypeDef *EMBx, uint32_t u32Polarity);
/**
 * @}
 */

#endif /* DDL_EMB_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_EMB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
