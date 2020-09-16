/**
 *******************************************************************************
 * @file  hc32m423_clk.h
 * @brief This file contains all the functions prototypes of the CLK driver
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
#ifndef __HC32M423_CLK_H__
#define __HC32M423_CLK_H__

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
 * @addtogroup DDL_CLK
 * @{
 */

#if (DDL_CLK_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CLK_Global_Types CLK Global Types
 * @{
 */
/**
 * @brief  CLK Xtal configuration structure definition
 */
typedef struct
{
    uint8_t u8XtalState;      /*!< The new state of the Xtal.
                                This parameter can be a value of @ref CLK_Xtal_Func_Switch */

    uint8_t u8XtalDrv;        /*!< The Xtal drive ability.
                                This parameter can be a value of @ref CLK_Xtal_Drv */

    uint8_t u8XtalMode;       /*!< The Xtal mode selection osc or extclk.
                                This parameter can be a value of @ref CLK_Xtal_Mode */

    uint8_t u8XtalSupSpeedDrv;/*!< The Xtal super speed drive on or off.
                                This parameter can be a value of @ref CLK_Xtal_SuperSpeed_Drv */

    uint8_t u8XtalStb;        /*!< The Xtal stable time selection.
                                This parameter can be a value of @ref CLK_Xtal_Stable_Time */
} stc_clock_xtal_init_t;


/**
 * @brief  CLK XTALSTD configuration structure definition
 */
typedef struct
{
    uint8_t u8XtalStdState;   /*!< Specifies the new state of XTALSTD.
                                This parameter can be a value of @ref CLK_XTALSTD_Switch */

    uint8_t u8XtalStdExceptionType;  /*!< Specifies the XTALSTD exception type.
                                       This parameter can be a value of @ref CLK_XTALSTD_Exception_type */

    uint8_t u8XtalStdInt;     /*!< Specifies the XTALSTD interrupt on or off.
                                This parameter can be a value of @ref CLK_XTALSTD_Irq_Switch */

    uint8_t u8XtalStdRst;     /*!< Specifies the XTALSTD reset on or off.
                                This parameter can be a value of @ref CLK_XTALSTD_Reset_Switch */
} stc_clock_xtalstd_init_t;

/**
 * @brief  CLK PLL configuration structure definition
 */
typedef struct
{
    uint8_t u8PLLState;         /*!< PLL new state,
                                    @ref CLK_PLL_Stat for details */
    union
    {
        uint32_t PLLCFGR;       /*!< PLL config register */
        struct
        {
            uint32_t PLLM   :3; /*!< PLL M divide */
            uint32_t resvd0 :4; /*!< reserved */
            uint32_t PLLSRC :1; /*!< PLL source clock select */
            uint32_t PLLN   :6; /*!< PLL N multi- */
            uint32_t resvd1 :14;/*!< reserved */
            uint32_t PLLP   :2; /*!< PLL P divide */
        } PLLCFGR_f;
    };
} stc_clock_pll_init_t;

/**
 * @brief  Clock frequency structure.
 */
typedef struct
{
    uint32_t u32SysclkFreq;        /*!< System clock frequency. */
    uint32_t u32HclkFreq;          /*!< Hclk frequency.  */
    uint32_t u32Pclk1Freq;         /*!< Pclk1 frequency. */
    uint32_t u32Pclk4Freq;         /*!< Pclk4 frequency. */
} stc_clock_freq_t;

/**
 * @brief  Clock PLL clock frequency structure definition
 */
typedef struct
{
    uint32_t pllvcin;              /*!< pll vcin clock frequency. */
    uint32_t pllvco;               /*!< pll vco clock frequency. */
    uint32_t pllp;                 /*!< pllp clock frequency. */
} stc_pll_clock_freq_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CLK_Global_Macros CLK Global Macros
 * @{
 */

#define EFM_HRCCFGR_HRCFREQS_012    (EFM_HRCCFGR_HRCFREQS_0 | EFM_HRCCFGR_HRCFREQS_1 | EFM_HRCCFGR_HRCFREQS_2)

/**
 * @defgroup CLK_Xtal_Func_Switch Xtal function switch
 * @{
 */
#define CLK_XTAL_OFF                (CMU_XTALCR_XTALSTP)
#define CLK_XTAL_ON                 (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_Xtal_Mode Xtal Mode
 * @{
 */
#define CLK_XTAL_MD_OSC             (0x00U)
#define CLK_XTAL_MD_EXT_CLK         (CMU_XTALCFGR_XTALMS)
/**
 * @}
 */

/**
 * @defgroup CLK_Xtal_Drv Xtal driver ability
 * @brief High suggest OSC 20MHz, Mid bettween 10~20MHz, Low bettween 4~10MHz, ULow 4MHz.
 * @{
 */
#define CLK_XTAL_DRV_HIGH           (0x00U)
#define CLK_XTAL_DRV_MID            (CMU_XTALCFGR_XTALDRV_0)
#define CLK_XTAL_DRV_LOW            (CMU_XTALCFGR_XTALDRV_1)
#define CLK_XTAL_DRV_ULOW           (CMU_XTALCFGR_XTALDRV)
/**
 * @}
 */

/**
 * @defgroup CLK_Xtal_SuperSpeed_Drv Xtal Super speed driver mode
 * @{
 */
#define CLK_XTAL_SUPSPEEDDRV_ON     (CMU_XTALCFGR_SUPDRV)
#define CLK_XTAL_SUPSPEEDDRV_OFF    (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_Xtal_Stable_Time Xtal stable time selection
 * @{
 */
#define CLK_XTALSTB_2POW8           (0x00U)       /*!< 2^8 * Xtal cycle.  */
#define CLK_XTALSTB_2POW9           (0x01U)       /*!< 2^9 * Xtal cycle.  */
#define CLK_XTALSTB_2POW10          (0x02U)       /*!< 2^10 * Xtal cycle. */
#define CLK_XTALSTB_2POW11          (0x03U)       /*!< 2^11 * Xtal cycle. */
#define CLK_XTALSTB_2POW13          (0x04U)       /*!< 2^13 * Xtal cycle. */
#define CLK_XTALSTB_2POW15          (0x05U)       /*!< 2^15 * Xtal cycle. */
#define CLK_XTALSTB_2POW16          (0x06U)       /*!< 2^16 * Xtal cycle. */
#define CLK_XTALSTB_2POW17          (0x07U)       /*!< 2^17 * Xtal cycle. */
/**
 * @}
 */

/**
 * @defgroup CLK_STB_Flag CLK stable Flag
 * @{
 */
#define CLK_STB_FLAG_HRCSTB         (CMU_OSCSTBSR_HRCSTBF)
#define CLK_STB_FLAG_XTALSTB        (CMU_OSCSTBSR_XTALSTBF)
#define CLK_STB_FLAG_PLLSTB         (CMU_OSCSTBSR_PLLSTBF)
#define CLK_STB_FLAG_MASK           (CMU_OSCSTBSR_HRCSTBF |                    \
                                     CMU_OSCSTBSR_XTALSTBF |                   \
                                     CMU_OSCSTBSR_PLLSTBF)
/**
 * @}
 */

/**
 * @defgroup CLK_PLL_Stat CLK PLL status
 * @{
 */
#define CLK_PLL_OFF                 (CMU_PLLCR_PLLOFF)
#define CLK_PLL_ON                  (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_PLL_Clock_Src CLK PLL Clock Source
 * @{
 */
#define CLK_PLLSRC_HRC              (0x01UL)
#define CLK_PLLSRC_XTAL             (0x00UL)
/**
 * @}
 */

/**
 * @defgroup CLK_CATE_Sel Clock category selection
 * @{
 */
#define CLK_CATE_PCLK1              (0x01U)
#define CLK_CATE_PCLK4              (0x02U)
#define CLK_CATE_HCLK               (0x04U)
#define CLK_CATE_ALL                (CLK_CATE_PCLK1 | CLK_CATE_PCLK4 |         \
                                     CLK_CATE_HCLK)
/**
 * @}
 */

/**
 * @defgroup CLK_Hclk_Div Hclk divider
 * @{
 */
#define CLK_HCLK_DIV1               (0x00U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV2               (0x01U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV4               (0x02U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV8               (0x03U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV16              (0x04U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV32              (0x05U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV64              (0x06U << CMU_SCFGR_HCLKS_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_Pclk1_Div Pclk1 divider
 * @{
 */
#define CLK_PCLK1_DIV1              (0x00U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV2              (0x01U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV4              (0x02U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV8              (0x03U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV16             (0x04U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV32             (0x05U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV64             (0x06U << CMU_SCFGR_PCLK1S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_Pclk4_Div Pclk4 divider
 * @{
 */
#define CLK_PCLK4_DIV1              (0x00U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV2              (0x01U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV4              (0x02U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV8              (0x03U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV16             (0x04U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV32             (0x05U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV64             (0x06U << CMU_SCFGR_PCLK4S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_TPIU_Div TPIU clock divider
 * @{
 */
#define CLK_TPIU_CLK_DIV1           (0x00U)
#define CLK_TPIU_CLK_DIV2           (CMU_TPIUCKCFGR_TPIUCKS_0)
#define CLK_TPIU_CLK_DIV4           (CMU_TPIUCKCFGR_TPIUCKS_1)
/**
 * @}
 */

/**
 * @defgroup CLK_MCO_Clock_Src CLK MCO Clock Source
 * @{
 */
#define CLK_MCO_SRC_HRC             (0x00U)
#define CLK_MCO_SRC_MRC             (0x01U)
#define CLK_MCO_SRC_LRC             (0x02U)
#define CLK_MCO_SRC_XTAL            (0x03U)
#define CLK_MCO_SRC_PLLP            (0x05U)
#define CLK_MCO_SRC_HCLK            (0x06U)
#define CLK_MCO_SRC_SWDT            (0x07U)
/**
 * @}
 */

/**
 * @defgroup CLK_MCO_Clock_Prescaler CLK MCO Clock Prescaler
 * @{
 */
#define CLK_MCO_DIV1                (0x00U)
#define CLK_MCO_DIV2                (0x10U)
#define CLK_MCO_DIV4                (0x20U)
#define CLK_MCO_DIV8                (0x30U)
#define CLK_MCO_DIV16               (0x40U)
#define CLK_MCO_DIV32               (0x50U)
#define CLK_MCO_DIV64               (0x60U)
#define CLK_MCO_DIV128              (0x70U)
/**
 * @}
 */

/**
 * @defgroup CLK_Hrc_Freq_Sel Hrc Frequency select
 * @{
 */
#define CLK_HRC_64M                 (0x00U)   /*!< ICG.HRCFREQS[3] = 0. */
#define CLK_HRC_32M                 (0x01U)   /*!< ICG.HRCFREQS[3] = 0. */
#define CLK_HRC_16M                 (0x02U)   /*!< ICG.HRCFREQS[3] = 0. */
#define CLK_HRC_8M                  (0x03U)   /*!< ICG.HRCFREQS[3] = 0. */
#define CLK_HRC_4M                  (0x04U)   /*!< ICG.HRCFREQS[3] = 0. */
#define CLK_HRC_2M                  (0x05U)   /*!< ICG.HRCFREQS[3] = 0. */

#define CLK_HRC_48M                 (0x00U & EFM_HRCCFGR_HRCFREQS_3)   /*!< ICG.HRCFREQS[3] = 1. */
#define CLK_HRC_24M                 (0x01U & EFM_HRCCFGR_HRCFREQS_3)   /*!< ICG.HRCFREQS[3] = 1. */
#define CLK_HRC_12M                 (0x02U & EFM_HRCCFGR_HRCFREQS_3)   /*!< ICG.HRCFREQS[3] = 1. */
#define CLK_HRC_6M                  (0x03U & EFM_HRCCFGR_HRCFREQS_3)   /*!< ICG.HRCFREQS[3] = 1. */
#define CLK_HRC_3M                  (0x04U & EFM_HRCCFGR_HRCFREQS_3)   /*!< ICG.HRCFREQS[3] = 1. */
#define CLK_HRC_1P5M                (0x05U & EFM_HRCCFGR_HRCFREQS_3)   /*!< ICG.HRCFREQS[3] = 1. */
/**
 * @}
 */

/**
 * @defgroup CLK_ADCCLK_Div ADC clock divider
 * @{
 */
#define CLK_ADCCLK_PCLK4_DIV1       (0x00U)
#define CLK_ADCCLK_PCLK4_DIV2       (0x01U)
#define CLK_ADCCLK_PCLK4_DIV3       (0x02U)
#define CLK_ADCCLK_PCLK4_DIV4       (0x03U)
#define CLK_ADCCLK_PCLK4_DIV5       (0x04U)
#define CLK_ADCCLK_PCLK4_DIV6       (0x05U)
#define CLK_ADCCLK_PCLK4_DIV7       (0x06U)
#define CLK_ADCCLK_PCLK4_DIV8       (0x07U)
/**
 * @}
 */

/**
 * @defgroup CLK_FCG_Periph_Control CLK FCG Peripheral function control
 * @{
 */
#define CLK_FCG_ADC                 (CMU_FCG_ADC)
#define CLK_FCG_CTC                 (CMU_FCG_CTC)
#define CLK_FCG_CMP                 (CMU_FCG_CMP)
#define CLK_FCG_AOS                 (CMU_FCG_AOS)
#define CLK_FCG_DMA                 (CMU_FCG_DMA)
#define CLK_FCG_CRC                 (CMU_FCG_CRC)
#define CLK_FCG_TMRA_1              (CMU_FCG_TMRA_1)
#define CLK_FCG_TMRA_2              (CMU_FCG_TMRA_2)
#define CLK_FCG_TMRA_3              (CMU_FCG_TMRA_3)
#define CLK_FCG_TMRA_4              (CMU_FCG_TMRA_4)
#define CLK_FCG_TMR0_1              (CMU_FCG_TMR0_1)
#define CLK_FCG_TMR0_2              (CMU_FCG_TMR0_2)
#define CLK_FCG_TMR4                (CMU_FCG_TMR4)
#define CLK_FCG_TMRB                (CMU_FCG_TMRB)
#define CLK_FCG_EMB                 (CMU_FCG_EMB)
#define CLK_FCG_FCM                 (CMU_FCG_FCM)
#define CLK_FCG_DCU                 (CMU_FCG_DCU)
#define CLK_FCG_UART1               (CMU_FCG_USART1)
#define CLK_FCG_UART2               (CMU_FCG_USART2)
#define CLK_FCG_UART3               (CMU_FCG_USART3)
#define CLK_FCG_UART4               (CMU_FCG_USART4)
#define CLK_FCG_IIC                 (CMU_FCG_IIC)
#define CLK_FCG_SPI                 (CMU_FCG_SPI)
/**
 * @}
 */

/**
 * @defgroup CLK_XTALSTD_Switch XTALSTD trouble detection on or off
 * @{
 */
#define CLK_XTALSTD_OFF             (0x00U)
#define CLK_XTALSTD_ON              (CMU_XTALSTDCR_XTALSTDE)
/**
 * @}
 */

/**
 * @defgroup CLK_XTALSTD_Exception_type XTALSTD exception type
 * @{
 */
#define CLK_XTALSTD_EXP_TYPE_RST    (CMU_XTALSTDCR_XTALSTDRIS)
#define CLK_XTALSTD_EXP_TYPE_INT    (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_XTALSTD_Reset_Switch XTALSTD reset on or off
 * @{
 */
#define CLK_XTALSTD_RST_OFF         (0x00U)
#define CLK_XTALSTD_RST_ON          (CMU_XTALSTDCR_XTALSTDRE)
/**
 * @}
 */

/**
 * @defgroup CLK_XTALSTD_Irq_Switch XTALSTD interrupt on or off
 * @{
 */
#define CLK_XTALSTD_INT_OFF         (0x00U)
#define CLK_XTALSTD_INT_ON          (CMU_XTALSTDCR_XTALSTDIE)
/**
 * @}
 */

/**
 * @defgroup CLK_Hrc_Config Hrc Config
 * @{
 */
#define CLK_HRC_OFF                 (CMU_HRCCR_HRCSTP)
#define CLK_HRC_ON                  (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_Mrc_Config Hrc Config
 * @{
 */
#define CLK_MRC_OFF                 (CMU_MRCCR_MRCSTP)
#define CLK_MRC_ON                  (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_Lrc_Config Lrc Config
 * @{
 */
#define CLK_LRC_OFF                 (CMU_LRCCR_LRCSTP)
#define CLK_LRC_ON                  (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_System_Clock_Src System Clock Source
 * @{
 */
#define CLK_SYSCLK_SRC_HRC          (0x00U)
#define CLK_SYSCLK_SRC_MRC          (0x01U)
#define CLK_SYSCLK_SRC_LRC          (0x02U)
#define CLK_SYSCLK_SRC_XTAL         (0x03U)
#define CLK_SYSCLK_SRC_PLL          (0x05U)
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
 * @addtogroup CLK_Global_Functions
 * @{
 */

void CLK_DeInit(void);

en_result_t CLK_XtalStdStructInit(stc_clock_xtalstd_init_t* pstcXtalStdInit);
en_result_t CLK_XtalStdInit(const stc_clock_xtalstd_init_t* pstcXtalStdInit);
void CLK_ClearXtalStdStatus(void);
en_flag_status_t CLK_GetXtalStdStatus(void);

en_result_t CLK_XtalCmd(en_functional_state_t enNewState);
en_result_t CLK_HrcCmd(en_functional_state_t enNewState);
en_result_t CLK_MrcCmd(en_functional_state_t enNewState);
en_result_t CLK_LrcCmd(en_functional_state_t enNewState);
en_result_t CLK_PLLCmd(en_functional_state_t enNewState);

en_result_t CLK_PLLStructInit(stc_clock_pll_init_t* pstcPLLInit);
en_result_t CLK_PLLInit(const stc_clock_pll_init_t *pstcPLLInit);
void CLK_SetPLLSrc(uint32_t u32PllSrc);

en_result_t CLK_XtalStructInit(stc_clock_xtal_init_t* pstcXtalInit);
en_result_t CLK_XtalInit(const stc_clock_xtal_init_t *pstcXtalInit);

en_flag_status_t CLK_GetStableStatus(uint8_t u8StableFlag);

void CLK_SetSysclkSrc(uint8_t u8Src);
void CLK_ClockDiv(uint8_t u8ClockCate, uint32_t u32Div);

void CLK_TpiuClockCmd(en_functional_state_t enNewState);
void CLK_TpiuClockConfig(uint8_t u8TpiuDiv);

void CLK_MCOConfig(uint8_t u8MCOSrc, uint8_t u8MCODiv);
void CLK_MCOCmd(en_functional_state_t enNewState);

en_result_t CLK_GetClockFreq(stc_clock_freq_t *pstcClockFreq);
en_result_t CLK_GetPLLClockFreq(stc_pll_clock_freq_t *pstcPLLClockFreq);

en_result_t CLK_HrcFreqConfig(uint8_t u8HrcFreq);

void CLK_SetADCClockDiv(uint8_t u8ADCClkDiv);

void CLK_FcgPeriphClockCmd(uint32_t u32FcgPeriph, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* DDL_CLK_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_CLK_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
