/**
 *******************************************************************************
 * @file  hc32m423_icg.c
 * @brief This file provides firmware functions to manage the Initial
 *        Configuration(ICG).
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
#include "hc32m423_icg.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_ICG ICG
 * @brief Initial Configuration Driver Library
 * @{
 */

#if (DDL_ICG_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @brief ICG parameters configuration
 */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
const uint32_t u32ICG[] __attribute__((section(".ARM.__at_0x240"))) =
#elif defined (__GNUC__) && !defined (__CC_ARM)
const uint32_t u32ICG[] __attribute__((section(".icg_sec"))) =
#elif defined (__CC_ARM)
const uint32_t u32ICG[] __attribute__((at(0x240))) =
#elif defined (__ICCARM__)
#pragma location = 0x240
__root static const uint32_t u32ICG[] =
#else
#error "unsupported compiler!!"
#endif
{
    /* ICG 0~1 */
    ICG_REG_CFG0_CONSTANT,
    ICG_REG_CFG1_CONSTANT,
    /* Reserved 2~6 */
    ICG_RESERVED_CONSTANT,
    ICG_RESERVED_CONSTANT,
    ICG_RESERVED_CONSTANT,
    ICG_RESERVED_CONSTANT,
    ICG_RESERVED_CONSTANT,
    /* ICG 7 */
    ICG_REG_CFG7_CONSTANT,
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

#endif /* DDL_ICG_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
