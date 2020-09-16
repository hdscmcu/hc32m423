/**
 *******************************************************************************
 * @file  HC32M423.h
 * @brief Headerfile for HC32M423 series MCU
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-15       CDT         First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 */

#ifndef __HC32M423_H__
#define __HC32M423_H__

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Configuration of the Cortex-M4 Processor and Core Peripherals
 ******************************************************************************/
#define __MPU_PRESENT             1       /*!< HC32M423 provides MPU                            */
#define __VTOR_PRESENT            1       /*!< HC32M423 supported vector table registers            */
#define __NVIC_PRIO_BITS          4       /*!< HC32M423 uses 4 Bits for the Priority Levels         */
#define __Vendor_SysTickConfig    0       /*!< Set to 1 if different SysTick Config is used              */
#define __FPU_PRESENT             1       /*!< FPU present                                               */

/*******************************************************************************
 * Interrupt Number Definition
 ******************************************************************************/
typedef enum
{
    NMI_IRQn                  = -14,  /* Non Maskable                             */
    HardFault_IRQn            = -13,  /* Hard Fault                               */
    MemManageFault_IRQn       = -12,  /* MemManage Fault                          */
    BusFault_IRQn             = -11,  /* Bus Fault                                */
    UsageFault_IRQn           = -10,  /* Usage Fault                              */
    SVC_IRQn                  = -5,   /* SVCall                                   */
    DebugMonitor_IRQn         = -4,   /* DebugMonitor                             */
    PendSV_IRQn               = -2,   /* Pend SV                                  */
    SysTick_IRQn              = -1,   /* System Tick                              */
    INT000_IRQn               = 0,
    INT001_IRQn               = 1,
    INT002_IRQn               = 2,
    INT003_IRQn               = 3,
    INT004_IRQn               = 4,
    INT005_IRQn               = 5,
    INT006_IRQn               = 6,
    INT007_IRQn               = 7,
    EXTINT_PORT_EIRQ0_IRQn    = 8,
    EXTINT_PORT_EIRQ1_IRQn    = 9,
    EXTINT_PORT_EIRQ2_IRQn    = 10,
    EXTINT_PORT_EIRQ3_IRQn    = 11,
    EXTINT_PORT_EIRQ4_IRQn    = 12,
    EXTINT_PORT_EIRQ5_IRQn    = 13,
    EXTINT_PORT_EIRQ6_IRQn    = 14,
    EXTINT_PORT_EIRQ7_IRQn    = 15,
    SWINT0_IRQn               = 0,
    SWINT1_IRQn               = 1,
    SWINT2_IRQn               = 2,
    SWINT3_IRQn               = 3,
    SWINT4_IRQn               = 4,
    SWINT5_IRQn               = 5,
    SWINT6_IRQn               = 6,
    SWINT7_IRQn               = 7,
    SWINT8_IRQn               = 8,
    SWINT9_IRQn               = 9,
    SWINT10_IRQn              = 10,
    SWINT11_IRQn              = 11,
    SWINT12_IRQn              = 12,
    SWINT13_IRQn              = 13,
    SWINT14_IRQn              = 14,
    SWINT15_IRQn              = 15,
    DMA_TC0_IRQn              = 16,
    DMA_TC1_IRQn              = 17,
    DMA_TC2_IRQn              = 18,
    DMA_TC3_IRQn              = 19,
    DMA_BTC0_IRQn             = 20,
    DMA_BTC1_IRQn             = 21,
    DMA_BTC2_IRQn             = 22,
    DMA_BTC3_IRQn             = 23,
    DMA_ERR_IRQn              = 24,
    EFM_PEERR_IRQn            = 25,
    EFM_COLERR_IRQn           = 26,
    EFM_OPTEND_IRQn           = 27,
    DCU_IRQn                  = 28,
    TMR0_1_GCMA_IRQn          = 29,
    TMR0_1_GCMB_IRQn          = 30,
    TMR0_2_GCMA_IRQn          = 31,
    TMR0_2_GCMB_IRQn          = 32,
    XTAL_STOP_IRQn            = 33,
    SWDT_IRQn                 = 34,
    TMRA_1_OVF_IRQn           = 35,
    TMRA_1_UDF_IRQn           = 36,
    TMRA_1_CMP_IRQn           = 37,
    TMRA_2_OVF_IRQn           = 38,
    TMRA_2_UDF_IRQn           = 39,
    TMRA_2_CMP_IRQn           = 40,
    TMRA_3_OVF_IRQn           = 41,
    TMRA_3_UDF_IRQn           = 42,
    TMRA_3_CMP_IRQn           = 43,
    TMRA_4_OVF_IRQn           = 44,
    TMRA_4_UDF_IRQn           = 45,
    TMRA_4_CMP_IRQn           = 46,
    TMRB_OVF_IRQn             = 47,
    TMRB_UDF_IRQn             = 48,
    TMRB_CMP_IRQn             = 49,
    USART1_EI_IRQn            = 50,
    USART1_RI_IRQn            = 51,
    USART1_TI_IRQn            = 52,
    USART1_TCI_IRQn           = 53,
    USART2_EI_IRQn            = 54,
    USART2_RI_IRQn            = 55,
    USART2_TI_IRQn            = 56,
    USART2_TCI_IRQn           = 57,
    USART3_EI_IRQn            = 58,
    USART3_RI_IRQn            = 59,
    USART3_TI_IRQn            = 60,
    USART3_TCI_IRQn           = 61,
    USART4_EI_IRQn            = 62,
    USART4_RI_IRQn            = 63,
    USART4_TI_IRQn            = 64,
    USART4_TCI_IRQn           = 65,
    SPI_SPRI_IRQn             = 66,
    SPI_SPTI_IRQn             = 67,
    SPI_SPII_IRQn             = 68,
    SPI_SPEI_IRQn             = 69,
    TMR4_GCMUH_IRQn           = 70,
    TMR4_GCMUL_IRQn           = 71,
    TMR4_GCMVH_IRQn           = 72,
    TMR4_GCMVL_IRQn           = 73,
    TMR4_GCMWH_IRQn           = 74,
    TMR4_GCMWL_IRQn           = 75,
    TMR4_GOVF_IRQn            = 76,
    TMR4_GUDF_IRQn            = 77,
    TMR4_RLOU_IRQn            = 78,
    TMR4_RLOV_IRQn            = 79,
    TMR4_RLOW_IRQn            = 80,
    EMB_IRQn                  = 81,
    CMP1_IRQn                 = 82,
    CMP2_IRQn                 = 83,
    CMP3_IRQn                 = 84,
    I2C_RXI_IRQn              = 85,
    I2C_TXI_IRQn              = 86,
    I2C_TEI_IRQn              = 87,
    I2C_EEI_IRQn              = 88,
    USART1_WUPI_IRQn          = 89,
    LVD1_IRQn                 = 90,
    LVD2_IRQn                 = 91,
    FCM_FERRI_IRQn            = 92,
    FCM_MENDI_IRQn            = 93,
    FCM_COVFI_IRQn            = 94,
    WDT_IRQn                  = 95,
    CTC_ERR_IRQn              = 96,
    ADC_EOCA_IRQn             = 97,
    ADC_EOCB_IRQn             = 98,
    ADC_CHCMP_IRQn            = 99,
    ADC_SEQCMP_IRQn           = 100,

} IRQn_Type;

#include <core_cm4.h>
#include <stdint.h>

/**
 *******************************************************************************
 ** \brief Event number enumeration
 ******************************************************************************/
typedef enum
{
    EVT_SWINT_IRQ0            = 0U,
    EVT_SWINT_IRQ1            = 1U,
    EVT_SWINT_IRQ2            = 2U,
    EVT_SWINT_IRQ3            = 3U,
    EVT_SWINT_IRQ4            = 4U,
    EVT_SWINT_IRQ5            = 5U,
    EVT_SWINT_IRQ6            = 6U,
    EVT_SWINT_IRQ7            = 7U,
    EVT_SWINT_IRQ8            = 8U,
    EVT_SWINT_IRQ9            = 9U,
    EVT_SWINT_IRQ10           = 10U,
    EVT_SWINT_IRQ11           = 11U,
    EVT_SWINT_IRQ12           = 12U,
    EVT_SWINT_IRQ13           = 13U,
    EVT_SWINT_IRQ14           = 14U,
    EVT_SWINT_IRQ15           = 15U,

    /* External Interrupt */
    EVT_PORT_EIRQ0            = 0U,
    EVT_PORT_EIRQ1            = 1U,
    EVT_PORT_EIRQ2            = 2U,
    EVT_PORT_EIRQ3            = 3U,
    EVT_PORT_EIRQ4            = 4U,
    EVT_PORT_EIRQ5            = 5U,
    EVT_PORT_EIRQ6            = 6U,
    EVT_PORT_EIRQ7            = 7U,

    /*  DMA  */
    EVT_DMA_TC0               = 32U,
    EVT_DMA_TC1               = 33U,
    EVT_DMA_TC2               = 34U,
    EVT_DMA_TC3               = 35U,

    EVT_DMA_BTC0              = 40U,
    EVT_DMA_BTC1              = 41U,
    EVT_DMA_BTC2              = 42U,
    EVT_DMA_BTC3              = 43U,

    /* EFM  */
    EVT_EFM_OPTEND            = 52U,

    /* DCU  */
    EVT_DCU                   = 55U,

    /* TMR0  */
    EVT_TMR0_1_GCMA           = 64U,
    EVT_TMR0_1_GCMB           = 65U,
    EVT_TMR0_2_GCMA           = 66U,
    EVT_TMR0_2_GCMB           = 67U,

    /* TMRA */
    EVT_TMRA_1_OVF            = 256U,
    EVT_TMRA_1_UDF            = 257U,
    EVT_TMRA_1_CMP            = 258U,
    EVT_TMRA_2_OVF            = 259U,
    EVT_TMRA_2_UDF            = 260U,
    EVT_TMRA_2_CMP            = 261U,
    EVT_TMRA_3_OVF            = 262U,
    EVT_TMRA_3_UDF            = 263U,
    EVT_TMRA_3_CMP            = 264U,
    EVT_TMRA_4_OVF            = 265U,
    EVT_TMRA_4_UDF            = 266U,
    EVT_TMRA_4_CMP            = 267U,

    /* TMRB */
    EVT_TMRB_OVF              = 274U,
    EVT_TMRB_UDF              = 275U,
    EVT_TMRB_CMP              = 276U,

    /* USART */
    EVT_USART1_EI             = 278U,
    EVT_USART1_RI             = 279U,
    EVT_USART1_TI             = 280U,
    EVT_USART1_TCI            = 281U,
    EVT_USART2_EI             = 283U,
    EVT_USART2_RI             = 284U,
    EVT_USART2_TI             = 285U,
    EVT_USART2_TCI            = 286U,
    EVT_USART3_EI             = 288U,
    EVT_USART3_RI             = 289U,
    EVT_USART3_TI             = 290U,
    EVT_USART3_TCI            = 291U,
    EVT_USART4_EI             = 293U,
    EVT_USART4_RI             = 294U,
    EVT_USART4_TI             = 295U,
    EVT_USART4_TCI            = 296U,

    /* SPI */
    EVT_SPI_SPRI              = 299U,
    EVT_SPI_SPTI              = 300U,
    EVT_SPI_SPII              = 301U,
    EVT_SPI_SPEI              = 302U,
    EVT_SPI_SPTEND            = 303U,

    /* AOS */
    EVT_AOS_STRG              = 319U,

    /* TMR4 */
    EVT_TMR4_SCMUH            = 368U,
    EVT_TMR4_SCMUL            = 369U,
    EVT_TMR4_SCMVH            = 370U,
    EVT_TMR4_SCMVL            = 371U,
    EVT_TMR4_SCMWH            = 372U,
    EVT_TMR4_SCMWL            = 373U,

    /* ACMP */
    EVT_CMP1                  = 416U,
    EVT_CMP2                  = 417U,
    EVT_CMP3                  = 418U,

    /* I2C */
    EVT_I2C_RXI               = 420U,
    EVT_I2C_TXI               = 421U,
    EVT_I2C_TEI               = 422U,
    EVT_I2C_EE1               = 423U,

    /* LVD */
    EVT_LVD1                  = 433U,
    EVT_LVD2                  = 434U,

    /* WDT */
    EVT_WDT_REFUDF            = 439U,

    /* ADC */
    EVT_ADC_EOCA              = 448U,
    EVT_ADC_EOCB              = 449U,
    EVT_ADC_CHCMP             = 450U,
    EVT_ADC_SEQCMP            = 451U,
    EVT_MAX                   = 511U,
} en_event_src_t;

/**
 *******************************************************************************
 ** \brief Interrupt number enumeration
 ******************************************************************************/
typedef enum
{
    INT_SWINT_IRQ0            = 0U,
    INT_SWINT_IRQ1            = 1U,
    INT_SWINT_IRQ2            = 2U,
    INT_SWINT_IRQ3            = 3U,
    INT_SWINT_IRQ4            = 4U,
    INT_SWINT_IRQ5            = 5U,
    INT_SWINT_IRQ6            = 6U,
    INT_SWINT_IRQ7            = 7U,
    INT_SWINT_IRQ8            = 8U,
    INT_SWINT_IRQ9            = 9U,
    INT_SWINT_IRQ10           = 10U,
    INT_SWINT_IRQ11           = 11U,
    INT_SWINT_IRQ12           = 12U,
    INT_SWINT_IRQ13           = 13U,
    INT_SWINT_IRQ14           = 14U,
    INT_SWINT_IRQ15           = 15U,

    /* External Interrupt */
    INT_PORT_EIRQ0            = 0U,
    INT_PORT_EIRQ1            = 1U,
    INT_PORT_EIRQ2            = 2U,
    INT_PORT_EIRQ3            = 3U,
    INT_PORT_EIRQ4            = 4U,
    INT_PORT_EIRQ5            = 5U,
    INT_PORT_EIRQ6            = 6U,
    INT_PORT_EIRQ7            = 7U,

    /* DMA */
    INT_DMA_TC0               = 32U,
    INT_DMA_TC1               = 33U,
    INT_DMA_TC2               = 34U,
    INT_DMA_TC3               = 35U,

    INT_DMA_BTC0              = 40U,
    INT_DMA_BTC1              = 41U,
    INT_DMA_BTC2              = 42U,
    INT_DMA_BTC3              = 43U,
    INT_DMA_ERR               = 48U,

    /* EFM */
    INT_EFM_PEERR             = 50U,
    INT_EFM_COLERR            = 51U,
    INT_EFM_OPTEND            = 52U,

    /* DCU */
    INT_DCU                   = 55U,

    /* TMR0 */
    INT_TMR0_1_GCMA           = 64U,
    INT_TMR0_1_GCMB           = 65U,
    INT_TMR0_2_GCMA           = 66U,
    INT_TMR0_2_GCMB           = 67U,

    /* XTAL */
    INT_XTAL_STOP             = 85U,

    /* SWDT */
    INT_SWDT_REFUDF           = 87U,

    /* TMRA */
    INT_TMRA_1_OVF            = 256U,
    INT_TMRA_1_UDF            = 257U,
    INT_TMRA_1_CMP            = 258U,
    INT_TMRA_2_OVF            = 259U,
    INT_TMRA_2_UDF            = 260U,
    INT_TMRA_2_CMP            = 261U,
    INT_TMRA_3_OVF            = 262U,
    INT_TMRA_3_UDF            = 263U,
    INT_TMRA_3_CMP            = 264U,
    INT_TMRA_4_OVF            = 265U,
    INT_TMRA_4_UDF            = 266U,
    INT_TMRA_4_CMP            = 267U,

    /* TMRB */
    INT_TMRB_OVF              = 274U,
    INT_TMRB_UDF              = 275U,
    INT_TMRB_CMP              = 276U,

    /* USART */
    INT_USART1_EI             = 278U,
    INT_USART1_RI             = 279U,
    INT_USART1_TI             = 280U,
    INT_USART1_TCI            = 281U,
    INT_USART2_EI             = 283U,
    INT_USART2_RI             = 284U,
    INT_USART2_TI             = 285U,
    INT_USART2_TCI            = 286U,
    INT_USART3_EI             = 288U,
    INT_USART3_RI             = 289U,
    INT_USART3_TI             = 290U,
    INT_USART3_TCI            = 291U,
    INT_USART4_EI             = 293U,
    INT_USART4_RI             = 294U,
    INT_USART4_TI             = 295U,
    INT_USART4_TCI            = 296U,

    /* SPI */
    INT_SPI_SPRI              = 299U,
    INT_SPI_SPTI              = 300U,
    INT_SPI_SPII              = 301U,
    INT_SPI_SPEI              = 302U,

    /* TMR4 */
    INT_TMR4_GCMUH            = 320U,
    INT_TMR4_GCMUL            = 321U,
    INT_TMR4_GCMVH            = 322U,
    INT_TMR4_GCMVL            = 323U,
    INT_TMR4_GCMWH            = 324U,
    INT_TMR4_GCMWL            = 325U,
    INT_TMR4_GOVF             = 326U,
    INT_TMR4_GUDF             = 327U,
    INT_TMR4_RLOU             = 328U,
    INT_TMR4_RLOV             = 329U,
    INT_TMR4_RLOW             = 330U,

    /* EMB */
    INT_EMB                   = 390U,

    /* ACMP */
    INT_CMP1                  = 416U,
    INT_CMP2                  = 417U,
    INT_CMP3                  = 418U,

    /* I2C */
    INT_I2C_RXI               = 420U,
    INT_I2C_TXI               = 421U,
    INT_I2C_TEI               = 422U,
    INT_I2C_EE1               = 423U,

    /* USART1 wakeup */
    INT_USART1_WUPI           = 432U,

    /* LVD */
    INT_LVD1                  = 433U,
    INT_LVD2                  = 434U,

    /* FCM */
    INT_FCM_FERRI             = 436U,
    INT_FCM_MENDI             = 437U,
    INT_FCM_COVFI             = 438U,

    /* WDT */
    INT_WDT_REFUDF            = 439U,

    /* CTC */
    INT_CTC_ERR               = 440U,

    /* ADC */
    INT_ADC_EOCA              = 448U,
    INT_ADC_EOCB              = 449U,
    INT_ADC_CHCMP             = 450U,
    INT_ADC_SEQCMP            = 451U,
    INT_MAX                   = 511U,
} en_int_src_t;

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/
/**
 * @brief ADC
 */
typedef struct
{
    __IO uint8_t  STR;
    uint8_t RESERVED0[1];
    __IO uint16_t CR0;
    __IO uint16_t CR1;
    uint8_t RESERVED1[4];
    __IO uint16_t TRGSR;
    __IO uint16_t CHSELRA0;
    uint8_t RESERVED2[2];
    __IO uint16_t CHSELRB0;
    uint8_t RESERVED3[2];
    __IO uint16_t AVCHSELR0;
    uint8_t RESERVED4[2];
    __IO uint8_t  EXCHSELR;
    uint8_t RESERVED5[1];
    __IO uint16_t SHCR;
    uint8_t RESERVED6[4];
    __IO uint8_t  SSTR0;
    __IO uint8_t  SSTR1;
    __IO uint8_t  SSTR2;
    __IO uint8_t  SSTR3;
    __IO uint8_t  SSTR4;
    __IO uint8_t  SSTR5;
    __IO uint8_t  SSTR6;
    __IO uint8_t  SSTR7;
    __IO uint8_t  SSTR8;
    __IO uint8_t  SSTR9;
    uint8_t RESERVED7[26];
    __IO uint8_t  ISR;
    __IO uint8_t  ICR;
    __IO uint8_t  ISCLRR;
    uint8_t RESERVED8[9];
    __IO uint16_t DR0;
    __IO uint16_t DR1;
    __IO uint16_t DR2;
    __IO uint16_t DR3;
    __IO uint16_t DR4;
    __IO uint16_t DR5;
    __IO uint16_t DR6;
    __IO uint16_t DR7;
    __IO uint16_t DR8;
    __IO uint16_t DR9;
} CM_ADC_TypeDef;

/**
 * @brief AOS
 */
typedef struct
{
    __IO uint32_t INTC_STRGCR;
    uint8_t RESERVED0[28];
    __IO uint32_t TMR00_HTSSR;
    __IO uint32_t TMR01_HTSSR;
    uint8_t RESERVED1[24];
    __IO uint32_t TMRA0_HTSSR;
    __IO uint32_t TMRA1_HTSSR;
    uint8_t RESERVED2[8];
    __IO uint32_t TMRB_HTSSR;
    uint8_t RESERVED3[12];
    __IO uint32_t ADC_ITRGSELR0;
    __IO uint32_t ADC_ITRGSELR1;
    uint8_t RESERVED4[24];
    __IO uint32_t DMA0_TRGSEL;
    __IO uint32_t DMA1_TRGSEL;
    __IO uint32_t DMA2_TRGSEL;
    __IO uint32_t DMA3_TRGSEL;
    __IO uint32_t DCU_TRGSEL;
} CM_AOS_TypeDef;

/**
 * @brief CMP
 */
typedef struct
{
    __IO uint8_t  MDR;
    __IO uint8_t  FIR;
    __IO uint8_t  OCR;
    __IO uint8_t  VSR;
    __IO uint8_t  TWR1;
    __IO uint8_t  TWR2;
} CM_CMP_TypeDef;

/**
 * @brief CMU
 */
typedef struct
{
    __IO uint8_t  ADCKSEL;
    uint8_t RESERVED0[3];
    __IO uint8_t  XTALSTDSR;
    uint8_t RESERVED1[3];
    __IO uint32_t SCFGR;
    __IO uint8_t  CKSWR;
    uint8_t RESERVED2[3];
    __IO uint8_t  XTALCR;
    uint8_t RESERVED3[3];
    __IO uint8_t  XTALCFGR;
    __IO uint8_t  XTALSTBCR;
    uint8_t RESERVED4[2];
    __IO uint8_t  HRCCR;
    uint8_t RESERVED5[7];
    __IO uint8_t  OSCSTBSR;
    uint8_t RESERVED6[3];
    __IO uint8_t  MCOCFGR;
    uint8_t RESERVED7[3];
    __IO uint8_t  XTALSTDCR;
    uint8_t RESERVED8[7];
    __IO uint32_t FCG;
    uint8_t RESERVED9[8];
    __IO uint8_t  LRCCR;
    uint8_t RESERVED10[3];
    __IO uint8_t  MRCCR;
    uint8_t RESERVED11[3];
    __IO uint32_t PLLCFGR;
    __IO uint8_t  PLLCR;
    uint8_t RESERVED12[3];
    __IO uint8_t  TPIUCKCFGR;
} CM_CMU_TypeDef;

/**
 * @brief CRC
 */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t RESLT;
    uint8_t RESERVED0[120];
    __IO uint32_t DAT0;
    __IO uint32_t DAT1;
    __IO uint32_t DAT2;
    __IO uint32_t DAT3;
    __IO uint32_t DAT4;
    __IO uint32_t DAT5;
    __IO uint32_t DAT6;
    __IO uint32_t DAT7;
    __IO uint32_t DAT8;
    __IO uint32_t DAT9;
    __IO uint32_t DAT10;
    __IO uint32_t DAT11;
    __IO uint32_t DAT12;
    __IO uint32_t DAT13;
    __IO uint32_t DAT14;
    __IO uint32_t DAT15;
    __IO uint32_t DAT16;
    __IO uint32_t DAT17;
    __IO uint32_t DAT18;
    __IO uint32_t DAT19;
    __IO uint32_t DAT20;
    __IO uint32_t DAT21;
    __IO uint32_t DAT22;
    __IO uint32_t DAT23;
    __IO uint32_t DAT24;
    __IO uint32_t DAT25;
    __IO uint32_t DAT26;
    __IO uint32_t DAT27;
    __IO uint32_t DAT28;
    __IO uint32_t DAT29;
    __IO uint32_t DAT30;
    __IO uint32_t DAT31;
} CM_CRC_TypeDef;

/**
 * @brief CTC
 */
typedef struct
{
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t STR;
} CM_CTC_TypeDef;

/**
 * @brief DAC
 */
typedef struct
{
    __IO uint16_t DADR1;
    uint8_t RESERVED0[6];
    __IO uint16_t DACR1;
    uint8_t RESERVED1[2];
    __IO uint16_t DADC1;
} CM_DAC_TypeDef;

/**
 * @brief DBGC
 */
typedef struct
{
    uint8_t RESERVED0[28];
    __IO uint32_t MCUDBGSTAT;
    __IO uint32_t MCUSTPCTL;
    __IO uint32_t MCUTRACECTL;
} CM_DBGC_TypeDef;

/**
 * @brief DCU
 */
typedef struct
{
    __IO uint32_t CTL;
    __IO uint32_t FLAG;
    __IO uint32_t DATA0;
    __IO uint32_t DATA1;
    __IO uint32_t DATA2;
    __IO uint32_t FLAGCLR;
    __IO uint32_t INTSEL;
} CM_DCU_TypeDef;

/**
 * @brief DMA
 */
typedef struct
{
    __IO uint32_t EN;
    __IO uint32_t INTSTAT0;
    __IO uint32_t INTSTAT1;
    __IO uint32_t INTMASK0;
    __IO uint32_t INTMASK1;
    __IO uint32_t INTCLR0;
    __IO uint32_t INTCLR1;
    __IO uint32_t CHEN;
    uint8_t RESERVED0[4];
    __IO uint32_t CHSTAT;
    uint8_t RESERVED1[8];
    __IO uint32_t RAM_LLP;
    __IO uint32_t ROM_LLP;
    __IO uint32_t CHENCLR;
    uint8_t RESERVED2[4];
    __IO uint32_t SAR0;
    __IO uint32_t DAR0;
    __IO uint32_t CH0CTL0;
    __IO uint32_t CH0CTL1;
    uint8_t RESERVED3[48];
    __IO uint32_t SAR1;
    __IO uint32_t DAR1;
    __IO uint32_t CH1CTL0;
    __IO uint32_t CH1CTL1;
    uint8_t RESERVED4[48];
    __IO uint32_t SAR2;
    __IO uint32_t DAR2;
    __IO uint32_t CH2CTL0;
    __IO uint32_t CH2CTL1;
    uint8_t RESERVED5[48];
    __IO uint32_t SAR3;
    __IO uint32_t DAR3;
    __IO uint32_t CH3CTL0;
    __IO uint32_t CH3CTL1;
} CM_DMA_TypeDef;

/**
 * @brief EFM
 */
typedef struct
{
    __IO uint32_t FAPRT;
    __IO uint32_t FSTP;
    __IO uint32_t FRMC;
    __IO uint32_t FWMC;
    __IO uint32_t FSR;
    __IO uint32_t FSCLR;
    __IO uint32_t FITE;
    uint8_t RESERVED0[4];
    __IO uint32_t FPMTSW;
    __IO uint32_t FPMTEW;
    uint8_t RESERVED1[40];
    __IO uint32_t UQID0;
    __IO uint32_t UQID1;
    __IO uint32_t UQID2;
    __IO uint32_t UQID3;
    uint8_t RESERVED2[546];
    __IO uint8_t  HRCCFGR;
} CM_EFM_TypeDef;

/**
 * @brief EMB
 */
typedef struct
{
    __IO uint32_t CTL;
    __IO uint32_t PWMLV;
    __IO uint32_t SOE;
    __IO uint32_t STAT;
    __IO uint32_t STATCLR;
    __IO uint32_t INTEN;
    __IO uint32_t ECSR;
} CM_EMB_TypeDef;

/**
 * @brief FCM
 */
typedef struct
{
    __IO uint32_t LVR;
    __IO uint32_t UVR;
    __IO uint32_t CNTR;
    __IO uint32_t STR;
    __IO uint32_t MCCR;
    __IO uint32_t RCCR;
    __IO uint32_t RIER;
    __IO uint32_t SR;
    __IO uint32_t CLR;
} CM_FCM_TypeDef;

/**
 * @brief GPIO
 */
typedef struct
{
    __IO uint8_t  PIDR0;
    __IO uint8_t  PIDR1;
    __IO uint8_t  PIDR2;
    __IO uint8_t  PIDR3;
    __IO uint8_t  PIDR4;
    __IO uint8_t  PIDR5;
    uint8_t RESERVED0[1];
    __IO uint8_t  PIDR7;
    uint8_t RESERVED1[1];
    __IO uint8_t  PIDR9;
    __IO uint8_t  PIDRA;
    __IO uint8_t  PIDRB;
    uint8_t RESERVED2[1];
    __IO uint8_t  PIDRD;
    __IO uint8_t  PIDRE;
    uint8_t RESERVED3[1];
    __IO uint8_t  PODR0;
    __IO uint8_t  PODR1;
    __IO uint8_t  PODR2;
    __IO uint8_t  PODR3;
    __IO uint8_t  PODR4;
    __IO uint8_t  PODR5;
    uint8_t RESERVED4[1];
    __IO uint8_t  PODR7;
    uint8_t RESERVED5[1];
    __IO uint8_t  PODR9;
    __IO uint8_t  PODRA;
    __IO uint8_t  PODRB;
    uint8_t RESERVED6[1];
    __IO uint8_t  PODRD;
    __IO uint8_t  PODRE;
    uint8_t RESERVED7[1];
    __IO uint8_t  POER0;
    __IO uint8_t  POER1;
    __IO uint8_t  POER2;
    __IO uint8_t  POER3;
    __IO uint8_t  POER4;
    __IO uint8_t  POER5;
    uint8_t RESERVED8[1];
    __IO uint8_t  POER7;
    uint8_t RESERVED9[1];
    __IO uint8_t  POER9;
    __IO uint8_t  POERA;
    __IO uint8_t  POERB;
    uint8_t RESERVED10[1];
    __IO uint8_t  POERD;
    __IO uint8_t  POERE;
    uint8_t RESERVED11[1];
    __IO uint8_t  POSR0;
    __IO uint8_t  POSR1;
    __IO uint8_t  POSR2;
    __IO uint8_t  POSR3;
    __IO uint8_t  POSR4;
    __IO uint8_t  POSR5;
    uint8_t RESERVED12[1];
    __IO uint8_t  POSR7;
    uint8_t RESERVED13[1];
    __IO uint8_t  POSR9;
    __IO uint8_t  POSRA;
    __IO uint8_t  POSRB;
    uint8_t RESERVED14[1];
    __IO uint8_t  POSRD;
    __IO uint8_t  POSRE;
    uint8_t RESERVED15[1];
    __IO uint8_t  PORR0;
    __IO uint8_t  PORR1;
    __IO uint8_t  PORR2;
    __IO uint8_t  PORR3;
    __IO uint8_t  PORR4;
    __IO uint8_t  PORR5;
    uint8_t RESERVED16[1];
    __IO uint8_t  PORR7;
    uint8_t RESERVED17[1];
    __IO uint8_t  PORR9;
    __IO uint8_t  PORRA;
    __IO uint8_t  PORRB;
    uint8_t RESERVED18[1];
    __IO uint8_t  PORRD;
    __IO uint8_t  PORRE;
    uint8_t RESERVED19[1];
    __IO uint8_t  POTR0;
    __IO uint8_t  POTR1;
    __IO uint8_t  POTR2;
    __IO uint8_t  POTR3;
    __IO uint8_t  POTR4;
    __IO uint8_t  POTR5;
    uint8_t RESERVED20[1];
    __IO uint8_t  POTR7;
    uint8_t RESERVED21[1];
    __IO uint8_t  POTR9;
    __IO uint8_t  POTRA;
    __IO uint8_t  POTRB;
    uint8_t RESERVED22[1];
    __IO uint8_t  POTRD;
    __IO uint8_t  POTRE;
    uint8_t RESERVED23[673];
    __IO uint16_t PSPCR;
    uint8_t RESERVED24[2];
    __IO uint16_t PCCR;
    __IO uint16_t PINAER;
    __IO uint16_t PWPR;
    uint8_t RESERVED25[246];
    __IO uint16_t PCR00;
    __IO uint16_t PFSR00;
    __IO uint16_t PCR01;
    __IO uint16_t PFSR01;
    __IO uint16_t PCR02;
    __IO uint16_t PFSR02;
    uint8_t RESERVED26[20];
    __IO uint16_t PCR10;
    __IO uint16_t PFSR10;
    __IO uint16_t PCR11;
    __IO uint16_t PFSR11;
    uint8_t RESERVED27[32];
    __IO uint16_t PCR22;
    __IO uint16_t PFSR22;
    __IO uint16_t PCR23;
    __IO uint16_t PFSR23;
    __IO uint16_t PCR24;
    __IO uint16_t PFSR24;
    uint8_t RESERVED28[12];
    __IO uint16_t PCR30;
    __IO uint16_t PFSR30;
    __IO uint16_t PCR31;
    __IO uint16_t PFSR31;
    __IO uint16_t PCR32;
    __IO uint16_t PFSR32;
    __IO uint16_t PCR33;
    __IO uint16_t PFSR33;
    uint8_t RESERVED29[8];
    __IO uint16_t PCR36;
    __IO uint16_t PFSR36;
    __IO uint16_t PCR37;
    __IO uint16_t PFSR37;
    __IO uint16_t PCR40;
    __IO uint16_t PFSR40;
    __IO uint16_t PCR41;
    __IO uint16_t PFSR41;
    __IO uint16_t PCR42;
    __IO uint16_t PFSR42;
    __IO uint16_t PCR43;
    __IO uint16_t PFSR43;
    __IO uint16_t PCR44;
    __IO uint16_t PFSR44;
    __IO uint16_t PCR45;
    __IO uint16_t PFSR45;
    __IO uint16_t PCR46;
    __IO uint16_t PFSR46;
    __IO uint16_t PCR47;
    __IO uint16_t PFSR47;
    __IO uint16_t PCR50;
    __IO uint16_t PFSR50;
    uint8_t RESERVED30[60];
    __IO uint16_t PCR70;
    __IO uint16_t PFSR70;
    __IO uint16_t PCR71;
    __IO uint16_t PFSR71;
    __IO uint16_t PCR72;
    __IO uint16_t PFSR72;
    __IO uint16_t PCR73;
    __IO uint16_t PFSR73;
    __IO uint16_t PCR74;
    __IO uint16_t PFSR74;
    __IO uint16_t PCR75;
    __IO uint16_t PFSR75;
    __IO uint16_t PCR76;
    __IO uint16_t PFSR76;
    uint8_t RESERVED31[40];
    __IO uint16_t PCR91;
    __IO uint16_t PFSR91;
    __IO uint16_t PCR92;
    __IO uint16_t PFSR92;
    __IO uint16_t PCR93;
    __IO uint16_t PFSR93;
    __IO uint16_t PCR94;
    __IO uint16_t PFSR94;
    uint8_t RESERVED32[20];
    __IO uint16_t PCRA2;
    __IO uint16_t PFSRA2;
    __IO uint16_t PCRA3;
    __IO uint16_t PFSRA3;
    __IO uint16_t PCRA4;
    __IO uint16_t PFSRA4;
    __IO uint16_t PCRA5;
    __IO uint16_t PFSRA5;
    uint8_t RESERVED33[8];
    __IO uint16_t PCRB0;
    __IO uint16_t PFSRB0;
    __IO uint16_t PCRB1;
    __IO uint16_t PFSRB1;
    __IO uint16_t PCRB2;
    __IO uint16_t PFSRB2;
    __IO uint16_t PCRB3;
    __IO uint16_t PFSRB3;
    __IO uint16_t PCRB4;
    __IO uint16_t PFSRB4;
    __IO uint16_t PCRB5;
    __IO uint16_t PFSRB5;
    __IO uint16_t PCRB6;
    __IO uint16_t PFSRB6;
    __IO uint16_t PCRB7;
    __IO uint16_t PFSRB7;
    uint8_t RESERVED34[44];
    __IO uint16_t PCRD3;
    __IO uint16_t PFSRD3;
    __IO uint16_t PCRD4;
    __IO uint16_t PFSRD4;
    __IO uint16_t PCRD5;
    __IO uint16_t PFSRD5;
    __IO uint16_t PCRD6;
    __IO uint16_t PFSRD6;
    __IO uint16_t PCRD7;
    __IO uint16_t PFSRD7;
    uint8_t RESERVED35[8];
    __IO uint16_t PCRE2;
    __IO uint16_t PFSRE2;
} CM_GPIO_TypeDef;

/**
 * @brief I2C
 */
typedef struct
{
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    uint8_t RESERVED0[8];
    __IO uint32_t SLR0;
    __IO uint32_t SLR1;
    uint8_t RESERVED1[4];
    __IO uint32_t SR;
    __IO uint32_t CLR;
    __IO uint8_t  DTR;
    uint8_t RESERVED2[3];
    __IO uint8_t  DRR;
    uint8_t RESERVED3[3];
    __IO uint32_t CCR;
    __IO uint32_t FLTR;
} CM_I2C_TypeDef;

/**
 * @brief ICG
 */
typedef struct
{
    __IO uint32_t ICG0;
    __IO uint32_t ICG1;
    __IO uint32_t ICG2;
    __IO uint32_t ICG3;
    __IO uint32_t ICG4;
    __IO uint32_t ICG5;
    __IO uint32_t ICG6;
    __IO uint32_t ICG7;
} CM_ICG_TypeDef;

/**
 * @brief INTC
 */
typedef struct
{
    __IO uint32_t NMICR;
    __IO uint32_t NMIER;
    __IO uint32_t NMIFR;
    __IO uint32_t NMICFR;
    __IO uint32_t EIRQCR0;
    __IO uint32_t EIRQCR1;
    __IO uint32_t EIRQCR2;
    __IO uint32_t EIRQCR3;
    __IO uint32_t EIRQCR4;
    __IO uint32_t EIRQCR5;
    __IO uint32_t EIRQCR6;
    __IO uint32_t EIRQCR7;
    uint8_t RESERVED0[32];
    __IO uint32_t WUPEN;
    __IO uint32_t EIRQFR;
    __IO uint32_t EIRQCFR;
    __IO uint32_t SEL0;
    __IO uint32_t SEL1;
    __IO uint32_t SEL2;
    __IO uint32_t SEL3;
    __IO uint32_t SEL4;
    __IO uint32_t SEL5;
    __IO uint32_t SEL6;
    __IO uint32_t SEL7;
    __IO uint32_t SEL8;
    __IO uint32_t SEL9;
    __IO uint32_t SEL10;
    __IO uint32_t SEL11;
    __IO uint32_t SEL12;
    __IO uint32_t SEL13;
    __IO uint32_t SEL14;
    __IO uint32_t SEL15;
    __IO uint32_t SEL16;
    __IO uint32_t SEL17;
    __IO uint32_t SEL18;
    __IO uint32_t SEL19;
    __IO uint32_t SEL20;
    __IO uint32_t SEL21;
    __IO uint32_t SEL22;
    __IO uint32_t SEL23;
    __IO uint32_t SEL24;
    __IO uint32_t SEL25;
    __IO uint32_t SEL26;
    __IO uint32_t SEL27;
    __IO uint32_t SEL28;
    __IO uint32_t SEL29;
    __IO uint32_t SEL30;
    __IO uint32_t SEL31;
    __IO uint32_t SEL32;
    __IO uint32_t SEL33;
    __IO uint32_t SEL34;
    __IO uint32_t SEL35;
    __IO uint32_t SEL36;
    __IO uint32_t SEL37;
    __IO uint32_t SEL38;
    __IO uint32_t SEL39;
    __IO uint32_t SEL40;
    __IO uint32_t SEL41;
    __IO uint32_t SEL42;
    __IO uint32_t SEL43;
    __IO uint32_t SEL44;
    __IO uint32_t SEL45;
    __IO uint32_t SEL46;
    __IO uint32_t SEL47;
    __IO uint32_t SEL48;
    __IO uint32_t SEL49;
    __IO uint32_t SEL50;
    __IO uint32_t SEL51;
    __IO uint32_t SEL52;
    __IO uint32_t SEL53;
    __IO uint32_t SEL54;
    __IO uint32_t SEL55;
    __IO uint32_t SEL56;
    __IO uint32_t SEL57;
    __IO uint32_t SEL58;
    __IO uint32_t SEL59;
    __IO uint32_t SEL60;
    __IO uint32_t SEL61;
    __IO uint32_t SEL62;
    __IO uint32_t SEL63;
    __IO uint32_t SEL64;
    __IO uint32_t SEL65;
    __IO uint32_t SEL66;
    __IO uint32_t SEL67;
    __IO uint32_t SEL68;
    __IO uint32_t SEL69;
    __IO uint32_t SEL70;
    __IO uint32_t SEL71;
    __IO uint32_t SEL72;
    __IO uint32_t SEL73;
    __IO uint32_t SEL74;
    __IO uint32_t SEL75;
    __IO uint32_t SEL76;
    __IO uint32_t SEL77;
    __IO uint32_t SEL78;
    __IO uint32_t SEL79;
    __IO uint32_t SEL80;
    __IO uint32_t SEL81;
    __IO uint32_t SEL82;
    __IO uint32_t SEL83;
    __IO uint32_t SEL84;
    __IO uint32_t SEL85;
    __IO uint32_t SEL86;
    __IO uint32_t SEL87;
    __IO uint32_t SEL88;
    __IO uint32_t SEL89;
    __IO uint32_t SEL90;
    __IO uint32_t SEL91;
    __IO uint32_t SEL92;
    __IO uint32_t SEL93;
    __IO uint32_t SEL94;
    __IO uint32_t SEL95;
    __IO uint32_t SEL96;
    __IO uint32_t SEL97;
    __IO uint32_t SEL98;
    __IO uint32_t SEL99;
    __IO uint32_t SEL100;
    uint8_t RESERVED1[172];
    __IO uint32_t SWIER;
    __IO uint32_t EVTER;
    __IO uint32_t IER;
} CM_INTC_TypeDef;

/**
 * @brief PWC
 */
typedef struct
{
    __IO uint8_t  STPMCR;
    uint8_t RESERVED0[3];
    __IO uint16_t PWRC;
    uint8_t RESERVED1[2];
    __IO uint8_t  PWRMONR;
    uint8_t RESERVED2[3];
    __IO uint8_t  RAMCR;
    uint8_t RESERVED3[3];
    __IO uint32_t LVDCR0;
    __IO uint8_t  LVDCSR1;
    uint8_t RESERVED4[11];
    __IO uint16_t FPRC;
    uint8_t RESERVED5[30];
    __IO uint16_t DBGC;
} CM_PWC_TypeDef;

/**
 * @brief RMU
 */
typedef struct
{
    __IO uint16_t RSTF0;
} CM_RMU_TypeDef;

/**
 * @brief SPI
 */
typedef struct
{
    __IO uint32_t DR;
    __IO uint32_t CR1;
    uint8_t RESERVED0[4];
    __IO uint32_t CFG1;
    uint8_t RESERVED1[4];
    __IO uint32_t SR;
    __IO uint32_t CFG2;
} CM_SPI_TypeDef;

/**
 * @brief SWDT
 */
typedef struct
{
    uint8_t RESERVED0[4];
    __IO uint32_t SR;
    __IO uint32_t RR;
} CM_SWDT_TypeDef;

/**
 * @brief TMR0
 */
typedef struct
{
    __IO uint32_t CNTAR;
    __IO uint32_t CNTBR;
    __IO uint32_t CMPAR;
    __IO uint32_t CMPBR;
    __IO uint32_t BCONR;
    __IO uint32_t STFLR;
} CM_TMR0_TypeDef;

/**
 * @brief TMR4
 */
typedef struct
{
    uint8_t RESERVED0[2];
    __IO uint16_t OCCRUH;
    uint8_t RESERVED1[2];
    __IO uint16_t OCCRUL;
    uint8_t RESERVED2[2];
    __IO uint16_t OCCRVH;
    uint8_t RESERVED3[2];
    __IO uint16_t OCCRVL;
    uint8_t RESERVED4[2];
    __IO uint16_t OCCRWH;
    uint8_t RESERVED5[2];
    __IO uint16_t OCCRWL;
    __IO uint16_t OCSRU;
    __IO uint16_t OCERU;
    __IO uint16_t OCSRV;
    __IO uint16_t OCERV;
    __IO uint16_t OCSRW;
    __IO uint16_t OCERW;
    __IO uint16_t OCMRHUH;
    uint8_t RESERVED6[2];
    __IO uint32_t OCMRLUL;
    __IO uint16_t OCMRHVH;
    uint8_t RESERVED7[2];
    __IO uint32_t OCMRLVL;
    __IO uint16_t OCMRHWH;
    uint8_t RESERVED8[2];
    __IO uint32_t OCMRLWL;
    uint8_t RESERVED9[6];
    __IO uint16_t CPSR;
    uint8_t RESERVED10[2];
    __IO uint16_t CNTR;
    __IO uint16_t CCSR;
    __IO uint16_t CVPR;
    uint8_t RESERVED11[54];
    __IO uint16_t PFSRU;
    __IO uint16_t PDARU;
    __IO uint16_t PDBRU;
    uint8_t RESERVED12[2];
    __IO uint16_t PFSRV;
    __IO uint16_t PDARV;
    __IO uint16_t PDBRV;
    uint8_t RESERVED13[2];
    __IO uint16_t PFSRW;
    __IO uint16_t PDARW;
    __IO uint16_t PDBRW;
    __IO uint16_t POCRU;
    uint8_t RESERVED14[2];
    __IO uint16_t POCRV;
    uint8_t RESERVED15[2];
    __IO uint16_t POCRW;
    uint8_t RESERVED16[2];
    __IO uint16_t RCSR;
    uint8_t RESERVED17[12];
    __IO uint16_t SCCRUH;
    uint8_t RESERVED18[2];
    __IO uint16_t SCCRUL;
    uint8_t RESERVED19[2];
    __IO uint16_t SCCRVH;
    uint8_t RESERVED20[2];
    __IO uint16_t SCCRVL;
    uint8_t RESERVED21[2];
    __IO uint16_t SCCRWH;
    uint8_t RESERVED22[2];
    __IO uint16_t SCCRWL;
    __IO uint16_t SCSRUH;
    __IO uint16_t SCMRUH;
    __IO uint16_t SCSRUL;
    __IO uint16_t SCMRUL;
    __IO uint16_t SCSRVH;
    __IO uint16_t SCMRVH;
    __IO uint16_t SCSRVL;
    __IO uint16_t SCMRVL;
    __IO uint16_t SCSRWH;
    __IO uint16_t SCMRWH;
    __IO uint16_t SCSRWL;
    __IO uint16_t SCMRWL;
    __IO uint32_t PSCR;
    __IO uint16_t SCER;
} CM_TMR4_TypeDef;

/**
 * @brief TMRA
 */
typedef struct
{
    __IO uint16_t CNTER;
    uint8_t RESERVED0[2];
    __IO uint16_t PERAR;
    uint8_t RESERVED1[58];
    __IO uint16_t CMPAR1;
    uint8_t RESERVED2[2];
    __IO uint16_t CMPAR2;
    uint8_t RESERVED3[58];
    __IO uint16_t BCSTR;
    uint8_t RESERVED4[2];
    __IO uint16_t HCONR;
    uint8_t RESERVED5[2];
    __IO uint16_t HCUPR;
    uint8_t RESERVED6[2];
    __IO uint16_t HCDOR;
    uint8_t RESERVED7[2];
    __IO uint16_t ICONR;
    uint8_t RESERVED8[2];
    __IO uint16_t ECONR;
    uint8_t RESERVED9[2];
    __IO uint16_t FCONR;
    uint8_t RESERVED10[2];
    __IO uint16_t STFLR;
    uint8_t RESERVED11[34];
    __IO uint16_t BCONR;
    uint8_t RESERVED12[62];
    __IO uint16_t CCONR1;
    uint8_t RESERVED13[2];
    __IO uint16_t CCONR2;
    uint8_t RESERVED14[58];
    __IO uint16_t PCONR1;
    uint8_t RESERVED15[2];
    __IO uint16_t PCONR2;
} CM_TMRA_TypeDef;

/**
 * @brief TMRB
 */
typedef struct
{
    __IO uint16_t CNTER;
    uint8_t RESERVED0[2];
    __IO uint16_t PERAR;
    uint8_t RESERVED1[58];
    __IO uint16_t CMPAR1;
    uint8_t RESERVED2[2];
    __IO uint16_t CMPAR2;
    uint8_t RESERVED3[2];
    __IO uint16_t CMPAR3;
    uint8_t RESERVED4[2];
    __IO uint16_t CMPAR4;
    uint8_t RESERVED5[2];
    __IO uint16_t CMPAR5;
    uint8_t RESERVED6[2];
    __IO uint16_t CMPAR6;
    uint8_t RESERVED7[42];
    __IO uint16_t BCSTR;
    uint8_t RESERVED8[2];
    __IO uint16_t HCONR;
    uint8_t RESERVED9[2];
    __IO uint16_t HCUPR;
    uint8_t RESERVED10[2];
    __IO uint16_t HCDOR;
    uint8_t RESERVED11[2];
    __IO uint16_t ICONR;
    uint8_t RESERVED12[2];
    __IO uint16_t ECONR;
    uint8_t RESERVED13[6];
    __IO uint16_t STFLR;
    uint8_t RESERVED14[34];
    __IO uint16_t BCONR1;
    uint8_t RESERVED15[6];
    __IO uint16_t BCONR2;
    uint8_t RESERVED16[6];
    __IO uint16_t BCONR3;
    uint8_t RESERVED17[46];
    __IO uint16_t CCONR1;
    uint8_t RESERVED18[2];
    __IO uint16_t CCONR2;
    uint8_t RESERVED19[2];
    __IO uint16_t CCONR3;
    uint8_t RESERVED20[2];
    __IO uint16_t CCONR4;
    uint8_t RESERVED21[50];
    __IO uint16_t PCONR1;
    uint8_t RESERVED22[2];
    __IO uint16_t PCONR2;
    uint8_t RESERVED23[2];
    __IO uint16_t PCONR3;
    uint8_t RESERVED24[2];
    __IO uint16_t PCONR4;
} CM_TMRB_TypeDef;

/**
 * @brief USART
 */
typedef struct
{
    __IO uint32_t SR;
    __IO uint32_t DR;
    __IO uint32_t BRR;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t CR3;
    __IO uint32_t PR;
} CM_USART_TypeDef;

/**
 * @brief WDT
 */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t SR;
    __IO uint32_t RR;
} CM_WDT_TypeDef;



/******************************************************************************/
/*           Device Specific Peripheral declaration & memory map              */
/******************************************************************************/

#define CM_ADC                               ((CM_ADC_TypeDef *)0x40030000UL)
#define CM_AOS                               ((CM_AOS_TypeDef *)0x40010800UL)
#define CM_CMP1                              ((CM_CMP_TypeDef *)0x4004A000UL)
#define CM_CMP2                              ((CM_CMP_TypeDef *)0x4004A010UL)
#define CM_CMP3                              ((CM_CMP_TypeDef *)0x4004A020UL)
#define CM_CMU                               ((CM_CMU_TypeDef *)0x40054400UL)
#define CM_CRC                               ((CM_CRC_TypeDef *)0x40050400UL)
#define CM_CTC                               ((CM_CTC_TypeDef *)0x40010000UL)
#define CM_DAC                               ((CM_DAC_TypeDef *)0x4004A100UL)
#define CM_DBGC                              ((CM_DBGC_TypeDef *)0xE0042000UL)
#define CM_DCU                               ((CM_DCU_TypeDef *)0x40052000UL)
#define CM_DMA                               ((CM_DMA_TypeDef *)0x40053000UL)
#define CM_EFM                               ((CM_EFM_TypeDef *)0x40010400UL)
#define CM_EMB0                              ((CM_EMB_TypeDef *)0x40017C00UL)
#define CM_EMB1                              ((CM_EMB_TypeDef *)0x40017C20UL)
#define CM_FCM                               ((CM_FCM_TypeDef *)0x40048400UL)
#define CM_GPIO                              ((CM_GPIO_TypeDef *)0x40053800UL)
#define CM_I2C                               ((CM_I2C_TypeDef *)0x4004E000UL)
#define CM_ICG                               ((CM_ICG_TypeDef *)0x00000240UL)
#define CM_INTC                              ((CM_INTC_TypeDef *)0x40051000UL)
#define CM_PWC                               ((CM_PWC_TypeDef *)0x40054000UL)
#define CM_RMU                               ((CM_RMU_TypeDef *)0x40054100UL)
#define CM_SPI                               ((CM_SPI_TypeDef *)0x4001C000UL)
#define CM_SWDT                              ((CM_SWDT_TypeDef *)0x40049400UL)
#define CM_TMR0_1                            ((CM_TMR0_TypeDef *)0x40024000UL)
#define CM_TMR0_2                            ((CM_TMR0_TypeDef *)0x40024400UL)
#define CM_TMR4                              ((CM_TMR4_TypeDef *)0x40017000UL)
#define CM_TMRA_1                            ((CM_TMRA_TypeDef *)0x40015000UL)
#define CM_TMRA_2                            ((CM_TMRA_TypeDef *)0x40015400UL)
#define CM_TMRA_3                            ((CM_TMRA_TypeDef *)0x40015800UL)
#define CM_TMRA_4                            ((CM_TMRA_TypeDef *)0x40015C00UL)
#define CM_TMRB                              ((CM_TMRB_TypeDef *)0x40025000UL)
#define CM_USART1                            ((CM_USART_TypeDef *)0x4001D000UL)
#define CM_USART2                            ((CM_USART_TypeDef *)0x4001D400UL)
#define CM_USART3                            ((CM_USART_TypeDef *)0x40021000UL)
#define CM_USART4                            ((CM_USART_TypeDef *)0x40021400UL)
#define CM_WDT                               ((CM_WDT_TypeDef *)0x40049000UL)


/******************************************************************************/
/*                   Peripheral Registers Bits Definition                     */
/******************************************************************************/

/*******************************************************************************
                Bit definition for Peripheral ADC
*******************************************************************************/
/*  Bit definition for ADC_STR register  */
#define ADC_STR_STRT                                   (0x01U)

/*  Bit definition for ADC_CR0 register  */
#define ADC_CR0_MS_POS                                 (0U)
#define ADC_CR0_MS                                     (0x0003U)
#define ADC_CR0_MS_0                                   (0x0001U)
#define ADC_CR0_MS_1                                   (0x0002U)
#define ADC_CR0_ACCSEL_POS                             (4U)
#define ADC_CR0_ACCSEL                                 (0x0030U)
#define ADC_CR0_ACCSEL_0                               (0x0010U)
#define ADC_CR0_ACCSEL_1                               (0x0020U)
#define ADC_CR0_CLREN_POS                              (6U)
#define ADC_CR0_CLREN                                  (0x0040U)
#define ADC_CR0_DFMT_POS                               (7U)
#define ADC_CR0_DFMT                                   (0x0080U)
#define ADC_CR0_AVCNT_POS                              (8U)
#define ADC_CR0_AVCNT                                  (0x0700U)
#define ADC_CR0_AVCNT_0                                (0x0100U)
#define ADC_CR0_AVCNT_1                                (0x0200U)
#define ADC_CR0_AVCNT_2                                (0x0400U)

/*  Bit definition for ADC_CR1 register  */
#define ADC_CR1_RSCHSEL_POS                            (2U)
#define ADC_CR1_RSCHSEL                                (0x0004U)

/*  Bit definition for ADC_TRGSR register  */
#define ADC_TRGSR_TRGSELA_POS                          (0U)
#define ADC_TRGSR_TRGSELA                              (0x0003U)
#define ADC_TRGSR_TRGSELA_0                            (0x0001U)
#define ADC_TRGSR_TRGSELA_1                            (0x0002U)
#define ADC_TRGSR_TRGENA_POS                           (7U)
#define ADC_TRGSR_TRGENA                               (0x0080U)
#define ADC_TRGSR_TRGSELB_POS                          (8U)
#define ADC_TRGSR_TRGSELB                              (0x0300U)
#define ADC_TRGSR_TRGSELB_0                            (0x0100U)
#define ADC_TRGSR_TRGSELB_1                            (0x0200U)
#define ADC_TRGSR_TRGENB_POS                           (15U)
#define ADC_TRGSR_TRGENB                               (0x8000U)

/*  Bit definition for ADC_CHSELRA0 register  */
#define ADC_CHSELRA0_CHSELA                            (0x03FFU)

/*  Bit definition for ADC_CHSELRB0 register  */
#define ADC_CHSELRB0_CHSELB                            (0x03FFU)

/*  Bit definition for ADC_AVCHSELR0 register  */
#define ADC_AVCHSELR0_AVCHSEL                          (0x03FFU)

/*  Bit definition for ADC_EXCHSELR register  */
#define ADC_EXCHSELR_EXCHSEL                           (0x01U)

/*  Bit definition for ADC_SHCR register  */
#define ADC_SHCR_SHT_POS                               (0U)
#define ADC_SHCR_SHT                                   (0x00FFU)
#define ADC_SHCR_SHSEL_POS                             (8U)
#define ADC_SHCR_SHSEL                                 (0x0700U)
#define ADC_SHCR_SHMD_POS                              (15U)
#define ADC_SHCR_SHMD                                  (0x8000U)

/*  Bit definition for ADC_SSTR0 register  */
#define ADC_SSTR0                                      (0xFFU)

/*  Bit definition for ADC_SSTR1 register  */
#define ADC_SSTR1                                      (0xFFU)

/*  Bit definition for ADC_SSTR2 register  */
#define ADC_SSTR2                                      (0xFFU)

/*  Bit definition for ADC_SSTR3 register  */
#define ADC_SSTR3                                      (0xFFU)

/*  Bit definition for ADC_SSTR4 register  */
#define ADC_SSTR4                                      (0xFFU)

/*  Bit definition for ADC_SSTR5 register  */
#define ADC_SSTR5                                      (0xFFU)

/*  Bit definition for ADC_SSTR6 register  */
#define ADC_SSTR6                                      (0xFFU)

/*  Bit definition for ADC_SSTR7 register  */
#define ADC_SSTR7                                      (0xFFU)

/*  Bit definition for ADC_SSTR8 register  */
#define ADC_SSTR8                                      (0xFFU)

/*  Bit definition for ADC_SSTR9 register  */
#define ADC_SSTR9                                      (0xFFU)

/*  Bit definition for ADC_ISR register  */
#define ADC_ISR_EOCAF_POS                              (0U)
#define ADC_ISR_EOCAF                                  (0x01U)
#define ADC_ISR_EOCBF_POS                              (1U)
#define ADC_ISR_EOCBF                                  (0x02U)
#define ADC_ISR_SASTPDF_POS                            (4U)
#define ADC_ISR_SASTPDF                                (0x10U)

/*  Bit definition for ADC_ICR register  */
#define ADC_ICR_EOCAIEN_POS                            (0U)
#define ADC_ICR_EOCAIEN                                (0x01U)
#define ADC_ICR_EOCBIEN_POS                            (1U)
#define ADC_ICR_EOCBIEN                                (0x02U)

/*  Bit definition for ADC_ISCLRR register  */
#define ADC_ISCLRR_CLREOCAF_POS                        (0U)
#define ADC_ISCLRR_CLREOCAF                            (0x01U)
#define ADC_ISCLRR_CLREOCBF_POS                        (1U)
#define ADC_ISCLRR_CLREOCBF                            (0x02U)
#define ADC_ISCLRR_CLRSASTPDF_POS                      (4U)
#define ADC_ISCLRR_CLRSASTPDF                          (0x10U)

/*  Bit definition for ADC_DR0 register  */
#define ADC_DR0                                        (0xFFFFU)

/*  Bit definition for ADC_DR1 register  */
#define ADC_DR1                                        (0xFFFFU)

/*  Bit definition for ADC_DR2 register  */
#define ADC_DR2                                        (0xFFFFU)

/*  Bit definition for ADC_DR3 register  */
#define ADC_DR3                                        (0xFFFFU)

/*  Bit definition for ADC_DR4 register  */
#define ADC_DR4                                        (0xFFFFU)

/*  Bit definition for ADC_DR5 register  */
#define ADC_DR5                                        (0xFFFFU)

/*  Bit definition for ADC_DR6 register  */
#define ADC_DR6                                        (0xFFFFU)

/*  Bit definition for ADC_DR7 register  */
#define ADC_DR7                                        (0xFFFFU)

/*  Bit definition for ADC_DR8 register  */
#define ADC_DR8                                        (0xFFFFU)

/*  Bit definition for ADC_DR9 register  */
#define ADC_DR9                                        (0xFFFFU)

/*******************************************************************************
                Bit definition for Peripheral AOS
*******************************************************************************/
/*  Bit definition for AOS_INTC_STRGCR register  */
#define AOS_INTC_STRGCR_STRG                           (0x00000001UL)

/*  Bit definition for AOS_TMR00_HTSSR register  */
#define AOS_TMR00_HTSSR_TRGSEL                         (0x000001FFUL)

/*  Bit definition for AOS_TMR01_HTSSR register  */
#define AOS_TMR01_HTSSR_TRGSEL                         (0x000001FFUL)

/*  Bit definition for AOS_TMRA0_HTSSR register  */
#define AOS_TMRA0_HTSSR_TRGSEL                         (0x000001FFUL)

/*  Bit definition for AOS_TMRA1_HTSSR register  */
#define AOS_TMRA1_HTSSR_TRGSEL                         (0x000001FFUL)

/*  Bit definition for AOS_TMRB_HTSSR register  */
#define AOS_TMRB_HTSSR_TRGSEL                          (0x000001FFUL)

/*  Bit definition for AOS_ADC_ITRGSELR0 register  */
#define AOS_ADC_ITRGSELR0_TRGSEL                       (0x000001FFUL)

/*  Bit definition for AOS_ADC_ITRGSELR1 register  */
#define AOS_ADC_ITRGSELR1_TRGSEL                       (0x000001FFUL)

/*  Bit definition for AOS_DMA0_TRGSEL register  */
#define AOS_DMA0_TRGSEL_TRGSEL                         (0x000001FFUL)

/*  Bit definition for AOS_DMA1_TRGSEL register  */
#define AOS_DMA1_TRGSEL_TRGSEL                         (0x000001FFUL)

/*  Bit definition for AOS_DMA2_TRGSEL register  */
#define AOS_DMA2_TRGSEL_TRGSEL                         (0x000001FFUL)

/*  Bit definition for AOS_DMA3_TRGSEL register  */
#define AOS_DMA3_TRGSEL_TRGSEL                         (0x000001FFUL)

/*  Bit definition for AOS_DCU_TRGSEL register  */
#define AOS_DCU_TRGSEL_TRGSEL                          (0x000001FFUL)

/*******************************************************************************
                Bit definition for Peripheral CMP
*******************************************************************************/
/*  Bit definition for CMP_MDR register  */
#define CMP_MDR_CENB_POS                               (0U)
#define CMP_MDR_CENB                                   (0x01U)
#define CMP_MDR_CWDE_POS                               (1U)
#define CMP_MDR_CWDE                                   (0x02U)
#define CMP_MDR_CMON_POS                               (7U)
#define CMP_MDR_CMON                                   (0x80U)

/*  Bit definition for CMP_FIR register  */
#define CMP_FIR_FCKS_POS                               (0U)
#define CMP_FIR_FCKS                                   (0x03U)
#define CMP_FIR_FCKS_0                                 (0x01U)
#define CMP_FIR_FCKS_1                                 (0x02U)
#define CMP_FIR_EDGS_POS                               (4U)
#define CMP_FIR_EDGS                                   (0x30U)
#define CMP_FIR_EDGS_0                                 (0x10U)
#define CMP_FIR_EDGS_1                                 (0x20U)
#define CMP_FIR_CIEN_POS                               (6U)
#define CMP_FIR_CIEN                                   (0x40U)

/*  Bit definition for CMP_OCR register  */
#define CMP_OCR_COEN_POS                               (0U)
#define CMP_OCR_COEN                                   (0x01U)
#define CMP_OCR_COPS_POS                               (1U)
#define CMP_OCR_COPS                                   (0x02U)
#define CMP_OCR_CPOE_POS                               (2U)
#define CMP_OCR_CPOE                                   (0x04U)
#define CMP_OCR_TWOE_POS                               (3U)
#define CMP_OCR_TWOE                                   (0x08U)
#define CMP_OCR_TWOL_POS                               (4U)
#define CMP_OCR_TWOL                                   (0x10U)

/*  Bit definition for CMP_VSR register  */
#define CMP_VSR_RVSL_POS                               (0U)
#define CMP_VSR_RVSL                                   (0x07U)
#define CMP_VSR_RVSL_0                                 (0x01U)
#define CMP_VSR_RVSL_1                                 (0x02U)
#define CMP_VSR_RVSL_2                                 (0x04U)
#define CMP_VSR_CVSL_POS                               (4U)
#define CMP_VSR_CVSL                                   (0xF0U)
#define CMP_VSR_CVSL_0                                 (0x10U)
#define CMP_VSR_CVSL_1                                 (0x20U)
#define CMP_VSR_CVSL_2                                 (0x40U)
#define CMP_VSR_CVSL_3                                 (0x80U)

/*  Bit definition for CMP_TWR1 register  */
#define CMP_TWR1_CTWS0_POS                             (0U)
#define CMP_TWR1_CTWS0                                 (0x01U)
#define CMP_TWR1_CTWS1_POS                             (1U)
#define CMP_TWR1_CTWS1                                 (0x02U)
#define CMP_TWR1_CTWS2_POS                             (2U)
#define CMP_TWR1_CTWS2                                 (0x04U)
#define CMP_TWR1_CTWS3_POS                             (3U)
#define CMP_TWR1_CTWS3                                 (0x08U)
#define CMP_TWR1_CTWS4_POS                             (4U)
#define CMP_TWR1_CTWS4                                 (0x10U)
#define CMP_TWR1_CTWS5_POS                             (5U)
#define CMP_TWR1_CTWS5                                 (0x20U)
#define CMP_TWR1_CTWS6_POS                             (6U)
#define CMP_TWR1_CTWS6                                 (0x40U)
#define CMP_TWR1_CTWS7_POS                             (7U)
#define CMP_TWR1_CTWS7                                 (0x80U)

/*  Bit definition for CMP_TWR2 register  */
#define CMP_TWR2_CTWP0_POS                             (0U)
#define CMP_TWR2_CTWP0                                 (0x01U)
#define CMP_TWR2_CTWP1_POS                             (1U)
#define CMP_TWR2_CTWP1                                 (0x02U)
#define CMP_TWR2_CTWP2_POS                             (2U)
#define CMP_TWR2_CTWP2                                 (0x04U)
#define CMP_TWR2_CTWP3_POS                             (3U)
#define CMP_TWR2_CTWP3                                 (0x08U)
#define CMP_TWR2_CTWP4_POS                             (4U)
#define CMP_TWR2_CTWP4                                 (0x10U)
#define CMP_TWR2_CTWP5_POS                             (5U)
#define CMP_TWR2_CTWP5                                 (0x20U)
#define CMP_TWR2_CTWP6_POS                             (6U)
#define CMP_TWR2_CTWP6                                 (0x40U)
#define CMP_TWR2_CTWP7_POS                             (7U)
#define CMP_TWR2_CTWP7                                 (0x80U)

/*******************************************************************************
                Bit definition for Peripheral CMU
*******************************************************************************/
/*  Bit definition for CMU_ADCKSEL register  */
#define CMU_ADCKSEL_ADCKSEL                            (0x07U)

/*  Bit definition for CMU_XTALSTDSR register  */
#define CMU_XTALSTDSR_XTALSTDF                         (0x01U)

/*  Bit definition for CMU_SCFGR register  */
#define CMU_SCFGR_PCLK1S_POS                           (0U)
#define CMU_SCFGR_PCLK1S                               (0x00000007UL)
#define CMU_SCFGR_PCLK4S_POS                           (12U)
#define CMU_SCFGR_PCLK4S                               (0x00007000UL)
#define CMU_SCFGR_HCLKS_POS                            (24U)
#define CMU_SCFGR_HCLKS                                (0x07000000UL)

/*  Bit definition for CMU_CKSWR register  */
#define CMU_CKSWR_CKSW                                 (0x07U)

/*  Bit definition for CMU_XTALCR register  */
#define CMU_XTALCR_XTALSTP                             (0x01U)

/*  Bit definition for CMU_XTALCFGR register  */
#define CMU_XTALCFGR_XTALDRV_POS                       (4U)
#define CMU_XTALCFGR_XTALDRV                           (0x30U)
#define CMU_XTALCFGR_XTALDRV_0                         (0x10U)
#define CMU_XTALCFGR_XTALDRV_1                         (0x20U)
#define CMU_XTALCFGR_XTALMS_POS                        (6U)
#define CMU_XTALCFGR_XTALMS                            (0x40U)
#define CMU_XTALCFGR_SUPDRV_POS                        (7U)
#define CMU_XTALCFGR_SUPDRV                            (0x80U)

/*  Bit definition for CMU_XTALSTBCR register  */
#define CMU_XTALSTBCR_XTALSTB                          (0x07U)

/*  Bit definition for CMU_HRCCR register  */
#define CMU_HRCCR_HRCSTP                               (0x01U)

/*  Bit definition for CMU_OSCSTBSR register  */
#define CMU_OSCSTBSR_HRCSTBF_POS                       (0U)
#define CMU_OSCSTBSR_HRCSTBF                           (0x01U)
#define CMU_OSCSTBSR_XTALSTBF_POS                      (3U)
#define CMU_OSCSTBSR_XTALSTBF                          (0x08U)
#define CMU_OSCSTBSR_PLLSTBF_POS                       (5U)
#define CMU_OSCSTBSR_PLLSTBF                           (0x20U)

/*  Bit definition for CMU_MCOCFGR register  */
#define CMU_MCOCFGR_MCO1SEL_POS                        (0U)
#define CMU_MCOCFGR_MCO1SEL                            (0x0FU)
#define CMU_MCOCFGR_MCO1DIV_POS                        (4U)
#define CMU_MCOCFGR_MCO1DIV                            (0x70U)
#define CMU_MCOCFGR_MCO1EN_POS                         (7U)
#define CMU_MCOCFGR_MCO1EN                             (0x80U)

/*  Bit definition for CMU_XTALSTDCR register  */
#define CMU_XTALSTDCR_XTALSTDIE_POS                    (0U)
#define CMU_XTALSTDCR_XTALSTDIE                        (0x01U)
#define CMU_XTALSTDCR_XTALSTDRE_POS                    (1U)
#define CMU_XTALSTDCR_XTALSTDRE                        (0x02U)
#define CMU_XTALSTDCR_XTALSTDRIS_POS                   (2U)
#define CMU_XTALSTDCR_XTALSTDRIS                       (0x04U)
#define CMU_XTALSTDCR_XTALSTDE_POS                     (7U)
#define CMU_XTALSTDCR_XTALSTDE                         (0x80U)

/*  Bit definition for CMU_FCG register  */
#define CMU_FCG_ADC_POS                                (0U)
#define CMU_FCG_ADC                                    (0x00000001UL)
#define CMU_FCG_CTC_POS                                (1U)
#define CMU_FCG_CTC                                    (0x00000002UL)
#define CMU_FCG_CMP_POS                                (2U)
#define CMU_FCG_CMP                                    (0x00000004UL)
#define CMU_FCG_AOS_POS                                (4U)
#define CMU_FCG_AOS                                    (0x00000010UL)
#define CMU_FCG_DMA_POS                                (5U)
#define CMU_FCG_DMA                                    (0x00000020UL)
#define CMU_FCG_CRC_POS                                (7U)
#define CMU_FCG_CRC                                    (0x00000080UL)
#define CMU_FCG_TMRA_1_POS                             (8U)
#define CMU_FCG_TMRA_1                                 (0x00000100UL)
#define CMU_FCG_TMRA_2_POS                             (9U)
#define CMU_FCG_TMRA_2                                 (0x00000200UL)
#define CMU_FCG_TMRA_3_POS                             (10U)
#define CMU_FCG_TMRA_3                                 (0x00000400UL)
#define CMU_FCG_TMRA_4_POS                             (11U)
#define CMU_FCG_TMRA_4                                 (0x00000800UL)
#define CMU_FCG_TMR0_1_POS                             (16U)
#define CMU_FCG_TMR0_1                                 (0x00010000UL)
#define CMU_FCG_TMR0_2_POS                             (17U)
#define CMU_FCG_TMR0_2                                 (0x00020000UL)
#define CMU_FCG_TMR4_POS                               (18U)
#define CMU_FCG_TMR4                                   (0x00040000UL)
#define CMU_FCG_TMRB_POS                               (19U)
#define CMU_FCG_TMRB                                   (0x00080000UL)
#define CMU_FCG_EMB_POS                                (20U)
#define CMU_FCG_EMB                                    (0x00100000UL)
#define CMU_FCG_FCM_POS                                (21U)
#define CMU_FCG_FCM                                    (0x00200000UL)
#define CMU_FCG_DCU_POS                                (22U)
#define CMU_FCG_DCU                                    (0x00400000UL)
#define CMU_FCG_USART1_POS                             (24U)
#define CMU_FCG_USART1                                 (0x01000000UL)
#define CMU_FCG_USART2_POS                             (25U)
#define CMU_FCG_USART2                                 (0x02000000UL)
#define CMU_FCG_USART3_POS                             (26U)
#define CMU_FCG_USART3                                 (0x04000000UL)
#define CMU_FCG_USART4_POS                             (27U)
#define CMU_FCG_USART4                                 (0x08000000UL)
#define CMU_FCG_IIC_POS                                (28U)
#define CMU_FCG_IIC                                    (0x10000000UL)
#define CMU_FCG_SPI_POS                                (29U)
#define CMU_FCG_SPI                                    (0x20000000UL)

/*  Bit definition for CMU_LRCCR register  */
#define CMU_LRCCR_LRCSTP                               (0x01U)

/*  Bit definition for CMU_MRCCR register  */
#define CMU_MRCCR_MRCSTP                               (0x01U)

/*  Bit definition for CMU_PLLCFGR register  */
#define CMU_PLLCFGR_PLLM_POS                           (0U)
#define CMU_PLLCFGR_PLLM                               (0x00000007UL)
#define CMU_PLLCFGR_PLLSRC_POS                         (7U)
#define CMU_PLLCFGR_PLLSRC                             (0x00000080UL)
#define CMU_PLLCFGR_PLLN_POS                           (8U)
#define CMU_PLLCFGR_PLLN                               (0x00003F00UL)
#define CMU_PLLCFGR_PLLP_POS                           (28U)
#define CMU_PLLCFGR_PLLP                               (0x30000000UL)

/*  Bit definition for CMU_PLLCR register  */
#define CMU_PLLCR_PLLOFF                               (0x01U)

/*  Bit definition for CMU_TPIUCKCFGR register  */
#define CMU_TPIUCKCFGR_TPIUCKS_POS                     (0U)
#define CMU_TPIUCKCFGR_TPIUCKS                         (0x03U)
#define CMU_TPIUCKCFGR_TPIUCKS_0                       (0x01U)
#define CMU_TPIUCKCFGR_TPIUCKS_1                       (0x02U)
#define CMU_TPIUCKCFGR_TPIUCKOE_POS                    (7U)
#define CMU_TPIUCKCFGR_TPIUCKOE                        (0x80U)

/*******************************************************************************
                Bit definition for Peripheral CRC
*******************************************************************************/
/*  Bit definition for CRC_CR register  */
#define CRC_CR_CR_POS                                  (0U)
#define CRC_CR_CR                                      (0x00000001UL)
#define CRC_CR_FLAG_POS                                (1U)
#define CRC_CR_FLAG                                    (0x00000002UL)

/*  Bit definition for CRC_RESLT register  */
#define CRC_RESLT                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT0 register  */
#define CRC_DAT0                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT1 register  */
#define CRC_DAT1                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT2 register  */
#define CRC_DAT2                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT3 register  */
#define CRC_DAT3                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT4 register  */
#define CRC_DAT4                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT5 register  */
#define CRC_DAT5                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT6 register  */
#define CRC_DAT6                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT7 register  */
#define CRC_DAT7                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT8 register  */
#define CRC_DAT8                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT9 register  */
#define CRC_DAT9                                       (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT10 register  */
#define CRC_DAT10                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT11 register  */
#define CRC_DAT11                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT12 register  */
#define CRC_DAT12                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT13 register  */
#define CRC_DAT13                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT14 register  */
#define CRC_DAT14                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT15 register  */
#define CRC_DAT15                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT16 register  */
#define CRC_DAT16                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT17 register  */
#define CRC_DAT17                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT18 register  */
#define CRC_DAT18                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT19 register  */
#define CRC_DAT19                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT20 register  */
#define CRC_DAT20                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT21 register  */
#define CRC_DAT21                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT22 register  */
#define CRC_DAT22                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT23 register  */
#define CRC_DAT23                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT24 register  */
#define CRC_DAT24                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT25 register  */
#define CRC_DAT25                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT26 register  */
#define CRC_DAT26                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT27 register  */
#define CRC_DAT27                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT28 register  */
#define CRC_DAT28                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT29 register  */
#define CRC_DAT29                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT30 register  */
#define CRC_DAT30                                      (0xFFFFFFFFUL)

/*  Bit definition for CRC_DAT31 register  */
#define CRC_DAT31                                      (0xFFFFFFFFUL)

/*******************************************************************************
                Bit definition for Peripheral CTC
*******************************************************************************/
/*  Bit definition for CTC_CR1 register  */
#define CTC_CR1_REFPSC_POS                             (0U)
#define CTC_CR1_REFPSC                                 (0x00000007UL)
#define CTC_CR1_REFPSC_0                               (0x00000001UL)
#define CTC_CR1_REFPSC_1                               (0x00000002UL)
#define CTC_CR1_REFPSC_2                               (0x00000004UL)
#define CTC_CR1_REFCKS_POS                             (4U)
#define CTC_CR1_REFCKS                                 (0x00000030UL)
#define CTC_CR1_REFCKS_0                               (0x00000010UL)
#define CTC_CR1_REFCKS_1                               (0x00000020UL)
#define CTC_CR1_ERRIE_POS                              (6U)
#define CTC_CR1_ERRIE                                  (0x00000040UL)
#define CTC_CR1_CTCEN_POS                              (7U)
#define CTC_CR1_CTCEN                                  (0x00000080UL)
#define CTC_CR1_TRMVAL_POS                             (16U)
#define CTC_CR1_TRMVAL                                 (0x003F0000UL)
#define CTC_CR1_TRMVAL_0                               (0x00010000UL)
#define CTC_CR1_TRMVAL_1                               (0x00020000UL)
#define CTC_CR1_TRMVAL_2                               (0x00040000UL)
#define CTC_CR1_TRMVAL_3                               (0x00080000UL)
#define CTC_CR1_TRMVAL_4                               (0x00100000UL)
#define CTC_CR1_TRMVAL_5                               (0x00200000UL)

/*  Bit definition for CTC_CR2 register  */
#define CTC_CR2_OFSVAL_POS                             (0U)
#define CTC_CR2_OFSVAL                                 (0x000000FFUL)
#define CTC_CR2_OFSVAL_0                               (0x00000001UL)
#define CTC_CR2_OFSVAL_1                               (0x00000002UL)
#define CTC_CR2_OFSVAL_2                               (0x00000004UL)
#define CTC_CR2_OFSVAL_3                               (0x00000008UL)
#define CTC_CR2_OFSVAL_4                               (0x00000010UL)
#define CTC_CR2_OFSVAL_5                               (0x00000020UL)
#define CTC_CR2_OFSVAL_6                               (0x00000040UL)
#define CTC_CR2_OFSVAL_7                               (0x00000080UL)
#define CTC_CR2_RLDVAL_POS                             (16U)
#define CTC_CR2_RLDVAL                                 (0xFFFF0000UL)
#define CTC_CR2_RLDVAL_0                               (0x00010000UL)
#define CTC_CR2_RLDVAL_1                               (0x00020000UL)
#define CTC_CR2_RLDVAL_2                               (0x00040000UL)
#define CTC_CR2_RLDVAL_3                               (0x00080000UL)
#define CTC_CR2_RLDVAL_4                               (0x00100000UL)
#define CTC_CR2_RLDVAL_5                               (0x00200000UL)
#define CTC_CR2_RLDVAL_6                               (0x00400000UL)
#define CTC_CR2_RLDVAL_7                               (0x00800000UL)
#define CTC_CR2_RLDVAL_8                               (0x01000000UL)
#define CTC_CR2_RLDVAL_9                               (0x02000000UL)
#define CTC_CR2_RLDVAL_10                              (0x04000000UL)
#define CTC_CR2_RLDVAL_11                              (0x08000000UL)
#define CTC_CR2_RLDVAL_12                              (0x10000000UL)
#define CTC_CR2_RLDVAL_13                              (0x20000000UL)
#define CTC_CR2_RLDVAL_14                              (0x40000000UL)
#define CTC_CR2_RLDVAL_15                              (0x80000000UL)

/*  Bit definition for CTC_STR register  */
#define CTC_STR_TRIMOK_POS                             (0U)
#define CTC_STR_TRIMOK                                 (0x00000001UL)
#define CTC_STR_TRMOVF_POS                             (1U)
#define CTC_STR_TRMOVF                                 (0x00000002UL)
#define CTC_STR_TRMUDF_POS                             (2U)
#define CTC_STR_TRMUDF                                 (0x00000004UL)
#define CTC_STR_CTCBSY_POS                             (3U)
#define CTC_STR_CTCBSY                                 (0x00000008UL)

/*******************************************************************************
                Bit definition for Peripheral DAC
*******************************************************************************/
/*  Bit definition for CMP_DADR1 register  */
#define CMP_DADR1_DATA1_POS                            (0U)
#define CMP_DADR1_DATA1                                (0x00FFU)
#define CMP_DADR1_DATA1_0                              (0x0001U)
#define CMP_DADR1_DATA1_1                              (0x0002U)
#define CMP_DADR1_DATA1_2                              (0x0004U)
#define CMP_DADR1_DATA1_3                              (0x0008U)
#define CMP_DADR1_DATA1_4                              (0x0010U)
#define CMP_DADR1_DATA1_5                              (0x0020U)
#define CMP_DADR1_DATA1_6                              (0x0040U)
#define CMP_DADR1_DATA1_7                              (0x0080U)
#define CMP_DADR1_DATA2_POS                            (8U)
#define CMP_DADR1_DATA2                                (0xFF00U)
#define CMP_DADR1_DATA2_0                              (0x0100U)
#define CMP_DADR1_DATA2_1                              (0x0200U)
#define CMP_DADR1_DATA2_2                              (0x0400U)
#define CMP_DADR1_DATA2_3                              (0x0800U)
#define CMP_DADR1_DATA2_4                              (0x1000U)
#define CMP_DADR1_DATA2_5                              (0x2000U)
#define CMP_DADR1_DATA2_6                              (0x4000U)
#define CMP_DADR1_DATA2_7                              (0x8000U)

/*  Bit definition for CMP_DACR1 register  */
#define CMP_DACR1_DAEN_POS                             (0U)
#define CMP_DACR1_DAEN                                 (0x0001U)
#define CMP_DACR1_ALGN_POS                             (8U)
#define CMP_DACR1_ALGN                                 (0x0100U)

/*  Bit definition for CMP_DADC1 register  */
#define CMP_DADC1_DASW_POS                             (0U)
#define CMP_DADC1_DASW                                 (0x0001U)
#define CMP_DADC1_WPRT_POS                             (8U)
#define CMP_DADC1_WPRT                                 (0xFF00U)
#define CMP_DADC1_WPRT_0                               (0x0100U)
#define CMP_DADC1_WPRT_1                               (0x0200U)
#define CMP_DADC1_WPRT_2                               (0x0400U)
#define CMP_DADC1_WPRT_3                               (0x0800U)
#define CMP_DADC1_WPRT_4                               (0x1000U)
#define CMP_DADC1_WPRT_5                               (0x2000U)
#define CMP_DADC1_WPRT_6                               (0x4000U)
#define CMP_DADC1_WPRT_7                               (0x8000U)

/*******************************************************************************
                Bit definition for Peripheral DBGC
*******************************************************************************/
/*  Bit definition for DBG_MCUDBGSTAT register  */
#define DBG_MCUDBGSTAT_CDBGPWRUPREQ_POS                (0U)
#define DBG_MCUDBGSTAT_CDBGPWRUPREQ                    (0x00000001UL)
#define DBG_MCUDBGSTAT_CDBGPWRUPACK_POS                (1U)
#define DBG_MCUDBGSTAT_CDBGPWRUPACK                    (0x00000002UL)

/*  Bit definition for DBG_MCUSTPCTL register  */
#define DBG_MCUSTPCTL_SWDTSTP_POS                      (0U)
#define DBG_MCUSTPCTL_SWDTSTP                          (0x00000001UL)
#define DBG_MCUSTPCTL_WDTSTP_POS                       (1U)
#define DBG_MCUSTPCTL_WDTSTP                           (0x00000002UL)
#define DBG_MCUSTPCTL_LVD0STP_POS                      (3U)
#define DBG_MCUSTPCTL_LVD0STP                          (0x00000008UL)
#define DBG_MCUSTPCTL_LVD1STP_POS                      (4U)
#define DBG_MCUSTPCTL_LVD1STP                          (0x00000010UL)
#define DBG_MCUSTPCTL_LVD2STP_POS                      (5U)
#define DBG_MCUSTPCTL_LVD2STP                          (0x00000020UL)
#define DBG_MCUSTPCTL_TMR0_1_STP_POS                   (6U)
#define DBG_MCUSTPCTL_TMR0_1_STP                       (0x00000040UL)
#define DBG_MCUSTPCTL_TMR0_2_STP_POS                   (7U)
#define DBG_MCUSTPCTL_TMR0_2_STP                       (0x00000080UL)
#define DBG_MCUSTPCTL_TMR4_STP_POS                     (8U)
#define DBG_MCUSTPCTL_TMR4_STP                         (0x00000100UL)
#define DBG_MCUSTPCTL_TMRA_1_STP_POS                   (9U)
#define DBG_MCUSTPCTL_TMRA_1_STP                       (0x00000200UL)
#define DBG_MCUSTPCTL_TMRA_2_STP_POS                   (10U)
#define DBG_MCUSTPCTL_TMRA_2_STP                       (0x00000400UL)
#define DBG_MCUSTPCTL_TMRA_3_STP_POS                   (11U)
#define DBG_MCUSTPCTL_TMRA_3_STP                       (0x00000800UL)
#define DBG_MCUSTPCTL_TMRA_4_STP_POS                   (12U)
#define DBG_MCUSTPCTL_TMRA_4_STP                       (0x00001000UL)
#define DBG_MCUSTPCTL_TMRB_STP_POS                     (13U)
#define DBG_MCUSTPCTL_TMRB_STP                         (0x00002000UL)

/*  Bit definition for DBG_MCUTRACECTL register  */
#define DBG_MCUTRACECTL_TRACE_MODE_POS                 (0U)
#define DBG_MCUTRACECTL_TRACE_MODE                     (0x00000003UL)
#define DBG_MCUTRACECTL_TRACE_MODE_0                   (0x00000001UL)
#define DBG_MCUTRACECTL_TRACE_MODE_1                   (0x00000002UL)
#define DBG_MCUTRACECTL_TRACE_IOEN_POS                 (2U)
#define DBG_MCUTRACECTL_TRACE_IOEN                     (0x00000004UL)

/*******************************************************************************
                Bit definition for Peripheral DCU
*******************************************************************************/
/*  Bit definition for DCU_CTL register  */
#define DCU_CTL_MODE_POS                               (0U)
#define DCU_CTL_MODE                                   (0x00000007UL)
#define DCU_CTL_MODE_0                                 (0x00000001UL)
#define DCU_CTL_MODE_1                                 (0x00000002UL)
#define DCU_CTL_MODE_2                                 (0x00000004UL)
#define DCU_CTL_DATASIZE_POS                           (3U)
#define DCU_CTL_DATASIZE                               (0x00000018UL)
#define DCU_CTL_DATASIZE_0                             (0x00000008UL)
#define DCU_CTL_DATASIZE_1                             (0x00000010UL)
#define DCU_CTL_COMP_TRG_POS                           (8U)
#define DCU_CTL_COMP_TRG                               (0x00000100UL)
#define DCU_CTL_INTEN_POS                              (31U)
#define DCU_CTL_INTEN                                  (0x80000000UL)

/*  Bit definition for DCU_FLAG register  */
#define DCU_FLAG_FLAG_OP_POS                           (0U)
#define DCU_FLAG_FLAG_OP                               (0x00000001UL)
#define DCU_FLAG_FLAG_LS2_POS                          (1U)
#define DCU_FLAG_FLAG_LS2                              (0x00000002UL)
#define DCU_FLAG_FLAG_EQ2_POS                          (2U)
#define DCU_FLAG_FLAG_EQ2                              (0x00000004UL)
#define DCU_FLAG_FLAG_GT2_POS                          (3U)
#define DCU_FLAG_FLAG_GT2                              (0x00000008UL)
#define DCU_FLAG_FLAG_LS1_POS                          (4U)
#define DCU_FLAG_FLAG_LS1                              (0x00000010UL)
#define DCU_FLAG_FLAG_EQ1_POS                          (5U)
#define DCU_FLAG_FLAG_EQ1                              (0x00000020UL)
#define DCU_FLAG_FLAG_GT1_POS                          (6U)
#define DCU_FLAG_FLAG_GT1                              (0x00000040UL)

/*  Bit definition for DCU_DATA0 register  */
#define DCU_DATA0                                      (0xFFFFFFFFUL)

/*  Bit definition for DCU_DATA1 register  */
#define DCU_DATA1                                      (0xFFFFFFFFUL)

/*  Bit definition for DCU_DATA2 register  */
#define DCU_DATA2                                      (0xFFFFFFFFUL)

/*  Bit definition for DCU_FLAGCLR register  */
#define DCU_FLAGCLR_CLR_OP_POS                         (0U)
#define DCU_FLAGCLR_CLR_OP                             (0x00000001UL)
#define DCU_FLAGCLR_CLR_LS2_POS                        (1U)
#define DCU_FLAGCLR_CLR_LS2                            (0x00000002UL)
#define DCU_FLAGCLR_CLR_EQ2_POS                        (2U)
#define DCU_FLAGCLR_CLR_EQ2                            (0x00000004UL)
#define DCU_FLAGCLR_CLR_GT2_POS                        (3U)
#define DCU_FLAGCLR_CLR_GT2                            (0x00000008UL)
#define DCU_FLAGCLR_CLR_LS1_POS                        (4U)
#define DCU_FLAGCLR_CLR_LS1                            (0x00000010UL)
#define DCU_FLAGCLR_CLR_EQ1_POS                        (5U)
#define DCU_FLAGCLR_CLR_EQ1                            (0x00000020UL)
#define DCU_FLAGCLR_CLR_GT1_POS                        (6U)
#define DCU_FLAGCLR_CLR_GT1                            (0x00000040UL)

/*  Bit definition for DCU_INTSEL register  */
#define DCU_INTSEL_INT_OP_POS                          (0U)
#define DCU_INTSEL_INT_OP                              (0x00000001UL)
#define DCU_INTSEL_INT_LS2_POS                         (1U)
#define DCU_INTSEL_INT_LS2                             (0x00000002UL)
#define DCU_INTSEL_INT_EQ2_POS                         (2U)
#define DCU_INTSEL_INT_EQ2                             (0x00000004UL)
#define DCU_INTSEL_INT_GT2_POS                         (3U)
#define DCU_INTSEL_INT_GT2                             (0x00000008UL)
#define DCU_INTSEL_INT_LS1_POS                         (4U)
#define DCU_INTSEL_INT_LS1                             (0x00000010UL)
#define DCU_INTSEL_INT_EQ1_POS                         (5U)
#define DCU_INTSEL_INT_EQ1                             (0x00000020UL)
#define DCU_INTSEL_INT_GT1_POS                         (6U)
#define DCU_INTSEL_INT_GT1                             (0x00000040UL)
#define DCU_INTSEL_INT_WIN_POS                         (7U)
#define DCU_INTSEL_INT_WIN                             (0x00000180UL)
#define DCU_INTSEL_INT_WIN_0                           (0x00000080UL)
#define DCU_INTSEL_INT_WIN_1                           (0x00000100UL)

/*******************************************************************************
                Bit definition for Peripheral DMA
*******************************************************************************/
/*  Bit definition for DMA_EN register  */
#define DMA_EN_EN                                      (0x00000001UL)

/*  Bit definition for DMA_INTSTAT0 register  */
#define DMA_INTSTAT0_TRNERR_POS                        (0U)
#define DMA_INTSTAT0_TRNERR                            (0x0000000FUL)
#define DMA_INTSTAT0_TRNERR_0                          (0x00000001UL)
#define DMA_INTSTAT0_TRNERR_1                          (0x00000002UL)
#define DMA_INTSTAT0_TRNERR_2                          (0x00000004UL)
#define DMA_INTSTAT0_TRNERR_3                          (0x00000008UL)
#define DMA_INTSTAT0_REQERR_POS                        (16U)
#define DMA_INTSTAT0_REQERR                            (0x000F0000UL)
#define DMA_INTSTAT0_REQERR_0                          (0x00010000UL)
#define DMA_INTSTAT0_REQERR_1                          (0x00020000UL)
#define DMA_INTSTAT0_REQERR_2                          (0x00040000UL)
#define DMA_INTSTAT0_REQERR_3                          (0x00080000UL)

/*  Bit definition for DMA_INTSTAT1 register  */
#define DMA_INTSTAT1_TC_POS                            (0U)
#define DMA_INTSTAT1_TC                                (0x0000000FUL)
#define DMA_INTSTAT1_TC_0                              (0x00000001UL)
#define DMA_INTSTAT1_TC_1                              (0x00000002UL)
#define DMA_INTSTAT1_TC_2                              (0x00000004UL)
#define DMA_INTSTAT1_TC_3                              (0x00000008UL)
#define DMA_INTSTAT1_BTC_POS                           (16U)
#define DMA_INTSTAT1_BTC                               (0x000F0000UL)
#define DMA_INTSTAT1_BTC_0                             (0x00010000UL)
#define DMA_INTSTAT1_BTC_1                             (0x00020000UL)
#define DMA_INTSTAT1_BTC_2                             (0x00040000UL)
#define DMA_INTSTAT1_BTC_3                             (0x00080000UL)

/*  Bit definition for DMA_INTMASK0 register  */
#define DMA_INTMASK0_MSKTRNERR_POS                     (0U)
#define DMA_INTMASK0_MSKTRNERR                         (0x0000000FUL)
#define DMA_INTMASK0_MSKTRNERR_0                       (0x00000001UL)
#define DMA_INTMASK0_MSKTRNERR_1                       (0x00000002UL)
#define DMA_INTMASK0_MSKTRNERR_2                       (0x00000004UL)
#define DMA_INTMASK0_MSKTRNERR_3                       (0x00000008UL)
#define DMA_INTMASK0_MSKREQERR_POS                     (16U)
#define DMA_INTMASK0_MSKREQERR                         (0x000F0000UL)
#define DMA_INTMASK0_MSKREQERR_0                       (0x00010000UL)
#define DMA_INTMASK0_MSKREQERR_1                       (0x00020000UL)
#define DMA_INTMASK0_MSKREQERR_2                       (0x00040000UL)
#define DMA_INTMASK0_MSKREQERR_3                       (0x00080000UL)

/*  Bit definition for DMA_INTMASK1 register  */
#define DMA_INTMASK1_MSKTC_POS                         (0U)
#define DMA_INTMASK1_MSKTC                             (0x0000000FUL)
#define DMA_INTMASK1_MSKTC_0                           (0x00000001UL)
#define DMA_INTMASK1_MSKTC_1                           (0x00000002UL)
#define DMA_INTMASK1_MSKTC_2                           (0x00000004UL)
#define DMA_INTMASK1_MSKTC_3                           (0x00000008UL)
#define DMA_INTMASK1_MSKBTC_POS                        (16U)
#define DMA_INTMASK1_MSKBTC                            (0x000F0000UL)
#define DMA_INTMASK1_MSKBTC_0                          (0x00010000UL)
#define DMA_INTMASK1_MSKBTC_1                          (0x00020000UL)
#define DMA_INTMASK1_MSKBTC_2                          (0x00040000UL)
#define DMA_INTMASK1_MSKBTC_3                          (0x00080000UL)

/*  Bit definition for DMA_INTCLR0 register  */
#define DMA_INTCLR0_CLRTRNERR_POS                      (0U)
#define DMA_INTCLR0_CLRTRNERR                          (0x0000000FUL)
#define DMA_INTCLR0_CLRTRNERR_0                        (0x00000001UL)
#define DMA_INTCLR0_CLRTRNERR_1                        (0x00000002UL)
#define DMA_INTCLR0_CLRTRNERR_2                        (0x00000004UL)
#define DMA_INTCLR0_CLRTRNERR_3                        (0x00000008UL)
#define DMA_INTCLR0_CLRREQERR_POS                      (16U)
#define DMA_INTCLR0_CLRREQERR                          (0x000F0000UL)
#define DMA_INTCLR0_CLRREQERR_0                        (0x00010000UL)
#define DMA_INTCLR0_CLRREQERR_1                        (0x00020000UL)
#define DMA_INTCLR0_CLRREQERR_2                        (0x00040000UL)
#define DMA_INTCLR0_CLRREQERR_3                        (0x00080000UL)

/*  Bit definition for DMA_INTCLR1 register  */
#define DMA_INTCLR1_CLRTC_POS                          (0U)
#define DMA_INTCLR1_CLRTC                              (0x0000000FUL)
#define DMA_INTCLR1_CLRTC_0                            (0x00000001UL)
#define DMA_INTCLR1_CLRTC_1                            (0x00000002UL)
#define DMA_INTCLR1_CLRTC_2                            (0x00000004UL)
#define DMA_INTCLR1_CLRTC_3                            (0x00000008UL)
#define DMA_INTCLR1_CLRBTC_POS                         (16U)
#define DMA_INTCLR1_CLRBTC                             (0x000F0000UL)
#define DMA_INTCLR1_CLRBTC_0                           (0x00010000UL)
#define DMA_INTCLR1_CLRBTC_1                           (0x00020000UL)
#define DMA_INTCLR1_CLRBTC_2                           (0x00040000UL)
#define DMA_INTCLR1_CLRBTC_3                           (0x00080000UL)

/*  Bit definition for DMA_CHEN register  */
#define DMA_CHEN_CHEN                                  (0x0000000FUL)
#define DMA_CHEN_CHEN_0                                (0x00000001UL)
#define DMA_CHEN_CHEN_1                                (0x00000002UL)
#define DMA_CHEN_CHEN_2                                (0x00000004UL)
#define DMA_CHEN_CHEN_3                                (0x00000008UL)

/*  Bit definition for DMA_CHSTAT register  */
#define DMA_CHSTAT_DMAACT_POS                          (0U)
#define DMA_CHSTAT_DMAACT                              (0x00000001UL)
#define DMA_CHSTAT_CHACT_POS                           (16U)
#define DMA_CHSTAT_CHACT                               (0x000F0000UL)
#define DMA_CHSTAT_CHACT_0                             (0x00010000UL)
#define DMA_CHSTAT_CHACT_1                             (0x00020000UL)
#define DMA_CHSTAT_CHACT_2                             (0x00040000UL)
#define DMA_CHSTAT_CHACT_3                             (0x00080000UL)

/*  Bit definition for DMA_RAM_LLP register  */
#define DMA_RAM_LLP_LLP_POS                            (14U)
#define DMA_RAM_LLP_LLP                                (0xFFFFC000UL)

/*  Bit definition for DMA_ROM_LLP register  */
#define DMA_ROM_LLP_LLP_POS                            (14U)
#define DMA_ROM_LLP_LLP                                (0xFFFFC000UL)

/*  Bit definition for DMA_CHENCLR register  */
#define DMA_CHENCLR_CHENCLR                            (0x0000000FUL)
#define DMA_CHENCLR_CHENCLR_0                          (0x00000001UL)
#define DMA_CHENCLR_CHENCLR_1                          (0x00000002UL)
#define DMA_CHENCLR_CHENCLR_2                          (0x00000004UL)
#define DMA_CHENCLR_CHENCLR_3                          (0x00000008UL)

/*  Bit definition for DMA_SAR register  */
#define DMA_SAR                                        (0xFFFFFFFFUL)

/*  Bit definition for DMA_DAR register  */
#define DMA_DAR                                        (0xFFFFFFFFUL)

/*  Bit definition for DMA_CH0CTL0 register  */
#define DMA_CH0CTL0_BLKSIZE_POS                        (0U)
#define DMA_CH0CTL0_BLKSIZE                            (0x000000FFUL)
#define DMA_CH0CTL0_CNT_POS                            (8U)
#define DMA_CH0CTL0_CNT                                (0x0003FF00UL)
#define DMA_CH0CTL0_LLP_POS                            (18U)
#define DMA_CH0CTL0_LLP                                (0x0FFC0000UL)
#define DMA_CH0CTL0_LLPEN_POS                          (28U)
#define DMA_CH0CTL0_LLPEN                              (0x10000000UL)
#define DMA_CH0CTL0_LLPRUN_POS                         (29U)
#define DMA_CH0CTL0_LLPRUN                             (0x20000000UL)
#define DMA_CH0CTL0_HSIZE_POS                          (30U)
#define DMA_CH0CTL0_HSIZE                              (0xC0000000UL)
#define DMA_CH0CTL0_HSIZE_0                            (0x40000000UL)
#define DMA_CH0CTL0_HSIZE_1                            (0x80000000UL)

/*  Bit definition for DMA_CH0CTL1 register  */
#define DMA_CH0CTL1_OFFSET_POS                         (0U)
#define DMA_CH0CTL1_OFFSET                             (0x0000FFFFUL)
#define DMA_CH0CTL1_RPTNSCNT_POS                       (16U)
#define DMA_CH0CTL1_RPTNSCNT                           (0x00FF0000UL)
#define DMA_CH0CTL1_RPTNSEN_POS                        (24U)
#define DMA_CH0CTL1_RPTNSEN                            (0x01000000UL)
#define DMA_CH0CTL1_RPTNSSEL_POS                       (25U)
#define DMA_CH0CTL1_RPTNSSEL                           (0x06000000UL)
#define DMA_CH0CTL1_RPTNSSEL_0                         (0x02000000UL)
#define DMA_CH0CTL1_RPTNSSEL_1                         (0x04000000UL)
#define DMA_CH0CTL1_LLPSEL_POS                         (27U)
#define DMA_CH0CTL1_LLPSEL                             (0x08000000UL)
#define DMA_CH0CTL1_SINC_POS                           (28U)
#define DMA_CH0CTL1_SINC                               (0x30000000UL)
#define DMA_CH0CTL1_SINC_0                             (0x10000000UL)
#define DMA_CH0CTL1_SINC_1                             (0x20000000UL)
#define DMA_CH0CTL1_DINC_POS                           (30U)
#define DMA_CH0CTL1_DINC                               (0xC0000000UL)
#define DMA_CH0CTL1_DINC_0                             (0x40000000UL)
#define DMA_CH0CTL1_DINC_1                             (0x80000000UL)

/*  Bit definition for DMA_CH1CTL0 register  */
#define DMA_CH1CTL0_BLKSIZE_POS                        (0U)
#define DMA_CH1CTL0_BLKSIZE                            (0x000000FFUL)
#define DMA_CH1CTL0_CNT_POS                            (8U)
#define DMA_CH1CTL0_CNT                                (0x0003FF00UL)
#define DMA_CH1CTL0_LLP_POS                            (18U)
#define DMA_CH1CTL0_LLP                                (0x0FFC0000UL)
#define DMA_CH1CTL0_LLPEN_POS                          (28U)
#define DMA_CH1CTL0_LLPEN                              (0x10000000UL)
#define DMA_CH1CTL0_LLPRUN_POS                         (29U)
#define DMA_CH1CTL0_LLPRUN                             (0x20000000UL)
#define DMA_CH1CTL0_HSIZE_POS                          (30U)
#define DMA_CH1CTL0_HSIZE                              (0xC0000000UL)
#define DMA_CH1CTL0_HSIZE_0                            (0x40000000UL)
#define DMA_CH1CTL0_HSIZE_1                            (0x80000000UL)

/*  Bit definition for DMA_CH1CTL1 register  */
#define DMA_CH1CTL1_OFFSET_POS                         (0U)
#define DMA_CH1CTL1_OFFSET                             (0x0000FFFFUL)
#define DMA_CH1CTL1_RPTNSCNT_POS                       (16U)
#define DMA_CH1CTL1_RPTNSCNT                           (0x00FF0000UL)
#define DMA_CH1CTL1_RPTNSEN_POS                        (24U)
#define DMA_CH1CTL1_RPTNSEN                            (0x01000000UL)
#define DMA_CH1CTL1_RPTNSSEL_POS                       (25U)
#define DMA_CH1CTL1_RPTNSSEL                           (0x06000000UL)
#define DMA_CH1CTL1_RPTNSSEL_0                         (0x02000000UL)
#define DMA_CH1CTL1_RPTNSSEL_1                         (0x04000000UL)
#define DMA_CH1CTL1_LLPSEL_POS                         (27U)
#define DMA_CH1CTL1_LLPSEL                             (0x08000000UL)
#define DMA_CH1CTL1_SINC_POS                           (28U)
#define DMA_CH1CTL1_SINC                               (0x30000000UL)
#define DMA_CH1CTL1_SINC_0                             (0x10000000UL)
#define DMA_CH1CTL1_SINC_1                             (0x20000000UL)
#define DMA_CH1CTL1_DINC_POS                           (30U)
#define DMA_CH1CTL1_DINC                               (0xC0000000UL)
#define DMA_CH1CTL1_DINC_0                             (0x40000000UL)
#define DMA_CH1CTL1_DINC_1                             (0x80000000UL)

/*  Bit definition for DMA_CH2CTL0 register  */
#define DMA_CH2CTL0_BLKSIZE_POS                        (0U)
#define DMA_CH2CTL0_BLKSIZE                            (0x000000FFUL)
#define DMA_CH2CTL0_CNT_POS                            (8U)
#define DMA_CH2CTL0_CNT                                (0x0003FF00UL)
#define DMA_CH2CTL0_LLP_POS                            (18U)
#define DMA_CH2CTL0_LLP                                (0x0FFC0000UL)
#define DMA_CH2CTL0_LLPEN_POS                          (28U)
#define DMA_CH2CTL0_LLPEN                              (0x10000000UL)
#define DMA_CH2CTL0_LLPRUN_POS                         (29U)
#define DMA_CH2CTL0_LLPRUN                             (0x20000000UL)
#define DMA_CH2CTL0_HSIZE_POS                          (30U)
#define DMA_CH2CTL0_HSIZE                              (0xC0000000UL)
#define DMA_CH2CTL0_HSIZE_0                            (0x40000000UL)
#define DMA_CH2CTL0_HSIZE_1                            (0x80000000UL)

/*  Bit definition for DMA_CH2CTL1 register  */
#define DMA_CH2CTL1_OFFSET_POS                         (0U)
#define DMA_CH2CTL1_OFFSET                             (0x0000FFFFUL)
#define DMA_CH2CTL1_RPTNSCNT_POS                       (16U)
#define DMA_CH2CTL1_RPTNSCNT                           (0x00FF0000UL)
#define DMA_CH2CTL1_RPTNSEN_POS                        (24U)
#define DMA_CH2CTL1_RPTNSEN                            (0x01000000UL)
#define DMA_CH2CTL1_RPTNSSEL_POS                       (25U)
#define DMA_CH2CTL1_RPTNSSEL                           (0x06000000UL)
#define DMA_CH2CTL1_RPTNSSEL_0                         (0x02000000UL)
#define DMA_CH2CTL1_RPTNSSEL_1                         (0x04000000UL)
#define DMA_CH2CTL1_LLPSEL_POS                         (27U)
#define DMA_CH2CTL1_LLPSEL                             (0x08000000UL)
#define DMA_CH2CTL1_SINC_POS                           (28U)
#define DMA_CH2CTL1_SINC                               (0x30000000UL)
#define DMA_CH2CTL1_SINC_0                             (0x10000000UL)
#define DMA_CH2CTL1_SINC_1                             (0x20000000UL)
#define DMA_CH2CTL1_DINC_POS                           (30U)
#define DMA_CH2CTL1_DINC                               (0xC0000000UL)
#define DMA_CH2CTL1_DINC_0                             (0x40000000UL)
#define DMA_CH2CTL1_DINC_1                             (0x80000000UL)

/*  Bit definition for DMA_CH3CTL0 register  */
#define DMA_CH3CTL0_BLKSIZE_POS                        (0U)
#define DMA_CH3CTL0_BLKSIZE                            (0x000000FFUL)
#define DMA_CH3CTL0_CNT_POS                            (8U)
#define DMA_CH3CTL0_CNT                                (0x0003FF00UL)
#define DMA_CH3CTL0_LLP_POS                            (18U)
#define DMA_CH3CTL0_LLP                                (0x0FFC0000UL)
#define DMA_CH3CTL0_LLPEN_POS                          (28U)
#define DMA_CH3CTL0_LLPEN                              (0x10000000UL)
#define DMA_CH3CTL0_LLPRUN_POS                         (29U)
#define DMA_CH3CTL0_LLPRUN                             (0x20000000UL)
#define DMA_CH3CTL0_HSIZE_POS                          (30U)
#define DMA_CH3CTL0_HSIZE                              (0xC0000000UL)
#define DMA_CH3CTL0_HSIZE_0                            (0x40000000UL)
#define DMA_CH3CTL0_HSIZE_1                            (0x80000000UL)

/*  Bit definition for DMA_CH3CTL1 register  */
#define DMA_CH3CTL1_OFFSET_POS                         (0U)
#define DMA_CH3CTL1_OFFSET                             (0x0000FFFFUL)
#define DMA_CH3CTL1_RPTNSCNT_POS                       (16U)
#define DMA_CH3CTL1_RPTNSCNT                           (0x00FF0000UL)
#define DMA_CH3CTL1_RPTNSEN_POS                        (24U)
#define DMA_CH3CTL1_RPTNSEN                            (0x01000000UL)
#define DMA_CH3CTL1_RPTNSSEL_POS                       (25U)
#define DMA_CH3CTL1_RPTNSSEL                           (0x06000000UL)
#define DMA_CH3CTL1_RPTNSSEL_0                         (0x02000000UL)
#define DMA_CH3CTL1_RPTNSSEL_1                         (0x04000000UL)
#define DMA_CH3CTL1_LLPSEL_POS                         (27U)
#define DMA_CH3CTL1_LLPSEL                             (0x08000000UL)
#define DMA_CH3CTL1_SINC_POS                           (28U)
#define DMA_CH3CTL1_SINC                               (0x30000000UL)
#define DMA_CH3CTL1_SINC_0                             (0x10000000UL)
#define DMA_CH3CTL1_SINC_1                             (0x20000000UL)
#define DMA_CH3CTL1_DINC_POS                           (30U)
#define DMA_CH3CTL1_DINC                               (0xC0000000UL)
#define DMA_CH3CTL1_DINC_0                             (0x40000000UL)
#define DMA_CH3CTL1_DINC_1                             (0x80000000UL)

/*******************************************************************************
                Bit definition for Peripheral EFM
*******************************************************************************/
/*  Bit definition for EFM_FAPRT register  */
#define EFM_FAPRT_FAPRT                                (0x0000FFFFUL)

/*  Bit definition for EFM_FSTP register  */
#define EFM_FSTP_FSTP                                  (0x00000001UL)

/*  Bit definition for EFM_FRMC register  */
#define EFM_FRMC_FLWT_POS                              (0U)
#define EFM_FRMC_FLWT                                  (0x00000007UL)
#define EFM_FRMC_FLWT_0                                (0x00000001UL)
#define EFM_FRMC_FLWT_1                                (0x00000002UL)
#define EFM_FRMC_FLWT_2                                (0x00000004UL)
#define EFM_FRMC_ICHE_POS                              (16U)
#define EFM_FRMC_ICHE                                  (0x00010000UL)
#define EFM_FRMC_DCHE_POS                              (17U)
#define EFM_FRMC_DCHE                                  (0x00020000UL)
#define EFM_FRMC_CRST_POS                              (19U)
#define EFM_FRMC_CRST                                  (0x00080000UL)

/*  Bit definition for EFM_FWMC register  */
#define EFM_FWMC_PEMODE_POS                            (0U)
#define EFM_FWMC_PEMODE                                (0x00000001UL)
#define EFM_FWMC_PEMOD_POS                             (4U)
#define EFM_FWMC_PEMOD                                 (0x00000070UL)
#define EFM_FWMC_PEMOD_0                               (0x00000010UL)
#define EFM_FWMC_PEMOD_1                               (0x00000020UL)
#define EFM_FWMC_PEMOD_2                               (0x00000040UL)
#define EFM_FWMC_BUSHLDCTL_POS                         (8U)
#define EFM_FWMC_BUSHLDCTL                             (0x00000100UL)

/*  Bit definition for EFM_FSR register  */
#define EFM_FSR_PEWERR_POS                             (0U)
#define EFM_FSR_PEWERR                                 (0x00000001UL)
#define EFM_FSR_PEPRTERR_POS                           (1U)
#define EFM_FSR_PEPRTERR                               (0x00000002UL)
#define EFM_FSR_PGMISMTCH_POS                          (3U)
#define EFM_FSR_PGMISMTCH                              (0x00000008UL)
#define EFM_FSR_OPTEND_POS                             (4U)
#define EFM_FSR_OPTEND                                 (0x00000010UL)
#define EFM_FSR_RDCOLERR_POS                           (5U)
#define EFM_FSR_RDCOLERR                               (0x00000020UL)
#define EFM_FSR_RDY_POS                                (8U)
#define EFM_FSR_RDY                                    (0x00000100UL)

/*  Bit definition for EFM_FSCLR register  */
#define EFM_FSCLR_PEWERRCLR_POS                        (0U)
#define EFM_FSCLR_PEWERRCLR                            (0x00000001UL)
#define EFM_FSCLR_PEPRTERRCLR_POS                      (1U)
#define EFM_FSCLR_PEPRTERRCLR                          (0x00000002UL)
#define EFM_FSCLR_PGMISMTCHCLR_POS                     (3U)
#define EFM_FSCLR_PGMISMTCHCLR                         (0x00000008UL)
#define EFM_FSCLR_OPTENDCLR_POS                        (4U)
#define EFM_FSCLR_OPTENDCLR                            (0x00000010UL)
#define EFM_FSCLR_RDCOLERRCLR_POS                      (5U)
#define EFM_FSCLR_RDCOLERRCLR                          (0x00000020UL)

/*  Bit definition for EFM_FITE register  */
#define EFM_FITE_PEERRITE_POS                          (0U)
#define EFM_FITE_PEERRITE                              (0x00000001UL)
#define EFM_FITE_OPTENDITE_POS                         (1U)
#define EFM_FITE_OPTENDITE                             (0x00000002UL)
#define EFM_FITE_RDCOLERRITE_POS                       (2U)
#define EFM_FITE_RDCOLERRITE                           (0x00000004UL)

/*  Bit definition for EFM_FPMTSW register  */
#define EFM_FPMTSW_FPMTSW                              (0x0001FFFFUL)

/*  Bit definition for EFM_FPMTEW register  */
#define EFM_FPMTEW_FPMTEW                              (0x0001FFFFUL)

/*  Bit definition for EFM_UQID0 register  */
#define EFM_UQID0                                      (0xFFFFFFFFUL)

/*  Bit definition for EFM_UQID1 register  */
#define EFM_UQID1                                      (0xFFFFFFFFUL)

/*  Bit definition for EFM_UQID2 register  */
#define EFM_UQID2                                      (0xFFFFFFFFUL)

/*  Bit definition for EFM_UQID3 register  */
#define EFM_UQID3                                      (0xFFFFFFFFUL)

/*  Bit definition for EFM_HRCCFGR register  */
#define EFM_HRCCFGR_HRCFREQS                           (0x0FU)
#define EFM_HRCCFGR_HRCFREQS_0                         (0x01U)
#define EFM_HRCCFGR_HRCFREQS_1                         (0x02U)
#define EFM_HRCCFGR_HRCFREQS_2                         (0x04U)
#define EFM_HRCCFGR_HRCFREQS_3                         (0x08U)

/*******************************************************************************
                Bit definition for Peripheral EMB
*******************************************************************************/
/*  Bit definition for EMB_CTL register  */
#define EMB_CTL_CMPEN_POS                              (0U)
#define EMB_CTL_CMPEN                                  (0x00000007UL)
#define EMB_CTL_CMPEN_0                                (0x00000001UL)
#define EMB_CTL_CMPEN_1                                (0x00000002UL)
#define EMB_CTL_CMPEN_2                                (0x00000004UL)
#define EMB_CTL_OSCSTPEN_POS                           (4U)
#define EMB_CTL_OSCSTPEN                               (0x00000010UL)
#define EMB_CTL_PWMSEN0_POS                            (5U)
#define EMB_CTL_PWMSEN0                                (0x00000020UL)
#define EMB_CTL_PWMSEN1_POS                            (6U)
#define EMB_CTL_PWMSEN1                                (0x00000040UL)
#define EMB_CTL_PWMSEN2_POS                            (7U)
#define EMB_CTL_PWMSEN2                                (0x00000080UL)
#define EMB_CTL_PORTINEN0_POS                          (8U)
#define EMB_CTL_PORTINEN0                              (0x00000100UL)
#define EMB_CTL_PORTINEN1_POS                          (9U)
#define EMB_CTL_PORTINEN1                              (0x00000200UL)
#define EMB_CTL_PORTINEN2_POS                          (10U)
#define EMB_CTL_PORTINEN2                              (0x00000400UL)
#define EMB_CTL_NFSEL0_POS                             (16U)
#define EMB_CTL_NFSEL0                                 (0x00030000UL)
#define EMB_CTL_NFSEL0_0                               (0x00010000UL)
#define EMB_CTL_NFSEL0_1                               (0x00020000UL)
#define EMB_CTL_NFEN0_POS                              (18U)
#define EMB_CTL_NFEN0                                  (0x00040000UL)
#define EMB_CTL_INVSEL0_POS                            (19U)
#define EMB_CTL_INVSEL0                                (0x00080000UL)
#define EMB_CTL_NFSEL1_POS                             (20U)
#define EMB_CTL_NFSEL1                                 (0x00300000UL)
#define EMB_CTL_NFSEL1_0                               (0x00100000UL)
#define EMB_CTL_NFSEL1_1                               (0x00200000UL)
#define EMB_CTL_NFEN1_POS                              (22U)
#define EMB_CTL_NFEN1                                  (0x00400000UL)
#define EMB_CTL_INVSEL1_POS                            (23U)
#define EMB_CTL_INVSEL1                                (0x00800000UL)
#define EMB_CTL_NFSEL2_POS                             (24U)
#define EMB_CTL_NFSEL2                                 (0x03000000UL)
#define EMB_CTL_NFSEL2_0                               (0x01000000UL)
#define EMB_CTL_NFSEL2_1                               (0x02000000UL)
#define EMB_CTL_NFEN2_POS                              (26U)
#define EMB_CTL_NFEN2                                  (0x04000000UL)
#define EMB_CTL_INVSEL2_POS                            (27U)
#define EMB_CTL_INVSEL2                                (0x08000000UL)

/*  Bit definition for EMB_PWMLV register  */
#define EMB_PWMLV_PWMLV                                (0x00000007UL)
#define EMB_PWMLV_PWMLV_0                              (0x00000001UL)
#define EMB_PWMLV_PWMLV_1                              (0x00000002UL)
#define EMB_PWMLV_PWMLV_2                              (0x00000004UL)

/*  Bit definition for EMB_SOE register  */
#define EMB_SOE_SOE                                    (0x00000001UL)

/*  Bit definition for EMB_STAT register  */
#define EMB_STAT_PWMSF_POS                             (0U)
#define EMB_STAT_PWMSF                                 (0x00000001UL)
#define EMB_STAT_CMPF_POS                              (1U)
#define EMB_STAT_CMPF                                  (0x00000002UL)
#define EMB_STAT_OSF_POS                               (2U)
#define EMB_STAT_OSF                                   (0x00000004UL)
#define EMB_STAT_PWMST_POS                             (3U)
#define EMB_STAT_PWMST                                 (0x00000008UL)
#define EMB_STAT_PORTINF0_POS                          (8U)
#define EMB_STAT_PORTINF0                              (0x00000100UL)
#define EMB_STAT_PORTINF1_POS                          (9U)
#define EMB_STAT_PORTINF1                              (0x00000200UL)
#define EMB_STAT_PORTINF2_POS                          (10U)
#define EMB_STAT_PORTINF2                              (0x00000400UL)
#define EMB_STAT_PORTINST0_POS                         (12U)
#define EMB_STAT_PORTINST0                             (0x00001000UL)
#define EMB_STAT_PORTINST1_POS                         (13U)
#define EMB_STAT_PORTINST1                             (0x00002000UL)
#define EMB_STAT_PORTINST2_POS                         (14U)
#define EMB_STAT_PORTINST2                             (0x00004000UL)

/*  Bit definition for EMB_STATCLR register  */
#define EMB_STATCLR_PWMSFCLR_POS                       (0U)
#define EMB_STATCLR_PWMSFCLR                           (0x00000001UL)
#define EMB_STATCLR_CMPFCLR_POS                        (1U)
#define EMB_STATCLR_CMPFCLR                            (0x00000002UL)
#define EMB_STATCLR_OSFCLR_POS                         (2U)
#define EMB_STATCLR_OSFCLR                             (0x00000004UL)
#define EMB_STATCLR_PORTINFCLR0_POS                    (8U)
#define EMB_STATCLR_PORTINFCLR0                        (0x00000100UL)
#define EMB_STATCLR_PORTINFCLR1_POS                    (9U)
#define EMB_STATCLR_PORTINFCLR1                        (0x00000200UL)
#define EMB_STATCLR_PORTINFCLR2_POS                    (10U)
#define EMB_STATCLR_PORTINFCLR2                        (0x00000400UL)

/*  Bit definition for EMB_INTEN register  */
#define EMB_INTEN_PWMSINTEN_POS                        (0U)
#define EMB_INTEN_PWMSINTEN                            (0x00000001UL)
#define EMB_INTEN_CMPINTEN_POS                         (1U)
#define EMB_INTEN_CMPINTEN                             (0x00000002UL)
#define EMB_INTEN_OSINTEN_POS                          (2U)
#define EMB_INTEN_OSINTEN                              (0x00000004UL)
#define EMB_INTEN_PORTININTEN0_POS                     (8U)
#define EMB_INTEN_PORTININTEN0                         (0x00000100UL)
#define EMB_INTEN_PORTININTEN1_POS                     (9U)
#define EMB_INTEN_PORTININTEN1                         (0x00000200UL)
#define EMB_INTEN_PORTININTEN2_POS                     (10U)
#define EMB_INTEN_PORTININTEN2                         (0x00000400UL)

/*  Bit definition for EMB_ECSR register  */
#define EMB_ECSR_EMBVAL                                (0x00000003UL)
#define EMB_ECSR_EMBVAL_0                              (0x00000001UL)
#define EMB_ECSR_EMBVAL_1                              (0x00000002UL)

/*******************************************************************************
                Bit definition for Peripheral FCM
*******************************************************************************/
/*  Bit definition for FCM_LVR register  */
#define FCM_LVR_LVR                                    (0x0000FFFFUL)

/*  Bit definition for FCM_UVR register  */
#define FCM_UVR_UVR                                    (0x0000FFFFUL)

/*  Bit definition for FCM_CNTR register  */
#define FCM_CNTR_CNTR                                  (0x0000FFFFUL)

/*  Bit definition for FCM_STR register  */
#define FCM_STR_START                                  (0x00000001UL)

/*  Bit definition for FCM_MCCR register  */
#define FCM_MCCR_MDIVS_POS                             (0U)
#define FCM_MCCR_MDIVS                                 (0x00000003UL)
#define FCM_MCCR_MDIVS_0                               (0x00000001UL)
#define FCM_MCCR_MDIVS_1                               (0x00000002UL)
#define FCM_MCCR_MCKS_POS                              (4U)
#define FCM_MCCR_MCKS                                  (0x000000F0UL)

/*  Bit definition for FCM_RCCR register  */
#define FCM_RCCR_RDIVS_POS                             (0U)
#define FCM_RCCR_RDIVS                                 (0x00000003UL)
#define FCM_RCCR_RDIVS_0                               (0x00000001UL)
#define FCM_RCCR_RDIVS_1                               (0x00000002UL)
#define FCM_RCCR_RCKS_POS                              (3U)
#define FCM_RCCR_RCKS                                  (0x00000078UL)
#define FCM_RCCR_INEXS_POS                             (7U)
#define FCM_RCCR_INEXS                                 (0x00000080UL)
#define FCM_RCCR_DNFS_POS                              (8U)
#define FCM_RCCR_DNFS                                  (0x00000300UL)
#define FCM_RCCR_DNFS_0                                (0x00000100UL)
#define FCM_RCCR_DNFS_1                                (0x00000200UL)
#define FCM_RCCR_EDGES_POS                             (12U)
#define FCM_RCCR_EDGES                                 (0x00003000UL)
#define FCM_RCCR_EDGES_0                               (0x00001000UL)
#define FCM_RCCR_EDGES_1                               (0x00002000UL)
#define FCM_RCCR_EXREFE_POS                            (15U)
#define FCM_RCCR_EXREFE                                (0x00008000UL)

/*  Bit definition for FCM_RIER register  */
#define FCM_RIER_ERRIE_POS                             (0U)
#define FCM_RIER_ERRIE                                 (0x00000001UL)
#define FCM_RIER_MENDIE_POS                            (1U)
#define FCM_RIER_MENDIE                                (0x00000002UL)
#define FCM_RIER_OVFIE_POS                             (2U)
#define FCM_RIER_OVFIE                                 (0x00000004UL)
#define FCM_RIER_ERRINTRS_POS                          (4U)
#define FCM_RIER_ERRINTRS                              (0x00000010UL)
#define FCM_RIER_ERRE_POS                              (7U)
#define FCM_RIER_ERRE                                  (0x00000080UL)

/*  Bit definition for FCM_SR register  */
#define FCM_SR_ERRF_POS                                (0U)
#define FCM_SR_ERRF                                    (0x00000001UL)
#define FCM_SR_MENDF_POS                               (1U)
#define FCM_SR_MENDF                                   (0x00000002UL)
#define FCM_SR_OVF_POS                                 (2U)
#define FCM_SR_OVF                                     (0x00000004UL)

/*  Bit definition for FCM_CLR register  */
#define FCM_CLR_ERRFCLR_POS                            (0U)
#define FCM_CLR_ERRFCLR                                (0x00000001UL)
#define FCM_CLR_MENDFCLR_POS                           (1U)
#define FCM_CLR_MENDFCLR                               (0x00000002UL)
#define FCM_CLR_OVFCLR_POS                             (2U)
#define FCM_CLR_OVFCLR                                 (0x00000004UL)

/*******************************************************************************
                Bit definition for Peripheral GPIO
*******************************************************************************/
/*  Bit definition for GPIO_PIDR register  */
#define GPIO_PIDR_PIN0_POS                             (0U)
#define GPIO_PIDR_PIN0                                 (0x01U)
#define GPIO_PIDR_PIN1_POS                             (1U)
#define GPIO_PIDR_PIN1                                 (0x02U)
#define GPIO_PIDR_PIN2_POS                             (2U)
#define GPIO_PIDR_PIN2                                 (0x04U)
#define GPIO_PIDR_PIN3_POS                             (3U)
#define GPIO_PIDR_PIN3                                 (0x08U)
#define GPIO_PIDR_PIN4_POS                             (4U)
#define GPIO_PIDR_PIN4                                 (0x10U)
#define GPIO_PIDR_PIN5_POS                             (5U)
#define GPIO_PIDR_PIN5                                 (0x20U)
#define GPIO_PIDR_PIN6_POS                             (6U)
#define GPIO_PIDR_PIN6                                 (0x40U)
#define GPIO_PIDR_PIN7_POS                             (7U)
#define GPIO_PIDR_PIN7                                 (0x80U)

/*  Bit definition for GPIO_PODR register  */
#define GPIO_PODR_POUT0_POS                            (0U)
#define GPIO_PODR_POUT0                                (0x01U)
#define GPIO_PODR_POUT1_POS                            (1U)
#define GPIO_PODR_POUT1                                (0x02U)
#define GPIO_PODR_POUT2_POS                            (2U)
#define GPIO_PODR_POUT2                                (0x04U)
#define GPIO_PODR_POUT3_POS                            (3U)
#define GPIO_PODR_POUT3                                (0x08U)
#define GPIO_PODR_POUT4_POS                            (4U)
#define GPIO_PODR_POUT4                                (0x10U)
#define GPIO_PODR_POUT5_POS                            (5U)
#define GPIO_PODR_POUT5                                (0x20U)
#define GPIO_PODR_POUT6_POS                            (6U)
#define GPIO_PODR_POUT6                                (0x40U)
#define GPIO_PODR_POUT7_POS                            (7U)
#define GPIO_PODR_POUT7                                (0x80U)

/*  Bit definition for GPIO_POER register  */
#define GPIO_POER_POUTE0_POS                           (0U)
#define GPIO_POER_POUTE0                               (0x01U)
#define GPIO_POER_POUTE1_POS                           (1U)
#define GPIO_POER_POUTE1                               (0x02U)
#define GPIO_POER_POUTE2_POS                           (2U)
#define GPIO_POER_POUTE2                               (0x04U)
#define GPIO_POER_POUTE3_POS                           (3U)
#define GPIO_POER_POUTE3                               (0x08U)
#define GPIO_POER_POUTE4_POS                           (4U)
#define GPIO_POER_POUTE4                               (0x10U)
#define GPIO_POER_POUTE5_POS                           (5U)
#define GPIO_POER_POUTE5                               (0x20U)
#define GPIO_POER_POUTE6_POS                           (6U)
#define GPIO_POER_POUTE6                               (0x40U)
#define GPIO_POER_POUTE7_POS                           (7U)
#define GPIO_POER_POUTE7                               (0x80U)

/*  Bit definition for GPIO_POSR register  */
#define GPIO_POSR_POS0_POS                             (0U)
#define GPIO_POSR_POS0                                 (0x01U)
#define GPIO_POSR_POS1_POS                             (1U)
#define GPIO_POSR_POS1                                 (0x02U)
#define GPIO_POSR_POS2_POS                             (2U)
#define GPIO_POSR_POS2                                 (0x04U)
#define GPIO_POSR_POS3_POS                             (3U)
#define GPIO_POSR_POS3                                 (0x08U)
#define GPIO_POSR_POS4_POS                             (4U)
#define GPIO_POSR_POS4                                 (0x10U)
#define GPIO_POSR_POS5_POS                             (5U)
#define GPIO_POSR_POS5                                 (0x20U)
#define GPIO_POSR_POS6_POS                             (6U)
#define GPIO_POSR_POS6                                 (0x40U)
#define GPIO_POSR_POS7_POS                             (7U)
#define GPIO_POSR_POS7                                 (0x80U)

/*  Bit definition for GPIO_PORR register  */
#define GPIO_PORR_POR0_POS                             (0U)
#define GPIO_PORR_POR0                                 (0x01U)
#define GPIO_PORR_POR1_POS                             (1U)
#define GPIO_PORR_POR1                                 (0x02U)
#define GPIO_PORR_POR2_POS                             (2U)
#define GPIO_PORR_POR2                                 (0x04U)
#define GPIO_PORR_POR3_POS                             (3U)
#define GPIO_PORR_POR3                                 (0x08U)
#define GPIO_PORR_POR4_POS                             (4U)
#define GPIO_PORR_POR4                                 (0x10U)
#define GPIO_PORR_POR5_POS                             (5U)
#define GPIO_PORR_POR5                                 (0x20U)
#define GPIO_PORR_POR6_POS                             (6U)
#define GPIO_PORR_POR6                                 (0x40U)
#define GPIO_PORR_POR7_POS                             (7U)
#define GPIO_PORR_POR7                                 (0x80U)

/*  Bit definition for GPIO_POTR register  */
#define GPIO_POTR_POT0_POS                             (0U)
#define GPIO_POTR_POT0                                 (0x01U)
#define GPIO_POTR_POT1_POS                             (1U)
#define GPIO_POTR_POT1                                 (0x02U)
#define GPIO_POTR_POT2_POS                             (2U)
#define GPIO_POTR_POT2                                 (0x04U)
#define GPIO_POTR_POT3_POS                             (3U)
#define GPIO_POTR_POT3                                 (0x08U)
#define GPIO_POTR_POT4_POS                             (4U)
#define GPIO_POTR_POT4                                 (0x10U)
#define GPIO_POTR_POT5_POS                             (5U)
#define GPIO_POTR_POT5                                 (0x20U)
#define GPIO_POTR_POT6_POS                             (6U)
#define GPIO_POTR_POT6                                 (0x40U)
#define GPIO_POTR_POT7_POS                             (7U)
#define GPIO_POTR_POT7                                 (0x80U)

/*  Bit definition for GPIO_PSPCR register  */
#define GPIO_PSPCR_SPFE                                (0x001FU)
#define GPIO_PSPCR_SPFE_0                              (0x0001U)
#define GPIO_PSPCR_SPFE_1                              (0x0002U)
#define GPIO_PSPCR_SPFE_2                              (0x0004U)
#define GPIO_PSPCR_SPFE_3                              (0x0008U)
#define GPIO_PSPCR_SPFE_4                              (0x0010U)

/*  Bit definition for GPIO_PCCR register  */
#define GPIO_PCCR_RDWT_POS                             (14U)
#define GPIO_PCCR_RDWT                                 (0xC000U)
#define GPIO_PCCR_RDWT_0                               (0x4000U)
#define GPIO_PCCR_RDWT_1                               (0x8000U)

/*  Bit definition for GPIO_PINAER register  */
#define GPIO_PINAER_PINAE0_POS                         (0U)
#define GPIO_PINAER_PINAE0                             (0x0001U)
#define GPIO_PINAER_PINAE1_POS                         (1U)
#define GPIO_PINAER_PINAE1                             (0x0002U)
#define GPIO_PINAER_PINAE2_POS                         (2U)
#define GPIO_PINAER_PINAE2                             (0x0004U)
#define GPIO_PINAER_PINAE3_POS                         (3U)
#define GPIO_PINAER_PINAE3                             (0x0008U)
#define GPIO_PINAER_PINAE4_POS                         (4U)
#define GPIO_PINAER_PINAE4                             (0x0010U)
#define GPIO_PINAER_PINAE5_POS                         (5U)
#define GPIO_PINAER_PINAE5                             (0x0020U)
#define GPIO_PINAER_PINAE7_POS                         (7U)
#define GPIO_PINAER_PINAE7                             (0x0080U)
#define GPIO_PINAER_PINAE9_POS                         (9U)
#define GPIO_PINAER_PINAE9                             (0x0200U)
#define GPIO_PINAER_PINAE10_POS                        (10U)
#define GPIO_PINAER_PINAE10                            (0x0400U)
#define GPIO_PINAER_PINAE11_POS                        (11U)
#define GPIO_PINAER_PINAE11                            (0x0800U)
#define GPIO_PINAER_PINAE13_POS                        (13U)
#define GPIO_PINAER_PINAE13                            (0x2000U)
#define GPIO_PINAER_PINAE14_POS                        (14U)
#define GPIO_PINAER_PINAE14                            (0x4000U)

/*  Bit definition for GPIO_PWPR register  */
#define GPIO_PWPR_WE_POS                               (0U)
#define GPIO_PWPR_WE                                   (0x0001U)
#define GPIO_PWPR_WP_POS                               (8U)
#define GPIO_PWPR_WP                                   (0xFF00U)

/*  Bit definition for GPIO_PCR register  */
#define GPIO_PCR_POUT_POS                              (0U)
#define GPIO_PCR_POUT                                  (0x0001U)
#define GPIO_PCR_POUTE_POS                             (1U)
#define GPIO_PCR_POUTE                                 (0x0002U)
#define GPIO_PCR_NOD_POS                               (2U)
#define GPIO_PCR_NOD                                   (0x0004U)
#define GPIO_PCR_DRV_POS                               (4U)
#define GPIO_PCR_DRV                                   (0x0010U)
#define GPIO_PCR_LTE_POS                               (5U)
#define GPIO_PCR_LTE                                   (0x0020U)
#define GPIO_PCR_PUU_POS                               (6U)
#define GPIO_PCR_PUU                                   (0x0040U)
#define GPIO_PCR_PIN_POS                               (8U)
#define GPIO_PCR_PIN                                   (0x0100U)
#define GPIO_PCR_INVE_POS                              (9U)
#define GPIO_PCR_INVE                                  (0x0200U)
#define GPIO_PCR_CINSEL_POS                            (10U)
#define GPIO_PCR_CINSEL                                (0x0400U)
#define GPIO_PCR_INTE_POS                              (11U)
#define GPIO_PCR_INTE                                  (0x0800U)

/*  Bit definition for GPIO_PFSR register  */
#define GPIO_PFSR_FSEL                                 (0x0007U)

/*******************************************************************************
                Bit definition for Peripheral I2C
*******************************************************************************/
/*  Bit definition for I2C_CR1 register  */
#define I2C_CR1_PE_POS                                 (0U)
#define I2C_CR1_PE                                     (0x00000001UL)
#define I2C_CR1_SMBUS_POS                              (1U)
#define I2C_CR1_SMBUS                                  (0x00000002UL)
#define I2C_CR1_SMBALRTEN_POS                          (2U)
#define I2C_CR1_SMBALRTEN                              (0x00000004UL)
#define I2C_CR1_SMBDEFAULTEN_POS                       (3U)
#define I2C_CR1_SMBDEFAULTEN                           (0x00000008UL)
#define I2C_CR1_SMBHOSTEN_POS                          (4U)
#define I2C_CR1_SMBHOSTEN                              (0x00000010UL)
#define I2C_CR1_FACKEN_POS                             (5U)
#define I2C_CR1_FACKEN                                 (0x00000020UL)
#define I2C_CR1_GCEN_POS                               (6U)
#define I2C_CR1_GCEN                                   (0x00000040UL)
#define I2C_CR1_RESTART_POS                            (7U)
#define I2C_CR1_RESTART                                (0x00000080UL)
#define I2C_CR1_START_POS                              (8U)
#define I2C_CR1_START                                  (0x00000100UL)
#define I2C_CR1_STOP_POS                               (9U)
#define I2C_CR1_STOP                                   (0x00000200UL)
#define I2C_CR1_ACK_POS                                (10U)
#define I2C_CR1_ACK                                    (0x00000400UL)
#define I2C_CR1_SWRST_POS                              (15U)
#define I2C_CR1_SWRST                                  (0x00008000UL)

/*  Bit definition for I2C_CR2 register  */
#define I2C_CR2_STARTIE_POS                            (0U)
#define I2C_CR2_STARTIE                                (0x00000001UL)
#define I2C_CR2_SLADDR0IE_POS                          (1U)
#define I2C_CR2_SLADDR0IE                              (0x00000002UL)
#define I2C_CR2_SLADDR1IE_POS                          (2U)
#define I2C_CR2_SLADDR1IE                              (0x00000004UL)
#define I2C_CR2_TENDIE_POS                             (3U)
#define I2C_CR2_TENDIE                                 (0x00000008UL)
#define I2C_CR2_STOPIE_POS                             (4U)
#define I2C_CR2_STOPIE                                 (0x00000010UL)
#define I2C_CR2_RFULLIE_POS                            (6U)
#define I2C_CR2_RFULLIE                                (0x00000040UL)
#define I2C_CR2_TEMPTYIE_POS                           (7U)
#define I2C_CR2_TEMPTYIE                               (0x00000080UL)
#define I2C_CR2_ARLOIE_POS                             (9U)
#define I2C_CR2_ARLOIE                                 (0x00000200UL)
#define I2C_CR2_NACKIE_POS                             (12U)
#define I2C_CR2_NACKIE                                 (0x00001000UL)
#define I2C_CR2_GENCALLIE_POS                          (20U)
#define I2C_CR2_GENCALLIE                              (0x00100000UL)
#define I2C_CR2_SMBDEFAULTIE_POS                       (21U)
#define I2C_CR2_SMBDEFAULTIE                           (0x00200000UL)
#define I2C_CR2_SMBHOSTIE_POS                          (22U)
#define I2C_CR2_SMBHOSTIE                              (0x00400000UL)
#define I2C_CR2_SMBALRTIE_POS                          (23U)
#define I2C_CR2_SMBALRTIE                              (0x00800000UL)

/*  Bit definition for I2C_SLR0 register  */
#define I2C_SLR0_SLADDR0_POS                           (0U)
#define I2C_SLR0_SLADDR0                               (0x000003FFUL)
#define I2C_SLR0_SLADDR0EN_POS                         (12U)
#define I2C_SLR0_SLADDR0EN                             (0x00001000UL)
#define I2C_SLR0_ADDRMOD0_POS                          (15U)
#define I2C_SLR0_ADDRMOD0                              (0x00008000UL)

/*  Bit definition for I2C_SLR1 register  */
#define I2C_SLR1_SLADDR1_POS                           (0U)
#define I2C_SLR1_SLADDR1                               (0x000003FFUL)
#define I2C_SLR1_SLADDR1EN_POS                         (12U)
#define I2C_SLR1_SLADDR1EN                             (0x00001000UL)
#define I2C_SLR1_ADDRMOD1_POS                          (15U)
#define I2C_SLR1_ADDRMOD1                              (0x00008000UL)

/*  Bit definition for I2C_SR register  */
#define I2C_SR_STARTF_POS                              (0U)
#define I2C_SR_STARTF                                  (0x00000001UL)
#define I2C_SR_SLADDR0F_POS                            (1U)
#define I2C_SR_SLADDR0F                                (0x00000002UL)
#define I2C_SR_SLADDR1F_POS                            (2U)
#define I2C_SR_SLADDR1F                                (0x00000004UL)
#define I2C_SR_TENDF_POS                               (3U)
#define I2C_SR_TENDF                                   (0x00000008UL)
#define I2C_SR_STOPF_POS                               (4U)
#define I2C_SR_STOPF                                   (0x00000010UL)
#define I2C_SR_RFULLF_POS                              (6U)
#define I2C_SR_RFULLF                                  (0x00000040UL)
#define I2C_SR_TEMPTYF_POS                             (7U)
#define I2C_SR_TEMPTYF                                 (0x00000080UL)
#define I2C_SR_ARLOF_POS                               (9U)
#define I2C_SR_ARLOF                                   (0x00000200UL)
#define I2C_SR_ACKRF_POS                               (10U)
#define I2C_SR_ACKRF                                   (0x00000400UL)
#define I2C_SR_NACKF_POS                               (12U)
#define I2C_SR_NACKF                                   (0x00001000UL)
#define I2C_SR_MSL_POS                                 (16U)
#define I2C_SR_MSL                                     (0x00010000UL)
#define I2C_SR_BUSY_POS                                (17U)
#define I2C_SR_BUSY                                    (0x00020000UL)
#define I2C_SR_TRA_POS                                 (18U)
#define I2C_SR_TRA                                     (0x00040000UL)
#define I2C_SR_GENCALLF_POS                            (20U)
#define I2C_SR_GENCALLF                                (0x00100000UL)
#define I2C_SR_SMBDEFAULTF_POS                         (21U)
#define I2C_SR_SMBDEFAULTF                             (0x00200000UL)
#define I2C_SR_SMBHOSTF_POS                            (22U)
#define I2C_SR_SMBHOSTF                                (0x00400000UL)
#define I2C_SR_SMBALRTF_POS                            (23U)
#define I2C_SR_SMBALRTF                                (0x00800000UL)

/*  Bit definition for I2C_CLR register  */
#define I2C_CLR_STARTFCLR_POS                          (0U)
#define I2C_CLR_STARTFCLR                              (0x00000001UL)
#define I2C_CLR_SLADDR0FCLR_POS                        (1U)
#define I2C_CLR_SLADDR0FCLR                            (0x00000002UL)
#define I2C_CLR_SLADDR1FCLR_POS                        (2U)
#define I2C_CLR_SLADDR1FCLR                            (0x00000004UL)
#define I2C_CLR_TENDFCLR_POS                           (3U)
#define I2C_CLR_TENDFCLR                               (0x00000008UL)
#define I2C_CLR_STOPFCLR_POS                           (4U)
#define I2C_CLR_STOPFCLR                               (0x00000010UL)
#define I2C_CLR_RFULLFCLR_POS                          (6U)
#define I2C_CLR_RFULLFCLR                              (0x00000040UL)
#define I2C_CLR_TEMPTYFCLR_POS                         (7U)
#define I2C_CLR_TEMPTYFCLR                             (0x00000080UL)
#define I2C_CLR_ARLOFCLR_POS                           (9U)
#define I2C_CLR_ARLOFCLR                               (0x00000200UL)
#define I2C_CLR_NACKFCLR_POS                           (12U)
#define I2C_CLR_NACKFCLR                               (0x00001000UL)
#define I2C_CLR_GENCALLFCLR_POS                        (20U)
#define I2C_CLR_GENCALLFCLR                            (0x00100000UL)
#define I2C_CLR_SMBDEFAULTF_POS                        (21U)
#define I2C_CLR_SMBDEFAULTF                            (0x00200000UL)
#define I2C_CLR_SMBHOSTFCL_POS                         (22U)
#define I2C_CLR_SMBHOSTFCL                             (0x00400000UL)
#define I2C_CLR_SMBALRTFCLR_POS                        (23U)
#define I2C_CLR_SMBALRTFCLR                            (0x00800000UL)

/*  Bit definition for I2C_DTR register  */
#define I2C_DTR_DT                                     (0xFFU)

/*  Bit definition for I2C_DRR register  */
#define I2C_DRR_DR                                     (0xFFU)

/*  Bit definition for I2C_CCR register  */
#define I2C_CCR_SLOWW_POS                              (0U)
#define I2C_CCR_SLOWW                                  (0x0000001FUL)
#define I2C_CCR_SHIGHW_POS                             (8U)
#define I2C_CCR_SHIGHW                                 (0x00001F00UL)
#define I2C_CCR_CKDIV_POS                              (16U)
#define I2C_CCR_CKDIV                                  (0x00070000UL)
#define I2C_CCR_CKDIV_0                                (0x00010000UL)
#define I2C_CCR_CKDIV_1                                (0x00020000UL)
#define I2C_CCR_CKDIV_2                                (0x00040000UL)
#define I2C_CCR_FMPE_POS                               (23U)
#define I2C_CCR_FMPE                                   (0x00800000UL)

/*  Bit definition for I2C_FLTR register  */
#define I2C_FLTR_DNF_POS                               (0U)
#define I2C_FLTR_DNF                                   (0x00000003UL)
#define I2C_FLTR_DNF_0                                 (0x00000001UL)
#define I2C_FLTR_DNF_1                                 (0x00000002UL)
#define I2C_FLTR_DNFEN_POS                             (4U)
#define I2C_FLTR_DNFEN                                 (0x00000010UL)
#define I2C_FLTR_ANFEN_POS                             (5U)
#define I2C_FLTR_ANFEN                                 (0x00000020UL)

/*******************************************************************************
                Bit definition for Peripheral ICG
*******************************************************************************/
/*  Bit definition for ICG_ICG0 register  */
#define ICG_ICG0_SWDTAUTST_POS                         (0U)
#define ICG_ICG0_SWDTAUTST                             (0x00000001UL)
#define ICG_ICG0_SWDTITS_POS                           (1U)
#define ICG_ICG0_SWDTITS                               (0x00000002UL)
#define ICG_ICG0_SWDTPERI_POS                          (2U)
#define ICG_ICG0_SWDTPERI                              (0x0000000CUL)
#define ICG_ICG0_SWDTPERI_0                            (0x00000004UL)
#define ICG_ICG0_SWDTPERI_1                            (0x00000008UL)
#define ICG_ICG0_SWDTCKS_POS                           (4U)
#define ICG_ICG0_SWDTCKS                               (0x000000F0UL)
#define ICG_ICG0_SWDTCKS_0                             (0x00000010UL)
#define ICG_ICG0_SWDTCKS_1                             (0x00000020UL)
#define ICG_ICG0_SWDTCKS_2                             (0x00000040UL)
#define ICG_ICG0_SWDTCKS_3                             (0x00000080UL)
#define ICG_ICG0_SWDTWDPT_POS                          (8U)
#define ICG_ICG0_SWDTWDPT                              (0x00000F00UL)
#define ICG_ICG0_SWDTWDPT_0                            (0x00000100UL)
#define ICG_ICG0_SWDTWDPT_1                            (0x00000200UL)
#define ICG_ICG0_SWDTWDPT_2                            (0x00000400UL)
#define ICG_ICG0_SWDTWDPT_3                            (0x00000800UL)
#define ICG_ICG0_SWDTSLPOFF_POS                        (12U)
#define ICG_ICG0_SWDTSLPOFF                            (0x00001000UL)
#define ICG_ICG0_HRCFRQSEL_POS                         (16U)
#define ICG_ICG0_HRCFRQSEL                             (0x000F0000UL)
#define ICG_ICG0_HRCFRQSEL_0                           (0x00010000UL)
#define ICG_ICG0_HRCFRQSEL_1                           (0x00020000UL)
#define ICG_ICG0_HRCFRQSEL_2                           (0x00040000UL)
#define ICG_ICG0_HRCFRQSEL_3                           (0x00080000UL)
#define ICG_ICG0_HRCSTOP_POS                           (20U)
#define ICG_ICG0_HRCSTOP                               (0x00100000UL)
#define ICG_ICG0_NMIFCLK_POS                           (26U)
#define ICG_ICG0_NMIFCLK                               (0x0C000000UL)
#define ICG_ICG0_NMIFCLK_0                             (0x04000000UL)
#define ICG_ICG0_NMIFCLK_1                             (0x08000000UL)
#define ICG_ICG0_NMIFEN_POS                            (28U)
#define ICG_ICG0_NMIFEN                                (0x10000000UL)
#define ICG_ICG0_NMITRG_POS                            (29U)
#define ICG_ICG0_NMITRG                                (0x20000000UL)
#define ICG_ICG0_NMIEN_POS                             (30U)
#define ICG_ICG0_NMIEN                                 (0x40000000UL)
#define ICG_ICG0_NMIICGEN_POS                          (31U)
#define ICG_ICG0_NMIICGEN                              (0x80000000UL)

/*  Bit definition for ICG_ICG1 register  */
#define ICG_ICG1_LKUPDIS_POS                           (8U)
#define ICG_ICG1_LKUPDIS                               (0x00000100UL)
#define ICG_ICG1_LVD0LVL_POS                           (12U)
#define ICG_ICG1_LVD0LVL                               (0x00007000UL)
#define ICG_ICG1_LVD0LVL_0                             (0x00001000UL)
#define ICG_ICG1_LVD0LVL_1                             (0x00002000UL)
#define ICG_ICG1_LVD0LVL_2                             (0x00004000UL)
#define ICG_ICG1_LVD0DIS_POS                           (15U)
#define ICG_ICG1_LVD0DIS                               (0x00008000UL)

/*  Bit definition for ICG_ICG2 register  */
#define ICG_ICG2                                       (0xFFFFFFFFUL)

/*  Bit definition for ICG_ICG3 register  */
#define ICG_ICG3                                       (0xFFFFFFFFUL)

/*  Bit definition for ICG_ICG4 register  */
#define ICG_ICG4                                       (0xFFFFFFFFUL)

/*  Bit definition for ICG_ICG5 register  */
#define ICG_ICG5                                       (0xFFFFFFFFUL)

/*  Bit definition for ICG_ICG6 register  */
#define ICG_ICG6                                       (0xFFFFFFFFUL)

/*  Bit definition for ICG_ICG7 register  */
#define ICG_ICG7_WDTAUTST_POS                          (0U)
#define ICG_ICG7_WDTAUTST                              (0x00000001UL)
#define ICG_ICG7_WDTITS_POS                            (1U)
#define ICG_ICG7_WDTITS                                (0x00000002UL)
#define ICG_ICG7_WDTPERI_POS                           (2U)
#define ICG_ICG7_WDTPERI                               (0x0000000CUL)
#define ICG_ICG7_WDTPERI_0                             (0x00000004UL)
#define ICG_ICG7_WDTPERI_1                             (0x00000008UL)
#define ICG_ICG7_WDTCKS_POS                            (4U)
#define ICG_ICG7_WDTCKS                                (0x000000F0UL)
#define ICG_ICG7_WDTCKS_0                              (0x00000010UL)
#define ICG_ICG7_WDTCKS_1                              (0x00000020UL)
#define ICG_ICG7_WDTCKS_2                              (0x00000040UL)
#define ICG_ICG7_WDTCKS_3                              (0x00000080UL)
#define ICG_ICG7_WDTWDPT_POS                           (8U)
#define ICG_ICG7_WDTWDPT                               (0x00000F00UL)
#define ICG_ICG7_WDTWDPT_0                             (0x00000100UL)
#define ICG_ICG7_WDTWDPT_1                             (0x00000200UL)
#define ICG_ICG7_WDTWDPT_2                             (0x00000400UL)
#define ICG_ICG7_WDTWDPT_3                             (0x00000800UL)
#define ICG_ICG7_WDTSLPOFF_POS                         (12U)
#define ICG_ICG7_WDTSLPOFF                             (0x00001000UL)

/*******************************************************************************
                Bit definition for Peripheral INTC
*******************************************************************************/
/*  Bit definition for INTC_NMICR register  */
#define INTC_NMICR_NMITRG_POS                          (0U)
#define INTC_NMICR_NMITRG                              (0x00000001UL)
#define INTC_NMICR_NMIFCLK_POS                         (4U)
#define INTC_NMICR_NMIFCLK                             (0x00000030UL)
#define INTC_NMICR_NMIFCLK_0                           (0x00000010UL)
#define INTC_NMICR_NMIFCLK_1                           (0x00000020UL)
#define INTC_NMICR_NMIFEN_POS                          (7U)
#define INTC_NMICR_NMIFEN                              (0x00000080UL)
#define INTC_NMICR_NOCSEL_POS                          (12U)
#define INTC_NMICR_NOCSEL                              (0x00003000UL)
#define INTC_NMICR_NOCSEL_0                            (0x00001000UL)
#define INTC_NMICR_NOCSEL_1                            (0x00002000UL)
#define INTC_NMICR_NOCEN_POS                           (15U)
#define INTC_NMICR_NOCEN                               (0x00008000UL)

/*  Bit definition for INTC_NMIER register  */
#define INTC_NMIER_NMIENR_POS                          (0U)
#define INTC_NMIER_NMIENR                              (0x00000001UL)
#define INTC_NMIER_SWDTENR_POS                         (1U)
#define INTC_NMIER_SWDTENR                             (0x00000002UL)
#define INTC_NMIER_PVD1ENR_POS                         (2U)
#define INTC_NMIER_PVD1ENR                             (0x00000004UL)
#define INTC_NMIER_PVD2ENR_POS                         (3U)
#define INTC_NMIER_PVD2ENR                             (0x00000008UL)
#define INTC_NMIER_XTALSTPENR_POS                      (5U)
#define INTC_NMIER_XTALSTPENR                          (0x00000020UL)
#define INTC_NMIER_REPENR_POS                          (8U)
#define INTC_NMIER_REPENR                              (0x00000100UL)
#define INTC_NMIER_WDTENR_POS                          (11U)
#define INTC_NMIER_WDTENR                              (0x00000800UL)

/*  Bit definition for INTC_NMIFR register  */
#define INTC_NMIFR_NMIFR_POS                           (0U)
#define INTC_NMIFR_NMIFR                               (0x00000001UL)
#define INTC_NMIFR_SWDTFR_POS                          (1U)
#define INTC_NMIFR_SWDTFR                              (0x00000002UL)
#define INTC_NMIFR_PVD1FR_POS                          (2U)
#define INTC_NMIFR_PVD1FR                              (0x00000004UL)
#define INTC_NMIFR_PVD2FR_POS                          (3U)
#define INTC_NMIFR_PVD2FR                              (0x00000008UL)
#define INTC_NMIFR_XTALSTPFR_POS                       (5U)
#define INTC_NMIFR_XTALSTPFR                           (0x00000020UL)
#define INTC_NMIFR_REPFR_POS                           (8U)
#define INTC_NMIFR_REPFR                               (0x00000100UL)
#define INTC_NMIFR_WDTFR_POS                           (11U)
#define INTC_NMIFR_WDTFR                               (0x00000800UL)

/*  Bit definition for INTC_NMICFR register  */
#define INTC_NMICFR_NMICFR_POS                         (0U)
#define INTC_NMICFR_NMICFR                             (0x00000001UL)
#define INTC_NMICFR_SWDTCFR_POS                        (1U)
#define INTC_NMICFR_SWDTCFR                            (0x00000002UL)
#define INTC_NMICFR_PVD1CFR_POS                        (2U)
#define INTC_NMICFR_PVD1CFR                            (0x00000004UL)
#define INTC_NMICFR_PVD2CFR_POS                        (3U)
#define INTC_NMICFR_PVD2CFR                            (0x00000008UL)
#define INTC_NMICFR_XTALSTPCFR_POS                     (5U)
#define INTC_NMICFR_XTALSTPCFR                         (0x00000020UL)
#define INTC_NMICFR_REPCFR_POS                         (8U)
#define INTC_NMICFR_REPCFR                             (0x00000100UL)
#define INTC_NMICFR_WDTCFR_POS                         (11U)
#define INTC_NMICFR_WDTCFR                             (0x00000800UL)

/*  Bit definition for INTC_EIRQCR register  */
#define INTC_EIRQCR_EIRQTRG_POS                        (0U)
#define INTC_EIRQCR_EIRQTRG                            (0x00000003UL)
#define INTC_EIRQCR_EIRQTRG_0                          (0x00000001UL)
#define INTC_EIRQCR_EIRQTRG_1                          (0x00000002UL)
#define INTC_EIRQCR_EISMPCLK_POS                       (4U)
#define INTC_EIRQCR_EISMPCLK                           (0x00000030UL)
#define INTC_EIRQCR_EISMPCLK_0                         (0x00000010UL)
#define INTC_EIRQCR_EISMPCLK_1                         (0x00000020UL)
#define INTC_EIRQCR_EFEN_POS                           (7U)
#define INTC_EIRQCR_EFEN                               (0x00000080UL)
#define INTC_EIRQCR_NOCEN_POS                          (15U)
#define INTC_EIRQCR_NOCEN                              (0x00008000UL)

/*  Bit definition for INTC_WUPEN register  */
#define INTC_WUPEN_EIRQWUEN_POS                        (0U)
#define INTC_WUPEN_EIRQWUEN                            (0x000000FFUL)
#define INTC_WUPEN_EIRQWUEN_0                          (0x00000001UL)
#define INTC_WUPEN_EIRQWUEN_1                          (0x00000002UL)
#define INTC_WUPEN_EIRQWUEN_2                          (0x00000004UL)
#define INTC_WUPEN_EIRQWUEN_3                          (0x00000008UL)
#define INTC_WUPEN_EIRQWUEN_4                          (0x00000010UL)
#define INTC_WUPEN_EIRQWUEN_5                          (0x00000020UL)
#define INTC_WUPEN_EIRQWUEN_6                          (0x00000040UL)
#define INTC_WUPEN_EIRQWUEN_7                          (0x00000080UL)
#define INTC_WUPEN_SWDTWUEN_POS                        (16U)
#define INTC_WUPEN_SWDTWUEN                            (0x00010000UL)
#define INTC_WUPEN_PVD1WUEN_POS                        (17U)
#define INTC_WUPEN_PVD1WUEN                            (0x00020000UL)
#define INTC_WUPEN_PVD2WUEN_POS                        (18U)
#define INTC_WUPEN_PVD2WUEN                            (0x00040000UL)
#define INTC_WUPEN_CMPI0WUEN_POS                       (19U)
#define INTC_WUPEN_CMPI0WUEN                           (0x00080000UL)
#define INTC_WUPEN_TMR0WUEN_POS                        (23U)
#define INTC_WUPEN_TMR0WUEN                            (0x00800000UL)
#define INTC_WUPEN_RXWUEN_POS                          (25U)
#define INTC_WUPEN_RXWUEN                              (0x02000000UL)

/*  Bit definition for INTC_EIRQFR register  */
#define INTC_EIRQFR_EIRQFR                             (0x000000FFUL)
#define INTC_EIRQFR_EIRQFR_0                           (0x00000001UL)
#define INTC_EIRQFR_EIRQFR_1                           (0x00000002UL)
#define INTC_EIRQFR_EIRQFR_2                           (0x00000004UL)
#define INTC_EIRQFR_EIRQFR_3                           (0x00000008UL)
#define INTC_EIRQFR_EIRQFR_4                           (0x00000010UL)
#define INTC_EIRQFR_EIRQFR_5                           (0x00000020UL)
#define INTC_EIRQFR_EIRQFR_6                           (0x00000040UL)
#define INTC_EIRQFR_EIRQFR_7                           (0x00000080UL)

/*  Bit definition for INTC_EIRQCFR register  */
#define INTC_EIRQCFR_EIRQCFR                           (0x000000FFUL)
#define INTC_EIRQCFR_EIRQCFR_0                         (0x00000001UL)
#define INTC_EIRQCFR_EIRQCFR_1                         (0x00000002UL)
#define INTC_EIRQCFR_EIRQCFR_2                         (0x00000004UL)
#define INTC_EIRQCFR_EIRQCFR_3                         (0x00000008UL)
#define INTC_EIRQCFR_EIRQCFR_4                         (0x00000010UL)
#define INTC_EIRQCFR_EIRQCFR_5                         (0x00000020UL)
#define INTC_EIRQCFR_EIRQCFR_6                         (0x00000040UL)
#define INTC_EIRQCFR_EIRQCFR_7                         (0x00000080UL)

/*  Bit definition for INTC_SEL register  */
#define INTC_SEL_ISEL                                  (0x000001FFUL)

/*  Bit definition for INTC_SWIER register  */
#define INTC_SWIER_SWIE0_POS                           (0U)
#define INTC_SWIER_SWIE0                               (0x00000001UL)
#define INTC_SWIER_SWIE1_POS                           (1U)
#define INTC_SWIER_SWIE1                               (0x00000002UL)
#define INTC_SWIER_SWIE2_POS                           (2U)
#define INTC_SWIER_SWIE2                               (0x00000004UL)
#define INTC_SWIER_SWIE3_POS                           (3U)
#define INTC_SWIER_SWIE3                               (0x00000008UL)
#define INTC_SWIER_SWIE4_POS                           (4U)
#define INTC_SWIER_SWIE4                               (0x00000010UL)
#define INTC_SWIER_SWIE5_POS                           (5U)
#define INTC_SWIER_SWIE5                               (0x00000020UL)
#define INTC_SWIER_SWIE6_POS                           (6U)
#define INTC_SWIER_SWIE6                               (0x00000040UL)
#define INTC_SWIER_SWIE7_POS                           (7U)
#define INTC_SWIER_SWIE7                               (0x00000080UL)
#define INTC_SWIER_SWIE8_POS                           (8U)
#define INTC_SWIER_SWIE8                               (0x00000100UL)
#define INTC_SWIER_SWIE9_POS                           (9U)
#define INTC_SWIER_SWIE9                               (0x00000200UL)
#define INTC_SWIER_SWIE10_POS                          (10U)
#define INTC_SWIER_SWIE10                              (0x00000400UL)
#define INTC_SWIER_SWIE11_POS                          (11U)
#define INTC_SWIER_SWIE11                              (0x00000800UL)
#define INTC_SWIER_SWIE12_POS                          (12U)
#define INTC_SWIER_SWIE12                              (0x00001000UL)
#define INTC_SWIER_SWIE13_POS                          (13U)
#define INTC_SWIER_SWIE13                              (0x00002000UL)
#define INTC_SWIER_SWIE14_POS                          (14U)
#define INTC_SWIER_SWIE14                              (0x00004000UL)
#define INTC_SWIER_SWIE15_POS                          (15U)
#define INTC_SWIER_SWIE15                              (0x00008000UL)

/*  Bit definition for INTC_EVTER register  */
#define INTC_EVTER_EVTE0_POS                           (0U)
#define INTC_EVTER_EVTE0                               (0x00000001UL)
#define INTC_EVTER_EVTE1_POS                           (1U)
#define INTC_EVTER_EVTE1                               (0x00000002UL)
#define INTC_EVTER_EVTE2_POS                           (2U)
#define INTC_EVTER_EVTE2                               (0x00000004UL)
#define INTC_EVTER_EVTE3_POS                           (3U)
#define INTC_EVTER_EVTE3                               (0x00000008UL)
#define INTC_EVTER_EVTE4_POS                           (4U)
#define INTC_EVTER_EVTE4                               (0x00000010UL)
#define INTC_EVTER_EVTE5_POS                           (5U)
#define INTC_EVTER_EVTE5                               (0x00000020UL)
#define INTC_EVTER_EVTE6_POS                           (6U)
#define INTC_EVTER_EVTE6                               (0x00000040UL)
#define INTC_EVTER_EVTE7_POS                           (7U)
#define INTC_EVTER_EVTE7                               (0x00000080UL)
#define INTC_EVTER_EVTE8_POS                           (8U)
#define INTC_EVTER_EVTE8                               (0x00000100UL)
#define INTC_EVTER_EVTE9_POS                           (9U)
#define INTC_EVTER_EVTE9                               (0x00000200UL)
#define INTC_EVTER_EVTE10_POS                          (10U)
#define INTC_EVTER_EVTE10                              (0x00000400UL)
#define INTC_EVTER_EVTE11_POS                          (11U)
#define INTC_EVTER_EVTE11                              (0x00000800UL)
#define INTC_EVTER_EVTE12_POS                          (12U)
#define INTC_EVTER_EVTE12                              (0x00001000UL)
#define INTC_EVTER_EVTE13_POS                          (13U)
#define INTC_EVTER_EVTE13                              (0x00002000UL)
#define INTC_EVTER_EVTE14_POS                          (14U)
#define INTC_EVTER_EVTE14                              (0x00004000UL)
#define INTC_EVTER_EVTE15_POS                          (15U)
#define INTC_EVTER_EVTE15                              (0x00008000UL)

/*  Bit definition for INTC_IER register  */
#define INTC_IER_IER0_POS                              (0U)
#define INTC_IER_IER0                                  (0x00000001UL)
#define INTC_IER_IER1_POS                              (1U)
#define INTC_IER_IER1                                  (0x00000002UL)
#define INTC_IER_IER2_POS                              (2U)
#define INTC_IER_IER2                                  (0x00000004UL)
#define INTC_IER_IER3_POS                              (3U)
#define INTC_IER_IER3                                  (0x00000008UL)
#define INTC_IER_IER4_POS                              (4U)
#define INTC_IER_IER4                                  (0x00000010UL)
#define INTC_IER_IER5_POS                              (5U)
#define INTC_IER_IER5                                  (0x00000020UL)
#define INTC_IER_IER6_POS                              (6U)
#define INTC_IER_IER6                                  (0x00000040UL)
#define INTC_IER_IER7_POS                              (7U)
#define INTC_IER_IER7                                  (0x00000080UL)
#define INTC_IER_IER8_POS                              (8U)
#define INTC_IER_IER8                                  (0x00000100UL)
#define INTC_IER_IER9_POS                              (9U)
#define INTC_IER_IER9                                  (0x00000200UL)
#define INTC_IER_IER10_POS                             (10U)
#define INTC_IER_IER10                                 (0x00000400UL)
#define INTC_IER_IER11_POS                             (11U)
#define INTC_IER_IER11                                 (0x00000800UL)
#define INTC_IER_IER12_POS                             (12U)
#define INTC_IER_IER12                                 (0x00001000UL)
#define INTC_IER_IER13_POS                             (13U)
#define INTC_IER_IER13                                 (0x00002000UL)
#define INTC_IER_IER14_POS                             (14U)
#define INTC_IER_IER14                                 (0x00004000UL)
#define INTC_IER_IER15_POS                             (15U)
#define INTC_IER_IER15                                 (0x00008000UL)

/*******************************************************************************
                Bit definition for Peripheral PWC
*******************************************************************************/
/*  Bit definition for PWC_STPMCR register  */
#define PWC_STPMCR_FLNWT_POS                           (0U)
#define PWC_STPMCR_FLNWT                               (0x01U)
#define PWC_STPMCR_CKSMRC_POS                          (1U)
#define PWC_STPMCR_CKSMRC                              (0x02U)
#define PWC_STPMCR_HAPORDIS_POS                        (3U)
#define PWC_STPMCR_HAPORDIS                            (0x08U)
#define PWC_STPMCR_STPDAS_POS                          (6U)
#define PWC_STPMCR_STPDAS                              (0x40U)
#define PWC_STPMCR_STOP_POS                            (7U)
#define PWC_STPMCR_STOP                                (0x80U)

/*  Bit definition for PWC_PWRC register  */
#define PWC_PWRC_PWDRV_POS                             (0U)
#define PWC_PWRC_PWDRV                                 (0x003FU)
#define PWC_PWRC_PWDRV_0                               (0x0001U)
#define PWC_PWRC_PWDRV_1                               (0x0002U)
#define PWC_PWRC_PWDRV_2                               (0x0004U)
#define PWC_PWRC_PWDRV_3                               (0x0008U)
#define PWC_PWRC_PWDRV_4                               (0x0010U)
#define PWC_PWRC_PWDRV_5                               (0x0020U)
#define PWC_PWRC_ACTV_POS                              (6U)
#define PWC_PWRC_ACTV                                  (0x0040U)
#define PWC_PWRC_DVS_POS                               (7U)
#define PWC_PWRC_DVS                                   (0x0080U)
#define PWC_PWRC_VHRCE_POS                             (8U)
#define PWC_PWRC_VHRCE                                 (0x0100U)
#define PWC_PWRC_VPLLE_POS                             (9U)
#define PWC_PWRC_VPLLE                                 (0x0200U)
#define PWC_PWRC_HCHDTDIS_POS                          (10U)
#define PWC_PWRC_HCHDTDIS                              (0x0400U)
#define PWC_PWRC_PLHDTDIS_POS                          (11U)
#define PWC_PWRC_PLHDTDIS                              (0x0800U)
#define PWC_PWRC_HDTDIS_POS                            (12U)
#define PWC_PWRC_HDTDIS                                (0x1000U)
#define PWC_PWRC_HRCPWRDY_POS                          (13U)
#define PWC_PWRC_HRCPWRDY                              (0x2000U)
#define PWC_PWRC_PLLPWRDY_POS                          (14U)
#define PWC_PWRC_PLLPWRDY                              (0x4000U)

/*  Bit definition for PWC_PWRMONR register  */
#define PWC_PWRMONR_PWMONSEL_POS                       (0U)
#define PWC_PWRMONR_PWMONSEL                           (0x01U)
#define PWC_PWRMONR_PWMONE_POS                         (1U)
#define PWC_PWRMONR_PWMONE                             (0x02U)

/*  Bit definition for PWC_RAMCR register  */
#define PWC_RAMCR_RPERDIS_POS                          (4U)
#define PWC_RAMCR_RPERDIS                              (0x10U)
#define PWC_RAMCR_SRPEF_POS                            (5U)
#define PWC_RAMCR_SRPEF                                (0x20U)
#define PWC_RAMCR_HRPEF_POS                            (6U)
#define PWC_RAMCR_HRPEF                                (0x40U)
#define PWC_RAMCR_CRPEF_POS                            (7U)
#define PWC_RAMCR_CRPEF                                (0x80U)

/*  Bit definition for PWC_LVDCR0 register  */
#define PWC_LVDCR0_L1IEGS_POS                          (2U)
#define PWC_LVDCR0_L1IEGS                              (0x0000000CUL)
#define PWC_LVDCR0_L1IEGS_0                            (0x00000004UL)
#define PWC_LVDCR0_L1IEGS_1                            (0x00000008UL)
#define PWC_LVDCR0_L1LVL_POS                           (4U)
#define PWC_LVDCR0_L1LVL                               (0x000000F0UL)
#define PWC_LVDCR0_L1NFS_POS                           (8U)
#define PWC_LVDCR0_L1NFS                               (0x00000300UL)
#define PWC_LVDCR0_L1NFS_0                             (0x00000100UL)
#define PWC_LVDCR0_L1NFS_1                             (0x00000200UL)
#define PWC_LVDCR0_L1NFDIS_POS                         (10U)
#define PWC_LVDCR0_L1NFDIS                             (0x00000400UL)
#define PWC_LVDCR0_L1NMIS_POS                          (11U)
#define PWC_LVDCR0_L1NMIS                              (0x00000800UL)
#define PWC_LVDCR0_L1IRS_POS                           (12U)
#define PWC_LVDCR0_L1IRS                               (0x00001000UL)
#define PWC_LVDCR0_L1IRE_POS                           (13U)
#define PWC_LVDCR0_L1IRE                               (0x00002000UL)
#define PWC_LVDCR0_L1CMPOE_POS                         (14U)
#define PWC_LVDCR0_L1CMPOE                             (0x00004000UL)
#define PWC_LVDCR0_L1EN_POS                            (15U)
#define PWC_LVDCR0_L1EN                                (0x00008000UL)
#define PWC_LVDCR0_EXVCCINEN_POS                       (16U)
#define PWC_LVDCR0_EXVCCINEN                           (0x00010000UL)
#define PWC_LVDCR0_L2IEGS_POS                          (18U)
#define PWC_LVDCR0_L2IEGS                              (0x000C0000UL)
#define PWC_LVDCR0_L2IEGS_0                            (0x00040000UL)
#define PWC_LVDCR0_L2IEGS_1                            (0x00080000UL)
#define PWC_LVDCR0_L2LVL_POS                           (20U)
#define PWC_LVDCR0_L2LVL                               (0x00F00000UL)
#define PWC_LVDCR0_L2NFS_POS                           (24U)
#define PWC_LVDCR0_L2NFS                               (0x03000000UL)
#define PWC_LVDCR0_L2NFS_0                             (0x01000000UL)
#define PWC_LVDCR0_L2NFS_1                             (0x02000000UL)
#define PWC_LVDCR0_L2NFDIS_POS                         (26U)
#define PWC_LVDCR0_L2NFDIS                             (0x04000000UL)
#define PWC_LVDCR0_L2NMIS_POS                          (27U)
#define PWC_LVDCR0_L2NMIS                              (0x08000000UL)
#define PWC_LVDCR0_L2IRS_POS                           (28U)
#define PWC_LVDCR0_L2IRS                               (0x10000000UL)
#define PWC_LVDCR0_L2IRE_POS                           (29U)
#define PWC_LVDCR0_L2IRE                               (0x20000000UL)
#define PWC_LVDCR0_L2CMPOE_POS                         (30U)
#define PWC_LVDCR0_L2CMPOE                             (0x40000000UL)
#define PWC_LVDCR0_L2EN_POS                            (31U)
#define PWC_LVDCR0_L2EN                                (0x80000000UL)

/*  Bit definition for PWC_LVDCSR1 register  */
#define PWC_LVDCSR1_L1MON_POS                          (0U)
#define PWC_LVDCSR1_L1MON                              (0x01U)
#define PWC_LVDCSR1_L2MON_POS                          (1U)
#define PWC_LVDCSR1_L2MON                              (0x02U)
#define PWC_LVDCSR1_L1DETF_POS                         (2U)
#define PWC_LVDCSR1_L1DETF                             (0x04U)
#define PWC_LVDCSR1_L2DETF_POS                         (3U)
#define PWC_LVDCSR1_L2DETF                             (0x08U)
#define PWC_LVDCSR1_L0MON_POS                          (4U)
#define PWC_LVDCSR1_L0MON                              (0x10U)
#define PWC_LVDCSR1_L0CMPOE_POS                        (7U)
#define PWC_LVDCSR1_L0CMPOE                            (0x80U)

/*  Bit definition for PWC_FPRC register  */
#define PWC_FPRC_CKRWE_POS                             (0U)
#define PWC_FPRC_CKRWE                                 (0x0001U)
#define PWC_FPRC_PWRWE_POS                             (1U)
#define PWC_FPRC_PWRWE                                 (0x0002U)
#define PWC_FPRC_FPRCB2_POS                            (2U)
#define PWC_FPRC_FPRCB2                                (0x0004U)
#define PWC_FPRC_LVRWE_POS                             (3U)
#define PWC_FPRC_LVRWE                                 (0x0008U)
#define PWC_FPRC_FPRCB4_POS                            (4U)
#define PWC_FPRC_FPRCB4                                (0x0010U)
#define PWC_FPRC_FPRCB5_POS                            (5U)
#define PWC_FPRC_FPRCB5                                (0x0020U)
#define PWC_FPRC_FPRCB6_POS                            (6U)
#define PWC_FPRC_FPRCB6                                (0x0040U)
#define PWC_FPRC_FPRCB7_POS                            (7U)
#define PWC_FPRC_FPRCB7                                (0x0080U)
#define PWC_FPRC_FPRCWE_POS                            (8U)
#define PWC_FPRC_FPRCWE                                (0xFF00U)

/*  Bit definition for PWC_DBGC register  */
#define PWC_DBGC_DBGEN_POS                             (0U)
#define PWC_DBGC_DBGEN                                 (0x0001U)
#define PWC_DBGC_TRSTF_POS                             (15U)
#define PWC_DBGC_TRSTF                                 (0x8000U)

/*******************************************************************************
                Bit definition for Peripheral RMU
*******************************************************************************/
/*  Bit definition for RMU_RSTF0 register  */
#define RMU_RSTF0_PORF_POS                             (0U)
#define RMU_RSTF0_PORF                                 (0x0001U)
#define RMU_RSTF0_PINRF_POS                            (1U)
#define RMU_RSTF0_PINRF                                (0x0002U)
#define RMU_RSTF0_LV0RF_POS                            (2U)
#define RMU_RSTF0_LV0RF                                (0x0004U)
#define RMU_RSTF0_LV1RF_POS                            (3U)
#define RMU_RSTF0_LV1RF                                (0x0008U)
#define RMU_RSTF0_LV2RF_POS                            (4U)
#define RMU_RSTF0_LV2RF                                (0x0010U)
#define RMU_RSTF0_SWDRF_POS                            (5U)
#define RMU_RSTF0_SWDRF                                (0x0020U)
#define RMU_RSTF0_WDRF_POS                             (6U)
#define RMU_RSTF0_WDRF                                 (0x0040U)
#define RMU_RSTF0_CKFERF_POS                           (7U)
#define RMU_RSTF0_CKFERF                               (0x0080U)
#define RMU_RSTF0_SWRF_POS                             (8U)
#define RMU_RSTF0_SWRF                                 (0x0100U)
#define RMU_RSTF0_RAMPERF_POS                          (10U)
#define RMU_RSTF0_RAMPERF                              (0x0400U)
#define RMU_RSTF0_CPULKUPRF_POS                        (12U)
#define RMU_RSTF0_CPULKUPRF                            (0x1000U)
#define RMU_RSTF0_XTALERF_POS                          (13U)
#define RMU_RSTF0_XTALERF                              (0x2000U)
#define RMU_RSTF0_MULTIRF_POS                          (14U)
#define RMU_RSTF0_MULTIRF                              (0x4000U)
#define RMU_RSTF0_CLRF_POS                             (15U)
#define RMU_RSTF0_CLRF                                 (0x8000U)

/*******************************************************************************
                Bit definition for Peripheral SPI
*******************************************************************************/
/*  Bit definition for SPI_DR register  */
#define SPI_DR_SPD                                     (0x0000FFFFUL)

/*  Bit definition for SPI_CR1 register  */
#define SPI_CR1_SPIMDS_POS                             (0U)
#define SPI_CR1_SPIMDS                                 (0x00000001UL)
#define SPI_CR1_TXMDS_POS                              (1U)
#define SPI_CR1_TXMDS                                  (0x00000002UL)
#define SPI_CR1_MSTR_POS                               (3U)
#define SPI_CR1_MSTR                                   (0x00000008UL)
#define SPI_CR1_SPLPBK_POS                             (4U)
#define SPI_CR1_SPLPBK                                 (0x00000010UL)
#define SPI_CR1_SPLPBK2_POS                            (5U)
#define SPI_CR1_SPLPBK2                                (0x00000020UL)
#define SPI_CR1_SPE_POS                                (6U)
#define SPI_CR1_SPE                                    (0x00000040UL)
#define SPI_CR1_EIE_POS                                (8U)
#define SPI_CR1_EIE                                    (0x00000100UL)
#define SPI_CR1_TXIE_POS                               (9U)
#define SPI_CR1_TXIE                                   (0x00000200UL)
#define SPI_CR1_RXIE_POS                               (10U)
#define SPI_CR1_RXIE                                   (0x00000400UL)
#define SPI_CR1_IDIE_POS                               (11U)
#define SPI_CR1_IDIE                                   (0x00000800UL)
#define SPI_CR1_MODFE_POS                              (12U)
#define SPI_CR1_MODFE                                  (0x00001000UL)
#define SPI_CR1_PATE_POS                               (13U)
#define SPI_CR1_PATE                                   (0x00002000UL)
#define SPI_CR1_PAOE_POS                               (14U)
#define SPI_CR1_PAOE                                   (0x00004000UL)
#define SPI_CR1_PAE_POS                                (15U)
#define SPI_CR1_PAE                                    (0x00008000UL)

/*  Bit definition for SPI_CFG1 register  */
#define SPI_CFG1_SS0PV_POS                             (8U)
#define SPI_CFG1_SS0PV                                 (0x00000100UL)

/*  Bit definition for SPI_SR register  */
#define SPI_SR_OVRERF_POS                              (0U)
#define SPI_SR_OVRERF                                  (0x00000001UL)
#define SPI_SR_IDLNF_POS                               (1U)
#define SPI_SR_IDLNF                                   (0x00000002UL)
#define SPI_SR_MODFERF_POS                             (2U)
#define SPI_SR_MODFERF                                 (0x00000004UL)
#define SPI_SR_PERF_POS                                (3U)
#define SPI_SR_PERF                                    (0x00000008UL)
#define SPI_SR_UDRERF_POS                              (4U)
#define SPI_SR_UDRERF                                  (0x00000010UL)
#define SPI_SR_TDEF_POS                                (5U)
#define SPI_SR_TDEF                                    (0x00000020UL)
#define SPI_SR_RDFF_POS                                (7U)
#define SPI_SR_RDFF                                    (0x00000080UL)

/*  Bit definition for SPI_CFG2 register  */
#define SPI_CFG2_CPHA_POS                              (0U)
#define SPI_CFG2_CPHA                                  (0x00000001UL)
#define SPI_CFG2_CPOL_POS                              (1U)
#define SPI_CFG2_CPOL                                  (0x00000002UL)
#define SPI_CFG2_MBR_POS                               (2U)
#define SPI_CFG2_MBR                                   (0x0000001CUL)
#define SPI_CFG2_DSIZE_POS                             (8U)
#define SPI_CFG2_DSIZE                                 (0x00000100UL)
#define SPI_CFG2_LSBF_POS                              (12U)
#define SPI_CFG2_LSBF                                  (0x00001000UL)

/*******************************************************************************
                Bit definition for Peripheral SWDT
*******************************************************************************/
/*  Bit definition for SWDT_SR register  */
#define SWDT_SR_CNT_POS                                (0U)
#define SWDT_SR_CNT                                    (0x0000FFFFUL)
#define SWDT_SR_UDF_POS                                (16U)
#define SWDT_SR_UDF                                    (0x00010000UL)
#define SWDT_SR_REF_POS                                (17U)
#define SWDT_SR_REF                                    (0x00020000UL)

/*  Bit definition for SWDT_RR register  */
#define SWDT_RR_RF                                     (0x0000FFFFUL)

/*******************************************************************************
                Bit definition for Peripheral TMR0
*******************************************************************************/
/*  Bit definition for TMR0_CNTAR register  */
#define TMR0_CNTAR_CNTA                                (0x0000FFFFUL)

/*  Bit definition for TMR0_CNTBR register  */
#define TMR0_CNTBR_CNTB                                (0x0000FFFFUL)

/*  Bit definition for TMR0_CMPAR register  */
#define TMR0_CMPAR_CMPA                                (0x0000FFFFUL)

/*  Bit definition for TMR0_CMPBR register  */
#define TMR0_CMPBR_CMPB                                (0x0000FFFFUL)

/*  Bit definition for TMR0_BCONR register  */
#define TMR0_BCONR_CSTA_POS                            (0U)
#define TMR0_BCONR_CSTA                                (0x00000001UL)
#define TMR0_BCONR_CAPMDA_POS                          (1U)
#define TMR0_BCONR_CAPMDA                              (0x00000002UL)
#define TMR0_BCONR_INTENA_POS                          (2U)
#define TMR0_BCONR_INTENA                              (0x00000004UL)
#define TMR0_BCONR_CKDIVA_POS                          (4U)
#define TMR0_BCONR_CKDIVA                              (0x000000F0UL)
#define TMR0_BCONR_CKDIVA_0                            (0x00000010UL)
#define TMR0_BCONR_CKDIVA_1                            (0x00000020UL)
#define TMR0_BCONR_CKDIVA_2                            (0x00000040UL)
#define TMR0_BCONR_CKDIVA_3                            (0x00000080UL)
#define TMR0_BCONR_SYNCLKA_POS                         (9U)
#define TMR0_BCONR_SYNCLKA                             (0x00000200UL)
#define TMR0_BCONR_HSTAA_POS                           (12U)
#define TMR0_BCONR_HSTAA                               (0x00001000UL)
#define TMR0_BCONR_HSTPA_POS                           (13U)
#define TMR0_BCONR_HSTPA                               (0x00002000UL)
#define TMR0_BCONR_HCLEA_POS                           (14U)
#define TMR0_BCONR_HCLEA                               (0x00004000UL)
#define TMR0_BCONR_HICPA_POS                           (15U)
#define TMR0_BCONR_HICPA                               (0x00008000UL)
#define TMR0_BCONR_CSTB_POS                            (16U)
#define TMR0_BCONR_CSTB                                (0x00010000UL)
#define TMR0_BCONR_CAPMDB_POS                          (17U)
#define TMR0_BCONR_CAPMDB                              (0x00020000UL)
#define TMR0_BCONR_INTENB_POS                          (18U)
#define TMR0_BCONR_INTENB                              (0x00040000UL)
#define TMR0_BCONR_CKDIVB_POS                          (20U)
#define TMR0_BCONR_CKDIVB                              (0x00F00000UL)
#define TMR0_BCONR_CKDIVB_0                            (0x00100000UL)
#define TMR0_BCONR_CKDIVB_1                            (0x00200000UL)
#define TMR0_BCONR_CKDIVB_2                            (0x00400000UL)
#define TMR0_BCONR_CKDIVB_3                            (0x00800000UL)
#define TMR0_BCONR_SYNCLKB_POS                         (25U)
#define TMR0_BCONR_SYNCLKB                             (0x02000000UL)
#define TMR0_BCONR_HSTAB_POS                           (28U)
#define TMR0_BCONR_HSTAB                               (0x10000000UL)
#define TMR0_BCONR_HSTPB_POS                           (29U)
#define TMR0_BCONR_HSTPB                               (0x20000000UL)
#define TMR0_BCONR_HCLEB_POS                           (30U)
#define TMR0_BCONR_HCLEB                               (0x40000000UL)
#define TMR0_BCONR_HICPB_POS                           (31U)
#define TMR0_BCONR_HICPB                               (0x80000000UL)

/*  Bit definition for TMR0_STFLR register  */
#define TMR0_STFLR_CMFA_POS                            (0U)
#define TMR0_STFLR_CMFA                                (0x00000001UL)
#define TMR0_STFLR_CMFB_POS                            (16U)
#define TMR0_STFLR_CMFB                                (0x00010000UL)

/*******************************************************************************
                Bit definition for Peripheral TMR4
*******************************************************************************/
/*  Bit definition for TMR4_OCCRUH register  */
#define TMR4_OCCRUH                                    (0xFFFFU)

/*  Bit definition for TMR4_OCCRUL register  */
#define TMR4_OCCRUL                                    (0xFFFFU)

/*  Bit definition for TMR4_OCCRVH register  */
#define TMR4_OCCRVH                                    (0xFFFFU)

/*  Bit definition for TMR4_OCCRVL register  */
#define TMR4_OCCRVL                                    (0xFFFFU)

/*  Bit definition for TMR4_OCCRWH register  */
#define TMR4_OCCRWH                                    (0xFFFFU)

/*  Bit definition for TMR4_OCCRWL register  */
#define TMR4_OCCRWL                                    (0xFFFFU)

/*  Bit definition for TMR4_OCSR register  */
#define TMR4_OCSR_OCEH_POS                             (0U)
#define TMR4_OCSR_OCEH                                 (0x0001U)
#define TMR4_OCSR_OCEL_POS                             (1U)
#define TMR4_OCSR_OCEL                                 (0x0002U)
#define TMR4_OCSR_OCPH_POS                             (2U)
#define TMR4_OCSR_OCPH                                 (0x0004U)
#define TMR4_OCSR_OCPL_POS                             (3U)
#define TMR4_OCSR_OCPL                                 (0x0008U)
#define TMR4_OCSR_OCIEH_POS                            (4U)
#define TMR4_OCSR_OCIEH                                (0x0010U)
#define TMR4_OCSR_OCIEL_POS                            (5U)
#define TMR4_OCSR_OCIEL                                (0x0020U)
#define TMR4_OCSR_OCFH_POS                             (6U)
#define TMR4_OCSR_OCFH                                 (0x0040U)
#define TMR4_OCSR_OCFL_POS                             (7U)
#define TMR4_OCSR_OCFL                                 (0x0080U)

/*  Bit definition for TMR4_OCER register  */
#define TMR4_OCER_CHBUFEN_POS                          (0U)
#define TMR4_OCER_CHBUFEN                              (0x0003U)
#define TMR4_OCER_CHBUFEN_0                            (0x0001U)
#define TMR4_OCER_CHBUFEN_1                            (0x0002U)
#define TMR4_OCER_CLBUFEN_POS                          (2U)
#define TMR4_OCER_CLBUFEN                              (0x000CU)
#define TMR4_OCER_CLBUFEN_0                            (0x0004U)
#define TMR4_OCER_CLBUFEN_1                            (0x0008U)
#define TMR4_OCER_MHBUFEN_POS                          (4U)
#define TMR4_OCER_MHBUFEN                              (0x0030U)
#define TMR4_OCER_MHBUFEN_0                            (0x0010U)
#define TMR4_OCER_MHBUFEN_1                            (0x0020U)
#define TMR4_OCER_MLBUFEN_POS                          (6U)
#define TMR4_OCER_MLBUFEN                              (0x00C0U)
#define TMR4_OCER_MLBUFEN_0                            (0x0040U)
#define TMR4_OCER_MLBUFEN_1                            (0x0080U)
#define TMR4_OCER_LMCH_POS                             (8U)
#define TMR4_OCER_LMCH                                 (0x0100U)
#define TMR4_OCER_LMCL_POS                             (9U)
#define TMR4_OCER_LMCL                                 (0x0200U)
#define TMR4_OCER_LMMH_POS                             (10U)
#define TMR4_OCER_LMMH                                 (0x0400U)
#define TMR4_OCER_LMML_POS                             (11U)
#define TMR4_OCER_LMML                                 (0x0800U)
#define TMR4_OCER_MCECH_POS                            (12U)
#define TMR4_OCER_MCECH                                (0x1000U)
#define TMR4_OCER_MCECL_POS                            (13U)
#define TMR4_OCER_MCECL                                (0x2000U)

/*  Bit definition for TMR4_OCMRH register  */
#define TMR4_OCMRH_OCFDCH_POS                          (0U)
#define TMR4_OCMRH_OCFDCH                              (0x0001U)
#define TMR4_OCMRH_OCFPKH_POS                          (1U)
#define TMR4_OCMRH_OCFPKH                              (0x0002U)
#define TMR4_OCMRH_OCFUCH_POS                          (2U)
#define TMR4_OCMRH_OCFUCH                              (0x0004U)
#define TMR4_OCMRH_OCFZRH_POS                          (3U)
#define TMR4_OCMRH_OCFZRH                              (0x0008U)
#define TMR4_OCMRH_OPDCH_POS                           (4U)
#define TMR4_OCMRH_OPDCH                               (0x0030U)
#define TMR4_OCMRH_OPDCH_0                             (0x0010U)
#define TMR4_OCMRH_OPDCH_1                             (0x0020U)
#define TMR4_OCMRH_OPPKH_POS                           (6U)
#define TMR4_OCMRH_OPPKH                               (0x00C0U)
#define TMR4_OCMRH_OPPKH_0                             (0x0040U)
#define TMR4_OCMRH_OPPKH_1                             (0x0080U)
#define TMR4_OCMRH_OPUCH_POS                           (8U)
#define TMR4_OCMRH_OPUCH                               (0x0300U)
#define TMR4_OCMRH_OPUCH_0                             (0x0100U)
#define TMR4_OCMRH_OPUCH_1                             (0x0200U)
#define TMR4_OCMRH_OPZRH_POS                           (10U)
#define TMR4_OCMRH_OPZRH                               (0x0C00U)
#define TMR4_OCMRH_OPZRH_0                             (0x0400U)
#define TMR4_OCMRH_OPZRH_1                             (0x0800U)
#define TMR4_OCMRH_OPNPKH_POS                          (12U)
#define TMR4_OCMRH_OPNPKH                              (0x3000U)
#define TMR4_OCMRH_OPNPKH_0                            (0x1000U)
#define TMR4_OCMRH_OPNPKH_1                            (0x2000U)
#define TMR4_OCMRH_OPNZRH_POS                          (14U)
#define TMR4_OCMRH_OPNZRH                              (0xC000U)
#define TMR4_OCMRH_OPNZRH_0                            (0x4000U)
#define TMR4_OCMRH_OPNZRH_1                            (0x8000U)

/*  Bit definition for TMR4_OCMRL register  */
#define TMR4_OCMRL_OCFDCL_POS                          (0U)
#define TMR4_OCMRL_OCFDCL                              (0x00000001UL)
#define TMR4_OCMRL_OCFPKL_POS                          (1U)
#define TMR4_OCMRL_OCFPKL                              (0x00000002UL)
#define TMR4_OCMRL_OCFUCL_POS                          (2U)
#define TMR4_OCMRL_OCFUCL                              (0x00000004UL)
#define TMR4_OCMRL_OCFZRL_POS                          (3U)
#define TMR4_OCMRL_OCFZRL                              (0x00000008UL)
#define TMR4_OCMRL_OPDCL_POS                           (4U)
#define TMR4_OCMRL_OPDCL                               (0x00000030UL)
#define TMR4_OCMRL_OPDCL_0                             (0x00000010UL)
#define TMR4_OCMRL_OPDCL_1                             (0x00000020UL)
#define TMR4_OCMRL_OPPKL_POS                           (6U)
#define TMR4_OCMRL_OPPKL                               (0x000000C0UL)
#define TMR4_OCMRL_OPPKL_0                             (0x00000040UL)
#define TMR4_OCMRL_OPPKL_1                             (0x00000080UL)
#define TMR4_OCMRL_OPUCL_POS                           (8U)
#define TMR4_OCMRL_OPUCL                               (0x00000300UL)
#define TMR4_OCMRL_OPUCL_0                             (0x00000100UL)
#define TMR4_OCMRL_OPUCL_1                             (0x00000200UL)
#define TMR4_OCMRL_OPZRL_POS                           (10U)
#define TMR4_OCMRL_OPZRL                               (0x00000C00UL)
#define TMR4_OCMRL_OPZRL_0                             (0x00000400UL)
#define TMR4_OCMRL_OPZRL_1                             (0x00000800UL)
#define TMR4_OCMRL_OPNPKL_POS                          (12U)
#define TMR4_OCMRL_OPNPKL                              (0x00003000UL)
#define TMR4_OCMRL_OPNPKL_0                            (0x00001000UL)
#define TMR4_OCMRL_OPNPKL_1                            (0x00002000UL)
#define TMR4_OCMRL_OPNZRL_POS                          (14U)
#define TMR4_OCMRL_OPNZRL                              (0x0000C000UL)
#define TMR4_OCMRL_OPNZRL_0                            (0x00004000UL)
#define TMR4_OCMRL_OPNZRL_1                            (0x00008000UL)
#define TMR4_OCMRL_EOPNDCL_POS                         (16U)
#define TMR4_OCMRL_EOPNDCL                             (0x00030000UL)
#define TMR4_OCMRL_EOPNDCL_0                           (0x00010000UL)
#define TMR4_OCMRL_EOPNDCL_1                           (0x00020000UL)
#define TMR4_OCMRL_EOPNUCL_POS                         (18U)
#define TMR4_OCMRL_EOPNUCL                             (0x000C0000UL)
#define TMR4_OCMRL_EOPNUCL_0                           (0x00040000UL)
#define TMR4_OCMRL_EOPNUCL_1                           (0x00080000UL)
#define TMR4_OCMRL_EOPDCL_POS                          (20U)
#define TMR4_OCMRL_EOPDCL                              (0x00300000UL)
#define TMR4_OCMRL_EOPDCL_0                            (0x00100000UL)
#define TMR4_OCMRL_EOPDCL_1                            (0x00200000UL)
#define TMR4_OCMRL_EOPPKL_POS                          (22U)
#define TMR4_OCMRL_EOPPKL                              (0x00C00000UL)
#define TMR4_OCMRL_EOPPKL_0                            (0x00400000UL)
#define TMR4_OCMRL_EOPPKL_1                            (0x00800000UL)
#define TMR4_OCMRL_EOPUCL_POS                          (24U)
#define TMR4_OCMRL_EOPUCL                              (0x03000000UL)
#define TMR4_OCMRL_EOPUCL_0                            (0x01000000UL)
#define TMR4_OCMRL_EOPUCL_1                            (0x02000000UL)
#define TMR4_OCMRL_EOPZRL_POS                          (26U)
#define TMR4_OCMRL_EOPZRL                              (0x0C000000UL)
#define TMR4_OCMRL_EOPZRL_0                            (0x04000000UL)
#define TMR4_OCMRL_EOPZRL_1                            (0x08000000UL)
#define TMR4_OCMRL_EOPNPKL_POS                         (28U)
#define TMR4_OCMRL_EOPNPKL                             (0x30000000UL)
#define TMR4_OCMRL_EOPNPKL_0                           (0x10000000UL)
#define TMR4_OCMRL_EOPNPKL_1                           (0x20000000UL)
#define TMR4_OCMRL_EOPNZRL_POS                         (30U)
#define TMR4_OCMRL_EOPNZRL                             (0xC0000000UL)
#define TMR4_OCMRL_EOPNZRL_0                           (0x40000000UL)
#define TMR4_OCMRL_EOPNZRL_1                           (0x80000000UL)

/*  Bit definition for TMR4_CPSR register  */
#define TMR4_CPSR                                      (0xFFFFU)

/*  Bit definition for TMR4_CNTR register  */
#define TMR4_CNTR                                      (0xFFFFU)

/*  Bit definition for TMR4_CCSR register  */
#define TMR4_CCSR_CKDIV_POS                            (0U)
#define TMR4_CCSR_CKDIV                                (0x000FU)
#define TMR4_CCSR_CKDIV_0                              (0x0001U)
#define TMR4_CCSR_CKDIV_1                              (0x0002U)
#define TMR4_CCSR_CKDIV_2                              (0x0004U)
#define TMR4_CCSR_CKDIV_3                              (0x0008U)
#define TMR4_CCSR_CLEAR_POS                            (4U)
#define TMR4_CCSR_CLEAR                                (0x0010U)
#define TMR4_CCSR_MODE_POS                             (5U)
#define TMR4_CCSR_MODE                                 (0x0020U)
#define TMR4_CCSR_STOP_POS                             (6U)
#define TMR4_CCSR_STOP                                 (0x0040U)
#define TMR4_CCSR_BUFEN_POS                            (7U)
#define TMR4_CCSR_BUFEN                                (0x0080U)
#define TMR4_CCSR_IRQPEN_POS                           (8U)
#define TMR4_CCSR_IRQPEN                               (0x0100U)
#define TMR4_CCSR_IRQPF_POS                            (9U)
#define TMR4_CCSR_IRQPF                                (0x0200U)
#define TMR4_CCSR_IRQZEN_POS                           (13U)
#define TMR4_CCSR_IRQZEN                               (0x2000U)
#define TMR4_CCSR_IRQZF_POS                            (14U)
#define TMR4_CCSR_IRQZF                                (0x4000U)
#define TMR4_CCSR_ECKEN_POS                            (15U)
#define TMR4_CCSR_ECKEN                                (0x8000U)

/*  Bit definition for TMR4_CVPR register  */
#define TMR4_CVPR_ZIM_POS                              (0U)
#define TMR4_CVPR_ZIM                                  (0x000FU)
#define TMR4_CVPR_PIM_POS                              (4U)
#define TMR4_CVPR_PIM                                  (0x00F0U)
#define TMR4_CVPR_ZIC_POS                              (8U)
#define TMR4_CVPR_ZIC                                  (0x0F00U)
#define TMR4_CVPR_PIC_POS                              (12U)
#define TMR4_CVPR_PIC                                  (0xF000U)

/*  Bit definition for TMR4_PFSRU register  */
#define TMR4_PFSRU                                     (0xFFFFU)

/*  Bit definition for TMR4_PDARU register  */
#define TMR4_PDARU                                     (0xFFFFU)

/*  Bit definition for TMR4_PDBRU register  */
#define TMR4_PDBRU                                     (0xFFFFU)

/*  Bit definition for TMR4_PFSRV register  */
#define TMR4_PFSRV                                     (0xFFFFU)

/*  Bit definition for TMR4_PDARV register  */
#define TMR4_PDARV                                     (0xFFFFU)

/*  Bit definition for TMR4_PDBRV register  */
#define TMR4_PDBRV                                     (0xFFFFU)

/*  Bit definition for TMR4_PFSRW register  */
#define TMR4_PFSRW                                     (0xFFFFU)

/*  Bit definition for TMR4_PDARW register  */
#define TMR4_PDARW                                     (0xFFFFU)

/*  Bit definition for TMR4_PDBRW register  */
#define TMR4_PDBRW                                     (0xFFFFU)

/*  Bit definition for TMR4_POCR register  */
#define TMR4_POCR_DIVCK_POS                            (0U)
#define TMR4_POCR_DIVCK                                (0x0007U)
#define TMR4_POCR_DIVCK_0                              (0x0001U)
#define TMR4_POCR_DIVCK_1                              (0x0002U)
#define TMR4_POCR_DIVCK_2                              (0x0004U)
#define TMR4_POCR_PWMMD_POS                            (4U)
#define TMR4_POCR_PWMMD                                (0x0030U)
#define TMR4_POCR_PWMMD_0                              (0x0010U)
#define TMR4_POCR_PWMMD_1                              (0x0020U)
#define TMR4_POCR_LVLS_POS                             (6U)
#define TMR4_POCR_LVLS                                 (0x00C0U)
#define TMR4_POCR_LVLS_0                               (0x0040U)
#define TMR4_POCR_LVLS_1                               (0x0080U)

/*  Bit definition for TMR4_RCSR register  */
#define TMR4_RCSR_RTIDU_POS                            (0U)
#define TMR4_RCSR_RTIDU                                (0x0001U)
#define TMR4_RCSR_RTIDV_POS                            (1U)
#define TMR4_RCSR_RTIDV                                (0x0002U)
#define TMR4_RCSR_RTIDW_POS                            (2U)
#define TMR4_RCSR_RTIDW                                (0x0004U)
#define TMR4_RCSR_RTIFU_POS                            (4U)
#define TMR4_RCSR_RTIFU                                (0x0010U)
#define TMR4_RCSR_RTICU_POS                            (5U)
#define TMR4_RCSR_RTICU                                (0x0020U)
#define TMR4_RCSR_RTEU_POS                             (6U)
#define TMR4_RCSR_RTEU                                 (0x0040U)
#define TMR4_RCSR_RTSU_POS                             (7U)
#define TMR4_RCSR_RTSU                                 (0x0080U)
#define TMR4_RCSR_RTIFV_POS                            (8U)
#define TMR4_RCSR_RTIFV                                (0x0100U)
#define TMR4_RCSR_RTICV_POS                            (9U)
#define TMR4_RCSR_RTICV                                (0x0200U)
#define TMR4_RCSR_RTEV_POS                             (10U)
#define TMR4_RCSR_RTEV                                 (0x0400U)
#define TMR4_RCSR_RTSV_POS                             (11U)
#define TMR4_RCSR_RTSV                                 (0x0800U)
#define TMR4_RCSR_RTIFW_POS                            (12U)
#define TMR4_RCSR_RTIFW                                (0x1000U)
#define TMR4_RCSR_RTICW_POS                            (13U)
#define TMR4_RCSR_RTICW                                (0x2000U)
#define TMR4_RCSR_RTEW_POS                             (14U)
#define TMR4_RCSR_RTEW                                 (0x4000U)
#define TMR4_RCSR_RTSW_POS                             (15U)
#define TMR4_RCSR_RTSW                                 (0x8000U)

/*  Bit definition for TMR4_SCCRUH register  */
#define TMR4_SCCRUH                                    (0xFFFFU)

/*  Bit definition for TMR4_SCCRUL register  */
#define TMR4_SCCRUL                                    (0xFFFFU)

/*  Bit definition for TMR4_SCCRVH register  */
#define TMR4_SCCRVH                                    (0xFFFFU)

/*  Bit definition for TMR4_SCCRVL register  */
#define TMR4_SCCRVL                                    (0xFFFFU)

/*  Bit definition for TMR4_SCCRWH register  */
#define TMR4_SCCRWH                                    (0xFFFFU)

/*  Bit definition for TMR4_SCCRWL register  */
#define TMR4_SCCRWL                                    (0xFFFFU)

/*  Bit definition for TMR4_SCSR register  */
#define TMR4_SCSR_BUFEN_POS                            (0U)
#define TMR4_SCSR_BUFEN                                (0x0003U)
#define TMR4_SCSR_BUFEN_0                              (0x0001U)
#define TMR4_SCSR_BUFEN_1                              (0x0002U)
#define TMR4_SCSR_EVTOS_POS                            (2U)
#define TMR4_SCSR_EVTOS                                (0x001CU)
#define TMR4_SCSR_EVTOS_0                              (0x0004U)
#define TMR4_SCSR_EVTOS_1                              (0x0008U)
#define TMR4_SCSR_EVTOS_2                              (0x0010U)
#define TMR4_SCSR_LMC_POS                              (5U)
#define TMR4_SCSR_LMC                                  (0x0020U)
#define TMR4_SCSR_EVTMS_POS                            (8U)
#define TMR4_SCSR_EVTMS                                (0x0100U)
#define TMR4_SCSR_EVTDS_POS                            (9U)
#define TMR4_SCSR_EVTDS                                (0x0200U)
#define TMR4_SCSR_DEN_POS                              (12U)
#define TMR4_SCSR_DEN                                  (0x1000U)
#define TMR4_SCSR_PEN_POS                              (13U)
#define TMR4_SCSR_PEN                                  (0x2000U)
#define TMR4_SCSR_UEN_POS                              (14U)
#define TMR4_SCSR_UEN                                  (0x4000U)
#define TMR4_SCSR_ZEN_POS                              (15U)
#define TMR4_SCSR_ZEN                                  (0x8000U)

/*  Bit definition for TMR4_SCMR register  */
#define TMR4_SCMR_AMC_POS                              (0U)
#define TMR4_SCMR_AMC                                  (0x000FU)
#define TMR4_SCMR_MZCE_POS                             (6U)
#define TMR4_SCMR_MZCE                                 (0x0040U)
#define TMR4_SCMR_MPCE_POS                             (7U)
#define TMR4_SCMR_MPCE                                 (0x0080U)

/*  Bit definition for TMR4_PSCR register  */
#define TMR4_PSCR_OEUH_POS                             (0U)
#define TMR4_PSCR_OEUH                                 (0x00000001UL)
#define TMR4_PSCR_OEUL_POS                             (1U)
#define TMR4_PSCR_OEUL                                 (0x00000002UL)
#define TMR4_PSCR_OEVH_POS                             (2U)
#define TMR4_PSCR_OEVH                                 (0x00000004UL)
#define TMR4_PSCR_OEVL_POS                             (3U)
#define TMR4_PSCR_OEVL                                 (0x00000008UL)
#define TMR4_PSCR_OEWH_POS                             (4U)
#define TMR4_PSCR_OEWH                                 (0x00000010UL)
#define TMR4_PSCR_OEWL_POS                             (5U)
#define TMR4_PSCR_OEWL                                 (0x00000020UL)
#define TMR4_PSCR_ODT_POS                              (6U)
#define TMR4_PSCR_ODT                                  (0x000000C0UL)
#define TMR4_PSCR_ODT_0                                (0x00000040UL)
#define TMR4_PSCR_ODT_1                                (0x00000080UL)
#define TMR4_PSCR_MOE_POS                              (8U)
#define TMR4_PSCR_MOE                                  (0x00000100UL)
#define TMR4_PSCR_AOE_POS                              (9U)
#define TMR4_PSCR_AOE                                  (0x00000200UL)
#define TMR4_PSCR_OSUH_POS                             (16U)
#define TMR4_PSCR_OSUH                                 (0x00030000UL)
#define TMR4_PSCR_OSUH_0                               (0x00010000UL)
#define TMR4_PSCR_OSUH_1                               (0x00020000UL)
#define TMR4_PSCR_OSUL_POS                             (18U)
#define TMR4_PSCR_OSUL                                 (0x000C0000UL)
#define TMR4_PSCR_OSUL_0                               (0x00040000UL)
#define TMR4_PSCR_OSUL_1                               (0x00080000UL)
#define TMR4_PSCR_OSVH_POS                             (20U)
#define TMR4_PSCR_OSVH                                 (0x00300000UL)
#define TMR4_PSCR_OSVH_0                               (0x00100000UL)
#define TMR4_PSCR_OSVH_1                               (0x00200000UL)
#define TMR4_PSCR_OSVL_POS                             (22U)
#define TMR4_PSCR_OSVL                                 (0x00C00000UL)
#define TMR4_PSCR_OSVL_0                               (0x00400000UL)
#define TMR4_PSCR_OSVL_1                               (0x00800000UL)
#define TMR4_PSCR_OSWH_POS                             (24U)
#define TMR4_PSCR_OSWH                                 (0x03000000UL)
#define TMR4_PSCR_OSWH_0                               (0x01000000UL)
#define TMR4_PSCR_OSWH_1                               (0x02000000UL)
#define TMR4_PSCR_OSWL_POS                             (26U)
#define TMR4_PSCR_OSWL                                 (0x0C000000UL)
#define TMR4_PSCR_OSWL_0                               (0x04000000UL)
#define TMR4_PSCR_OSWL_1                               (0x08000000UL)

/*  Bit definition for TMR4_SCER register  */
#define TMR4_SCER_EVTRS_POS                            (0U)
#define TMR4_SCER_EVTRS                                (0x0007U)
#define TMR4_SCER_EVTRS_0                              (0x0001U)
#define TMR4_SCER_EVTRS_1                              (0x0002U)
#define TMR4_SCER_EVTRS_2                              (0x0004U)
#define TMR4_SCER_PCTS_POS                             (3U)
#define TMR4_SCER_PCTS                                 (0x0008U)

/*******************************************************************************
                Bit definition for Peripheral TMRA
*******************************************************************************/
/*  Bit definition for TMRA_CNTER register  */
#define TMRA_CNTER_CNT                                 (0xFFFFU)

/*  Bit definition for TMRA_PERAR register  */
#define TMRA_PERAR_PER                                 (0xFFFFU)

/*  Bit definition for TMRA_CMPAR register  */
#define TMRA_CMPAR_CMP                                 (0xFFFFU)

/*  Bit definition for TMRA_BCSTR register  */
#define TMRA_BCSTR_START_POS                           (0U)
#define TMRA_BCSTR_START                               (0x0001U)
#define TMRA_BCSTR_DIR_POS                             (1U)
#define TMRA_BCSTR_DIR                                 (0x0002U)
#define TMRA_BCSTR_MODE_POS                            (2U)
#define TMRA_BCSTR_MODE                                (0x0004U)
#define TMRA_BCSTR_SYNST_POS                           (3U)
#define TMRA_BCSTR_SYNST                               (0x0008U)
#define TMRA_BCSTR_CKDIV_POS                           (4U)
#define TMRA_BCSTR_CKDIV                               (0x00F0U)
#define TMRA_BCSTR_CKDIV_0                             (0x0010U)
#define TMRA_BCSTR_CKDIV_1                             (0x0020U)
#define TMRA_BCSTR_CKDIV_2                             (0x0040U)
#define TMRA_BCSTR_CKDIV_3                             (0x0080U)
#define TMRA_BCSTR_OVSTP_POS                           (8U)
#define TMRA_BCSTR_OVSTP                               (0x0100U)
#define TMRA_BCSTR_INENOVF_POS                         (12U)
#define TMRA_BCSTR_INENOVF                             (0x1000U)
#define TMRA_BCSTR_INENUDF_POS                         (13U)
#define TMRA_BCSTR_INENUDF                             (0x2000U)
#define TMRA_BCSTR_OVFF_POS                            (14U)
#define TMRA_BCSTR_OVFF                                (0x4000U)
#define TMRA_BCSTR_UDFF_POS                            (15U)
#define TMRA_BCSTR_UDFF                                (0x8000U)

/*  Bit definition for TMRA_HCONR register  */
#define TMRA_HCONR_HSTA0_POS                           (0U)
#define TMRA_HCONR_HSTA0                               (0x0001U)
#define TMRA_HCONR_HSTA1_POS                           (1U)
#define TMRA_HCONR_HSTA1                               (0x0002U)
#define TMRA_HCONR_HSTA2_POS                           (2U)
#define TMRA_HCONR_HSTA2                               (0x0004U)
#define TMRA_HCONR_HSTP0_POS                           (4U)
#define TMRA_HCONR_HSTP0                               (0x0010U)
#define TMRA_HCONR_HSTP1_POS                           (5U)
#define TMRA_HCONR_HSTP1                               (0x0020U)
#define TMRA_HCONR_HSTP2_POS                           (6U)
#define TMRA_HCONR_HSTP2                               (0x0040U)
#define TMRA_HCONR_HCLE0_POS                           (8U)
#define TMRA_HCONR_HCLE0                               (0x0100U)
#define TMRA_HCONR_HCLE1_POS                           (9U)
#define TMRA_HCONR_HCLE1                               (0x0200U)
#define TMRA_HCONR_HCLE2_POS                           (10U)
#define TMRA_HCONR_HCLE2                               (0x0400U)
#define TMRA_HCONR_HCLE3_POS                           (12U)
#define TMRA_HCONR_HCLE3                               (0x1000U)
#define TMRA_HCONR_HCLE4_POS                           (13U)
#define TMRA_HCONR_HCLE4                               (0x2000U)

/*  Bit definition for TMRA_HCUPR register  */
#define TMRA_HCUPR_HCUP0_POS                           (0U)
#define TMRA_HCUPR_HCUP0                               (0x0001U)
#define TMRA_HCUPR_HCUP1_POS                           (1U)
#define TMRA_HCUPR_HCUP1                               (0x0002U)
#define TMRA_HCUPR_HCUP2_POS                           (2U)
#define TMRA_HCUPR_HCUP2                               (0x0004U)
#define TMRA_HCUPR_HCUP3_POS                           (3U)
#define TMRA_HCUPR_HCUP3                               (0x0008U)
#define TMRA_HCUPR_HCUP4_POS                           (4U)
#define TMRA_HCUPR_HCUP4                               (0x0010U)
#define TMRA_HCUPR_HCUP5_POS                           (5U)
#define TMRA_HCUPR_HCUP5                               (0x0020U)
#define TMRA_HCUPR_HCUP6_POS                           (6U)
#define TMRA_HCUPR_HCUP6                               (0x0040U)
#define TMRA_HCUPR_HCUP7_POS                           (7U)
#define TMRA_HCUPR_HCUP7                               (0x0080U)
#define TMRA_HCUPR_HCUP8_POS                           (8U)
#define TMRA_HCUPR_HCUP8                               (0x0100U)
#define TMRA_HCUPR_HCUP9_POS                           (9U)
#define TMRA_HCUPR_HCUP9                               (0x0200U)
#define TMRA_HCUPR_HCUP10_POS                          (10U)
#define TMRA_HCUPR_HCUP10                              (0x0400U)
#define TMRA_HCUPR_HCUP11_POS                          (11U)
#define TMRA_HCUPR_HCUP11                              (0x0800U)
#define TMRA_HCUPR_HCUP12_POS                          (12U)
#define TMRA_HCUPR_HCUP12                              (0x1000U)

/*  Bit definition for TMRA_HCDOR register  */
#define TMRA_HCDOR_HCDO0_POS                           (0U)
#define TMRA_HCDOR_HCDO0                               (0x0001U)
#define TMRA_HCDOR_HCDO1_POS                           (1U)
#define TMRA_HCDOR_HCDO1                               (0x0002U)
#define TMRA_HCDOR_HCDO2_POS                           (2U)
#define TMRA_HCDOR_HCDO2                               (0x0004U)
#define TMRA_HCDOR_HCDO3_POS                           (3U)
#define TMRA_HCDOR_HCDO3                               (0x0008U)
#define TMRA_HCDOR_HCDO4_POS                           (4U)
#define TMRA_HCDOR_HCDO4                               (0x0010U)
#define TMRA_HCDOR_HCDO5_POS                           (5U)
#define TMRA_HCDOR_HCDO5                               (0x0020U)
#define TMRA_HCDOR_HCDO6_POS                           (6U)
#define TMRA_HCDOR_HCDO6                               (0x0040U)
#define TMRA_HCDOR_HCDO7_POS                           (7U)
#define TMRA_HCDOR_HCDO7                               (0x0080U)
#define TMRA_HCDOR_HCDO8_POS                           (8U)
#define TMRA_HCDOR_HCDO8                               (0x0100U)
#define TMRA_HCDOR_HCDO9_POS                           (9U)
#define TMRA_HCDOR_HCDO9                               (0x0200U)
#define TMRA_HCDOR_HCDO10_POS                          (10U)
#define TMRA_HCDOR_HCDO10                              (0x0400U)
#define TMRA_HCDOR_HCDO11_POS                          (11U)
#define TMRA_HCDOR_HCDO11                              (0x0800U)
#define TMRA_HCDOR_HCDO12_POS                          (12U)
#define TMRA_HCDOR_HCDO12                              (0x1000U)

/*  Bit definition for TMRA_ICONR register  */
#define TMRA_ICONR_ITEN1_POS                           (0U)
#define TMRA_ICONR_ITEN1                               (0x0001U)
#define TMRA_ICONR_ITEN2_POS                           (1U)
#define TMRA_ICONR_ITEN2                               (0x0002U)

/*  Bit definition for TMRA_ECONR register  */
#define TMRA_ECONR_ETEN1_POS                           (0U)
#define TMRA_ECONR_ETEN1                               (0x0001U)
#define TMRA_ECONR_ETEN2_POS                           (1U)
#define TMRA_ECONR_ETEN2                               (0x0002U)

/*  Bit definition for TMRA_FCONR register  */
#define TMRA_FCONR_NOFIENTG_POS                        (0U)
#define TMRA_FCONR_NOFIENTG                            (0x0001U)
#define TMRA_FCONR_NOFICKTG_POS                        (1U)
#define TMRA_FCONR_NOFICKTG                            (0x0006U)
#define TMRA_FCONR_NOFICKTG_0                          (0x0002U)
#define TMRA_FCONR_NOFICKTG_1                          (0x0004U)
#define TMRA_FCONR_NOFIENCA_POS                        (8U)
#define TMRA_FCONR_NOFIENCA                            (0x0100U)
#define TMRA_FCONR_NOFICKCA_POS                        (9U)
#define TMRA_FCONR_NOFICKCA                            (0x0600U)
#define TMRA_FCONR_NOFICKCA_0                          (0x0200U)
#define TMRA_FCONR_NOFICKCA_1                          (0x0400U)
#define TMRA_FCONR_NOFIENCB_POS                        (12U)
#define TMRA_FCONR_NOFIENCB                            (0x1000U)
#define TMRA_FCONR_NOFICKCB_POS                        (13U)
#define TMRA_FCONR_NOFICKCB                            (0x6000U)
#define TMRA_FCONR_NOFICKCB_0                          (0x2000U)
#define TMRA_FCONR_NOFICKCB_1                          (0x4000U)

/*  Bit definition for TMRA_STFLR register  */
#define TMRA_STFLR_CMPF1_POS                           (0U)
#define TMRA_STFLR_CMPF1                               (0x0001U)
#define TMRA_STFLR_CMPF2_POS                           (1U)
#define TMRA_STFLR_CMPF2                               (0x0002U)

/*  Bit definition for TMRA_BCONR register  */
#define TMRA_BCONR_BEN_POS                             (0U)
#define TMRA_BCONR_BEN                                 (0x0001U)
#define TMRA_BCONR_BSE0_POS                            (1U)
#define TMRA_BCONR_BSE0                                (0x0002U)
#define TMRA_BCONR_BSE1_POS                            (2U)
#define TMRA_BCONR_BSE1                                (0x0004U)

/*  Bit definition for TMRA_CCONR register  */
#define TMRA_CCONR_CAPMD_POS                           (0U)
#define TMRA_CCONR_CAPMD                               (0x0001U)
#define TMRA_CCONR_HICP0_POS                           (4U)
#define TMRA_CCONR_HICP0                               (0x0010U)
#define TMRA_CCONR_HICP1_POS                           (5U)
#define TMRA_CCONR_HICP1                               (0x0020U)
#define TMRA_CCONR_HICP2_POS                           (6U)
#define TMRA_CCONR_HICP2                               (0x0040U)
#define TMRA_CCONR_NOFIENCP_POS                        (12U)
#define TMRA_CCONR_NOFIENCP                            (0x1000U)
#define TMRA_CCONR_NOFICKCP_POS                        (13U)
#define TMRA_CCONR_NOFICKCP                            (0x6000U)
#define TMRA_CCONR_NOFICKCP_0                          (0x2000U)
#define TMRA_CCONR_NOFICKCP_1                          (0x4000U)

/*  Bit definition for TMRA_PCONR register  */
#define TMRA_PCONR_STAC_POS                            (0U)
#define TMRA_PCONR_STAC                                (0x0003U)
#define TMRA_PCONR_STAC_0                              (0x0001U)
#define TMRA_PCONR_STAC_1                              (0x0002U)
#define TMRA_PCONR_STPC_POS                            (2U)
#define TMRA_PCONR_STPC                                (0x000CU)
#define TMRA_PCONR_STPC_0                              (0x0004U)
#define TMRA_PCONR_STPC_1                              (0x0008U)
#define TMRA_PCONR_CMPC_POS                            (4U)
#define TMRA_PCONR_CMPC                                (0x0030U)
#define TMRA_PCONR_CMPC_0                              (0x0010U)
#define TMRA_PCONR_CMPC_1                              (0x0020U)
#define TMRA_PCONR_PERC_POS                            (6U)
#define TMRA_PCONR_PERC                                (0x00C0U)
#define TMRA_PCONR_PERC_0                              (0x0040U)
#define TMRA_PCONR_PERC_1                              (0x0080U)
#define TMRA_PCONR_FORC_POS                            (8U)
#define TMRA_PCONR_FORC                                (0x0300U)
#define TMRA_PCONR_FORC_0                              (0x0100U)
#define TMRA_PCONR_FORC_1                              (0x0200U)
#define TMRA_PCONR_OUTEN_POS                           (12U)
#define TMRA_PCONR_OUTEN                               (0x1000U)

/*******************************************************************************
                Bit definition for Peripheral TMRB
*******************************************************************************/
/*  Bit definition for TMRB_CNTER register  */
#define TMRB_CNTER_CNT                                 (0xFFFFU)

/*  Bit definition for TMRB_PERAR register  */
#define TMRB_PERAR_PER                                 (0xFFFFU)

/*  Bit definition for TMRB_CMPAR register  */
#define TMRB_CMPAR_CMP                                 (0xFFFFU)

/*  Bit definition for TMRB_BCSTR register  */
#define TMRB_BCSTR_START_POS                           (0U)
#define TMRB_BCSTR_START                               (0x0001U)
#define TMRB_BCSTR_DIR_POS                             (1U)
#define TMRB_BCSTR_DIR                                 (0x0002U)
#define TMRB_BCSTR_MODE_POS                            (2U)
#define TMRB_BCSTR_MODE                                (0x0004U)
#define TMRB_BCSTR_CKDIV_POS                           (4U)
#define TMRB_BCSTR_CKDIV                               (0x00F0U)
#define TMRB_BCSTR_CKDIV_0                             (0x0010U)
#define TMRB_BCSTR_CKDIV_1                             (0x0020U)
#define TMRB_BCSTR_CKDIV_2                             (0x0040U)
#define TMRB_BCSTR_CKDIV_3                             (0x0080U)
#define TMRB_BCSTR_OVSTP_POS                           (8U)
#define TMRB_BCSTR_OVSTP                               (0x0100U)
#define TMRB_BCSTR_INENOVF_POS                         (12U)
#define TMRB_BCSTR_INENOVF                             (0x1000U)
#define TMRB_BCSTR_INENUDF_POS                         (13U)
#define TMRB_BCSTR_INENUDF                             (0x2000U)
#define TMRB_BCSTR_OVFF_POS                            (14U)
#define TMRB_BCSTR_OVFF                                (0x4000U)
#define TMRB_BCSTR_UDFF_POS                            (15U)
#define TMRB_BCSTR_UDFF                                (0x8000U)

/*  Bit definition for TMRB_HCONR register  */
#define TMRB_HCONR_HSTA0_POS                           (0U)
#define TMRB_HCONR_HSTA0                               (0x0001U)
#define TMRB_HCONR_HSTA1_POS                           (1U)
#define TMRB_HCONR_HSTA1                               (0x0002U)
#define TMRB_HCONR_HSTA2_POS                           (2U)
#define TMRB_HCONR_HSTA2                               (0x0004U)
#define TMRB_HCONR_HSTP0_POS                           (4U)
#define TMRB_HCONR_HSTP0                               (0x0010U)
#define TMRB_HCONR_HSTP1_POS                           (5U)
#define TMRB_HCONR_HSTP1                               (0x0020U)
#define TMRB_HCONR_HSTP2_POS                           (6U)
#define TMRB_HCONR_HSTP2                               (0x0040U)
#define TMRB_HCONR_HCLE0_POS                           (8U)
#define TMRB_HCONR_HCLE0                               (0x0100U)
#define TMRB_HCONR_HCLE1_POS                           (9U)
#define TMRB_HCONR_HCLE1                               (0x0200U)
#define TMRB_HCONR_HCLE2_POS                           (10U)
#define TMRB_HCONR_HCLE2                               (0x0400U)
#define TMRB_HCONR_HCLE5_POS                           (14U)
#define TMRB_HCONR_HCLE5                               (0x4000U)
#define TMRB_HCONR_HCLE6_POS                           (15U)
#define TMRB_HCONR_HCLE6                               (0x8000U)

/*  Bit definition for TMRB_HCUPR register  */
#define TMRB_HCUPR_HCUP8_POS                           (8U)
#define TMRB_HCUPR_HCUP8                               (0x0100U)
#define TMRB_HCUPR_HCUP9_POS                           (9U)
#define TMRB_HCUPR_HCUP9                               (0x0200U)
#define TMRB_HCUPR_HCUP10_POS                          (10U)
#define TMRB_HCUPR_HCUP10                              (0x0400U)

/*  Bit definition for TMRB_HCDOR register  */
#define TMRB_HCDOR_HCDO8_POS                           (8U)
#define TMRB_HCDOR_HCDO8                               (0x0100U)
#define TMRB_HCDOR_HCDO9_POS                           (9U)
#define TMRB_HCDOR_HCDO9                               (0x0200U)
#define TMRB_HCDOR_HCDO10_POS                          (10U)
#define TMRB_HCDOR_HCDO10                              (0x0400U)

/*  Bit definition for TMRB_ICONR register  */
#define TMRB_ICONR_ITEN1_POS                           (0U)
#define TMRB_ICONR_ITEN1                               (0x0001U)
#define TMRB_ICONR_ITEN2_POS                           (1U)
#define TMRB_ICONR_ITEN2                               (0x0002U)
#define TMRB_ICONR_ITEN3_POS                           (2U)
#define TMRB_ICONR_ITEN3                               (0x0004U)
#define TMRB_ICONR_ITEN4_POS                           (3U)
#define TMRB_ICONR_ITEN4                               (0x0008U)
#define TMRB_ICONR_ITEN5_POS                           (4U)
#define TMRB_ICONR_ITEN5                               (0x0010U)
#define TMRB_ICONR_ITEN6_POS                           (5U)
#define TMRB_ICONR_ITEN6                               (0x0020U)

/*  Bit definition for TMRB_ECONR register  */
#define TMRB_ECONR_ETEN1_POS                           (0U)
#define TMRB_ECONR_ETEN1                               (0x0001U)
#define TMRB_ECONR_ETEN2_POS                           (1U)
#define TMRB_ECONR_ETEN2                               (0x0002U)
#define TMRB_ECONR_ETEN3_POS                           (2U)
#define TMRB_ECONR_ETEN3                               (0x0004U)
#define TMRB_ECONR_ETEN4_POS                           (3U)
#define TMRB_ECONR_ETEN4                               (0x0008U)
#define TMRB_ECONR_ETEN5_POS                           (4U)
#define TMRB_ECONR_ETEN5                               (0x0010U)
#define TMRB_ECONR_ETEN6_POS                           (5U)
#define TMRB_ECONR_ETEN6                               (0x0020U)

/*  Bit definition for TMRB_STFLR register  */
#define TMRB_STFLR_CMPF1_POS                           (0U)
#define TMRB_STFLR_CMPF1                               (0x0001U)
#define TMRB_STFLR_CMPF2_POS                           (1U)
#define TMRB_STFLR_CMPF2                               (0x0002U)
#define TMRB_STFLR_CMPF3_POS                           (2U)
#define TMRB_STFLR_CMPF3                               (0x0004U)
#define TMRB_STFLR_CMPF4_POS                           (3U)
#define TMRB_STFLR_CMPF4                               (0x0008U)
#define TMRB_STFLR_CMPF5_POS                           (4U)
#define TMRB_STFLR_CMPF5                               (0x0010U)
#define TMRB_STFLR_CMPF6_POS                           (5U)
#define TMRB_STFLR_CMPF6                               (0x0020U)

/*  Bit definition for TMRB_BCONR register  */
#define TMRB_BCONR_BEN_POS                             (0U)
#define TMRB_BCONR_BEN                                 (0x0001U)
#define TMRB_BCONR_BSE0_POS                            (1U)
#define TMRB_BCONR_BSE0                                (0x0002U)
#define TMRB_BCONR_BSE1_POS                            (2U)
#define TMRB_BCONR_BSE1                                (0x0004U)

/*  Bit definition for TMRB_CCONR register  */
#define TMRB_CCONR_CAPMD_POS                           (0U)
#define TMRB_CCONR_CAPMD                               (0x0001U)
#define TMRB_CCONR_HICP0_POS                           (4U)
#define TMRB_CCONR_HICP0                               (0x0010U)
#define TMRB_CCONR_HICP1_POS                           (5U)
#define TMRB_CCONR_HICP1                               (0x0020U)
#define TMRB_CCONR_HICP2_POS                           (6U)
#define TMRB_CCONR_HICP2                               (0x0040U)
#define TMRB_CCONR_NOFIENCP_POS                        (12U)
#define TMRB_CCONR_NOFIENCP                            (0x1000U)
#define TMRB_CCONR_NOFICKCP_POS                        (13U)
#define TMRB_CCONR_NOFICKCP                            (0x6000U)
#define TMRB_CCONR_NOFICKCP_0                          (0x2000U)
#define TMRB_CCONR_NOFICKCP_1                          (0x4000U)

/*  Bit definition for TMRB_PCONR register  */
#define TMRB_PCONR_STAC_POS                            (0U)
#define TMRB_PCONR_STAC                                (0x0003U)
#define TMRB_PCONR_STAC_0                              (0x0001U)
#define TMRB_PCONR_STAC_1                              (0x0002U)
#define TMRB_PCONR_STPC_POS                            (2U)
#define TMRB_PCONR_STPC                                (0x000CU)
#define TMRB_PCONR_STPC_0                              (0x0004U)
#define TMRB_PCONR_STPC_1                              (0x0008U)
#define TMRB_PCONR_CMPC_POS                            (4U)
#define TMRB_PCONR_CMPC                                (0x0030U)
#define TMRB_PCONR_CMPC_0                              (0x0010U)
#define TMRB_PCONR_CMPC_1                              (0x0020U)
#define TMRB_PCONR_PERC_POS                            (6U)
#define TMRB_PCONR_PERC                                (0x00C0U)
#define TMRB_PCONR_PERC_0                              (0x0040U)
#define TMRB_PCONR_PERC_1                              (0x0080U)
#define TMRB_PCONR_FORC_POS                            (8U)
#define TMRB_PCONR_FORC                                (0x0300U)
#define TMRB_PCONR_FORC_0                              (0x0100U)
#define TMRB_PCONR_FORC_1                              (0x0200U)
#define TMRB_PCONR_OUTEN_POS                           (12U)
#define TMRB_PCONR_OUTEN                               (0x1000U)

/*******************************************************************************
                Bit definition for Peripheral USART
*******************************************************************************/
/*  Bit definition for USART_SR register  */
#define USART_SR_PE_POS                                (0U)
#define USART_SR_PE                                    (0x00000001UL)
#define USART_SR_FE_POS                                (1U)
#define USART_SR_FE                                    (0x00000002UL)
#define USART_SR_ORE_POS                               (3U)
#define USART_SR_ORE                                   (0x00000008UL)
#define USART_SR_RXNE_POS                              (5U)
#define USART_SR_RXNE                                  (0x00000020UL)
#define USART_SR_TC_POS                                (6U)
#define USART_SR_TC                                    (0x00000040UL)
#define USART_SR_TXE_POS                               (7U)
#define USART_SR_TXE                                   (0x00000080UL)
#define USART_SR_MPB_POS                               (16U)
#define USART_SR_MPB                                   (0x00010000UL)

/*  Bit definition for USART_DR register  */
#define USART_DR_TDR_POS                               (0U)
#define USART_DR_TDR                                   (0x000001FFUL)
#define USART_DR_MPID_POS                              (9U)
#define USART_DR_MPID                                  (0x00000200UL)
#define USART_DR_RDR_POS                               (16U)
#define USART_DR_RDR                                   (0x01FF0000UL)

/*  Bit definition for USART_BRR register  */
#define USART_BRR_DIV_INTEGER_POS                      (8U)
#define USART_BRR_DIV_INTEGER                          (0x0000FF00UL)

/*  Bit definition for USART_CR1 register  */
#define USART_CR1_RE_POS                               (2U)
#define USART_CR1_RE                                   (0x00000004UL)
#define USART_CR1_TE_POS                               (3U)
#define USART_CR1_TE                                   (0x00000008UL)
#define USART_CR1_SLME_POS                             (4U)
#define USART_CR1_SLME                                 (0x00000010UL)
#define USART_CR1_RIE_POS                              (5U)
#define USART_CR1_RIE                                  (0x00000020UL)
#define USART_CR1_TCIE_POS                             (6U)
#define USART_CR1_TCIE                                 (0x00000040UL)
#define USART_CR1_TXEIE_POS                            (7U)
#define USART_CR1_TXEIE                                (0x00000080UL)
#define USART_CR1_PS_POS                               (9U)
#define USART_CR1_PS                                   (0x00000200UL)
#define USART_CR1_PCE_POS                              (10U)
#define USART_CR1_PCE                                  (0x00000400UL)
#define USART_CR1_M_POS                                (12U)
#define USART_CR1_M                                    (0x00001000UL)
#define USART_CR1_OVER8_POS                            (15U)
#define USART_CR1_OVER8                                (0x00008000UL)
#define USART_CR1_CPE_POS                              (16U)
#define USART_CR1_CPE                                  (0x00010000UL)
#define USART_CR1_CFE_POS                              (17U)
#define USART_CR1_CFE                                  (0x00020000UL)
#define USART_CR1_CORE_POS                             (19U)
#define USART_CR1_CORE                                 (0x00080000UL)
#define USART_CR1_MS_POS                               (24U)
#define USART_CR1_MS                                   (0x01000000UL)
#define USART_CR1_ML_POS                               (28U)
#define USART_CR1_ML                                   (0x10000000UL)
#define USART_CR1_NFE_POS                              (30U)
#define USART_CR1_NFE                                  (0x40000000UL)
#define USART_CR1_SBS_POS                              (31U)
#define USART_CR1_SBS                                  (0x80000000UL)

/*  Bit definition for USART_CR2 register  */
#define USART_CR2_MPE_POS                              (0U)
#define USART_CR2_MPE                                  (0x00000001UL)
#define USART_CR2_CLKC_POS                             (11U)
#define USART_CR2_CLKC                                 (0x00001800UL)
#define USART_CR2_CLKC_0                               (0x00000800UL)
#define USART_CR2_CLKC_1                               (0x00001000UL)
#define USART_CR2_STOP_POS                             (13U)
#define USART_CR2_STOP                                 (0x00002000UL)

/*  Bit definition for USART_CR3 register  */
#define USART_CR3_HDSEL_POS                            (3U)
#define USART_CR3_HDSEL                                (0x00000008UL)
#define USART_CR3_CTSE_POS                             (9U)
#define USART_CR3_CTSE                                 (0x00000200UL)

/*  Bit definition for USART_PR register  */
#define USART_PR_PSC                                   (0x00000003UL)
#define USART_PR_PSC_0                                 (0x00000001UL)
#define USART_PR_PSC_1                                 (0x00000002UL)

/*******************************************************************************
                Bit definition for Peripheral WDT
*******************************************************************************/
/*  Bit definition for WDT_CR register  */
#define WDT_CR_PERI_POS                                (0U)
#define WDT_CR_PERI                                    (0x00000003UL)
#define WDT_CR_PERI_0                                  (0x00000001UL)
#define WDT_CR_PERI_1                                  (0x00000002UL)
#define WDT_CR_CKS_POS                                 (4U)
#define WDT_CR_CKS                                     (0x000000F0UL)
#define WDT_CR_CKS_0                                   (0x00000010UL)
#define WDT_CR_CKS_1                                   (0x00000020UL)
#define WDT_CR_CKS_2                                   (0x00000040UL)
#define WDT_CR_CKS_3                                   (0x00000080UL)
#define WDT_CR_WDPT_POS                                (8U)
#define WDT_CR_WDPT                                    (0x00000F00UL)
#define WDT_CR_WDPT_0                                  (0x00000100UL)
#define WDT_CR_WDPT_1                                  (0x00000200UL)
#define WDT_CR_WDPT_2                                  (0x00000400UL)
#define WDT_CR_WDPT_3                                  (0x00000800UL)
#define WDT_CR_SLPOFF_POS                              (16U)
#define WDT_CR_SLPOFF                                  (0x00010000UL)
#define WDT_CR_ITS_POS                                 (31U)
#define WDT_CR_ITS                                     (0x80000000UL)

/*  Bit definition for WDT_SR register  */
#define WDT_SR_CNT_POS                                 (0U)
#define WDT_SR_CNT                                     (0x0000FFFFUL)
#define WDT_SR_UDF_POS                                 (16U)
#define WDT_SR_UDF                                     (0x00010000UL)
#define WDT_SR_REF_POS                                 (17U)
#define WDT_SR_REF                                     (0x00020000UL)

/*  Bit definition for WDT_RR register  */
#define WDT_RR_RF                                      (0x0000FFFFUL)


/******************************************************************************/
/*             Device Specific Registers bit_band structure                   */
/******************************************************************************/

typedef struct
{
    __IO uint32_t STRT;
    uint32_t RESERVED0[7];
} stc_adc_str_bit_t;

typedef struct
{
    __IO uint32_t MS0;
    __IO uint32_t MS1;
    uint32_t RESERVED0[2];
    __IO uint32_t ACCSEL0;
    __IO uint32_t ACCSEL1;
    __IO uint32_t CLREN;
    __IO uint32_t DFMT;
    __IO uint32_t AVCNT0;
    __IO uint32_t AVCNT1;
    __IO uint32_t AVCNT2;
    uint32_t RESERVED1[5];
} stc_adc_cr0_bit_t;

typedef struct
{
    uint32_t RESERVED0[2];
    __IO uint32_t RSCHSEL;
    uint32_t RESERVED1[13];
} stc_adc_cr1_bit_t;

typedef struct
{
    __IO uint32_t TRGSELA0;
    __IO uint32_t TRGSELA1;
    uint32_t RESERVED0[5];
    __IO uint32_t TRGENA;
    __IO uint32_t TRGSELB0;
    __IO uint32_t TRGSELB1;
    uint32_t RESERVED1[5];
    __IO uint32_t TRGENB;
} stc_adc_trgsr_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_adc_chselra0_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_adc_chselrb0_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_adc_avchselr0_bit_t;

typedef struct
{
    __IO uint32_t EXCHSEL;
    uint32_t RESERVED0[7];
} stc_adc_exchselr_bit_t;

typedef struct
{
    uint32_t RESERVED0[15];
    __IO uint32_t SHMD;
} stc_adc_shcr_bit_t;

typedef struct
{
    __IO uint32_t EOCAF;
    __IO uint32_t EOCBF;
    uint32_t RESERVED0[2];
    __IO uint32_t SASTPDF;
    uint32_t RESERVED1[3];
} stc_adc_isr_bit_t;

typedef struct
{
    __IO uint32_t EOCAIEN;
    __IO uint32_t EOCBIEN;
    uint32_t RESERVED0[6];
} stc_adc_icr_bit_t;

typedef struct
{
    __IO uint32_t CLREOCAF;
    __IO uint32_t CLREOCBF;
    uint32_t RESERVED0[2];
    __IO uint32_t CLRSASTPDF;
    uint32_t RESERVED1[3];
} stc_adc_isclrr_bit_t;

typedef struct
{
    __IO uint32_t STRG;
    uint32_t RESERVED0[31];
} stc_aos_intc_strgcr_bit_t;

typedef struct
{
    __IO uint32_t CENB;
    __IO uint32_t CWDE;
    uint32_t RESERVED0[5];
    __IO uint32_t CMON;
} stc_cmp_mdr_bit_t;

typedef struct
{
    __IO uint32_t FCKS0;
    __IO uint32_t FCKS1;
    uint32_t RESERVED0[2];
    __IO uint32_t EDGS0;
    __IO uint32_t EDGS1;
    __IO uint32_t CIEN;
    uint32_t RESERVED1[1];
} stc_cmp_fir_bit_t;

typedef struct
{
    __IO uint32_t COEN;
    __IO uint32_t COPS;
    __IO uint32_t CPOE;
    __IO uint32_t TWOE;
    __IO uint32_t TWOL;
    uint32_t RESERVED0[3];
} stc_cmp_ocr_bit_t;

typedef struct
{
    __IO uint32_t RVSL0;
    __IO uint32_t RVSL1;
    __IO uint32_t RVSL2;
    uint32_t RESERVED0[1];
    __IO uint32_t CVSL0;
    __IO uint32_t CVSL1;
    __IO uint32_t CVSL2;
    __IO uint32_t CVSL3;
} stc_cmp_vsr_bit_t;

typedef struct
{
    __IO uint32_t CTWS0;
    __IO uint32_t CTWS1;
    __IO uint32_t CTWS2;
    __IO uint32_t CTWS3;
    __IO uint32_t CTWS4;
    __IO uint32_t CTWS5;
    __IO uint32_t CTWS6;
    __IO uint32_t CTWS7;
} stc_cmp_twr1_bit_t;

typedef struct
{
    __IO uint32_t CTWP0;
    __IO uint32_t CTWP1;
    __IO uint32_t CTWP2;
    __IO uint32_t CTWP3;
    __IO uint32_t CTWP4;
    __IO uint32_t CTWP5;
    __IO uint32_t CTWP6;
    __IO uint32_t CTWP7;
} stc_cmp_twr2_bit_t;

typedef struct
{
    uint32_t RESERVED0[8];
} stc_cmu_adcksel_bit_t;

typedef struct
{
    __IO uint32_t XTALSTDF;
    uint32_t RESERVED0[7];
} stc_cmu_xtalstdsr_bit_t;

typedef struct
{
    uint32_t RESERVED0[8];
} stc_cmu_ckswr_bit_t;

typedef struct
{
    __IO uint32_t XTALSTP;
    uint32_t RESERVED0[7];
} stc_cmu_xtalcr_bit_t;

typedef struct
{
    uint32_t RESERVED0[4];
    __IO uint32_t XTALDRV0;
    __IO uint32_t XTALDRV1;
    __IO uint32_t XTALMS;
    __IO uint32_t SUPDRV;
} stc_cmu_xtalcfgr_bit_t;

typedef struct
{
    uint32_t RESERVED0[8];
} stc_cmu_xtalstbcr_bit_t;

typedef struct
{
    __IO uint32_t HRCSTP;
    uint32_t RESERVED0[7];
} stc_cmu_hrccr_bit_t;

typedef struct
{
    __IO uint32_t HRCSTBF;
    uint32_t RESERVED0[2];
    __IO uint32_t XTALSTBF;
    uint32_t RESERVED1[1];
    __IO uint32_t PLLSTBF;
    uint32_t RESERVED2[2];
} stc_cmu_oscstbsr_bit_t;

typedef struct
{
    uint32_t RESERVED0[7];
    __IO uint32_t MCO1EN;
} stc_cmu_mcocfgr_bit_t;

typedef struct
{
    __IO uint32_t XTALSTDIE;
    __IO uint32_t XTALSTDRE;
    __IO uint32_t XTALSTDRIS;
    uint32_t RESERVED0[4];
    __IO uint32_t XTALSTDE;
} stc_cmu_xtalstdcr_bit_t;

typedef struct
{
    __IO uint32_t ADC;
    __IO uint32_t CTC;
    __IO uint32_t CMP;
    uint32_t RESERVED0[1];
    __IO uint32_t AOS;
    __IO uint32_t DMA;
    uint32_t RESERVED1[1];
    __IO uint32_t CRC;
    __IO uint32_t TMRA_1;
    __IO uint32_t TMRA_2;
    __IO uint32_t TMRA_3;
    __IO uint32_t TMRA_4;
    uint32_t RESERVED2[4];
    __IO uint32_t TMR0_1;
    __IO uint32_t TMR0_2;
    __IO uint32_t TMR4;
    __IO uint32_t TMRB;
    __IO uint32_t EMB;
    __IO uint32_t FCM;
    __IO uint32_t DCU;
    uint32_t RESERVED3[1];
    __IO uint32_t USART1;
    __IO uint32_t USART2;
    __IO uint32_t USART3;
    __IO uint32_t USART4;
    __IO uint32_t IIC;
    __IO uint32_t SPI;
    uint32_t RESERVED4[2];
} stc_cmu_fcg_bit_t;

typedef struct
{
    __IO uint32_t LRCSTP;
    uint32_t RESERVED0[7];
} stc_cmu_lrccr_bit_t;

typedef struct
{
    __IO uint32_t MRCSTP;
    uint32_t RESERVED0[7];
} stc_cmu_mrccr_bit_t;

typedef struct
{
    uint32_t RESERVED0[7];
    __IO uint32_t PLLSRC;
    uint32_t RESERVED1[24];
} stc_cmu_pllcfgr_bit_t;

typedef struct
{
    __IO uint32_t PLLOFF;
    uint32_t RESERVED0[7];
} stc_cmu_pllcr_bit_t;

typedef struct
{
    __IO uint32_t TPIUCKS0;
    __IO uint32_t TPIUCKS1;
    uint32_t RESERVED0[5];
    __IO uint32_t TPIUCKOE;
} stc_cmu_tpiuckcfgr_bit_t;

typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t FLAG;
    uint32_t RESERVED0[30];
} stc_crc_cr_bit_t;

typedef struct
{
    __IO uint32_t REFPSC0;
    __IO uint32_t REFPSC1;
    __IO uint32_t REFPSC2;
    uint32_t RESERVED0[1];
    __IO uint32_t REFCKS0;
    __IO uint32_t REFCKS1;
    __IO uint32_t ERRIE;
    __IO uint32_t CTCEN;
    uint32_t RESERVED1[8];
    __IO uint32_t TRMVAL0;
    __IO uint32_t TRMVAL1;
    __IO uint32_t TRMVAL2;
    __IO uint32_t TRMVAL3;
    __IO uint32_t TRMVAL4;
    __IO uint32_t TRMVAL5;
    uint32_t RESERVED2[10];
} stc_ctc_cr1_bit_t;

typedef struct
{
    __IO uint32_t OFSVAL0;
    __IO uint32_t OFSVAL1;
    __IO uint32_t OFSVAL2;
    __IO uint32_t OFSVAL3;
    __IO uint32_t OFSVAL4;
    __IO uint32_t OFSVAL5;
    __IO uint32_t OFSVAL6;
    __IO uint32_t OFSVAL7;
    uint32_t RESERVED0[8];
    __IO uint32_t RLDVAL0;
    __IO uint32_t RLDVAL1;
    __IO uint32_t RLDVAL2;
    __IO uint32_t RLDVAL3;
    __IO uint32_t RLDVAL4;
    __IO uint32_t RLDVAL5;
    __IO uint32_t RLDVAL6;
    __IO uint32_t RLDVAL7;
    __IO uint32_t RLDVAL8;
    __IO uint32_t RLDVAL9;
    __IO uint32_t RLDVAL10;
    __IO uint32_t RLDVAL11;
    __IO uint32_t RLDVAL12;
    __IO uint32_t RLDVAL13;
    __IO uint32_t RLDVAL14;
    __IO uint32_t RLDVAL15;
} stc_ctc_cr2_bit_t;

typedef struct
{
    __IO uint32_t TRIMOK;
    __IO uint32_t TRMOVF;
    __IO uint32_t TRMUDF;
    __IO uint32_t CTCBSY;
    uint32_t RESERVED0[28];
} stc_ctc_str_bit_t;

typedef struct
{
    __IO uint32_t DATA10;
    __IO uint32_t DATA11;
    __IO uint32_t DATA12;
    __IO uint32_t DATA13;
    __IO uint32_t DATA14;
    __IO uint32_t DATA15;
    __IO uint32_t DATA16;
    __IO uint32_t DATA17;
    __IO uint32_t DATA20;
    __IO uint32_t DATA21;
    __IO uint32_t DATA22;
    __IO uint32_t DATA23;
    __IO uint32_t DATA24;
    __IO uint32_t DATA25;
    __IO uint32_t DATA26;
    __IO uint32_t DATA27;
} stc_cmp_dadr1_bit_t;

typedef struct
{
    __IO uint32_t DAEN;
    uint32_t RESERVED0[7];
    __IO uint32_t ALGN;
    uint32_t RESERVED1[7];
} stc_cmp_dacr1_bit_t;

typedef struct
{
    __IO uint32_t DASW;
    uint32_t RESERVED0[7];
    __IO uint32_t WPRT0;
    __IO uint32_t WPRT1;
    __IO uint32_t WPRT2;
    __IO uint32_t WPRT3;
    __IO uint32_t WPRT4;
    __IO uint32_t WPRT5;
    __IO uint32_t WPRT6;
    __IO uint32_t WPRT7;
} stc_cmp_dadc1_bit_t;

typedef struct
{
    __IO uint32_t MODE0;
    __IO uint32_t MODE1;
    __IO uint32_t MODE2;
    __IO uint32_t DATASIZE0;
    __IO uint32_t DATASIZE1;
    uint32_t RESERVED0[3];
    __IO uint32_t COMP_TRG;
    uint32_t RESERVED1[22];
    __IO uint32_t INTEN;
} stc_dcu_ctl_bit_t;

typedef struct
{
    __IO uint32_t FLAG_OP;
    __IO uint32_t FLAG_LS2;
    __IO uint32_t FLAG_EQ2;
    __IO uint32_t FLAG_GT2;
    __IO uint32_t FLAG_LS1;
    __IO uint32_t FLAG_EQ1;
    __IO uint32_t FLAG_GT1;
    uint32_t RESERVED0[25];
} stc_dcu_flag_bit_t;

typedef struct
{
    __IO uint32_t CLR_OP;
    __IO uint32_t CLR_LS2;
    __IO uint32_t CLR_EQ2;
    __IO uint32_t CLR_GT2;
    __IO uint32_t CLR_LS1;
    __IO uint32_t CLR_EQ1;
    __IO uint32_t CLR_GT1;
    uint32_t RESERVED0[25];
} stc_dcu_flagclr_bit_t;

typedef struct
{
    __IO uint32_t INT_OP;
    __IO uint32_t INT_LS2;
    __IO uint32_t INT_EQ2;
    __IO uint32_t INT_GT2;
    __IO uint32_t INT_LS1;
    __IO uint32_t INT_EQ1;
    __IO uint32_t INT_GT1;
    __IO uint32_t INT_WIN0;
    __IO uint32_t INT_WIN1;
    uint32_t RESERVED0[23];
} stc_dcu_intsel_bit_t;

typedef struct
{
    __IO uint32_t EN;
    uint32_t RESERVED0[31];
} stc_dma_en_bit_t;

typedef struct
{
    __IO uint32_t TRNERR0;
    __IO uint32_t TRNERR1;
    __IO uint32_t TRNERR2;
    __IO uint32_t TRNERR3;
    uint32_t RESERVED0[12];
    __IO uint32_t REQERR0;
    __IO uint32_t REQERR1;
    __IO uint32_t REQERR2;
    __IO uint32_t REQERR3;
    uint32_t RESERVED1[12];
} stc_dma_intstat0_bit_t;

typedef struct
{
    __IO uint32_t TC0;
    __IO uint32_t TC1;
    __IO uint32_t TC2;
    __IO uint32_t TC3;
    uint32_t RESERVED0[12];
    __IO uint32_t BTC0;
    __IO uint32_t BTC1;
    __IO uint32_t BTC2;
    __IO uint32_t BTC3;
    uint32_t RESERVED1[12];
} stc_dma_intstat1_bit_t;

typedef struct
{
    __IO uint32_t MSKTRNERR0;
    __IO uint32_t MSKTRNERR1;
    __IO uint32_t MSKTRNERR2;
    __IO uint32_t MSKTRNERR3;
    uint32_t RESERVED0[12];
    __IO uint32_t MSKREQERR0;
    __IO uint32_t MSKREQERR1;
    __IO uint32_t MSKREQERR2;
    __IO uint32_t MSKREQERR3;
    uint32_t RESERVED1[12];
} stc_dma_intmask0_bit_t;

typedef struct
{
    __IO uint32_t MSKTC0;
    __IO uint32_t MSKTC1;
    __IO uint32_t MSKTC2;
    __IO uint32_t MSKTC3;
    uint32_t RESERVED0[12];
    __IO uint32_t MSKBTC0;
    __IO uint32_t MSKBTC1;
    __IO uint32_t MSKBTC2;
    __IO uint32_t MSKBTC3;
    uint32_t RESERVED1[12];
} stc_dma_intmask1_bit_t;

typedef struct
{
    __IO uint32_t CLRTRNERR0;
    __IO uint32_t CLRTRNERR1;
    __IO uint32_t CLRTRNERR2;
    __IO uint32_t CLRTRNERR3;
    uint32_t RESERVED0[12];
    __IO uint32_t CLRREQERR0;
    __IO uint32_t CLRREQERR1;
    __IO uint32_t CLRREQERR2;
    __IO uint32_t CLRREQERR3;
    uint32_t RESERVED1[12];
} stc_dma_intclr0_bit_t;

typedef struct
{
    __IO uint32_t CLRTC0;
    __IO uint32_t CLRTC1;
    __IO uint32_t CLRTC2;
    __IO uint32_t CLRTC3;
    uint32_t RESERVED0[12];
    __IO uint32_t CLRBTC0;
    __IO uint32_t CLRBTC1;
    __IO uint32_t CLRBTC2;
    __IO uint32_t CLRBTC3;
    uint32_t RESERVED1[12];
} stc_dma_intclr1_bit_t;

typedef struct
{
    __IO uint32_t CHEN0;
    __IO uint32_t CHEN1;
    __IO uint32_t CHEN2;
    __IO uint32_t CHEN3;
    uint32_t RESERVED0[28];
} stc_dma_chen_bit_t;

typedef struct
{
    __IO uint32_t DMAACT;
    uint32_t RESERVED0[15];
    __IO uint32_t CHACT0;
    __IO uint32_t CHACT1;
    __IO uint32_t CHACT2;
    __IO uint32_t CHACT3;
    uint32_t RESERVED1[12];
} stc_dma_chstat_bit_t;

typedef struct
{
    __IO uint32_t CHENCLR0;
    __IO uint32_t CHENCLR1;
    __IO uint32_t CHENCLR2;
    __IO uint32_t CHENCLR3;
    uint32_t RESERVED0[28];
} stc_dma_chenclr_bit_t;

typedef struct
{
    uint32_t RESERVED0[28];
    __IO uint32_t LLPEN;
    __IO uint32_t LLPRUN;
    __IO uint32_t HSIZE0;
    __IO uint32_t HSIZE1;
} stc_dma_ch0ctl0_bit_t;

typedef struct
{
    uint32_t RESERVED0[24];
    __IO uint32_t RPTNSEN;
    __IO uint32_t RPTNSSEL0;
    __IO uint32_t RPTNSSEL1;
    __IO uint32_t LLPSEL;
    __IO uint32_t SINC0;
    __IO uint32_t SINC1;
    __IO uint32_t DINC0;
    __IO uint32_t DINC1;
} stc_dma_ch0ctl1_bit_t;

typedef struct
{
    uint32_t RESERVED0[28];
    __IO uint32_t LLPEN;
    __IO uint32_t LLPRUN;
    __IO uint32_t HSIZE0;
    __IO uint32_t HSIZE1;
} stc_dma_ch1ctl0_bit_t;

typedef struct
{
    uint32_t RESERVED0[24];
    __IO uint32_t RPTNSEN;
    __IO uint32_t RPTNSSEL0;
    __IO uint32_t RPTNSSEL1;
    __IO uint32_t LLPSEL;
    __IO uint32_t SINC0;
    __IO uint32_t SINC1;
    __IO uint32_t DINC0;
    __IO uint32_t DINC1;
} stc_dma_ch1ctl1_bit_t;

typedef struct
{
    uint32_t RESERVED0[28];
    __IO uint32_t LLPEN;
    __IO uint32_t LLPRUN;
    __IO uint32_t HSIZE0;
    __IO uint32_t HSIZE1;
} stc_dma_ch2ctl0_bit_t;

typedef struct
{
    uint32_t RESERVED0[24];
    __IO uint32_t RPTNSEN;
    __IO uint32_t RPTNSSEL0;
    __IO uint32_t RPTNSSEL1;
    __IO uint32_t LLPSEL;
    __IO uint32_t SINC0;
    __IO uint32_t SINC1;
    __IO uint32_t DINC0;
    __IO uint32_t DINC1;
} stc_dma_ch2ctl1_bit_t;

typedef struct
{
    uint32_t RESERVED0[28];
    __IO uint32_t LLPEN;
    __IO uint32_t LLPRUN;
    __IO uint32_t HSIZE0;
    __IO uint32_t HSIZE1;
} stc_dma_ch3ctl0_bit_t;

typedef struct
{
    uint32_t RESERVED0[24];
    __IO uint32_t RPTNSEN;
    __IO uint32_t RPTNSSEL0;
    __IO uint32_t RPTNSSEL1;
    __IO uint32_t LLPSEL;
    __IO uint32_t SINC0;
    __IO uint32_t SINC1;
    __IO uint32_t DINC0;
    __IO uint32_t DINC1;
} stc_dma_ch3ctl1_bit_t;

typedef struct
{
    __IO uint32_t FSTP;
    uint32_t RESERVED0[31];
} stc_efm_fstp_bit_t;

typedef struct
{
    __IO uint32_t FLWT0;
    __IO uint32_t FLWT1;
    __IO uint32_t FLWT2;
    uint32_t RESERVED0[13];
    __IO uint32_t ICHE;
    __IO uint32_t DCHE;
    uint32_t RESERVED1[1];
    __IO uint32_t CRST;
    uint32_t RESERVED2[12];
} stc_efm_frmc_bit_t;

typedef struct
{
    __IO uint32_t PEMODE;
    uint32_t RESERVED0[3];
    __IO uint32_t PEMOD0;
    __IO uint32_t PEMOD1;
    __IO uint32_t PEMOD2;
    uint32_t RESERVED1[1];
    __IO uint32_t BUSHLDCTL;
    uint32_t RESERVED2[23];
} stc_efm_fwmc_bit_t;

typedef struct
{
    __IO uint32_t PEWERR;
    __IO uint32_t PEPRTERR;
    uint32_t RESERVED0[1];
    __IO uint32_t PGMISMTCH;
    __IO uint32_t OPTEND;
    __IO uint32_t RDCOLERR;
    uint32_t RESERVED1[2];
    __IO uint32_t RDY;
    uint32_t RESERVED2[23];
} stc_efm_fsr_bit_t;

typedef struct
{
    __IO uint32_t PEWERRCLR;
    __IO uint32_t PEPRTERRCLR;
    uint32_t RESERVED0[1];
    __IO uint32_t PGMISMTCHCLR;
    __IO uint32_t OPTENDCLR;
    __IO uint32_t RDCOLERRCLR;
    uint32_t RESERVED1[26];
} stc_efm_fsclr_bit_t;

typedef struct
{
    __IO uint32_t PEERRITE;
    __IO uint32_t OPTENDITE;
    __IO uint32_t RDCOLERRITE;
    uint32_t RESERVED0[29];
} stc_efm_fite_bit_t;

typedef struct
{
    __IO uint32_t HRCFREQS0;
    __IO uint32_t HRCFREQS1;
    __IO uint32_t HRCFREQS2;
    __IO uint32_t HRCFREQS3;
    uint32_t RESERVED0[4];
} stc_efm_hrccfgr_bit_t;

typedef struct
{
    __IO uint32_t CMPEN0;
    __IO uint32_t CMPEN1;
    __IO uint32_t CMPEN2;
    uint32_t RESERVED0[1];
    __IO uint32_t OSCSTPEN;
    __IO uint32_t PWMSEN0;
    __IO uint32_t PWMSEN1;
    __IO uint32_t PWMSEN2;
    __IO uint32_t PORTINEN0;
    __IO uint32_t PORTINEN1;
    __IO uint32_t PORTINEN2;
    uint32_t RESERVED1[5];
    __IO uint32_t NFSEL00;
    __IO uint32_t NFSEL01;
    __IO uint32_t NFEN0;
    __IO uint32_t INVSEL0;
    __IO uint32_t NFSEL10;
    __IO uint32_t NFSEL11;
    __IO uint32_t NFEN1;
    __IO uint32_t INVSEL1;
    __IO uint32_t NFSEL20;
    __IO uint32_t NFSEL21;
    __IO uint32_t NFEN2;
    __IO uint32_t INVSEL2;
    uint32_t RESERVED2[4];
} stc_emb_ctl_bit_t;

typedef struct
{
    __IO uint32_t PWMLV0;
    __IO uint32_t PWMLV1;
    __IO uint32_t PWMLV2;
    uint32_t RESERVED0[29];
} stc_emb_pwmlv_bit_t;

typedef struct
{
    __IO uint32_t SOE;
    uint32_t RESERVED0[31];
} stc_emb_soe_bit_t;

typedef struct
{
    __IO uint32_t PWMSF;
    __IO uint32_t CMPF;
    __IO uint32_t OSF;
    __IO uint32_t PWMST;
    uint32_t RESERVED0[4];
    __IO uint32_t PORTINF0;
    __IO uint32_t PORTINF1;
    __IO uint32_t PORTINF2;
    uint32_t RESERVED1[1];
    __IO uint32_t PORTINST0;
    __IO uint32_t PORTINST1;
    __IO uint32_t PORTINST2;
    uint32_t RESERVED2[17];
} stc_emb_stat_bit_t;

typedef struct
{
    __IO uint32_t PWMSFCLR;
    __IO uint32_t CMPFCLR;
    __IO uint32_t OSFCLR;
    uint32_t RESERVED0[5];
    __IO uint32_t PORTINFCLR0;
    __IO uint32_t PORTINFCLR1;
    __IO uint32_t PORTINFCLR2;
    uint32_t RESERVED1[21];
} stc_emb_statclr_bit_t;

typedef struct
{
    __IO uint32_t PWMSINTEN;
    __IO uint32_t CMPINTEN;
    __IO uint32_t OSINTEN;
    uint32_t RESERVED0[5];
    __IO uint32_t PORTININTEN0;
    __IO uint32_t PORTININTEN1;
    __IO uint32_t PORTININTEN2;
    uint32_t RESERVED1[21];
} stc_emb_inten_bit_t;

typedef struct
{
    __IO uint32_t EMBVAL0;
    __IO uint32_t EMBVAL1;
    uint32_t RESERVED0[30];
} stc_emb_ecsr_bit_t;

typedef struct
{
    __IO uint32_t START;
    uint32_t RESERVED0[31];
} stc_fcm_str_bit_t;

typedef struct
{
    __IO uint32_t MDIVS0;
    __IO uint32_t MDIVS1;
    uint32_t RESERVED0[30];
} stc_fcm_mccr_bit_t;

typedef struct
{
    __IO uint32_t RDIVS0;
    __IO uint32_t RDIVS1;
    uint32_t RESERVED0[5];
    __IO uint32_t INEXS;
    __IO uint32_t DNFS0;
    __IO uint32_t DNFS1;
    uint32_t RESERVED1[2];
    __IO uint32_t EDGES0;
    __IO uint32_t EDGES1;
    uint32_t RESERVED2[1];
    __IO uint32_t EXREFE;
    uint32_t RESERVED3[16];
} stc_fcm_rccr_bit_t;

typedef struct
{
    __IO uint32_t ERRIE;
    __IO uint32_t MENDIE;
    __IO uint32_t OVFIE;
    uint32_t RESERVED0[1];
    __IO uint32_t ERRINTRS;
    uint32_t RESERVED1[2];
    __IO uint32_t ERRE;
    uint32_t RESERVED2[24];
} stc_fcm_rier_bit_t;

typedef struct
{
    __IO uint32_t ERRF;
    __IO uint32_t MENDF;
    __IO uint32_t OVF;
    uint32_t RESERVED0[29];
} stc_fcm_sr_bit_t;

typedef struct
{
    __IO uint32_t ERRFCLR;
    __IO uint32_t MENDFCLR;
    __IO uint32_t OVFCLR;
    uint32_t RESERVED0[29];
} stc_fcm_clr_bit_t;

typedef struct
{
    __IO uint32_t PIN0;
    __IO uint32_t PIN1;
    __IO uint32_t PIN2;
    __IO uint32_t PIN3;
    __IO uint32_t PIN4;
    __IO uint32_t PIN5;
    __IO uint32_t PIN6;
    __IO uint32_t PIN7;
} stc_gpio_pidr_bit_t;

typedef struct
{
    __IO uint32_t POUT0;
    __IO uint32_t POUT1;
    __IO uint32_t POUT2;
    __IO uint32_t POUT3;
    __IO uint32_t POUT4;
    __IO uint32_t POUT5;
    __IO uint32_t POUT6;
    __IO uint32_t POUT7;
} stc_gpio_podr_bit_t;

typedef struct
{
    __IO uint32_t POUTE0;
    __IO uint32_t POUTE1;
    __IO uint32_t POUTE2;
    __IO uint32_t POUTE3;
    __IO uint32_t POUTE4;
    __IO uint32_t POUTE5;
    __IO uint32_t POUTE6;
    __IO uint32_t POUTE7;
} stc_gpio_poer_bit_t;

typedef struct
{
    __IO uint32_t POS0;
    __IO uint32_t POS1;
    __IO uint32_t POS2;
    __IO uint32_t POS3;
    __IO uint32_t POS4;
    __IO uint32_t POS5;
    __IO uint32_t POS6;
    __IO uint32_t POS7;
} stc_gpio_posr_bit_t;

typedef struct
{
    __IO uint32_t POR0;
    __IO uint32_t POR1;
    __IO uint32_t POR2;
    __IO uint32_t POR3;
    __IO uint32_t POR4;
    __IO uint32_t POR5;
    __IO uint32_t POR6;
    __IO uint32_t POR7;
} stc_gpio_porr_bit_t;

typedef struct
{
    __IO uint32_t POT0;
    __IO uint32_t POT1;
    __IO uint32_t POT2;
    __IO uint32_t POT3;
    __IO uint32_t POT4;
    __IO uint32_t POT5;
    __IO uint32_t POT6;
    __IO uint32_t POT7;
} stc_gpio_potr_bit_t;

typedef struct
{
    __IO uint32_t SPFE0;
    __IO uint32_t SPFE1;
    __IO uint32_t SPFE2;
    __IO uint32_t SPFE3;
    __IO uint32_t SPFE4;
    uint32_t RESERVED0[11];
} stc_gpio_pspcr_bit_t;

typedef struct
{
    uint32_t RESERVED0[14];
    __IO uint32_t RDWT0;
    __IO uint32_t RDWT1;
} stc_gpio_pccr_bit_t;

typedef struct
{
    __IO uint32_t PINAE0;
    __IO uint32_t PINAE1;
    __IO uint32_t PINAE2;
    __IO uint32_t PINAE3;
    __IO uint32_t PINAE4;
    __IO uint32_t PINAE5;
    uint32_t RESERVED0[1];
    __IO uint32_t PINAE7;
    uint32_t RESERVED1[1];
    __IO uint32_t PINAE9;
    __IO uint32_t PINAE10;
    __IO uint32_t PINAE11;
    uint32_t RESERVED2[1];
    __IO uint32_t PINAE13;
    __IO uint32_t PINAE14;
    uint32_t RESERVED3[1];
} stc_gpio_pinaer_bit_t;

typedef struct
{
    __IO uint32_t WE;
    uint32_t RESERVED0[15];
} stc_gpio_pwpr_bit_t;

typedef struct
{
    __IO uint32_t POUT;
    __IO uint32_t POUTE;
    __IO uint32_t NOD;
    uint32_t RESERVED0[1];
    __IO uint32_t DRV;
    __IO uint32_t LTE;
    __IO uint32_t PUU;
    uint32_t RESERVED1[1];
    __IO uint32_t PIN;
    __IO uint32_t INVE;
    __IO uint32_t CINSEL;
    __IO uint32_t INTE;
    uint32_t RESERVED2[4];
} stc_gpio_pcr_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_gpio_pfsr_bit_t;

typedef struct
{
    __IO uint32_t PE;
    __IO uint32_t SMBUS;
    __IO uint32_t SMBALRTEN;
    __IO uint32_t SMBDEFAULTEN;
    __IO uint32_t SMBHOSTEN;
    __IO uint32_t FACKEN;
    __IO uint32_t GCEN;
    __IO uint32_t RESTART;
    __IO uint32_t START;
    __IO uint32_t STOP;
    __IO uint32_t ACK;
    uint32_t RESERVED0[4];
    __IO uint32_t SWRST;
    uint32_t RESERVED1[16];
} stc_i2c_cr1_bit_t;

typedef struct
{
    __IO uint32_t STARTIE;
    __IO uint32_t SLADDR0IE;
    __IO uint32_t SLADDR1IE;
    __IO uint32_t TENDIE;
    __IO uint32_t STOPIE;
    uint32_t RESERVED0[1];
    __IO uint32_t RFULLIE;
    __IO uint32_t TEMPTYIE;
    uint32_t RESERVED1[1];
    __IO uint32_t ARLOIE;
    uint32_t RESERVED2[2];
    __IO uint32_t NACKIE;
    uint32_t RESERVED3[7];
    __IO uint32_t GENCALLIE;
    __IO uint32_t SMBDEFAULTIE;
    __IO uint32_t SMBHOSTIE;
    __IO uint32_t SMBALRTIE;
    uint32_t RESERVED4[8];
} stc_i2c_cr2_bit_t;

typedef struct
{
    uint32_t RESERVED0[12];
    __IO uint32_t SLADDR0EN;
    uint32_t RESERVED1[2];
    __IO uint32_t ADDRMOD0;
    uint32_t RESERVED2[16];
} stc_i2c_slr0_bit_t;

typedef struct
{
    uint32_t RESERVED0[12];
    __IO uint32_t SLADDR1EN;
    uint32_t RESERVED1[2];
    __IO uint32_t ADDRMOD1;
    uint32_t RESERVED2[16];
} stc_i2c_slr1_bit_t;

typedef struct
{
    __IO uint32_t STARTF;
    __IO uint32_t SLADDR0F;
    __IO uint32_t SLADDR1F;
    __IO uint32_t TENDF;
    __IO uint32_t STOPF;
    uint32_t RESERVED0[1];
    __IO uint32_t RFULLF;
    __IO uint32_t TEMPTYF;
    uint32_t RESERVED1[1];
    __IO uint32_t ARLOF;
    __IO uint32_t ACKRF;
    uint32_t RESERVED2[1];
    __IO uint32_t NACKF;
    uint32_t RESERVED3[3];
    __IO uint32_t MSL;
    __IO uint32_t BUSY;
    __IO uint32_t TRA;
    uint32_t RESERVED4[1];
    __IO uint32_t GENCALLF;
    __IO uint32_t SMBDEFAULTF;
    __IO uint32_t SMBHOSTF;
    __IO uint32_t SMBALRTF;
    uint32_t RESERVED5[8];
} stc_i2c_sr_bit_t;

typedef struct
{
    __IO uint32_t STARTFCLR;
    __IO uint32_t SLADDR0FCLR;
    __IO uint32_t SLADDR1FCLR;
    __IO uint32_t TENDFCLR;
    __IO uint32_t STOPFCLR;
    uint32_t RESERVED0[1];
    __IO uint32_t RFULLFCLR;
    __IO uint32_t TEMPTYFCLR;
    uint32_t RESERVED1[1];
    __IO uint32_t ARLOFCLR;
    uint32_t RESERVED2[2];
    __IO uint32_t NACKFCLR;
    uint32_t RESERVED3[7];
    __IO uint32_t GENCALLFCLR;
    __IO uint32_t SMBDEFAULTF;
    __IO uint32_t SMBHOSTFCL;
    __IO uint32_t SMBALRTFCLR;
    uint32_t RESERVED4[8];
} stc_i2c_clr_bit_t;

typedef struct
{
    uint32_t RESERVED0[8];
} stc_i2c_dtr_bit_t;

typedef struct
{
    uint32_t RESERVED0[8];
} stc_i2c_drr_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
    __IO uint32_t CKDIV0;
    __IO uint32_t CKDIV1;
    __IO uint32_t CKDIV2;
    uint32_t RESERVED1[4];
    __IO uint32_t FMPE;
    uint32_t RESERVED2[8];
} stc_i2c_ccr_bit_t;

typedef struct
{
    __IO uint32_t DNF0;
    __IO uint32_t DNF1;
    uint32_t RESERVED0[2];
    __IO uint32_t DNFEN;
    __IO uint32_t ANFEN;
    uint32_t RESERVED1[26];
} stc_i2c_fltr_bit_t;

typedef struct
{
    __IO uint32_t SWDTAUTST;
    __IO uint32_t SWDTITS;
    __IO uint32_t SWDTPERI0;
    __IO uint32_t SWDTPERI1;
    __IO uint32_t SWDTCKS0;
    __IO uint32_t SWDTCKS1;
    __IO uint32_t SWDTCKS2;
    __IO uint32_t SWDTCKS3;
    __IO uint32_t SWDTWDPT0;
    __IO uint32_t SWDTWDPT1;
    __IO uint32_t SWDTWDPT2;
    __IO uint32_t SWDTWDPT3;
    __IO uint32_t SWDTSLPOFF;
    uint32_t RESERVED0[3];
    __IO uint32_t HRCFRQSEL0;
    __IO uint32_t HRCFRQSEL1;
    __IO uint32_t HRCFRQSEL2;
    __IO uint32_t HRCFRQSEL3;
    __IO uint32_t HRCSTOP;
    uint32_t RESERVED1[5];
    __IO uint32_t NMIFCLK0;
    __IO uint32_t NMIFCLK1;
    __IO uint32_t NMIFEN;
    __IO uint32_t NMITRG;
    __IO uint32_t NMIEN;
    __IO uint32_t NMIICGEN;
} stc_icg_icg0_bit_t;

typedef struct
{
    uint32_t RESERVED0[8];
    __IO uint32_t LKUPDIS;
    uint32_t RESERVED1[3];
    __IO uint32_t LVD0LVL0;
    __IO uint32_t LVD0LVL1;
    __IO uint32_t LVD0LVL2;
    __IO uint32_t LVD0DIS;
    uint32_t RESERVED2[16];
} stc_icg_icg1_bit_t;

typedef struct
{
    __IO uint32_t WDTAUTST;
    __IO uint32_t WDTITS;
    __IO uint32_t WDTPERI0;
    __IO uint32_t WDTPERI1;
    __IO uint32_t WDTCKS0;
    __IO uint32_t WDTCKS1;
    __IO uint32_t WDTCKS2;
    __IO uint32_t WDTCKS3;
    __IO uint32_t WDTWDPT0;
    __IO uint32_t WDTWDPT1;
    __IO uint32_t WDTWDPT2;
    __IO uint32_t WDTWDPT3;
    __IO uint32_t WDTSLPOFF;
    uint32_t RESERVED0[19];
} stc_icg_icg7_bit_t;

typedef struct
{
    __IO uint32_t NMITRG;
    uint32_t RESERVED0[3];
    __IO uint32_t NMIFCLK0;
    __IO uint32_t NMIFCLK1;
    uint32_t RESERVED1[1];
    __IO uint32_t NMIFEN;
    uint32_t RESERVED2[4];
    __IO uint32_t NOCSEL0;
    __IO uint32_t NOCSEL1;
    uint32_t RESERVED3[1];
    __IO uint32_t NOCEN;
    uint32_t RESERVED4[16];
} stc_intc_nmicr_bit_t;

typedef struct
{
    __IO uint32_t NMIENR;
    __IO uint32_t SWDTENR;
    __IO uint32_t PVD1ENR;
    __IO uint32_t PVD2ENR;
    uint32_t RESERVED0[1];
    __IO uint32_t XTALSTPENR;
    uint32_t RESERVED1[2];
    __IO uint32_t REPENR;
    uint32_t RESERVED2[2];
    __IO uint32_t WDTENR;
    uint32_t RESERVED3[20];
} stc_intc_nmier_bit_t;

typedef struct
{
    __IO uint32_t NMIFR;
    __IO uint32_t SWDTFR;
    __IO uint32_t PVD1FR;
    __IO uint32_t PVD2FR;
    uint32_t RESERVED0[1];
    __IO uint32_t XTALSTPFR;
    uint32_t RESERVED1[2];
    __IO uint32_t REPFR;
    uint32_t RESERVED2[2];
    __IO uint32_t WDTFR;
    uint32_t RESERVED3[20];
} stc_intc_nmifr_bit_t;

typedef struct
{
    __IO uint32_t NMICFR;
    __IO uint32_t SWDTCFR;
    __IO uint32_t PVD1CFR;
    __IO uint32_t PVD2CFR;
    uint32_t RESERVED0[1];
    __IO uint32_t XTALSTPCFR;
    uint32_t RESERVED1[2];
    __IO uint32_t REPCFR;
    uint32_t RESERVED2[2];
    __IO uint32_t WDTCFR;
    uint32_t RESERVED3[20];
} stc_intc_nmicfr_bit_t;

typedef struct
{
    __IO uint32_t EIRQTRG0;
    __IO uint32_t EIRQTRG1;
    uint32_t RESERVED0[2];
    __IO uint32_t EISMPCLK0;
    __IO uint32_t EISMPCLK1;
    uint32_t RESERVED1[1];
    __IO uint32_t EFEN;
    uint32_t RESERVED2[7];
    __IO uint32_t NOCEN;
    uint32_t RESERVED3[16];
} stc_intc_eirqcr_bit_t;

typedef struct
{
    __IO uint32_t EIRQWUEN0;
    __IO uint32_t EIRQWUEN1;
    __IO uint32_t EIRQWUEN2;
    __IO uint32_t EIRQWUEN3;
    __IO uint32_t EIRQWUEN4;
    __IO uint32_t EIRQWUEN5;
    __IO uint32_t EIRQWUEN6;
    __IO uint32_t EIRQWUEN7;
    uint32_t RESERVED0[8];
    __IO uint32_t SWDTWUEN;
    __IO uint32_t PVD1WUEN;
    __IO uint32_t PVD2WUEN;
    __IO uint32_t CMPI0WUEN;
    uint32_t RESERVED1[3];
    __IO uint32_t TMR0WUEN;
    uint32_t RESERVED2[1];
    __IO uint32_t RXWUEN;
    uint32_t RESERVED3[6];
} stc_intc_wupen_bit_t;

typedef struct
{
    __IO uint32_t EIRQFR0;
    __IO uint32_t EIRQFR1;
    __IO uint32_t EIRQFR2;
    __IO uint32_t EIRQFR3;
    __IO uint32_t EIRQFR4;
    __IO uint32_t EIRQFR5;
    __IO uint32_t EIRQFR6;
    __IO uint32_t EIRQFR7;
    uint32_t RESERVED0[24];
} stc_intc_eirqfr_bit_t;

typedef struct
{
    __IO uint32_t EIRQCFR0;
    __IO uint32_t EIRQCFR1;
    __IO uint32_t EIRQCFR2;
    __IO uint32_t EIRQCFR3;
    __IO uint32_t EIRQCFR4;
    __IO uint32_t EIRQCFR5;
    __IO uint32_t EIRQCFR6;
    __IO uint32_t EIRQCFR7;
    uint32_t RESERVED0[24];
} stc_intc_eirqcfr_bit_t;

typedef struct
{
    __IO uint32_t SWIE0;
    __IO uint32_t SWIE1;
    __IO uint32_t SWIE2;
    __IO uint32_t SWIE3;
    __IO uint32_t SWIE4;
    __IO uint32_t SWIE5;
    __IO uint32_t SWIE6;
    __IO uint32_t SWIE7;
    __IO uint32_t SWIE8;
    __IO uint32_t SWIE9;
    __IO uint32_t SWIE10;
    __IO uint32_t SWIE11;
    __IO uint32_t SWIE12;
    __IO uint32_t SWIE13;
    __IO uint32_t SWIE14;
    __IO uint32_t SWIE15;
    uint32_t RESERVED0[16];
} stc_intc_swier_bit_t;

typedef struct
{
    __IO uint32_t EVTE0;
    __IO uint32_t EVTE1;
    __IO uint32_t EVTE2;
    __IO uint32_t EVTE3;
    __IO uint32_t EVTE4;
    __IO uint32_t EVTE5;
    __IO uint32_t EVTE6;
    __IO uint32_t EVTE7;
    __IO uint32_t EVTE8;
    __IO uint32_t EVTE9;
    __IO uint32_t EVTE10;
    __IO uint32_t EVTE11;
    __IO uint32_t EVTE12;
    __IO uint32_t EVTE13;
    __IO uint32_t EVTE14;
    __IO uint32_t EVTE15;
    uint32_t RESERVED0[16];
} stc_intc_evter_bit_t;

typedef struct
{
    __IO uint32_t IER0;
    __IO uint32_t IER1;
    __IO uint32_t IER2;
    __IO uint32_t IER3;
    __IO uint32_t IER4;
    __IO uint32_t IER5;
    __IO uint32_t IER6;
    __IO uint32_t IER7;
    __IO uint32_t IER8;
    __IO uint32_t IER9;
    __IO uint32_t IER10;
    __IO uint32_t IER11;
    __IO uint32_t IER12;
    __IO uint32_t IER13;
    __IO uint32_t IER14;
    __IO uint32_t IER15;
    uint32_t RESERVED0[16];
} stc_intc_ier_bit_t;

typedef struct
{
    __IO uint32_t FLNWT;
    __IO uint32_t CKSMRC;
    uint32_t RESERVED0[1];
    __IO uint32_t HAPORDIS;
    uint32_t RESERVED1[2];
    __IO uint32_t STPDAS;
    __IO uint32_t STOP;
} stc_pwc_stpmcr_bit_t;

typedef struct
{
    __IO uint32_t PWDRV0;
    __IO uint32_t PWDRV1;
    __IO uint32_t PWDRV2;
    __IO uint32_t PWDRV3;
    __IO uint32_t PWDRV4;
    __IO uint32_t PWDRV5;
    __IO uint32_t ACTV;
    __IO uint32_t DVS;
    __IO uint32_t VHRCE;
    __IO uint32_t VPLLE;
    __IO uint32_t HCHDTDIS;
    __IO uint32_t PLHDTDIS;
    __IO uint32_t HDTDIS;
    __IO uint32_t HRCPWRDY;
    __IO uint32_t PLLPWRDY;
    uint32_t RESERVED0[1];
} stc_pwc_pwrc_bit_t;

typedef struct
{
    __IO uint32_t PWMONSEL;
    __IO uint32_t PWMONE;
    uint32_t RESERVED0[6];
} stc_pwc_pwrmonr_bit_t;

typedef struct
{
    uint32_t RESERVED0[4];
    __IO uint32_t RPERDIS;
    __IO uint32_t SRPEF;
    __IO uint32_t HRPEF;
    __IO uint32_t CRPEF;
} stc_pwc_ramcr_bit_t;

typedef struct
{
    uint32_t RESERVED0[2];
    __IO uint32_t L1IEGS0;
    __IO uint32_t L1IEGS1;
    uint32_t RESERVED1[4];
    __IO uint32_t L1NFS0;
    __IO uint32_t L1NFS1;
    __IO uint32_t L1NFDIS;
    __IO uint32_t L1NMIS;
    __IO uint32_t L1IRS;
    __IO uint32_t L1IRE;
    __IO uint32_t L1CMPOE;
    __IO uint32_t L1EN;
    __IO uint32_t EXVCCINEN;
    uint32_t RESERVED2[1];
    __IO uint32_t L2IEGS0;
    __IO uint32_t L2IEGS1;
    uint32_t RESERVED3[4];
    __IO uint32_t L2NFS0;
    __IO uint32_t L2NFS1;
    __IO uint32_t L2NFDIS;
    __IO uint32_t L2NMIS;
    __IO uint32_t L2IRS;
    __IO uint32_t L2IRE;
    __IO uint32_t L2CMPOE;
    __IO uint32_t L2EN;
} stc_pwc_lvdcr0_bit_t;

typedef struct
{
    __IO uint32_t L1MON;
    __IO uint32_t L2MON;
    __IO uint32_t L1DETF;
    __IO uint32_t L2DETF;
    __IO uint32_t L0MON;
    uint32_t RESERVED0[2];
    __IO uint32_t L0CMPOE;
} stc_pwc_lvdcsr1_bit_t;

typedef struct
{
    __IO uint32_t CKRWE;
    __IO uint32_t PWRWE;
    __IO uint32_t FPRCB2;
    __IO uint32_t LVRWE;
    __IO uint32_t FPRCB4;
    __IO uint32_t FPRCB5;
    __IO uint32_t FPRCB6;
    __IO uint32_t FPRCB7;
    uint32_t RESERVED0[8];
} stc_pwc_fprc_bit_t;

typedef struct
{
    __IO uint32_t DBGEN;
    uint32_t RESERVED0[14];
    __IO uint32_t TRSTF;
} stc_pwc_dbgc_bit_t;

typedef struct
{
    __IO uint32_t PORF;
    __IO uint32_t PINRF;
    __IO uint32_t LV0RF;
    __IO uint32_t LV1RF;
    __IO uint32_t LV2RF;
    __IO uint32_t SWDRF;
    __IO uint32_t WDRF;
    __IO uint32_t CKFERF;
    __IO uint32_t SWRF;
    uint32_t RESERVED0[1];
    __IO uint32_t RAMPERF;
    uint32_t RESERVED1[1];
    __IO uint32_t CPULKUPRF;
    __IO uint32_t XTALERF;
    __IO uint32_t MULTIRF;
    __IO uint32_t CLRF;
} stc_rmu_rstf0_bit_t;

typedef struct
{
    __IO uint32_t SPIMDS;
    __IO uint32_t TXMDS;
    uint32_t RESERVED0[1];
    __IO uint32_t MSTR;
    __IO uint32_t SPLPBK;
    __IO uint32_t SPLPBK2;
    __IO uint32_t SPE;
    uint32_t RESERVED1[1];
    __IO uint32_t EIE;
    __IO uint32_t TXIE;
    __IO uint32_t RXIE;
    __IO uint32_t IDIE;
    __IO uint32_t MODFE;
    __IO uint32_t PATE;
    __IO uint32_t PAOE;
    __IO uint32_t PAE;
    uint32_t RESERVED2[16];
} stc_spi_cr1_bit_t;

typedef struct
{
    uint32_t RESERVED0[8];
    __IO uint32_t SS0PV;
    uint32_t RESERVED1[23];
} stc_spi_cfg1_bit_t;

typedef struct
{
    __IO uint32_t OVRERF;
    __IO uint32_t IDLNF;
    __IO uint32_t MODFERF;
    __IO uint32_t PERF;
    __IO uint32_t UDRERF;
    __IO uint32_t TDEF;
    uint32_t RESERVED0[1];
    __IO uint32_t RDFF;
    uint32_t RESERVED1[24];
} stc_spi_sr_bit_t;

typedef struct
{
    __IO uint32_t CPHA;
    __IO uint32_t CPOL;
    uint32_t RESERVED0[6];
    __IO uint32_t DSIZE;
    uint32_t RESERVED1[3];
    __IO uint32_t LSBF;
    uint32_t RESERVED2[19];
} stc_spi_cfg2_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
    __IO uint32_t UDF;
    __IO uint32_t REF;
    uint32_t RESERVED1[14];
} stc_swdt_sr_bit_t;

typedef struct
{
    __IO uint32_t CSTA;
    __IO uint32_t CAPMDA;
    __IO uint32_t INTENA;
    uint32_t RESERVED0[1];
    __IO uint32_t CKDIVA0;
    __IO uint32_t CKDIVA1;
    __IO uint32_t CKDIVA2;
    __IO uint32_t CKDIVA3;
    uint32_t RESERVED1[1];
    __IO uint32_t SYNCLKA;
    uint32_t RESERVED2[2];
    __IO uint32_t HSTAA;
    __IO uint32_t HSTPA;
    __IO uint32_t HCLEA;
    __IO uint32_t HICPA;
    __IO uint32_t CSTB;
    __IO uint32_t CAPMDB;
    __IO uint32_t INTENB;
    uint32_t RESERVED3[1];
    __IO uint32_t CKDIVB0;
    __IO uint32_t CKDIVB1;
    __IO uint32_t CKDIVB2;
    __IO uint32_t CKDIVB3;
    uint32_t RESERVED4[1];
    __IO uint32_t SYNCLKB;
    uint32_t RESERVED5[2];
    __IO uint32_t HSTAB;
    __IO uint32_t HSTPB;
    __IO uint32_t HCLEB;
    __IO uint32_t HICPB;
} stc_tmr0_bconr_bit_t;

typedef struct
{
    __IO uint32_t CMFA;
    uint32_t RESERVED0[15];
    __IO uint32_t CMFB;
    uint32_t RESERVED1[15];
} stc_tmr0_stflr_bit_t;

typedef struct
{
    __IO uint32_t OCEH;
    __IO uint32_t OCEL;
    __IO uint32_t OCPH;
    __IO uint32_t OCPL;
    __IO uint32_t OCIEH;
    __IO uint32_t OCIEL;
    __IO uint32_t OCFH;
    __IO uint32_t OCFL;
    uint32_t RESERVED0[8];
} stc_tmr4_ocsr_bit_t;

typedef struct
{
    __IO uint32_t CHBUFEN0;
    __IO uint32_t CHBUFEN1;
    __IO uint32_t CLBUFEN0;
    __IO uint32_t CLBUFEN1;
    __IO uint32_t MHBUFEN0;
    __IO uint32_t MHBUFEN1;
    __IO uint32_t MLBUFEN0;
    __IO uint32_t MLBUFEN1;
    __IO uint32_t LMCH;
    __IO uint32_t LMCL;
    __IO uint32_t LMMH;
    __IO uint32_t LMML;
    __IO uint32_t MCECH;
    __IO uint32_t MCECL;
    uint32_t RESERVED0[2];
} stc_tmr4_ocer_bit_t;

typedef struct
{
    __IO uint32_t OCFDCH;
    __IO uint32_t OCFPKH;
    __IO uint32_t OCFUCH;
    __IO uint32_t OCFZRH;
    __IO uint32_t OPDCH0;
    __IO uint32_t OPDCH1;
    __IO uint32_t OPPKH0;
    __IO uint32_t OPPKH1;
    __IO uint32_t OPUCH0;
    __IO uint32_t OPUCH1;
    __IO uint32_t OPZRH0;
    __IO uint32_t OPZRH1;
    __IO uint32_t OPNPKH0;
    __IO uint32_t OPNPKH1;
    __IO uint32_t OPNZRH0;
    __IO uint32_t OPNZRH1;
} stc_tmr4_ocmrh_bit_t;

typedef struct
{
    __IO uint32_t OCFDCL;
    __IO uint32_t OCFPKL;
    __IO uint32_t OCFUCL;
    __IO uint32_t OCFZRL;
    __IO uint32_t OPDCL0;
    __IO uint32_t OPDCL1;
    __IO uint32_t OPPKL0;
    __IO uint32_t OPPKL1;
    __IO uint32_t OPUCL0;
    __IO uint32_t OPUCL1;
    __IO uint32_t OPZRL0;
    __IO uint32_t OPZRL1;
    __IO uint32_t OPNPKL0;
    __IO uint32_t OPNPKL1;
    __IO uint32_t OPNZRL0;
    __IO uint32_t OPNZRL1;
    __IO uint32_t EOPNDCL0;
    __IO uint32_t EOPNDCL1;
    __IO uint32_t EOPNUCL0;
    __IO uint32_t EOPNUCL1;
    __IO uint32_t EOPDCL0;
    __IO uint32_t EOPDCL1;
    __IO uint32_t EOPPKL0;
    __IO uint32_t EOPPKL1;
    __IO uint32_t EOPUCL0;
    __IO uint32_t EOPUCL1;
    __IO uint32_t EOPZRL0;
    __IO uint32_t EOPZRL1;
    __IO uint32_t EOPNPKL0;
    __IO uint32_t EOPNPKL1;
    __IO uint32_t EOPNZRL0;
    __IO uint32_t EOPNZRL1;
} stc_tmr4_ocmrl_bit_t;

typedef struct
{
    __IO uint32_t CKDIV0;
    __IO uint32_t CKDIV1;
    __IO uint32_t CKDIV2;
    __IO uint32_t CKDIV3;
    __IO uint32_t CLEAR;
    __IO uint32_t MODE;
    __IO uint32_t STOP;
    __IO uint32_t BUFEN;
    __IO uint32_t IRQPEN;
    __IO uint32_t IRQPF;
    uint32_t RESERVED0[3];
    __IO uint32_t IRQZEN;
    __IO uint32_t IRQZF;
    __IO uint32_t ECKEN;
} stc_tmr4_ccsr_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_tmr4_cvpr_bit_t;

typedef struct
{
    __IO uint32_t DIVCK0;
    __IO uint32_t DIVCK1;
    __IO uint32_t DIVCK2;
    uint32_t RESERVED0[1];
    __IO uint32_t PWMMD0;
    __IO uint32_t PWMMD1;
    __IO uint32_t LVLS0;
    __IO uint32_t LVLS1;
    uint32_t RESERVED1[8];
} stc_tmr4_pocr_bit_t;

typedef struct
{
    __IO uint32_t RTIDU;
    __IO uint32_t RTIDV;
    __IO uint32_t RTIDW;
    uint32_t RESERVED0[1];
    __IO uint32_t RTIFU;
    __IO uint32_t RTICU;
    __IO uint32_t RTEU;
    __IO uint32_t RTSU;
    __IO uint32_t RTIFV;
    __IO uint32_t RTICV;
    __IO uint32_t RTEV;
    __IO uint32_t RTSV;
    __IO uint32_t RTIFW;
    __IO uint32_t RTICW;
    __IO uint32_t RTEW;
    __IO uint32_t RTSW;
} stc_tmr4_rcsr_bit_t;

typedef struct
{
    __IO uint32_t BUFEN0;
    __IO uint32_t BUFEN1;
    __IO uint32_t EVTOS0;
    __IO uint32_t EVTOS1;
    __IO uint32_t EVTOS2;
    __IO uint32_t LMC;
    uint32_t RESERVED0[2];
    __IO uint32_t EVTMS;
    __IO uint32_t EVTDS;
    uint32_t RESERVED1[2];
    __IO uint32_t DEN;
    __IO uint32_t PEN;
    __IO uint32_t UEN;
    __IO uint32_t ZEN;
} stc_tmr4_scsr_bit_t;

typedef struct
{
    uint32_t RESERVED0[6];
    __IO uint32_t MZCE;
    __IO uint32_t MPCE;
    uint32_t RESERVED1[8];
} stc_tmr4_scmr_bit_t;

typedef struct
{
    __IO uint32_t OEUH;
    __IO uint32_t OEUL;
    __IO uint32_t OEVH;
    __IO uint32_t OEVL;
    __IO uint32_t OEWH;
    __IO uint32_t OEWL;
    __IO uint32_t ODT0;
    __IO uint32_t ODT1;
    __IO uint32_t MOE;
    __IO uint32_t AOE;
    uint32_t RESERVED0[6];
    __IO uint32_t OSUH0;
    __IO uint32_t OSUH1;
    __IO uint32_t OSUL0;
    __IO uint32_t OSUL1;
    __IO uint32_t OSVH0;
    __IO uint32_t OSVH1;
    __IO uint32_t OSVL0;
    __IO uint32_t OSVL1;
    __IO uint32_t OSWH0;
    __IO uint32_t OSWH1;
    __IO uint32_t OSWL0;
    __IO uint32_t OSWL1;
    uint32_t RESERVED1[4];
} stc_tmr4_pscr_bit_t;

typedef struct
{
    __IO uint32_t EVTRS0;
    __IO uint32_t EVTRS1;
    __IO uint32_t EVTRS2;
    __IO uint32_t PCTS;
    uint32_t RESERVED0[12];
} stc_tmr4_scer_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_tmra_cnter_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_tmra_perar_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_tmra_cmpar_bit_t;

typedef struct
{
    __IO uint32_t START;
    __IO uint32_t DIR;
    __IO uint32_t MODE;
    __IO uint32_t SYNST;
    __IO uint32_t CKDIV0;
    __IO uint32_t CKDIV1;
    __IO uint32_t CKDIV2;
    __IO uint32_t CKDIV3;
    __IO uint32_t OVSTP;
    uint32_t RESERVED0[3];
    __IO uint32_t INENOVF;
    __IO uint32_t INENUDF;
    __IO uint32_t OVFF;
    __IO uint32_t UDFF;
} stc_tmra_bcstr_bit_t;

typedef struct
{
    __IO uint32_t HSTA0;
    __IO uint32_t HSTA1;
    __IO uint32_t HSTA2;
    uint32_t RESERVED0[1];
    __IO uint32_t HSTP0;
    __IO uint32_t HSTP1;
    __IO uint32_t HSTP2;
    uint32_t RESERVED1[1];
    __IO uint32_t HCLE0;
    __IO uint32_t HCLE1;
    __IO uint32_t HCLE2;
    uint32_t RESERVED2[1];
    __IO uint32_t HCLE3;
    __IO uint32_t HCLE4;
    uint32_t RESERVED3[2];
} stc_tmra_hconr_bit_t;

typedef struct
{
    __IO uint32_t HCUP0;
    __IO uint32_t HCUP1;
    __IO uint32_t HCUP2;
    __IO uint32_t HCUP3;
    __IO uint32_t HCUP4;
    __IO uint32_t HCUP5;
    __IO uint32_t HCUP6;
    __IO uint32_t HCUP7;
    __IO uint32_t HCUP8;
    __IO uint32_t HCUP9;
    __IO uint32_t HCUP10;
    __IO uint32_t HCUP11;
    __IO uint32_t HCUP12;
    uint32_t RESERVED0[3];
} stc_tmra_hcupr_bit_t;

typedef struct
{
    __IO uint32_t HCDO0;
    __IO uint32_t HCDO1;
    __IO uint32_t HCDO2;
    __IO uint32_t HCDO3;
    __IO uint32_t HCDO4;
    __IO uint32_t HCDO5;
    __IO uint32_t HCDO6;
    __IO uint32_t HCDO7;
    __IO uint32_t HCDO8;
    __IO uint32_t HCDO9;
    __IO uint32_t HCDO10;
    __IO uint32_t HCDO11;
    __IO uint32_t HCDO12;
    uint32_t RESERVED0[3];
} stc_tmra_hcdor_bit_t;

typedef struct
{
    __IO uint32_t ITEN1;
    __IO uint32_t ITEN2;
    uint32_t RESERVED0[14];
} stc_tmra_iconr_bit_t;

typedef struct
{
    __IO uint32_t ETEN1;
    __IO uint32_t ETEN2;
    uint32_t RESERVED0[14];
} stc_tmra_econr_bit_t;

typedef struct
{
    __IO uint32_t NOFIENTG;
    __IO uint32_t NOFICKTG0;
    __IO uint32_t NOFICKTG1;
    uint32_t RESERVED0[5];
    __IO uint32_t NOFIENCA;
    __IO uint32_t NOFICKCA0;
    __IO uint32_t NOFICKCA1;
    uint32_t RESERVED1[1];
    __IO uint32_t NOFIENCB;
    __IO uint32_t NOFICKCB0;
    __IO uint32_t NOFICKCB1;
    uint32_t RESERVED2[1];
} stc_tmra_fconr_bit_t;

typedef struct
{
    __IO uint32_t CMPF1;
    __IO uint32_t CMPF2;
    uint32_t RESERVED0[14];
} stc_tmra_stflr_bit_t;

typedef struct
{
    __IO uint32_t BEN;
    __IO uint32_t BSE0;
    __IO uint32_t BSE1;
    uint32_t RESERVED0[13];
} stc_tmra_bconr_bit_t;

typedef struct
{
    __IO uint32_t CAPMD;
    uint32_t RESERVED0[3];
    __IO uint32_t HICP0;
    __IO uint32_t HICP1;
    __IO uint32_t HICP2;
    uint32_t RESERVED1[5];
    __IO uint32_t NOFIENCP;
    __IO uint32_t NOFICKCP0;
    __IO uint32_t NOFICKCP1;
    uint32_t RESERVED2[1];
} stc_tmra_cconr_bit_t;

typedef struct
{
    __IO uint32_t STAC0;
    __IO uint32_t STAC1;
    __IO uint32_t STPC0;
    __IO uint32_t STPC1;
    __IO uint32_t CMPC0;
    __IO uint32_t CMPC1;
    __IO uint32_t PERC0;
    __IO uint32_t PERC1;
    __IO uint32_t FORC0;
    __IO uint32_t FORC1;
    uint32_t RESERVED0[2];
    __IO uint32_t OUTEN;
    uint32_t RESERVED1[3];
} stc_tmra_pconr_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_tmrb_cnter_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_tmrb_perar_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
} stc_tmrb_cmpar_bit_t;

typedef struct
{
    __IO uint32_t START;
    __IO uint32_t DIR;
    __IO uint32_t MODE;
    uint32_t RESERVED0[1];
    __IO uint32_t CKDIV0;
    __IO uint32_t CKDIV1;
    __IO uint32_t CKDIV2;
    __IO uint32_t CKDIV3;
    __IO uint32_t OVSTP;
    uint32_t RESERVED1[3];
    __IO uint32_t INENOVF;
    __IO uint32_t INENUDF;
    __IO uint32_t OVFF;
    __IO uint32_t UDFF;
} stc_tmrb_bcstr_bit_t;

typedef struct
{
    __IO uint32_t HSTA0;
    __IO uint32_t HSTA1;
    __IO uint32_t HSTA2;
    uint32_t RESERVED0[1];
    __IO uint32_t HSTP0;
    __IO uint32_t HSTP1;
    __IO uint32_t HSTP2;
    uint32_t RESERVED1[1];
    __IO uint32_t HCLE0;
    __IO uint32_t HCLE1;
    __IO uint32_t HCLE2;
    uint32_t RESERVED2[3];
    __IO uint32_t HCLE5;
    __IO uint32_t HCLE6;
} stc_tmrb_hconr_bit_t;

typedef struct
{
    uint32_t RESERVED0[8];
    __IO uint32_t HCUP8;
    __IO uint32_t HCUP9;
    __IO uint32_t HCUP10;
    uint32_t RESERVED1[5];
} stc_tmrb_hcupr_bit_t;

typedef struct
{
    uint32_t RESERVED0[8];
    __IO uint32_t HCDO8;
    __IO uint32_t HCDO9;
    __IO uint32_t HCDO10;
    uint32_t RESERVED1[5];
} stc_tmrb_hcdor_bit_t;

typedef struct
{
    __IO uint32_t ITEN1;
    __IO uint32_t ITEN2;
    __IO uint32_t ITEN3;
    __IO uint32_t ITEN4;
    __IO uint32_t ITEN5;
    __IO uint32_t ITEN6;
    uint32_t RESERVED0[10];
} stc_tmrb_iconr_bit_t;

typedef struct
{
    __IO uint32_t ETEN1;
    __IO uint32_t ETEN2;
    __IO uint32_t ETEN3;
    __IO uint32_t ETEN4;
    __IO uint32_t ETEN5;
    __IO uint32_t ETEN6;
    uint32_t RESERVED0[10];
} stc_tmrb_econr_bit_t;

typedef struct
{
    __IO uint32_t CMPF1;
    __IO uint32_t CMPF2;
    __IO uint32_t CMPF3;
    __IO uint32_t CMPF4;
    __IO uint32_t CMPF5;
    __IO uint32_t CMPF6;
    uint32_t RESERVED0[10];
} stc_tmrb_stflr_bit_t;

typedef struct
{
    __IO uint32_t BEN;
    __IO uint32_t BSE0;
    __IO uint32_t BSE1;
    uint32_t RESERVED0[13];
} stc_tmrb_bconr_bit_t;

typedef struct
{
    __IO uint32_t CAPMD;
    uint32_t RESERVED0[3];
    __IO uint32_t HICP0;
    __IO uint32_t HICP1;
    __IO uint32_t HICP2;
    uint32_t RESERVED1[5];
    __IO uint32_t NOFIENCP;
    __IO uint32_t NOFICKCP0;
    __IO uint32_t NOFICKCP1;
    uint32_t RESERVED2[1];
} stc_tmrb_cconr_bit_t;

typedef struct
{
    __IO uint32_t STAC0;
    __IO uint32_t STAC1;
    __IO uint32_t STPC0;
    __IO uint32_t STPC1;
    __IO uint32_t CMPC0;
    __IO uint32_t CMPC1;
    __IO uint32_t PERC0;
    __IO uint32_t PERC1;
    __IO uint32_t FORC0;
    __IO uint32_t FORC1;
    uint32_t RESERVED0[2];
    __IO uint32_t OUTEN;
    uint32_t RESERVED1[3];
} stc_tmrb_pconr_bit_t;

typedef struct
{
    __IO uint32_t PE;
    __IO uint32_t FE;
    uint32_t RESERVED0[1];
    __IO uint32_t ORE;
    uint32_t RESERVED1[1];
    __IO uint32_t RXNE;
    __IO uint32_t TC;
    __IO uint32_t TXE;
    uint32_t RESERVED2[8];
    __IO uint32_t MPB;
    uint32_t RESERVED3[15];
} stc_usart_sr_bit_t;

typedef struct
{
    uint32_t RESERVED0[9];
    __IO uint32_t MPID;
    uint32_t RESERVED1[22];
} stc_usart_dr_bit_t;

typedef struct
{
    uint32_t RESERVED0[2];
    __IO uint32_t RE;
    __IO uint32_t TE;
    __IO uint32_t SLME;
    __IO uint32_t RIE;
    __IO uint32_t TCIE;
    __IO uint32_t TXEIE;
    uint32_t RESERVED1[1];
    __IO uint32_t PS;
    __IO uint32_t PCE;
    uint32_t RESERVED2[1];
    __IO uint32_t M;
    uint32_t RESERVED3[2];
    __IO uint32_t OVER8;
    __IO uint32_t CPE;
    __IO uint32_t CFE;
    uint32_t RESERVED4[1];
    __IO uint32_t CORE;
    uint32_t RESERVED5[4];
    __IO uint32_t MS;
    uint32_t RESERVED6[3];
    __IO uint32_t ML;
    uint32_t RESERVED7[1];
    __IO uint32_t NFE;
    __IO uint32_t SBS;
} stc_usart_cr1_bit_t;

typedef struct
{
    __IO uint32_t MPE;
    uint32_t RESERVED0[10];
    __IO uint32_t CLKC0;
    __IO uint32_t CLKC1;
    __IO uint32_t STOP;
    uint32_t RESERVED1[18];
} stc_usart_cr2_bit_t;

typedef struct
{
    uint32_t RESERVED0[3];
    __IO uint32_t HDSEL;
    uint32_t RESERVED1[5];
    __IO uint32_t CTSE;
    uint32_t RESERVED2[22];
} stc_usart_cr3_bit_t;

typedef struct
{
    __IO uint32_t PSC0;
    __IO uint32_t PSC1;
    uint32_t RESERVED0[30];
} stc_usart_pr_bit_t;

typedef struct
{
    __IO uint32_t PERI0;
    __IO uint32_t PERI1;
    uint32_t RESERVED0[2];
    __IO uint32_t CKS0;
    __IO uint32_t CKS1;
    __IO uint32_t CKS2;
    __IO uint32_t CKS3;
    __IO uint32_t WDPT0;
    __IO uint32_t WDPT1;
    __IO uint32_t WDPT2;
    __IO uint32_t WDPT3;
    uint32_t RESERVED1[4];
    __IO uint32_t SLPOFF;
    uint32_t RESERVED2[14];
    __IO uint32_t ITS;
} stc_wdt_cr_bit_t;

typedef struct
{
    uint32_t RESERVED0[16];
    __IO uint32_t UDF;
    __IO uint32_t REF;
    uint32_t RESERVED1[14];
} stc_wdt_sr_bit_t;


typedef struct
{
    stc_adc_str_bit_t                        STR_b;
    uint32_t                                 RESERVED0[8];
    stc_adc_cr0_bit_t                        CR0_b;
    stc_adc_cr1_bit_t                        CR1_b;
    uint32_t                                 RESERVED1[32];
    stc_adc_trgsr_bit_t                      TRGSR_b;
    uint32_t                                 RESERVED2[96];
    stc_adc_exchselr_bit_t                   EXCHSELR_b;
    uint32_t                                 RESERVED3[8];
    stc_adc_shcr_bit_t                       SHCR_b;
    uint32_t                                 RESERVED4[320];
    stc_adc_isr_bit_t                        ISR_b;
    stc_adc_icr_bit_t                        ICR_b;
    stc_adc_isclrr_bit_t                     ISCLRR_b;
} bCM_ADC_TypeDef;

typedef struct
{
    stc_aos_intc_strgcr_bit_t                INTC_STRGCR_b;
} bCM_AOS_TypeDef;

typedef struct
{
    stc_cmp_mdr_bit_t                        MDR_b;
    stc_cmp_fir_bit_t                        FIR_b;
    stc_cmp_ocr_bit_t                        OCR_b;
    stc_cmp_vsr_bit_t                        VSR_b;
    stc_cmp_twr1_bit_t                       TWR1_b;
    stc_cmp_twr2_bit_t                       TWR2_b;
} bCM_CMP_TypeDef;

typedef struct
{
    uint32_t                                 RESERVED0[32];
    stc_cmu_xtalstdsr_bit_t                  XTALSTDSR_b;
    uint32_t                                 RESERVED1[88];
    stc_cmu_xtalcr_bit_t                     XTALCR_b;
    uint32_t                                 RESERVED2[24];
    stc_cmu_xtalcfgr_bit_t                   XTALCFGR_b;
    uint32_t                                 RESERVED3[24];
    stc_cmu_hrccr_bit_t                      HRCCR_b;
    uint32_t                                 RESERVED4[56];
    stc_cmu_oscstbsr_bit_t                   OSCSTBSR_b;
    uint32_t                                 RESERVED5[24];
    stc_cmu_mcocfgr_bit_t                    MCOCFGR_b;
    uint32_t                                 RESERVED6[24];
    stc_cmu_xtalstdcr_bit_t                  XTALSTDCR_b;
    uint32_t                                 RESERVED7[56];
    stc_cmu_fcg_bit_t                        FCG_b;
    uint32_t                                 RESERVED8[64];
    stc_cmu_lrccr_bit_t                      LRCCR_b;
    uint32_t                                 RESERVED9[24];
    stc_cmu_mrccr_bit_t                      MRCCR_b;
    uint32_t                                 RESERVED10[24];
    stc_cmu_pllcfgr_bit_t                    PLLCFGR_b;
    stc_cmu_pllcr_bit_t                      PLLCR_b;
    uint32_t                                 RESERVED11[24];
    stc_cmu_tpiuckcfgr_bit_t                 TPIUCKCFGR_b;
} bCM_CMU_TypeDef;

typedef struct
{
    stc_crc_cr_bit_t                         CR_b;
} bCM_CRC_TypeDef;

typedef struct
{
    stc_ctc_cr1_bit_t                        CR1_b;
    stc_ctc_cr2_bit_t                        CR2_b;
    stc_ctc_str_bit_t                        STR_b;
} bCM_CTC_TypeDef;

typedef struct
{
    stc_cmp_dadr1_bit_t                      DADR1_b;
    uint32_t                                 RESERVED0[48];
    stc_cmp_dacr1_bit_t                      DACR1_b;
    uint32_t                                 RESERVED1[16];
    stc_cmp_dadc1_bit_t                      DADC1_b;
} bCM_DAC_TypeDef;

typedef struct
{
    stc_dcu_ctl_bit_t                        CTL_b;
    stc_dcu_flag_bit_t                       FLAG_b;
    uint32_t                                 RESERVED0[96];
    stc_dcu_flagclr_bit_t                    FLAGCLR_b;
    stc_dcu_intsel_bit_t                     INTSEL_b;
} bCM_DCU_TypeDef;

typedef struct
{
    stc_dma_en_bit_t                         EN_b;
    stc_dma_intstat0_bit_t                   INTSTAT0_b;
    stc_dma_intstat1_bit_t                   INTSTAT1_b;
    stc_dma_intmask0_bit_t                   INTMASK0_b;
    stc_dma_intmask1_bit_t                   INTMASK1_b;
    stc_dma_intclr0_bit_t                    INTCLR0_b;
    stc_dma_intclr1_bit_t                    INTCLR1_b;
    stc_dma_chen_bit_t                       CHEN_b;
    uint32_t                                 RESERVED0[32];
    stc_dma_chstat_bit_t                     CHSTAT_b;
    uint32_t                                 RESERVED1[128];
    stc_dma_chenclr_bit_t                    CHENCLR_b;
    uint32_t                                 RESERVED2[96];
    stc_dma_ch0ctl0_bit_t                    CH0CTL0_b;
    stc_dma_ch0ctl1_bit_t                    CH0CTL1_b;
    uint32_t                                 RESERVED3[448];
    stc_dma_ch1ctl0_bit_t                    CH1CTL0_b;
    stc_dma_ch1ctl1_bit_t                    CH1CTL1_b;
    uint32_t                                 RESERVED4[448];
    stc_dma_ch2ctl0_bit_t                    CH2CTL0_b;
    stc_dma_ch2ctl1_bit_t                    CH2CTL1_b;
    uint32_t                                 RESERVED5[448];
    stc_dma_ch3ctl0_bit_t                    CH3CTL0_b;
    stc_dma_ch3ctl1_bit_t                    CH3CTL1_b;
} bCM_DMA_TypeDef;

typedef struct
{
    uint32_t                                 RESERVED0[32];
    stc_efm_fstp_bit_t                       FSTP_b;
    stc_efm_frmc_bit_t                       FRMC_b;
    stc_efm_fwmc_bit_t                       FWMC_b;
    stc_efm_fsr_bit_t                        FSR_b;
    stc_efm_fsclr_bit_t                      FSCLR_b;
    stc_efm_fite_bit_t                       FITE_b;
    uint32_t                                 RESERVED1[4912];
    stc_efm_hrccfgr_bit_t                    HRCCFGR_b;
} bCM_EFM_TypeDef;

typedef struct
{
    stc_emb_ctl_bit_t                        CTL_b;
    stc_emb_pwmlv_bit_t                      PWMLV_b;
    stc_emb_soe_bit_t                        SOE_b;
    stc_emb_stat_bit_t                       STAT_b;
    stc_emb_statclr_bit_t                    STATCLR_b;
    stc_emb_inten_bit_t                      INTEN_b;
    stc_emb_ecsr_bit_t                       ECSR_b;
} bCM_EMB_TypeDef;

typedef struct
{
    uint32_t                                 RESERVED0[96];
    stc_fcm_str_bit_t                        STR_b;
    stc_fcm_mccr_bit_t                       MCCR_b;
    stc_fcm_rccr_bit_t                       RCCR_b;
    stc_fcm_rier_bit_t                       RIER_b;
    stc_fcm_sr_bit_t                         SR_b;
    stc_fcm_clr_bit_t                        CLR_b;
} bCM_FCM_TypeDef;

typedef struct
{
    stc_gpio_pidr_bit_t                      PIDR0_b;
    stc_gpio_pidr_bit_t                      PIDR1_b;
    stc_gpio_pidr_bit_t                      PIDR2_b;
    stc_gpio_pidr_bit_t                      PIDR3_b;
    stc_gpio_pidr_bit_t                      PIDR4_b;
    stc_gpio_pidr_bit_t                      PIDR5_b;
    uint32_t                                 RESERVED0[8];
    stc_gpio_pidr_bit_t                      PIDR7_b;
    uint32_t                                 RESERVED1[8];
    stc_gpio_pidr_bit_t                      PIDR9_b;
    stc_gpio_pidr_bit_t                      PIDRA_b;
    stc_gpio_pidr_bit_t                      PIDRB_b;
    uint32_t                                 RESERVED2[8];
    stc_gpio_pidr_bit_t                      PIDRD_b;
    stc_gpio_pidr_bit_t                      PIDRE_b;
    uint32_t                                 RESERVED3[8];
    stc_gpio_podr_bit_t                      PODR0_b;
    stc_gpio_podr_bit_t                      PODR1_b;
    stc_gpio_podr_bit_t                      PODR2_b;
    stc_gpio_podr_bit_t                      PODR3_b;
    stc_gpio_podr_bit_t                      PODR4_b;
    stc_gpio_podr_bit_t                      PODR5_b;
    uint32_t                                 RESERVED4[8];
    stc_gpio_podr_bit_t                      PODR7_b;
    uint32_t                                 RESERVED5[8];
    stc_gpio_podr_bit_t                      PODR9_b;
    stc_gpio_podr_bit_t                      PODRA_b;
    stc_gpio_podr_bit_t                      PODRB_b;
    uint32_t                                 RESERVED6[8];
    stc_gpio_podr_bit_t                      PODRD_b;
    stc_gpio_podr_bit_t                      PODRE_b;
    uint32_t                                 RESERVED7[8];
    stc_gpio_poer_bit_t                      POER0_b;
    stc_gpio_poer_bit_t                      POER1_b;
    stc_gpio_poer_bit_t                      POER2_b;
    stc_gpio_poer_bit_t                      POER3_b;
    stc_gpio_poer_bit_t                      POER4_b;
    stc_gpio_poer_bit_t                      POER5_b;
    uint32_t                                 RESERVED8[8];
    stc_gpio_poer_bit_t                      POER7_b;
    uint32_t                                 RESERVED9[8];
    stc_gpio_poer_bit_t                      POER9_b;
    stc_gpio_poer_bit_t                      POERA_b;
    stc_gpio_poer_bit_t                      POERB_b;
    uint32_t                                 RESERVED10[8];
    stc_gpio_poer_bit_t                      POERD_b;
    stc_gpio_poer_bit_t                      POERE_b;
    uint32_t                                 RESERVED11[8];
    stc_gpio_posr_bit_t                      POSR0_b;
    stc_gpio_posr_bit_t                      POSR1_b;
    stc_gpio_posr_bit_t                      POSR2_b;
    stc_gpio_posr_bit_t                      POSR3_b;
    stc_gpio_posr_bit_t                      POSR4_b;
    stc_gpio_posr_bit_t                      POSR5_b;
    uint32_t                                 RESERVED12[8];
    stc_gpio_posr_bit_t                      POSR7_b;
    uint32_t                                 RESERVED13[8];
    stc_gpio_posr_bit_t                      POSR9_b;
    stc_gpio_posr_bit_t                      POSRA_b;
    stc_gpio_posr_bit_t                      POSRB_b;
    uint32_t                                 RESERVED14[8];
    stc_gpio_posr_bit_t                      POSRD_b;
    stc_gpio_posr_bit_t                      POSRE_b;
    uint32_t                                 RESERVED15[8];
    stc_gpio_porr_bit_t                      PORR0_b;
    stc_gpio_porr_bit_t                      PORR1_b;
    stc_gpio_porr_bit_t                      PORR2_b;
    stc_gpio_porr_bit_t                      PORR3_b;
    stc_gpio_porr_bit_t                      PORR4_b;
    stc_gpio_porr_bit_t                      PORR5_b;
    uint32_t                                 RESERVED16[8];
    stc_gpio_porr_bit_t                      PORR7_b;
    uint32_t                                 RESERVED17[8];
    stc_gpio_porr_bit_t                      PORR9_b;
    stc_gpio_porr_bit_t                      PORRA_b;
    stc_gpio_porr_bit_t                      PORRB_b;
    uint32_t                                 RESERVED18[8];
    stc_gpio_porr_bit_t                      PORRD_b;
    stc_gpio_porr_bit_t                      PORRE_b;
    uint32_t                                 RESERVED19[8];
    stc_gpio_potr_bit_t                      POTR0_b;
    stc_gpio_potr_bit_t                      POTR1_b;
    stc_gpio_potr_bit_t                      POTR2_b;
    stc_gpio_potr_bit_t                      POTR3_b;
    stc_gpio_potr_bit_t                      POTR4_b;
    stc_gpio_potr_bit_t                      POTR5_b;
    uint32_t                                 RESERVED20[8];
    stc_gpio_potr_bit_t                      POTR7_b;
    uint32_t                                 RESERVED21[8];
    stc_gpio_potr_bit_t                      POTR9_b;
    stc_gpio_potr_bit_t                      POTRA_b;
    stc_gpio_potr_bit_t                      POTRB_b;
    uint32_t                                 RESERVED22[8];
    stc_gpio_potr_bit_t                      POTRD_b;
    stc_gpio_potr_bit_t                      POTRE_b;
    uint32_t                                 RESERVED23[5384];
    stc_gpio_pspcr_bit_t                     PSPCR_b;
    uint32_t                                 RESERVED24[16];
    stc_gpio_pccr_bit_t                      PCCR_b;
    stc_gpio_pinaer_bit_t                    PINAER_b;
    stc_gpio_pwpr_bit_t                      PWPR_b;
    uint32_t                                 RESERVED25[1968];
    stc_gpio_pcr_bit_t                       PCR00_b;
    uint32_t                                 RESERVED26[16];
    stc_gpio_pcr_bit_t                       PCR01_b;
    uint32_t                                 RESERVED27[16];
    stc_gpio_pcr_bit_t                       PCR02_b;
    uint32_t                                 RESERVED28[176];
    stc_gpio_pcr_bit_t                       PCR10_b;
    uint32_t                                 RESERVED29[16];
    stc_gpio_pcr_bit_t                       PCR11_b;
    uint32_t                                 RESERVED30[272];
    stc_gpio_pcr_bit_t                       PCR22_b;
    uint32_t                                 RESERVED31[16];
    stc_gpio_pcr_bit_t                       PCR23_b;
    uint32_t                                 RESERVED32[16];
    stc_gpio_pcr_bit_t                       PCR24_b;
    uint32_t                                 RESERVED33[112];
    stc_gpio_pcr_bit_t                       PCR30_b;
    uint32_t                                 RESERVED34[16];
    stc_gpio_pcr_bit_t                       PCR31_b;
    uint32_t                                 RESERVED35[16];
    stc_gpio_pcr_bit_t                       PCR32_b;
    uint32_t                                 RESERVED36[16];
    stc_gpio_pcr_bit_t                       PCR33_b;
    uint32_t                                 RESERVED37[80];
    stc_gpio_pcr_bit_t                       PCR36_b;
    uint32_t                                 RESERVED38[16];
    stc_gpio_pcr_bit_t                       PCR37_b;
    uint32_t                                 RESERVED39[16];
    stc_gpio_pcr_bit_t                       PCR40_b;
    uint32_t                                 RESERVED40[16];
    stc_gpio_pcr_bit_t                       PCR41_b;
    uint32_t                                 RESERVED41[16];
    stc_gpio_pcr_bit_t                       PCR42_b;
    uint32_t                                 RESERVED42[16];
    stc_gpio_pcr_bit_t                       PCR43_b;
    uint32_t                                 RESERVED43[16];
    stc_gpio_pcr_bit_t                       PCR44_b;
    uint32_t                                 RESERVED44[16];
    stc_gpio_pcr_bit_t                       PCR45_b;
    uint32_t                                 RESERVED45[16];
    stc_gpio_pcr_bit_t                       PCR46_b;
    uint32_t                                 RESERVED46[16];
    stc_gpio_pcr_bit_t                       PCR47_b;
    uint32_t                                 RESERVED47[16];
    stc_gpio_pcr_bit_t                       PCR50_b;
    uint32_t                                 RESERVED48[496];
    stc_gpio_pcr_bit_t                       PCR70_b;
    uint32_t                                 RESERVED49[16];
    stc_gpio_pcr_bit_t                       PCR71_b;
    uint32_t                                 RESERVED50[16];
    stc_gpio_pcr_bit_t                       PCR72_b;
    uint32_t                                 RESERVED51[16];
    stc_gpio_pcr_bit_t                       PCR73_b;
    uint32_t                                 RESERVED52[16];
    stc_gpio_pcr_bit_t                       PCR74_b;
    uint32_t                                 RESERVED53[16];
    stc_gpio_pcr_bit_t                       PCR75_b;
    uint32_t                                 RESERVED54[16];
    stc_gpio_pcr_bit_t                       PCR76_b;
    uint32_t                                 RESERVED55[336];
    stc_gpio_pcr_bit_t                       PCR91_b;
    uint32_t                                 RESERVED56[16];
    stc_gpio_pcr_bit_t                       PCR92_b;
    uint32_t                                 RESERVED57[16];
    stc_gpio_pcr_bit_t                       PCR93_b;
    uint32_t                                 RESERVED58[16];
    stc_gpio_pcr_bit_t                       PCR94_b;
    uint32_t                                 RESERVED59[176];
    stc_gpio_pcr_bit_t                       PCRA2_b;
    uint32_t                                 RESERVED60[16];
    stc_gpio_pcr_bit_t                       PCRA3_b;
    uint32_t                                 RESERVED61[16];
    stc_gpio_pcr_bit_t                       PCRA4_b;
    uint32_t                                 RESERVED62[16];
    stc_gpio_pcr_bit_t                       PCRA5_b;
    uint32_t                                 RESERVED63[80];
    stc_gpio_pcr_bit_t                       PCRB0_b;
    uint32_t                                 RESERVED64[16];
    stc_gpio_pcr_bit_t                       PCRB1_b;
    uint32_t                                 RESERVED65[16];
    stc_gpio_pcr_bit_t                       PCRB2_b;
    uint32_t                                 RESERVED66[16];
    stc_gpio_pcr_bit_t                       PCRB3_b;
    uint32_t                                 RESERVED67[16];
    stc_gpio_pcr_bit_t                       PCRB4_b;
    uint32_t                                 RESERVED68[16];
    stc_gpio_pcr_bit_t                       PCRB5_b;
    uint32_t                                 RESERVED69[16];
    stc_gpio_pcr_bit_t                       PCRB6_b;
    uint32_t                                 RESERVED70[16];
    stc_gpio_pcr_bit_t                       PCRB7_b;
    uint32_t                                 RESERVED71[368];
    stc_gpio_pcr_bit_t                       PCRD3_b;
    uint32_t                                 RESERVED72[16];
    stc_gpio_pcr_bit_t                       PCRD4_b;
    uint32_t                                 RESERVED73[16];
    stc_gpio_pcr_bit_t                       PCRD5_b;
    uint32_t                                 RESERVED74[16];
    stc_gpio_pcr_bit_t                       PCRD6_b;
    uint32_t                                 RESERVED75[16];
    stc_gpio_pcr_bit_t                       PCRD7_b;
    uint32_t                                 RESERVED76[80];
    stc_gpio_pcr_bit_t                       PCRE2_b;
} bCM_GPIO_TypeDef;

typedef struct
{
    stc_i2c_cr1_bit_t                        CR1_b;
    stc_i2c_cr2_bit_t                        CR2_b;
    uint32_t                                 RESERVED0[64];
    stc_i2c_slr0_bit_t                       SLR0_b;
    stc_i2c_slr1_bit_t                       SLR1_b;
    uint32_t                                 RESERVED1[32];
    stc_i2c_sr_bit_t                         SR_b;
    stc_i2c_clr_bit_t                        CLR_b;
    uint32_t                                 RESERVED2[64];
    stc_i2c_ccr_bit_t                        CCR_b;
    stc_i2c_fltr_bit_t                       FLTR_b;
} bCM_I2C_TypeDef;

typedef struct
{
    stc_icg_icg0_bit_t                       ICG0_b;
    stc_icg_icg1_bit_t                       ICG1_b;
    uint32_t                                 RESERVED0[160];
    stc_icg_icg7_bit_t                       ICG7_b;
} bCM_ICG_TypeDef;

typedef struct
{
    stc_intc_nmicr_bit_t                     NMICR_b;
    stc_intc_nmier_bit_t                     NMIER_b;
    stc_intc_nmifr_bit_t                     NMIFR_b;
    stc_intc_nmicfr_bit_t                    NMICFR_b;
    stc_intc_eirqcr_bit_t                    EIRQCR0_b;
    stc_intc_eirqcr_bit_t                    EIRQCR1_b;
    stc_intc_eirqcr_bit_t                    EIRQCR2_b;
    stc_intc_eirqcr_bit_t                    EIRQCR3_b;
    stc_intc_eirqcr_bit_t                    EIRQCR4_b;
    stc_intc_eirqcr_bit_t                    EIRQCR5_b;
    stc_intc_eirqcr_bit_t                    EIRQCR6_b;
    stc_intc_eirqcr_bit_t                    EIRQCR7_b;
    uint32_t                                 RESERVED0[256];
    stc_intc_wupen_bit_t                     WUPEN_b;
    stc_intc_eirqfr_bit_t                    EIRQFR_b;
    stc_intc_eirqcfr_bit_t                   EIRQCFR_b;
    uint32_t                                 RESERVED1[4608];
    stc_intc_swier_bit_t                     SWIER_b;
    stc_intc_evter_bit_t                     EVTER_b;
    stc_intc_ier_bit_t                       IER_b;
} bCM_INTC_TypeDef;

typedef struct
{
    stc_pwc_stpmcr_bit_t                     STPMCR_b;
    uint32_t                                 RESERVED0[24];
    stc_pwc_pwrc_bit_t                       PWRC_b;
    uint32_t                                 RESERVED1[16];
    stc_pwc_pwrmonr_bit_t                    PWRMONR_b;
    uint32_t                                 RESERVED2[24];
    stc_pwc_ramcr_bit_t                      RAMCR_b;
    uint32_t                                 RESERVED3[24];
    stc_pwc_lvdcr0_bit_t                     LVDCR0_b;
    stc_pwc_lvdcsr1_bit_t                    LVDCSR1_b;
    uint32_t                                 RESERVED4[88];
    stc_pwc_fprc_bit_t                       FPRC_b;
    uint32_t                                 RESERVED5[240];
    stc_pwc_dbgc_bit_t                       DBGC_b;
} bCM_PWC_TypeDef;

typedef struct
{
    stc_rmu_rstf0_bit_t                      RSTF0_b;
} bCM_RMU_TypeDef;

typedef struct
{
    uint32_t                                 RESERVED0[32];
    stc_spi_cr1_bit_t                        CR1_b;
    uint32_t                                 RESERVED1[32];
    stc_spi_cfg1_bit_t                       CFG1_b;
    uint32_t                                 RESERVED2[32];
    stc_spi_sr_bit_t                         SR_b;
    stc_spi_cfg2_bit_t                       CFG2_b;
} bCM_SPI_TypeDef;

typedef struct
{
    uint32_t                                 RESERVED0[32];
    stc_swdt_sr_bit_t                        SR_b;
} bCM_SWDT_TypeDef;

typedef struct
{
    uint32_t                                 RESERVED0[128];
    stc_tmr0_bconr_bit_t                     BCONR_b;
    stc_tmr0_stflr_bit_t                     STFLR_b;
} bCM_TMR0_TypeDef;

typedef struct
{
    uint32_t                                 RESERVED0[192];
    stc_tmr4_ocsr_bit_t                      OCSRU_b;
    stc_tmr4_ocer_bit_t                      OCERU_b;
    stc_tmr4_ocsr_bit_t                      OCSRV_b;
    stc_tmr4_ocer_bit_t                      OCERV_b;
    stc_tmr4_ocsr_bit_t                      OCSRW_b;
    stc_tmr4_ocer_bit_t                      OCERW_b;
    stc_tmr4_ocmrh_bit_t                     OCMRHUH_b;
    uint32_t                                 RESERVED1[16];
    stc_tmr4_ocmrl_bit_t                     OCMRLUL_b;
    stc_tmr4_ocmrh_bit_t                     OCMRHVH_b;
    uint32_t                                 RESERVED2[16];
    stc_tmr4_ocmrl_bit_t                     OCMRLVL_b;
    stc_tmr4_ocmrh_bit_t                     OCMRHWH_b;
    uint32_t                                 RESERVED3[16];
    stc_tmr4_ocmrl_bit_t                     OCMRLWL_b;
    uint32_t                                 RESERVED4[96];
    stc_tmr4_ccsr_bit_t                      CCSR_b;
    uint32_t                                 RESERVED5[624];
    stc_tmr4_pocr_bit_t                      POCRU_b;
    uint32_t                                 RESERVED6[16];
    stc_tmr4_pocr_bit_t                      POCRV_b;
    uint32_t                                 RESERVED7[16];
    stc_tmr4_pocr_bit_t                      POCRW_b;
    uint32_t                                 RESERVED8[16];
    stc_tmr4_rcsr_bit_t                      RCSR_b;
    uint32_t                                 RESERVED9[272];
    stc_tmr4_scsr_bit_t                      SCSRUH_b;
    stc_tmr4_scmr_bit_t                      SCMRUH_b;
    stc_tmr4_scsr_bit_t                      SCSRUL_b;
    stc_tmr4_scmr_bit_t                      SCMRUL_b;
    stc_tmr4_scsr_bit_t                      SCSRVH_b;
    stc_tmr4_scmr_bit_t                      SCMRVH_b;
    stc_tmr4_scsr_bit_t                      SCSRVL_b;
    stc_tmr4_scmr_bit_t                      SCMRVL_b;
    stc_tmr4_scsr_bit_t                      SCSRWH_b;
    stc_tmr4_scmr_bit_t                      SCMRWH_b;
    stc_tmr4_scsr_bit_t                      SCSRWL_b;
    stc_tmr4_scmr_bit_t                      SCMRWL_b;
    stc_tmr4_pscr_bit_t                      PSCR_b;
    stc_tmr4_scer_bit_t                      SCER_b;
} bCM_TMR4_TypeDef;

typedef struct
{
    uint32_t                                 RESERVED0[1024];
    stc_tmra_bcstr_bit_t                     BCSTR_b;
    uint32_t                                 RESERVED1[16];
    stc_tmra_hconr_bit_t                     HCONR_b;
    uint32_t                                 RESERVED2[16];
    stc_tmra_hcupr_bit_t                     HCUPR_b;
    uint32_t                                 RESERVED3[16];
    stc_tmra_hcdor_bit_t                     HCDOR_b;
    uint32_t                                 RESERVED4[16];
    stc_tmra_iconr_bit_t                     ICONR_b;
    uint32_t                                 RESERVED5[16];
    stc_tmra_econr_bit_t                     ECONR_b;
    uint32_t                                 RESERVED6[16];
    stc_tmra_fconr_bit_t                     FCONR_b;
    uint32_t                                 RESERVED7[16];
    stc_tmra_stflr_bit_t                     STFLR_b;
    uint32_t                                 RESERVED8[272];
    stc_tmra_bconr_bit_t                     BCONR_b;
    uint32_t                                 RESERVED9[496];
    stc_tmra_cconr_bit_t                     CCONR1_b;
    uint32_t                                 RESERVED10[16];
    stc_tmra_cconr_bit_t                     CCONR2_b;
    uint32_t                                 RESERVED11[464];
    stc_tmra_pconr_bit_t                     PCONR1_b;
    uint32_t                                 RESERVED12[16];
    stc_tmra_pconr_bit_t                     PCONR2_b;
} bCM_TMRA_TypeDef;

typedef struct
{
    uint32_t                                 RESERVED0[1024];
    stc_tmrb_bcstr_bit_t                     BCSTR_b;
    uint32_t                                 RESERVED1[16];
    stc_tmrb_hconr_bit_t                     HCONR_b;
    uint32_t                                 RESERVED2[16];
    stc_tmrb_hcupr_bit_t                     HCUPR_b;
    uint32_t                                 RESERVED3[16];
    stc_tmrb_hcdor_bit_t                     HCDOR_b;
    uint32_t                                 RESERVED4[16];
    stc_tmrb_iconr_bit_t                     ICONR_b;
    uint32_t                                 RESERVED5[16];
    stc_tmrb_econr_bit_t                     ECONR_b;
    uint32_t                                 RESERVED6[48];
    stc_tmrb_stflr_bit_t                     STFLR_b;
    uint32_t                                 RESERVED7[272];
    stc_tmrb_bconr_bit_t                     BCONR1_b;
    uint32_t                                 RESERVED8[48];
    stc_tmrb_bconr_bit_t                     BCONR2_b;
    uint32_t                                 RESERVED9[48];
    stc_tmrb_bconr_bit_t                     BCONR3_b;
    uint32_t                                 RESERVED10[368];
    stc_tmrb_cconr_bit_t                     CCONR1_b;
    uint32_t                                 RESERVED11[16];
    stc_tmrb_cconr_bit_t                     CCONR2_b;
    uint32_t                                 RESERVED12[16];
    stc_tmrb_cconr_bit_t                     CCONR3_b;
    uint32_t                                 RESERVED13[16];
    stc_tmrb_cconr_bit_t                     CCONR4_b;
    uint32_t                                 RESERVED14[400];
    stc_tmrb_pconr_bit_t                     PCONR1_b;
    uint32_t                                 RESERVED15[16];
    stc_tmrb_pconr_bit_t                     PCONR2_b;
    uint32_t                                 RESERVED16[16];
    stc_tmrb_pconr_bit_t                     PCONR3_b;
    uint32_t                                 RESERVED17[16];
    stc_tmrb_pconr_bit_t                     PCONR4_b;
} bCM_TMRB_TypeDef;

typedef struct
{
    stc_usart_sr_bit_t                       SR_b;
    stc_usart_dr_bit_t                       DR_b;
    uint32_t                                 RESERVED0[32];
    stc_usart_cr1_bit_t                      CR1_b;
    stc_usart_cr2_bit_t                      CR2_b;
    stc_usart_cr3_bit_t                      CR3_b;
    stc_usart_pr_bit_t                       PR_b;
} bCM_USART_TypeDef;

typedef struct
{
    stc_wdt_cr_bit_t                         CR_b;
    stc_wdt_sr_bit_t                         SR_b;
} bCM_WDT_TypeDef;



/******************************************************************************/
/*      Device Specific Peripheral bit_band declaration & memory map          */
/******************************************************************************/

#define bCM_ADC                              ((bCM_ADC_TypeDef *)0x42600000UL)
#define bCM_AOS                              ((bCM_AOS_TypeDef *)0x42210000UL)
#define bCM_CMP1                             ((bCM_CMP_TypeDef *)0x42940000UL)
#define bCM_CMP2                             ((bCM_CMP_TypeDef *)0x42940200UL)
#define bCM_CMP3                             ((bCM_CMP_TypeDef *)0x42940400UL)
#define bCM_CMU                              ((bCM_CMU_TypeDef *)0x42A88000UL)
#define bCM_CRC                              ((bCM_CRC_TypeDef *)0x42A08000UL)
#define bCM_CTC                              ((bCM_CTC_TypeDef *)0x42200000UL)
#define bCM_DAC                              ((bCM_DAC_TypeDef *)0x42942000UL)
#define bCM_DCU                              ((bCM_DCU_TypeDef *)0x42A40000UL)
#define bCM_DMA                              ((bCM_DMA_TypeDef *)0x42A60000UL)
#define bCM_EFM                              ((bCM_EFM_TypeDef *)0x42208000UL)
#define bCM_EMB0                             ((bCM_EMB_TypeDef *)0x422F8000UL)
#define bCM_EMB1                             ((bCM_EMB_TypeDef *)0x422F8400UL)
#define bCM_FCM                              ((bCM_FCM_TypeDef *)0x42908000UL)
#define bCM_GPIO                             ((bCM_GPIO_TypeDef *)0x42A70000UL)
#define bCM_I2C                              ((bCM_I2C_TypeDef *)0x429C0000UL)
#define bCM_INTC                             ((bCM_INTC_TypeDef *)0x42A20000UL)
#define bCM_PWC                              ((bCM_PWC_TypeDef *)0x42A80000UL)
#define bCM_RMU                              ((bCM_RMU_TypeDef *)0x42A82000UL)
#define bCM_SPI                              ((bCM_SPI_TypeDef *)0x42380000UL)
#define bCM_SWDT                             ((bCM_SWDT_TypeDef *)0x42928000UL)
#define bCM_TMR0_1                           ((bCM_TMR0_TypeDef *)0x42480000UL)
#define bCM_TMR0_2                           ((bCM_TMR0_TypeDef *)0x42488000UL)
#define bCM_TMR4                             ((bCM_TMR4_TypeDef *)0x422E0000UL)
#define bCM_TMRA_1                           ((bCM_TMRA_TypeDef *)0x422A0000UL)
#define bCM_TMRA_2                           ((bCM_TMRA_TypeDef *)0x422A8000UL)
#define bCM_TMRA_3                           ((bCM_TMRA_TypeDef *)0x422B0000UL)
#define bCM_TMRA_4                           ((bCM_TMRA_TypeDef *)0x422B8000UL)
#define bCM_TMRB                             ((bCM_TMRB_TypeDef *)0x424A0000UL)
#define bCM_USART1                           ((bCM_USART_TypeDef *)0x423A0000UL)
#define bCM_USART2                           ((bCM_USART_TypeDef *)0x423A8000UL)
#define bCM_USART3                           ((bCM_USART_TypeDef *)0x42420000UL)
#define bCM_USART4                           ((bCM_USART_TypeDef *)0x42428000UL)
#define bCM_WDT                              ((bCM_WDT_TypeDef *)0x42920000UL)


#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_H__ */

