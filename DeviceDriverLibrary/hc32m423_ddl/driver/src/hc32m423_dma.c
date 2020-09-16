/**
 *******************************************************************************
 * @file  hc32m423_dma.c
 * @brief This file provides firmware functions to manage the Direct Memory
 *        Access (DMA).
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
#include "hc32m423_dma.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_DMA DMA
 * @brief Direct Memory Access Driver Library
 * @{
 */

#if (DDL_DMA_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DMA_Local_Macros DMA Local Macros
 * @{
 */
#define DMA_CH_REG(reg_base, ch)    (*(uint32_t *)((uint32_t)(&(reg_base)) + ((ch) * 0x40UL)))

/**
 * @defgroup DMA_Check_Parameters_Validity DMA Check Parameters Validity
 * @{
 */
/*! Parameter valid check for DMA unit. */
#define IS_VALID_DMA_UNIT(x)                    ((x) == CM_DMA)

/*! Parameter valid check for DMA Channel. */
#define IS_VALID_DMA_CH(ch)                     ((ch) <= DMA_CH3)

/*! Parameter valid check for DMA multiplex channel. */
#define IS_VALID_DMA_MX_CH(x)                                                  \
(   ((x) != 0x00UL)                             &&                             \
    (((x) | DMA_MX_CH_ALL) == DMA_MX_CH_ALL))

/*! Parameter valid check for DMA channel status. */
#define IS_VALID_DMA_TRANS_STAT(x)                                             \
(   ((x) != 0x00000000UL)                       &&                             \
    (((x) | DMA_TRANS_STAT_MASK) == DMA_TRANS_STAT_MASK))

/*! Parameter valid check for DMA block size. */
#define IS_VALID_DMA_BLOCK_SIZE(x)              ((x) < 256U)

/*! Parameter valid check for DMA transfer count. */
#define IS_VALID_DMA_TRANS_CNT(x)               ((x) < 1024U)

/*! Parameter valid check for DMA transfer data width. */
#define IS_VALID_DMA_DATA_WIDTH(x)                                             \
(   ((x) == DMA_DATA_WIDTH_8BIT)                ||                             \
    ((x) == DMA_DATA_WIDTH_16BIT)               ||                             \
    ((x) == DMA_DATA_WIDTH_32BIT))

/*! Parameter valid check for DMA source address mode. */
#define IS_VALID_DMA_SRCADDR_MD(x)                                             \
(   ((x) == DMA_SRC_ADDR_MD_FIX)                ||                             \
    ((x) == DMA_SRC_ADDR_MD_INC)                ||                             \
    ((x) == DMA_SRC_ADDR_MD_DEC))

/*! Parameter valid check for DMA destination address mode. */
#define IS_VALID_DMA_DESTADDR_MD(x)                                            \
(   ((x) == DMA_DEST_ADDR_MD_FIX)               ||                             \
    ((x) == DMA_DEST_ADDR_MD_INC)               ||                             \
    ((x) == DMA_DEST_ADDR_MD_DEC))

/*! Parameter valid check for DMA link-list-pointer. */
#define IS_VALID_DMA_LLP(x)                                                    \
(   ((x) == DMA_LLP_ENABLE)                     ||                             \
    ((x) == DMA_LLP_DISABLE))

/*! Parameter valid check for DMA link-list-pointer mode. */
#define IS_VALID_DMA_LLP_MD(x)                                                 \
(   ((x) == DMA_LLP_RUN)                        ||                             \
    ((x) == DMA_LLP_WAIT))

/*! Parameter valid check for DMA link-list-pointer descriptor base address mode. */
#define IS_VALID_DMA_LLP_ADDR_MD(x)                                            \
(   ((x) == DMA_LLP_ADDR_ROM)                   ||                             \
    ((x) == DMA_LLP_ADDR_RAM))

/*! Parameter valid check for DMA link-list-pointer descriptor base address. */
#define IS_VALID_DMA_LLP_ADDR(x)                                               \
(   ((x) <= 0x0001FFFFUL)                       ||                             \
    (((x) >= 0x1FFFE000UL)                      &&                             \
    ((x) <= 0x20001FFFUL))                      ||                             \
    (((x) >= 0x22000000UL)                      &&                             \
    ((x) <= 0x23FFFFFFUL))                      ||                             \
    (((x) >= 0x40010000UL)                      &&                             \
    ((x) <= 0x40010BFFUL))                      ||                             \
    (((x) >= 0x40015000UL)                      &&                             \
    ((x) <= 0x40015FFFUL))                      ||                             \
    (((x) >= 0x40017000UL)                      &&                             \
    ((x) <= 0x400173FFUL))                      ||                             \
    (((x) >= 0x40017C00UL)                      &&                             \
    ((x) <= 0x40017FFFUL))                      ||                             \
    (((x) >= 0x4001C000UL)                      &&                             \
    ((x) <= 0x4001C3FFUL))                      ||                             \
    (((x) >= 0x4001D000UL)                      &&                             \
    ((x) <= 0x4001D7FFUL))                      ||                             \
    (((x) >= 0x40021000UL)                      &&                             \
    ((x) <= 0x400217FFUL))                      ||                             \
    (((x) >= 0x40024000UL)                      &&                             \
    ((x) <= 0x400247FFUL))                      ||                             \
    (((x) >= 0x40025000UL)                      &&                             \
    ((x) <= 0x400253FFUL))                      ||                             \
    (((x) >= 0x40030000UL)                      &&                             \
    ((x) <= 0x400303FFUL))                      ||                             \
    (((x) >= 0x40048400UL)                      &&                             \
    ((x) <= 0x400487FFUL))                      ||                             \
    (((x) >= 0x40049000UL)                      &&                             \
    ((x) <= 0x400497FFUL))                      ||                             \
    (((x) >= 0x4004A000UL)                      &&                             \
    ((x) <= 0x4004A3FFUL))                      ||                             \
    (((x) >= 0x4004E000UL)                      &&                             \
    ((x) <= 0x4004E3FFUL))                      ||                             \
    (((x) >= 0x40050400UL)                      &&                             \
    ((x) <= 0x400507FFUL))                      ||                             \
    (((x) >= 0x40051000UL)                      &&                             \
    ((x) <= 0x400523FFUL))                      ||                             \
    (((x) >= 0x40053000UL)                      &&                             \
    ((x) <= 0x400533FFUL))                      ||                             \
    (((x) >= 0x40053800UL)                      &&                             \
    ((x) <= 0x400547FFUL))                      ||                             \
    (((x) >= 0x42000000UL)                      &&                             \
    ((x) <= 0x43FFFFFFUL)))

/*! Parameter valid check for DMA repeat mode */
#define IS_VALID_DMA_RPT_MD(x)                                                 \
(   ((x) == DMA_RPT_ENABLE)                     ||                             \
    ((x) == DMA_RPT_DISABLE))

/*! Parameter valid check for DMA source & destination address repeat selection. */
#define IS_VALID_DMA_RPT_SEL(x)                                                \
(   ((x) == DMA_SRC_RPT)                        ||                             \
    ((x) == DMA_DEST_RPT))

/*! Parameter valid check for DMA non_sequence mode */
#define IS_VALID_DMA_NONSEQ_MD(x)                                              \
(   ((x) == DMA_NONSEQ_ENABLE)                  ||                             \
    ((x) == DMA_NONSEQ_DISABLE))

/*! Parameter valid check for DMA source & destination address non_sequence selection. */
#define IS_VALID_DMA_NONSEQ_SEL(x)                                             \
(   ((x) == DMA_SRC_NONSEQ)                     ||                             \
    ((x) == DMA_DEST_NONSEQ))

/*! Parameter valid check for DMA non-sequence transfer count. */
#define IS_VALID_DMA_NONSEQ_CNT(x)              ((x) < 256U)

/*! Parameter valid check for DMA non-sequence offset. */
#define IS_VALID_DMA_NONSEQ_OFFSET(x)           ((x) < (1UL << 16U))

/*! Parameter valid check for DMA error interrupt. */
#define IS_VALID_DMA_ERR_INT(x)                                                \
(   ((x) != 0x00000000UL)                       &&                             \
    (((x) | DMA_ERR_INT_MASK) == DMA_ERR_INT_MASK))


/*! Parameter valid check for DMA transfer interrupt. */
#define IS_VALID_DMA_TRANS_INT(x)                                              \
(   ((x) != 0x00000000UL)                       &&                             \
    (((x) | DMA_TRANS_INT_MASK) == DMA_TRANS_INT_MASK))

#define DMA_LLP_RAM_ADDR                        (0x1FFFE000U)
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
 * @defgroup DMA_Global_Functions DMA Global Functions
 * @{
 */

/**
 * @brief  Enable or disable the DMA.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] enNewState              The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DMA_Cmd(CM_DMA_TypeDef *DMAx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Enable or Disable DMA */
    WRITE_REG32(DMAx->EN, enNewState);
}

/**
 * @brief  Enable or disable the specified DMA error interrupt.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] enNewState           The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @param  [in] u32ErrInt       DMA error IRQ flag.
 *   @arg  DMA_REQ_ERR_CH0.
 *   @arg  DMA_REQ_ERR_CH1.
 *   @arg  DMA_REQ_ERR_CH2.
 *   @arg  DMA_REQ_ERR_CH3.
 *   @arg  DMA_TRANS_ERR_CH0.
 *   @arg  DMA_TRANS_ERR_CH1.
 *   @arg  DMA_TRANS_ERR_CH2.
 *   @arg  DMA_TRANS_ERR_CH3.
 * @retval None
 */
void DMA_ErrIntCmd(CM_DMA_TypeDef *DMAx, uint32_t u32ErrInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_DMA_ERR_INT(u32ErrInt));

    if (Disable == enNewState)
    {
        SET_REG32_BIT(DMAx->INTMASK0, u32ErrInt);
    }
    else
    {
        CLEAR_REG32_BIT(DMAx->INTMASK0, u32ErrInt);
    }
}

/**
 * @brief  Get DMA error IRQ status.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32ErrInt DMA error IRQ flag.
 *   @arg  DMA_REQ_ERR_CH0.
 *   @arg  DMA_REQ_ERR_CH1.
 *   @arg  DMA_REQ_ERR_CH2.
 *   @arg  DMA_REQ_ERR_CH3.
 *   @arg  DMA_TRANS_ERR_CH0.
 *   @arg  DMA_TRANS_ERR_CH1.
 *   @arg  DMA_TRANS_ERR_CH2.
 *   @arg  DMA_TRANS_ERR_CH3.
 * @retval en_flag_status_t
 */
en_flag_status_t DMA_GetErrIntStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32ErrInt)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_ERR_INT(u32ErrInt));

    return (READ_REG32_BIT(DMAx->INTSTAT0, u32ErrInt) ? Set : Reset);
}

/**
 * @brief  Clear DMA error IRQ status.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32ErrInt DMA error IRQ flag.
 *   @arg  DMA_REQ_ERR_CH0.
 *   @arg  DMA_REQ_ERR_CH1.
 *   @arg  DMA_REQ_ERR_CH2.
 *   @arg  DMA_REQ_ERR_CH3.
 *   @arg  DMA_TRANS_ERR_CH0.
 *   @arg  DMA_TRANS_ERR_CH1.
 *   @arg  DMA_TRANS_ERR_CH2.
 *   @arg  DMA_TRANS_ERR_CH3.
 * @retval en_flag_status_t
 */
void DMA_ClearErrIntStatus(CM_DMA_TypeDef *DMAx, uint32_t u32ErrInt)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_ERR_INT(u32ErrInt));

    SET_REG32_BIT(DMAx->INTCLR0, u32ErrInt);
}

/**
 * @brief  Enable or disable the specified DMA transfer interrupt.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] enNewState           The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @param  [in] u32TransInt DMA transfer IRQ flag.
 *   @arg  DMA_INT_BTC0
 *   @arg  DMA_INT_BTC1
 *   @arg  DMA_INT_BTC2
 *   @arg  DMA_INT_BTC3
 *   @arg  DMA_INT_TC0
 *   @arg  DMA_INT_TC1
 *   @arg  DMA_INT_TC2
 *   @arg  DMA_INT_TC3
 * @retval None
 */
void DMA_TransIntCmd(CM_DMA_TypeDef *DMAx, uint32_t u32TransInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_TRANS_INT(u32TransInt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Disable == enNewState)
    {
        SET_REG32_BIT(DMAx->INTMASK1, u32TransInt);
    }
    else
    {
        CLEAR_REG32_BIT(DMAx->INTMASK1, u32TransInt);
    }
}

/**
 * @brief  Get DMA transfer IRQ status.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32TransInt DMA transfer IRQ flag.
 *   @arg  DMA_INT_BTC0
 *   @arg  DMA_INT_BTC1
 *   @arg  DMA_INT_BTC2
 *   @arg  DMA_INT_BTC3
 *   @arg  DMA_INT_TC0
 *   @arg  DMA_INT_TC1
 *   @arg  DMA_INT_TC2
 *   @arg  DMA_INT_TC3
 * @retval en_flag_status_t
 */
en_flag_status_t DMA_GetTransIntStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32TransInt)
{
    DDL_ASSERT(IS_VALID_DMA_TRANS_INT(u32TransInt));
    return (READ_REG32_BIT(DMAx->INTSTAT1, u32TransInt) ? Set : Reset);
}

/**
 * @brief  Clear DMA transfer IRQ status.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32TransInt DMA transfer IRQ flag.
 *   @arg  DMA_INT_BTC0
 *   @arg  DMA_INT_BTC1
 *   @arg  DMA_INT_BTC2
 *   @arg  DMA_INT_BTC3
 *   @arg  DMA_INT_TC0
 *   @arg  DMA_INT_TC1
 *   @arg  DMA_INT_TC2
 *   @arg  DMA_INT_TC3
 * @retval None
 */
void DMA_ClearTransIntStatus(CM_DMA_TypeDef *DMAx, uint32_t u32TransInt)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_TRANS_INT(u32TransInt));

    SET_REG32_BIT(DMAx->INTCLR1, u32TransInt);
}

/**
 * @brief  DMA multiplex channel function config.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32MxCh DMA multiplex channel.
 *   @arg  DMA_MX_CH0.
 *   @arg  DMA_MX_CH1.
 *   @arg  DMA_MX_CH2.
 *   @arg  DMA_MX_CH3.
 *   @arg  DMA_MX_CH_ALL.
 * @param  [in] enNewState The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DMA_MxChCmd(CM_DMA_TypeDef *DMAx, uint32_t u32MxCh, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_MX_CH(u32MxCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(DMAx->CHEN, u32MxCh);
    }
    else
    {
        SET_REG32_BIT(DMAx->CHENCLR, u32MxCh);
    }
}

/**
 * @brief  DMA channel function config.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] enNewState The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DMA_ChCmd(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(DMAx->CHEN, ((1UL << u32Ch) & 0x0FUL));
    }
    else
    {
        SET_REG32_BIT(DMAx->CHENCLR, ((1UL << u32Ch) & 0x0FUL));
    }
}

/**
 * @brief  Get DMA transfer status.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Status DMA transfer status.
 *   @arg  DMA_TRANS_CH0.
 *   @arg  DMA_TRANS_CH1.
 *   @arg  DMA_TRANS_CH2.
 *   @arg  DMA_TRANS_CH3.
 *   @arg  DMA_TRANS_DMA.
 * @retval en_flag_status_t
 */
en_flag_status_t DMA_GetTransStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32Status)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_TRANS_STAT(u32Status));

    return (READ_REG32_BIT(DMAx->CHSTAT, u32Status) ? Set : Reset);
}

/**
 * @brief  Config DMA transfer trigger source.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] enEventSrc DMA transfer trigger source.
 *   @arg  This parameter can be @ref en_event_src_t
 * @retval None
 * @note This register belongs to AOS module, please ensure enable it in advance.
 */
void DMA_SetTriggerSrc(const CM_DMA_TypeDef *DMAx, uint32_t u32Ch, en_event_src_t enEventSrc)
{
    __IO uint32_t *TRGSELx;

    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));

    TRGSELx = (uint32_t *)((uint32_t)(&CM_AOS->DMA0_TRGSEL) + (u32Ch*4UL));

    MODIFY_REG32(*TRGSELx, AOS_DMA0_TRGSEL_TRGSEL, enEventSrc);
}

/**
 * @brief  Set the source address of the specified DMA channel.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] u32Addr The specified source address.
 * @retval None
 */
void DMA_SetSrcAddr(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, uint32_t u32Addr)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));

    /* Set source address. */
    WRITE_REG32(DMA_CH_REG(DMAx->SAR0, u32Ch), u32Addr);
}

/**
 * @brief  Set the destination address of the specified DMA channel.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] u32Addr The specified destination address.
 * @retval None
 */
void DMA_SetDestAddr(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, uint32_t u32Addr)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));

    /* Set destination address. */
    WRITE_REG32(DMA_CH_REG(DMAx->DAR0, u32Ch), u32Addr);
}

/**
 * @brief  Set the block size of the specified DMA channel.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] u8Size DMA block size (0 : 256, 1 ~ 255).
 * @retval None
 */
void DMA_SetBlockSize(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, uint8_t u8Size)
{
    __IO uint32_t *CHxCTL0;
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));

    CHxCTL0 = &DMA_CH_REG(DMAx->CH0CTL0, u32Ch);
    /* Set block size. */
    MODIFY_REG32(*CHxCTL0, DMA_CH0CTL0_BLKSIZE, ((uint32_t)u8Size << DMA_CH0CTL0_BLKSIZE_POS));
}

/**
 * @brief  Set the transfer count of the specified DMA channel.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] u16Count DMA transfer count (0: infinite, 1 ~ 1023).
 * @retval None
 */
void DMA_SetTransCount(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, uint16_t u16Count)
{
    __IO uint32_t *CHxCTL0;
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));
    DDL_ASSERT(IS_VALID_DMA_TRANS_CNT(u16Count));

    CHxCTL0 = &DMA_CH_REG(DMAx->CH0CTL0, u32Ch);
    /* Set transfer count. */
    MODIFY_REG32(*CHxCTL0, DMA_CH0CTL0_CNT, (uint32_t)u16Count << DMA_CH0CTL0_CNT_POS);
}

/**
 * @brief  Initialize DMA config structure. Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaInit Pointer to a stc_dma_init_t structure that
 *                            contains configuration information.
 * @retval Ok: DMA structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_StructInit(stc_dma_init_t *pstcDmaInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcDmaInit->u32SrcAddr         = 0x00UL;
        pstcDmaInit->u32DestAddr        = 0x00UL;
        pstcDmaInit->u32DataWidth       = DMA_DATA_WIDTH_8BIT;
        pstcDmaInit->u32BlockSize       = 0x00UL;
        pstcDmaInit->u32TransCount      = 0x01UL;
        pstcDmaInit->u32SrcAddrMode     = DMA_SRC_ADDR_MD_FIX;
        pstcDmaInit->u32DestAddrMode    = DMA_DEST_ADDR_MD_FIX;
    }
    return enRet;
}

/**
 * @brief  DMA basic function initialize.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] pstcDmaInit DMA config structure.
 *   @arg u32DataWidth      The DMA transfer data width.
 *   @arg u32BlockSize      The DMA block size.
 *   @arg u32TransCount     The DMA transfer count.
 *   @arg u32SrcAddr        The DMA source address.
 *   @arg u32DestAddr       The DMA destination address.
 *   @arg u32SrcAddrMode    The source address increment mode.
 *   @arg u32DestAddrMode   The destination address increment mode.
 * @retval Ok: DMA basic function initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_Init(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, const stc_dma_init_t *pstcDmaInit)
{
    en_result_t enRet = Ok;
    __IO uint32_t *CHxCTL0;
    __IO uint32_t *CHxCTL1;

    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));

    if (NULL == pstcDmaInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_VALID_DMA_DATA_WIDTH(pstcDmaInit->u32DataWidth));
        DDL_ASSERT(IS_VALID_DMA_SRCADDR_MD(pstcDmaInit->u32SrcAddrMode));
        DDL_ASSERT(IS_VALID_DMA_DESTADDR_MD(pstcDmaInit->u32DestAddrMode));
        DDL_ASSERT(IS_VALID_DMA_BLOCK_SIZE(pstcDmaInit->u32BlockSize));

        /* Set source address. */
        WRITE_REG32(DMA_CH_REG(DMAx->SAR0, u32Ch), pstcDmaInit->u32SrcAddr);
        /* Set destination address. */
        WRITE_REG32(DMA_CH_REG(DMAx->DAR0, u32Ch), pstcDmaInit->u32DestAddr);

        CHxCTL0 = &DMA_CH_REG(DMAx->CH0CTL0, u32Ch);
        /* Set data width, transfer count, block size. */
        MODIFY_REG32(*CHxCTL0,
                   DMA_CH0CTL0_BLKSIZE | DMA_CH0CTL0_CNT |DMA_CH0CTL0_HSIZE,
                   pstcDmaInit->u32BlockSize | pstcDmaInit->u32DataWidth |
                   (pstcDmaInit->u32TransCount << DMA_CH0CTL0_CNT_POS));
        CHxCTL1 = &DMA_CH_REG(DMAx->CH0CTL1, u32Ch);
        /* Set source & destination address increment mode */
        MODIFY_REG32(*CHxCTL1,
                   DMA_CH0CTL1_SINC | DMA_CH0CTL1_DINC,
                   pstcDmaInit->u32SrcAddrMode | pstcDmaInit->u32DestAddrMode);
    }

    return enRet;
}

/**
 * @brief  Initialize DMA repeat mode config structure.
 *          Fill each pstcDmaRptInit with default value
 * @param  [in] pstcDmaRptInit Pointer to a stc_dma_repeat_init_t structure that
 *                            contains configuration information.
 * @retval Ok: DMA repeat mode config structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_RepeatStructInit(stc_dma_repeat_init_t *pstcDmaRptInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaRptInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcDmaRptInit->u32RepeatEn   = DMA_RPT_DISABLE;
        pstcDmaRptInit->u32RepeatSize = 0x00UL;
        pstcDmaRptInit->u32RepeatSel  = 0x00UL;
    }
    return enRet;
}

/**
 * @brief  Initialize the DMA repeat transfer.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] pstcDmaRptInit DMA repeat mode config structure.
 *   @arg  u32RepeatEn     DMA repeat enable or disable.
 *   @arg  u32RepeatSize   DMA repeat size.
 *   @arg  u32RepeatSel    DMA source repeat or destination repeat.
 * @retval Ok: DMA repeat function initialize successful
 *         ErrorInvalidParameter: NULL pointer
 * @note Call this function after DMA_Init();
 */
en_result_t DMA_RepeatInit(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, const stc_dma_repeat_init_t *pstcDmaRptInit)
{
    en_result_t enRet = Ok;
    __IO uint32_t *CHxCTL1;

    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));

    if (NULL == pstcDmaRptInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_VALID_DMA_RPT_MD(pstcDmaRptInit->u32RepeatEn));
        DDL_ASSERT(IS_VALID_DMA_BLOCK_SIZE(pstcDmaRptInit->u32RepeatSize));
        DDL_ASSERT(IS_VALID_DMA_RPT_SEL(pstcDmaRptInit->u32RepeatSel));

        CHxCTL1 = &DMA_CH_REG(DMAx->CH0CTL1, u32Ch);
        /* Config repeat transfer include mode, selection & repeat size */
        MODIFY_REG32(*CHxCTL1,                                                 \
            DMA_CH0CTL1_RPTNSEN | DMA_CH0CTL1_RPTNSSEL | DMA_CH0CTL1_RPTNSCNT, \
            pstcDmaRptInit->u32RepeatEn | pstcDmaRptInit->u32RepeatSel |
            (pstcDmaRptInit->u32RepeatSize << DMA_CH0CTL1_RPTNSCNT_POS));
    }
    return enRet;
}


/**
 * @brief  Initialize DMA non-sequence mode config structure.
 *          Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaNonSeqInit Pointer to a stc_dma_nonseq_init_t structure that
 *                            contains configuration information.
 * @retval Ok: DMA non-sequence mode structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_NonSeqStructInit(stc_dma_nonseq_init_t *pstcDmaNonSeqInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaNonSeqInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcDmaNonSeqInit->u32NonSeqEn     = DMA_NONSEQ_DISABLE;
        pstcDmaNonSeqInit->u32NonSeqCount  = 0x00UL;
        pstcDmaNonSeqInit->u32NonSeqSel    = 0x00UL;
        pstcDmaNonSeqInit->u32NonSeqOffset = 0x00UL;
    }
    return enRet;
}

/**
 * @brief  DMA non-sequence mode initialize.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] pstcDmaNonSeqInit DMA non-sequence mode config structure.
 *   @arg  u32NonSeqEn      DMA non-sequence transfer enable or disable.
 *   @arg  u32NonSeqCount   DMA non-sequence count.
 *   @arg  u32NonSeqOffset  DMA non-sequence offset.
 *   @arg       DMA source or destination non-sequence transfer.
 * @retval Ok: DMA non-sequence function initialize successful
 *         ErrorInvalidParameter: NULL pointer
 * @note Call this function after DMA_Init();
 */
en_result_t DMA_NonSeqInit(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, const stc_dma_nonseq_init_t *pstcDmaNonSeqInit)
{
    en_result_t enRet = Ok;
    __IO uint32_t *CHxCTL1;

    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));

    if (NULL == pstcDmaNonSeqInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_VALID_DMA_NONSEQ_MD(pstcDmaNonSeqInit->u32NonSeqEn));
        DDL_ASSERT(IS_VALID_DMA_NONSEQ_CNT(pstcDmaNonSeqInit->u32NonSeqCount));
        DDL_ASSERT(IS_VALID_DMA_NONSEQ_OFFSET(pstcDmaNonSeqInit->u32NonSeqOffset));
        DDL_ASSERT(IS_VALID_DMA_NONSEQ_SEL(pstcDmaNonSeqInit->u32NonSeqSel));

        CHxCTL1 = &DMA_CH_REG(DMAx->CH0CTL1, u32Ch);
        /* Config non_sequence transfer include mode, selection, count & offset */
        MODIFY_REG32(*CHxCTL1,                                                 \
            DMA_CH0CTL1_RPTNSEN | DMA_CH0CTL1_RPTNSSEL |                       \
            DMA_CH0CTL1_RPTNSCNT | DMA_CH0CTL1_OFFSET,                         \
            pstcDmaNonSeqInit->u32NonSeqEn | pstcDmaNonSeqInit->u32NonSeqSel | \
            (pstcDmaNonSeqInit->u32NonSeqCount << DMA_CH0CTL1_RPTNSCNT_POS)  | \
            (pstcDmaNonSeqInit->u32NonSeqOffset << DMA_CH0CTL1_OFFSET_POS));
    }
    return enRet;
}

/**
 * @brief  Initialize DMA Linked List Pointer (hereafter, LLP) mode config structure.
 *          Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaLlpInit Pointer to a stc_dma_llp_init_t structure that
 *                            contains configuration information.
 * @retval Ok: DMA LLP mode config structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_LlpStructInit(stc_dma_llp_init_t *pstcDmaLlpInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaLlpInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcDmaLlpInit->u32Llp         = DMA_LLP_DISABLE;
        pstcDmaLlpInit->u32LlpMode     = DMA_LLP_WAIT;
        pstcDmaLlpInit->u32LlpAddr     = 0x00UL;
        pstcDmaLlpInit->u32LlpAddrMode = DMA_LLP_ADDR_RAM;
    }
    return enRet;
}

/**
 * @brief  DMA LLP mode initialize.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] pstcDmaLlpInit DMA LLP config structure.
 *   @arg  u32Llp           DMA LLP enable or disable.
 *   @arg  u32LlpMode       DMA LLP auto-run or wait request.
 *   @arg  u32LlpAddr       DMA LLP next list pointer address.
 *   @arg  u32LlpAddrMode   DMA LLP descriptor base address mode.
 * @retval Ok: DMA LLP function initialize successful
 *         ErrorInvalidParameter: NULL pointer
 * @note Call this function after DMA_Init();
 */
en_result_t DMA_LlpInit(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, const stc_dma_llp_init_t *pstcDmaLlpInit)
{
    en_result_t enRet = Ok;
    __IO uint32_t *CHxCTL0;
    __IO uint32_t *CHxCTL1;

    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));

    if (NULL == pstcDmaLlpInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_VALID_DMA_LLP(pstcDmaLlpInit->u32Llp));
        DDL_ASSERT(IS_VALID_DMA_LLP_MD(pstcDmaLlpInit->u32LlpMode));
        DDL_ASSERT(IS_VALID_DMA_LLP_ADDR_MD(pstcDmaLlpInit->u32LlpAddrMode));

        CHxCTL0 = &DMA_CH_REG(DMAx->CH0CTL0, u32Ch);
        CHxCTL1 = &DMA_CH_REG(DMAx->CH0CTL1, u32Ch);
        MODIFY_REG32(*CHxCTL0,                                                 \
            DMA_CH0CTL0_LLP | DMA_CH0CTL0_LLPEN | DMA_CH0CTL0_LLPRUN,          \
            pstcDmaLlpInit->u32Llp | pstcDmaLlpInit->u32LlpMode |              \
            ((pstcDmaLlpInit->u32LlpAddr << (DMA_CH0CTL0_LLP_POS - 4U)) & DMA_CH0CTL0_LLP));

        if(DMA_LLP_ADDR_ROM == pstcDmaLlpInit->u32LlpAddrMode)
        {
            MODIFY_REG32(*CHxCTL1, DMA_CH0CTL1_LLPSEL, pstcDmaLlpInit->u32LlpAddrMode);
            WRITE_REG32(DMAx->ROM_LLP, pstcDmaLlpInit->u32LlpAddr & DMA_ROM_LLP_LLP);
        }
        else
        {
            MODIFY_REG32(*CHxCTL1, DMA_CH0CTL1_LLPSEL, pstcDmaLlpInit->u32LlpAddrMode);
            WRITE_REG32(DMAx->RAM_LLP, pstcDmaLlpInit->u32LlpAddr & DMA_RAM_LLP_LLP);
        }
    }
    return enRet;
}

/**
 * @brief  DMA LLP enable or disable.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] enNewState New state of LLP function.
 * @retval None
 */
void DMA_LlpCmd(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(DMA_CH_REG(DMAx->CH0CTL0, u32Ch), DMA_CH0CTL0_LLPEN);
    }
    else
    {
        CLEAR_REG32_BIT(DMA_CH_REG(DMAx->CH0CTL0, u32Ch), DMA_CH0CTL0_LLPEN);
    }
}

/**
 * @brief  Set DMA llp descriptor base address mode.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 * @param  [in] u32AddrMode DMA LLP descriptor base address mode.
 *   @arg  DMA_LLP_ADDR_ROM.
 *   @arg  DMA_LLP_ADDR_RAM.
 * @retval None
 */
void DMA_SetLlpAddrMode(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, uint32_t u32AddrMode)
{
    __IO uint32_t *CHxCTL1;

    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_CH(u32Ch));
    DDL_ASSERT(IS_VALID_DMA_LLP_ADDR_MD(u32AddrMode));

    CHxCTL1 = &DMA_CH_REG(DMAx->CH0CTL1, u32Ch);
    /* Set DMA llp descriptor base address mode. */
    MODIFY_REG32(*CHxCTL1, DMA_CH0CTL1_LLPSEL, u32AddrMode);
}

/**
 * @brief  Set DMA llp descriptor base address.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Addr  DMA LLP descriptor base address.
 * @retval None
 */
void DMA_SetLlpRamAddr(CM_DMA_TypeDef *DMAx, uint32_t u32Addr)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_LLP_ADDR(u32Addr));

    /* Set DMA llp descriptor base address. */
    WRITE_REG32(DMAx->RAM_LLP, u32Addr & DMA_RAM_LLP_LLP);
}

/**
 * @brief  Set DMA llp descriptor base address.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMA Unit.
 * @param  [in] u32Addr  DMA LLP descriptor base address.
 * @retval None
 */
void DMA_SetLlpRomAddr(CM_DMA_TypeDef *DMAx, uint32_t u32Addr)
{
    DDL_ASSERT(IS_VALID_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_VALID_DMA_LLP_ADDR(u32Addr));

    /* Set DMA llp descriptor base address. */
    WRITE_REG32(DMAx->ROM_LLP, u32Addr & DMA_ROM_LLP_LLP);
}

/**
 * @}
 */

#endif  /* DDL_DMA_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
