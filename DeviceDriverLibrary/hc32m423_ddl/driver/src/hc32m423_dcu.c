/**
 *******************************************************************************
 * @file  hc32m423_dcu.c
 * @brief This file provides firmware functions to manage the DCU.
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
#include "hc32m423_dcu.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_DCU DCU
 * @brief DCU Driver Library
 * @{
 */

#if (DDL_DCU_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DCU_Local_Macros DCU Local Macros
 * @{
 */

/**
 * @defgroup DCU_Check_Parameters_Validity DCU Check Parameters Validity
 * @{
 */
#define IS_DCU_UNIT(x)                          ((x) == CM_DCU)

#define IS_DCU_MD(x)                                                           \
(   ((x) == DCU_MD_INVD)                        ||                             \
    ((x) == DCU_MD_CMP)                         ||                             \
    ((x) == DCU_MD_ADD)                         ||                             \
    ((x) == DCU_MD_SUB)                         ||                             \
    ((x) == DCU_MD_HW_ADD)                      ||                             \
    ((x) == DCU_MD_HW_SUB))

#define IS_DCU_FLAG(x)                                                         \
(   ((x) != 0UL)                                &&                             \
    (((x) | DCU_FLAG_ALL) == DCU_FLAG_ALL))

#define IS_DCU_INT_CATEGORY(x)                                                 \
(   ((x) == DCU_CATEGORY_OP)                    ||                             \
    ((x) == DCU_CATEGORY_CMP_WIN)               ||                             \
    ((x) == DCU_CATEGORY_CMP_NON_WIN))

#define IS_DCU_INT_OP(x)                        ((x) == DCU_INT_OP_CARRY)

#define IS_DCU_INT_CMP_WIN(x)                                                  \
(   ((x) == DCU_INT_CMP_WIN_INSIDE)             ||                             \
    ((x) == DCU_INT_CMP_WIN_OUTSIDE))

#define IS_DCU_INT_CMP_NON_WIN(x)                                              \
(   ((x) != 0UL)                                ||                             \
    (((x) | DUC_INT_CMP_NON_WIN_ALL) == DUC_INT_CMP_NON_WIN_ALL))

#define IS_DCU_CMP_TRIG_MD(x)                                                  \
(   ((x) == DCU_CMP_TRIG_DATA0)                 ||                             \
    ((x) == DCU_CMP_TRIG_DATA012))

#define IS_DCU_DATA_WIDTH(x)                                                    \
(   ((x) == DCU_DATA_WIDTH_8BIT)                ||                             \
    ((x) == DCU_DATA_WIDTH_16BIT)               ||                             \
    ((x) == DCU_DATA_WIDTH_32BIT))

#define IS_DCU_DATA_REG(x)                                                     \
(   ((x) == DCU_DATA0_IDX)                      ||                             \
    ((x) == DCU_DATA1_IDX)                      ||                             \
    ((x) == DCU_DATA2_IDX))
/**
 * @}
 */

/**
 * @defgroup DCU_Register_Address Get DCU register address
 * @{
 */
#define DCU_REG_ADDR(_REG_)                 ((uint32_t)(&(_REG_)))
#define DCU_DATA_REG_ADDR(_UNITx_, _IDX_)   (DCU_REG_ADDR((_UNITx_)->DATA0) + ((_IDX_) << 2UL))

#define DCU_DATA_REG8(_UNITx_, _IDX_)       (*(__IO uint8_t *)DCU_DATA_REG_ADDR(_UNITx_, _IDX_))
#define DCU_DATA_REG16(_UNITx_, _IDX_)      (*(__IO uint16_t *)DCU_DATA_REG_ADDR(_UNITx_, _IDX_))
#define DCU_DATA_REG32(_UNITx_, _IDX_)      (*(__IO uint32_t *)DCU_DATA_REG_ADDR(_UNITx_, _IDX_))
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
 * @addtogroup DCU_Local_Functions
 * @{
 */
static __IO uint32_t* DCU_TRGSELx(const CM_DCU_TypeDef *DCUx);
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
 * @defgroup DCU_Global_Functions DCU Global Functions
 * @{
 */

/**
 * @brief  Initialize DCU function.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] pstcDcuInit         Pointer to a @ref stc_dcu_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcDcuInit is NULL
 */
en_result_t DCU_Init(CM_DCU_TypeDef *DCUx, const stc_dcu_init_t *pstcDcuInit)
{
    uint32_t u32Value;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcDcuInit)
    {
        DDL_ASSERT(IS_DCU_UNIT(DCUx));
        DDL_ASSERT(IS_DCU_MD(pstcDcuInit->u32Mode));
        DDL_ASSERT(IS_DCU_DATA_WIDTH(pstcDcuInit->u32DataWidth));
        DDL_ASSERT(IS_DCU_CMP_TRIG_MD(pstcDcuInit->u32CompareTriggerMode));

        /* Set register: CTL */
        u32Value = (pstcDcuInit->u32Mode | \
                     pstcDcuInit->u32DataWidth | \
                     pstcDcuInit->u32CompareTriggerMode);
        WRITE_REG32(DCUx->CTL, u32Value);

        /* Disable interrupt */
        WRITE_REG32(DCUx->INTSEL, 0x00000000UL);

        /* Clear Flag */
        WRITE_REG32(DCUx->FLAGCLR, 0x0000007FUL);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_uart_init_t to default values.
 * @param  [out] pstcDcuInit        Pointer to a @ref stc_dcu_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcDcuInit is NULL
 */
en_result_t DCU_StructInit(stc_dcu_init_t *pstcDcuInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    if (NULL != pstcDcuInit)
    {
        pstcDcuInit->u32Mode = DCU_MD_INVD;
        pstcDcuInit->u32DataWidth = DCU_DATA_WIDTH_8BIT;
        pstcDcuInit->u32CompareTriggerMode = DCU_CMP_TRIG_DATA0;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize DCU function.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @retval None
 */
en_result_t DCU_DeInit(CM_DCU_TypeDef *DCUx)
{
    /* Configures the registers to reset value. */
    WRITE_REG32(DCUx->CTL, 0x00000000UL);
    WRITE_REG32(DCUx->INTSEL, 0x00000000UL);

    /* Clear Flag */
    WRITE_REG32(DCUx->FLAGCLR, 0x0000007FUL);

    return Ok;
}

/**
 * @brief  Set DCU operation mode.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32Mode             DCU mode
 *         This parameter can be one of the following values:
 *           @arg DCU_MD_INVD:      DCU invalid
 *           @arg DCU_MD_CMP:          DCU compare
 *           @arg DCU_MD_ADD:          DCU add operation
 *           @arg DCU_MD_SUB:          DCU sub operation
 *           @arg DCU_MD_HW_ADD:       DCU hardware trigger add
 *           @arg DCU_MD_HW_SUB:       DCU hardware trigger sub
 * @retval None
 */
void DCU_SetMode(CM_DCU_TypeDef *DCUx, uint32_t u32Mode)
{
    /* Check for DCUx pointer */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_MD(u32Mode));

    MODIFY_REG32(DCUx->CTL, DCU_CTL_MODE, u32Mode);
}

/**
 * @brief  Set DCU data width.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32DataWidth        DCU data width
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA_WIDTH_8BIT:  DCU data size 8 bit
 *           @arg DCU_DATA_WIDTH_16BIT: DCU data size 16 bit
 *           @arg DCU_DATA_WIDTH_32BIT: DCU data size 32 bit
 * @retval None
 */
void DCU_SetDataWidth(CM_DCU_TypeDef *DCUx, uint32_t u32DataWidth)
{
    /* Check for DCUx pointer */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_WIDTH(u32DataWidth));

    MODIFY_REG32(DCUx->CTL, DCU_CTL_DATASIZE, u32DataWidth);
}

/**
 * @brief  Get DCU flag.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32Flag             The specified DCU flag
 *         This parameter can be any composed value of the following values:
 *           @arg DCU_FLAG_CARRY:          DCU addition overflow or subtraction underflow flag
 *           @arg DCU_FLAG_DATA0_LT_DATA2: DCU DATA0 < DATA2 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA2: DCU DATA0 = DATA2 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA2: DCU DATA0 > DATA2 flag
 *           @arg DCU_FLAG_DATA0_LT_DATA1: DCU DATA0 < DATA1 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA1: DCU DATA0 = DATA1 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA1: DCU DATA0 > DATA1 flag
 * @retval Returned value can be one of the following values:
 *           - Set:   Any bit of the composed flag is set.
 *           - Reset: All bit of the composed flag is reset.
 */
en_flag_status_t DCU_GetStatus(const CM_DCU_TypeDef *DCUx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_FLAG(u32Flag));

    return (READ_REG32_BIT(DCUx->FLAG, u32Flag) == 0UL) ? Reset : Set;
}

/**
 * @brief  Clear DCU flag.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32Flag             The specified DCU flag
 *         This parameter can be any composed value of the following values:
 *           @arg DCU_FLAG_CARRY:          DCU addition overflow or subtraction underflow flag
 *           @arg DCU_FLAG_DATA0_LT_DATA2: DCU DATA0 < DATA2 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA2: DCU DATA0 = DATA2 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA2: DCU DATA0 > DATA2 flag
 *           @arg DCU_FLAG_DATA0_LT_DATA1: DCU DATA0 < DATA1 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA1: DCU DATA0 = DATA1 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA1: DCU DATA0 > DATA1 flag
 * @retval None
 */
void DCU_ClearStatus(CM_DCU_TypeDef *DCUx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_FLAG(u32Flag));

    WRITE_REG32(DCUx->FLAGCLR, u32Flag);
}

/**
 * @brief  Enable or disable DCU interupt function.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the DCU interupt function.
 *           @arg Disable:          Disable the DCU interupt function.
 * @retval None
 */
void DCU_GlobalIntCmd(CM_DCU_TypeDef *DCUx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(DCUx->CTL, DCU_CTL_INTEN);
    }
    else
    {
        CLEAR_REG32_BIT(DCUx->CTL, DCU_CTL_INTEN);
    }
}

/**
 * @brief  Enable or disable the specified DCU interupt.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32Category         DCU interrupt
 *         This parameter can be one of the following values:
 *           @arg DCU_CATEGORY_OP:          DCU operation result(overflow/underflow) interrupt
 *           @arg DCU_CATEGORY_CMP_WIN:     DCU comparison(window) interrupt
 *           @arg DCU_CATEGORY_CMP_NON_WIN: DCU comparison(non-window) interrupt
 * @param  [in] u32IntType          DCU interrupt
 *         This parameter can be one of the following case:
 *         a. this parameter can be one of the following values when u32Category = DCU_CATEGORY_OP:
 *           @arg DCU_INT_OP_CARRY: DCU addition overflow or subtraction underflow interrupt
 *         b. this parameter can be one of the following values when u32Category = DCU_CATEGORY_CMP_WIN:
 *           @arg DCU_INT_CMP_WIN_INSIDE:DCU comparison(DATA2 <= DATA0 <= DATA1) interrupt
 *           @arg DCU_INT_CMP_WIN_OUTSIDE: DCU comparison(DATA0 < DATA2 & DATA0 > DATA1 ) interrupt
 *           @note Only one of the window inside and outside interrupt is valid.
 *           @note Both of the window inside and outside interrupt is disabled and the window interrupt is invalid.
 *           @note Both of the window inside and outside interrupt is enabled and the compare mode interrupt is invalid.
 *         c. this parameter can be any composed value of the following values when u32Category = DCU_CATEGORY_CMP_NON_WIN:
 *           @arg DCU_INT_CMP_DATA0_LT_DATA2: DCU DATA0 < DATA2 interrupt
 *           @arg DCU_INT_CMP_DATA0_EQ_DATA2: DCU DATA0 = DATA2 interrupt
 *           @arg DCU_INT_CMP_DATA0_GT_DATA2: DCU DATA0 > DATA2 interrupt
 *           @arg DCU_INT_CMP_DATA0_LT_DATA1: DCU DATA0 < DATA1 interrupt
 *           @arg DCU_INT_CMP_DATA0_EQ_DATA1: DCU DATA0 = DATA1 interrupt
 *           @arg DCU_INT_CMP_DATA0_GT_DATA1: DCU DATA0 > DATA1 interrupt
 *           @note Both of the window inside and outside interrupt is disabled and the compare non-window interrupt is valid.
 * @param   [in] enNewState         The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified DCU interupt.
 *           @arg Disable:          Disable the specified DCU interupt.
 * @retval None
 */
void DCU_IntCmd(CM_DCU_TypeDef *DCUx,
                uint32_t u32Category,
                uint32_t u32IntType,
                en_functional_state_t enNewState)
{
    uint32_t u32Type;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_INT_CATEGORY(u32Category));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DCU_CATEGORY_OP == u32Category)
    {
        DDL_ASSERT(IS_DCU_INT_OP(u32IntType));
        u32Type = (u32IntType & DCU_INT_OP_CARRY);
    }
    else if (DCU_CATEGORY_CMP_WIN == u32Category)
    {
        DDL_ASSERT(IS_DCU_INT_CMP_WIN(u32IntType));
        u32Type = (u32IntType & (DCU_INT_CMP_WIN_INSIDE | DCU_INT_CMP_WIN_OUTSIDE));
    }
    else
    {
        DDL_ASSERT(IS_DCU_INT_CMP_NON_WIN(u32IntType));
        u32Type = (u32IntType & DUC_INT_CMP_NON_WIN_ALL);
    }

    if (Enable == enNewState)
    {
        SET_REG32_BIT(DCUx->INTSEL, u32Type);
    }
    else
    {
        CLEAR_REG32_BIT(DCUx->INTSEL, u32Type);
    }
}

/**
 * @brief  Set compare interrupt mode.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32Mode             The compare interrupt mode
 *         This parameter can be one of the following values:
 *           @arg DCU_CMP_TRIG_DATA0:   DCU compare triggered by DATA0
 *           @arg DCU_CMP_TRIG_DATA012: DCU compare triggered by DATA0 or DATA1 or DATA2
 * @retval None
 */
void DCU_SetCompareTriggerMode(CM_DCU_TypeDef *DCUx, uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_CMP_TRIG_MD(u32Mode));

    MODIFY_REG32(DCUx->INTSEL, DCU_CTL_COMP_TRG, u32Mode);
}

/**
 * @brief  Set the specified event trigger source for DCU.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] enEventSrc          The trigger event source
 *           @arg This parameter can be any value of @ref en_event_src_t
 * @retval None
 */
void DCU_SetTriggerSrc(const CM_DCU_TypeDef *DCUx, en_event_src_t enEventSrc)
{
    __IO uint32_t *const TRGSELx = DCU_TRGSELx(DCUx);

    if (NULL != TRGSELx)
    {
        WRITE_REG32(*TRGSELx, enEventSrc);
    }
}

/**
 * @brief  Read DCU register DATA0 for byte.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32DataIndex        DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:    DCU DATA0
 *           @arg DCU_DATA1_IDX:    DCU DATA1
 *           @arg DCU_DATA2_IDX:    DCU DATA2
 * @retval DCU register DATA value for byte
 */
uint8_t DCU_ReadData8(const CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    return READ_REG8(DCU_DATA_REG8(DCUx, u32DataIndex));
}

/**
 * @brief  Write DCU register DATA for byte.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32DataIndex        DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:    DCU DATA0
 *           @arg DCU_DATA1_IDX:    DCU DATA1
 *           @arg DCU_DATA2_IDX:    DCU DATA2
 * @param  [in] u8Data              The data to write.
 * @retval None
 */
void DCU_WriteData8(CM_DCU_TypeDef *DCUx,
                    uint32_t u32DataIndex,
                    uint8_t u8Data)
{
    __IO uint8_t *DATA;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = &DCU_DATA_REG8(DCUx, u32DataIndex);
    WRITE_REG8(*DATA, u8Data);
}

/**
 * @brief  Read DCU register DATA for half-word.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32DataIndex        DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:    DCU DATA0
 *           @arg DCU_DATA1_IDX:    DCU DATA1
 *           @arg DCU_DATA2_IDX:    DCU DATA2
 * @retval DCU register DATA value for half-word.
 */
uint16_t DCU_ReadData16(const CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    return READ_REG16(DCU_DATA_REG16(DCUx, u32DataIndex));
}

/**
 * @brief  Write DCU register DATA for half-word.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32DataIndex        DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:    DCU DATA0
 *           @arg DCU_DATA1_IDX:    DCU DATA1
 *           @arg DCU_DATA2_IDX:    DCU DATA2
 * @param  [in] u16Data             The data to write.
 * @retval None
 */
void DCU_WriteData16(CM_DCU_TypeDef *DCUx,
                        uint32_t u32DataIndex,
                        uint16_t u16Data)
{
    __IO uint16_t *DATA;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = &DCU_DATA_REG16(DCUx, u32DataIndex);
    WRITE_REG16(*DATA, u16Data);
}

/**
 * @brief  Read DCU register DATA for word.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32DataIndex        DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:    DCU DATA0
 *           @arg DCU_DATA1_IDX:    DCU DATA1
 *           @arg DCU_DATA2_IDX:    DCU DATA2
 * @retval DCU register DATA value for word
 */
uint32_t DCU_ReadData32(const CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    return READ_REG32(DCU_DATA_REG32(DCUx, u32DataIndex));
}

/**
 * @brief  Write DCU register DATA0 for word.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @param  [in] u32DataIndex        DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:    DCU DATA0
 *           @arg DCU_DATA1_IDX:    DCU DATA1
 *           @arg DCU_DATA2_IDX:    DCU DATA2
 * @param  [in] u32Data             The data to write.
 * @retval None
 */
void DCU_WriteData32(CM_DCU_TypeDef *DCUx,
                        uint32_t u32DataIndex,
                        uint32_t u32Data)
{
    __IO uint32_t *DATA;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = &DCU_DATA_REG32(DCUx, u32DataIndex);
    WRITE_REG32(*DATA, u32Data);
}

/**
 * @brief  Get DCU trigger register pointer.
 * @param  [in] DCUx                Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU:           DCU unit instance register base
 * @retval DCU trigger register pointer
 */
static __IO uint32_t* DCU_TRGSELx(const CM_DCU_TypeDef *DCUx)
{
    __IO uint32_t *TRGSELx = NULL;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));

    if (CM_DCU == DCUx)
    {
        TRGSELx = &CM_AOS->DCU_TRGSEL;
    }

    return TRGSELx;
}

/**
 * @}
 */

#endif /* DDL_DCU_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
