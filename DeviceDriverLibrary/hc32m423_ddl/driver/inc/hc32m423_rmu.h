/**
 *******************************************************************************
 * @file  hc32m423_rmu.h
 * @brief Head file for RMU module.
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
#ifndef __HC32M423_RMU_H__
#define __HC32M423_RMU_H__

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
 * @addtogroup DDL_RMU
 * @{
 */

#if (DDL_RMU_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RMU_Global_Macros RMU Global Macros
 * @{
 */

/**
 * @defgroup RMU_ResetCause Rmu reset cause
 * @{
 */
#define RMU_RST_PWR_ON                (RMU_RSTF0_PORF)        /*!< Power on reset */
#define RMU_RST_RST_PIN               (RMU_RSTF0_PINRF)       /*!< Reset pin reset */
#define RMU_RST_LVD0                  (RMU_RSTF0_LV0RF)       /*!< Low voltage Detection 0 reset */
#define RMU_RST_LVD1                  (RMU_RSTF0_LV1RF)       /*!< Low voltage Detection 1 reset */
#define RMU_RST_LVD2                  (RMU_RSTF0_LV2RF)       /*!< Low voltage Detection 2 reset */
#define RMU_RST_WDT                   (RMU_RSTF0_WDRF)        /*!< Watchdog timer reset */
#define RMU_RST_SWDT                  (RMU_RSTF0_SWDRF)       /*!< Special watchdog timer reset */
#define RMU_RST_SW                    (RMU_RSTF0_SWRF)        /*!< Software reset */
#define RMU_RST_RAM_PARITY_ERR        (RMU_RSTF0_RAMPERF)     /*!< Ram parity error reset */
#define RMU_RST_CLK_ERR               (RMU_RSTF0_CKFERF)      /*!< Clk frequency error reset */
#define RMU_RST_XTAL_ERR              (RMU_RSTF0_XTALERF)     /*!< Xtal error reset */
#define RMU_RST_CPU_LOCKUP            (RMU_RSTF0_CPULKUPRF)   /*!< M4 Lockup reset */
#define RMU_RST_MX                    (RMU_RSTF0_MULTIRF)     /*!< Multiplex reset cause */
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
 * @addtogroup RMU_Global_Functions
 * @{
 */
en_flag_status_t RMU_GetStatus(uint32_t u16RmuResetStatus);
void RMU_ClearStatus(void);
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

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_RMU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
