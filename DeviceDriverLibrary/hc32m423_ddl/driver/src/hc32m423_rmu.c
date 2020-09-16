/**
 *******************************************************************************
 * @file  hc32m423_rmu.c
 * @brief This file provides firmware functions to manage the Reset Manage Unit
 *        (RMU).
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
#include "hc32m423_rmu.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_RMU RMU
 * @brief RMU Driver Library
 * @{
 */

#if (DDL_RMU_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RMU_Local_Macros RMU Local Macros
 * @{
 */
#define RMU_STAT_MASK              (RMU_RST_PWR_ON | RMU_RST_RST_PIN | \
                                    RMU_RST_LVD0 | RMU_RST_LVD1 | \
                                    RMU_RST_LVD2 | RMU_RST_WDT | \
                                    RMU_RST_SWDT | RMU_RST_SW | \
                                    RMU_RST_RAM_PARITY_ERR | RMU_RST_CLK_ERR | \
                                    RMU_RST_XTAL_ERR | RMU_RST_CPU_LOCKUP | \
                                    RMU_RST_MX)

/**
 * @defgroup RMU_Check_Parameters_Validity RMU Check Parameters Validity
 * @{
 */

/*! Parameter validity check for RMU reset status. */
#define IS_VALID_RMU_RST_STAT(x)                                               \
(   ((x) != 0U)                              ||                                \
    (((x) | RMU_STAT_MASK) == RMU_STAT_MASK))

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
 * @defgroup RMU_Global_Functions RMU Global Functions
 * @{
 */

/**
 * @brief  Get reset status.
 * @param  [in] u16RmuResetStatus   Reset flags that need to be queried
 *   @arg  RMU_RST_PWR_ON:          Power on reset
 *   @arg  RMU_RST_RST_PIN:         Reset pin reset
 *   @arg  RMU_RST_LVD0:            Low voltage Detection 0 reset
 *   @arg  RMU_RST_LVD1:            Low voltage Detection 1 reset
 *   @arg  RMU_RST_LVD2:            Low voltage Detection 2 reset
 *   @arg  RMU_RST_WDT:             Watchdog timer reset
 *   @arg  RMU_RST_SWDT:            Special watchdog timer reset
 *   @arg  RMU_RST_SW:              Software reset
 *   @arg  RMU_RST_RAM_PARITY_ERR:  Ram parity error reset
 *   @arg  RMU_RST_CLK_ERR:         Clk frequency error reset
 *   @arg  RMU_RST_XTAL_ERR:        Xtal error reset
 *   @arg  RMU_RST_CPU_LOCKUP:      M4 Lockup reset
 *   @arg  RMU_RST_MX:              Multiplex reset cause
 * @retval Set: Flag is Set.
 *         Reset: Flag is Reset
 */
en_flag_status_t RMU_GetStatus(uint32_t u16RmuResetStatus)
{
    en_flag_status_t enRet;
    DDL_ASSERT(IS_VALID_RMU_RST_STAT(u16RmuResetStatus));
    enRet = ((0UL == READ_REG32_BIT(CM_RMU->RSTF0, u16RmuResetStatus)) ? Reset :Set);
    return enRet;
}

/**
 * @brief  Clear reset status.
 * @param  None
 * @retval None
 * @note   Clear reset flag should be done after read RMU_RSTF0 register.
 *         Call PWC_Unlock(PWC_UNLOCK_CODE_1) unlock RMU_RSTF0 register first.
 */
void RMU_ClearStatus(void)
{
    DDL_ASSERT((CM_PWC->FPRC & PWC_FPRC_PWRWE) == PWC_FPRC_PWRWE);

    SET_REG16_BIT(CM_RMU->RSTF0, RMU_RSTF0_CLRF);
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

/**
 * @}
 */

#endif /* DDL_RMU_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
