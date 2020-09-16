/**
 *******************************************************************************
 * @file  hc32m423_swdt.c
 * @brief This file provides firmware functions to manage the Special Watch Dog
 *        Timer(SWDT).
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
#include "hc32m423_swdt.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_SWDT SWDT
 * @brief Specialized Watch Dog Timer
 * @{
 */

#if (DDL_SWDT_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SWDT_Local_Macros SWDT Local Macros
 * @{
 */

/* SWDT Refresh Key */
#define SWDT_REFRESH_KEY_START          (0x0123UL)
#define SWDT_REFRESH_KEY_END            (0x3210UL)

/* SWDT clear flag timeout(ms) */
#define SWDT_CLR_FLAG_TIMEOUT           (5UL)

/**
 * @defgroup SWDT_Check_Parameters_Validity SWDT Check Parameters Validity
 * @{
 */
#define IS_SWDT_FLAG(x)                                                        \
(   ((x) != 0UL)                                &&                             \
    (((x) | SWDT_FLAG_ALL) == SWDT_FLAG_ALL))

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
 * @defgroup SWDT_Global_Functions SWDT Global Functions
 * @{
 */

/**
 * @brief  SWDT feed dog.
 * @param  None
 * @retval None
 */
void SWDT_Feed(void)
{
    WRITE_REG32(CM_SWDT->RR, SWDT_REFRESH_KEY_START);
    WRITE_REG32(CM_SWDT->RR, SWDT_REFRESH_KEY_END);
}

/**
 * @brief  Get SWDT flag status.
 * @param  [in] u32Flag                 SWDT flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg SWDT_FLAG_UDF:        Count underflow flag
 *           @arg SWDT_FLAG_REFRESH:    Refresh error flag
 *           @arg SWDT_FLAG_ALL:        All of the above
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t SWDT_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_SWDT_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_SWDT->SR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Clear SWDT flag.
 * @param  [in] u32Flag                 SWDT flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg SWDT_FLAG_UDF:        Count underflow flag
 *           @arg SWDT_FLAG_REFRESH:    Refresh error flag
 *           @arg SWDT_FLAG_ALL:        All of the above
 * @retval An en_result_t enumeration value:
 *           - Ok: Clear flag success
 *           - ErrorTimeout: Clear flag timeout
 */
en_result_t SWDT_ClearStatus(uint32_t u32Flag)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    /* Check parameters */
    DDL_ASSERT(IS_SWDT_FLAG(u32Flag));

    CLEAR_REG32_BIT(CM_SWDT->SR, u32Flag);
    /* Waiting for FLAG bit clear */
    u32Count = SWDT_CLR_FLAG_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32_BIT(CM_SWDT->SR, u32Flag))
    {
        if (0UL == u32Count)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    return enRet;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
