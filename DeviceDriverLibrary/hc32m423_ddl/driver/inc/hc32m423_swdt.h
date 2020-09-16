/**
 *******************************************************************************
 * @file  hc32m423_swdt.h
 * @brief This file contains all the functions prototypes of the SWDT driver
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
#ifndef __HC32M423_SWDT_H__
#define __HC32M423_SWDT_H__

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
 * @addtogroup DDL_SWDT
 * @{
 */

#if (DDL_SWDT_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SWDT_Global_Macros SWDT Global Macros
 * @{
 */

/**
 * @defgroup SWDT_Flag SWDT Flag
 * @{
 */
#define SWDT_FLAG_UDF                           (SWDT_SR_UDF)     /*!< Count underflow flag */
#define SWDT_FLAG_REFRESH                       (SWDT_SR_REF)     /*!< Refresh error flag   */
#define SWDT_FLAG_ALL                           (SWDT_SR_UDF | SWDT_SR_REF)
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
 * @addtogroup SWDT_Global_Functions
 * @{
 */

/**
 * @brief  Get SWDT count value.
 * @param  None
 * @retval uint16_t                     Count value
 */
__STATIC_INLINE uint16_t SWDT_GetCountValue(void)
{
    return (uint16_t)(READ_REG32(CM_SWDT->SR) & SWDT_SR_CNT);
}

/* Configuration function */
void SWDT_Feed(void);

/* Flags management functions */
en_flag_status_t SWDT_GetStatus(uint32_t u32Flag);
en_result_t SWDT_ClearStatus(uint32_t u32Flag);

/**
 * @}
 */

#endif /* DDL_SWDT_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_SWDT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
