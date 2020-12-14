/**
 *******************************************************************************
 * @file  spi/spi_master/source/main.c
 * @brief Main program SPI master for the Device Driver Library.
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
 * @addtogroup SPI_Master
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*
 * Function control.
 * Defines the following macro as non-zero to enable the corresponding function.
 * 'SPI_FUNC_TEST_SLAVE': Used to test salve mode of SPI. It is used as master for 'spi_slave'
 */
#define SPI_FUNC_TEST_SLAVE             (1U)

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
 * NOTE! The maximum transmission baud rate of the slave is PCLK1/6, slave's PCLK1. \
     Master baud rate depends on slave baud rate.
 */
#define SPI_CLK_DIV                     (SPI_CLK_DIV8)

/* SPI NSS pin active level. @ref SPI_NSS_Active_Level */
#define SPI_NSS_ACTIVE_LEVEL            (SPI_NSS_ACTIVE_LOW)

/* SPI data buffer size definition. */
#define SPI_BUF_LEN                     (8U)

/* Customer definitions. */
#if (SPI_FUNC_TEST_SLAVE > 0U)
    #define SPI_CMD_WR_SLAVE            (0x51U)     /* Customer definition. */
    #define SPI_CMD_RD_SLAVE            (0x56U)     /* Customer definition. */
#endif

/* SPI timeout value. According to max clock divider of PCLK1 and SPI. */
#define SPI_TIMEOUT                     (16384UL)

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

static void SpiConfig(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
#if (SPI_FUNC_TEST_SLAVE > 0U)
    static uint8_t m_au8SpiTxBuf[SPI_BUF_LEN] = {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57};
    static uint8_t m_au8SpiRxBuf[SPI_BUF_LEN];
#else
    static uint8_t m_au8SpiTxBuf[SPI_BUF_LEN] = {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57};
#if (SPI_TRANS_MD == SPI_FULL_DUPLEX)
    static uint8_t m_au8SpiRxBuf[SPI_BUF_LEN];
#endif
#endif /* #if (SPI_FUNC_TEST_SLAVE > 0U) */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of spi_master project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
#if (SPI_FUNC_TEST_SLAVE > 0U)
    uint32_t i;
#endif

    /* MCU Peripheral registers write unprotected. */
    Peripheral_WE();
#if (DDL_PRINT_ENABLE == DDL_ON)
    /* Initializes UART for debug printing. Baudrate is 115200. */
    (void)DDL_PrintfInit();
#endif /* #if (DDL_PRINT_ENABLE == DDL_ON) */
    /* Initializes key. */
    BSP_KEY_Init(BSP_KEY_MD_GPIO);
    /* Configures SPI. */
    SpiConfig();
    /* MCU Peripheral registers write protected. */
    Peripheral_WP();

    /***************** Configuration end, application start **************/
    DBG("------- Master start -------\n");

    for (;;)
    {
        /* Press key SW1 to start. */
        while (BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_GPIO) == Reset)
        {
            __NOP();
        }
        while (BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_GPIO) == Set)
        {
            __NOP();
        }

#if (SPI_FUNC_TEST_SLAVE > 0U)
        /* Write data to the slave. */
        m_au8SpiTxBuf[0U] = SPI_CMD_WR_SLAVE;
        (void)SPI_Trans(SPI_UNIT, (uint8_t *)&m_au8SpiTxBuf[0U], SPI_BUF_LEN, SPI_TIMEOUT);
        /* Delay for slave handling data. */
        DDL_DelayMS(20U);

        /* Read data from the slave. */
        m_au8SpiTxBuf[0U] = SPI_CMD_RD_SLAVE;
        (void)SPI_Trans(SPI_UNIT, (uint8_t *)&m_au8SpiTxBuf[0U], SPI_BUF_LEN, SPI_TIMEOUT);
        /* Delay for slave handling data. */
        DDL_DelayMS(50U);
        (void)SPI_Receive(SPI_UNIT, (uint8_t *)&m_au8SpiRxBuf[0U], SPI_BUF_LEN, SPI_TIMEOUT);
        /* User code: Use the data received from slave. */
        DBG("Master received data:");
        for (i=0UL; i<SPI_BUF_LEN; i++)
        {
            DBG(" 0x%.2x", m_au8SpiRxBuf[i]);
        }
        DBG("\n");
#else
    #if (SPI_TRANS_MD == SPI_FULL_DUPLEX)
        /* SPI send and receive in master mode. */
        SPI_TransReceive(SPI_UNIT,    \
                         (uint8_t *)&m_au8SpiTxBuf[0U], \
                         (uint8_t *)&m_au8SpiRxBuf[0U], \
                         SPI_BUF_LEN, \
                         SPI_TIMEOUT);
    #else
        /* SPI send only in master mode. */
        SPI_Trans(SPI_UNIT, (uint8_t *)&m_au8SpiTxBuf[0U], SPI_BUF_LEN, SPI_TIMEOUT);
    #endif
#endif /* #if (SPI_FUNC_TEST_SLAVE > 0U) */
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
 * @brief  SPI configuration, including initialization and pin configuration.
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
    stcSpiInit.u32WireMode       = SPI_WIRE_MD;
    stcSpiInit.u32TransMode      = SPI_TRANS_MD;
    stcSpiInit.u32NssActiveLevel = SPI_NSS_ACTIVE_LEVEL;
    stcSpiInit.u32SpiMode        = SPI_MD;
    stcSpiInit.u32ClockDiv       = SPI_CLK_DIV;
    /* The SPI register can be written only after the SPI peripheral is enabled. */
    CLK_FcgPeriphClockCmd(SPI_PERIPH_CLK, Enable);
    /* Initializes SPI. */
    (void)SPI_Init(SPI_UNIT, &stcSpiInit);
    /* Enable SPI function. */
    SPI_Cmd(SPI_UNIT, Enable);
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
