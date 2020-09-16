/**
 *******************************************************************************
 * @file  hc32m423_tmra.c
 * @brief This file provides firmware functions to manage the TMRA(TimerA).
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
#include "hc32m423_tmra.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TMRA TMRA
 * @brief TMRA Driver Library
 * @{
 */

#if (DDL_TMRA_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMRA_Local_Macros TMRA Local Macros
 * @{
 */

/* Maximum value of TMRA PWM channel*/
#define TMRA_MAX_CH_NUM                 (2UL)

/* TMRA Register Combination Mask */
#define TMRA_BCONR_BSE_MASK             (TMRA_BCONR_BSE1  | TMRA_BCONR_BSE0)
#define TMRA_CCONR_HICP_MASK            (TMRA_CCONR_HICP2 | TMRA_CCONR_HICP1 | TMRA_CCONR_HICP0)
#define TMRA_HCONR_HSTA_MASK            (TMRA_HCONR_HSTA2 | TMRA_HCONR_HSTA1 | TMRA_HCONR_HSTA0)
#define TMRA_HCONR_HSTP_MASK            (TMRA_HCONR_HSTP2 | TMRA_HCONR_HSTP1 | TMRA_HCONR_HSTP0)
#define TMRA_HCONR_HCLE_MASK            (TMRA_HCONR_HCLE4 | TMRA_HCONR_HCLE3 | TMRA_HCONR_HCLE2 | \
                                         TMRA_HCONR_HCLE1 | TMRA_HCONR_HCLE0)

/* The flag, interrupt, event and count condition of special unit (unit1 and unit2) */
#define TMRA_SPEC_UNIT_CNT_UP_COND      (TMRA_CNT_UP_COND_CLKBL_CLKAR | TMRA_CNT_UP_COND_CLKBL_CLKAF | \
                                         TMRA_CNT_UP_COND_TRIGR       | TMRA_CNT_UP_COND_TRIGF       | \
                                         TMRA_CNT_UP_COND_EVT         | TMRA_CNT_UP_COND_SYM_OVF     | \
                                         TMRA_CNT_UP_COND_SYM_UDF)
#define TMRA_SPEC_UNIT_CNT_DOWN_COND    (TMRA_CNT_DOWN_COND_CLKBL_CLKAR | TMRA_CNT_DOWN_COND_CLKBL_CLKAF | \
                                         TMRA_CNT_DOWN_COND_TRIGR       | TMRA_CNT_DOWN_COND_TRIGF       | \
                                         TMRA_CNT_DOWN_COND_EVT         | TMRA_CNT_DOWN_COND_SYM_OVF     | \
                                         TMRA_CNT_DOWN_COND_SYM_UDF)
#define TMRA_SPEC_UNIT_FLAG             (TMRA_FLAG_OVF | TMRA_FLAG_UDF | TMRA_FLAG_CMP1)
#define TMRA_SPEC_UNIT_INT              (TMRA_INT_OVF  | TMRA_INT_UDF  | TMRA_INT_CMP1)
#define TMRA_SPRC_UNIT_EVT              (TMRA_EVT_CMP1)

/* Get the specified Compare/Capture register address of the TMRA unit */
#define TMRA_CMPAR(__UNIT__, __CH__)    ((uint32_t)(&((__UNIT__)->CMPAR1)) + ((uint32_t)(__CH__) << 2U))
#define TMRA_CCONR(__UNIT__, __CH__)    ((uint32_t)(&((__UNIT__)->CCONR1)) + ((uint32_t)(__CH__) << 2U))
#define TMRA_PCONR(__UNIT__, __CH__)    ((uint32_t)(&((__UNIT__)->PCONR1)) + ((uint32_t)(__CH__) << 2U))
#define TMRA_HTSSR(__USAGE__)           ((uint32_t)(&(CM_AOS->TMRA0_HTSSR)) + ((uint32_t)(__USAGE__) << 2U))

/**
 * @defgroup TMRA_Check_Parameters_Validity TMRA Check Parameters Validity
 * @{
 */
#define IS_TMRA_UNIT(x)                                                        \
(   ((x) == CM_TMRA_1)                          ||                             \
    ((x) == CM_TMRA_2)                          ||                             \
    ((x) == CM_TMRA_3)                          ||                             \
    ((x) == CM_TMRA_4))

#define IS_TMRA_BUF_UNIT(x)                                                    \
(   ((x) == CM_TMRA_3)                          ||                             \
    ((x) == CM_TMRA_4))

#define IS_TMRA_SYNC_UNIT(x)                                                   \
(   ((x) == CM_TMRA_2)                          ||                             \
    ((x) == CM_TMRA_4))

#define IS_TMRA_COMB_UNIT_CH(unit, ch)                                         \
(   ((((unit) == CM_TMRA_1) || ((unit) == CM_TMRA_2))       &&                 \
     ((ch) == TMRA_CH1))                                            ||         \
    ((((unit) == CM_TMRA_3) || ((unit) == CM_TMRA_4))       &&                 \
     (((ch) == TMRA_CH1)    || ((ch) == TMRA_CH2))))

#define IS_TMRA_CLK_DIV(x)                                                     \
(   ((x) == TMRA_CLK_DIV1)                      ||                             \
    ((x) == TMRA_CLK_DIV2)                      ||                             \
    ((x) == TMRA_CLK_DIV4)                      ||                             \
    ((x) == TMRA_CLK_DIV8)                      ||                             \
    ((x) == TMRA_CLK_DIV16)                     ||                             \
    ((x) == TMRA_CLK_DIV32)                     ||                             \
    ((x) == TMRA_CLK_DIV64)                     ||                             \
    ((x) == TMRA_CLK_DIV128)                    ||                             \
    ((x) == TMRA_CLK_DIV256)                    ||                             \
    ((x) == TMRA_CLK_DIV512)                    ||                             \
    ((x) == TMRA_CLK_DIV1024))

#define IS_TMRA_CNT_MD(x)                                                      \
(   ((x) == TMRA_MD_SAWTOOTH)                   ||                             \
    ((x) == TMRA_MD_TRIANGLE))

#define IS_TMRA_CNT_DIR(x)                                                     \
(   ((x) == TMRA_DIR_DOWN)                      ||                             \
    ((x) == TMRA_DIR_UP))

#define IS_TMRA_CNT_UP_COND(unit, cond)                                        \
(   ((cond) != 0U)                                                  &&         \
    (((((unit) == CM_TMRA_3) || ((unit) == CM_TMRA_4))      &&                 \
     (((cond) | TMRA_CNT_UP_COND_ALL) == TMRA_CNT_UP_COND_ALL))     ||         \
    ((((unit) == CM_TMRA_1)  || ((unit) == CM_TMRA_2))      &&                 \
     (((cond) | TMRA_SPEC_UNIT_CNT_UP_COND) == TMRA_SPEC_UNIT_CNT_UP_COND))))

#define IS_TMRA_CNT_DOWN_COND(unit, cond)                                      \
(   ((cond) != 0U)                                                  &&         \
    (((((unit) == CM_TMRA_3) || ((unit) == CM_TMRA_4))      &&                 \
     (((cond) | TMRA_CNT_DOWN_COND_ALL) == TMRA_CNT_DOWN_COND_ALL)) ||         \
    ((((unit) == CM_TMRA_1)  || ((unit) == CM_TMRA_2))      &&                 \
     (((cond) | TMRA_SPEC_UNIT_CNT_DOWN_COND) == TMRA_SPEC_UNIT_CNT_DOWN_COND))))

#define IS_TMRA_PWM_POLARITY(state, polarity)                                  \
(   ((((state) == TMRA_PWM_CNT_MATCH) ||                                       \
      ((state) == TMRA_PWM_CNT_PERIOD))                     &&                 \
     (((polarity) == TMRA_PWM_LOW)    ||                                       \
      ((polarity) == TMRA_PWM_HIGH)   ||                                       \
      ((polarity) == TMRA_PWM_HOLD)   ||                                       \
      ((polarity) == TMRA_PWM_INVT)))                               ||         \
    ((((state) == TMRA_PWM_CNT_START) ||                                       \
      ((state) == TMRA_PWM_CNT_STOP))                       &&                 \
     (((polarity) == TMRA_PWM_LOW)    ||                                       \
      ((polarity) == TMRA_PWM_HIGH)   ||                                       \
      ((polarity) == TMRA_PWM_HOLD))))

#define IS_TMRA_FORCE_POLARITY(x)                                              \
(   ((x) == TMRA_PWM_FORCE_INVD)                ||                             \
    ((x) == TMRA_PWM_FORCE_LOW)                 ||                             \
    ((x) == TMRA_PWM_FORCE_HIGH))

#define IS_TMRA_BUF_TRANS_COND(x)                                              \
(   ((x) == TMRA_BUF_COND_OVF_UDF_CLR)          ||                             \
    ((x) == TMRA_BUF_COND_PEAK)                 ||                             \
    ((x) == TMRA_BUF_COND_VALLEY)               ||                             \
    ((x) == TMRA_BUF_COND_PEAK_VALLEY))

#define IS_TMRA_INPUT_PIN(unit, pin)                                           \
(   ((((unit) == CM_TMRA_3)    || ((unit) == CM_TMRA_4))    &&                 \
     (((pin) == TMRA_PIN_PWM1) ||                                              \
      ((pin) == TMRA_PIN_PWM2) ||                                              \
      ((pin) == TMRA_PIN_CLKB) ||                                              \
      ((pin) == TMRA_PIN_CLKA) ||                                              \
      ((pin) == TMRA_PIN_TRIG)))                                    ||         \
    ((((unit) == CM_TMRA_1)    || ((unit) == CM_TMRA_2))    &&                 \
     (((pin) == TMRA_PIN_PWM1) ||                                              \
      ((pin) == TMRA_PIN_CLKA) ||                                              \
      ((pin) == TMRA_PIN_TRIG))))

#define IS_TMRA_FILTER_CLK_DIV(x)                                              \
(   ((x) == TMRA_FILTER_CLK_DIV1)               ||                             \
    ((x) == TMRA_FILTER_CLK_DIV4)               ||                             \
    ((x) == TMRA_FILTER_CLK_DIV16)              ||                             \
    ((x) == TMRA_FILTER_CLK_DIV64))

#define IS_TMRA_FUNC_MD(x)                                                     \
(   ((x) == TMRA_FUNC_CMP)                      ||                             \
    ((x) == TMRA_FUNC_CAPT))

#define IS_TMRA_CAPT_COND(x)                                                   \
(   ((x) != 0U)                                 &&                             \
    (((x) | TMRA_CAPT_COND_ALL) == TMRA_CAPT_COND_ALL))

#define IS_TMRA_HW_START_COND(x)                                               \
(   ((x) != 0U)                                 &&                             \
    (((x) | TMRA_START_COND_ALL) == TMRA_START_COND_ALL))

#define IS_TMRA_HW_STOP_COND(x)                                                \
(   ((x) != 0U)                                 &&                             \
    (((x) | TMRA_STOP_COND_ALL) == TMRA_STOP_COND_ALL))

#define IS_TMRA_HW_CLR_COND(x)                                                 \
(   ((x) != 0U)                                 &&                             \
    (((x) | TMRA_CLR_COND_ALL) == TMRA_CLR_COND_ALL))

#define IS_TMRA_FLAG(unit, flag)                                               \
(   ((((unit) == CM_TMRA_3) || ((unit) == CM_TMRA_4))       &&                 \
     (((flag) | TMRA_FLAG_ALL) == TMRA_FLAG_ALL))                   ||         \
    ((((unit) == CM_TMRA_1)  || ((unit) == CM_TMRA_2))      &&                 \
     (((flag) | TMRA_SPEC_UNIT_FLAG) == TMRA_SPEC_UNIT_FLAG)))

#define IS_TMRA_INT(unit, interrupt)                                           \
(   ((((unit) == CM_TMRA_3) || ((unit) == CM_TMRA_4))       &&                 \
     (((interrupt) | TMRA_INT_ALL) == TMRA_INT_ALL))                ||         \
    ((((unit) == CM_TMRA_1)  || ((unit) == CM_TMRA_2))      &&                 \
     (((interrupt) | TMRA_SPEC_UNIT_INT) == TMRA_SPEC_UNIT_INT)))

#define IS_TMRA_EVENT(unit, evt)                                               \
(   ((((unit) == CM_TMRA_3) || ((unit) == CM_TMRA_4))       &&                 \
     (((evt) | TMRA_EVT_ALL) == TMRA_EVT_ALL))                      ||         \
    ((((unit) == CM_TMRA_1)  || ((unit) == CM_TMRA_2))      &&                 \
     (((evt) | TMRA_SPRC_UNIT_EVT) == TMRA_SPRC_UNIT_EVT)))

#define IS_TMRA_EVT_USAGE(x)                                                   \
(   ((x) == TMRA_EVT_USAGE_CNT)                 ||                             \
    ((x) == TMRA_EVT_USAGE_CAPT))

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
 * @defgroup TMRA_Global_Functions TMRA Global Functions
 * @{
 */

/**
 * @brief  De-initializes the TMRA peripheral.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @retval None
 */
void TMRA_DeInit(CM_TMRA_TypeDef *TMRAx)
{
    uint32_t i;
    uint32_t u32ChNum;
    __IO uint16_t *CMPAR;
    __IO uint16_t *CCONR;
    __IO uint16_t *PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    /* Configures the registers to reset value. */
    WRITE_REG16(TMRAx->BCSTR, 0x0002U);
    WRITE_REG16(TMRAx->ICONR, 0x0000U);
    WRITE_REG16(TMRAx->ECONR, 0x0000U);
    WRITE_REG16(TMRAx->CNTER, 0x0000U);
    WRITE_REG16(TMRAx->PERAR, 0xFFFFU);
    WRITE_REG16(TMRAx->FCONR, 0x0000U);
    WRITE_REG16(TMRAx->STFLR, 0x0000U);
    WRITE_REG16(TMRAx->HCONR, 0x0000U);
    WRITE_REG16(TMRAx->HCUPR, 0x0000U);
    WRITE_REG16(TMRAx->HCDOR, 0x0000U);

    if ((CM_TMRA_3 == TMRAx) || (CM_TMRA_4 == TMRAx))
    {
        u32ChNum = TMRA_MAX_CH_NUM;
        WRITE_REG16(TMRAx->BCONR, 0x0000U);
    }
    else
    {
        u32ChNum = 1UL;
    }
    for (i = 0U; i < u32ChNum; i++)
    {
        CMPAR = (__IO uint16_t *)TMRA_CMPAR(TMRAx, i);
        WRITE_REG16(*CMPAR, 0xFFFFU);
        CCONR = (__IO uint16_t *)TMRA_CCONR(TMRAx, i);
        WRITE_REG16(*CCONR, 0x0000U);
        PCONR = (__IO uint16_t *)TMRA_PCONR(TMRAx, i);
        WRITE_REG16(*PCONR, 0x0000U);
    }

    WRITE_REG32(CM_AOS->TMRA0_HTSSR, EVT_MAX);
    WRITE_REG32(CM_AOS->TMRA1_HTSSR, EVT_MAX);
}

/**
 * @brief  Initializes TMRA base function.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] pstcTmraInit            Pointer to a @ref stc_tmra_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initializes success
 *           - ErrorInvalidParameter: pstcTmraInit == NULL
 */
en_result_t TMRA_Init(CM_TMRA_TypeDef *TMRAx, const stc_tmra_init_t *pstcTmraInit)
{
    en_result_t enRet = Ok;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    if (NULL == pstcTmraInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMRA_CLK_DIV(pstcTmraInit->u16ClockDiv));
        DDL_ASSERT(IS_TMRA_CNT_MD(pstcTmraInit->u16CountMode));
        DDL_ASSERT(IS_TMRA_CNT_DIR(pstcTmraInit->u16CountDir));

        WRITE_REG16(TMRAx->PERAR, pstcTmraInit->u16PeriodValue);
        MODIFY_REG16(TMRAx->BCSTR,
                     (TMRA_BCSTR_CKDIV | TMRA_BCSTR_DIR | TMRA_BCSTR_MODE),
                     (pstcTmraInit->u16ClockDiv | pstcTmraInit->u16CountDir | pstcTmraInit->u16CountMode));

    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmra_init_t to default values.
 * @param  [out] pstcTmraInit           Pointer to a @ref stc_tmra_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: The structure initializes success
 *           - ErrorInvalidParameter: pstcTmraInit == NULL
 */
en_result_t TMRA_StructInit(stc_tmra_init_t *pstcTmraInit)
{
    en_result_t enRet = Ok;

    /* Check parameters */
    if (NULL == pstcTmraInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcTmraInit->u16ClockDiv    = TMRA_CLK_DIV1;
        pstcTmraInit->u16CountMode   = TMRA_MD_SAWTOOTH;
        pstcTmraInit->u16CountDir    = TMRA_DIR_DOWN;
        pstcTmraInit->u16PeriodValue = 0xFFFFU;
    }

    return enRet;
}

/**
 * @brief  Set the count value.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Value                Count value (between 0 and 0xFFFF)
 * @retval None
 */
void TMRA_SetCountValue(CM_TMRA_TypeDef *TMRAx, uint16_t u16Value)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    WRITE_REG16(TMRAx->CNTER, u16Value);
}

/**
 * @brief  Get the current count value.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @retval uint16_t                     Current count value (between 0 and 0xFFFF)
 */
uint16_t TMRA_GetCountValue(const CM_TMRA_TypeDef *TMRAx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    return READ_REG16(TMRAx->CNTER);
}

/**
 * @brief  Set the period value.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Value                Period value (between 0 and 0xFFFF)
 * @retval None
 */
void TMRA_SetPeriodValue(CM_TMRA_TypeDef *TMRAx, uint16_t u16Value)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    WRITE_REG16(TMRAx->PERAR, u16Value);
}

/**
 * @brief  Get the period value.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @retval uint16_t                     Period value (between 0 and 0xFFFF)
 */
uint16_t TMRA_GetPeriodValue(const CM_TMRA_TypeDef *TMRAx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    return READ_REG16(TMRAx->PERAR);
}

/**
 * @brief  Set the compare value of the TMRA pwm channel.
 * @note   TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Ch                   TMRA pwm channel
           This parameter can be one of the following values:
             @arg TMRA_CH1:             TMRA pwm Channel 1
             @arg TMRA_CH2:             TMRA pwm Channel 2
 * @param  [in] u16Value                Compare value (between 0 and 0xFFFF)
 * @retval None
 */
void TMRA_SetCompareValue(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Value)
{
    __IO uint16_t *CMPAR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_COMB_UNIT_CH(TMRAx, u32Ch));

    CMPAR = (__IO uint16_t *)TMRA_CMPAR(TMRAx, u32Ch);
    WRITE_REG16(*CMPAR, u16Value);
}

/**
 * @brief  Get the compare value of the TMRA pwm channel.
 * @note   TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Ch                   TMRA pwm channel
           This parameter can be one of the following values:
             @arg TMRA_CH1:             TMRA pwm Channel 1
             @arg TMRA_CH2:             TMRA pwm Channel 2
 * @retval uint16_t                     Current compare value (between 0 and 0xFFFF)
 */
uint16_t TMRA_GetCompareValue(const CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch)
{
    __IO uint16_t *CMPAR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_COMB_UNIT_CH(TMRAx, u32Ch));

    CMPAR = (__IO uint16_t *)TMRA_CMPAR(TMRAx, u32Ch);
    return READ_REG16(*CMPAR);
}

/**
 * @brief  Set the clock division factor.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Div                  Division factor
 *         This parameter can be one of the following values:
 *           @arg TMRA_CLK_DIV1:        PCLK1
 *           @arg TMRA_CLK_DIV2:        PCLK1/2
 *           @arg TMRA_CLK_DIV4:        PCLK1/4
 *           @arg TMRA_CLK_DIV8:        PCLK1/8
 *           @arg TMRA_CLK_DIV16:       PCLK1/16
 *           @arg TMRA_CLK_DIV32:       PCLK1/32
 *           @arg TMRA_CLK_DIV64:       PCLK1/64
 *           @arg TMRA_CLK_DIV128:      PCLK1/128
 *           @arg TMRA_CLK_DIV256:      PCLK1/256
 *           @arg TMRA_CLK_DIV512:      PCLK1/512
 *           @arg TMRA_CLK_DIV1024:     PCLK1/1024
 * @retval None
 */
void TMRA_SetClockDiv(CM_TMRA_TypeDef *TMRAx, uint16_t u16Div)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CLK_DIV(u16Div));

    MODIFY_REG16(TMRAx->BCSTR, TMRA_BCSTR_CKDIV, u16Div);
}

/**
 * @brief  Set the counting direction.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Dir                  Counting direction
 *         This parameter can be one of the following values:
 *           @arg TMRA_DIR_DOWN:        Count down
 *           @arg TMRA_DIR_UP:          Count up
 * @retval None
 */
void TMRA_SetCountDir(CM_TMRA_TypeDef *TMRAx, uint16_t u16Dir)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CNT_DIR(u16Dir));

    MODIFY_REG16(TMRAx->BCSTR, TMRA_BCSTR_DIR, u16Dir);
}

/**
 * @brief  Get the counting direction.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @retval uint16_t                     Current counting direction
 */
uint16_t TMRA_GetCountDir(const CM_TMRA_TypeDef *TMRAx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    return READ_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_DIR);
}

/**
 * @brief  Set the counting mode.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Mode                 Counting mode
 *         This parameter can be one of the following values:
 *           @arg TMRA_MD_SAWTOOTH:     Count mode is sawtooth wave
 *           @arg TMRA_MD_TRIANGLE:     Count mode is triangle wave
 * @retval None
 */
void TMRA_SetCountMode(CM_TMRA_TypeDef *TMRAx, uint16_t u16Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CNT_MD(u16Mode));

    MODIFY_REG16(TMRAx->BCSTR, TMRA_BCSTR_MODE, u16Mode);
}

/**
 * @brief  Enable or disable TMRA count value reload.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRA_ReloadCmd(CM_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        CLEAR_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_OVSTP);
    }
    else
    {
        SET_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_OVSTP);
    }
}

/**
 * @brief  Enable or disable TMRA sync start.
 * @note  The function is only valid when the TMRA unit is unit2 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRA_SyncStartCmd(CM_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_SYNC_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_SYNST);
    }
    else
    {
        CLEAR_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_SYNST);
    }
}

/**
 * @brief  Start the TMRA unit.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @retval None
 */
void TMRA_Start(CM_TMRA_TypeDef *TMRAx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    SET_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_START);
}

/**
 * @brief  Stop the TMRA unit.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @retval None
 */
void TMRA_Stop(CM_TMRA_TypeDef *TMRAx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    CLEAR_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_START);
}

/**
 * @brief  Enable or disable TMRA hardware up count condition.
 * @note     'TMRA_CNT_UP_COND_CLKAL_CLKBR', 'TMRA_CNT_UP_COND_CLKAL_CLKBF', 'TMRA_CNT_UP_COND_CLKAH_CLKBR',
 *           'TMRA_CNT_UP_COND_CLKAH_CLKBF', 'TMRA_CNT_UP_COND_CLKBH_CLKAR' and 'TMRA_CNT_UP_COND_CLKBH_CLKAF'
 *           are only valid when the TMRA unit is unit3 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Cond                 Hardware up count condition
 *         This parameter can be one or any combination of the following values:
 *           @arg TMRA_CNT_UP_COND_CLKAL_CLKBR: When CLKA is low, a rising edge is sampled on CLKB, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_CLKAL_CLKBF: When CLKA is low, a falling edge is sampled on CLKB, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_CLKAH_CLKBR: When CLKA is high, a rising edge is sampled on CLKB, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_CLKAH_CLKBF: When CLKA is high, a falling edge is sampled on CLKB, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_CLKBL_CLKAR: When CLKB is low, a rising edge is sampled on CLKA, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_CLKBL_CLKAF: When CLKB is low, a falling edge is sampled on CLKA, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_CLKBH_CLKAR: When CLKB is high, a rising edge is sampled on CLKA, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_CLKBH_CLKAF: When CLKB is high, a falling edge is sampled on CLKA, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_TRIGR:       When a rising edge occurred on TRIG, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_TRIGF:       When a falling edge occurred on TRIG, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_EVT:         When the event specified by TMRA_HTSSR occurred, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_SYM_OVF:     When the symmetric unit overflow, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_SYM_UDF:     When the symmetric unit underflow, the counter register counts up
 *           @arg TMRA_CNT_UP_COND_ALL:         All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval  None
 */
void TMRA_HWCountUpCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_CNT_UP_COND(TMRAx, u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRAx->HCUPR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(TMRAx->HCUPR, u16Cond);
    }
}

/**
 * @brief  Enable or disable TMRA hardware down count condition.
 * @note     'TMRA_CNT_DOWN_COND_CLKAL_CLKBR', 'TMRA_CNT_DOWN_COND_CLKAL_CLKBF', 'TMRA_CNT_DOWN_COND_CLKAH_CLKBR',
 *           'TMRA_CNT_DOWN_COND_CLKAH_CLKBF', 'TMRA_CNT_DOWN_COND_CLKBH_CLKAR' and 'TMRA_CNT_DOWN_COND_CLKBH_CLKAF'
 *           are only valid when the TMRA unit is unit3 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Cond                 Hardware down count condition
 *         This parameter can be one or any combination of the following values:
 *           @arg TMRA_CNT_DOWN_COND_CLKAL_CLKBR:   When CLKA is low, a rising edge is sampled on CLKB, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_CLKAL_CLKBF:   When CLKA is low, a falling edge is sampled on CLKB, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_CLKAH_CLKBR:   When CLKA is high, a rising edge is sampled on CLKB, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_CLKAH_CLKBF:   When CLKA is high, a falling edge is sampled on CLKB, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_CLKBL_CLKAR:   When CLKB is low, a rising edge is sampled on CLKA, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_CLKBL_CLKAF:   When CLKB is low, a falling edge is sampled on CLKA, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_CLKBH_CLKAR:   When CLKB is high, a rising edge is sampled on CLKA, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_CLKBH_CLKAF:   When CLKB is high, a falling edge is sampled on CLKA, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_TRIGR:         When a rising edge occurred on TRIG, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_TRIGF:         When a falling edge occurred on TRIG, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_EVT:           When the event specified by TMRA_HTSSR occurred, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_SYM_OVF:       When the symmetric unit overflow, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_SYM_UDF:       When the symmetric unit underflow, the counter register counts down
 *           @arg TMRA_CNT_DOWN_COND_ALL:           All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval  None
 */
void TMRA_HWCountDownCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_CNT_DOWN_COND(TMRAx, u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRAx->HCDOR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(TMRAx->HCDOR, u16Cond);
    }
}

/**
 * @brief  Enable or disable TMRA hardware start count condition.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Cond                 Hardware start counter condition
 *         This parameter can be one or any combination of the following values:
 *           @arg TMRA_START_COND_TRIGR:        The condition is that a rising edge is sampled on TRIG of the current TMRA unit
 *           @arg TMRA_START_COND_TRIGF:        The condition is that a falling edge is sampled on TRIG of the current TMRA unit
 *           @arg TMRA_START_COND_EVT:          The condition is that the event which is set in register TMRA_HTSSR0 has occurred
 *           @arg TMRA_START_COND_ALL:          All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval  None
 */
void TMRA_HWStartCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_HW_START_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRAx->HCONR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(TMRAx->HCONR, u16Cond);
    }
}

/**
 * @brief  Enable or disable TMRA hardware stop count condition.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Cond                 Hardware stop counter condition
 *         This parameter can be one or any combination of the following values:
 *           @arg TMRA_STOP_COND_TRIGR: The condition is that a rising edge is sampled on pin TRIG of the current TMRA unit
 *           @arg TMRA_STOP_COND_TRIGF: The condition is that a falling edge is sampled on pin TRIG of the current TMRA unit
 *           @arg TMRA_STOP_COND_EVT:   The condition is that the event which is set in register TMRA_HTSSR0 has occurred
 *           @arg TMRA_STOP_COND_ALL:   All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval  None
 */
void TMRA_HWStopCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_HW_STOP_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRAx->HCONR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(TMRAx->HCONR, u16Cond);
    }
}

/**
 * @brief  Enable or disable TMRA hardware clear count condition.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Cond                 Hardware clear counter condition
 *         This parameter can be one or any combination of the following values:
 *           @arg TMRA_CLR_COND_TRIGR:          The condition is that a rising edge is sampled on TRIG of the current TMRA unit
 *           @arg TMRA_CLR_COND_TRIGF:          The condition is that a falling edge is sampled on TRIG of the current TMRA unit
 *           @arg TMRA_CLR_COND_EVT:            The condition is that the event which is set in register TMRA_HTSSR0 has occurred
 *           @arg TMRA_CLR_COND_SYM_TRIGR:      The condition is that a rising edge is sampled on TRIG of the symmetric unit
 *           @arg TMRA_CLR_COND_SYM_TRIGF:      The condition is that a falling edge is sampled on TRIG of the symmetric unit
 *           @arg TMRA_CLR_COND_ALL:            All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval  None
 */
void TMRA_HWClearCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_HW_CLR_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRAx->HCONR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(TMRAx->HCONR, u16Cond);
    }
}

/**
 * @brief  Set the function mode of the TMRA pwm channel.
 * @note   TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Ch                   TMRA pwm channel
           This parameter can be one of the following values:
             @arg TMRA_CH1:             TMRA pwm Channel 1
             @arg TMRA_CH2:             TMRA pwm Channel 2
 * @param  [in] u16Func                 Function mode
 *         This parameter can be one of the following values:
 *           @arg TMRA_FUNC_CMP:        The function mode of TMRA is comparison ouput
 *           @arg TMRA_FUNC_CAPT:       The function mode of TMRA is capture the input
 * @retval None
 */
void TMRA_SetFunc(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Func)
{
    __IO uint16_t *CCONR;

    DDL_ASSERT(IS_TMRA_COMB_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_TMRA_FUNC_MD(u16Func));

    CCONR = (__IO uint16_t *)TMRA_CCONR(TMRAx, u32Ch);
    MODIFY_REG16(*CCONR, TMRA_CCONR_CAPMD, u16Func);
}

/**
 * @brief  Enable or disable hardware capture condition of the TMRA pwm channel.
  * @note   TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Ch                   TMRA pwm channel
           This parameter can be one of the following values:
             @arg TMRA_CH1:             TMRA pwm Channel 1
             @arg TMRA_CH2:             TMRA pwm Channel 2
 * @param  [in] u16Cond                 Hardware capture condition
 *         This parameter can be one or any combination of the following values:
 *           @arg TMRA_CAPT_COND_PWMR:  The condition of capture is a rising edge is sampled on pin TIMA_<t>_PWMn
 *           @arg TMRA_CAPT_COND_PWMF:  The condition of capture is a falling edge is sampled on pin TIMA_<t>_PWMn
 *           @arg TMRA_CAPT_COND_EVT:   The condition of capture is the specified event occurred
 *           @arg TMRA_CAPT_COND_ALL:   All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval  None
 */
void TMRA_HWCaptureCondCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Cond, en_functional_state_t enNewState)
{
    __IO uint16_t *CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_COMB_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_TMRA_CAPT_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    CCONR = (__IO uint16_t *)TMRA_CCONR(TMRAx, u32Ch);
    if (Enable == enNewState)
    {
        SET_REG16_BIT(*CCONR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(*CCONR, u16Cond);
    }
}

/**
 * @brief  Set the filter clock division of TMRA input pin.
 * @note   'TMRA_PIN_PWM2' and 'TMRA_PIN_CLKB' are only valid when the TMRA unit is unit3 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Pin                  Input pin
           This parameter can be one of the following values:
             @arg TMRA_PIN_PWM1:        Pin TIMA_<t>_PWM1
             @arg TMRA_PIN_PWM2:        Pin TIMA_<t>_PWM2
             @arg TMRA_PIN_CLKB:        Pin TIMA_<t>_CLKB
             @arg TMRA_PIN_CLKA:        Pin TIMA_<t>_CLKA
             @arg TMRA_PIN_TRIG:        Pin TIMA_<t>_TRIG
 * @param  [in] u16Div                  Input pin filter clock division
 *         This parameter can be one of the following values:
 *           @arg TMRA_FILTER_CLK_DIV1:         The filter clock is PCLK/1
 *           @arg TMRA_FILTER_CLK_DIV4:         The filter clock is PCLK/4
 *           @arg TMRA_FILTER_CLK_DIV16:        The filter clock is PCLK/16
 *           @arg TMRA_FILTER_CLK_DIV64:        The filter clock is PCLK/64
 * @retval None
 */
void TMRA_SetFilterClockDiv(CM_TMRA_TypeDef *TMRAx, uint32_t u32Pin, uint16_t u16Div)
{
    uint32_t u32Offset;
    __IO uint16_t *CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_INPUT_PIN(TMRAx, u32Pin));
    DDL_ASSERT(IS_TMRA_FILTER_CLK_DIV(u16Div));

    if (u32Pin >= TMRA_PIN_CLKB)
    {
        u32Offset = ((u32Pin >> 8U) - 1U) << 2U;
        MODIFY_REG16(TMRAx->FCONR, (TMRA_FCONR_NOFICKCB >> u32Offset), (u16Div >> u32Offset));
    }
    else
    {
        CCONR = (__IO uint16_t *)TMRA_CCONR(TMRAx, u32Pin);
        MODIFY_REG16(*CCONR, TMRA_CCONR_NOFICKCP, u16Div);
    }
}

/**
 * @brief  Enable or disable filter clock division of TMRA input pin.
 * @note   'TMRA_PIN_PWM2' and 'TMRA_PIN_CLKB' are only valid when the TMRA unit is unit3 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Pin                  Input pin
           This parameter can be one of the following values:
             @arg TMRA_PIN_PWM1:        Pin TIMA_<t>_PWM1
             @arg TMRA_PIN_PWM2:        Pin TIMA_<t>_PWM2
             @arg TMRA_PIN_CLKB:        Pin TIMA_<t>_CLKB
             @arg TMRA_PIN_CLKA:        Pin TIMA_<t>_CLKA
             @arg TMRA_PIN_TRIG:        Pin TIMA_<t>_TRIG
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRA_FilterCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Pin, en_functional_state_t enNewState)
{
    uint32_t u32Offset;
    __IO uint16_t *CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_INPUT_PIN(TMRAx, u32Pin));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        if (u32Pin >= TMRA_PIN_CLKB)
        {
            u32Offset = ((u32Pin >> 8U) - 1U) << 2U;
            SET_REG16_BIT(TMRAx->FCONR, (TMRA_FCONR_NOFIENCB >> u32Offset));
        }
        else
        {
            CCONR = (__IO uint16_t *)TMRA_CCONR(TMRAx, u32Pin);
            SET_REG16_BIT(*CCONR, TMRA_CCONR_NOFIENCP);
        }
    }
    else
    {
        if (u32Pin >= TMRA_PIN_CLKB)
        {
            u32Offset = ((u32Pin >> 8U) - 1U) << 2U;
            CLEAR_REG16_BIT(TMRAx->FCONR, (TMRA_FCONR_NOFIENCB >> u32Offset));
        }
        else
        {
            CCONR = (__IO uint16_t *)TMRA_CCONR(TMRAx, u32Pin);
            CLEAR_REG16_BIT(*CCONR, TMRA_CCONR_NOFIENCP);
        }
    }
}

/**
 * @brief  Set the transmfer condition of compare value buffer.
 * @note   The function is only valid when the TMRA unit is unit3 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Cond                 Buffer transmfer condition
 *         This parameter can be one of the following values:
 *           @arg TMRA_BUF_COND_OVF_UDF_CLR:    When counting overflow or underflow or counting register was cleared, transfer CMPARm(m=2) to CMPARn(n=1)
 *           @arg TMRA_BUF_COND_PEAK:           In triangle wave count mode, when count reached peak, transfer CMPARm(m=2) to CMPARn(n=1)
 *           @arg TMRA_BUF_COND_VALLEY:         In triangle wave count mode, when count reached valley, transfer CMPARm(m=2) to CMPARn(n=1)
 *           @arg TMRA_BUF_COND_PEAK_VALLEY:    In triangle wave count mode, when count reached peak or valley, transfer CMPARm(m=2) to CMPARn(n=1)
 * @retval None
 */
void TMRA_SetCompareBufCond(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_BUF_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_BUF_TRANS_COND(u16Cond));

    MODIFY_REG16(TMRAx->BCONR, TMRA_BCONR_BSE_MASK, u16Cond);
}

/**
 * @brief  Enable or Disable TMRA compare value buffer.
 * @note   The function is only valid when the TMRA unit is unit3 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRA_CompareBufCmd(CM_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_BUF_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRAx->BCONR, TMRA_BCONR_BEN);
    }
    else
    {
        CLEAR_REG16_BIT(TMRAx->BCONR, TMRA_BCONR_BEN);
    }
}

/**
 * @brief  De-Initializes the PWM function of the TMRA channel.
 * @note   TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Ch                   TMRA pwm channel
           This parameter can be one of the following values:
             @arg TMRA_CH1:             TMRA pwm Channel 1
             @arg TMRA_CH2:             TMRA pwm Channel 2
 * @retval None
 */
void TMRA_PWM_DeInit(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch)
{
    __IO uint16_t *CMPAR;
    __IO uint16_t *PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_COMB_UNIT_CH(TMRAx, u32Ch));

    /* Configures the registers to reset value. */
    CMPAR = (__IO uint16_t *)TMRA_CMPAR(TMRAx, u32Ch);
    WRITE_REG16(*CMPAR, 0xFFFFU);
    PCONR = (__IO uint16_t *)TMRA_PCONR(TMRAx, u32Ch);
    WRITE_REG16(*PCONR, 0x0000U);
}

/**
 * @brief  Initializes the PWM function of the TMRA channel.
 * @note   TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @note   'TMRA_PWM_INVT' is only valid when the PWM count state is u16MatchPolarity or u16PeriodPolarity.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Ch                   TMRA pwm channel
           This parameter can be one of the following values:
             @arg TMRA_CH1:             TMRA pwm Channel 1
             @arg TMRA_CH2:             TMRA pwm Channel 2
 * @param  [in] pstcPwmInit             Pointer to a @ref stc_tmra_pwm_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initializes success
 *           - ErrorInvalidParameter: pstcPwmInit == NULL
 */
en_result_t TMRA_PWM_Init(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, const stc_tmra_pwm_init_t *pstcPwmInit)
{
    en_result_t enRet = Ok;
    __IO uint16_t *CCONR;
    __IO uint16_t *CMPAR;
    __IO uint16_t *PCONR;

    /* Check TMRAx instance and pstcPwmInit */
    if (NULL == pstcPwmInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMRA_COMB_UNIT_CH(TMRAx, u32Ch));
        DDL_ASSERT(IS_TMRA_PWM_POLARITY(TMRA_PWM_CNT_START, pstcPwmInit->u16StartPolarity));
        DDL_ASSERT(IS_TMRA_PWM_POLARITY(TMRA_PWM_CNT_STOP, pstcPwmInit->u16StopPolarity));
        DDL_ASSERT(IS_TMRA_PWM_POLARITY(TMRA_PWM_CNT_MATCH, pstcPwmInit->u16MatchPolarity));
        DDL_ASSERT(IS_TMRA_PWM_POLARITY(TMRA_PWM_CNT_PERIOD, pstcPwmInit->u16PeriodPolarity));

        CCONR = (__IO uint16_t *)TMRA_CCONR(TMRAx, u32Ch);
        CLEAR_REG16_BIT(*CCONR, TMRA_CCONR_CAPMD);
        CMPAR = (__IO uint16_t *)TMRA_CMPAR(TMRAx, u32Ch);
        WRITE_REG16(*CMPAR, pstcPwmInit->u16CompareValue);
        /* Configure output compare */
        PCONR = (__IO uint16_t *)TMRA_PCONR(TMRAx, u32Ch);
        MODIFY_REG16(*PCONR, (TMRA_PCONR_STAC | TMRA_PCONR_STPC | TMRA_PCONR_CMPC | TMRA_PCONR_PERC),
                     ((uint16_t)(pstcPwmInit->u16StartPolarity  << TMRA_PCONR_STAC_POS) |
                      (uint16_t)(pstcPwmInit->u16StopPolarity   << TMRA_PCONR_STPC_POS) |
                      (uint16_t)(pstcPwmInit->u16MatchPolarity  << TMRA_PCONR_CMPC_POS) |
                      (uint16_t)(pstcPwmInit->u16PeriodPolarity << TMRA_PCONR_PERC_POS)));
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmra_pwm_init_t to default values.
 * @param  [out] pstcPwmInit            Pointer to a @ref stc_tmra_pwm_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: The structure initializes success
 *           - ErrorInvalidParameter: pstcPwmInit == NULL
 */
en_result_t TMRA_PWM_StructInit(stc_tmra_pwm_init_t *pstcPwmInit)
{
    en_result_t enRet = Ok;

    /* Check parameters */
    if (NULL == pstcPwmInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcPwmInit->u16CompareValue   = 0xFFFFU;
        pstcPwmInit->u16StartPolarity  = TMRA_PWM_LOW;
        pstcPwmInit->u16StopPolarity   = TMRA_PWM_LOW;
        pstcPwmInit->u16MatchPolarity  = TMRA_PWM_LOW;
        pstcPwmInit->u16PeriodPolarity = TMRA_PWM_LOW;
    }

    return enRet;
}

/**
 * @brief  Set the PWM polarity when the TMRA counter is in the specified count state.
  * @note   TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @note   'TMRA_PWM_INVT' is only valid when the PWM count state is u16MatchPolarity or u16PeriodPolarity.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Ch                   TMRA pwm channel
           This parameter can be one of the following values:
             @arg TMRA_CH1:             TMRA pwm Channel 1
             @arg TMRA_CH2:             TMRA pwm Channel 2
 * @param  [in] u16CountState           TMRA count state
 *         This parameter can be one of the following values:
 *           @arg TMRA_PWM_CNT_START:   The TMRA start counting
 *           @arg TMRA_PWM_CNT_STOP:    The TMRA stop counting
 *           @arg TMRA_PWM_CNT_MATCH:   The TMRA counting matches the channel compare value
 *           @arg TMRA_PWM_CNT_PERIOD:  The TMRA counting matches the period value
 * @param  [in] u16Polarity             PWM output polarity
 *         This parameter can be one of the following values:
 *           @arg TMRA_PWM_LOW:         PWM output low
 *           @arg TMRA_PWM_HIGH:        PWM output high
 *           @arg TMRA_PWM_HOLD:        PWM output hold the current polarity
 *           @arg TMRA_PWM_INVT:        PWM output invert the current polarity
 * @retval None
 */
void TMRA_PWM_SetPolarity(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16CountState, uint16_t u16Polarity)
{
    __IO uint16_t *PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_COMB_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_TMRA_PWM_POLARITY(u16CountState, u16Polarity));

    PCONR = (__IO uint16_t *)TMRA_PCONR(TMRAx, u32Ch);
    MODIFY_REG16(*PCONR, (uint16_t)((uint16_t)TMRA_PCONR_STAC << u16CountState), (uint16_t)(u16Polarity << u16CountState));
}

/**
 * @brief  Set the PWM force output polarity.
 * @note   TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Ch                   TMRA pwm channel
           This parameter can be one of the following values:
             @arg TMRA_CH1:             TMRA pwm Channel 1
             @arg TMRA_CH2:             TMRA pwm Channel 2
 * @param  [in] u16Polarity             PWM output polarity
 *         This parameter can be one of the following values:
 *           @arg TMRA_PWM_FORCE_INVD:  Force polarity is invalid
 *           @arg TMRA_PWM_FORCE_LOW:   Force the PWM output low at the beginning of the next cycle
 *           @arg TMRA_PWM_FORCE_HIGH:  Force the PWM output high at the beginning of the next cycle
 * @retval None
 */
void TMRA_PWM_SetForcePolarity(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Polarity)
{
    __IO uint16_t *PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_COMB_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_TMRA_FORCE_POLARITY(u16Polarity));

    PCONR = (__IO uint16_t *)TMRA_PCONR(TMRAx, u32Ch);
    MODIFY_REG16(*PCONR, TMRA_PCONR_FORC, u16Polarity);
}

/**
 * @brief  Enable or Disable the PWM output of the TMRA channel.
 * @note   TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Ch                   TMRA pwm channel
           This parameter can be one of the following values:
             @arg TMRA_CH1:             TMRA pwm Channel 1
             @arg TMRA_CH2:             TMRA pwm Channel 2
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRA_PWM_Cmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, en_functional_state_t enNewState)
{
    __IO uint16_t *PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_COMB_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PCONR = (__IO uint16_t *)TMRA_PCONR(TMRAx, u32Ch);
    if (Enable == enNewState)
    {
        SET_REG16_BIT(*PCONR, TMRA_PCONR_OUTEN);
    }
    else
    {
        CLEAR_REG16_BIT(*PCONR, TMRA_PCONR_OUTEN);
    }
}

/**
 * @brief  Set the event source for specified usage.
 * @param  [in] u8EventUsage            Usage type
 *         This parameter can be one of the following values:
 *           @arg TMRA_EVT_USAGE_CNT:   The specified event is used for counting
 *           @arg TMRA_EVT_USAGE_CAPT:  The specified event is used for capturing
 * @param  [in] enEventSrc              An en_event_src_t enumeration type value
 * @retval None
 */
void TMRA_SetTriggerSrc(uint8_t u8EventUsage, en_event_src_t enEventSrc)
{
    __IO uint32_t *HTSSR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_EVT_USAGE(u8EventUsage));

    HTSSR = (__IO uint32_t *)TMRA_HTSSR(u8EventUsage);
    WRITE_REG32(*HTSSR, enEventSrc);
}

/**
 * @brief  Enable or disable specified event output.
 * @note   TMRA unit1 and unit2 have only 'TMRA_CH1', unit3 and unit4 have 'TMRA_CH1' and 'TMRA_CH2'.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u32Ch                   TMRA pwm channel
           This parameter can be one of the following values:
             @arg TMRA_CH1:             TMRA pwm Channel 1
             @arg TMRA_CH2:             TMRA pwm Channel 2
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRA_EventCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_COMB_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRAx->ECONR, (uint16_t)((uint16_t)0x1U << u32Ch));
    }
    else
    {
        CLEAR_REG16_BIT(TMRAx->ECONR, (uint16_t)((uint16_t)0x1U << u32Ch));
    }
}

/**
 * @brief  Enable or disable the specified multiple event outputs.
 * @note   'TMRA_EVT_CMP2' is only valid when the TMRA unit is unit3 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16MxCh                 TMRA event channel
           This parameter can be one or any combination of the following values:
             @arg TMRA_EVT_CMP1:        The event of compare-match or capture completed of channel 1
             @arg TMRA_EVT_CMP2:        The event of compare-match or capture completed of channel 2
             @arg TMRA_EVT_ALL:         All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRA_MxEventCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16MxCh, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRA_EVENT(TMRAx, u16MxCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRAx->ECONR, u16MxCh);
    }
    else
    {
        CLEAR_REG16_BIT(TMRAx->ECONR, u16MxCh);
    }
}

/**
 * @brief  Enable or disable specified TMRA interrupt.
 * @note   'TMRA_INT_CMP2' is only valid when the TMRA unit is unit3 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16IntType              Interrupt type
 *         This parameter can be one or any combination of the following values:
 *           @arg TMRA_INT_OVF:         The interrupt of counting overflow
 *           @arg TMRA_INT_UDF:         The interrupt of counting underflow
 *           @arg TMRA_INT_CMP1:        The interrupt of compare-match or capture completed of channel 1
 *           @arg TMRA_INT_CMP2:        The interrupt of compare-match or capture completed of channel 2
 *           @arg TMRA_INT_ALL:         All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRA_IntCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16IntType, en_functional_state_t enNewState)
{
    uint16_t u16GlobalInt;
    uint16_t u16CmpInt;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_INT(TMRAx, u16IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u16GlobalInt = u16IntType & 0xFF00U;
    u16CmpInt    = u16IntType & 0x00FFU;
    if (Enable == enNewState)
    {
        if (0U != u16GlobalInt)
        {
            SET_REG16_BIT(TMRAx->BCSTR, u16GlobalInt);
        }
        if (0U != u16CmpInt)
        {
            SET_REG16_BIT(TMRAx->ICONR, u16CmpInt);
        }
    }
    else
    {
        if (0U != u16GlobalInt)
        {
            CLEAR_REG16_BIT(TMRAx->BCSTR, u16GlobalInt);
        }
        if (0U != u16CmpInt)
        {
            CLEAR_REG16_BIT(TMRAx->ICONR, u16CmpInt);
        }
    }
}

/**
 * @brief  Get TMRA flag status.
 * @note   'TMRA_FLAG_CMP2' is only valid when the TMRA unit is unit3 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Flag                 TMRA flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg TMRA_FLAG_OVF:        The flag of counting overflow
 *           @arg TMRA_FLAG_UDF:        The flag of counting underflow
 *           @arg TMRA_FLAG_CMP1:       The flag of compare-match or capture completed of channel 1
 *           @arg TMRA_FLAG_CMP2:       The flag of compare-match or capture completed of channel 2
 *           @arg TMRA_FLAG_ALL:        All of the above
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t TMRA_GetStatus(const CM_TMRA_TypeDef *TMRAx, uint16_t u16Flag)
{
    en_flag_status_t enFlagSta = Reset;
    uint16_t u16GlobalFlag;
    uint16_t u16CmpFlag;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_FLAG(TMRAx, u16Flag));

    u16GlobalFlag = u16Flag & 0xFF00U;
    u16CmpFlag    = u16Flag & 0x00FFU;
    if (0U != u16GlobalFlag)
    {
        if (0U != (READ_REG16_BIT(TMRAx->BCSTR, u16GlobalFlag)))
        {
            enFlagSta = Set;
        }
    }
    if ((Reset == enFlagSta) && (0U != u16CmpFlag))
    {
        if (0U != (READ_REG16_BIT(TMRAx->STFLR, u16CmpFlag)))
        {
            enFlagSta = Set;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Clear TMRA flag.
 * @note   'TMRA_FLAG_CMP2' is only valid when the TMRA unit is unit3 or unit4.
 * @param  [in] TMRAx                   Pointer to TMRA instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRA_1:            TMRA unit 1 instance register base
 *           @arg CM_TMRA_2:            TMRA unit 2 instance register base
 *           @arg CM_TMRA_3:            TMRA unit 3 instance register base
 *           @arg CM_TMRA_4:            TMRA unit 4 instance register base
 * @param  [in] u16Flag                 TMRA flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg TMRA_FLAG_OVF:        The flag of counting overflow
 *           @arg TMRA_FLAG_UDF:        The flag of counting underflow
 *           @arg TMRA_FLAG_CMP1:       The flag of compare-match or capture completed of channel 1
 *           @arg TMRA_FLAG_CMP2:       The flag of compare-match or capture completed of channel 2
 *           @arg TMRA_FLAG_ALL:        All of the above
 * @retval None
 */
void TMRA_ClearStatus(CM_TMRA_TypeDef *TMRAx, uint16_t u16Flag)
{
    uint16_t u16GlobalFlag;
    uint16_t u16CmpFlag;

    /* Check parameters */
    DDL_ASSERT(IS_TMRA_FLAG(TMRAx, u16Flag));

    u16GlobalFlag = u16Flag & 0xFF00U;
    u16CmpFlag    = u16Flag & 0x00FFU;
    if (0U != u16GlobalFlag)
    {
        CLEAR_REG16_BIT(TMRAx->BCSTR, u16GlobalFlag);
    }
    if (0U != u16CmpFlag)
    {
        CLEAR_REG16_BIT(TMRAx->STFLR, u16CmpFlag);
    }
}

/**
 * @}
 */

#endif /* DDL_TMRA_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
