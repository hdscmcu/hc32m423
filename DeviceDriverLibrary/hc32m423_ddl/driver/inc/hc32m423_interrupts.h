/**
 *******************************************************************************
 * @file  hc32m423_interrupts.h
 * @brief This file contains all the functions prototypes of the interrupt driver
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
#ifndef __HC32M423_INTERRUPTS_H__
#define __HC32M423_INTERRUPTS_H__

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
 * @addtogroup DDL_INTERRUPTS
 * @{
 */

#if (DDL_INTERRUPTS_ENABLE == DDL_ON) || (DDL_EXTINT_NMI_SWINT_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup INTC_Global_Types INTC Global Types
 * @{
 */
/**
 * @brief  Interrupt registration structure definition
 */
typedef struct
{
    en_int_src_t enIntSrc;      /*!< Peripheral interrupt number, can be any value @ref en_int_src_t */
    IRQn_Type    enIRQn;        /*!< Peripheral IRQ type, can be any value @ref IRQn_Type */
    func_ptr_t   pfnCallback;   /*!< Callback function for corresponding peripheral IRQ */
}stc_irq_signin_config_t;

/**
 * @brief  NMI initialize configuration structure definition
 */
typedef struct
{
    uint32_t   u32NmiFilterA;           /*!< NMI pin filter A function, @ref NMI_FilterAClock_Sel for details */
    uint32_t   u32NmiFilterAClockDiv;   /*!< NMI pin filter A clock  division, @ref NMI_FilterAClock_Div for details */
    uint32_t   u32NmiTrigger;           /*!< NMI pin trigger edge, @ref NMI_Trigger_Sel for details */
    uint32_t   u32NmiSrc;               /*!< NMI trigger source, @ref NMI_TriggerSrc_Sel for details */
    func_ptr_t pfnNmiCallback;          /*!< NMI Callback function pointers */
}stc_nmi_init_t;

/**
 * @brief  EXTINT initialize configuration structure definition
 */
typedef struct
{
    uint32_t u32ExtIntFilterA;      /*!< ExtInt filter clock, @ref EXTINT_FilterAClock_Sel for details */
    uint32_t u32ExtIntFilterAClock; /*!< ExtInt filter clock division, @ref EXTINT_FilterAClock_Div for details */
    uint32_t u32ExtIntLevel;        /*!< ExtInt trigger edge, @ref EXTINT_Trigger_Sel for details */
}stc_extint_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup INTC_Global_Macros INTC Global Macros
 * @{
 */
/**
 * @defgroup INTC_DefaultPriority_Sel Interrupt default priority level
 * Possible values are 0 (high priority) to 15 (low priority)
 * @{
 */
#define DDL_IRQ_PRI_DEFAULT         (15U)
/**
 * @}
 */

/**
 * @defgroup INTC_Priority_Sel Interrupt priority level 0 ~ 15
 * @{
 */
#define DDL_IRQ_PRI00               (0U)
#define DDL_IRQ_PRI01               (1U)
#define DDL_IRQ_PRI02               (2U)
#define DDL_IRQ_PRI03               (3U)
#define DDL_IRQ_PRI04               (4U)
#define DDL_IRQ_PRI05               (5U)
#define DDL_IRQ_PRI06               (6U)
#define DDL_IRQ_PRI07               (7U)
#define DDL_IRQ_PRI08               (8U)
#define DDL_IRQ_PRI09               (9U)
#define DDL_IRQ_PRI10               (10U)
#define DDL_IRQ_PRI11               (11U)
#define DDL_IRQ_PRI12               (12U)
#define DDL_IRQ_PRI13               (13U)
#define DDL_IRQ_PRI14               (14U)
#define DDL_IRQ_PRI15               (15U)
/**
 * @}
 */

/**
 * @defgroup NMI_FilterAClock_Sel NMI pin filter A selection
 * @{
 */
#define NMI_FILTER_A_OFF            (0UL)
#define NMI_FILTER_A_ON             (INTC_NMICR_NMIFEN)
/**
 * @}
 */

/**
 * @defgroup NMI_FilterBClock_Sel External interrupt filter B function selection
 * @{
 */
#define NMI_FILTER_B_OFF            (0UL)
#define NMI_FILTER_B_ON             (INTC_NMICR_NOCEN)
/**
 * @}
 */

/**
 * @defgroup NMI_FilterAClock_Div NMI pin filter A sampling clock division selection
 * @{
 */
#define NMI_FILTER_A_CLK_DIV1       (0UL)
#define NMI_FILTER_A_CLK_DIV8       (INTC_NMICR_NMIFCLK_0)
#define NMI_FILTER_A_CLK_DIV32      (INTC_NMICR_NMIFCLK_1)
#define NMI_FILTER_A_CLK_DIV64      (INTC_NMICR_NMIFCLK)
/**
 * @}
 */

/**
 * @defgroup NMI_Trigger_Sel NMI pin trigger method selection
 * @{
 */
#define NMI_TRIG_FALLING            (0UL)
#define NMI_TRIG_RISING             (INTC_NMICR_NMITRG)
/**
 * @}
 */

/**
 * @defgroup NMI_TriggerSrc_Sel NMI trigger source selection
 * @{
 */
#define NMI_SRC_NMI_PIN             (INTC_NMIER_NMIENR)
#define NMI_SRC_SWDT                (INTC_NMIER_SWDTENR)
#define NMI_SRC_LVD1                (INTC_NMIER_PVD1ENR)
#define NMI_SRC_LVD2                (INTC_NMIER_PVD2ENR)
#define NMI_SRC_XTAL_STOP           (INTC_NMIER_XTALSTPENR)
#define NMI_SRC_RAM_PARITY_ERR      (INTC_NMIER_REPENR)
#define NMI_SRC_WDT                 (INTC_NMIER_WDTENR)
#define NMI_SRC_ALL                 (NMI_SRC_NMI_PIN    | NMI_SRC_SWDT  |       \
                                    NMI_SRC_LVD1        | NMI_SRC_LVD2  |       \
                                    NMI_SRC_XTAL_STOP   | NMI_SRC_WDT   |       \
                                    NMI_SRC_RAM_PARITY_ERR)
#define NMI_SRC_MASK                NMI_SRC_ALL
/**
 * @}
 */

/**
 * @defgroup MNI_Register_Msk NMI register mask
 * @{
 */
#define INTC_NMICR_MASK     (INTC_NMICR_NMITRG | INTC_NMICR_NMIFCLK |           \
                             INTC_NMICR_NMIFEN | INTC_NMICR_NOCSEL  |           \
                             INTC_NMICR_NOCEN)

#define INTC_NMIER_MASK     (INTC_NMIER_NMIENR      | INTC_NMIER_SWDTENR    |   \
                             INTC_NMIER_PVD1ENR     | INTC_NMIER_PVD2ENR    |   \
                             INTC_NMIER_XTALSTPENR  | INTC_NMIER_REPENR     |   \
                             INTC_NMIER_WDTENR)

#define INTC_NMIFR_MASK     (INTC_NMIFR_NMIFR       | INTC_NMIFR_SWDTFR     |   \
                             INTC_NMIFR_PVD1FR      | INTC_NMIFR_PVD2FR     |   \
                             INTC_NMIFR_XTALSTPFR   | INTC_NMIFR_REPFR      |   \
                             INTC_NMIFR_WDTFR)

#define INTC_NMICFR_MASK    (INTC_NMICFR_NMICFR     | INTC_NMICFR_SWDTCFR   |   \
                             INTC_NMICFR_PVD1CFR    | INTC_NMICFR_PVD2CFR   |   \
                             INTC_NMICFR_XTALSTPCFR | INTC_NMICFR_REPCFR    |   \
                             INTC_NMICFR_WDTCFR)
/**
 * @}
 */

/**
 * @defgroup EXTINT_Channel_Sel External interrupt channel selection
 * @{
 */
#define EXTINT_CH00                 (1UL << 0U)
#define EXTINT_CH01                 (1UL << 1U)
#define EXTINT_CH02                 (1UL << 2U)
#define EXTINT_CH03                 (1UL << 3U)
#define EXTINT_CH04                 (1UL << 4U)
#define EXTINT_CH05                 (1UL << 5U)
#define EXTINT_CH06                 (1UL << 6U)
#define EXTINT_CH07                 (1UL << 7U)
#define EXTINT_CH_MASK              (EXTINT_CH00 | EXTINT_CH01 |                \
                                     EXTINT_CH02 | EXTINT_CH03 |                \
                                     EXTINT_CH04 | EXTINT_CH05 |                \
                                     EXTINT_CH06 | EXTINT_CH07)
/**
 * @}
 */

/**
 * @defgroup EXTINT_FilterAClock_Sel External interrupt filter A function selection
 * @{
 */
#define EXTINT_FILTER_A_OFF         (0UL)
#define EXTINT_FILTER_A_ON          (INTC_EIRQCR_EFEN)
/**
 * @}
 */

/**
 * @defgroup EXTINT_FilterBClock_Sel External interrupt filter B function selection
 * @{
 */
#define EXTINT_FILTER_B_OFF         (0UL)
#define EXTINT_FILTER_B_ON          (INTC_EIRQCR_NOCEN)
/**
 * @}
 */

/**
 * @defgroup EXTINT_FilterAClock_Div External interrupt filter A sampling clock division selection
 * @{
 */
#define EXTINT_FILTER_A_CLK_DIV1    (0UL)
#define EXTINT_FILTER_A_CLK_DIV8    (INTC_EIRQCR_EISMPCLK_0)
#define EXTINT_FILTER_A_CLK_DIV32   (INTC_EIRQCR_EISMPCLK_1)
#define EXTINT_FILTER_A_CLK_DIV64   (INTC_EIRQCR_EISMPCLK)
/**
 * @}
 */

/**
 * @defgroup NMI_EXTINT_FilterBTim_Sel NMI/External pin interrupt filter B time selection
 * @{
 */
#define NMI_EXTINT_FILTER_B_500NS   (0UL)
#define NMI_EXTINT_FILTER_B_1US     (INTC_NMICR_NOCSEL_0)
#define NMI_EXTINT_FILTER_B_2US     (INTC_NMICR_NOCSEL_1)
#define NMI_EXTINT_FILTER_B_4US     (INTC_NMICR_NOCSEL)
/**
 * @}
 */

/**
 * @defgroup EXTINT_Trigger_Sel External interrupt trigger edge selection
 * @{
 */
#define EXTINT_TRIG_FALLING         (0UL)
#define EXTINT_TRIG_RISING          (INTC_EIRQCR_EIRQTRG_0)
#define EXTINT_TRIG_BOTH            (INTC_EIRQCR_EIRQTRG_1)
#define EXTINT_TRIG_LOW             (INTC_EIRQCR_EIRQTRG)
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
 * @addtogroup INTC_Global_Functions
 * @{
 */

/**
 * @brief  AOS software trigger.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void AOS_SW_Trigger(void)
{
    WRITE_REG32(bCM_AOS->INTC_STRGCR_b.STRG, Set);
}

en_result_t INTC_IrqSignIn(const stc_irq_signin_config_t *pstcIrqSignConfig);
en_result_t INTC_IrqSignOut(IRQn_Type enIRQn);
void INTC_WakeupSrcCmd(uint32_t u32Src, en_functional_state_t enNewState);
void INTC_EventCmd(uint32_t u32Event, en_functional_state_t enNewState);
void INTC_IntCmd(uint32_t u32Int, en_functional_state_t enNewState);
void INTC_SWIntCmd(uint32_t u32SWInt, en_functional_state_t enNewState);

en_result_t NMI_Init(const stc_nmi_init_t *pstcNmiInit);
en_result_t NMI_StructInit(stc_nmi_init_t *pstcNmiInit);
en_flag_status_t NMI_GetNmiStatus(uint32_t u32Flag);
void NMI_ClearNmiStatus(uint32_t u32Flag);
void NMI_FilterBCmd(en_functional_state_t enNewState);

en_result_t EXTINT_Init(uint32_t u32Ch, const stc_extint_init_t *pstcExtIntInit);
en_result_t EXTINT_StructInit(stc_extint_init_t *pstcExtIntInit);
en_flag_status_t EXTINT_GetExtIntStatus(uint32_t u32Ch);
void EXTINT_ClearExtIntStatus(uint32_t u32Ch);
void EXTINT_FilterBCmd(uint32_t u32Ch, en_functional_state_t enNewState);

void NMI_EXTINT_SetFilterBClockTime(uint32_t u32Time);

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void IRQ000_Handler(void);
void IRQ001_Handler(void);
void IRQ002_Handler(void);
void IRQ003_Handler(void);
void IRQ004_Handler(void);
void IRQ005_Handler(void);
void IRQ006_Handler(void);
void IRQ007_Handler(void);
void IRQ008_Handler(void);
void IRQ009_Handler(void);
void IRQ010_Handler(void);
void IRQ011_Handler(void);
void IRQ012_Handler(void);
void IRQ013_Handler(void);
void IRQ014_Handler(void);
void IRQ015_Handler(void);
void IRQ016_Handler(void);
void IRQ017_Handler(void);
void IRQ018_Handler(void);
void IRQ019_Handler(void);
void IRQ020_Handler(void);
void IRQ021_Handler(void);
void IRQ022_Handler(void);
void IRQ023_Handler(void);
void IRQ024_Handler(void);
void IRQ025_Handler(void);
void IRQ026_Handler(void);
void IRQ027_Handler(void);
void IRQ028_Handler(void);
void IRQ029_Handler(void);
void IRQ030_Handler(void);
void IRQ031_Handler(void);
void IRQ032_Handler(void);
void IRQ033_Handler(void);
void IRQ034_Handler(void);
void IRQ035_Handler(void);
void IRQ036_Handler(void);
void IRQ037_Handler(void);
void IRQ038_Handler(void);
void IRQ039_Handler(void);
void IRQ040_Handler(void);
void IRQ041_Handler(void);
void IRQ042_Handler(void);
void IRQ043_Handler(void);
void IRQ044_Handler(void);
void IRQ045_Handler(void);
void IRQ046_Handler(void);
void IRQ047_Handler(void);
void IRQ048_Handler(void);
void IRQ049_Handler(void);
void IRQ050_Handler(void);
void IRQ051_Handler(void);
void IRQ052_Handler(void);
void IRQ053_Handler(void);
void IRQ054_Handler(void);
void IRQ055_Handler(void);
void IRQ056_Handler(void);
void IRQ057_Handler(void);
void IRQ058_Handler(void);
void IRQ059_Handler(void);
void IRQ060_Handler(void);
void IRQ061_Handler(void);
void IRQ062_Handler(void);
void IRQ063_Handler(void);
void IRQ064_Handler(void);
void IRQ065_Handler(void);
void IRQ066_Handler(void);
void IRQ067_Handler(void);
void IRQ068_Handler(void);
void IRQ069_Handler(void);
void IRQ070_Handler(void);
void IRQ071_Handler(void);
void IRQ072_Handler(void);
void IRQ073_Handler(void);
void IRQ074_Handler(void);
void IRQ075_Handler(void);
void IRQ076_Handler(void);
void IRQ077_Handler(void);
void IRQ078_Handler(void);
void IRQ079_Handler(void);
void IRQ080_Handler(void);
void IRQ081_Handler(void);
void IRQ082_Handler(void);
void IRQ083_Handler(void);
void IRQ084_Handler(void);
void IRQ085_Handler(void);
void IRQ086_Handler(void);
void IRQ087_Handler(void);
void IRQ088_Handler(void);
void IRQ089_Handler(void);
void IRQ090_Handler(void);
void IRQ091_Handler(void);
void IRQ092_Handler(void);
void IRQ093_Handler(void);
void IRQ094_Handler(void);
void IRQ095_Handler(void);
void IRQ096_Handler(void);
void IRQ097_Handler(void);
void IRQ098_Handler(void);
void IRQ099_Handler(void);
void IRQ100_Handler(void);

void NMI_IrqHandler(void);
void HardFault_IrqHandler(void);
void MemManage_IrqHandler(void);
void BusFault_IrqHandler(void);
void UsageFault_IrqHandler(void);
void SVC_IrqHandler(void);
void DebugMon_IrqHandler(void);
void PendSV_IrqHandler(void);
void SysTick_IrqHandler(void);
void ExtInt00_SWInt08_IrqHandler(void);
void ExtInt01_SWInt09_IrqHandler(void);
void ExtInt02_SWInt10_IrqHandler(void);
void ExtInt03_SWInt11_IrqHandler(void);
void ExtInt04_SWInt12_IrqHandler(void);
void ExtInt05_SWInt13_IrqHandler(void);
void ExtInt06_SWInt14_IrqHandler(void);
void ExtInt07_SWInt15_IrqHandler(void);
void DMA_TC0_IrqHandler(void);
void DMA_TC1_IrqHandler(void);
void DMA_TC2_IrqHandler(void);
void DMA_TC3_IrqHandler(void);
void DMA_BTC0_IrqHandler(void);
void DMA_BTC1_IrqHandler(void);
void DMA_BTC2_IrqHandler(void);
void DMA_BTC3_IrqHandler(void);
void DMA_Error_IrqHandler(void);
void EFM_ProgramEraseError_IrqHandler(void);
void EFM_ColError_IrqHandler(void);
void EFM_OpEnd_IrqHandler(void);
void DCU_IrqHandler(void);
void TMR0_1_CmpA_IrqHandler(void);
void TMR0_1_CmpB_IrqHandler(void);
void TMR0_2_CmpA_IrqHandler(void);
void TMR0_2_CmpB_IrqHandler(void);
void CLK_XtalStop_IrqHandler(void);
void SWDT_IrqHandler(void);
void TMRA_1_Ovf_IrqHandler(void);
void TMRA_1_Udf_IrqHandler(void);
void TMRA_1_Cmp_IrqHandler(void);
void TMRA_2_Ovf_IrqHandler(void);
void TMRA_2_Udf_IrqHandler(void);
void TMRA_2_Cmp_IrqHandler(void);
void TMRA_3_Ovf_IrqHandler(void);
void TMRA_3_Udf_IrqHandler(void);
void TMRA_3_Cmp_IrqHandler(void);
void TMRA_4_Ovf_IrqHandler(void);
void TMRA_4_Udf_IrqHandler(void);
void TMRA_4_Cmp_IrqHandler(void);
void TMRB_Ovf_IrqHandler(void);
void TMRB_Udf_IrqHandler(void);
void TMRB_Cmp_IrqHandler(void);
void USART1_RxError_IrqHandler(void);
void USART1_RxEnd_IrqHandler(void);
void USART1_TxEmpty_IrqHandler(void);
void USART1_TxEnd_IrqHandler(void);
void USART2_RxError_IrqHandler(void);
void USART2_RxEnd_IrqHandler(void);
void USART2_TxEmpty_IrqHandler(void);
void USART2_TxEnd_IrqHandler(void);
void USART3_RxError_IrqHandler(void);
void USART3_RxEnd_IrqHandler(void);
void USART3_TxEmpty_IrqHandler(void);
void USART3_TxEnd_IrqHandler(void);
void USART4_RxError_IrqHandler(void);
void USART4_RxEnd_IrqHandler(void);
void USART4_TxEmpty_IrqHandler(void);
void USART4_TxEnd_IrqHandler(void);
void SPI_RxEnd_IrqHandler(void);
void SPI_TxEmpty_IrqHandler(void);
void SPI_Idle_IrqHandler(void);
void SPI_Error_IrqHandler(void);
void TMR4_GCmpUH_IrqHandler(void);
void TMR4_GCmpUL_IrqHandler(void);
void TMR4_GCmpVH_IrqHandler(void);
void TMR4_GCmpVL_IrqHandler(void);
void TMR4_GCmpWH_IrqHandler(void);
void TMR4_GCmpWL_IrqHandler(void);
void TMR4_Ovf_IrqHandler(void);
void TMR4_Udf_IrqHandler(void);
void TMR4_ReloadU_IrqHandler(void);
void TMR4_ReloadV_IrqHandler(void);
void TMR4_ReloadW_IrqHandler(void);
void EMB_IrqHandler(void);
void CMP1_IrqHandler(void);
void CMP2_IrqHandler(void);
void CMP3_IrqHandler(void);
void I2C_RxEnd_IrqHandler(void);
void I2C_TxEmpty_IrqHandler(void);
void I2C_TxEnd_IrqHandler(void);
void I2C_Error_IrqHandler(void);
void USART1_WKUP_IrqHandler(void);
void PWC_LVD1_IrqHandler(void);
void PWC_LVD2_IrqHandler(void);
void FCM_Error_IrqHandler(void);
void FCM_End_IrqHandler(void);
void FCM_Ovf_IrqHandler(void);
void WDT_IrqHandler(void);
void CTC_IrqHandler(void);
void ADC_SeqA_IrqHandler(void);
void ADC_SeqB_IrqHandler(void);
void ADC_ChCmp_IrqHandler(void);
void ADC_SeqCmp_IrqHandler(void);

/**
 * @}
 */

#endif /* DDL_INTERRUPTS_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_INTERRUPTS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
