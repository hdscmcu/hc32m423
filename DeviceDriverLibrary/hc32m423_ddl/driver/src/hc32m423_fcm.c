/**
 *******************************************************************************
 * @file  hc32m423_fcm.c
 * @brief This file provides firmware functions to manage the Frequency Clock
 *        Measurement (FCM).
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32m423_fcm.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_FCM FCM
 * @brief FCM Driver Library
 * @{
 */

#if (DDL_FCM_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FCM_Local_Macros FCM Local Macros
 * @{
 */

/* FCM Registers Reset Value */
#define FCM_REG_RST_VALUE     (0x00000000UL)

/* FCM interrupt mask */
#define FCM_INT_MASK          (FCM_INT_OVF | FCM_INT_END | FCM_INT_ERR)
/* FCM status flag mask */
#define FCM_FLAG_MASK         (FCM_SR_ERRF | FCM_SR_MENDF | FCM_SR_OVF)

/**
 * @defgroup FCM_Check_Parameters_Validity FCM Check Parameters Validity
 * @{
 */

/* Parameter validity check for FCM target clock source. */
#define IS_FCM_TARGET_SRC(src)                                                 \
(   ((src) == FCM_TARGET_CLK_XTAL)          ||                                 \
    ((src) == FCM_TARGET_CLK_HRC)           ||                                 \
    ((src) == FCM_TARGET_CLK_LRC)           ||                                 \
    ((src) == FCM_TARGET_CLK_SWDTLRC)       ||                                 \
    ((src) == FCM_TARGET_CLK_PCLK1)         ||                                 \
    ((src) == FCM_TARGET_CLK_MRC)           ||                                 \
    ((src) == FCM_TARGET_CLK_PLLP))

/* Parameter validity check for FCM target clock division. */
#define IS_FCM_TARGET_DIV(div)                                                 \
(   ((div) == FCM_TARGET_CLK_DIV1)          ||                                 \
    ((div) == FCM_TARGET_CLK_DIV4)          ||                                 \
    ((div) == FCM_TARGET_CLK_DIV8)          ||                                 \
    ((div) == FCM_TARGET_CLK_DIV32))

/* Parameter validity check for FCM external reference input function. */
#define IS_FCM_EXT_REF_FUNC(func)                                              \
(   ((func) == FCM_EXT_REF_OFF)             ||                                 \
    ((func) == FCM_EXT_REF_ON))

/* Parameter validity check for FCM reference clock edge. */
#define IS_FCM_REF_EDGE(edge)                                                  \
(   ((edge) == FCM_REF_CLK_RISING)          ||                                 \
    ((edge) == FCM_REF_CLK_FALLING)         ||                                 \
    ((edge) == FCM_REF_CLK_BOTH))

/* Parameter validity check for FCM digital filter function. */
#define IS_FCM_DIG_FILTER(df)                                                  \
(   ((df) == FCM_DIG_FILTER_OFF)            ||                                 \
    ((df) == FCM_DIG_FILTER_DIV1)           ||                                 \
    ((df) == FCM_DIG_FILTER_DIV4)           ||                                 \
    ((df) == FCM_DIG_FILTER_DIV16))

/* Parameter validity check for FCM reference clock source. */
#define IS_FCM_REF_SRC(src)                                                    \
(   ((src) == FCM_REF_CLK_EXINPUT)          ||                                 \
    ((src) == FCM_REF_CLK_XTAL)             ||                                 \
    ((src) == FCM_REF_CLK_HRC)              ||                                 \
    ((src) == FCM_REF_CLK_LRC)              ||                                 \
    ((src) == FCM_REF_CLK_SWDTLRC)          ||                                 \
    ((src) == FCM_REF_CLK_PCLK1)            ||                                 \
    ((src) == FCM_REF_CLK_MRC)              ||                                 \
    ((src) == FCM_REF_CLK_PLLP))

/* Parameter validity check for FCM reference clock division. */
#define IS_FCM_REF_DIV(div)                                                    \
(   ((div) == FCM_REF_CLK_DIV32)            ||                                 \
    ((div) == FCM_REF_CLK_DIV128)           ||                                 \
    ((div) == FCM_REF_CLK_DIV1024)          ||                                 \
    ((div) == FCM_REF_CLK_DIV8192))

/* Parameter validity check for FCM exception type function. */
#define IS_FCM_EXP_TYPE(type)                                                  \
(   ((type) == FCM_EXP_TYPE_INT)            ||                                 \
    ((type) == FCM_EXP_TYPE_RST))

/* Parameter validity check for FCM interrupt. */
#define IS_FCM_INT(it)      (((it) | FCM_INT_MASK) == FCM_INT_MASK)

/* Parameter validity check for FCM flag state. */
#define IS_FCM_FLAG(flag)                                                      \
(   ((flag) != 0x00UL)                      &&                                 \
    (((flag) | FCM_FLAG_MASK) == FCM_FLAG_MASK))

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup FCM_Global_Functions FCM Global Functions
 * @{
 */

/**
 * @brief  Initialize FCM.
 * @param  [in] pstcFcmInit         Pointer to a @ref stc_fcm_init_t structure
 *                                  that contains configuration information.
 * @retval en_result_t              Enumeration value:
 *    @arg Ok:                      FCM initialize successful
 *    @arg ErrorInvalidParameter:   Invalid parameter
 */
en_result_t FCM_Init(const stc_fcm_init_t *pstcFcmInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcFcmInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_FCM_TARGET_SRC(pstcFcmInit->u32TargetClock));
        DDL_ASSERT(IS_FCM_TARGET_DIV(pstcFcmInit->u32TargetClockDiv));
        DDL_ASSERT(IS_FCM_EXT_REF_FUNC(pstcFcmInit->u32ExtRefClockEnable));
        DDL_ASSERT(IS_FCM_REF_EDGE(pstcFcmInit->u32RefClockEdge));
        DDL_ASSERT(IS_FCM_DIG_FILTER(pstcFcmInit->u32DigitalFilter));
        DDL_ASSERT(IS_FCM_REF_SRC(pstcFcmInit->u32RefClock));
        DDL_ASSERT(IS_FCM_REF_DIV(pstcFcmInit->u32RefClockDiv));
        DDL_ASSERT(IS_FCM_EXP_TYPE(pstcFcmInit->u32ExceptionType));

        WRITE_REG32(CM_FCM->LVR, pstcFcmInit->u16LowerLimit);
        WRITE_REG32(CM_FCM->UVR, pstcFcmInit->u16UpperLimit);
        WRITE_REG32(CM_FCM->MCCR, (pstcFcmInit->u32TargetClock |               \
                                   pstcFcmInit->u32TargetClockDiv));
        WRITE_REG32(CM_FCM->RCCR, (pstcFcmInit->u32ExtRefClockEnable |         \
                                   pstcFcmInit->u32RefClockEdge |              \
                                   pstcFcmInit->u32DigitalFilter |             \
                                   pstcFcmInit->u32RefClock|                   \
                                   pstcFcmInit->u32RefClockDiv));
        MODIFY_REG32(CM_FCM->RIER, FCM_RIER_ERRINTRS, pstcFcmInit->u32ExceptionType);
    }
    return enRet;
}

/**
 * @brief  Initialize FCM structure. Fill each pstcFcmInit with
 *         default value
 * @param  [in] pstcFcmInit         Pointer to a @ref stc_fcm_init_t structure
 *                                  that contains configuration information.
 * @retval en_result_t              Enumeration value:
 *    @arg Ok:                      FCM structure initialize successful
 *    @arg ErrorInvalidParameter:   Invalid parameter
 */
en_result_t FCM_StructInit(stc_fcm_init_t *pstcFcmInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcFcmInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Reset FCM init structure parameters values */
        pstcFcmInit->u16LowerLimit = 0U;
        pstcFcmInit->u16UpperLimit = 0U;
        pstcFcmInit->u32TargetClock = FCM_TARGET_CLK_XTAL;
        pstcFcmInit->u32TargetClockDiv = FCM_TARGET_CLK_DIV1;
        pstcFcmInit->u32ExtRefClockEnable = FCM_EXT_REF_OFF;
        pstcFcmInit->u32RefClockEdge = FCM_REF_CLK_RISING;
        pstcFcmInit->u32DigitalFilter = FCM_DIG_FILTER_OFF;
        pstcFcmInit->u32RefClock = FCM_REF_CLK_XTAL;
        pstcFcmInit->u32RefClockDiv = FCM_REF_CLK_DIV32;
        pstcFcmInit->u32ExceptionType = FCM_EXP_TYPE_INT;
    }
    return enRet;
}

/**
 * @brief  De-Initialize FCM.
 * @param  None
 * @retval None
 */
void FCM_DeInit(void)
{
    WRITE_REG32(CM_FCM->STR, FCM_REG_RST_VALUE);
    WRITE_REG32(CM_FCM->CLR, FCM_FLAG_MASK);
    WRITE_REG32(CM_FCM->LVR, FCM_REG_RST_VALUE);
    WRITE_REG32(CM_FCM->UVR, FCM_REG_RST_VALUE);
    WRITE_REG32(CM_FCM->MCCR,FCM_REG_RST_VALUE);
    WRITE_REG32(CM_FCM->RCCR,FCM_REG_RST_VALUE);
    WRITE_REG32(CM_FCM->RIER,FCM_REG_RST_VALUE);
}

/**
 * @brief  Get FCM state, get FCM overflow, complete, error flag.
 * @param  [in] u32Flag         FCM flags.This parameter can be one or any
 *                              combination of the following values: @ref FCM_Flag_Sel
 *   @arg  FCM_FLAG_ERR:        FCM error.
 *   @arg  FCM_FLAG_END:        FCM measure end.
 *   @arg  FCM_FLAG_OVF:        FCM overflow.
 * @retval en_flag_status_t:    FCM flag status.
 */
en_flag_status_t FCM_GetStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_FCM_FLAG(u32Flag));

    return (READ_REG32_BIT(CM_FCM->SR, u32Flag) ? Set : Reset);
}

/**
 * @brief  Clear FCM state, Clear FCM overflow, complete, error flag.
 * @param  [in] u32Flag     FCM flags.This parameter can be one or any
 *                          combination of the following values: @ref FCM_Flag_Sel
 *   @arg  FCM_FLAG_ERR:    FCM error.
 *   @arg  FCM_FLAG_END:    FCM measure end.
 *   @arg  FCM_FLAG_OVF:    FCM overflow.
 * @retval None.
 */
void FCM_ClearStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_FCM_FLAG(u32Flag));

    SET_REG32_BIT(CM_FCM->CLR, u32Flag);
}

/**
 * @brief  Get FCM counter value.
 * @param  None
 * @retval FCM counter value.
 */
uint16_t FCM_GetCountValue(void)
{
    return (uint16_t)(READ_REG32(CM_FCM->CNTR) & 0xFFFFU);
}

/**
 * @brief  FCM target clock type and division config.
 * @param  [in] u32ClockSrc Target clock type. @ref FCM_Target_Clock_Src
 *   @arg  FCM_TARGET_CLK_XTAL
 *   @arg  FCM_TARGET_CLK_HRC
 *   @arg  FCM_TARGET_CLK_LRC
 *   @arg  FCM_TARGET_CLK_SWDTLRC
 *   @arg  FCM_TARGET_CLK_PCLK1
 *   @arg  FCM_TARGET_CLK_MRC
 *   @arg  FCM_TARGET_CLK_PLLP
 * @param  [in] u32Div Target clock division. @ref FCM_Target_Clock_Div
 *   @arg  FCM_TARGET_CLK_DIV1
 *   @arg  FCM_TARGET_CLK_DIV4
 *   @arg  FCM_TARGET_CLK_DIV8
 *   @arg  FCM_TARGET_CLK_DIV32
 * @retval None.
 */
void FCM_SetTargetClock(uint32_t u32ClockSrc, uint32_t u32Div)
{
    DDL_ASSERT(IS_FCM_TARGET_SRC(u32ClockSrc));
    DDL_ASSERT(IS_FCM_TARGET_DIV(u32Div));
    WRITE_REG32(CM_FCM->MCCR, (u32ClockSrc | u32Div));
}

/**
 * @brief  FCM reference clock type and division config.
 * @param  [in] u32ClockSrc Reference clock type. @ref FCM_Ref_Clock_Src
 *   @arg  FCM_REF_CLK_EXINPUT
 *   @arg  FCM_REF_CLK_XTAL
 *   @arg  FCM_REF_CLK_HRC
 *   @arg  FCM_REF_CLK_LRC
 *   @arg  FCM_REF_CLK_SWDTLRC
 *   @arg  FCM_REF_CLK_PCLK1
 *   @arg  FCM_REF_CLK_MRC
 *   @arg  FCM_REF_CLK_PLLP
 * @param  [in] u32Div Reference clock division. @ref FCM_Ref_Clock_Div
 *   @arg  FCM_REF_CLK_DIV32
 *   @arg  FCM_REF_CLK_DIV128
 *   @arg  FCM_REF_CLK_DIV1024
 *   @arg  FCM_REF_CLK_DIV8192
 * @retval None.
 */
void FCM_SetRefClock(uint32_t u32ClockSrc, uint32_t u32Div)
{
    DDL_ASSERT(IS_FCM_REF_SRC(u32ClockSrc));
    DDL_ASSERT(IS_FCM_REF_DIV(u32Div));
    MODIFY_REG32(CM_FCM->RCCR,                                                 \
                (FCM_RCCR_INEXS | FCM_RCCR_RCKS | FCM_RCCR_RDIVS),             \
                (u32ClockSrc | u32Div));
}

/**
 * @brief  Enable or disable the FCM reset
 * @param  [in] enNewState      The new state of the FCM reset.
 *    @arg Enable:              Enable FCM reset
 *    @arg Disable:             Disable FCM reset
 * @retval None
 */
void FCM_ResetCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_FCM->RIER_b.ERRE, enNewState);
}

/**
 * @brief  Enable or disable the FCM interrupt
 * @param  [in] u32IntType      The FCM interrupt type. This parameter can be 
 *                              one or any combination @ref FCM_Int_Type
 *    @arg FCM_INT_OVF:         FCM overflow interrupt
 *    @arg FCM_INT_END:         FCM calculate end interrupt
 *    @arg FCM_INT_ERR:         FCM frequency abnormal interrupt
 * @param  [in] enNewState      The new state of the FCM interrupt.
 *    @arg Enable:              Enable FCM interrupt
 *    @arg Disable:             Disable FCM interrupt
 * @retval None
 */
void FCM_IntCmd(uint32_t u32IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FCM_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(CM_FCM->RIER, u32IntType);
    }
    else
    {
        CLEAR_REG32_BIT(CM_FCM->RIER, u32IntType);
    }
}

/**
 * @brief  FCM function config.
 * @param  [in] enNewState
 *   @arg  Enable:      Enable FCM
 *   @arg  Disable:     Disable FCM
 * @retval None.
 */
void FCM_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(bCM_FCM->STR_b.START, enNewState);
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
