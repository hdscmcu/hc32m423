/**
 *******************************************************************************
 * @file  hc32m423_dma.h
 * @brief This file contains all the functions prototypes of the DMA driver
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
#ifndef __HC32M423_DMA_H__
#define __HC32M423_DMA_H__

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
 * @addtogroup DDL_DMA
 * @{
 */

#if (DDL_DMA_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup DMA_Global_Types DMA Global Types
 * @{
 */

/**
 * @brief  DMA channel configuration
 */
typedef struct
{
    uint32_t    u32DataWidth;     /*!< Specifies the DMA transfer data width.
                                      This parameter can be a value of @ref DMA_Data_Width                  */

    uint32_t    u32BlockSize;     /*!< Specifies the DMA block size.                                        */

    uint32_t    u32TransCount;    /*!< Specifies the DMA transfer count.                                    */

    uint32_t    u32SrcAddr;       /*!< Specifies the DMA source address.                                    */

    uint32_t    u32DestAddr;      /*!< Specifies the DMA destination address.                               */

    uint32_t    u32SrcAddrMode;   /*!< Specifies the source address increment mode.
                                      This parameter can be a value of @ref DMA_SourceAddr_Incremented_Mode */

    uint32_t    u32DestAddrMode;  /*!< Specifies the destination address increment mode.
                                      This parameter can be a value of @ref DMA_DestAddr_Incremented_Mode   */

} stc_dma_init_t;

/**
 * @brief  DMA repeat mode configuration
 */
typedef struct
{
    uint32_t u32RepeatEn;       /*!< Specifies the DMA repeat function.
                                    This parameter can be a value of @ref DMA_Repeat_Config */

    uint32_t u32RepeatSize;     /*!< Specifies the DMA repeat size.                         */

    uint32_t u32RepeatSel;      /*!< Specifies the DMA source repeat or destination repeat.
                                    This parameter can be a value of @ref DMA_Repeat_Config */

} stc_dma_repeat_init_t;

/**
 * @brief  DMA non_sequence mode configuration
 */
typedef struct
{
    uint32_t u32NonSeqEn;       /*!< Specifies the DMA non_sequence function.
                                    This parameter can be a value of @ref DMA_NonSeq_Config */

    uint32_t u32NonSeqCount;    /*!< Specifies the DMA non_sequence count.                  */

    uint32_t u32NonSeqOffset;   /*!< Specifies the DMA non_sequence offset.                 */

    uint32_t u32NonSeqSel;      /*!< Specifies the DMA source or destination non_sequence.
                                    This parameter can be a value of @ref DMA_NonSeq_Config */

} stc_dma_nonseq_init_t;

/**
 * @brief  DMA Link List Pointer (LLP) mode configuration
 */
typedef struct
{
    uint32_t u32Llp;            /*!< Specifies the DMA LLP function.
                                    This parameter can be a value of @ref DMA_Llp_En.           */

    uint32_t u32LlpMode;        /*!< Specifies the DMA LLP auto or wait REQ.
                                    This parameter can be a value of @ref DMA_Llp_Mode.         */

    uint32_t u32LlpAddr;        /*!< Specifies the DMA list pointer address for LLP function.   */

    uint32_t u32LlpAddrMode;    /*!< Specifies the DMA list pointer descriptor base address.
                                    This parameter can be a value of @ref DMA_Llp_Addr_Mode.    */

} stc_dma_llp_init_t;

/**
 * @brief  Dma LLP(linked list pointer) descriptor structure definition
 */
typedef struct
{
    uint32_t SARx;                              /*!< DMA source address register.       */
    uint32_t DARx;                              /*!< DMA destination address register.  */
    uint32_t CHxCTL0;                           /*!< DMA data control register.         */
    uint32_t CHxCTL1;                           /*!< DMA channel control register.      */
} stc_dma_llp_descriptor_t;

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

/**
 * @defgroup DMA_Channel_selection DMA Channel Position selection
 * @{
 */
#define DMA_CH0                     (0x00UL)      /*!< DMA Channel 0 */
#define DMA_CH1                     (0x01UL)      /*!< DMA Channel 1 */
#define DMA_CH2                     (0x02UL)      /*!< DMA Channel 2 */
#define DMA_CH3                     (0x03UL)      /*!< DMA Channel 3 */
/**
 * @}
 */

/**
 * @defgroup DMA_Mx_Channel_selection DMA Multiplex Channel selection
 * @{
 */
#define DMA_MX_CH0                  (0x01UL)      /*!< DMA Channel 0 position     */
#define DMA_MX_CH1                  (0x02UL)      /*!< DMA Channel 1 position     */
#define DMA_MX_CH2                  (0x04UL)      /*!< DMA Channel 2 position     */
#define DMA_MX_CH3                  (0x08UL)      /*!< DMA Channel 3 position     */
#define DMA_MX_CH_ALL               (0x0FUL)      /*!< DMA Channel mask position  */
/**
 * @}
 */

/**
 * @defgroup DMA_ReqErrIrq_Sel DMA request error interrupt selection
 * @{
 */
#define DMA_REQ_ERR_CH0             (DMA_INTSTAT0_REQERR_0) /*!< DMA request error interrupt CH.0 */
#define DMA_REQ_ERR_CH1             (DMA_INTSTAT0_REQERR_1) /*!< DMA request error interrupt CH.1 */
#define DMA_REQ_ERR_CH2             (DMA_INTSTAT0_REQERR_2) /*!< DMA request error interrupt CH.2 */
#define DMA_REQ_ERR_CH3             (DMA_INTSTAT0_REQERR_3) /*!< DMA request error interrupt CH.3 */
/**
 * @}
 */

/**
 * @defgroup DMA_TransErrIrq_Sel DMA transfer error interrupt selection
 * @{
 */
#define DMA_TRANS_ERR_CH0           (DMA_INTSTAT0_TRNERR_0) /*!< DMA transfer error interrupt CH.0 */
#define DMA_TRANS_ERR_CH1           (DMA_INTSTAT0_TRNERR_1) /*!< DMA transfer error interrupt CH.1 */
#define DMA_TRANS_ERR_CH2           (DMA_INTSTAT0_TRNERR_2) /*!< DMA transfer error interrupt CH.2 */
#define DMA_TRANS_ERR_CH3           (DMA_INTSTAT0_TRNERR_3) /*!< DMA transfer error interrupt CH.3 */
/**
 * @}
 */

/**
 * @defgroup DMA_BtcIrq_Sel DMA block transfer completed interrupt selection
 * @{
 */
#define DMA_INT_BTC0                (DMA_INTSTAT1_BTC_0)    /*!< DMA CH.0 block transfer completed interrupt */
#define DMA_INT_BTC1                (DMA_INTSTAT1_BTC_1)    /*!< DMA CH.1 block transfer completed interrupt */
#define DMA_INT_BTC2                (DMA_INTSTAT1_BTC_2)    /*!< DMA CH.2 block transfer completed interrupt */
#define DMA_INT_BTC3                (DMA_INTSTAT1_BTC_3)    /*!< DMA CH.3 block transfer completed interrupt */
/**
 * @}
 */

/**
 * @defgroup DMA_TcIrq_Sel DMA transfer completed interrupt selection
 * @{
 */
#define DMA_INT_TC0                 (DMA_INTSTAT1_TC_0)     /*!< DMA CH.0 transfer completed interrupt */
#define DMA_INT_TC1                 (DMA_INTSTAT1_TC_1)     /*!< DMA CH.1 transfer completed interrupt */
#define DMA_INT_TC2                 (DMA_INTSTAT1_TC_2)     /*!< DMA CH.2 transfer completed interrupt */
#define DMA_INT_TC3                 (DMA_INTSTAT1_TC_3)     /*!< DMA CH.3 transfer completed interrupt */
/**
 * @}
 */

/**
 * @defgroup DMA_IntMsk_Sel DMA interrupt mask selection
 * @{
 */
#define DMA_ERR_INT_MASK            (0x000F000FUL)    /*!< DMA error interrupt mask     */
#define DMA_TRANS_INT_MASK          (0x000F000FUL)    /*!< DMA transfer interrupt mask  */
/**
 * @}
 */

/**
 * @defgroup DMA_Trans_Status_Sel DMA transfer status
 * @{
 */
#define DMA_TRANS_CH0               (DMA_CHSTAT_CHACT_0)    /*!< DMA transfer status of CH.0    */
#define DMA_TRANS_CH1               (DMA_CHSTAT_CHACT_1)    /*!< DMA transfer status of CH.1    */
#define DMA_TRANS_CH2               (DMA_CHSTAT_CHACT_2)    /*!< DMA transfer status of CH.2    */
#define DMA_TRANS_CH3               (DMA_CHSTAT_CHACT_3)    /*!< DMA transfer status of CH.3    */
#define DMA_TRANS_DMA               (DMA_CHSTAT_DMAACT)     /*!< DMA transfer status of the DMA */
#define DMA_TRANS_STAT_MASK         (0x000F0001UL)          /*!< DMA request mask               */
/**
 * @}
 */

/**
 * @defgroup DMA_Data_Width DMA transfer data width
 * @{
 */
#define DMA_DATA_WIDTH_8BIT          (0x00000000UL)            /*!< DMA transfer data width 8bit       */
#define DMA_DATA_WIDTH_16BIT         (DMA_CH0CTL0_HSIZE_0)     /*!< DMA transfer data width 16bit      */
#define DMA_DATA_WIDTH_32BIT         (DMA_CH0CTL0_HSIZE_1)     /*!< DMA transfer data width 32bit      */
/**
 * @}
 */

/**
 * @defgroup DMA_Llp_En DMA LLP(linked list pointer) enable or disable
 * @{
 */
#define DMA_LLP_ENABLE              (DMA_CH0CTL0_LLPEN)     /*!< DMA LLP(linked list pointer) enable     */
#define DMA_LLP_DISABLE             (0x00000000UL)          /*!< DMA LLP(linked list pointer) disable    */
/**
 * @}
 */

/**
 * @defgroup DMA_Llp_Mode DMA LLP mode
 * @brief DMA linked list pointer mode while transferring complete
 * @{
 */
#define DMA_LLP_RUN                 (DMA_CH0CTL0_LLPRUN)    /*!< DMA Llp run right now while transfering complete     */
#define DMA_LLP_WAIT                (0x00000000UL)          /*!< DMA Llp wait next request while transfering complete */
/**
 * @}
 */

/**
 * @defgroup DMA_Llp_Addr_Mode DMA LLP address mode
 * @brief DMA linked list pointer descriptor base address mode.
 * @{
 */
#define DMA_LLP_ADDR_ROM            (DMA_CH0CTL1_LLPSEL)    /*!< DMA Llp descriptor base address at rom */
#define DMA_LLP_ADDR_RAM            (0x00000000UL)          /*!< DMA Llp descriptor base address at ram */
/**
 * @}
 */

/**
 * @defgroup DMA_SourceAddr_Incremented_Mode DMA source address increment mode
 * @{
 */
#define DMA_SRC_ADDR_MD_FIX         (0x00000000UL)          /*!< DMA source address fix             */
#define DMA_SRC_ADDR_MD_INC         (DMA_CH0CTL1_SINC_0)    /*!< DMA source address increment       */
#define DMA_SRC_ADDR_MD_DEC         (DMA_CH0CTL1_SINC_1)    /*!< DMA source address decrement       */
/**
 * @}
 */

/**
 * @defgroup DMA_DestAddr_Incremented_Mode DMA destination address increment mode
 * @{
 */
#define DMA_DEST_ADDR_MD_FIX        (0x00000000UL)        /*!< DMA destination address fix        */
#define DMA_DEST_ADDR_MD_INC        (DMA_CH0CTL1_DINC_0)  /*!< DMA destination address increment  */
#define DMA_DEST_ADDR_MD_DEC        (DMA_CH0CTL1_DINC_1)  /*!< DMA destination address decrement  */
/**
 * @}
 */

/**
 * @defgroup DMA_Repeat_Config DMA repeat mode function config
 * @{
 */
#define DMA_RPT_ENABLE              (DMA_CH0CTL1_RPTNSEN)       /*!< DMA repeat transfer enable     */
#define DMA_RPT_DISABLE             (0x00000000UL)              /*!< DMA repeat transfer disable    */
#define DMA_SRC_RPT                 (0x00000000UL)              /*!< DMA source repeat mode         */
#define DMA_DEST_RPT                (DMA_CH0CTL1_RPTNSSEL_0)    /*!< DMA destination repeat mode    */
/**
 * @}
 */

/**
 * @defgroup DMA_NonSeq_Config DMA non-sequence mode function config
 * @{
 */
#define DMA_NONSEQ_ENABLE           (DMA_CH0CTL1_RPTNSEN)       /*!< DMA non-sequence transfer enable   */
#define DMA_NONSEQ_DISABLE          (0x00000000UL)              /*!< DMA non-sequence transfer disable  */
#define DMA_SRC_NONSEQ              (DMA_CH0CTL1_RPTNSSEL_1)    /*!< DMA source non-sequence mode       */
#define DMA_DEST_NONSEQ             (DMA_CH0CTL1_RPTNSSEL)      /*!< DMA destination non-sequence mode  */
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
 * @addtogroup DMA_Global_Functions
 * @{
 */
void DMA_Cmd(CM_DMA_TypeDef *DMAx, en_functional_state_t enNewState);

void DMA_ErrIntCmd(CM_DMA_TypeDef *DMAx, uint32_t u32ErrInt, en_functional_state_t enNewState);
en_flag_status_t DMA_GetErrIntStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32ErrInt);
void DMA_ClearErrIntStatus(CM_DMA_TypeDef *DMAx, uint32_t u32ErrInt);

void DMA_TransIntCmd(CM_DMA_TypeDef *DMAx, uint32_t u32TransInt, en_functional_state_t enNewState);
en_flag_status_t DMA_GetTransIntStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32TransInt);
void DMA_ClearTransIntStatus(CM_DMA_TypeDef *DMAx, uint32_t u32TransInt);

void DMA_MxChCmd(CM_DMA_TypeDef *DMAx, uint32_t u32MxCh, en_functional_state_t enNewState);
void DMA_ChCmd(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, en_functional_state_t enNewState);

en_flag_status_t DMA_GetTransStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32Status);

void DMA_SetTriggerSrc(const CM_DMA_TypeDef *DMAx, uint32_t u32Ch, en_event_src_t enEventSrc);

void DMA_SetSrcAddr(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, uint32_t u32Addr);
void DMA_SetDestAddr(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, uint32_t u32Addr);
void DMA_SetBlockSize(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, uint8_t u8Size);
void DMA_SetTransCount(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, uint16_t u16Count);

en_result_t DMA_StructInit(stc_dma_init_t *pstcDmaInit);
en_result_t DMA_RepeatStructInit(stc_dma_repeat_init_t *pstcDmaRptInit);
en_result_t DMA_NonSeqStructInit(stc_dma_nonseq_init_t *pstcDmaNonSeqInit);
en_result_t DMA_LlpStructInit(stc_dma_llp_init_t *pstcDmaLlpInit);

en_result_t DMA_Init(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, const stc_dma_init_t *pstcDmaInit);
en_result_t DMA_RepeatInit(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, const stc_dma_repeat_init_t *pstcDmaRptInit);
en_result_t DMA_NonSeqInit(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, const stc_dma_nonseq_init_t *pstcDmaNonSeqInit);
en_result_t DMA_LlpInit(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, const stc_dma_llp_init_t *pstcDmaLlpInit);

void DMA_SetLlpAddrMode(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, uint32_t u32AddrMode);
void DMA_SetLlpRamAddr(CM_DMA_TypeDef *DMAx, uint32_t u32Addr);
void DMA_SetLlpRomAddr(CM_DMA_TypeDef *DMAx, uint32_t u32Addr);
void DMA_LlpCmd(CM_DMA_TypeDef *DMAx, uint32_t u32Ch, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* DDL_DMA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_DMA_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
