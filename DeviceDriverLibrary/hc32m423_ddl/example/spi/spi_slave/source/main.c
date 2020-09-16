/**
 *******************************************************************************
 * @file  spi/spi_slave/source/main.c
 * @brief Main program SPI slave interrupt for the Device Driver Library.
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
 * @addtogroup SPI_Slave_Interrupt
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
#define SPI_UNIT                    (CM_SPI)
#define SPI_PERIPH_CLK              (CLK_FCG_SPI)

/* SPI pin definition. */
#define SPI_NSS_PORT                (GPIO_PORT_D)
#define SPI_NSS_PIN                 (GPIO_PIN_6)
#define SPI_SCK_PORT                (GPIO_PORT_D)
#define SPI_SCK_PIN                 (GPIO_PIN_4)
#define SPI_MOSI_PORT               (GPIO_PORT_D)
#define SPI_MOSI_PIN                (GPIO_PIN_3)
#define SPI_MISO_PORT               (GPIO_PORT_D)
#define SPI_MISO_PIN                (GPIO_PIN_5)

/* SPI wire mode definition. @ref SPI_Wire_Mode */
#define SPI_WIRE_MD                 (SPI_4WIRE)

/*
 * SPI standard mode. @ref SPI_Standard_Mode
 * NOTE: Only SPI_MD1 and SPI_MD3 can be used in 3-wire slave mode.
 */
#define SPI_MD                      (SPI_MD1)

/* SPI transmission mode. @ref SPI_Trans_Mode */
#define SPI_TRANS_MD                (SPI_FULL_DUPLEX)

/*
 * SPI baud rate divider. @ref SPI_Clock_Divider
 * NOTE! The maximum transmission baud rate of the slave is PCLK/6. \
     Master baud rate depends on slave PCLK frequency.
 */
#define SPI_CLK_DIV                 (SPI_CLK_DIV8)

/* SPI NSS pin active level. @ref SPI_NSS_Active_Level */
#define SPI_NSS_ACTIVE_LEVEL        (SPI_NSS_ACTIVE_LOW)

/* SPI data buffer size definition. */
#define SPI_BUF_LEN                 (8U)
#define SPI_IDLE_TIME               (400U)              /* Customer definition. */

/* Command from master. */
#define SPI_CMD_WR_SLAVE            (0x51U)             /* Customer definition. */
#define SPI_CMD_RD_SLAVE            (0x56U)             /* Customer definition. */
#define SPI_DUMMY_DATA              (0xFFU)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);

static void SpiConfig(void);
static void SpiIrqConfig(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static __IO uint32_t m_u32RxIdle    = 0U;
static __IO uint8_t m_u8RxStart     = 0U;
static __IO uint8_t m_u8RxDataCount = 0U;
static __IO uint8_t m_u8TxDataCount = 0U;
/* All of the data is valid. */
static __IO uint8_t m_au8SpiRxBuf[SPI_BUF_LEN];
/* Valid data starts at offset 0 and length is SPI_BUF_LEN-2. */
static __IO uint8_t m_au8SpiTxBuf[SPI_BUF_LEN] = \
{
    0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of spi_slave project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* The maximum transfer rate of the slave is PCLK/6.
       The SPI clock of the slave is from the master, so the SCK frequency
       of the master SPI is at most PCLK/6. */

    /* MCU Peripheral registers write unprotected. */
    Peripheral_WE();
    /* Configures SPI. */
    SpiConfig();
    /* MCU Peripheral registers write protected. */
    Peripheral_WP();
    /***************** Configuration end, application start **************/

    for (;;)
    {
        if (m_u8RxStart)
        {
            if (++m_u32RxIdle >= SPI_IDLE_TIME)
            {
                if (m_au8SpiRxBuf[0U] == SPI_CMD_WR_SLAVE)
                {
                    /* User code: Use the data from master. */
                }

                if (m_au8SpiRxBuf[0U] == SPI_CMD_RD_SLAVE)
                {
                    /* Prepare data that needs to be sent to master.
                       Valid data starts at offset 0 and length is SPI_BUF_LEN-2. */
                    m_au8SpiTxBuf[0U]++;
                    m_au8SpiTxBuf[1U]++;
                    m_au8SpiTxBuf[2U]++;
                    m_au8SpiTxBuf[3U]++;
                    m_au8SpiTxBuf[4U]++;
                    m_au8SpiTxBuf[5U]++;
                }
                m_u32RxIdle = 0U;
                m_u8RxStart = 0U;
                m_u8RxDataCount = 0U;
                m_u8TxDataCount = 0U;
            }
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

    /* Configures RX interrupt. */
    stcIrqCfg.enIRQn = SPI_SPRI_IRQn;
    (void)INTC_IrqSignIn(&stcIrqCfg);
    NVIC_ClearPendingIRQ(stcIrqCfg.enIRQn);
    NVIC_SetPriority(stcIrqCfg.enIRQn, DDL_IRQ_PRI02);
    NVIC_EnableIRQ(stcIrqCfg.enIRQn);

    /* Configures TX interrupt. */
    stcIrqCfg.enIRQn = SPI_SPTI_IRQn;
    (void)INTC_IrqSignIn(&stcIrqCfg);
    NVIC_ClearPendingIRQ(stcIrqCfg.enIRQn);
    NVIC_SetPriority(stcIrqCfg.enIRQn, DDL_IRQ_PRI03);
    NVIC_EnableIRQ(stcIrqCfg.enIRQn);

    /* Configures error interrupt. */
    stcIrqCfg.enIRQn = SPI_SPEI_IRQn;
    (void)INTC_IrqSignIn(&stcIrqCfg);
    NVIC_ClearPendingIRQ(stcIrqCfg.enIRQn);
    NVIC_SetPriority(stcIrqCfg.enIRQn, DDL_IRQ_PRI03);
    NVIC_EnableIRQ(stcIrqCfg.enIRQn);

    /* Enable the interrupts. */
    SPI_IntCmd(SPI_UNIT, \
               (SPI_INT_ERR | SPI_INT_RX_FULL | SPI_INT_TX_EMPTY), \
               Enable);
}

/**
 * @brief  SPI RX buffer full interrupt callback function. Read and save the \
 *         data received from master via MOSI.
 * @param  None
 * @retval None
 */
void SPI_RxEnd_IrqHandler(void)
{
    m_u8RxStart = 1U;
    m_u32RxIdle = 0U;
    if (m_u8RxDataCount < SPI_BUF_LEN)
    {
        m_au8SpiRxBuf[m_u8RxDataCount] = (uint8_t)SPI_ReadData(SPI_UNIT);
        m_u8RxDataCount++;
    }
}

/**
 * @brief  SPI TX buffer empty interrupt callback function. Load the data that \
 *         will be sent to master via MISO.
 * @param  None
 * @retval None
 */
void SPI_TxEmpty_IrqHandler(void)
{
    SPI_WriteData(SPI_UNIT, m_au8SpiTxBuf[m_u8TxDataCount++]);
    if (m_u8TxDataCount >= SPI_BUF_LEN)
    {
        m_u8TxDataCount = 0U;
    }
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
