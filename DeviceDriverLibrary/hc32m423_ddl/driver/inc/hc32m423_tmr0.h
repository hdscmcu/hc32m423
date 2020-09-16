/**
 *******************************************************************************
 * @file  hc32m423_tmr0.h
 * @brief Head file for TMR0 module.
 *
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
#ifndef __HC32M423_TMR0_H__
#define __HC32M423_TMR0_H__

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
 * @addtogroup DDL_TMR0
 * @{
 */

#if (DDL_TMR0_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR0_Global_Types TMR0 Global Types
 * @{
 */

/**
 * @brief Tmr0 base counter function init structrue definition
 */
typedef struct
{
    uint32_t       u32ClockDiv;     /*!< specifies the TMR0 clock division,
                                         and this parameter can be a value of
                                         @ref TMR0_Clock_Division */

    uint32_t       u32ClockSrc;     /*!< Specifies the TMR0 clock source,
                                         and this parameter can be a value of
                                         @ref TMR0_Clock_Source*/

    uint16_t       u16PeriodValue;  /*!< Specifies the TMR0 compare value
                                         This value can be set 0-0xFFFF */
}stc_tmr0_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR0_Global_Macros TMR0 Global Macros
 * @{
 */

/** @defgroup TMR0_Clock_Division TMR0 clock division
 * @{
 */
#define TMR0_CLK_DIV1              (0UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV2              (1UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV4              (2UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV8              (3UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV16             (4UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV32             (5UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV64             (6UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV128            (7UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV256            (8UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV512            (9UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV1024           (10UL<<TMR0_BCONR_CKDIVA_POS)
/**
 * @}
 */

/**
 * @defgroup TMR0_Channel_Index TMR0 Channel Index
 * @{
 */
#define TMR0_CH_A                  (0U)
#define TMR0_CH_B                  (1U)
/**
 * @}
 */

/** @defgroup TMR0_Clock_Source TMR0 clock source
 * @{
 */
#define TMR0_SYNC_CLK_PCLK         (0x00000000UL)
#define TMR0_SYNC_CLK_HWTRIG       (TMR0_BCONR_SYNCLKA)
/**
 * @}
 */

/** @defgroup TMR0_Function TMR0 Function
 * @{
 */
#define TMR0_FUNC_CMP              (0x00000000UL)
#define TMR0_FUNC_CAPT             (TMR0_BCONR_CAPMDA)
/**
 * @}
 */

/** @defgroup TMR0_HWTrig_Func TMR0 hardware trigger function
 * @{
 */
#define TMR0_START_COND_EVT        (TMR0_BCONR_HSTAA)
#define TMR0_CLR_COND_EVT          (TMR0_BCONR_HCLEA)
#define TMR0_STOP_COND_EVT         (TMR0_BCONR_HSTPA)
/**
 * @}
 */

/**
 * @defgroup TMR0_CAMPAR_FLAG TMR0 Compare Flag
 * @{
 */
#define TMR0_FLAG_CMP_A            (TMR0_STFLR_CMFA)
#define TMR0_FLAG_CMP_B            (TMR0_STFLR_CMFB)
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
 * @addtogroup TMR0_Global_Functions
 * @{
 */

en_result_t TMR0_StructInit(stc_tmr0_init_t* pstcTmr0Init);
en_result_t TMR0_Init(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch, \
                      const stc_tmr0_init_t* pstcTmr0Init);
en_flag_status_t TMR0_GetStatus(const CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch);

void TMR0_DeInit(CM_TMR0_TypeDef* TMR0x);
void TMR0_Start(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch);
void TMR0_Stop(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch);
void TMR0_IntCmd(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch, \
                 en_functional_state_t enNewState);
void TMR0_ClearStatus(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch);
void TMR0_SetCountValue(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch, uint16_t u16Value);
void TMR0_SetCompareValue(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch, uint16_t u16Value);
void TMR0_SetTriggerSrc(const CM_TMR0_TypeDef* TMR0x, en_event_src_t enEvent);
void TMR0_SetClockSrc(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Src);
void TMR0_SetClockDiv(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Div);
void TMR0_HWCaptureCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, \
                           en_functional_state_t enNewState);
void TMR0_HWStartCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, \
                         en_functional_state_t enNewState);
void TMR0_HWStopCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, \
                        en_functional_state_t enNewState);
void TMR0_HWClearCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, \
                         en_functional_state_t enNewState);
void TMR0_SetFunc(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Func);

uint16_t TMR0_GetCompareValue(const CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch);
uint16_t TMR0_GetCountValue(const CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch);
/**
 * @}
 */

#endif /* DDL_TMR0_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_TMR0_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
