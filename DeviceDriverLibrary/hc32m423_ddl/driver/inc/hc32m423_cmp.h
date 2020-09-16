/**
 *******************************************************************************
 * @file  hc32m423_cmp.h
 * @brief Head file for CMP module.
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
#ifndef __HC32M423_CMP_H__
#define __HC32M423_CMP_H__

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
 * @addtogroup DDL_CMP
 * @{
 */

#if (DDL_CMP_ENABLE == DDL_ON)
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CMP_Global_Types CMP Global Types
 * @{
 */

/**
 * @brief CMP configuration structure
 */
typedef struct
{
    uint8_t u8CompareVoltage;      /*!< Compare voltage for normal mode
                                        @ref CMP_Compare_Voltage */
    uint8_t u8RefVoltage;          /*!< Reference voltage for normal mode ,
                                        @ref CMP_Ref_Voltage*/

    uint8_t u8WinVoltageLow;       /*!< CMP reference low voltage for window mode
                                        @ref CMP_Ref_Voltage */
    uint8_t u8WinVoltageHigh;      /*!< CMP reference high voltage for window mode
                                        @ref CMP_Ref_Voltage */

    uint8_t u8OutPolarity;         /*!< Output polarity select, @ref CMP_Out_Polarity */
    uint8_t u8OutDetectEdges;      /*!< Output detect edge, @ref CMP_Out_Detect_Edge */
    uint8_t u8OutFilter;           /*!< Output Filter, @ref CMP_Out_Filter */
}stc_cmp_init_t;

//time u8TWInvalidLevel
/**
 * @brief CMP timer windows function configuration structure
 */
typedef struct
{
    uint8_t u8TimerWinSignal;       /*!< Timer window control signal select, @ref CMP_Timer_Win_Signal */
    uint8_t u8TimerWinValidLevel;   /*!< Timer window mode output level @ref CMP_Timer_Win_Signal_Valid_Level*/
    uint8_t u8TWInvalidLevel;       /*!< Output level when timer window invalid, @ref CMP_Timer_Win_Invalid_Out */
}stc_cmp_timerwindows_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup CMP_Global_Macros CMP Global Macros
 * @{
 */

/**
 * @defgroup CMP_Mode CMP compare mode
 * @{
 */
#define CMP_MD_NORMAL               (0U)
#define CMP_MD_WIN                  (CMP_MDR_CWDE)
/**
 * @}
 */

/**
 * @defgroup CMP_Compare_Voltage CMP compare voltage selection
 * @{
 */
/* No compare voltage input */
#define CMP_CMP_VOLT_NONE           (0U)
/* Select pin IVCMPx_0 as compare voltage for CMPx */
#define CMP_CMP_VOLT_IVCMPx_0       (CMP_VSR_CVSL_0)
/* Select pin IVCMPx_1 as compare voltage for CMPx */
#define CMP_CMP_VOLT_IVCMPx_1       (CMP_VSR_CVSL_1)
/* Select pin IVCMPx_2 as compare voltage for CMPx */
#define CMP_CMP_VOLT_IVCMPx_2       (CMP_VSR_CVSL_2)
/* Select Vref as compare voltage */
#define CMP_CMP_VOLT_VREF           (CMP_VSR_CVSL_3)
/**
 * @}
 */

/**
 * @defgroup CMP_Ref_Voltage CMP reference voltage selection
 * @{
 */
/* No reference voltage input */
#define CMP_REF_VOLT_NONE           (0U)
/* Select pin IVREF1 as reference voltage */
#define CMP_REF_VOLT_IVREF1         (CMP_VSR_RVSL_0)
/* Select pin IVREF2 as reference voltage for CMP1 and CMP2 */
#define CMP_REF_VOLT_IVREF2         (CMP_VSR_RVSL_1)
/* Select 8 bit DAC as reference voltage */
#define CMP_REF_VOLT_DAC            (CMP_VSR_RVSL_2)
/**
 * @}
 */

/**
 * @defgroup CMP_Out_Polarity CMP output polarity
 * @{
 */
/* CMP output don't reverse */
#define CMP_OUT_POLARITY_NORMAL     (0U)
/* CMP output level reverse */
#define CMP_OUT_POLARITY_REVS       (CMP_OCR_COPS)
/**
 * @}
 */

/**
 * @defgroup CMP_Out_Detect_Edge CMP output detect edge
 * @{
 */
#define CMP_DETECT_EDGE_NONE        (0U)
#define CMP_DETECT_EDGE_RISING      (CMP_FIR_EDGS_0)
#define CMP_DETECT_EDGE_FALLING     (CMP_FIR_EDGS_1)
#define CMP_DETECT_EDGE_BOTH        (CMP_FIR_EDGS)
/**
 * @}
 */

/**
 * @defgroup CMP_Out_Filter CMP output filter
 * @{
 */
#define CMP_OUT_FILTER_NONE         (0U)
#define CMP_OUT_FILTER_CLK_DIV1     (CMP_FIR_FCKS_0) /* Pclk/1 */
#define CMP_OUT_FILTER_CLK_DIV8     (CMP_FIR_FCKS_1) /* Pclk/8 */
#define CMP_OUT_FILTER_CLK_DIV32    (CMP_FIR_FCKS)   /* Pclk/32 */
/**
 * @}
 */

/**
 * @defgroup CMP_Timer_Win_Switch CMP timer window function switch
 * @{
 */
#define CMP_TMR_WIN_OFF             (0U)
#define CMP_TMR_WIN_ON              (CMP_OCR_TWOE)
/**
 * @}
 */

/**
 * @defgroup CMP_Timer_Win_Signal CMP timer windows function control signal
 * @{
 */
/* CMP1 select TIMB_1_PWM1 as timer window signal;
   CMP2 select TIMB_1_PWM3 as timer window signal;
   CMP3 select TIMB_1_PWM5 as timer window signal */
#define CMP_TMR_WIN_TIMB_1_PWM1_3_5 (CMP_TWR1_CTWS0)
/* CMP1 select TIMB_1_PWM2 as timer window signal;
   CMP2 select TIMB_1_PWM4 as timer window signal;
   CMP3 select TIMB_1_PWM6 as timer window signal */
#define CMP_TMR_WIN_TIMB_1_PWM2_4_6 (CMP_TWR1_CTWS1)
/* Chose TIM4_OWL as timer window signal */
#define CMP_TMR_WIN_TIM4_OWL        (CMP_TWR1_CTWS2)
/* Chose TIM4_OWH as timer window signal */
#define CMP_TMR_WIN_TIM4_OWH        (CMP_TWR1_CTWS3)
/* Chose TIM4_OVL as timer window signal */
#define CMP_TMR_WIN_TIM4_OVL        (CMP_TWR1_CTWS4)
/* Chose TIM4_OVH as timer window signal */
#define CMP_TMR_WIN_TIM4_OVH        (CMP_TWR1_CTWS5)
/* Chose TIM4_OUL as timer window signal */
#define CMP_TMR_WIN_TIM4_OUL        (CMP_TWR1_CTWS6)
/* Chose TIM4_OUH as timer window signal */
#define CMP_TMR_WIN_TIM4_OUH        (CMP_TWR1_CTWS7)
/**
 * @}
 */

/**
 * @defgroup CMP_Timer_Win_Invalid_Out CMP output level when timer window signal invalid
 * @{
 */
#define CMP_TMR_WIN_INVD_OUT_LOW    (0U)
#define CMP_TMR_WIN_INVD_OUT_HIGH   (CMP_OCR_TWOL)
/**
 * @}
 */

/**
 * @defgroup CMP_Timer_Win_Signal_Valid_Level CMP timer windows mode timer signal valid level
 * @{
 */
#define CMP_TMR_WIN_SIGNAL_VALID_LOW  (0U)
#define CMP_TMR_WIN_SIGNAL_VALID_HIGH (1U)
/**
 * @}
 */

/**
 * @defgroup CMP_DAC_Align_Mode CMP DAC data align mode
 * @{
 */
#define CMP_DAC_ALIGN_RIGHT         (0U)
#define CMP_DAC_ALIGN_LEFT          (CMP_DACR1_ALGN)
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
 * @addtogroup CMP_Global_Functions
 * @{
 */

/**
 * @brief  Write data to DAC right align
 * @param  [in] u8DACData       DAC voltage data
 *    @arg u8DACData: This parameter can be one data range 0x00~0xFF
 *                    DAC Voltage = VCCA x u8DACData / 255
 * @retval None
 */
__STATIC_INLINE void CMP_DAC_RightAlignWriteData(uint8_t u8DACData)
{
    WRITE_REG16(CM_DAC->DADR1, u8DACData);
}

/**
 * @brief  Write data to DAC left align
 * @param  [in] u8DACData       DAC voltage data
 *    @arg u8DACData: This parameter can be one data range 0x00~0xFF
 *                    DAC Voltage = VCCA x u8DACData / 255
 * @retval None
 */
__STATIC_INLINE void CMP_DAC_LeftAlignWriteData(uint8_t u8DACData)
{
    WRITE_REG16(CM_DAC->DADR1, ((uint16_t)u8DACData) << 8U);
}

en_result_t CMP_StructInit(stc_cmp_init_t* pstcCMPInit);
void CMP_DeInit(CM_CMP_TypeDef *CMPx);
en_result_t CMP_NormalModeInit(CM_CMP_TypeDef *CMPx,
                     const stc_cmp_init_t* pstcCMPInit);
en_result_t CMP_WindowModeInit(const stc_cmp_init_t* pstcCMPInit);

en_result_t CMP_TimerWindowConfig(CM_CMP_TypeDef *CMPx,
                                 const stc_cmp_timerwindows_t* pstcCMP_TimerWinConfig);
void CMP_TimerWindowCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);

void CMP_SetDetectEdge(CM_CMP_TypeDef *CMPx, uint32_t u8Edge);
void CMP_SetCompareVoltage(CM_CMP_TypeDef *CMPx, uint8_t u8CompareVoltage);
void CMP_SetRefVoltage(CM_CMP_TypeDef *CMPx, uint8_t u8RefVoltage);

void CMP_Cmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);
void CMP_IntCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);
void CMP_OutputCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);
void CMP_VCOUTCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);

en_flag_status_t CMP_GetCompareResult(const CM_CMP_TypeDef *CMPx);

void CMP_DAC_SetAlign(uint16_t u16Align);
void CMP_DAC_RightAlignWriteData(uint8_t u8DACData);
void CMP_DAC_LeftAlignWriteData(uint8_t u8DACData);
void CMP_DAC_Cmd(en_functional_state_t enNewState);
void CMP_DAC_ConnectADCCmd(en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* DDL_CMP_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_CMP_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
