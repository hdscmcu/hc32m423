/**
 *******************************************************************************
 * @file  spi/spi_dma/source/main.c
 * @brief Main program SPI DMA for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-15       CDT             First version
   2020-12-04       CDT             Refined this example.
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
 * @addtogroup SPI_Dma
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*
 * SPI unit instance for this example.
 * 'SPI_UNIT' can only be defined as CM_SPI.
 */
#define SPI_UNIT                        (CM_SPI)
#define SPI_PERIPH_CLK                  (CLK_FCG_SPI)

/* SPI pin definition. */
#define SPI_NSS_PORT                    (GPIO_PORT_D)
#define SPI_NSS_PIN                     (GPIO_PIN_6)
#define SPI_SCK_PORT                    (GPIO_PORT_D)
#define SPI_SCK_PIN                     (GPIO_PIN_4)
#define SPI_MOSI_PORT                   (GPIO_PORT_D)
#define SPI_MOSI_PIN                    (GPIO_PIN_3)
#define SPI_MISO_PORT                   (GPIO_PORT_D)
#define SPI_MISO_PIN                    (GPIO_PIN_5)

/* SPI wire mode definition. @ref SPI_Wire_Mode */
#define SPI_WIRE_MD                     (SPI_4WIRE)

/*
 * SPI standard mode. @ref SPI_Standard_Mode
 * NOTE: Only SPI_MD1 and SPI_MD3 can be used in 3-wire slave mode.
 */
#define SPI_MD                          (SPI_MD1)

/* SPI transmission mode. @ref SPI_Trans_Mode */
#define SPI_TRANS_MD                    (SPI_FULL_DUPLEX)

/*
 * SPI baud rate divider. @ref SPI_Clock_Divider
 * NOTE! The maximum transmission baud rate of the slave is PCLK/6. \
     Master baud rate depends on slave PCLK frequency.
 */
#define SPI_CLK_DIV                     (SPI_CLK_DIV8)

/* SPI NSS pin active level. @ref SPI_NSS_Active_Level */
#define SPI_NSS_ACTIVE_LEVEL            (SPI_NSS_ACTIVE_LOW)

/* SPI data buffer size definition. */
#define SPI_BUF_LEN                     (8UL)
#define SPI_IDLE_TIME                   (4000U)             /* Customer definition. */

/* Command from master. */
#define SPI_CMD_WR_SLAVE                (0x51U)             /* Customer definition. */
#define SPI_CMD_RD_SLAVE                (0x56U)             /* Customer definition. */
#define SPI_DUMMY_DATA                  (0xFFU)

/* SPI DMA definition. */
#define SPI_DMA_UNIT                    (CM_DMA)
#define SPI_DMA_PERIPH_CLK              (CLK_FCG_DMA)

#define SPI_DMA_DATA_WIDTH              (DMA_DATA_WIDTH_8BIT)

#define SPI_RX_DMA_BLOCK_SIZE           (1UL)
#define SPI_RX_DMA_TRANS_CNT            (SPI_BUF_LEN)
#define SPI_RX_DMA_CH                   (DMA_CH0)
#define SPI_RX_DMA_TRIG_SRC             (EVT_SPI_SPRI)
#define SPI_RX_DMA_SRC_ADDR             ((uint32_t)(&SPI_UNIT->DR))
#define SPI_RX_DMA_DEST_ADDR            ((uint32_t)(&m_au8SpiRxBuf[0U]))
#define SPI_RX_DMA_DEST_ADDR_MD         (DMA_DEST_ADDR_MD_INC)
#define SPI_RX_DMA_SRC_ADDR_MD          (DMA_SRC_ADDR_MD_FIX)
#define SPI_RX_DMA_LLP_MD               (DMA_LLP_WAIT)
#define SPI_RX_DMA_LLP_POS              (DMA_CH0CTL0_LLP_POS - 4U)
#define SPI_RX_DMA_LLP_ADDR_MD          (DMA_LLP_ADDR_RAM)
#define SPI_RX_DMA_INT_TYPE             (DMA_INT_TC0)
#define SPI_RX_DMA_IRQn                 (DMA_TC0_IRQn)
#define SPI_RX_DMA_IRQ_PRI              (DDL_IRQ_PRI03)
#define SPI_RX_DMA_FLAG                 (DMA_INT_TC0)
#define SPI_RX_DMA_IRQ_HANDLER          (DMA_TC0_IrqHandler)

#define SPI_TX_DMA_BLOCK_SIZE           (1UL)
#define SPI_TX_DMA_TRANS_CNT            (SPI_BUF_LEN)
#define SPI_TX_DMA_CH                   (DMA_CH1)
#define SPI_TX_DMA_TRIG_SRC             (EVT_SPI_SPTI)
#define SPI_TX_DMA_SRC_ADDR             ((uint32_t)(&m_au8SpiTxBuf[0U]))
#define SPI_TX_DMA_DEST_ADDR            ((uint32_t)(&SPI_UNIT->DR))
#define SPI_TX_DMA_DEST_ADDR_MD         (DMA_DEST_ADDR_MD_FIX)
#define SPI_TX_DMA_SRC_ADDR_MD          (DMA_SRC_ADDR_MD_INC)
#define SPI_TX_DMA_LLP_MD               (DMA_LLP_WAIT)
#define SPI_TX_DMA_LLP_POS              (DMA_CH1CTL0_LLP_POS - 4U)
#define SPI_TX_DMA_LLP_ADDR_MD          (DMA_LLP_ADDR_RAM)
#define SPI_TX_DMA_INT_TYPE             (DMA_INT_TC1)
#define SPI_TX_DMA_IRQn                 (DMA_TC1_IRQn)
#define SPI_TX_DMA_IRQ_PRI              (DDL_IRQ_PRI04)
#define SPI_TX_DMA_FLAG                 (DMA_INT_TC1)
#define SPI_TX_DMA_IRQ_HANDLER          (DMA_TC1_IrqHandler)

#define SPI_DMA_LLP_MASK                (DMA_CH0CTL0_LLP)

/* Debug printing definition. */
#if (DDL_PRINT_ENABLE == DDL_ON)
#define DBG         (void)printf
#else
#define DBG(...)
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);

static void DmaConfig(void);
static void DmaIrqConfig(void);
static void SpiConfig(void);
static void SpiIrqConfig(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8RxFlag = 0U;
static uint8_t m_au8SpiRxBuf[SPI_BUF_LEN];
static uint8_t m_au8SpiTxBuf[SPI_BUF_LEN] = \
{
    0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80
};

#if defined (__ICCARM__)
_Pragma("data_alignment=16")
static stc_dma_llp_descriptor_t m_stcLlpDescRx;
_Pragma("data_alignment=16")
static stc_dma_llp_descriptor_t m_stcLlpDescTx;
#else
static stc_dma_llp_descriptor_t m_stcLlpDescRx __ALIGNED(16);
static stc_dma_llp_descriptor_t m_stcLlpDescTx __ALIGNED(16);
#endif

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of spi_dma project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t i;
    /* The maximum transfer rate of the slave is PCLK/6.
       The SPI clock of the slave is from the master, so the SCK frequency
       of the master SPI is at most PCLK/6. */

    /* MCU Peripheral registers write unprotected. */
    Peripheral_WE();
#if (DDL_PRINT_ENABLE == DDL_ON)
    /* Initializes UART for debug printing. Baudrate is 115200. */
    (void)DDL_PrintfInit();
#endif /* #if (DDL_PRINT_ENABLE == DDL_ON) */
    /* Configures DMA for SPI. */
    DmaConfig();
    /* Configures SPI. */
    SpiConfig();
    /* MCU Peripheral registers write protected. */
    Peripheral_WP();

    /***************** Configuration end, application start **************/

    for (;;)
    {
        if (u8RxFlag != 0U)
        {
            u8RxFlag = 0U;

            if (m_au8SpiRxBuf[0U] == SPI_CMD_WR_SLAVE)
            {
                /* User code: Use the data from the master. */
            }

            if (m_au8SpiRxBuf[0U] == SPI_CMD_RD_SLAVE)
            {
                /* Prepare data that needs to be sent to the master. */
                m_au8SpiTxBuf[0U]++;
                m_au8SpiTxBuf[1U]++;
                m_au8SpiTxBuf[2U]++;
                m_au8SpiTxBuf[3U]++;
                m_au8SpiTxBuf[4U]++;
                m_au8SpiTxBuf[5U]++;
                m_au8SpiTxBuf[6U]++;
                m_au8SpiTxBuf[7U]++;
            }

            DBG("Slave received data:");
            for (i=0UL; i<SPI_BUF_LEN; i++)
            {
                DBG(" 0x%.2x", m_au8SpiRxBuf[i]);
            }
            DBG("\n");

            SPI_Cmd(SPI_UNIT, Disable);
            DMA_ChCmd(SPI_DMA_UNIT, SPI_TX_DMA_CH, Enable);
            SPI_Cmd(SPI_UNIT, Enable);
        }
    }
}

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
    /* Unlock PWC, CLK, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Unlock(PWC_UNLOCK_CODE_0);
    /* Unlock all EFM registers */
    /* EFM_Unlock(); */
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
    /* Lock PWC, CLK, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Lock(PWC_UNLOCK_CODE_0);
    /* Lock all EFM registers */
    /* EFM_Lock(); */
}

/**
 * @brief  DMA configuration for SPI.
 * @param  None
 * @retval None
 */
static void DmaConfig(void)
{
    stc_dma_init_t stcDmaInit;
    stc_dma_llp_init_t stcDmaLlpInit;

    CLK_FcgPeriphClockCmd(SPI_DMA_PERIPH_CLK, Enable);

    /* Descriptor RX. This structure variable is used to reload the configuration of the RX channel. */
    m_stcLlpDescRx.SARx    = SPI_RX_DMA_SRC_ADDR;
    m_stcLlpDescRx.DARx    = SPI_RX_DMA_DEST_ADDR;
    m_stcLlpDescRx.CHxCTL0 = SPI_RX_DMA_BLOCK_SIZE | \
                             (SPI_RX_DMA_TRANS_CNT << DMA_CH0CTL0_CNT_POS) | \
                             (((uint32_t)&m_stcLlpDescRx << SPI_RX_DMA_LLP_POS) & SPI_DMA_LLP_MASK)| \
                             DMA_LLP_ENABLE    | \
                             SPI_RX_DMA_LLP_MD | \
                             SPI_DMA_DATA_WIDTH;
    m_stcLlpDescRx.CHxCTL1 = SPI_RX_DMA_SRC_ADDR_MD  | \
                             SPI_RX_DMA_DEST_ADDR_MD | \
                             SPI_RX_DMA_LLP_ADDR_MD;

    (void)DMA_LlpStructInit(&stcDmaLlpInit);
    stcDmaLlpInit.u32Llp       = DMA_LLP_ENABLE;
    stcDmaLlpInit.u32LlpMode   = SPI_RX_DMA_LLP_MD;
    stcDmaLlpInit.u32LlpAddr   = (uint32_t)&m_stcLlpDescRx;
    stcDmaLlpInit.u32LlpAddrMode = SPI_RX_DMA_LLP_ADDR_MD;

    /* Config DMA */
    stcDmaInit.u32SrcAddr      = SPI_RX_DMA_SRC_ADDR;
    stcDmaInit.u32DestAddr     = SPI_RX_DMA_DEST_ADDR;
    stcDmaInit.u32DataWidth    = SPI_DMA_DATA_WIDTH;
    stcDmaInit.u32BlockSize    = SPI_RX_DMA_BLOCK_SIZE;
    stcDmaInit.u32TransCount   = SPI_RX_DMA_TRANS_CNT;
    stcDmaInit.u32SrcAddrMode  = SPI_RX_DMA_SRC_ADDR_MD;
    stcDmaInit.u32DestAddrMode = SPI_RX_DMA_DEST_ADDR_MD;

    CLK_FcgPeriphClockCmd(SPI_DMA_PERIPH_CLK, Enable);
    (void)DMA_LlpInit(SPI_DMA_UNIT, SPI_RX_DMA_CH, &stcDmaLlpInit);
    (void)DMA_Init(SPI_DMA_UNIT, SPI_RX_DMA_CH, &stcDmaInit);

    /* Descriptor TX. This structure variable is used to reload the configuration of the TX channel. */
    m_stcLlpDescTx.SARx    = SPI_TX_DMA_SRC_ADDR;
    m_stcLlpDescTx.DARx    = SPI_TX_DMA_DEST_ADDR;
    m_stcLlpDescTx.CHxCTL0 = SPI_TX_DMA_BLOCK_SIZE | \
                             (SPI_TX_DMA_TRANS_CNT << DMA_CH1CTL0_CNT_POS) | \
                             (((uint32_t)&m_stcLlpDescTx << SPI_TX_DMA_LLP_POS) & SPI_DMA_LLP_MASK) | \
                             DMA_LLP_ENABLE    | \
                             SPI_TX_DMA_LLP_MD | \
                             SPI_DMA_DATA_WIDTH;
    m_stcLlpDescTx.CHxCTL1 = SPI_TX_DMA_SRC_ADDR_MD  | \
                             SPI_TX_DMA_DEST_ADDR_MD | \
                             SPI_TX_DMA_LLP_ADDR_MD;

    stcDmaLlpInit.u32Llp       = DMA_LLP_ENABLE;
    stcDmaLlpInit.u32LlpMode   = SPI_TX_DMA_LLP_MD;
    stcDmaLlpInit.u32LlpAddr   = (uint32_t)&m_stcLlpDescTx;
    stcDmaLlpInit.u32LlpAddrMode = SPI_TX_DMA_LLP_ADDR_MD;

    /* Config DMA */
    stcDmaInit.u32SrcAddr      = SPI_TX_DMA_SRC_ADDR;
    stcDmaInit.u32DestAddr     = SPI_TX_DMA_DEST_ADDR;
    stcDmaInit.u32DataWidth    = SPI_DMA_DATA_WIDTH;
    stcDmaInit.u32BlockSize    = SPI_TX_DMA_BLOCK_SIZE;
    stcDmaInit.u32TransCount   = SPI_TX_DMA_TRANS_CNT;
    stcDmaInit.u32SrcAddrMode  = SPI_TX_DMA_SRC_ADDR_MD;
    stcDmaInit.u32DestAddrMode = SPI_TX_DMA_DEST_ADDR_MD;

    (void)DMA_LlpInit(SPI_DMA_UNIT, SPI_TX_DMA_CH, &stcDmaLlpInit);
    (void)DMA_Init(SPI_DMA_UNIT, SPI_TX_DMA_CH, &stcDmaInit);

    /* Enable AOS clock */
    CLK_FcgPeriphClockCmd(CLK_FCG_AOS, Enable);

    /* Set DMA trigger source */
    DMA_SetTriggerSrc(SPI_DMA_UNIT, SPI_RX_DMA_CH, SPI_RX_DMA_TRIG_SRC);
    DMA_SetTriggerSrc(SPI_DMA_UNIT, SPI_TX_DMA_CH, SPI_TX_DMA_TRIG_SRC);

    DMA_ClearTransIntStatus(SPI_DMA_UNIT, SPI_RX_DMA_FLAG | SPI_TX_DMA_FLAG);

    DmaIrqConfig();

    /* Enable DMA channel. */
    DMA_ChCmd(SPI_DMA_UNIT, SPI_RX_DMA_CH, Enable);
    DMA_ChCmd(SPI_DMA_UNIT, SPI_TX_DMA_CH, Enable);

    /* Enable DMA. */
    DMA_Cmd(SPI_DMA_UNIT, Enable);
}

/**
 * @brief  Interrupt configuration.
 * @param  None
 * @retval None
 */
static void DmaIrqConfig(void)
{
    stc_irq_signin_config_t stcCfg;

    stcCfg.enIRQn = SPI_RX_DMA_IRQn;
    (void)INTC_IrqSignIn(&stcCfg);

    NVIC_ClearPendingIRQ(stcCfg.enIRQn);
    NVIC_SetPriority(stcCfg.enIRQn, SPI_RX_DMA_IRQ_PRI);
    NVIC_EnableIRQ(stcCfg.enIRQn);

    stcCfg.enIRQn = SPI_TX_DMA_IRQn;
    (void)INTC_IrqSignIn(&stcCfg);

    NVIC_ClearPendingIRQ(stcCfg.enIRQn);
    NVIC_SetPriority(stcCfg.enIRQn, SPI_TX_DMA_IRQ_PRI);
    NVIC_EnableIRQ(stcCfg.enIRQn);

    DMA_TransIntCmd(SPI_DMA_UNIT, SPI_RX_DMA_INT_TYPE|SPI_TX_DMA_INT_TYPE, Enable);
}

/**
 * @brief  DMA TC0 IRQ handler.
 * @param  None
 * @retval None
 */
void DMA_TC0_IrqHandler(void)
{
    DMA_ClearTransIntStatus(SPI_DMA_UNIT, SPI_RX_DMA_FLAG);
    u8RxFlag = 1U;
}

/**
 * @brief  DMA TC1 IRQ handler.
 * @param  None
 * @retval None
 */
void DMA_TC1_IrqHandler(void)
{
    DMA_ChCmd(SPI_DMA_UNIT, SPI_TX_DMA_CH, Disable);
    DMA_ClearTransIntStatus(SPI_DMA_UNIT, SPI_TX_DMA_FLAG);
}

/**
 * @brief  SPI configuration, including initialization, pin configuration
 *         and interrupt configuration.
 * @param  None
 * @retval None
 */
static void SpiConfig(void)
{
    stc_spi_init_t stcSpiInit;

    /* Set the pins to SPI function. */
#if (SPI_WIRE_MD == SPI_4WIRE)
    GPIO_SetFunc(SPI_NSS_PORT, SPI_NSS_PIN, GPIO_FUNC_6_SPI);
#endif
    GPIO_SetFunc(SPI_SCK_PORT, SPI_SCK_PIN, GPIO_FUNC_6_SPI);
    GPIO_SetFunc(SPI_MOSI_PORT, SPI_MOSI_PIN, GPIO_FUNC_6_SPI);
    GPIO_SetFunc(SPI_MISO_PORT, SPI_MISO_PIN, GPIO_FUNC_6_SPI);

    /* Set a default value. */
    (void)SPI_StructInit(&stcSpiInit);
    /* User configuration value. */
    stcSpiInit.u32MasterSlave    = SPI_SLAVE;
    stcSpiInit.u32WireMode       = SPI_WIRE_MD;
    stcSpiInit.u32TransMode      = SPI_TRANS_MD;
    stcSpiInit.u32NssActiveLevel = SPI_NSS_ACTIVE_LEVEL;
    stcSpiInit.u32SpiMode        = SPI_MD;
    stcSpiInit.u32ClockDiv       = SPI_CLK_DIV;

    /* The SPI register can be written only after the SPI peripheral is enabled. */
    CLK_FcgPeriphClockCmd(SPI_PERIPH_CLK, Enable);
    /* Initializes SPI. */
    (void)SPI_Init(SPI_UNIT, &stcSpiInit);
    /* Enable mode fault detection if needed. */
    SPI_ModeFaultDetectCmd(SPI_UNIT, Enable);
    /* SPI interrupt configuration. */
    SpiIrqConfig();
    /* Enable SPI function. */
    SPI_Cmd(SPI_UNIT, Enable);
}

/**
 * @brief  SPI interrupt configuration.
 * @param  None
 * @retval None
 */
static void SpiIrqConfig(void)
{
    stc_irq_signin_config_t stcIrqCfg;

    /* Configures error interrupt. */
    stcIrqCfg.enIRQn = SPI_SPEI_IRQn;
    (void)INTC_IrqSignIn(&stcIrqCfg);
    NVIC_ClearPendingIRQ(stcIrqCfg.enIRQn);
    NVIC_SetPriority(stcIrqCfg.enIRQn, DDL_IRQ_PRI05);
    NVIC_EnableIRQ(stcIrqCfg.enIRQn);

    /* Enable the interrupts. */
    SPI_IntCmd(SPI_UNIT, SPI_INT_ERR, Enable);
}

/**
 * @brief  SPI error interrupt callback function.
 * @param  None
 * @retval None
 */
void SPI_Error_IrqHandler(void)
{
    uint32_t u32Data;

    if (SPI_GetStatus(SPI_UNIT, SPI_FLAG_OVERLOAD) == Set)
    {
        u32Data  = (uint8_t)SPI_ReadData(SPI_UNIT);
        u32Data |= SPI_FLAG_OVERLOAD;
        SPI_ClearStatus(SPI_UNIT, u32Data & SPI_FLAG_OVERLOAD);
    }

    if (SPI_GetStatus(SPI_UNIT, SPI_FLAG_MD_FAULT) == Set)
    {
        SPI_ClearStatus(SPI_UNIT, SPI_FLAG_MD_FAULT);
        SPI_Cmd(SPI_UNIT, Enable);
    }

    if (SPI_GetStatus(SPI_UNIT, SPI_FLAG_PARITY_ERR) == Set)
    {
        SPI_ClearStatus(SPI_UNIT, SPI_FLAG_PARITY_ERR);
    }

    if (SPI_GetStatus(SPI_UNIT, SPI_FLAG_UNDERLOAD) == Set)
    {
        SPI_ClearStatus(SPI_UNIT, SPI_FLAG_UNDERLOAD);
        SPI_Cmd(SPI_UNIT, Enable);
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
