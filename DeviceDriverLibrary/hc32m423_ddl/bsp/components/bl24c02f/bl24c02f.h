/**
 *******************************************************************************
 * @file  bl24c02f.h
 * @brief This file provides firmware functions to BL24C02F E2PROM.
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
#ifndef __BL24C02F_H__
#define __BL24C02F_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/** @addtogroup BL24C02F
  * @{
  */

#if (BSP_BL24C02F_ENABLE == BSP_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroupBL24C02F_Global_Macros BL24C02F Global Macros
 * @{
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
 * @addtogroup BL24C02F_Global_Functions BL24C02F Global Functions
 * @{
 */

en_result_t BL24C02F_Init(void);
en_result_t BL24C02F_ReadBuf(uint8_t u8ReadAddr, uint8_t au8ReadBuf[], uint32_t u32NumByte);
en_result_t BL24C02F_WritePage(uint8_t u8WriteAddr, const uint8_t au8WriteBuf[], uint32_t u32NumByte);
en_result_t BL24C02F_WriteBuf(uint8_t u8WriteAddr, const uint8_t au8WriteBuf[], uint32_t u32NumByte);
en_result_t BL24C02F_WaitReady(void);

/**
 * @}
 */

#endif /* BSP_BL24C02F_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __BL24C02F_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
