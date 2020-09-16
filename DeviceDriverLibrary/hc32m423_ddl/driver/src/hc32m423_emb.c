/**
 *******************************************************************************
 * @file  hc32m423_emb.c
 * @brief This file provides firmware functions to manage the EMB
 *        (Emergency Brake).
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
#include "hc32m423_emb.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_EMB EMB
 * @brief Emergency Brake Driver Library
 * @{
 */

#if (DDL_EMB_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EMB_Local_Macros EMB Local Macros
 * @{
 */

/**
 * @defgroup EMB_Check_Parameters_Validity EMB Check Parameters Validity
 * @{
 */

#define IS_EMB_UNIT(x)                                                         \
(   ((x) == CM_EMB0)                            ||                             \
    ((x) == CM_EMB1))

#define IS_EMB_TMR4_UNIT(x)               ((x) == CM_EMB0)

#define IS_EMB_TMRB_UNIT(x)               ((x) == CM_EMB1)

#define IS_EMB_CMP1_SEL(x)                                                     \
(   ((x) == EMB_CMP1_ENABLE)                    ||                             \
    ((x) == EMB_CMP1_DISABLE))

#define IS_EMB_CMP2_SEL(x)                                                     \
(   ((x) == EMB_CMP2_ENABLE)                    ||                             \
    ((x) == EMB_CMP2_DISABLE))

#define IS_EMB_CMP3_SEL(x)                                                     \
(   ((x) == EMB_CMP3_ENABLE)                    ||                             \
    ((x) == EMB_CMP3_DISABLE))

#define IS_EMB_OSC_SEL(x)                                                      \
(   ((x) == EMB_OSC_ENABLE)                     ||                             \
    ((x) == EMB_OSC_DISABLE))

#define IS_EMB_PORT0_SEL(x)                                                    \
(   ((x) == EMB_PORT0_ENABLE)                   ||                             \
    ((x) == EMB_PORT0_DISABLE))

#define IS_EMB_PORT1_SEL(x)                                                    \
(   ((x) == EMB_PORT1_ENABLE)                   ||                             \
    ((x) == EMB_PORT1_DISABLE))

#define IS_EMB_PORT2_SEL(x)                                                    \
(   ((x) == EMB_PORT2_ENABLE)                   ||                             \
    ((x) == EMB_PORT2_DISABLE))

#define IS_EMB_TMR4_PWM_W_SEL(x)                                               \
(   ((x) == EMB_TMR4_PWM_W_ENABLE)              ||                             \
    ((x) == EMB_TMR4_PWM_W_DISABLE))

#define IS_EMB_TMR4_PWM_V_SEL(x)                                               \
(   ((x) == EMB_TMR4_PWM_V_ENABLE)              ||                             \
    ((x) == EMB_TMR4_PWM_V_DISABLE))

#define IS_EMB_TMR4_PWM_U_SEL(x)                                               \
(   ((x) == EMB_TMR4_PWM_U_ENABLE)              ||                             \
    ((x) == EMB_TMR4_PWM_U_DISABLE))

#define IS_EMB_DETECT_PORT0_LEVEL(x)                                           \
(   ((x) == EMB_DETECT_PORT0_LEVEL_LOW)         ||                             \
    ((x) == EMB_DETECT_PORT0_LEVEL_HIGH))

#define IS_EMB_DETECT_PORT1_LEVEL(x)                                           \
(   ((x) == EMB_DETECT_PORT1_LEVEL_LOW)         ||                             \
    ((x) == EMB_DETECT_PORT1_LEVEL_HIGH))

#define IS_EMB_DETECT_PORT2_LEVEL(x)                                           \
(   ((x) == EMB_DETECT_PORT2_LEVEL_LOW)         ||                             \
    ((x) == EMB_DETECT_PORT2_LEVEL_HIGH))

#define IS_EMB_DETECT_TMR4_PWM_W_LEVEL(x)                                      \
(   ((x) == EMB_DETECT_TMR4_PWM_W_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR4_PWM_W_BOTH_HIGH))

#define IS_EMB_DETECT_TMR4_PWM_V_LEVEL(x)                                      \
(   ((x) == EMB_DETECT_TMR4_PWM_V_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR4_PWM_V_BOTH_HIGH))

#define IS_EMB_DETECT_TMR4_PWM_U_LEVEL(x)                                      \
(   ((x) == EMB_DETECT_TMR4_PWM_U_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR4_PWM_U_BOTH_HIGH))

#define IS_EMB_INT(unit, x)                                                    \
(   ((x) != 0UL)                                &&                             \
    ((IS_EMB_TMR4_UNIT(unit) && (((x) | EMB_TMR4_INT_ALL) == EMB_TMR4_INT_ALL)) || \
     (IS_EMB_TMRB_UNIT(unit) && (((x) | EMB_TMRB_INT_ALL) == EMB_TMRB_INT_ALL))))

#define IS_EMB_CLR_FLAG(unit, x)                                               \
(   ((x) != 0UL)                                &&                             \
    ((IS_EMB_TMR4_UNIT(unit) && (((x) | EMB_TMR4_CLR_FLAG_MASK) == EMB_TMR4_CLR_FLAG_MASK)) || \
     (IS_EMB_TMRB_UNIT(unit) && (((x) | EMB_TMRB_CLR_FLAG_MASK) == EMB_TMRB_CLR_FLAG_MASK))))

#define IS_EMB_STAT(unit, x)                                                   \
(   ((x) != 0UL)                                &&                             \
    ((IS_EMB_TMR4_UNIT(unit) && (((x) | EMB_TMR4_STAT_ALL) == EMB_TMR4_STAT_ALL)) || \
     (IS_EMB_TMRB_UNIT(unit) && (((x) | EMB_TMRB_STAT_ALL) == EMB_TMRB_STAT_ALL))))

#define IS_EMB_PORT0_FILTER_DIV(x)                                             \
(   ((x) == EMB_PORT0_FILTER_NONE)              ||                             \
    ((x) == EMB_PORT0_FILTER_CLK_DIV1)          ||                             \
    ((x) == EMB_PORT0_FILTER_CLK_DIV8)          ||                             \
    ((x) == EMB_PORT0_FILTER_CLK_DIV32)         ||                             \
    ((x) == EMB_PORT0_FILTER_CLK_DIV128))

#define IS_EMB_PORT1_FILTER_DIV(x)                                             \
(   ((x) == EMB_PORT1_FILTER_NONE)              ||                             \
    ((x) == EMB_PORT1_FILTER_CLK_DIV1)          ||                             \
    ((x) == EMB_PORT1_FILTER_CLK_DIV8)          ||                             \
    ((x) == EMB_PORT1_FILTER_CLK_DIV32)         ||                             \
    ((x) == EMB_PORT1_FILTER_CLK_DIV128))

#define IS_EMB_PORT2_FILTER_DIV(x)                                             \
(   ((x) == EMB_PORT2_FILTER_NONE)              ||                             \
    ((x) == EMB_PORT2_FILTER_CLK_DIV1)          ||                             \
    ((x) == EMB_PORT2_FILTER_CLK_DIV8)          ||                             \
    ((x) == EMB_PORT2_FILTER_CLK_DIV32)         ||                             \
    ((x) == EMB_PORT2_FILTER_CLK_DIV128))

#define IS_EMB_TMRB_PWM_POLARITY(x)                                            \
(   ((x) == EMB_TMRB_PWM_NORMAL)                ||                             \
    ((x) == EMB_TMRB_PWM_HIZ)                   ||                             \
    ((x) == EMB_TMRB_PWM_LOW)                   ||                             \
    ((x) == EMB_TMRB_PWM_HIGH))
/**
 * @}
 */
/**
 * @defgroup EMB_Clear_Flag EMB Clear Flag
 * @{
 */
#define EMB_TMR4_CLR_FLAG_MASK              (EMB_FLAG_PWMS  |                  \
                                             EMB_FLAG_CMP   |                  \
                                             EMB_FLAG_OSC   |                  \
                                             EMB_FLAG_PORT0 |                  \
                                             EMB_FLAG_PORT1 |                  \
                                             EMB_FLAG_PORT2)
#define EMB_TMRB_CLR_FLAG_MASK              (EMB_FLAG_CMP   |                  \
                                             EMB_FLAG_OSC   |                  \
                                             EMB_FLAG_PORT0 |                  \
                                             EMB_FLAG_PORT1 |                  \
                                             EMB_FLAG_PORT2)
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
 * @defgroup EMB_Global_Functions EMB Global Functions
 * @{
 */

/**
 * @brief  Initialize EMB for TMR4.
 * @param  [in] EMBx                Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMB0:          EMB group 0 instance register base
 * @param  [in] pstcEmbTmr4Init     Pointer to a @ref stc_emb_tmr4_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcEmbTmr4Init is NULL
 * @note   The EMB group 0(CM_EMB0) only can control TMR4 PWM
 */
en_result_t EMB_Tmr4Init(CM_EMB_TypeDef *EMBx,
                            const stc_emb_tmr4_init_t *pstcEmbTmr4Init)
{
    uint32_t u32Value;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcEmbTmr4Init)
    {
        /* Check parameters */
        DDL_ASSERT(IS_EMB_TMR4_UNIT(EMBx));
        DDL_ASSERT(IS_EMB_CMP1_SEL(pstcEmbTmr4Init->u32Cmp1));
        DDL_ASSERT(IS_EMB_CMP2_SEL(pstcEmbTmr4Init->u32Cmp2));
        DDL_ASSERT(IS_EMB_CMP3_SEL(pstcEmbTmr4Init->u32Cmp3));
        DDL_ASSERT(IS_EMB_OSC_SEL(pstcEmbTmr4Init->u32Osc));
        DDL_ASSERT(IS_EMB_PORT0_SEL(pstcEmbTmr4Init->stcPort0.u32Port));
        DDL_ASSERT(IS_EMB_DETECT_PORT0_LEVEL(pstcEmbTmr4Init->stcPort0.u32PortLevel));
        DDL_ASSERT(IS_EMB_PORT0_FILTER_DIV(pstcEmbTmr4Init->stcPort0.u32PortFilterDiv));
        DDL_ASSERT(IS_EMB_PORT1_SEL(pstcEmbTmr4Init->stcPort1.u32Port));
        DDL_ASSERT(IS_EMB_DETECT_PORT1_LEVEL(pstcEmbTmr4Init->stcPort1.u32PortLevel));
        DDL_ASSERT(IS_EMB_PORT1_FILTER_DIV(pstcEmbTmr4Init->stcPort1.u32PortFilterDiv));
        DDL_ASSERT(IS_EMB_PORT2_SEL(pstcEmbTmr4Init->stcPort2.u32Port));
        DDL_ASSERT(IS_EMB_DETECT_PORT2_LEVEL(pstcEmbTmr4Init->stcPort2.u32PortLevel));
        DDL_ASSERT(IS_EMB_PORT2_FILTER_DIV(pstcEmbTmr4Init->stcPort2.u32PortFilterDiv));
        DDL_ASSERT(IS_EMB_TMR4_PWM_U_SEL(pstcEmbTmr4Init->stcTmr4PwmU.u32Pwm));
        DDL_ASSERT(IS_EMB_DETECT_TMR4_PWM_U_LEVEL(pstcEmbTmr4Init->stcTmr4PwmU.u32PwmLevel));
        DDL_ASSERT(IS_EMB_TMR4_PWM_V_SEL(pstcEmbTmr4Init->stcTmr4PwmV.u32Pwm));
        DDL_ASSERT(IS_EMB_DETECT_TMR4_PWM_V_LEVEL(pstcEmbTmr4Init->stcTmr4PwmV.u32PwmLevel));
        DDL_ASSERT(IS_EMB_TMR4_PWM_W_SEL(pstcEmbTmr4Init->stcTmr4PwmW.u32Pwm));
        DDL_ASSERT(IS_EMB_DETECT_TMR4_PWM_W_LEVEL(pstcEmbTmr4Init->stcTmr4PwmW.u32PwmLevel));

        /* Set default value && clear flag */
        WRITE_REG32(EMBx->SOE, 0UL);
        WRITE_REG32(EMBx->INTEN, 0UL);
        WRITE_REG32(EMBx->STATCLR, (EMB_STATCLR_PWMSFCLR | \
                                    EMB_STATCLR_CMPFCLR | \
                                    EMB_STATCLR_OSFCLR | \
                                    EMB_STATCLR_PORTINFCLR0 | \
                                    EMB_STATCLR_PORTINFCLR1 | \
                                    EMB_STATCLR_PORTINFCLR2));

        /* Set EMB_CTL register */
        u32Value = (pstcEmbTmr4Init->u32Cmp1 | \
                    pstcEmbTmr4Init->u32Cmp2 | \
                    pstcEmbTmr4Init->u32Cmp3 | \
                    pstcEmbTmr4Init->u32Osc | \
                    pstcEmbTmr4Init->stcTmr4PwmW.u32Pwm | \
                    pstcEmbTmr4Init->stcTmr4PwmV.u32Pwm | \
                    pstcEmbTmr4Init->stcTmr4PwmU.u32Pwm | \
                    pstcEmbTmr4Init->stcPort0.u32Port | \
                    pstcEmbTmr4Init->stcPort0.u32PortLevel | \
                    pstcEmbTmr4Init->stcPort0.u32PortFilterDiv | \
                    pstcEmbTmr4Init->stcPort1.u32Port | \
                    pstcEmbTmr4Init->stcPort1.u32PortLevel | \
                    pstcEmbTmr4Init->stcPort1.u32PortFilterDiv | \
                    pstcEmbTmr4Init->stcPort2.u32Port | \
                    pstcEmbTmr4Init->stcPort2.u32PortLevel | \
                    pstcEmbTmr4Init->stcPort2.u32PortFilterDiv);
        WRITE_REG32(EMBx->CTL, u32Value);

        /* Check writing EMB_CTL because EMB_CTL can write once only after reset */
        if (READ_REG32(EMBx->CTL) == u32Value)
        {
            u32Value = (pstcEmbTmr4Init->stcTmr4PwmW.u32PwmLevel | \
                        pstcEmbTmr4Init->stcTmr4PwmV.u32PwmLevel | \
                        pstcEmbTmr4Init->stcTmr4PwmU.u32PwmLevel);
            WRITE_REG32(EMBx->PWMLV, u32Value);

            /* Check writing EMB_PWMLV because EMB_PWMLV can write once only after reset */
            if (READ_REG32(EMBx->PWMLV) == u32Value)
            {
                enRet = Ok;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_emb_tmr4_init_t to default values
 * @param  [out] pstcEmbTmr4Init    Pointer to a @ref stc_emb_tmr4_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcEmbTmr4Init is NULL
 */
en_result_t EMB_Tmr4StructInit(stc_emb_tmr4_init_t *pstcEmbTmr4Init)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcEmbTmr4Init)
    {
        pstcEmbTmr4Init->u32Cmp1 = EMB_CMP1_DISABLE;
        pstcEmbTmr4Init->u32Cmp2 = EMB_CMP2_DISABLE;
        pstcEmbTmr4Init->u32Cmp3 = EMB_CMP3_DISABLE;
        pstcEmbTmr4Init->u32Osc = EMB_OSC_DISABLE;
        pstcEmbTmr4Init->stcPort0.u32Port = EMB_PORT0_DISABLE;
        pstcEmbTmr4Init->stcPort0.u32PortLevel = EMB_DETECT_PORT0_LEVEL_HIGH;
        pstcEmbTmr4Init->stcPort0.u32PortFilterDiv = EMB_PORT0_FILTER_NONE;
        pstcEmbTmr4Init->stcPort1.u32Port = EMB_PORT1_DISABLE;
        pstcEmbTmr4Init->stcPort1.u32PortLevel = EMB_DETECT_PORT1_LEVEL_HIGH;
        pstcEmbTmr4Init->stcPort1.u32PortFilterDiv = EMB_PORT1_FILTER_NONE;
        pstcEmbTmr4Init->stcPort2.u32Port = EMB_PORT2_DISABLE;
        pstcEmbTmr4Init->stcPort2.u32PortLevel = EMB_DETECT_PORT2_LEVEL_HIGH;
        pstcEmbTmr4Init->stcPort2.u32PortFilterDiv = EMB_PORT2_FILTER_NONE;
        pstcEmbTmr4Init->stcTmr4PwmU.u32Pwm = EMB_TMR4_PWM_U_DISABLE;
        pstcEmbTmr4Init->stcTmr4PwmU.u32PwmLevel = EMB_DETECT_TMR4_PWM_U_BOTH_LOW;
        pstcEmbTmr4Init->stcTmr4PwmV.u32Pwm = EMB_TMR4_PWM_V_DISABLE;
        pstcEmbTmr4Init->stcTmr4PwmV.u32PwmLevel = EMB_DETECT_TMR4_PWM_V_BOTH_LOW;
        pstcEmbTmr4Init->stcTmr4PwmW.u32Pwm = EMB_TMR4_PWM_W_DISABLE;
        pstcEmbTmr4Init->stcTmr4PwmW.u32PwmLevel = EMB_DETECT_TMR4_PWM_W_BOTH_LOW;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Initialize EMB for TMRB.
 * @param  [in] EMBx                Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMB1:          EMB group 1 instance register base
 * @param  [in] pstcEmbTmrbInit     Pointer to a @ref stc_emb_tmrb_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcEmbTmrbInit is NULL
 * @note   The EMB group 1(CM_EMB1) only can control TMR4 PWM
 */
en_result_t EMB_TmrbInit(CM_EMB_TypeDef *EMBx,
                            const stc_emb_tmrb_init_t *pstcEmbTmrbInit)
{
    uint32_t u32Value;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcEmbTmrbInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_EMB_TMRB_UNIT(EMBx));
        DDL_ASSERT(IS_EMB_CMP1_SEL(pstcEmbTmrbInit->u32Cmp1));
        DDL_ASSERT(IS_EMB_CMP2_SEL(pstcEmbTmrbInit->u32Cmp2));
        DDL_ASSERT(IS_EMB_CMP3_SEL(pstcEmbTmrbInit->u32Cmp3));
        DDL_ASSERT(IS_EMB_OSC_SEL(pstcEmbTmrbInit->u32Osc));
        DDL_ASSERT(IS_EMB_PORT0_SEL(pstcEmbTmrbInit->stcPort0.u32Port));
        DDL_ASSERT(IS_EMB_DETECT_PORT0_LEVEL(pstcEmbTmrbInit->stcPort0.u32PortLevel));
        DDL_ASSERT(IS_EMB_PORT0_FILTER_DIV(pstcEmbTmrbInit->stcPort0.u32PortFilterDiv));
        DDL_ASSERT(IS_EMB_PORT1_SEL(pstcEmbTmrbInit->stcPort1.u32Port));
        DDL_ASSERT(IS_EMB_DETECT_PORT1_LEVEL(pstcEmbTmrbInit->stcPort1.u32PortLevel));
        DDL_ASSERT(IS_EMB_PORT1_FILTER_DIV(pstcEmbTmrbInit->stcPort1.u32PortFilterDiv));
        DDL_ASSERT(IS_EMB_PORT2_SEL(pstcEmbTmrbInit->stcPort2.u32Port));
        DDL_ASSERT(IS_EMB_DETECT_PORT2_LEVEL(pstcEmbTmrbInit->stcPort2.u32PortLevel));
        DDL_ASSERT(IS_EMB_PORT2_FILTER_DIV(pstcEmbTmrbInit->stcPort2.u32PortFilterDiv));
        DDL_ASSERT(IS_EMB_TMRB_PWM_POLARITY(pstcEmbTmrbInit->u32EmbPolarity));

        /* Set default value && clear flag */
        WRITE_REG32(EMBx->SOE, 0UL);
        WRITE_REG32(EMBx->INTEN, 0UL);
        WRITE_REG32(EMBx->STATCLR, (EMB_STATCLR_CMPFCLR | \
                                    EMB_STATCLR_OSFCLR | \
                                    EMB_STATCLR_PORTINFCLR0 | \
                                    EMB_STATCLR_PORTINFCLR1 | \
                                    EMB_STATCLR_PORTINFCLR2));

        u32Value = (pstcEmbTmrbInit->u32Cmp1 | \
                    pstcEmbTmrbInit->u32Cmp2 | \
                    pstcEmbTmrbInit->u32Cmp3 | \
                    pstcEmbTmrbInit->u32Osc | \
                    pstcEmbTmrbInit->stcPort0.u32Port | \
                    pstcEmbTmrbInit->stcPort0.u32PortLevel | \
                    pstcEmbTmrbInit->stcPort0.u32PortFilterDiv | \
                    pstcEmbTmrbInit->stcPort1.u32Port | \
                    pstcEmbTmrbInit->stcPort1.u32PortLevel | \
                    pstcEmbTmrbInit->stcPort1.u32PortFilterDiv | \
                    pstcEmbTmrbInit->stcPort2.u32Port | \
                    pstcEmbTmrbInit->stcPort2.u32PortLevel | \
                    pstcEmbTmrbInit->stcPort2.u32PortFilterDiv);
        WRITE_REG32(EMBx->CTL, u32Value);

        /* Check writing EMB_CTL because EMB_CTL can write once only after reset */
        if (READ_REG32(EMBx->CTL) == u32Value)
        {
            WRITE_REG32(EMBx->ECSR, pstcEmbTmrbInit->u32EmbPolarity);
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_emb_tmrb_init_t to default values
 * @param  [out] pstcEmbTmrbInit    Pointer to a @ref stc_emb_tmrb_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcEmbTmrbInit is NULL
 */
en_result_t EMB_TmrbStructInit(stc_emb_tmrb_init_t *pstcEmbTmrbInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcEmbTmrbInit)
    {
        pstcEmbTmrbInit->u32Cmp1 = EMB_CMP1_DISABLE;
        pstcEmbTmrbInit->u32Cmp2 = EMB_CMP2_DISABLE;
        pstcEmbTmrbInit->u32Cmp3 = EMB_CMP3_DISABLE;
        pstcEmbTmrbInit->u32Osc = EMB_OSC_DISABLE;
        pstcEmbTmrbInit->stcPort0.u32Port = EMB_PORT0_DISABLE;
        pstcEmbTmrbInit->stcPort0.u32PortLevel = EMB_DETECT_PORT0_LEVEL_HIGH;
        pstcEmbTmrbInit->stcPort0.u32PortFilterDiv = EMB_PORT0_FILTER_NONE;
        pstcEmbTmrbInit->stcPort1.u32Port = EMB_PORT1_DISABLE;
        pstcEmbTmrbInit->stcPort1.u32PortLevel = EMB_DETECT_PORT1_LEVEL_HIGH;
        pstcEmbTmrbInit->stcPort1.u32PortFilterDiv = EMB_PORT1_FILTER_NONE;
        pstcEmbTmrbInit->stcPort2.u32Port = EMB_PORT2_DISABLE;
        pstcEmbTmrbInit->stcPort2.u32PortLevel = EMB_DETECT_PORT2_LEVEL_HIGH;
        pstcEmbTmrbInit->stcPort2.u32PortFilterDiv = EMB_PORT2_FILTER_NONE;
        pstcEmbTmrbInit->u32EmbPolarity = EMB_TMRB_PWM_NORMAL;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize EMB function
 * @param  [in] EMBx                Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMB0:          EMB group 0 instance register base
 *           @arg CM_EMB1:          EMB group 1 instance register base
 * @retval None
 * @note   The feature for detecting TMR PWM is supported only by EMB group 0(CM_EMB0).
 */
void EMB_DeInit(CM_EMB_TypeDef *EMBx)
{
    uint32_t u32ClearFlag = (EMB_STATCLR_CMPFCLR | \
                             EMB_STATCLR_OSFCLR | \
                             EMB_STATCLR_PORTINFCLR0 | \
                             EMB_STATCLR_PORTINFCLR1 | \
                             EMB_STATCLR_PORTINFCLR2);

    /* Check parameters */
    DDL_ASSERT(IS_EMB_UNIT(EMBx));

    /* Configures the registers to reset value. */
    WRITE_REG32(EMBx->SOE, 0UL);
    WRITE_REG32(EMBx->INTEN, 0UL);

    if (IS_EMB_TMR4_UNIT(EMBx))
    {
        u32ClearFlag |= EMB_STATCLR_PWMSFCLR;
        WRITE_REG32(EMBx->ECSR, 0UL);
    }

    WRITE_REG32(EMBx->STATCLR, u32ClearFlag);
}

/**
 * @brief  Enable or disable the specified EMB interrupt function
 * @param  [in] EMBx                Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMB0:          EMB group 0 instance register base
 *           @arg CM_EMB1:          EMB group 1 instance register base
 * @param  [in] u32IntType          EMB interrupt
 *         This parameter can be any composed value of the following values:
 *           @arg EMB_INT_PWMS:     PWM same phase event interrupt
 *           @arg EMB_INT_CMP:      CMP result event interrupt
 *           @arg EMB_INT_OSC:      OSC stop event interrupt
 *           @arg EMB_INT_PORT0:    Port0 input event interrupt
 *           @arg EMB_INT_PORT1:    Port1 input event interrupt
 *           @arg EMB_INT_PORT2:    Port2 input event interrupt
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified EMB interrupt function
 *           @arg Disable:          Disable the specified EMB interrupt function
 * @note   The feature for detecting TMR PWM is supported only by EMB group 0(CM_EMB0).
 */
void EMB_IntCmd(CM_EMB_TypeDef *EMBx,
                    uint32_t u32IntType,
                    en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_EMB_UNIT(EMBx));
    DDL_ASSERT(IS_EMB_INT(EMBx, u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(EMBx->INTEN, u32IntType);
    }
    else
    {
        CLEAR_REG32_BIT(EMBx->INTEN, u32IntType);
    }
}

/**
 * @brief  Get EMB status
 * @param  [in] EMBx                Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMB0:          EMB group 0 instance register base
 *           @arg CM_EMB1:          EMB group 1 instance register base
 * @param  [in] u32Flag             EMB flag
 *         This parameter can be any composed value of the following values:
 *           @arg EMB_FLAG_PWMS:    PWM same phase control flag
 *           @arg EMB_FLAG_CMP:     CMP comapre control flag
 *           @arg EMB_FLAG_OSC:     OSC stop control flag
 *           @arg EMB_FLAG_PORT0:   EMB Port0 input control flag
 *           @arg EMB_FLAG_PORT1:   EMB Port1 input control flag
 *           @arg EMB_FLAG_PORT2:   EMB Port2 input control flag
 * @note   The feature for detecting TMR PWM is supported only by EMB group 0(CM_EMB0).
 */
void EMB_ClearStatus(CM_EMB_TypeDef *EMBx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_EMB_UNIT(EMBx));
    DDL_ASSERT(IS_EMB_CLR_FLAG(EMBx, u32Flag));

    SET_REG32_BIT(EMBx->STATCLR, u32Flag);
}

/**
 * @brief  Get EMB status
 * @param  [in] EMBx                Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMB0:          EMB group 0 instance register base
 *           @arg CM_EMB1:          EMB group 1 instance register base
 * @param  [in] u32Flag             EMB flag
 *         This parameter can be any composed value of the following values:
 *           @arg EMB_FLAG_PWMS:    PWM same phase control flag
 *           @arg EMB_FLAG_CMP:     CMP comapre control flag
 *           @arg EMB_FLAG_OSC:     OSC stop control flag
 *           @arg EMB_FLAG_PORT0:   EMB Port0 input control flag
 *           @arg EMB_FLAG_PORT1:   EMB Port1 input control flag
 *           @arg EMB_FLAG_PORT2:   EMB Port2 input control flag
 *           @arg EMB_STAT_PWMS:    PWM same phase control state
 *           @arg EMB_STAT_CMP:     CMP comapre control state
 *           @arg EMB_STAT_OSC:     OSC stop control state
 *           @arg EMB_STAT_PORT1:   EMB Port1 input control state
 *           @arg EMB_STAT_PORT2:   EMB Port2 input control state
 *           @arg EMB_STAT_PORT3:   EMB Port3 input control state
 * @retval An en_flag_status_t enumeration value:
 *           - Set:   Any bit of the composed flag is set.
 *           - Reset: All bit of the composed flag is reset.
 * @note   The feature for detecting TMR PWM is supported only by EMB group 0(CM_EMB0).
 */
en_flag_status_t EMB_GetStatus(const CM_EMB_TypeDef *EMBx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_EMB_UNIT(EMBx));
    DDL_ASSERT(IS_EMB_STAT(EMBx, u32Flag));

    return READ_REG32_BIT(EMBx->STAT, u32Flag) ? Set : Reset;
}

/**
 * @brief  Start/stop EMB software brake
 * @param  [in] EMBx                Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMB0:          EMB group 0 instance register base
 *           @arg CM_EMB1:          EMB group 1 instance register base
 * @param  [in] enNewState          The function new state
 *           @arg Enable:           Start EMB software brake
 *           @arg Disable:          Stop EMB software brake
 * @retval None
 */
void EMB_SWBrake(CM_EMB_TypeDef *EMBx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_EMB_UNIT(EMBx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(EMBx->SOE, enNewState);
}

/**
 * @brief  Set TMRB PWM polarity when EMB occur
 * @param  [in] EMBx                Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMB1:          EMB group 1 instance register base
 * @param  [in] u32Polarity         EMB flag
 *         This parameter can be one of the following values:
 *           @arg EMB_TMRB_PWM_NORMAL: TIMB_1_PWMn(n=1~4) output normal
 *           @arg EMB_TMRB_PWM_HIZ:    TIMB_1_PWMn(n=1~4) output Hi-z
 *           @arg EMB_TMRB_PWM_LOW:    TIMB_1_PWMn(n=1~4) output low level
 *           @arg EMB_TMRB_PWM_HIGH:   TIMB_1_PWMn(n=1~4) output high level
 * @note   The feature for TMRB PWM polarity is supported only by EMB group 1(CM_EMB1).
 */
void EMB_SetTmrbPwmPolarity(CM_EMB_TypeDef *EMBx, uint32_t u32Polarity)
{
    /* Check parameters */
    DDL_ASSERT(IS_EMB_TMRB_UNIT(EMBx));
    DDL_ASSERT(IS_EMB_TMRB_PWM_POLARITY(u32Polarity));

    WRITE_REG32(EMBx->ECSR, u32Polarity);
}

/**
 * @}
 */

#endif /* DDL_EMB_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
