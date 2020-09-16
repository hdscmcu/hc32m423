/**
 *******************************************************************************
 * @file  hc32m423_cmp.c
 * @brief This file provides firmware functions to manage the Comparator(CMP).
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32m423_cmp.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CMP CMP
 * @brief CMP Driver Library
 * @{
 */

#if (DDL_CMP_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CMP_Local_Macros CMP Local Macros
 * @{
 */

#define CMP_DADC1_REG_UNLOCK                (0x5500U)

/**
 * @defgroup CMP_Check_Parameters_Validity CMP Check Parameters Validity
 * @{
 */

#define IS_CMP_UNIT(x)                                                         \
(   ((x) == CM_CMP1)                            ||                             \
    ((x) == CM_CMP2)                            ||                             \
    ((x) == CM_CMP3))

#define IS_CMP_MODE(x)                                                         \
(   ((x) == CMP_MD_NORMAL)                      ||                             \
    ((x) == CMP_MD_WIN))

#define IS_CMP_CMP_VOLT(x)                                                     \
(   ((x) == CMP_CMP_VOLT_NONE)                  ||                             \
    ((x) == CMP_CMP_VOLT_IVCMPx_0)              ||                             \
    ((x) == CMP_CMP_VOLT_IVCMPx_1)              ||                             \
    ((x) == CMP_CMP_VOLT_IVCMPx_2)              ||                             \
    ((x) == CMP_CMP_VOLT_VREF))

#define IS_CMP_REF_VOLT(x)                                                     \
(   ((x) == CMP_REF_VOLT_NONE)                  ||                             \
    ((x) == CMP_REF_VOLT_IVREF1)                ||                             \
    ((x) == CMP_REF_VOLT_IVREF2)                ||                             \
    ((x) == CMP_REF_VOLT_DAC))

#define IS_CMP_OUT_POLARITY(x)                                                 \
(   ((x) == CMP_OUT_POLARITY_NORMAL)            ||                             \
    ((x) == CMP_OUT_POLARITY_REVS))

#define IS_CMP_OUT_DETECT_EDGE(x)                                               \
(   ((x) == CMP_DETECT_EDGE_NONE)                ||                             \
    ((x) == CMP_DETECT_EDGE_RISING)              ||                             \
    ((x) == CMP_DETECT_EDGE_FALLING)             ||                             \
    ((x) == CMP_DETECT_EDGE_BOTH))

#define IS_CMP_OUT_FILTER(x)                                                   \
(   ((x) == CMP_OUT_FILTER_NONE)                ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV1)           ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV8)           ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV32))

#define IS_CMP_TMR_WIN_SWITCH(x)                                               \
(   ((x) == CMP_TMR_WIN_OFF)                    ||                             \
    ((x) == CMP_TMR_WIN_ON))

#define IS_CMP_TMR_WIN_INVD_OUT(x)                                             \
(   ((x) == CMP_TMR_WIN_INVD_OUT_LOW)           ||                             \
    ((x) == CMP_TMR_WIN_INVD_OUT_HIGH))

#define IS_CMP_TMR_WIN_SIGNAL_VALID_LVL(x)                                     \
(   ((x) == CMP_TMR_WIN_SIGNAL_VALID_LOW)       ||                             \
    ((x) == CMP_TMR_WIN_SIGNAL_VALID_HIGH))

#define IS_CMP_DAC_ALIGN_MD(x)                                                 \
(   ((x) == CMP_DAC_ALIGN_RIGHT)                ||                             \
    ((x) == CMP_DAC_ALIGN_LEFT))

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
 * @defgroup CMP_Global_Functions CMP Global Functions
 * @{
 */

/**
 * @brief  Voltage compare command
 * @param  [in] CMPx            Pointer to CMP instance register base,This
 *                              parameter can be one of the following values:
 *    @arg CM_CMP1: CMP unit 1
 *    @arg CM_CMP2: CMP unit 2
 *    @arg CM_CMP3: CMP unit 3
 * @param  [in] enNewState      The function new state.
 *    @arg Enable:  Enable the CMP analog compare
 *    @arg Disable: Disable the CMP analog compare
 * @retval None
 */
void CMP_Cmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
        /* Delay about 300ns */
        DDL_DelayUS(1UL);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    }
}

/**
 * @brief  Voltage compare interrupt command
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *    @arg CM_CMP1: CMP unit 1
 *    @arg CM_CMP2: CMP unit 2
 *    @arg CM_CMP3: CMP unit 3
 * @param  [in] enNewState        The function new state.
 *    @arg Enable:  Enable the CMP interrupt
 *    @arg Disable: Disable the CMP interrupt
 * @retval None
 */
void CMP_IntCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN);
    }
}

/**
 * @brief  Voltage analog compare output command
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *    @arg CM_CMP1: CMP unit 1
 *    @arg CM_CMP2: CMP unit 2
 *    @arg CM_CMP3: CMP unit 3
 * @param  [in] enNewState        The function new state.
 *    @arg Enable:  Enable the CMP analog output
 *    @arg Disable: Disable the CMP analog output
 * @retval None
 */
void CMP_OutputCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_COEN);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->OCR, CMP_OCR_COEN);
    }
}

/**
 * @brief  Voltage compare output port VCOUT function command
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *    @arg CM_CMP1: CMP unit 1
 *    @arg CM_CMP2: CMP unit 2
 *    @arg CM_CMP3: CMP unit 3
 * @param  [in] enNewState        The function new state.
 *    @arg Enable:  Enable the CMP VCOUT pin
 *    @arg Disable: Disable the CMP VCOUT pin
 * @retval None
 */
void CMP_VCOUTCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_CPOE);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->OCR, CMP_OCR_CPOE);
    }
}

/**
 * @brief  Voltage compare result monitor read
 * @param  [in] CMPx            Pointer to CMP instance register base,This
 *                              parameter can be one of the following values:
 *    @arg CM_CMP1: CMP unit 1
 *    @arg CM_CMP2: CMP unit 2
 *    @arg CM_CMP3: CMP unit 3
 * @retval CMP monitor flag status
 *    In normal mode
 *    @arg Set:   Compare voltage > reference voltage
 *    @arg Reset: Compare voltage < reference voltage
 *    In Window mode
 *    @arg Set:   Compare voltage > reference low voltage and
 *                Compare voltage < reference high voltage
 *    @arg Reset: Compare voltage < reference low voltage or
 *                Compare voltage > reference high voltage
 */
en_flag_status_t CMP_GetCompareResult(const CM_CMP_TypeDef *CMPx)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    return (READ_REG8_BIT(CMPx->MDR, CMP_MDR_CMON) ? Set : Reset);
}

/**
 * @brief  Voltage compare timer window function configurate
 * @param  [in] CMPx            Pointer to CMP instance register base,This
 *                              parameter can be one of the following values:
 *    @arg CM_CMP1:   CMP unit 1
 *    @arg CM_CMP2:   CMP unit 2
 *    @arg CM_CMP3:   CMP unit 3
 * @param  [in] pstcCMP_TimerWinConfig Configuration structure for timer window function
 *    @arg pstcCMP_TimerWinConfig->u8TWInvalidLevel:
 *                    The output level when timer window signal invalid.
 *                    @ref CMP_Timer_Win_Invalid_Out
 *    @arg pstcCMP_TimerWinConfig->u8TimerWinSignal:
 *                    The timer event signal for timer window function.
 *                    @ref CMP_Timer_Win_Signal
 *    @arg pstcCMP_TimerWinConfig->u8TimerWinValidLevel:
 *                    Timer window mode signal valid level.
 *                    @ref CMP_Timer_Win_Signal_Valid_Level
 * @retval An en_result_t enumeration value:
 *    @arg Ok: Configurate success
 *    @arg ErrorInvalidParameter: Invalid parameter
 */
en_result_t CMP_TimerWindowConfig(CM_CMP_TypeDef *CMPx,
                                 const stc_cmp_timerwindows_t* pstcCMP_TimerWinConfig)
{
    en_result_t enRet = Ok;
    /* Check configuration structure*/
    if (NULL == pstcCMP_TimerWinConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_CMP_UNIT(CMPx));
        DDL_ASSERT(IS_CMP_TMR_WIN_INVD_OUT(pstcCMP_TimerWinConfig->u8TWInvalidLevel));
        DDL_ASSERT(IS_CMP_TMR_WIN_SIGNAL_VALID_LVL(pstcCMP_TimerWinConfig->u8TimerWinValidLevel));

        /* Write TWR2 register and TWR1 register */
        if(0U != pstcCMP_TimerWinConfig->u8TimerWinValidLevel)
        {
            SET_REG8_BIT(CMPx->TWR2, pstcCMP_TimerWinConfig->u8TimerWinSignal);
        }
        else
        {
            CLEAR_REG8_BIT(CMPx->TWR2, pstcCMP_TimerWinConfig->u8TimerWinSignal);
        }

        WRITE_REG8(CMPx->TWR1, pstcCMP_TimerWinConfig->u8TimerWinSignal);

        /* Enable timer window mode and configuration output level in windows invalid */
        MODIFY_REG8(CMPx->OCR, CMP_OCR_TWOL, pstcCMP_TimerWinConfig->u8TWInvalidLevel);
    }
    return enRet;
}

/**
 * @brief  CMP out timer window function command
 * @param  [in] CMPx            Pointer to CMP instance register base,This
 *                              parameter can be one of the following values:
 *    @arg CM_CMP1:   CMP unit 1
 *    @arg CM_CMP2:   CMP unit 2
 *    @arg CM_CMP3:   CMP unit 3
 * @param  [in] enNewState      The function new state.
 *    @arg Enable:    Enable the CMP out timer window function
 *    @arg Disable:   Disable the CMP out timer window function
 * @retval None
 */
void CMP_TimerWindowCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_TWOE);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->OCR, CMP_OCR_TWOE);
    }
}

/**
 * @brief  CMP normal mode initialize
 * @param  [in] CMPx            Pointer to CMP instance register base,This
 *                              parameter can be one of the following values:
 *    @arg CM_CMP1:   CMP unit 1
 *    @arg CM_CMP2:   CMP unit 2
 *    @arg CM_CMP3:   CMP unit 3
 * @param  [in] pstcCMPInit Configuration structure for normal mode initialize
 *    @arg pstcCMPInit->u8CompareVoltage:
 *                    Compare voltage, @ref CMP_Compare_Voltage
 *    @arg pstcCMPInit->u8RefVoltage:
 *                    Reference voltage, @ref CMP_Ref_Voltage
 *    @arg pstcCMPInit->u8OutPolarity:
 *                    Output polarity select, @ref CMP_Out_Polarity
 *    @arg pstcCMPInit->u8OutDetectEdges:
 *                    Output detect edge, @ref CMP_Out_Detect_Edge
 *    @arg pstcCMPInit->u8OutFilter:
 *                    Output Filter, @ref CMP_Out_Filter
 * @retval An en_result_t enumeration value:
 *    @arg Ok:        Initialize success
 *    @arg ErrorInvalidParameter: Invalid parameter
 */
en_result_t CMP_NormalModeInit(CM_CMP_TypeDef *CMPx,
                     const stc_cmp_init_t* pstcCMPInit)
{
    en_result_t enRet = Ok;
    /* Check configuration structure*/
    if (NULL == pstcCMPInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_CMP_UNIT(CMPx));
        DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(pstcCMPInit->u8OutDetectEdges));
        DDL_ASSERT(IS_CMP_OUT_FILTER(pstcCMPInit->u8OutFilter));
        DDL_ASSERT(IS_CMP_OUT_POLARITY(pstcCMPInit->u8OutPolarity));
        DDL_ASSERT(IS_CMP_CMP_VOLT(pstcCMPInit->u8CompareVoltage));
        DDL_ASSERT(IS_CMP_REF_VOLT(pstcCMPInit->u8RefVoltage));

        /* Stop CMP compare */
        WRITE_REG8(CMPx->MDR, 0x00U);

        /* Set compare voltage and reference voltage */
        WRITE_REG8(CMPx->VSR,
                  pstcCMPInit->u8CompareVoltage | pstcCMPInit->u8RefVoltage);

        /* Start CMP compare */
        WRITE_REG8(CMPx->MDR, CMP_MDR_CENB);
        /* Delay about 300ns */
        DDL_DelayUS(1UL);

        /* Set output filter and output detect edge and output polarity */
        WRITE_REG8(CMPx->FIR,
                  pstcCMPInit->u8OutFilter | pstcCMPInit->u8OutDetectEdges);
        WRITE_REG8(CMPx->OCR, pstcCMPInit->u8OutPolarity);
    }
    return enRet;
}

/**
 * @brief  CMP window mode initialize
 * @param  [in] pstcCMPInit Configuration structure for window mode initialize
 *    @arg pstcCMPInit->u8WinVoltageLow:
 *                    CMP reference low voltage for window mode,
 *                    @ref CMP_Ref_Voltage
 *    @arg pstcCMPInit->u8WinVoltageHigh:
 *                    CMP reference high voltage for window mode,
 *                    @ref CMP_Ref_Voltage
 *    @arg pstcCMPInit->u8OutPolarity:
 *                    Output polarity select, @ref CMP_Out_Polarity
 *    @arg pstcCMPInit->u8OutDetectEdges:
 *                    Output detect edge, @ref CMP_Out_Detect_Edge
 *    @arg pstcCMPInit->u8OutFilter:
 *                    Output Filter, @ref CMP_Out_Filter
 * @retval An en_result_t enumeration value:
 *    @arg Ok:        Initialize success
 *    @arg ErrorInvalidParameter: Invalid parameter
 */
en_result_t CMP_WindowModeInit(const stc_cmp_init_t* pstcCMPInit)
{
    en_result_t enRet = Ok;
    /* Check configuration structure */
    if (NULL == pstcCMPInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(pstcCMPInit->u8OutDetectEdges));
        DDL_ASSERT(IS_CMP_OUT_FILTER(pstcCMPInit->u8OutFilter));
        DDL_ASSERT(IS_CMP_OUT_POLARITY(pstcCMPInit->u8OutPolarity));
        DDL_ASSERT(IS_CMP_REF_VOLT(pstcCMPInit->u8WinVoltageLow));
        DDL_ASSERT(IS_CMP_REF_VOLT(pstcCMPInit->u8WinVoltageHigh));

        /* Stop CMP compare */
        WRITE_REG8(CM_CMP2->MDR, 0x00U);
        WRITE_REG8(CM_CMP3->MDR, 0x00U);

        /* Set compare voltage and reference voltage */
        WRITE_REG8(CM_CMP3->VSR,
                  CMP_CMP_VOLT_IVCMPx_2 | pstcCMPInit->u8WinVoltageLow);
        WRITE_REG8(CM_CMP2->VSR,
                  CMP_CMP_VOLT_IVCMPx_2 | pstcCMPInit->u8WinVoltageHigh);

        /* Select window compare mode and start CMP compare function */
        WRITE_REG8(CM_CMP2->MDR, CMP_MDR_CENB | CMP_MDR_CWDE);
        WRITE_REG8(CM_CMP3->MDR, CMP_MDR_CENB);
        /* Delay about 300ns */
        DDL_DelayUS(1UL);

        /* Set output filter and output detect edge and output polarity */
        WRITE_REG8(CM_CMP2->FIR,
                  pstcCMPInit->u8OutFilter | pstcCMPInit->u8OutDetectEdges);
        WRITE_REG8(CM_CMP2->OCR, pstcCMPInit->u8OutPolarity);
    }
    return enRet;
}

/**
 * @brief  CMP set 8 bit DAC align mode
 * @param  [in] u16Align        DAC align mode, @ref CMP_DAC_Align_Mode
 *    @arg CMP_DAC_ALIGN_RIGHT: Data align right
 *    @arg CMP_DAC_ALIGN_LEFT:  Data align left
 * @retval None
 */
void CMP_DAC_SetAlign(uint16_t u16Align)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_DAC_ALIGN_MD(u16Align));

    WRITE_REG32(bCM_DAC->DACR1_b.ALGN, (uint32_t)u16Align >> CMP_DACR1_ALGN_POS);
}

/**
 * @brief  CMP 8 bit DAC reference voltage function command
 * @param  [in] enNewState      The function new state.
 *    @arg Enable:  Enable the 8 bit DAC
 *    @arg Disable: Disable the 8 bit DAC
 * @retval None
 */
void CMP_DAC_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG16_BIT(CM_DAC->DACR1, CMP_DACR1_DAEN);
    }
    else
    {
        CLEAR_REG16_BIT(CM_DAC->DACR1, CMP_DACR1_DAEN);
    }
}

/**
 * @brief  CMP 8 bit DAC connect to ADC command
 * @param  [in] enNewState      The function new state.
 *    @arg Enable:  Enable the 8 bit DAC connect to ADC
 *    @arg Disable: Disable the 8 bit DAC connect to ADC
 * @retval None
 */
void CMP_DAC_ConnectADCCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG16(CM_DAC->DACR1, CMP_DADC1_REG_UNLOCK | (uint16_t)enNewState);
}

/**
 * @brief De-initialize CMP unit
 * @param [in] CMPx             Pointer to CMP instance register base,This
 *                              parameter can be one of the following values:
 *   @arg CM_CMP1: CMP unit 1
 *   @arg CM_CMP2: CMP unit 2
 *   @arg CM_CMP3: CMP unit 3
 * @retval None
 */
void CMP_DeInit(CM_CMP_TypeDef *CMPx)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));

    WRITE_REG8(CMPx->MDR, 0x00U);
    WRITE_REG8(CMPx->FIR, 0x00U);
    WRITE_REG8(CMPx->OCR, 0x00U);
    WRITE_REG8(CMPx->VSR, 0x00U);
    WRITE_REG8(CMPx->TWR1, 0x00U);
    WRITE_REG8(CMPx->TWR2, 0x00U);
}

/**
 * @brief  Initialize structure stc_cmp_init_t variable with default value.
 * @param  [out] pstcCMPInit     Pointer to a stc_cmp_init_t structure variable
 *                               which will be initialized. @ref stc_cmp_init_t.
 * @retval An en_result_t enumeration value:
 *    @arg Ok:        Initialize success
 *    @arg ErrorInvalidParameter: Invalid parameter
 */
en_result_t CMP_StructInit(stc_cmp_init_t* pstcCMPInit)
{
    en_result_t enRet = Ok;
    if (NULL == pstcCMPInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcCMPInit->u8CompareVoltage = CMP_CMP_VOLT_NONE;
        pstcCMPInit->u8RefVoltage = CMP_REF_VOLT_NONE;
        pstcCMPInit->u8OutDetectEdges = CMP_DETECT_EDGE_NONE;
        pstcCMPInit->u8OutFilter = CMP_OUT_FILTER_NONE;
        pstcCMPInit->u8OutPolarity = CMP_OUT_POLARITY_NORMAL;
        pstcCMPInit->u8WinVoltageLow = CMP_REF_VOLT_NONE;
        pstcCMPInit->u8WinVoltageHigh = CMP_REF_VOLT_NONE;
    }
    return enRet;
}

/**
 * @brief  Set output detect edge for CMP
 * @param  [in] CMPx                Pointer to CMP instance register base,This
 *                                  parameter can be one of the following values:
 *    @arg CM_CMP1: CMP unit 1
 *    @arg CM_CMP2: CMP unit 2
 *    @arg CM_CMP3: CMP unit 3
 * @param  [in] u8Edge              Detect edge @ref CMP_Out_Detect_Edge
 *    @arg CMP_DETECT_EDGE_NONE:    Don't dectect any edge for CMP output
 *    @arg CMP_DETECT_EDGE_RISING:  Detect rising edge for CMP output
 *    @arg CMP_DETECT_EDGE_FALLING: Detect falling edge for CMP output
 *    @arg CMP_DETECT_EDGE_BOTH:    Detect rising and falling edge for CMP output
 * @retval None
 * @note   Can't set detect edge when CMP interrupt or event trigger is enable.
 * @note   Clear interrupt flag after detect edge changed.
 */
void CMP_SetDetectEdge(CM_CMP_TypeDef *CMPx, uint32_t u8Edge)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(u8Edge));

    MODIFY_REG8(CMPx->FIR, CMP_FIR_EDGS, u8Edge);
}

/**
 * @brief  Set compare voltage for CMP
 * @param  [in] CMPx                Pointer to CMP instance register base,This
 *                                  parameter can be one of the following values:
 *    @arg CM_CMP1: CMP unit 1
 *    @arg CM_CMP2: CMP unit 2
 *    @arg CM_CMP3: CMP unit 3
 * @param  [in] u8CompareVoltage    Compare voltage @ref CMP_Compare_Voltage
 *    @arg CMP_CMP_VOLT_NONE:       No compare voltage input
 *    @arg CMP_CMP_VOLT_IVCMPx_0:   Select pin IVCMPx_0 as compare voltage for CMPx
 *    @arg CMP_CMP_VOLT_IVCMPx_1:   Select pin IVCMPx_1 as compare voltage for CMPx
 *    @arg CMP_CMP_VOLT_IVCMPx_2:   Select pin IVCMPx_2 as compare voltage for CMPx
 *    @arg CMP_CMP_VOLT_VREF:       Select Vref as compare voltage
 * @retval None
 * @note   Can't set compare voltage when CMP analog output enable.
 * @note   Can't set compare voltage when CMP interrupt or event trigger is enable.
 * @note   Clear interrupt flag after compare voltage changed.
 */
void CMP_SetCompareVoltage(CM_CMP_TypeDef *CMPx, uint8_t u8CompareVoltage)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_CMP_VOLT(u8CompareVoltage));

    MODIFY_REG8(CMPx->VSR, CMP_VSR_CVSL, u8CompareVoltage);
    /* Delay about 300ns */
    DDL_DelayUS(1UL);
}

/**
 * @brief  Set reference voltage for CMP
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *    @arg CM_CMP1: CMP unit 1
 *    @arg CM_CMP2: CMP unit 2
 *    @arg CM_CMP3: CMP unit 3
 * @param  [in] u8RefVoltage      Reference voltage @ref CMP_Ref_Voltage
 *    @arg CMP_REF_VOLT_NONE:     No reference voltage input
 *    @arg CMP_REF_VOLT_IVREF1:   Select pin IVREF1 as reference voltage
 *    @arg CMP_REF_VOLT_IVREF2:   Select pin IVREF2 as reference voltage for CMP1 and CMP2
 *    @arg CMP_REF_VOLT_DAC:      Select 8 bit DAC as reference voltage
 * @retval None
 * @note   Can't set reference voltage when CMP analog output enable.
 * @note   Can't set reference voltage when CMP interrupt or event trigger is enable.
 * @note   Clear interrupt flag after reference voltage changed.
 */
void CMP_SetRefVoltage(CM_CMP_TypeDef *CMPx, uint8_t u8RefVoltage)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_REF_VOLT(u8RefVoltage));

    MODIFY_REG8(CMPx->VSR, CMP_VSR_RVSL, u8RefVoltage);
    /* Delay about 300ns */
    DDL_DelayUS(1UL);
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
