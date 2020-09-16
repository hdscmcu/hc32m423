/**
 *******************************************************************************
 * @file  ev_hc32m423_lqfp64.h
 * @brief This file contains all the functions prototypes of the
 *        EV_HC32M423_LQFP64 BSP driver library.
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
#ifndef __EV_HC32M423_LQFP64_H__
#define __EV_HC32M423_LQFP64_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "hc32m423_clk.h"
#include "hc32m423_efm.h"
#include "hc32m423_gpio.h"
#include "hc32m423_i2c.h"
#include "hc32m423_icg.h"
#include "hc32m423_interrupts.h"
#include "hc32m423_pwc.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32M423_LQFP64
 * @{
 */

#if (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32M423_LQFP64_Global_Macros EV_HC32M423_LQFP64 Global Macros
 * @{
 */
/** 
 * @defgroup EV_HC32M423_LQFP64_LED_Sel EV_HC32M423_LQFP64 LED definition
 * @{
 */
#define LED_RED                 (0x01U)
#define LED_GREEN               (0x02U)
#define LED_BLUE                (0x04U)
/**
 * @}
 */

/** 
 * @defgroup EV_HC32M423_LQFP64_KEY_Sel EV_HC32M423_LQFP64 KEY definition
 * @{
 */
#define BSP_KEY_1               (0x00U)
#define BSP_KEY_2               (0x01U)
#define BSP_KEY_3               (0x02U)
#define BSP_KEY_4               (0x03U)
/**
 * @}
 */

/** 
 * @defgroup EV_HC32M423_LQFP64_KEY_MD_Sel EV_HC32M423_LQFP64 KEY work mode definition
 * @{
 */
#define BSP_KEY_MD_GPIO         (0x00U)
#define BSP_KEY_MD_EXTINT       (0x01U)
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
 * @addtogroup EV_HC32M423_LQFP64_Global_Functions
 * @{
 */
void BSP_LED_Init(void);
void BSP_LED_On(uint8_t u8Led);
void BSP_LED_Off(uint8_t u8Led);
void BSP_LED_Toggle(uint8_t u8Led);
void BSP_CLK_Init(void);
void BSP_KEY_Init(uint8_t u8Mode);
en_flag_status_t BSP_KEY_GetStatus(uint32_t u32Key, uint8_t u8Mode);

/**
 * @}
 */

#endif /* BSP_EV_HC32M423_LQFP64 */
/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __EV_HC32M423_LQFP64_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
