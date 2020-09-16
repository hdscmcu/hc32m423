/**
 *******************************************************************************
 * @file  hc32_ddl.h
 * @brief This file contains HC32 Series Device Driver Library file call
 *        management.
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
#ifndef __HC32_DDL_H__
#define __HC32_DDL_H__

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

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Defined use Device Driver Library */
#if !defined (USE_DDL_DRIVER)
/**
 * @brief Comment the line below if you will not use the Device Driver Library.
 * In this case, the application code will be based on direct access to
 * peripherals registers.
 */
    /* #define USE_DDL_DRIVER */
#endif /* USE_DDL_DRIVER */

/**
 * @brief HC32 Series Device Driver Library version number v1.0.0
 */
#define HC32_DDL_VERSION_MAIN           0x01U  /*!< [31:24] main version */
#define HC32_DDL_VERSION_SUB1           0x00U  /*!< [23:16] sub1 version */
#define HC32_DDL_VERSION_SUB2           0x00U  /*!< [15:8]  sub2 version */
#define HC32_DDL_VERSION_RC             0x00U  /*!< [7:0]   release candidate */
#define HC32_DDL_VERSION                ((HC32_DDL_VERSION_MAIN << 24) | \
                                         (HC32_DDL_VERSION_SUB1 << 16) | \
                                         (HC32_DDL_VERSION_SUB2 << 8 ) | \
                                         (HC32_DDL_VERSION_RC))

/* Use Device Driver Library */
#if defined (USE_DDL_DRIVER)

/**
 * @brief Include peripheral module's header file
 */
#if (DDL_ADC_ENABLE == DDL_ON)
    #include "hc32m423_adc.h"
#endif /* DDL_ADC_ENABLE */

#if (DDL_CLK_ENABLE == DDL_ON)
    #include "hc32m423_clk.h"
#endif /* DDL_CLK_ENABLE */

#if (DDL_CMP_ENABLE == DDL_ON)
    #include "hc32m423_cmp.h"
#endif /* DDL_CMP_ENABLE */

#if (DDL_CRC_ENABLE == DDL_ON)
    #include "hc32m423_crc.h"
#endif /* DDL_CRC_ENABLE */

#if (DDL_CTC_ENABLE == DDL_ON)
    #include "hc32m423_ctc.h"
#endif /* DDL_CTC_ENABLE */

#if (DDL_DCU_ENABLE == DDL_ON)
    #include "hc32m423_dcu.h"
#endif /* DDL_DCU_ENABLE */

#if (DDL_DMA_ENABLE == DDL_ON)
    #include "hc32m423_dma.h"
#endif /* DDL_DMA_ENABLE */

#if (DDL_EFM_ENABLE == DDL_ON)
    #include "hc32m423_efm.h"
#endif /* DDL_EFM_ENABLE */

#if (DDL_EMB_ENABLE == DDL_ON)
    #include "hc32m423_emb.h"
#endif /* DDL_EMB_ENABLE */

#if (DDL_FCM_ENABLE == DDL_ON)
    #include "hc32m423_fcm.h"
#endif /* DDL_FCM_ENABLE */

#if (DDL_GPIO_ENABLE == DDL_ON)
    #include "hc32m423_gpio.h"
#endif /* DDL_GPIO_ENABLE */

#if (DDL_I2C_ENABLE == DDL_ON)
    #include "hc32m423_i2c.h"
#endif /* DDL_I2C_ENABLE */

#if (DDL_ICG_ENABLE == DDL_ON)
    #include "hc32m423_icg.h"
#endif /* DDL_ICG_ENABLE */

#if ((DDL_INTERRUPTS_ENABLE == DDL_ON) || (DDL_EXTINT_NMI_SWINT_ENABLE == DDL_ON))
    #include "hc32m423_interrupts.h"
#endif /* DDL_INTERRUPTS_ENABLE || DDL_EXTINT_NMI_SWINT_ENABLE */

#if (DDL_PWC_ENABLE == DDL_ON)
    #include "hc32m423_pwc.h"
#endif /* DDL_PWC_ENABLE */

#if (DDL_RMU_ENABLE == DDL_ON)
    #include "hc32m423_rmu.h"
#endif /* DDL_RMU_ENABLE */

#if (DDL_SPI_ENABLE == DDL_ON)
    #include "hc32m423_spi.h"
#endif /* DDL_SPI_ENABLE */

#if (DDL_SWDT_ENABLE == DDL_ON)
    #include "hc32m423_swdt.h"
#endif /* DDL_SWDT_ENABLE */

#if (DDL_TMR0_ENABLE == DDL_ON)
    #include "hc32m423_tmr0.h"
#endif /* DDL_TMR0_ENABLE */

#if (DDL_TMR4_ENABLE == DDL_ON)
    #include "hc32m423_tmr4.h"
#endif /* DDL_TMR4_ENABLE */

#if (DDL_TMRA_ENABLE == DDL_ON)
    #include "hc32m423_tmra.h"
#endif /* DDL_TMRA_ENABLE */

#if (DDL_TMRB_ENABLE == DDL_ON)
    #include "hc32m423_tmrb.h"
#endif /* DDL_TMRB_ENABLE */

#if (DDL_USART_ENABLE == DDL_ON)
    #include "hc32m423_usart.h"
#endif /* DDL_USART_ENABLE */

#if (DDL_UTILITY_ENABLE == DDL_ON)
    #include "hc32m423_utility.h"
#endif /* DDL_UTILITY_ENABLE */

#if (DDL_WDT_ENABLE == DDL_ON)
    #include "hc32m423_wdt.h"
#endif /* DDL_WDT_ENABLE */


/**
 * @brief Include BSP board's header file
 */
#if (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423)
    #include "ev_hc32m423_lqfp64.h"
#endif /* BSP_EV_HC32M423_LQFP64 */

#endif /* USE_DDL_DRIVER */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __HC32_DDL_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
