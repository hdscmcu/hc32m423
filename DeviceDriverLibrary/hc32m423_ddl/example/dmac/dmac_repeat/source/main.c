 /*******************************************************************************
 * @file  dmac/dmac_repeat/source/main.c
 * @brief This example demonstrates TIMERA base count function.
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
#include "hc32_ddl.h"
#include "string.h"

/**
 * @addtogroup HC32M423_DDL_Examples
 * @{
 */

/**
 * @addtogroup DMAC_Repeat
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* DMAC */
#define DMA_UNIT        (CM_DMA)
#define DMA_CH          (DMA_CH2)
#define DMA_TRNCNT      (5U)
#define DMA_BLKSIZE     (4U)
#define DMA_RPTSIZE     (11U)
#define DMA_INT_SRC     (INT_DMA_TC2)
#define DMA_IRQn        (INT000_IRQn)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
en_flag_status_t u8DmaTcEnd = Reset;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static const uint32_t u32SrcBuf[22] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                       11, 12, 13, 14, 15, 16, 17, 18,
                                       19, 20, 21, 22};
static uint32_t u32DestBuf[22] = {0};
static uint32_t u32ExpectDestBufData[22] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 10,
                                           11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
 /**
 * @brief  MCU Peripheral registers write unprotected.
 * @param  None
 * @retval None
 * @note Comment/uncomment each API depending on APP requires.
 */
static void Peripheral_WE(void)
{
    /* Unlock GPIO register: PSPCR, PCCR, PINAER, PCRxy, PFSRxy */
    GPIO_Unlock();
    /* Unlock CLK registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Unlock(PWC_UNLOCK_CODE_0);
}

/**
 * @brief  MCU Peripheral registers write protected.
 * @param  None
 * @retval None
 * @note Comment/uncomment each API depending on APP requires.
 */
static void Peripheral_WP(void)
{
    /* Lock GPIO register: PSPCR, PCCR, PINAER, PCRxy, PFSRxy */
    GPIO_Lock();
    /* Lock CLK registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Lock(PWC_UNLOCK_CODE_0);
}


/**
 * @brief  DMA basic function init
 * @param  None
 * @retval en_result_t
 */
en_result_t DmaInit(void)
{
    stc_dma_init_t stcDmaInit;
    stc_dma_repeat_init_t stcDmaRepeatInit;

    DMA_SetTriggerSrc(DMA_UNIT, DMA_CH, EVT_AOS_STRG);

    DMA_StructInit(&stcDmaInit);

    stcDmaInit.u32DataWidth     = DMA_DATA_WIDTH_32BIT;
    stcDmaInit.u32BlockSize     = DMA_BLKSIZE;
    stcDmaInit.u32TransCount    = DMA_TRNCNT;
    stcDmaInit.u32SrcAddr       = (uint32_t)(&u32SrcBuf[0]);
    stcDmaInit.u32DestAddr      = (uint32_t)(&u32DestBuf[0]);
    stcDmaInit.u32SrcAddrMode   = DMA_SRC_ADDR_MD_INC;
    stcDmaInit.u32DestAddrMode  = DMA_DEST_ADDR_MD_INC;

    if (Ok != DMA_Init(DMA_UNIT, DMA_CH, &stcDmaInit))
    {
        for(;;)
        {
            ;
        }
    }

    DMA_RepeatStructInit(&stcDmaRepeatInit);

    stcDmaRepeatInit.u32RepeatEn   = DMA_RPT_ENABLE;
    stcDmaRepeatInit.u32RepeatSize = DMA_RPTSIZE;
    stcDmaRepeatInit.u32RepeatSel  = DMA_DEST_RPT;

    return (DMA_RepeatInit(DMA_UNIT, DMA_CH, &stcDmaRepeatInit));
}

/**
 * @brief  DMA ch.2 transfer complete IRQ callback
 * @param  None
 * @retval None
 */
void DMA_CH2_TransEnd_IrqCallback(void)
{
    u8DmaTcEnd = Set;
    DMA_ClearTransIntStatus(DMA_UNIT, DMA_INT_TC2);
}

/**
 * @brief  DMA basic function interrupt init
 * @param  None
 * @retval None
 */
void DmaIntInit(void)
{
    stc_irq_signin_config_t stcIrqSignConfig;

    stcIrqSignConfig.enIntSrc   = DMA_INT_SRC;
    stcIrqSignConfig.enIRQn     = DMA_IRQn;
    stcIrqSignConfig.pfnCallback= &DMA_CH2_TransEnd_IrqCallback;

    INTC_IrqSignIn(&stcIrqSignConfig);
    DMA_ClearTransIntStatus(DMA_UNIT, DMA_INT_TC2);

    /* NVIC setting */
    NVIC_ClearPendingIRQ(DMA_IRQn);
    NVIC_SetPriority(DMA_IRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(DMA_IRQn);
}

/**
 * @brief  Main function of DMAC project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Led Init */
    BSP_LED_Init();

    /* DMA/AOS FCG enable */
    CLK_FcgPeriphClockCmd(CLK_FCG_DMA | CLK_FCG_AOS, Enable);

    /* MCU Peripheral registers write protected. */
    Peripheral_WP();
    /* DMA config */
    DmaInit();
    /* DMA interrupt config */
    DmaIntInit();

    /* Enable DMA. */
    DMA_Cmd(DMA_UNIT, Enable);

    /* Enable DMA channel */
    DMA_ChCmd(DMA_UNIT, DMA_CH, Enable);

    while(Reset == u8DmaTcEnd)
    {
         AOS_SW_Trigger();
    }

    if(0U == (uint8_t)memcmp(u32DestBuf, u32ExpectDestBufData, sizeof(u32DestBuf)))
    {
        BSP_LED_On(LED_GREEN);    /* Meet the expected */
    }
    else
    {
        BSP_LED_On(LED_RED);    /* Don't meet the expected */
    }

    for(;;)
    {
        ;
    }
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
