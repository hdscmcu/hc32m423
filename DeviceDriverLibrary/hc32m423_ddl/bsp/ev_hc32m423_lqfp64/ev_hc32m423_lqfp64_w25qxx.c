/**
 *******************************************************************************
 * @file  ev_hc32m423_lqfp64_w25qxx.c
 * @brief This file provides firmware functions for QSPI/SPI NOR W25QXX.
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
#include "ev_hc32m423_lqfp64_w25qxx.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32M423_LQFP64
 * @{
 */

/** @defgroup EV_HC32M423_LQFP64_W25QXX HC32M423 EVB W25QXX
  * @{
  */

#if ((BSP_W25QXX_ENABLE == BSP_ON) && \
     (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423))

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* SPI timeout value. According to max clock divider of PCLK1 and SPI. */
#define W25Q_SPI_TIMEOUT                (16384UL)

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
 * @defgroup W25QXX_Global_Functions W25QXX Global Functions
 * @{
 */

/**
 * @brief  Initializes SPI for W25QXX.
 * @param  None
 * @retval None
 */
void BSP_W25Q_SPI_Init(void)
{
    stc_gpio_init_t stcGpioInit;
    stc_spi_init_t stcSpiInit;

    /* Set a default value for structures. */
    (void)SPI_StructInit(&stcSpiInit);
    (void)GPIO_StructInit(&stcGpioInit);

    /* Configure peripheral clock */
    CLK_FcgPeriphClockCmd(W25Q_SPI_UNIT_CLOCK, Enable);

    /* Pin configuration. */
    GPIO_SetFunc(W25Q_SCK_PORT, W25Q_SCK_PIN, W25Q_SCK_FUNC);
    GPIO_SetFunc(W25Q_MOSI_PORT, W25Q_MOSI_PIN, W25Q_MOSI_FUNC);
    GPIO_SetFunc(W25Q_MISO_PORT, W25Q_MISO_PIN, W25Q_MISO_FUNC);

    stcGpioInit.u16PullUp = PIN_PU_ON;
    (void)GPIO_Init(W25Q_MISO_PORT, W25Q_MISO_PIN, &stcGpioInit);

    (void)GPIO_Init(W25Q_CS_PORT, W25Q_CS_PIN, &stcGpioInit);
    GPIO_OE(W25Q_CS_PORT, W25Q_CS_PIN, Enable);
    W25Q_CS_INACTIVE();

    /* Initializes SPI. */
    stcSpiInit.u32WireMode = SPI_3WIRE;
    stcSpiInit.u32ClockDiv = SPI_CLK_DIV2;
    (void)SPI_Init(W25Q_SPI_UNIT, &stcSpiInit);

    /* Enable SPI. */
    SPI_Cmd(W25Q_SPI_UNIT, Enable);
}

/**
 * @brief  BSP W25QXX SPI transmit and receive data.
 * @param  [in]  pvTxBuf            The pointer to the buffer which contains the data to be sent.
 *                                  If this pointer is NULL and the pvRxBuf is NOT NULL, the MOSI output high
 *                                  and the the received data will be stored in the buffer pointed by pvRxBuf.
 * @param  [in]  u32TxLen           The length of the data(in byte or half word) to be sent and received.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                      No errors occurred
 *   @arg  ErrorTimeout:            SPI transmit and receive timeout.
 *   @arg  ErrorInvalidParameter:   pvRxBuf == NULL or pvRxBuf == NULL or u32TxLen == 0U
 * @note   SPI receives data while sending data. Only works in full duplex master mode.
 */
en_result_t BSP_W25Q_SPI_Trans(const void *pvTxBuf, uint32_t u32TxLen)
{
    return SPI_Trans(W25Q_SPI_UNIT, pvTxBuf, u32TxLen, W25Q_SPI_TIMEOUT);
}

/**
 * @brief  BSP W25QXX SPI receive data.
 * @param  [in]  pvRxBuf            The pointer to the buffer which the received data to be stored.
 * @param  [in]  u32RxLen           The length of the data to be received.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                      No errors occurred
 *   @arg  ErrorTimeout:            SPI receive timeout.
 *   @arg  ErrorInvalidParameter:   pvRxBuf == NULL or u32RxLen == 0U
 * @note   -No NSS pin active and inactive operation in 3-wire mode. Add operations of NSS pin depending on your application.
 *         -This function only works in full duplex master mode.
 */
en_result_t BSP_W25Q_SPI_Receive(void *pvRxBuf, uint32_t u32RxLen)
{
    return SPI_Receive(W25Q_SPI_UNIT, pvRxBuf, u32RxLen, W25Q_SPI_TIMEOUT);
}

/**
 * @}
 */

/**
 * @addtogroup W25QXX_Local_Functions W25QXX Local Functions
 * @{
 */

/**
 * @}
 */

#endif /* BSP_W25QXX_ENABLE && (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423) */

/**
 * @}
 */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
