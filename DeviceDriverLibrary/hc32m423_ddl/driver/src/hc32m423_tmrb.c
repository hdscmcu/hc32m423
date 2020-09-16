/**
 *******************************************************************************
 * @file  hc32m423_tmrb.c
 * @brief This file provides firmware functions to manage the TMRB(TimerB)
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
#include "hc32m423_tmrb.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TMRB TMRB
 * @brief TMRB Driver Library
 * @{
 */

#if (DDL_TMRB_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMRB_Local_Macros TMRB Local Macros
 * @{
 */

/**
 * @defgroup TMRB_Check_Parameters_Validity TMRB Check Parameters Validity
 * @{
 */

#define IS_TMRB_UNIT(x)                         ((x) == CM_TMRB)

#define IS_TMRB_CH(x)                                                          \
(   ((x) == TMRB_CH1)                           ||                             \
    ((x) == TMRB_CH2)                           ||                             \
    ((x) == TMRB_CH3)                           ||                             \
    ((x) == TMRB_CH4)                           ||                             \
    ((x) == TMRB_CH5)                           ||                             \
    ((x) == TMRB_CH6))

#define IS_TMRB_PWM_CH(x)                                                      \
(   ((x) == TMRB_CH1)                           ||                             \
    ((x) == TMRB_CH2)                           ||                             \
    ((x) == TMRB_CH3)                           ||                             \
    ((x) == TMRB_CH4))

#define IS_TMRB_BUF_CH(x)                                                      \
(   ((x) == TMRB_CH1)                           ||                             \
    ((x) == TMRB_CH3)                           ||                             \
    ((x) == TMRB_CH5))

#define IS_TMRB_CNT_DIR(x)                                                     \
(   ((x) == TMRB_DIR_UP)                        ||                             \
    ((x) == TMRB_DIR_DOWN))

#define IS_TMRB_CNT_MD(x)                                                      \
(   ((x) == TMRB_MD_SAWTOOTH)                   ||                             \
    ((x) == TMRB_MD_TRIANGLE))

#define IS_TMRB_FUNC_MD(x)                                                     \
(   ((x) == TMRB_FUNC_CMP)                      ||                             \
    ((x) == TMRB_FUNC_CAPT))

#define IS_TMRB_CMP_BUF_COND(x)                                                \
(   ((x) == TMRB_BUF_COND_INVD)                 ||                             \
    ((x) == TMRB_BUF_COND_PEAK)                 ||                             \
    ((x) == TMRB_BUF_COND_VALLEY)               ||                             \
    ((x) == TMRB_BUF_COND_PEAK_VALLEY))

#define IS_TMRB_CLK_DIV(x)                                                     \
(   ((x) == TMRB_CLK_DIV1)                      ||                             \
    ((x) == TMRB_CLK_DIV2)                      ||                             \
    ((x) == TMRB_CLK_DIV4)                      ||                             \
    ((x) == TMRB_CLK_DIV8)                      ||                             \
    ((x) == TMRB_CLK_DIV16)                     ||                             \
    ((x) == TMRB_CLK_DIV32)                     ||                             \
    ((x) == TMRB_CLK_DIV64)                     ||                             \
    ((x) == TMRB_CLK_DIV128)                    ||                             \
    ((x) == TMRB_CLK_DIV256)                    ||                             \
    ((x) == TMRB_CLK_DIV512)                    ||                             \
    ((x) == TMRB_CLK_DIV1024))

#define IS_TMRB_FLAG(x)                                                        \
(   ((x) != 0U)                                 &&                             \
    (((x) | TMRB_FLAG_ALL) == TMRB_FLAG_ALL))

#define IS_TMRB_INT(x)                                                         \
(   ((x) != 0U)                                 &&                             \
    (((x) | TMRB_INT_ALL) == TMRB_INT_ALL))

#define IS_TMRB_EVT_MXCH(x)                                                    \
(   ((x) != 0U)                                 &&                             \
    (((x) | TMRB_EVT_ALL) == TMRB_EVT_ALL))

#define IS_TMRB_FILTER_CLK_DIV(x)                                              \
(   ((x) == TMRB_FILTER_CLK_DIV1)               ||                             \
    ((x) == TMRB_FILTER_CLK_DIV4)               ||                             \
    ((x) == TMRB_FILTER_CLK_DIV16)              ||                             \
    ((x) == TMRB_FILTER_CLK_DIV64))

#define IS_TMRB_PWM_CNT_STAT(x)                                                \
(   ((x) == TMRB_PWM_CNT_START)                 ||                             \
    ((x) == TMRB_PWM_CNT_STOP)                  ||                             \
    ((x) == TMRB_PWM_CNT_MATCH)                 ||                             \
    ((x) == TMRB_PWM_CNT_PERIOD))

#define IS_TMRB_PWM_START_POLARITY(x)                                          \
(   ((x) == TMRB_PWM_LOW)                       ||                             \
    ((x) == TMRB_PWM_HIGH)                      ||                             \
    ((x) == TMRB_PWM_HOLD))

#define IS_TMRB_PWM_STOP_POLARITY(x)                                           \
(   ((x) == TMRB_PWM_LOW)                       ||                             \
    ((x) == TMRB_PWM_HIGH)                      ||                             \
    ((x) == TMRB_PWM_HOLD))

#define IS_TMRB_PWM_MATCH_POLARITY(x)                                          \
(   ((x) == TMRB_PWM_LOW)                       ||                             \
    ((x) == TMRB_PWM_HIGH)                      ||                             \
    ((x) == TMRB_PWM_HOLD)                      ||                             \
    ((x) == TMRB_PWM_INVT))

#define IS_TMRB_PWM_PERIOD_POLARITY(x)                                         \
(   ((x) == TMRB_PWM_LOW)                       ||                             \
    ((x) == TMRB_PWM_HIGH)                      ||                             \
    ((x) == TMRB_PWM_HOLD)                      ||                             \
    ((x) == TMRB_PWM_INVT))

#define IS_TMRB_PWM_POLARITY(state, polarity)                                     \
(   (((state) == TMRB_PWM_CNT_START) && IS_TMRB_PWM_START_POLARITY(polarity)) || \
    (((state) == TMRB_PWM_CNT_STOP)  && IS_TMRB_PWM_STOP_POLARITY(polarity))   || \
    (((state) == TMRB_PWM_CNT_MATCH) && IS_TMRB_PWM_MATCH_POLARITY(polarity)) || \
    (((state) == TMRB_PWM_CNT_PERIOD) && IS_TMRB_PWM_PERIOD_POLARITY(polarity)))

#define IS_TMRB_PWM_FORCE_POLARITY(x)                                          \
(   ((x) == TMRB_PWM_FORCE_INVD)                ||                             \
    ((x) == TMRB_PWM_FORCE_LOW)                 ||                             \
    ((x) == TMRB_PWM_FORCE_HIGH))

#define IS_TMRB_CAPT_COND(x)                                                   \
(   ((x) != 0U)                                 ||                             \
    (((x) | TMRB_START_COND_ALL) == TMRB_START_COND_ALL))

#define IS_TMRB_START_COND(x)                                                  \
(   ((x) != 0U)                                 ||                             \
    (((x) | TMRB_START_COND_ALL) == TMRB_START_COND_ALL))

#define IS_TMRB_STOP_COND(x)                                                   \
(   ((x) != 0U)                                 ||                             \
    (((x) | TMRB_STOP_COND_ALL) == TMRB_STOP_COND_ALL))

#define IS_TMRB_CLR_COND(x)                                                    \
(   ((x) != 0U)                                 ||                             \
    (((x) | TMRB_CLR_COND_ALL) == TMRB_CLR_COND_ALL))

#define IS_TMRB_CNT_UP_COND(x)                                                 \
(   ((x) != 0U)                                 ||                             \
    (((x) | TMRB_CNT_UP_COND_ALL) == TMRB_CNT_UP_COND_ALL))

#define IS_TMRB_CNT_DOWN_COND(x)                                               \
(   ((x) != 0U)                                 ||                             \
    (((x) | TMRB_CNT_DOWN_COND_ALL) == TMRB_CNT_DOWN_COND_ALL))

/**
 * @}
 */

/**
 * @defgroup TMRB_Flag_Mask TMRB Flag Mask
 * @{
 */
#define TMRB_CNT_FLAG_MASK                  (TMRB_FLAG_OVF | TMRB_FLAG_UDF)

#define TMRB_CMP_FLAG_MASK                  (TMRB_FLAG_CMP1 |                  \
                                             TMRB_FLAG_CMP2 |                  \
                                             TMRB_FLAG_CMP3 |                  \
                                             TMRB_FLAG_CMP4 |                  \
                                             TMRB_FLAG_CMP5 |                  \
                                             TMRB_FLAG_CMP6)
/**
 * @}
 */

/**
 * @defgroup TMRB_Interrupt_Mask TMRB Interrupt Mask
 * @{
 */
#define TMRB_CNT_INT_MASK                   (TMRB_INT_OVF | TMRB_INT_UDF)

#define TMRB_CMP_INT_MASK                   (TMRB_INT_CMP1 |                   \
                                             TMRB_INT_CMP2 |                   \
                                             TMRB_INT_CMP3 |                   \
                                             TMRB_INT_CMP4 |                   \
                                             TMRB_INT_CMP5 |                   \
                                             TMRB_INT_CMP6)
/**
 * @}
 */

/**
 * @defgroup TMRB_BCONRx_Register TMRB BCONRx Register(x = 1 ~ 3)
 * @brief Get the specified BCONR register address of the specified TMRB unit
 * @{
 */
#define TMRB_BCONRx(_UNITx_, _CH_)  ((__IO uint16_t *)((uint32_t)(&((_UNITx_)->BCONR1)) + (((_CH_) % 2UL) << 2UL)))
/**
 * @}
 */

/**
 * @defgroup TMRB_CMPARx_Register TMRB CMPARx Register(x = 1 ~ 6)
 * @brief Get the specified CMPAR register address of the specified TMRB unit
 * @{
 */
#define TMRB_CMPARx(_UNITx_, _CH_)  ((__IO uint16_t *)((uint32_t)(&((_UNITx_)->CMPAR1)) + ((_CH_) << 2UL)))
/**
 * @}
 */

/**
 * @defgroup TMRB_CCONRx_Register TMRB CCONRx Register(x = 1 ~ 4)
 * @brief Get the specified CCONR register address of the specified TMRB unit
 * @{
 */
#define TMRB_CCONRx(_UNITx_, _CH_)  ((__IO uint16_t *)((uint32_t)(&((_UNITx_)->CCONR1)) + ((_CH_) << 2UL)))
/**
 * @}
 */

/**
 * @defgroup TMRB_PCONRx_Register TMRB PCONRx Register(x = 1 ~ 4)
 * @brief Get the specified PCONR register address of the specified TMRB unit
 * @{
 */
#define TMRB_PCONRx(_UNITx_, _CH_)  ((__IO uint16_t *)((uint32_t)(&((_UNITx_)->PCONR1)) + ((_CH_) << 2UL)))
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

/**
 * @addtogroup TMRB_Local_Functions
 * @{
 */
static __IO uint32_t* TMRB_HTSSR(const CM_TMRB_TypeDef *DCUx);
/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup TMRB_Global_Functions TMRB Global Functions
 * @{
 */

/**
 * @brief  Initialize TMRB base function.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] pstcTmrbInit        Pointer to a @ref stc_tmrb_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcTmrbInit is NULL
 */
en_result_t TMRB_Init(CM_TMRB_TypeDef *TMRBx,
                        const stc_tmrb_init_t *pstcTmrbInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcTmrbInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
        DDL_ASSERT(IS_TMRB_CLK_DIV(pstcTmrbInit->u16ClockDiv));
        DDL_ASSERT(IS_TMRB_CNT_MD(pstcTmrbInit->u16CountMode));
        DDL_ASSERT(IS_TMRB_CNT_DIR(pstcTmrbInit->u16CountDir));

        WRITE_REG16(TMRBx->BCSTR, (pstcTmrbInit->u16CountDir | \
                                   pstcTmrbInit->u16ClockDiv | \
                                   pstcTmrbInit->u16CountMode));

        WRITE_REG16(TMRBx->CNTER, 0U);
        WRITE_REG16(TMRBx->PERAR, pstcTmrbInit->u16PeriodValue);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmrb_init_t to default values.
 * @param  [out] pstcTmrbInit       Pointer to a @ref stc_tmrb_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcTmrbInit is NULL
 */
en_result_t TMRB_StructInit(stc_tmrb_init_t *pstcTmrbInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    if (NULL != pstcTmrbInit)
    {
        pstcTmrbInit->u16ClockDiv = TMRB_CLK_DIV1;
        pstcTmrbInit->u16CountMode = TMRB_MD_SAWTOOTH;
        pstcTmrbInit->u16CountDir = TMRB_DIR_DOWN;
        pstcTmrbInit->u16PeriodValue = 0xFFFFU;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize TMRB unit base function.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @retval None
 */
void TMRB_DeInit(CM_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));

    /* Configures the registers to reset value. */
    WRITE_REG16(TMRBx->BCSTR, 0x0002U);
    WRITE_REG16(TMRBx->CNTER, 0x0000U);
    WRITE_REG16(TMRBx->PERAR, 0xFFFFU);
}

/**
 * @brief  Get the TMRB counter count value.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @retval Counter count value (between Min_Data=0 and Max_Data=0xFFFF)
 */
uint16_t TMRB_GetCountValue(const CM_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));

    return READ_REG16(TMRBx->CNTER);
}

/**
 * @brief  Set the TMRB counter count value.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Value            Counter count value (between Min_Data=0 and Max_Data=0xFFFF)
 * @retval None
 */
void TMRB_SetCountValue(CM_TMRB_TypeDef *TMRBx, uint16_t u16Value)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));

    WRITE_REG16(TMRBx->CNTER, u16Value);
}

/**
 * @brief  Get TMRB counter period value.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @retval Counter period value (between Min_Data=0 and Max_Data=0xFFFF)
 */
uint16_t TMRB_GetPeriodValue(const CM_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));

    return READ_REG16(TMRBx->PERAR);
}

/**
 * @brief  Set TMRB counter period value.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Value            Counter period value (between Min_Data=0 and Max_Data=0xFFFF)
 * @retval None
 */
void TMRB_SetPeriodValue(CM_TMRB_TypeDef *TMRBx, uint16_t u16Value)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));

    WRITE_REG16(TMRBx->PERAR, u16Value);
}

/**
 * @brief  Get TMRB compare register value.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH2:         TMRB channel 2
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH4:         TMRB channel 4
 *           @arg TMRB_CH5:         TMRB channel 5
 *           @arg TMRB_CH6:         TMRB channel 6
 * @retval Compare value (between Min_Data=0 and Max_Data=0xFFFF)
 */
uint16_t TMRB_GetCompareValue(const CM_TMRB_TypeDef *TMRBx, uint32_t u32Ch)
{
    __I uint16_t *TMRB_CMPAR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CH(u32Ch));

    TMRB_CMPAR = TMRB_CMPARx(TMRBx, u32Ch);
    return READ_REG16(*TMRB_CMPAR);
}

/**
 * @brief  Set TMRB compare register value.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH2:         TMRB channel 2
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH4:         TMRB channel 4
 *           @arg TMRB_CH5:         TMRB channel 5
 *           @arg TMRB_CH6:         TMRB channel 6
 * @param  [in] u16Value            Compare value (between Min_Data=0 and Max_Data=0xFFFF)
 * @retval None
 */
void TMRB_SetCompareValue(CM_TMRB_TypeDef *TMRBx,
                                uint32_t u32Ch,
                                uint16_t u16Value)
{
    __IO uint16_t *TMRB_CMPAR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CH(u32Ch));

    TMRB_CMPAR = TMRB_CMPARx(TMRBx, u32Ch);
    WRITE_REG16(*TMRB_CMPAR, u16Value);
}

/**
 * @brief  Start TMRB counter.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @retval None
 */
void TMRB_Start(CM_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));

    SET_REG16_BIT(TMRBx->BCSTR, TMRB_BCSTR_START);
}

/**
 * @brief  Stop TMRB counter.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @retval None
 */
void TMRB_Stop(CM_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));

    CLEAR_REG16_BIT(TMRBx->BCSTR, TMRB_BCSTR_START);
}

/**
 * @brief  Get TMRB flag status.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Flag             TMRB flag type
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_FLAG_OVF:    Overflow flag
 *           @arg TMRB_FLAG_UDF:    Underflow flag
 *           @arg TMRB_FLAG_CMP1:   Channel1 compare match flag
 *           @arg TMRB_FLAG_CMP2:   Channel2 compare match flag
 *           @arg TMRB_FLAG_CMP3:   Channel3 compare match flag
 *           @arg TMRB_FLAG_CMP4:   Channel4 compare match flag
 *           @arg TMRB_FLAG_CMP5:   Channel5 compare match flag
 *           @arg TMRB_FLAG_CMP6:   Channel6 compare match flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set:   Any bit of the composed flag is set.
 *           - Reset: All bit of the composed flag is reset.
 */
en_flag_status_t TMRB_GetStatus(const CM_TMRB_TypeDef *TMRBx, uint16_t u16Flag)
{
    en_flag_status_t enCntStatus = Reset;
    en_flag_status_t enCmpStatus = Reset;
    const uint16_t u16CntFlag = (u16Flag & TMRB_CNT_FLAG_MASK);
    const uint16_t u16CmpFlag = (u16Flag & TMRB_CMP_FLAG_MASK);

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_FLAG(u16Flag));

    if (u16CntFlag == READ_REG16_BIT(TMRBx->BCSTR, u16CntFlag))
    {
        enCntStatus = Set;
    }

    if (u16CmpFlag == READ_REG16_BIT(TMRBx->STFLR, u16CmpFlag))
    {
        enCmpStatus = Set;
    }

    return ((Set == enCntStatus) || (Set == enCmpStatus)) ? Set : Reset;
}

/**
 * @brief  Clear TMRB flag.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Flag             TMRB flag type
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_FLAG_OVF:    Overflow flag
 *           @arg TMRB_FLAG_UDF:    Underflow flag
 *           @arg TMRB_FLAG_CMP1:   Channel1 compare match flag
 *           @arg TMRB_FLAG_CMP2:   Channel2 compare match flag
 *           @arg TMRB_FLAG_CMP3:   Channel3 compare match flag
 *           @arg TMRB_FLAG_CMP4:   Channel4 compare match flag
 *           @arg TMRB_FLAG_CMP5:   Channel5 compare match flag
 *           @arg TMRB_FLAG_CMP6:   Channel6 compare match flag
 * @retval None
 */
void TMRB_ClearStatus(CM_TMRB_TypeDef *TMRBx, uint16_t u16Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_FLAG(u16Flag));

    if (0U != (u16Flag & TMRB_CNT_FLAG_MASK))
    {
        CLEAR_REG16_BIT(TMRBx->BCSTR, (u16Flag & TMRB_CNT_FLAG_MASK));
    }

    if (0U != (u16Flag & TMRB_CMP_FLAG_MASK))
    {
        CLEAR_REG16_BIT(TMRBx->STFLR, (u16Flag & TMRB_CMP_FLAG_MASK));
    }
}

/**
 * @brief  Set TMRB clock division.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Div              TMRB clock division
 *         This parameter can be one of the following values:
 *           @arg TMRB_CLK_DIV1:    PCLK
 *           @arg TMRB_CLK_DIV2:    PCLK/2
 *           @arg TMRB_CLK_DIV4:    PCLK/4
 *           @arg TMRB_CLK_DIV8:    PCLK/8
 *           @arg TMRB_CLK_DIV16:   PCLK/16
 *           @arg TMRB_CLK_DIV32:   PCLK/32
 *           @arg TMRB_CLK_DIV64:   PCLK/64
 *           @arg TMRB_CLK_DIV128:  PCLK/128
 *           @arg TMRB_CLK_DIV256:  PCLK/256
 *           @arg TMRB_CLK_DIV512:  PCLK/512
 *           @arg TMRB_CLK_DIV1024: PCLK/1024
 * @retval None
 * @note   The PCLK division function is valid when clock source is PCLK
 */
void TMRB_SetClockDiv(CM_TMRB_TypeDef *TMRBx, uint16_t u16Div)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CLK_DIV(u16Div));

    MODIFY_REG16(TMRBx->BCSTR, TMRB_BCSTR_CKDIV, u16Div);
}

/**
 * @brief  Set the TMRB count direction.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Dir              The TMRB count direction
 *         This parameter can be one of the following values:
 *           @arg TMRB_DIR_DOWN:    Count down
 *           @arg TMRB_DIR_UP:      Count up
 * @retval None
 */
void TMRB_SetCountDir(CM_TMRB_TypeDef *TMRBx, uint16_t u16Dir)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CNT_DIR(u16Dir));

    MODIFY_REG16(TMRBx->BCSTR, TMRB_BCSTR_DIR, u16Dir);
}

/**
 * @brief  Get the TMRB count direction.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @retval Count direction:
 *           - TMRB_DIR_DOWN:       Count down
 *           - TMRB_DIR_UP:         Count up
 */
uint16_t TMRB_GetCountDir(const CM_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));

    return READ_REG16_BIT(TMRBx->BCSTR, TMRB_BCSTR_DIR);
}

/**
 * @brief  Set the TMRB count mode.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Mode             The TMRB count mode
 *         This parameter can be one of the following values:
 *           @arg TMRB_MD_SAWTOOTH: Sawtooth wave mode
 *           @arg TMRB_MD_TRIANGLE: Triangle wave mode
 * @retval None
 */
void TMRB_SetCountMode(CM_TMRB_TypeDef *TMRBx, uint16_t u16Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CNT_MD(u16Mode));

    MODIFY_REG16(TMRBx->BCSTR, TMRB_BCSTR_MODE, u16Mode);
}

/**
 * @brief  Enable or disable the specified TMRB interrupt.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16IntType          TMRB interrupt type
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_INT_OVF:     TMRB Overflow interrupt
 *           @arg TMRB_INT_UDF:     TMRB Underflow interrupt
 *           @arg TMRB_INT_CMP1:    TMRB compare channel 1 match interrupt
 *           @arg TMRB_INT_CMP2:    TMRB compare channel 2 match interrupt
 *           @arg TMRB_INT_CMP3:    TMRB compare channel 3 match interrupt
 *           @arg TMRB_INT_CMP4:    TMRB compare channel 4 match interrupt
 *           @arg TMRB_INT_CMP5:    TMRB compare channel 5 match interrupt
 *           @arg TMRB_INT_CMP6:    TMRB compare channel 6 match interrupt
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified TMRB interrupt.
 *           @arg Disable:          Disable the specified TMRB interrupt.
 * @retval None
 */
void TMRB_IntCmd(CM_TMRB_TypeDef *TMRBx,
                    uint16_t u16IntType,
                    en_functional_state_t enNewState)
{
    const uint16_t u16CntIntType = (u16IntType & TMRB_CNT_INT_MASK);
    const uint16_t u16CmpIntType = (u16IntType & TMRB_CMP_INT_MASK);

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_INT(u16IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRBx->BCSTR, u16CntIntType);
        SET_REG16_BIT(TMRBx->ICONR, u16CmpIntType);
    }
    else
    {
        CLEAR_REG16_BIT(TMRBx->BCSTR, u16CntIntType);
        CLEAR_REG16_BIT(TMRBx->ICONR, u16CmpIntType);
    }
}

/**
 * @brief  Enable or disable the specified compare channel event of TMRB.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB compare channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB compare channel 1
 *           @arg TMRB_CH2:         TMRB compare channel 2
 *           @arg TMRB_CH3:         TMRB compare channel 3
 *           @arg TMRB_CH4:         TMRB compare channel 4
 *           @arg TMRB_CH5:         TMRB compare channel 5
 *           @arg TMRB_CH6:         TMRB compare channel 6
 * @param  [in] enNewState          The function new state.
 *           @arg Enable:  Enable the specified channel event.
 *           @arg Disable: Disable the specified channel event.
 * @retval None
 */
void TMRB_EventCmd(CM_TMRB_TypeDef *TMRBx,
                        uint32_t u32Ch,
                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRBx->ECONR, (1UL << u32Ch));
    }
    else
    {
        CLEAR_REG16_BIT(TMRBx->ECONR, (1UL << u32Ch));
    }
}

/**
 * @brief  Enable/disable the specified TMRB event.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32MxCh             TMRB mx-channel
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_EVT_CMP1:    TMRB mx-channel 1 compare match/capture event
 *           @arg TMRB_EVT_CMP2:    TMRB mx-channel 2 compare match/capture event
 *           @arg TMRB_EVT_CMP3:    TMRB mx-channel 3 compare match/capture event
 *           @arg TMRB_EVT_CMP4:    TMRB mx-channel 4 compare match/capture event
 *           @arg TMRB_EVT_CMP5:    TMRB mx-channel 5 compare match/capture event
 *           @arg TMRB_EVT_CMP6:    TMRB mx-channel 6 compare match/capture event
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified TMRB event.
 *           @arg Disable:          Disable the specified TMRB event.
 * @retval None
 */
void TMRB_MxEventCmd(CM_TMRB_TypeDef *TMRBx,
                            uint32_t u32MxCh,
                            en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_EVT_MXCH(u32MxCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRBx->ECONR, u32MxCh);
    }
    else
    {
        CLEAR_REG16_BIT(TMRBx->ECONR, u32MxCh);
    }
}

/**
 * @brief  Set TMRB counter period value.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB compare channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB compare channel 1
 *           @arg TMRB_CH2:         TMRB compare channel 2
 *           @arg TMRB_CH3:         TMRB compare channel 3
 *           @arg TMRB_CH4:         TMRB compare channel 4
 * @param  [in] u16Func             Function mode
 *         This parameter can be one of the following values:
 *           @arg TMRB_FUNC_CMP:    Compare output function
 *           @arg TMRB_FUNC_CAPT:   Capture input function
 * @retval None
 * @note   The TMRB channel 5&6 don't capture input function
 */
void TMRB_SetFunc(CM_TMRB_TypeDef *TMRBx, uint32_t u32Ch, uint16_t u16Func)
{
    __IO uint16_t *TMRB_CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_FUNC_MD(u16Func));

    TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_CCONR, TMRB_CCONR_CAPMD, u16Func);
}

/**
 * @brief  Enable or disable TMRB reload function.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the reload function.
 *           @arg Disable:          Disable the reload function.
 * @retval None
 */
void TMRB_ReloadCmd(CM_TMRB_TypeDef *TMRBx,
                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRBx->BCSTR, TMRB_BCSTR_OVSTP);
    }
    else
    {
        CLEAR_REG16_BIT(TMRBx->BCSTR, TMRB_BCSTR_OVSTP);
    }
}

/**
 * @brief  Set the specified event trigger source for TMRB.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] enEventSrc          The trigger external event source source.
 *           @arg This parameter can be any value of @ref en_event_src_t
 * @retval None
 */
void TMRB_SetTriggerSrc(const CM_TMRB_TypeDef *TMRBx,
                        en_event_src_t enEventSrc)
{
    __IO uint32_t *const HTSSRx = TMRB_HTSSR(TMRBx);

    if (NULL != HTSSRx)
    {
        WRITE_REG32(*HTSSRx, ((uint32_t)enEventSrc) & 0x1FFUL);
    }
}

/**
 * @brief  Enable or disable the specified hardware start condition of TMRB.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Cond             TMRB hardware start counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_START_COND_PWM1R: Start count when detect the rising edge on TIMB_1_PWM1
 *           @arg TMRB_START_COND_PWM1F: Start count when detect the falling edge on TIMB_1_PWM1
 *           @arg TMRB_START_COND_EVT:   Start count when detect the timer TMRB_HTSSR specified event
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified hardware start condition.
 *           @arg Disable:          Disable the specified hardware start condition.
 * @retval None
 */
void TMRB_HWStartCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_START_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRBx->HCONR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(TMRBx->HCONR, u16Cond);
    }
}

/**
 * @brief  Enable or disable the specified hardware stop condition of TMRB.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Cond             TMRB hardware start counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_STOP_COND_PWM1R: Stop count when detect the rising edge on TIMB_1_PWM1
 *           @arg TMRB_STOP_COND_PWM1F: Stop count when detect the falling edge on TIMB_1_PWM1
 *           @arg TMRB_STOP_COND_EVT:   Stop count when detect the timer TMRB_HTSSR specified event
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified hardware stop condition.
 *           @arg Disable:          Disable the specified hardware stop condition.
 * @retval None
 */
void TMRB_HWStopCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_STOP_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRBx->HCONR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(TMRBx->HCONR, u16Cond);
    }
}

/**
 * @brief  Enable or disable the specified hardware clear condition of TMRB.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Cond             TMRB hardware start counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_CLR_COND_PWM1R: Clear count value when detect the rising edge on TIMB_1_PWM1
 *           @arg TMRB_CLR_COND_PWM1F: Clear count value when detect the falling edge on TIMB_1_PWM1
 *           @arg TMRB_CLR_COND_EVT:   Clear count value when detect the timer TMRB_HTSSR specified event
 *           @arg TMRB_CLR_COND_PWM3R: Clear count value when detect the rising edge on TIMB_1_PWM3
 *           @arg TMRB_CLR_COND_PWM3F: Clear count value when detect the falling edge on TIMB_1_PWM3
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified hardware clear condition.
 *           @arg Disable:          Disable the specified hardware clear condition.
 * @retval None
 */
void TMRB_HWClearCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CLR_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRBx->HCONR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(TMRBx->HCONR, u16Cond);
    }
}

/**
 * @brief  Enable or disable the specified hardware count up condition of TMRB.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Cond             TMRB hardware up counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_UP_COND_PWM1R: Count up when detect the rising edge on TIMB_1_PWM1
 *           @arg TMRB_UP_COND_PWM1F: Count up when detect the falling edge on TIMB_1_PWM1
 *           @arg TMRB_UP_COND_EVT:   Count up when detect the timer TMRB_HTSSR specified event
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified hardware count up condition.
 *           @arg Disable:          Disable the specified hardware count up condition.
 * @retval None
 */
void TMRB_HWCountUpCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CNT_UP_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRBx->HCUPR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(TMRBx->HCUPR, u16Cond);
    }
}

/**
 * @brief  Enable or disable the specified hardware count down condition of TMRB.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u16Cond             TMRB hardware down counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_DOWN_COND_PWM1R: Count down when detect the rising edge on TIMB_1_PWM1
 *           @arg TMRB_DOWN_COND_PWM1F: Count down when detect the falling edge on TIMB_1_PWM1
 *           @arg TMRB_DOWN_COND_EVT:   Count down when detect the timer TMRB_HTSSR specified event
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified hardware count down condition.
 *           @arg Disable:          Disable the specified hardware count down condition.
 * @retval None
 */
void TMRB_HWCountDownCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CNT_DOWN_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRBx->HCDOR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(TMRBx->HCDOR, u16Cond);
    }
}

/**
 * @brief  Enable or disable the specified hardware capture condition of TMRB.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH2:         TMRB channel 2
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH4:         TMRB channel 4
 * @param  [in] u16Cond             TMRB hardware down counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_CAPT_COND_PWMR: Trigger capture when detect the rising edge on TIMB_<t>_PWMn(n=1~4)
 *           @arg TMRB_CAPT_COND_PWMF: Trigger capture when detect the falling edge on TIMB_<t>_PWMn(n=1~4)
 *           @arg TMRB_CAPT_COND_EVT:  Trigger capture when detect the timer TMRB_HTSSR specified event
 * @param  [in] enNewState          The function new state
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified hardware capture condition.
 *           @arg Disable:          Disable the specified hardware capture condition.
 * @retval None
 * @note   TMRB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_HWCaptureCondCmd(CM_TMRB_TypeDef *TMRBx,
                                uint32_t u32Ch,
                                uint16_t u16Cond,
                                en_functional_state_t enNewState)
{
    __IO uint16_t *TMRB_CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CNT_DOWN_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);

    if (Enable == enNewState)
    {
        SET_REG16_BIT(*TMRB_CCONR, u16Cond);
    }
    else
    {
        CLEAR_REG16_BIT(*TMRB_CCONR, u16Cond);
    }
}

/**
 * @brief  Enable or disalbe the TMRB input capture noise filter function.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH2:         TMRB channel 2
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH4:         TMRB channel 4
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the TMRB input capture noise filter function.
 *           @arg Disable:          Disable the TMRB input capture noise filter function.
 * @retval None
 * @note   TMRB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_FilterCmd(CM_TMRB_TypeDef *TMRBx,
                    uint32_t u32Ch,
                    en_functional_state_t enNewState)
{
    __IO uint16_t *TMRB_CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);

    if (Enable == enNewState)
    {
        SET_REG16_BIT(*TMRB_CCONR, TMRB_CCONR_NOFIENCP);
    }
    else
    {
        CLEAR_REG16_BIT(*TMRB_CCONR, TMRB_CCONR_NOFIENCP);
    }
}

/**
 * @brief  Set TMRB input capture noise filter clock division.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH2:         TMRB channel 2
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH4:         TMRB channel 4
 * @param  [in] u16Div              TMRB input capture noise filter clock division
 *         This parameter can be one of the following values:
 *           @arg TMRB_FILTER_CLK_DIV1:  PCLK
 *           @arg TMRB_FILTER_CLK_DIV4:  PCLK/4
 *           @arg TMRB_FILTER_CLK_DIV16: PCLK/16
 *           @arg TMRB_FILTER_CLK_DIV64: PCLK/64
 * @retval None
 * @note   TMRB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_SetFilterClockDiv(CM_TMRB_TypeDef *TMRBx,
                                    uint32_t u32Ch,
                                    uint16_t u16Div)
{
    __IO uint16_t *TMRB_CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_FILTER_CLK_DIV(u16Div));

    TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_CCONR, TMRB_CCONR_NOFICKCP, u16Div);
}

/**
 * @brief  Enable or disable the specified channel buffer function of TMRB.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH5:         TMRB channel 5
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified channel buffer function.
 *           @arg Disable:          Disable the specified channel buffer function.
 * @retval None
 */
void TMRB_CompareBufCmd(CM_TMRB_TypeDef *TMRBx,
                            uint32_t u32Ch,
                            en_functional_state_t enNewState)
{
    __IO uint16_t *TMRB_BCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_BUF_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    TMRB_BCONR = TMRB_BCONRx(TMRBx, u32Ch);

    if (Enable == enNewState)
    {
        SET_REG16_BIT(*TMRB_BCONR, TMRB_BCONR_BEN);
    }
    else
    {
        CLEAR_REG16_BIT(*TMRB_BCONR, TMRB_BCONR_BEN);
    }
}

/**
 * @brief  Set TMRB triangle wave buffer mode.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH5:         TMRB channel 5
 * @param  [in] u16BufCond          The buffer transfer condition
 *         This parameter can be one of the following values:
 *           @arg TMRB_BUF_COND_INVD:   Don't transfer buffer value
 *           @arg TMRB_BUF_COND_PEAK:   Transfer buffer value when TMRB count peak
 *           @arg TMRB_BUF_COND_VALLEY: Transfer buffer value when TMRB count valley
 *           @arg TMRB_BUF_COND_PEAK_AND_VALLEY: Transfer buffer value when TMRB count peak or valley
 * @retval None
 * @note   TMRB channel 1&3&5 support buffer function.
 */
 void TMRB_SetCompareBufCond(CM_TMRB_TypeDef *TMRBx,
                                    uint32_t u32Ch,
                                    uint16_t u16BufCond)
{
    __IO uint16_t *TMRB_BCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_BUF_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_CMP_BUF_COND(u16BufCond));

    TMRB_BCONR = TMRB_BCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_BCONR, (TMRB_BCONR_BSE0 | TMRB_BCONR_BSE1), u16BufCond);
}

/**
 * @defgroup TMRB_PWM_Global_Functions TMRB PWM Global Functions
 * @{
 */

/**
 * @brief  Initialize TMRB PWM function.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH2:         TMRB channel 2
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH4:         TMRB channel 4
 * @param  [in] pstcPwmInit         Pointer to a @ref stc_tmrb_pwm_init_t.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcPwmInit is NULL
 * @note   TMRB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
en_result_t TMRB_PWM_Init(CM_TMRB_TypeDef *TMRBx,
                            uint32_t u32Ch,
                            const stc_tmrb_pwm_init_t *pstcPwmInit)
{
    __IO uint16_t *TMRB_PCONR;
    __IO uint16_t *TMRB_CMPAR;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcPwmInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
        DDL_ASSERT(IS_TMRB_CH(u32Ch));
        DDL_ASSERT(IS_TMRB_PWM_START_POLARITY(pstcPwmInit->u16StartPolarity));
        DDL_ASSERT(IS_TMRB_PWM_STOP_POLARITY(pstcPwmInit->u16StopPolarity));
        DDL_ASSERT(IS_TMRB_PWM_MATCH_POLARITY(pstcPwmInit->u16MatchPolarity));
        DDL_ASSERT(IS_TMRB_PWM_PERIOD_POLARITY(pstcPwmInit->u16PeriodPolarity));

        TMRB_CMPAR = TMRB_CMPARx(TMRBx, u32Ch);
        WRITE_REG16(*TMRB_CMPAR, pstcPwmInit->u16CompareValue);

        if (IS_TMRB_PWM_CH(u32Ch))
        {
            /* Set TMRB compare output function mode */
            TMRB_SetFunc(TMRBx, u32Ch, TMRB_FUNC_CMP);

            TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
            WRITE_REG16(*TMRB_PCONR, \
                        ((uint16_t)(pstcPwmInit->u16StartPolarity << TMRB_PCONR_STAC_POS) | \
                         (uint16_t)(pstcPwmInit->u16StopPolarity << TMRB_PCONR_STPC_POS)  | \
                         (uint16_t)(pstcPwmInit->u16MatchPolarity << TMRB_PCONR_CMPC_POS) | \
                         (uint16_t)(pstcPwmInit->u16PeriodPolarity << TMRB_PCONR_PERC_POS)));
        }
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmrb_pwm_init_t to default values.
 * @param  [out] pstcPwmInit        Pointer to a @ref stc_tmrb_pwm_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcPwmInit is NULL
 */
en_result_t TMRB_PWM_StructInit(stc_tmrb_pwm_init_t *pstcPwmInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    if (NULL != pstcPwmInit)
    {
        pstcPwmInit->u16CompareValue = 0xFFFFU;
        pstcPwmInit->u16StartPolarity = TMRB_PWM_LOW;
        pstcPwmInit->u16StopPolarity = TMRB_PWM_LOW;
        pstcPwmInit->u16MatchPolarity = TMRB_PWM_LOW;
        pstcPwmInit->u16PeriodPolarity = TMRB_PWM_LOW;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize the TMRB PWM.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH2:         TMRB channel 2
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH4:         TMRB channel 4
 *           @arg TMRB_CH5:         TMRB channel 5
 *           @arg TMRB_CH6:         TMRB channel 6
 * @retval None
 * @note   TMRB channel 5&6 only output inner signal and don't support TIMB_t_PWMn(n=1~4) port function.
 */
void TMRB_PWM_DeInit(CM_TMRB_TypeDef *TMRBx, uint32_t u32Ch)
{
    __IO uint16_t *TMRB_BCONR;
    __IO uint16_t *TMRB_PCONR;
    __IO uint16_t *TMRB_CMPAR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_CH(u32Ch));

    TMRB_CMPAR = TMRB_CMPARx(TMRBx, u32Ch);

    /* Configures the registers to reset value. */
    if (IS_TMRB_PWM_CH(u32Ch))
    {
        TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
        WRITE_REG16(*TMRB_PCONR, 0x0000U);
    }

    if (IS_TMRB_BUF_CH(u32Ch))
    {
        TMRB_BCONR = TMRB_BCONRx(TMRBx, u32Ch);
        WRITE_REG16(*TMRB_BCONR, 0x0000U);
    }

    WRITE_REG16(*TMRB_CMPAR, 0xFFFFU);
    WRITE_REG16(TMRBx->STFLR, (1UL << u32Ch));
}

/**
 * @brief  Enable or disable the TMRB PWM TIMB_t_PWMn(n=1~4) port function.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH2:         TMRB channel 2
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH4:         TMRB channel 4
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the TMRB PWM TIMB_t_PWMn(n=1~4) port function.
 *           @arg Disable:          Disable the TMRB PWM TIMB_t_PWMn(n=1~4) port function.
 * @retval None
 * @note   TMRB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_PWM_Cmd(CM_TMRB_TypeDef *TMRBx,
                        uint32_t u32Ch,
                        en_functional_state_t enNewState)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    if (Enable == enNewState)
    {
        SET_REG16_BIT(*TMRB_PCONR, TMRB_PCONR_OUTEN);
    }
    else
    {
        CLEAR_REG16_BIT(*TMRB_PCONR, TMRB_PCONR_OUTEN);
    }
}

/**
 * @brief  Set TIMB_<t>_PWMn(t=1,n=1~4) port output polarity.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH2:         TMRB channel 2
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH4:         TMRB channel 4
 * @param  [in] u16CountState       TMRB count state
 *         This parameter can be one of the following values:
 *           @arg TMRB_PWM_CNT_START:  The TMRB start count
 *           @arg TMRB_PWM_CNT_STOP:   The TMRB stop count
 *           @arg TMRB_PWM_CNT_MATCH:  The TMRB compare match
 *           @arg TMRB_PWM_CNT_PERIOD: The TMRB period match
 * @param  [in] u16Polarity         TMRB TIMB_<t>_PWMn port output polarity
 *         This parameter can be one of the following values:
 *           @arg TMRB_PWM_LOW:  TIM_<t>_PWMn(t=1,n=1~4) output low level
 *           @arg TMRB_PWM_HIGH: TIM_<t>_PWMn(t=1,n=1~4) output high level
 *           @arg TMRB_PWM_HOLD: TIM_<t>_PWMn(t=1,n=1~4) output hold level
 *           @arg TMRB_PWM_INVT: TIM_<t>_PWMn(t=1,n=1~4) output inverted level
 * @retval None
 * @note   TMRB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_PWM_SetPolarity(CM_TMRB_TypeDef *TMRBx,
                          uint32_t u32Ch,
                          uint16_t u16CountState,
                          uint16_t u16Polarity)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_PWM_POLARITY(u16CountState, u16Polarity));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_PCONR, (((uint16_t)3U) << u16CountState), (u16Polarity << u16CountState));
}

/**
 * @brief  Set TIMB_<t>_PWMn(t=1,n=1~4) port force output polarity.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @param  [in] u32Ch               TMRB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:         TMRB channel 1
 *           @arg TMRB_CH2:         TMRB channel 2
 *           @arg TMRB_CH3:         TMRB channel 3
 *           @arg TMRB_CH4:         TMRB channel 4
 * @param  [in] u16Polarity         TMRB TIMB_<t>_PWMn port output polarity
 *         This parameter can be one of the following values:
 *           @arg TMRB_PWM_FORCE_INVD: Invalid
 *           @arg TMRB_PWM_FORCE_LOW:  Force TIM_<t>_PWMn(t=1,n=1~4) output low level
 *           @arg TMRB_PWM_FORCE_HIGH: Force TIM_<t>_PWMn(t=1,n=1~4) force output high level
 * @retval None
 * @note   TMRB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_PWM_SetForcePolarity(CM_TMRB_TypeDef *TMRBx,
                          uint32_t u32Ch,
                          uint16_t u16Polarity)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_PWM_FORCE_POLARITY(u16Polarity));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_PCONR, TMRB_PCONR_FORC, u16Polarity);
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup TMRB_Local_Functions TMRB Local Functions
 * @{
 */

/**
 * @brief Get TMRB trigger selection register of the specified TMRB unit.
 * @param  [in] TMRBx               Pointer to TMRB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_TMRB:          TMRB unit instance register base
 * @retval TMRB trigger selection register
 */
static __IO uint32_t* TMRB_HTSSR(const CM_TMRB_TypeDef *TMRBx)
{
    __IO uint32_t *HTSSRx = NULL;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_UNIT(TMRBx));

    if (CM_TMRB == TMRBx)
    {
        HTSSRx = &CM_AOS->TMRB_HTSSR;
    }

    return HTSSRx;
}

/**
 * @}
 */

#endif /* DDL_TMRB_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
