 /*******************************************************************************
 * @file  dmac/dmac_link_list_pointer/source/main.c
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

/**
 * @addtogroup HC32M423_DDL_Examples
 * @{
 */

/**
 * @addtogroup DMAC_LLP
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
#define DMA_CH          (DMA_CH3)
#define DMA_TRNCNT      (1UL)
#define DMA_BLKSIZE     ((uint32_t)ARRAY_SZ(u16SourceBuf))
#define DMA_INT_SRC     (INT_DMA_TC3)
#define DMA_IRQn        (INT000_IRQn)

#define DMA_LLP_MD      (DMA_LLP_RUN)
#define DMA_LLP_POS     (DMA_CH0CTL0_LLP_POS -4U)
#define DMA_LLP_ADDR_MD (DMA_LLP_ADDR_RAM)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
en_flag_status_t u8DmaTcEnd = Reset;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8SourceBuf[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
static uint8_t u8DestBuf[10] = {0};

static uint16_t u16SourceBuf[10] = {21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
static uint16_t u16DestBuf[10] = {0};

static uint32_t u32SourceBuf[10] = {31, 32, 33, 34, 35, 36, 37, 38, 39, 40};
static uint32_t u32DestBuf[10] = {0};

#if defined (__ICCARM__)
_Pragma("data_alignment=16")
static stc_dma_llp_descriptor_t stcLlpDesc[2] = {0};
#else
static stc_dma_llp_descriptor_t stcLlpDesc[2] __ALIGNED(16) = {0};
#endif

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
    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Unlock all EFM registers */
    EFM_Unlock();
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
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  DMA basic function init
 * @param  None
 * @retval None
 */
static void DmaInit(void)
{
    stc_dma_init_t stcDmaInit;
    stc_dma_llp_init_t stcDmaLlpInit;

    DMA_SetTriggerSrc(DMA_UNIT, DMA_CH, EVT_AOS_STRG);

    (void)DMA_StructInit(&stcDmaInit);

    stcDmaInit.u32DataWidth     = DMA_DATA_WIDTH_8BIT;
    stcDmaInit.u32BlockSize     = DMA_BLKSIZE;
    stcDmaInit.u32TransCount    = DMA_TRNCNT;
    stcDmaInit.u32SrcAddr       = (uint32_t)(&u8SourceBuf[0]);
    stcDmaInit.u32DestAddr      = (uint32_t)(&u8DestBuf[0]);
    stcDmaInit.u32SrcAddrMode   = DMA_SRC_ADDR_MD_INC;
    stcDmaInit.u32DestAddrMode  = DMA_DEST_ADDR_MD_INC;

    (void)DMA_Init(DMA_UNIT, DMA_CH, &stcDmaInit);

    /* descriptor 0 */
    stcLlpDesc[0].SARx = (uint32_t)(&u16SourceBuf[0]);
    stcLlpDesc[0].DARx = (uint32_t)(&u16DestBuf[0]);
    stcLlpDesc[0].CHxCTL0 = DMA_BLKSIZE | (DMA_TRNCNT << DMA_CH0CTL0_CNT_POS) |  \
                            (((uint32_t)(&stcLlpDesc[1]) << DMA_LLP_POS) & DMA_CH0CTL0_LLP) |  \
                            DMA_LLP_ENABLE | DMA_LLP_MD | DMA_DATA_WIDTH_16BIT;
    stcLlpDesc[0].CHxCTL1 = DMA_DEST_ADDR_MD_INC | DMA_SRC_ADDR_MD_INC | DMA_LLP_ADDR_MD;

    /* descriptor 1 */
    stcLlpDesc[1].SARx = (uint32_t)(&u32SourceBuf[0]);
    stcLlpDesc[1].DARx = (uint32_t)(&u32DestBuf[0]);
    stcLlpDesc[1].CHxCTL0 = DMA_BLKSIZE | (DMA_TRNCNT << DMA_CH0CTL0_CNT_POS) |  \
                            DMA_LLP_DISABLE | DMA_DATA_WIDTH_32BIT;
    stcLlpDesc[1].CHxCTL1 = DMA_DEST_ADDR_MD_INC | DMA_SRC_ADDR_MD_INC | DMA_LLP_ADDR_MD;

    /* Init LLP struct */
    (void)DMA_LlpStructInit(&stcDmaLlpInit);

    stcDmaLlpInit.u32Llp         = DMA_LLP_ENABLE;
    stcDmaLlpInit.u32LlpMode     = DMA_LLP_MD;
    stcDmaLlpInit.u32LlpAddr     = (uint32_t)&stcLlpDesc[0];

    (void)DMA_LlpInit(DMA_UNIT, DMA_CH, &stcDmaLlpInit);
}

/**
 * @brief  DMA ch.3 transfer complete IRQ callback
 * @param  None
 * @retval None
 */
static void DMA_CH3_TransEnd_IrqCallback(void)
{
    u8DmaTcEnd = Set;
    DMA_ClearTransIntStatus(DMA_UNIT, DMA_INT_TC3);
}

/**
 * @brief  DMA basic function interrupt init
 * @param  None
 * @retval None
 */
static void DmaIntInit(void)
{
    stc_irq_signin_config_t stcIrqSignConfig;

    stcIrqSignConfig.enIntSrc   = DMA_INT_SRC;
    stcIrqSignConfig.enIRQn     = DMA_IRQn;
    stcIrqSignConfig.pfnCallback= &DMA_CH3_TransEnd_IrqCallback;

    (void)INTC_IrqSignIn(&stcIrqSignConfig);

    DMA_ClearTransIntStatus(DMA_UNIT, DMA_INT_TC3);

    /* NVIC setting */
    NVIC_ClearPendingIRQ(DMA_IRQn);
    NVIC_SetPriority(DMA_IRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(DMA_IRQn);
}

/**
 * @brief  SysTick interrupt callback function.
 * @param  None
 * @retval None
 */
void SysTick_IrqHandler(void)
{
    SysTick_IncTick();
}

/**
 * @brief  Main function of DMAC project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint8_t u8CmpRet = 0U;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Clock Init */
    BSP_CLK_Init();
    (void)SysTick_Init(1000U);

    /* Led Init */
    BSP_LED_Init();

    /* DMA/AOS FCG enable */
    CLK_FcgPeriphClockCmd(CLK_FCG_DMA | CLK_FCG_AOS, Enable);

    /* MCU Peripheral registers write protected. */
    Peripheral_WP();
    /* Config DMA */
    DmaInit();
    /* DMA interrupt config */
    DmaIntInit();

    /* Enable DMA. */
    DMA_Cmd(DMA_UNIT, Enable);

    /* Enable DMA channel */
    DMA_ChCmd(DMA_UNIT, DMA_CH, Enable);

    /* 1st trigger for DMA */
    AOS_SW_Trigger();

    SysTick_Delay(1U);

    while (Reset == u8DmaTcEnd)
    {
        AOS_SW_Trigger();
    }

    /* Verify destination buffer data && expeted data */
    if(0 != memcmp(u8DestBuf, u8SourceBuf, sizeof(u8SourceBuf)))
    {
        u8CmpRet += 1U;
    }

    if(0 != memcmp(u16DestBuf, u16SourceBuf, sizeof(u16SourceBuf)))
    {
        u8CmpRet += 1U;
    }

    if(0 != memcmp(u32DestBuf, u32SourceBuf, sizeof(u32SourceBuf)))
    {
        u8CmpRet += 1U;
    }

    if(0U == u8CmpRet)
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
