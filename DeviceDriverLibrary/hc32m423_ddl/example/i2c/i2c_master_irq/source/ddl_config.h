/**
 *******************************************************************************
 * @file  template/source/ddl_config.h
 * @brief This file contains HC32 Series Device Driver Library usage management.
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
#ifndef __DDL_CONFIG_H__
#define __DDL_CONFIG_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Chip module on-off define */
#define DDL_ON                                      (1U)
#define DDL_OFF                                     (0U)

/**
 * @brief This is the list of modules to be used in the Device Driver Library.
 * Select the modules you need to use to DDL_ON.
 * @note DDL_ICG_ENABLE must be turned on(DDL_ON) to ensure that the chip works
 * properly.
 * @note DDL_UTILITY_ENABLE must be turned on(DDL_ON) if using Device Driver
 * Library.
 * @note DDL_PRINT_ENABLE must be turned on(DDL_ON) if using printf function.
 */
#define DDL_ICG_ENABLE                              (DDL_ON)
#define DDL_UTILITY_ENABLE                          (DDL_ON)
#define DDL_PRINT_ENABLE                            (DDL_OFF)

#define DDL_ADC_ENABLE                              (DDL_OFF)
#define DDL_CLK_ENABLE                              (DDL_ON)
#define DDL_CMP_ENABLE                              (DDL_OFF)
#define DDL_CRC_ENABLE                              (DDL_OFF)
#define DDL_CTC_ENABLE                              (DDL_OFF)
#define DDL_DCU_ENABLE                              (DDL_OFF)
#define DDL_DMA_ENABLE                              (DDL_OFF)
#define DDL_EFM_ENABLE                              (DDL_ON)
#define DDL_EMB_ENABLE                              (DDL_OFF)
#define DDL_EXTINT_NMI_SWINT_ENABLE                 (DDL_OFF)
#define DDL_FCM_ENABLE                              (DDL_OFF)
#define DDL_GPIO_ENABLE                             (DDL_ON)
#define DDL_I2C_ENABLE                              (DDL_ON)
#define DDL_INTERRUPTS_ENABLE                       (DDL_ON)
#define DDL_PWC_ENABLE                              (DDL_ON)
#define DDL_RMU_ENABLE                              (DDL_OFF)
#define DDL_SPI_ENABLE                              (DDL_OFF)
#define DDL_SWDT_ENABLE                             (DDL_OFF)
#define DDL_TMR0_ENABLE                             (DDL_OFF)
#define DDL_TMR2_ENABLE                             (DDL_OFF)
#define DDL_TMR4_ENABLE                             (DDL_OFF)
#define DDL_TMRA_ENABLE                             (DDL_OFF)
#define DDL_TMRB_ENABLE                             (DDL_OFF)
#define DDL_USART_ENABLE                            (DDL_OFF)
#define DDL_WDT_ENABLE                              (DDL_OFF)

/* BSP on-off define */
#define BSP_ON                                      (1U)
#define BSP_OFF                                     (0U)

/**
 * @brief The following is a list of currently supported BSP boards.
 */
#define BSP_EV_HC32M423_LQFP64                      (1U)

/**
 * @brief The macro BSP_EV_HC32M423 is used to specify the BSP board currently
 * in use.
 * The value should be set to one of the list of currently supported BSP boards.
 * @note  If there is no supported BSP board or the BSP function is not used,
 * the value needs to be set to BSP_EV_HC32M423.
 */
#define BSP_EV_HC32M423                             (BSP_EV_HC32M423_LQFP64)

/**
 * @brief This is the list of BSP components to be used.
 * Select the components you need to use to BSP_ON.
 */
#define BSP_BL24C02F_ENABLE                         (BSP_OFF)
#define BSP_W25QXX_ENABLE                           (BSP_OFF)
#define BSP_INT_KEY_ENABLE                          (BSP_OFF)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __DDL_CONFIG_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
