/**
 *******************************************************************************
 * @file  hc32m423_fcm.h
 * @brief This file contains all the functions prototypes of the FCM driver
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
#ifndef __HC32M423_FCM_H__
#define __HC32M423_FCM_H__

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
 * @addtogroup DDL_FCM
 * @{
 */

#if (DDL_FCM_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup FCM_Global_Types FCM Global Types
 * @{
 */
/**
 * @brief  FCM Init structure definition
 */
typedef struct
{
    uint16_t u16LowerLimit;     /*!< FCM lower limit value*/

    uint16_t u16UpperLimit;     /*!< FCM upper limit value*/

    uint32_t u32TargetClock;    /*!< FCM target clock source selection,         \
                                     @ref FCM_Target_Clock_Src for details */

    uint32_t u32TargetClockDiv; /*!< FCM target clock source division selection,\
                                     @ref FCM_Target_Clock_Div for details */

    uint32_t u32ExtRefClockEnable; /*!< FCM external reference clock function config,  \
                                     @ref FCM_Ext_Ref_Clock_Config for details    */

    uint32_t u32RefClockEdge;   /*!< FCM reference clock trigger edge selection,\
                                     @ref FCM_Ref_Clock_Edge for details    */

    uint32_t u32DigitalFilter;  /*!< FCM digital filter function config,        \
                                     @ref FCM_Digital_Filter_config for details    */

    uint32_t u32RefClock;       /*!< FCM reference clock source selection,      \
                                     @ref FCM_Ref_Clock_Src for details    */

    uint32_t u32RefClockDiv;    /*!< FCM reference clock source division selection, \
                                     @ref FCM_Ref_Clock_Div for details */

    uint32_t u32ExceptionType;  /*!< FCM exception type select,  @ref FCM_Exception_Type */
} stc_fcm_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FCM_Global_Macros FCM Global Macros
 * @{
 */

/**
 * @defgroup FCM_Target_Clock_Src FCM target clock source
 * @{
 */
#define FCM_TARGET_CLK_XTAL       (0x00UL << FCM_MCCR_MCKS_POS)
#define FCM_TARGET_CLK_HRC        (0x02UL << FCM_MCCR_MCKS_POS)
#define FCM_TARGET_CLK_LRC        (0x03UL << FCM_MCCR_MCKS_POS)
#define FCM_TARGET_CLK_SWDTLRC    (0x04UL << FCM_MCCR_MCKS_POS)
#define FCM_TARGET_CLK_PCLK1      (0x05UL << FCM_MCCR_MCKS_POS)
#define FCM_TARGET_CLK_MRC        (0x07UL << FCM_MCCR_MCKS_POS)
#define FCM_TARGET_CLK_PLLP       (0x08UL << FCM_MCCR_MCKS_POS)
/**
 * @}
 */

/**
 * @defgroup FCM_Target_Clock_Div FCM target clock division
 * @{
 */
#define FCM_TARGET_CLK_DIV1       (0x00UL)
#define FCM_TARGET_CLK_DIV4       (FCM_MCCR_MDIVS_0)
#define FCM_TARGET_CLK_DIV8       (FCM_MCCR_MDIVS_1)
#define FCM_TARGET_CLK_DIV32      (FCM_MCCR_MDIVS)
/**
 * @}
 */

/**
 * @defgroup FCM_Ext_Ref_Clock_Config FCM external reference clock config
 * @{
 */
#define FCM_EXT_REF_OFF           (0x00UL)
#define FCM_EXT_REF_ON            (FCM_RCCR_EXREFE)
/**
 * @}
 */

/**
 * @defgroup FCM_Ref_Clock_Edge FCM reference clock edge
 * @{
 */
#define FCM_REF_CLK_RISING        (0x00UL)
#define FCM_REF_CLK_FALLING       (FCM_RCCR_EDGES_0)
#define FCM_REF_CLK_BOTH          (FCM_RCCR_EDGES_1)
/**
 * @}
 */

/**
 * @defgroup FCM_Digital_Filter_config FCM digital filter config
 * @{
 */
#define FCM_DIG_FILTER_OFF        (0x00UL)
#define FCM_DIG_FILTER_DIV1       (FCM_RCCR_DNFS_0)
#define FCM_DIG_FILTER_DIV4       (FCM_RCCR_DNFS_1)
#define FCM_DIG_FILTER_DIV16      (FCM_RCCR_DNFS)
/**
 * @}
 */

/**
 * @defgroup FCM_Ref_Clock_Src FCM reference clock source
 * @{
 */
#define FCM_REF_CLK_EXINPUT       (0x00UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_XTAL          (0x10UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_HRC           (0x12UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_LRC           (0x13UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_SWDTLRC       (0x14UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_PCLK1         (0x15UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_MRC           (0x17UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_PLLP          (0x18UL << FCM_RCCR_RCKS_POS)
/**
 * @}
 */

/**
 * @defgroup FCM_Ref_Clock_Div FCM reference clock division
 * @{
 */
#define FCM_REF_CLK_DIV32         (0x00UL)
#define FCM_REF_CLK_DIV128        (FCM_RCCR_RDIVS_0)
#define FCM_REF_CLK_DIV1024       (FCM_RCCR_RDIVS_1)
#define FCM_REF_CLK_DIV8192       (FCM_RCCR_RDIVS)
/**
 * @}
 */

/**
 * @defgroup FCM_Abnormal_Reset_Func FCM abnormal reset function config
 * @{
 */
#define FCM_ERR_RST_OFF           (0x00UL)
#define FCM_ERR_RST_ON            (FCM_RIER_ERRE)
/**
 * @}
 */

/**
 * @defgroup FCM_Exception_Type FCM exception type
 * @{
 */
#define FCM_EXP_TYPE_INT          (0x00UL)
#define FCM_EXP_TYPE_RST          (FCM_RIER_ERRINTRS)
/**
 * @}
 */

/**
 * @defgroup FCM_Int_Type FCM interrupt type define
 * @{
 */
#define FCM_INT_OVF               (FCM_RIER_OVFIE)
#define FCM_INT_END               (FCM_RIER_MENDIE)
#define FCM_INT_ERR               (FCM_RIER_ERRIE)
/**
 * @}
 */

/**
 * @defgroup FCM_Flag_Sel FCM status flag selection
 * @{
 */
#define FCM_FLAG_ERR              (FCM_SR_ERRF)
#define FCM_FLAG_END              (FCM_SR_MENDF)
#define FCM_FLAG_OVF              (FCM_SR_OVF)
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
 * @addtogroup FCM_Global_Functions
 * @{
 */

/**
 * @brief  Set FCM upper limit value.
 * @param  u16Limit
 * @retval None.
 */
__STATIC_INLINE void FCM_SetUpperLimit(uint16_t u16Limit)
{
    WRITE_REG32(CM_FCM->UVR, u16Limit);
}

/**
 * @brief  Set FCM lower limit value.
 * @param  u16Limit
 * @retval None
 */
__STATIC_INLINE void FCM_SetLowerLimit(uint16_t u16Limit)
{
    WRITE_REG32(CM_FCM->LVR, u16Limit);
}

en_result_t FCM_Init(const stc_fcm_init_t *pstcFcmInit);
en_result_t FCM_StructInit(stc_fcm_init_t *pstcFcmInit);
void FCM_DeInit(void);
uint16_t FCM_GetCountValue(void);
void FCM_SetUpperLimit(uint16_t u16Limit);
void FCM_SetLowerLimit(uint16_t u16Limit);
void FCM_SetTargetClock(uint32_t u32ClockSrc, uint32_t u32Div);
void FCM_SetRefClock(uint32_t u32ClockSrc, uint32_t u32Div);
en_flag_status_t FCM_GetStatus(uint32_t u32Flag);
void FCM_ClearStatus(uint32_t u32Flag);
void FCM_ResetCmd(en_functional_state_t enNewState);
void FCM_IntCmd(uint32_t u32IntType, en_functional_state_t enNewState);
void FCM_Cmd(en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* DDL_FCM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_FCM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
