/**
 *******************************************************************************
 * @file    hc32m423_icg.h
 * @brief   This file contains all the Macro Definitions of the ICG driver
 *          library.
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
#ifndef __HC32M423_ICG_H__
#define __HC32M423_ICG_H__

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
 * @addtogroup DDL_ICG
 * @{
 */

#if (DDL_ICG_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ICG_Global_Macros ICG Global Macros
 * @{
 */

/**
 * @defgroup ICG_SWDT_Reset_State ICG SWDT Reset State
 * @{
 */
#define ICG_SWDT_RST_START                      (0UL)                 /*!< SWDT Auto Start after reset */
#define ICG_SWDT_RST_STOP                       (ICG_ICG0_SWDTAUTST)  /*!< SWDT stop after reset       */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Exception_Type ICG SWDT Exception Type
 * @{
 */
#define ICG_SWDT_EXP_TYPE_INT                   (0UL)                 /*!< SWDT trigger interrupt */
#define ICG_SWDT_EXP_TYPE_RST                   (ICG_ICG0_SWDTITS)    /*!< SWDT trigger reset     */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Count_Period ICG SWDT Count Period
 * @{
 */
#define ICG_SWDT_CNT_PERIOD256                  (0UL)                   /*!< 256 clock cycle   */
#define ICG_SWDT_CNT_PERIOD4096                 (ICG_ICG0_SWDTPERI_0)   /*!< 4096 clock cycle  */
#define ICG_SWDT_CNT_PERIOD16384                (ICG_ICG0_SWDTPERI_1)   /*!< 16384 clock cycle */
#define ICG_SWDT_CNT_PERIOD65536                (ICG_ICG0_SWDTPERI)     /*!< 65536 clock cycle */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Clock_Division ICG SWDT Clock Division
 * @{
 */
#define ICG_SWDT_CLK_DIV1                       (0UL)                             /*!< SWDTCLK      */
#define ICG_SWDT_CLK_DIV16                      (0x04UL << ICG_ICG0_SWDTCKS_POS)  /*!< SWDTCLK/16   */
#define ICG_SWDT_CLK_DIV32                      (0x05UL << ICG_ICG0_SWDTCKS_POS)  /*!< SWDTCLK/32   */
#define ICG_SWDT_CLK_DIV64                      (0x06UL << ICG_ICG0_SWDTCKS_POS)  /*!< SWDTCLK/64   */
#define ICG_SWDT_CLK_DIV128                     (0x07UL << ICG_ICG0_SWDTCKS_POS)  /*!< SWDTCLK/128  */
#define ICG_SWDT_CLK_DIV256                     (0x08UL << ICG_ICG0_SWDTCKS_POS)  /*!< SWDTCLK/256  */
#define ICG_SWDT_CLK_DIV2048                    (0x0BUL << ICG_ICG0_SWDTCKS_POS)  /*!< SWDTCLK/2048 */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Refresh_Range ICG SWDT Refresh Range
 * @{
 */
#define ICG_SWDT_RANGE_0TO100PCT                (0UL)                               /*!< 0%~100%            */
#define ICG_SWDT_RANGE_0TO25PCT                 (0x01UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~25%             */
#define ICG_SWDT_RANGE_25TO50PCT                (0x02UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 25%~50%            */
#define ICG_SWDT_RANGE_0TO50PCT                 (0x03UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~50%             */
#define ICG_SWDT_RANGE_50TO75PCT                (0x04UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 50%~75%            */
#define ICG_SWDT_RANGE_0TO25PCT_50TO75PCT       (0x05UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~25% & 50%~75%   */
#define ICG_SWDT_RANGE_25TO75PCT                (0x06UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 25%~75%            */
#define ICG_SWDT_RANGE_0TO75PCT                 (0x07UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~75%             */
#define ICG_SWDT_RANGE_75TO100PCT               (0x08UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 75%~100%           */
#define ICG_SWDT_RANGE_0TO25PCT_75TO100PCT      (0x09UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~25% & 75%~100%  */
#define ICG_SWDT_RANGE_25TO50PCT_75TO100PCT     (0x0AUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 25%~50% & 75%~100% */
#define ICG_SWDT_RANGE_0TO50PCT_75TO100PCT      (0x0BUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~50% & 75%~100%  */
#define ICG_SWDT_RANGE_50TO100PCT               (0x0CUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 50%~100%           */
#define ICG_SWDT_RANGE_0TO25PCT_50TO100PCT      (0x0DUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~25% & 50%~100%  */
#define ICG_SWDT_RANGE_25TO100PCT               (0x0EUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 25%~100%           */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_LPM_Count ICG SWDT Low Power Mode Count
 * @brief    Counting control of SWDT in sleep/stop mode
 * @{
 */
#define ICG_SWDT_LPM_CNT_CONTINUE               (0UL)                   /*!< Continue counting in sleep/stop mode */
#define ICG_SWDT_LPM_CNT_STOP                   (ICG_ICG0_SWDTSLPOFF)   /*!< Stop counting in sleep/stop mode     */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Reset_State ICG WDT Reset State
 * @{
 */
#define ICG_WDT_RST_START                       (0UL)                 /*!< WDT Auto Start after reset */
#define ICG_WDT_RST_STOP                        (ICG_ICG7_WDTAUTST)   /*!< WDT stop after reset       */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Exception_Type ICG WDT Exception Type
 * @{
 */
#define ICG_WDT_EXP_TYPE_INT                    (0UL)               /*!< WDT trigger interrupt */
#define ICG_WDT_EXP_TYPE_RST                    (ICG_ICG7_WDTITS)   /*!< WDT trigger reset     */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Count_Period ICG WDT Count Period
 * @{
 */
#define ICG_WDT_CNT_PERIOD256                   (0UL)                 /*!< 256 clock cycle   */
#define ICG_WDT_CNT_PERIOD4096                  (ICG_ICG7_WDTPERI_0)  /*!< 4096 clock cycle  */
#define ICG_WDT_CNT_PERIOD16384                 (ICG_ICG7_WDTPERI_1)  /*!< 16384 clock cycle */
#define ICG_WDT_CNT_PERIOD65536                 (ICG_ICG7_WDTPERI)    /*!< 65536 clock cycle */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Clock_Division ICG WDT Clock Division
 * @{
 */
#define ICG_WDT_CLK_DIV4                        (0x02UL << ICG_ICG7_WDTCKS_POS)   /*!< PCLK1/4    */
#define ICG_WDT_CLK_DIV64                       (0x06UL << ICG_ICG7_WDTCKS_POS)   /*!< PCLK1/64   */
#define ICG_WDT_CLK_DIV128                      (0x07UL << ICG_ICG7_WDTCKS_POS)   /*!< PCLK1/128  */
#define ICG_WDT_CLK_DIV256                      (0x08UL << ICG_ICG7_WDTCKS_POS)   /*!< PCLK1/256  */
#define ICG_WDT_CLK_DIV512                      (0x09UL << ICG_ICG7_WDTCKS_POS)   /*!< PCLK1/512  */
#define ICG_WDT_CLK_DIV1024                     (0x0AUL << ICG_ICG7_WDTCKS_POS)   /*!< PCLK1/1024 */
#define ICG_WDT_CLK_DIV2048                     (0x0BUL << ICG_ICG7_WDTCKS_POS)   /*!< PCLK1/2048 */
#define ICG_WDT_CLK_DIV8192                     (0x0DUL << ICG_ICG7_WDTCKS_POS)   /*!< PCLK1/8192 */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Refresh_Range ICG WDT Refresh Range
 * @{
 */
#define ICG_WDT_RANGE_0TO100PCT                 (0UL)                             /*!< 0%~100%            */
#define ICG_WDT_RANGE_0TO25PCT                  (0x01UL << ICG_ICG7_WDTWDPT_POS)  /*!< 0%~25%             */
#define ICG_WDT_RANGE_25TO50PCT                 (0x02UL << ICG_ICG7_WDTWDPT_POS)  /*!< 25%~50%            */
#define ICG_WDT_RANGE_0TO50PCT                  (0x03UL << ICG_ICG7_WDTWDPT_POS)  /*!< 0%~50%             */
#define ICG_WDT_RANGE_50TO75PCT                 (0x04UL << ICG_ICG7_WDTWDPT_POS)  /*!< 50%~75%            */
#define ICG_WDT_RANGE_0TO25PCT_50TO75PCT        (0x05UL << ICG_ICG7_WDTWDPT_POS)  /*!< 0%~25% & 50%~75%   */
#define ICG_WDT_RANGE_25TO75PCT                 (0x06UL << ICG_ICG7_WDTWDPT_POS)  /*!< 25%~75%            */
#define ICG_WDT_RANGE_0TO75PCT                  (0x07UL << ICG_ICG7_WDTWDPT_POS)  /*!< 0%~75%             */
#define ICG_WDT_RANGE_75TO100PCT                (0x08UL << ICG_ICG7_WDTWDPT_POS)  /*!< 75%~100%           */
#define ICG_WDT_RANGE_0TO25PCT_75TO100PCT       (0x09UL << ICG_ICG7_WDTWDPT_POS)  /*!< 0%~25% & 75%~100%  */
#define ICG_WDT_RANGE_25TO50PCT_75TO100PCT      (0x0AUL << ICG_ICG7_WDTWDPT_POS)  /*!< 25%~50% & 75%~100% */
#define ICG_WDT_RANGE_0TO50PCT_75TO100PCT       (0x0BUL << ICG_ICG7_WDTWDPT_POS)  /*!< 0%~50% & 75%~100%  */
#define ICG_WDT_RANGE_50TO100PCT                (0x0CUL << ICG_ICG7_WDTWDPT_POS)  /*!< 50%~100%           */
#define ICG_WDT_RANGE_0TO25PCT_50TO100PCT       (0x0DUL << ICG_ICG7_WDTWDPT_POS)  /*!< 0%~25% & 50%~100%  */
#define ICG_WDT_RANGE_25TO100PCT                (0x0EUL << ICG_ICG7_WDTWDPT_POS)  /*!< 25%~100%           */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_LPM_Count ICG WDT Low Power Mode Count
 * @brief    Counting control of WDT in sleep mode
 * @{
 */
#define ICG_WDT_LPM_CNT_CONTINUE                (0UL)                 /*!< Continue counting in sleep mode */
#define ICG_WDT_LPM_CNT_STOP                    (ICG_ICG7_WDTSLPOFF)  /*!< Stop counting in sleep mode     */
/**
 * @}
 */

/**
 * @defgroup ICG_HRC_Frequency ICG HRC Frequency
 * @{
 */
#define ICG_HRC_1P5M                            (0x0DUL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 1.5MHz */
#define ICG_HRC_2M                              (0x05UL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 2MHz   */
#define ICG_HRC_3M                              (0x0CUL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 3MHz   */
#define ICG_HRC_4M                              (0x04UL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 4MHz   */
#define ICG_HRC_6M                              (0x0BUL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 6MHz   */
#define ICG_HRC_8M                              (0x03UL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 8MHz   */
#define ICG_HRC_12M                             (0x0AUL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 12MHz  */
#define ICG_HRC_16M                             (0x02UL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 16MHz  */
#define ICG_HRC_24M                             (0x09UL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 24MHz  */
#define ICG_HRC_32M                             (0x01UL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 32MHz  */
#define ICG_HRC_48M                             (0x08UL << ICG_ICG0_HRCFRQSEL_POS)  /*!< HRC = 48MHz  */
#define ICG_HRC_64M                             (0UL)                               /*!< HRC = 64MHz  */
/**
 * @}
 */

/**
 * @defgroup ICG_HRC_Reset_State ICG HRC Reset State
 * @{
 */
#define ICG_HRC_RST_OSCILLATE                   (0UL)               /*!< HRC Oscillate after reset */
#define ICG_HRC_RST_STOP                        (ICG_ICG0_HRCSTOP)  /*!< HRC stop after reset        */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Filter_Clock_Division ICG NMI Pin Filter Clock Division
 * @{
 */
#define ICG_NMI_PIN_FILTER_CLK_DIV1             (0UL)                 /*!< HCLK    */
#define ICG_NMI_PIN_FILTER_CLK_DIV8             (ICG_ICG0_NMIFCLK_0)  /*!< HCLK/8  */
#define ICG_NMI_PIN_FILTER_CLK_DIV32            (ICG_ICG0_NMIFCLK_1)  /*!< HCLK/32 */
#define ICG_NMI_PIN_FILTER_CLK_DIV64            (ICG_ICG0_NMIFCLK)    /*!< HCLK/64 */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Filter ICG NMI Pin Filter
 * @{
 */
#define ICG_NMI_PIN_FILTER_DISABLE              (0UL)               /*!< Disable NMI Pin filter */
#define ICG_NMI_PIN_FILTER_ENABLE               (ICG_ICG0_NMIFEN)   /*!< Enable NMI Pin filter  */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Trigger_Edge ICG NMI Pin Trigger Edge
 * @{
 */
#define ICG_NMI_PIN_TRIG_EDGE_FALLING           (0UL)               /*!< Falling edge trigger */
#define ICG_NMI_PIN_TRIG_EDGE_RISING            (ICG_ICG0_NMITRG)   /*!< Rising edge trigger  */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Interrupt ICG NMI Pin Interrupt
 * @{
 */
#define ICG_NMI_PIN_INT_DISABLE                 (0UL)             /*!< Disable NMI pin interrupt */
#define ICG_NMI_PIN_INT_ENABLE                  (ICG_ICG0_NMIEN)  /*!< Enable NMI pin interrupt  */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Reset_State ICG NMI Pin Reset State
 * @{
 */
#define ICG_NMI_PIN_RST_ENABLE                  (0UL)                 /*!< Enable NMI pin after reset  */
#define ICG_NMI_PIN_RST_DISABLE                 (ICG_ICG0_NMIICGEN)   /*!< Disable NMI pin after reset */
/**
 * @}
 */

/**
 * @defgroup ICG_Lockup_Reset_State ICG Lockup Reset State
 * @{
 */
#define ICG_LOCKUP_RST_ENABLE                   (0UL)               /*!< Enable core Lockup reset  */
#define ICG_LOCKUP_RST_DISABLE                  (ICG_ICG1_LKUPDIS)  /*!< Disable core Lockup reset */
/**
 * @}
 */

/**
 * @defgroup ICG_LVD_Voltage_Threshold ICG LVD Voltage Threshold
 * @{
 */
#define ICG_LVD_THRESHOLD_LVL0                  (0UL)                             /*!< LVD0 voltage threshold less than 4.29 or higher than 4.39 */
#define ICG_LVD_THRESHOLD_LVL1                  (0x01UL << ICG_ICG1_LVD0LVL_POS)  /*!< LVD0 voltage threshold less than 3.84 or higher than 3.96 */
#define ICG_LVD_THRESHOLD_LVL2                  (0x02UL << ICG_ICG1_LVD0LVL_POS)  /*!< LVD0 voltage threshold less than 2.82 or higher than 2.90 */
#define ICG_LVD_THRESHOLD_LVL3                  (0x03UL << ICG_ICG1_LVD0LVL_POS)  /*!< LVD0 voltage threshold less than 2.51 or higher than 2.59 */
#define ICG_LVD_THRESHOLD_LVL4                  (0x04UL << ICG_ICG1_LVD0LVL_POS)  /*!< LVD0 voltage threshold less than 2.34 or higher than 2.41 */
#define ICG_LVD_THRESHOLD_LVL5                  (0x05UL << ICG_ICG1_LVD0LVL_POS)  /*!< LVD0 voltage threshold less than 2.14 or higher than 2.21 */
#define ICG_LVD_THRESHOLD_LVL6                  (0x06UL << ICG_ICG1_LVD0LVL_POS)  /*!< LVD0 voltage threshold less than 1.94 or higher than 2.01 */
#define ICG_LVD_THRESHOLD_LVL7                  (0x07UL << ICG_ICG1_LVD0LVL_POS)  /*!< LVD0 voltage threshold less than 1.84 or higher than 1.90 */
/**
 * @}
 */

/**
 * @defgroup ICG_LVD_Reset_State ICG LVD Reset State
 * @{
 */
#define ICG_LVD_RST_ENABLE                      (0UL)               /*!< Enable LVD0 after reset  */
#define ICG_LVD_RST_DISABLE                     (ICG_ICG1_LVD0DIS)  /*!< Disable LVD0 after reset */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup ICG_Register_Configuration ICG Register Configuration
 * @{
 */

/**
 *******************************************************************************
 * @defgroup ICG_SWDT_Preload_Configuration ICG SWDT Preload Configuration
 * @{
 *******************************************************************************
 */
/* SWDT register config */
#define ICG0_RB_SWDT_AUTST                      (ICG_SWDT_RST_STOP)
#define ICG0_RB_SWDT_ITS                        (ICG_SWDT_EXP_TYPE_INT)
#define ICG0_RB_SWDT_PERI                       (ICG_SWDT_CNT_PERIOD65536)
#define ICG0_RB_SWDT_CKS                        (ICG_SWDT_CLK_DIV2048)
#define ICG0_RB_SWDT_WDPT                       (ICG_SWDT_RANGE_0TO100PCT)
#define ICG0_RB_SWDT_SLTPOFF                    (ICG_SWDT_LPM_CNT_CONTINUE)

/* SWDT register value */
#define ICG0_RB_SWDT_CONFIG                     (ICG0_RB_SWDT_AUTST | ICG0_RB_SWDT_ITS | \
                                                 ICG0_RB_SWDT_PERI  | ICG0_RB_SWDT_CKS | \
                                                 ICG0_RB_SWDT_WDPT  | ICG0_RB_SWDT_SLTPOFF)
/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_WDT_Preload_Configuration ICG WDT Preload Configuration
 * @{
 *******************************************************************************
 */
/* WDT register config */
#define ICG7_RB_WDT_AUTST                       (ICG_WDT_RST_STOP)
#define ICG7_RB_WDT_ITS                         (ICG_WDT_EXP_TYPE_INT)
#define ICG7_RB_WDT_PERI                        (ICG_WDT_CNT_PERIOD65536)
#define ICG7_RB_WDT_CKS                         (ICG_WDT_CLK_DIV8192)
#define ICG7_RB_WDT_WDPT                        (ICG_WDT_RANGE_0TO100PCT)
#define ICG7_RB_WDT_SLTPOFF                     (ICG_WDT_LPM_CNT_CONTINUE)

/* WDT register value */
#define ICG7_RB_WDT_CONFIG                      (ICG7_RB_WDT_AUTST | ICG7_RB_WDT_ITS | \
                                                 ICG7_RB_WDT_PERI  | ICG7_RB_WDT_CKS | \
                                                 ICG7_RB_WDT_WDPT  | ICG7_RB_WDT_SLTPOFF)
/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_HRC_Preload_Configuration ICG HRC Preload Configuration
 * @{
 *******************************************************************************
 */
/* HRC register config */
#define ICG0_RB_HRC_FRQSEL                      (ICG_HRC_16M)
#define ICG0_RB_HRC_STOP                        (ICG_HRC_RST_STOP)

/* HRC register value */
#define ICG0_RB_HRC_CONFIG                      (ICG0_RB_HRC_FRQSEL | ICG0_RB_HRC_STOP)
/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_NMI_Pin_Preload_Configuration ICG NMI Pin Preload Configuration
 * @{
 *******************************************************************************
 */
/* NMI register config */
#define ICG0_RB_NMI_FCLK                        (ICG_NMI_PIN_FILTER_CLK_DIV64)
#define ICG0_RB_NMI_FEN                         (ICG_NMI_PIN_FILTER_ENABLE)
#define ICG0_RB_NMI_TRG                         (ICG_NMI_PIN_TRIG_EDGE_RISING)
#define ICG0_RB_NMI_EN                          (ICG_NMI_PIN_INT_ENABLE)
#define ICG0_RB_NMI_ICGEN                       (ICG_NMI_PIN_RST_DISABLE)

/* NMI register value */
#define ICG0_RB_NMI_CONFIG                      (ICG0_RB_NMI_FCLK | ICG0_RB_NMI_FEN | ICG0_RB_NMI_TRG | \
                                                 ICG0_RB_NMI_EN   | ICG0_RB_NMI_ICGEN)
/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_LKUP_Preload_Configuration ICG LKUP Preload Configuration
 * @{
 *******************************************************************************
 */
/* Lockup register config */
#define ICG1_RB_LKUP_DIS                        (ICG_LOCKUP_RST_DISABLE)

/* Lockup register value */
#define ICG1_RB_LKUP_CONFIG                     (ICG1_RB_LKUP_DIS)
/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_LVD0_Preload_Configuration ICG LVD0 Preload Configuration
 * @{
 *******************************************************************************
 */
/* LVD0 register config */
#define ICG1_RB_LVD0_LVL                        (ICG_LVD_THRESHOLD_LVL7)
#define ICG1_RB_LVD0_DIS                        (ICG_LVD_RST_DISABLE)

/* LVD0 register value */
#define ICG1_RB_LVD0_CONFIG                     (ICG1_RB_LVD0_LVL | ICG1_RB_LVD0_DIS)
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup ICG_Register_Value ICG Register Value
 * @{
 */
/* ICG register value */
#define ICG_REG_CFG0_CONSTANT                   (ICG0_RB_SWDT_CONFIG | ICG0_RB_HRC_CONFIG  | ICG0_RB_NMI_CONFIG | 0x03E0E000UL)
#define ICG_REG_CFG1_CONSTANT                   (ICG1_RB_LKUP_CONFIG | ICG1_RB_LVD0_CONFIG | 0xFFFF0EFFUL)
#define ICG_REG_CFG7_CONSTANT                   (ICG7_RB_WDT_CONFIG  | 0xFFFFE000UL)
/* ICG reserved value */
#define ICG_RESERVED_CONSTANT                   (0xFFFFFFFFUL)

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

#endif /* DDL_ICG_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_ICG_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
