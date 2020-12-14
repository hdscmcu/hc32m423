/**
 *******************************************************************************
 * @file  system_hc32m423.h
 * @brief This file contains all the functions prototypes of the HC32 System.
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
#ifndef __SYSTEM_HC32M423_H__
#define __SYSTEM_HC32M423_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <stdint.h>

/**
 * @addtogroup CMSIS
 * @{
 */

/**
 * @addtogroup HC32M423_System
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('define')
 ******************************************************************************/
/**
 * @addtogroup HC32M423_System_Global_Macros
 * @{
 */

/**
 * @brief Clock setup macro definition
 */
#define CLOCK_SETTING_NONE      (0U)            /*!< User provides own clock setting in application */
#define CLOCK_SETTING_CMSIS     (1U)


/**
 * @addtogroup HC32M423_System_Clock_Source
 * @{
 */

#if !defined (HRC_64MHz_VALUE)
    #define HRC_64MHz_VALUE     (64000000UL)
#endif
#if !defined (HRC_32MHz_VALUE)
    #define HRC_32MHz_VALUE     (32000000UL)
#endif
#if !defined (HRC_16MHz_VALUE)
    #define HRC_16MHz_VALUE     (16000000UL)     /*!< Internal high speed RC default freq. */
#endif
#if !defined (HRC_8MHz_VALUE)
    #define HRC_8MHz_VALUE      (8000000UL)
#endif
#if !defined (HRC_4MHz_VALUE)
    #define HRC_4MHz_VALUE      (4000000UL)
#endif
#if !defined (HRC_2MHz_VALUE)
    #define HRC_2MHz_VALUE      (2000000UL)
#endif

#if !defined (MRC_VALUE)
    #define MRC_VALUE           (8000000UL)     /*!< Internal middle speed RC freq. */
#endif

#if !defined (LRC_VALUE)
    #define LRC_VALUE           (32768UL)       /*!< Internal low speed RC freq. */
#endif

#if !defined (XTAL_VALUE)
    #define XTAL_VALUE          (8000000UL)     /*!< External high speed OSC freq. */
#endif

#if !defined (SWDTLRC_VALUE)
    #define SWDTLRC_VALUE       (16000UL)       /*!< External low speed OSC freq.(16KHz) */
#endif

#if !defined (HCLK_VALUE)
#define HCLK_VALUE              (SystemCoreClock >> ((CM_CMU->SCFGR & CMU_SCFGR_HCLKS) >> CMU_SCFGR_HCLKS_POS))
#endif

#if !defined (CLK_PLL_SRC_XTAL_FREQ_48M)
#define CLK_PLL_SRC_XTAL_FREQ_48M       (48UL*1000UL*1000UL)   /*!< high speed RC frequency 48M for PLL source */
#endif

#if !defined (CLK_PLL_SRC_XTAL_FREQ_64M)
#define CLK_PLL_SRC_XTAL_FREQ_64M       (64UL*1000UL*1000UL)   /*!< high speed RC frequency 64M for PLL source */
#endif

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/**
 * @addtogroup HC32M423_System_Exported_Variable
 * @{
 */

extern uint32_t SystemCoreClock;                /*!< System clock frequency (Core clock) */
extern uint32_t HRC_VALUE;                      /*!< HRC frequency */
extern const uint32_t au32HrcFreqTable[8];      /*!< HRC frequency table */
/**
 * @}
 */

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup HC32M423_System_Global_Functions
 * @{
 */

extern void SystemInit(void);             /*!< Initialize the system */
extern void SystemCoreClockUpdate(void);  /*!< Update SystemCoreClock variable */

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

#endif /* __SYSTEM_HC32M423_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
