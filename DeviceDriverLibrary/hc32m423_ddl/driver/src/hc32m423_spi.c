/**
 *******************************************************************************
 * @file  hc32m423_spi.c
 * @brief This file provides firmware functions to manage the Serial Peripheral
 *        Interface(SPI).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-15       CDT             First version
   2020-12-04       CDT             Corrected comments of SPI unit.
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
#include "hc32m423_spi.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_SPI SPI
 * @brief Serial Peripheral Interface Driver Library
 * @{
 */

#if (DDL_SPI_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SPI_Local_Macros SPI Local Macros
 * @{
 */

/**
 * @defgroup SPI_Configuration_Bit_Mask SPI Configuration Bit Mask
 * @{
 */
#define SPI_LOOPBACK_MODE_MASK      (SPI_LOOPBACK_REVERSE | SPI_CR1_SPLPBK2)
/**
 * @}
 */

/**
 * @defgroup SPI_Check_Parameters_Validity SPI check parameters validity
 * @{
 */
/*!< Parameter validity check for SPI unit. */
#define IS_SPI_UNIT(x)                                                         \
(   (x) == CM_SPI)

/*!< Parameter validity check for SPI wire mode. */
#define IS_SPI_WIRE_MODE(x)                                                    \
(   ((x) == SPI_4WIRE)                      ||                                 \
    ((x) == SPI_3WIRE))

/*!< Parameter validity check for SPI transmission mode. */
#define IS_SPI_TRANS_MODE(x)                                                   \
(   ((x) == SPI_FULL_DUPLEX)                ||                                 \
    ((x) == SPI_SEND_ONLY))

/*!< Parameter validity check for SPI master-slave mode. */
#define IS_SPI_MASTER_SLAVE(x)                                                 \
(   ((x) == SPI_SLAVE)                      ||                                 \
    ((x) == SPI_MASTER))

/*!< Parameter validity check for SPI loopback mode. */
#define IS_SPI_LOOPBACK_MD(x)                                                \
(   ((x) == SPI_LOOPBACK_INVD)              ||                                 \
    ((x) == SPI_LOOPBACK_REVERSE)           ||                                 \
    ((x) == SPI_LOOPBACK_NORMAL))

/*!< Parameter validity check for SPI parity check. */
#define IS_SPI_PARITY_CHECK(x)                                                 \
(   ((x) == SPI_PARITY_NONE)                ||                                 \
    ((x) == SPI_PARITY_EVEN)                ||                                 \
    ((x) == SPI_PARITY_ODD))

/*!< Parameter validity check for SPI NSS active level. */
#define IS_SPI_NSS_ACTIVE_LEVEL(x)                                             \
(   ((x) == SPI_NSS_ACTIVE_LOW)             ||                                 \
    ((x) == SPI_NSS_ACTIVE_HIGH))

/*!< Parameter validity check for SPI standard mode. */
#define IS_SPI_SPI_MD(x)                                                       \
(   ((x) == SPI_MD0)                        ||                                 \
    ((x) == SPI_MD1)                        ||                                 \
    ((x) == SPI_MD2)                        ||                                 \
    ((x) == SPI_MD3))

/*!< Parameter validity check for SPI clock divider. */
#define IS_SPI_CLK_DIV(x)                                                      \
(   ((x) == SPI_CLK_DIV2)                   ||                                 \
    ((x) == SPI_CLK_DIV4)                   ||                                 \
    ((x) == SPI_CLK_DIV8)                   ||                                 \
    ((x) == SPI_CLK_DIV16)                  ||                                 \
    ((x) == SPI_CLK_DIV32)                  ||                                 \
    ((x) == SPI_CLK_DIV64)                  ||                                 \
    ((x) == SPI_CLK_DIV128)                 ||                                 \
    ((x) == SPI_CLK_DIV256))

/*!< Parameter validity check for SPI data width. */
#define IS_SPI_DATA_WIDTH(x)                                                   \
(   ((x) == SPI_DATA_WIDTH_8BIT)            ||                                 \
    ((x) == SPI_DATA_WIDTH_16BIT))

/*!< Parameter validity check for SPI first bit. */
#define IS_SPI_FIRST_BIT(x)                                                    \
(   ((x) == SPI_FIRST_BIT_MSB)              ||                                 \
    ((x) == SPI_FIRST_BIT_LSB))

/*!< Parameter validity check for SPI bit mask. */
#define IS_SPI_BIT_MASK(x, mask)                                               \
(   ((x) != 0U)                             &&                                 \
    (((x) | (mask)) == mask))

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
 * @defgroup SPI_Local_Functions SPI Local Functions
 * @{
 */
static en_result_t SPI_TxRx(CM_SPI_TypeDef *SPIx, const void *pvTxBuf, void *pvRxBuf, \
                            uint32_t u32Len, uint32_t u32Timeout);
static en_result_t SPI_Tx(CM_SPI_TypeDef *SPIx, const void *pvBuf, \
                          uint32_t u32Len, uint32_t u32Timeout);
static en_result_t SPI_WaitStatus(const CM_SPI_TypeDef *SPIx, uint32_t u32FlagMsk, \
                                  uint32_t u32Value, uint32_t u32Timeout);

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
 * @defgroup SPI_Global_Functions SPI Global Functions
 * @{
 */

/**
 * @brief  Initializes the SPI peripheral according to the specified parameters
 *         in the structure stc_spi_init.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  pstcSpiInit            Pointer to a stc_spi_init_t structure that contains
 *                                      the configuration information for the SPI.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred
 *   @arg  ErrorInvalidParameter:       pstcSpiInit == NULL
 */
en_result_t SPI_Init(CM_SPI_TypeDef *SPIx, const stc_spi_init_t *pstcSpiInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcSpiInit != NULL)
    {
        DDL_ASSERT(IS_SPI_UNIT(SPIx));
        DDL_ASSERT(IS_SPI_WIRE_MODE(pstcSpiInit->u32WireMode));
        DDL_ASSERT(IS_SPI_TRANS_MODE(pstcSpiInit->u32TransMode));
        DDL_ASSERT(IS_SPI_MASTER_SLAVE(pstcSpiInit->u32MasterSlave));
        DDL_ASSERT(IS_SPI_PARITY_CHECK(pstcSpiInit->u32Parity));
        DDL_ASSERT(IS_SPI_NSS_ACTIVE_LEVEL(pstcSpiInit->u32NssActiveLevel));
        DDL_ASSERT(IS_SPI_SPI_MD(pstcSpiInit->u32SpiMode));
        DDL_ASSERT(IS_SPI_CLK_DIV(pstcSpiInit->u32ClockDiv));
        DDL_ASSERT(IS_SPI_DATA_WIDTH(pstcSpiInit->u32DataWidth));
        DDL_ASSERT(IS_SPI_FIRST_BIT(pstcSpiInit->u32FirstBit));

        WRITE_REG32(SPIx->CR1, \
                    (pstcSpiInit->u32WireMode    | \
                     pstcSpiInit->u32TransMode   | \
                     pstcSpiInit->u32MasterSlave | \
                     pstcSpiInit->u32Parity));

        WRITE_REG32(SPIx->CFG1, pstcSpiInit->u32NssActiveLevel);

        WRITE_REG32(SPIx->CFG2, \
                    (pstcSpiInit->u32SpiMode   | \
                     pstcSpiInit->u32ClockDiv  | \
                     pstcSpiInit->u32DataWidth | \
                     pstcSpiInit->u32FirstBit));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes the SPI peripheral.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @retval None
 */
void SPI_DeInit(CM_SPI_TypeDef *SPIx)
{
    DDL_ASSERT(IS_SPI_UNIT(SPIx));

    /* Disable SPI. */
    CLEAR_REG32_BIT(SPIx->CR1, SPI_CR1_SPE);
    /* Reset registers. */
    WRITE_REG32(SPIx->CR1, 0x0UL);
    WRITE_REG32(SPIx->CFG1, 0x10UL);
    WRITE_REG32(SPIx->CFG2, 0x20UL);
    WRITE_REG32(SPIx->SR, 0x31DUL);
}

/**
 * @brief  Set a default value for the SPI initialization structure.
 * @param  [in]  pstcSpiInit            Pointer to a stc_spi_init_t structure that
 *                                      contains configuration information.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcSpiInit == NULL.
 */
en_result_t SPI_StructInit(stc_spi_init_t *pstcSpiInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcSpiInit != NULL)
    {
        pstcSpiInit->u32WireMode        = SPI_4WIRE;
        pstcSpiInit->u32TransMode       = SPI_FULL_DUPLEX;
        pstcSpiInit->u32MasterSlave     = SPI_MASTER;
        pstcSpiInit->u32Parity          = SPI_PARITY_NONE;
        pstcSpiInit->u32NssActiveLevel  = SPI_NSS_ACTIVE_LOW;
        pstcSpiInit->u32SpiMode         = SPI_MD3;
        pstcSpiInit->u32ClockDiv        = SPI_CLK_DIV8;
        pstcSpiInit->u32DataWidth       = SPI_DATA_WIDTH_8BIT;
        pstcSpiInit->u32FirstBit        = SPI_FIRST_BIT_MSB;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable SPI interrupt.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  u32IntType             SPI interrupt type.
 *                                      This parameter can be values of @ref SPI_Interrupt_Type
 *   @arg  SPI_INT_ERR
 *   @arg  SPI_INT_TX_EMPTY
 *   @arg  SPI_INT_RX_FULL
 *   @arg  SPI_INT_IDLE
 *   @arg  SPI_INT_ALL
 * @param  [in]  enNewState             An en_functional_state_t enumeration value.
 *   @arg  Enable:                      Enable the specified interrupt of SPI.
 *   @arg  Disable:                     Disable the specified interrupt of SPI.
 * @retval None
 */
void SPI_IntCmd(CM_SPI_TypeDef *SPIx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_SPI_BIT_MASK(u32IntType, SPI_INT_ALL));

    if (enNewState == Enable)
    {
        SET_REG32_BIT(SPIx->CR1, u32IntType);
    }
    else
    {
        CLEAR_REG32_BIT(SPIx->CR1, u32IntType);
    }
}

/**
 * @brief  SPI function enable or disable.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  enNewState             An en_functional_state_t enumeration value.
 *   @arg  Enable:                      Enable SPI function.
 *   @arg  Disable:                     Disable SPI function.
 * @retval None
 */
void SPI_Cmd(CM_SPI_TypeDef *SPIx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG32_BIT(SPIx->CR1, SPI_CR1_SPE);
    }
    else
    {
        CLEAR_REG32_BIT(SPIx->CR1, SPI_CR1_SPE);
    }
}

/**
 * @brief  Enable or disable mode fault detection.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  enNewState             An en_functional_state_t enumeration value.
 *   @arg  Enable:                      Enable mode fault detection.
 *   @arg  Disable:                     Disable mode fault detection.
 * @retval None
 * @note   Enable only for slave mode.
 */
void SPI_ModeFaultDetectCmd(CM_SPI_TypeDef *SPIx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG32_BIT(SPIx->CR1, SPI_CR1_MODFE);
    }
    else
    {
        CLEAR_REG32_BIT(SPIx->CR1, SPI_CR1_MODFE);
    }
}

/**
 * @brief  SPI transmit data.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  pvBuf                  The pointer to the buffer which contains the data to be sent.
 * @param  [in]  u32Len                 The length of the data to be sent.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred
 *   @arg  ErrorTimeout:                SPI transmit timeout.
 *   @arg  ErrorInvalidParameter:       pvBuf == NULL or u32Len == 0UL
 * @note   -No NSS pin active and inactive operation in 3-wire mode. Add operations of NSS pin depending on your application.
 *         -This function supports full duplex mode and send only mode.
 */
en_result_t SPI_Trans(CM_SPI_TypeDef *SPIx, const void *pvBuf, \
                      uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t u32TransMode;
    en_result_t enRet = ErrorInvalidParameter;

    if ((pvBuf != NULL) && (u32Len != 0U))
    {
        DDL_ASSERT(IS_SPI_UNIT(SPIx));

        u32TransMode = READ_REG32_BIT(SPIx->CR1, SPI_SEND_ONLY);
        if (u32TransMode == SPI_FULL_DUPLEX)
        {
            /* Transmit data in full duplex mode. */
            enRet = SPI_TxRx(SPIx, pvBuf, NULL, u32Len, u32Timeout);
        }
        else
        {
            /* Transmit data in send only mode. */
            enRet = SPI_Tx(SPIx, pvBuf, u32Len, u32Timeout);
        }
    }

    return enRet;
}

/**
 * @brief  SPI receive data.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  pvBuf                  The pointer to the buffer which the received data to be stored.
 * @param  [in]  u32Len                 The length of the data to be received.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred
 *   @arg  ErrorTimeout:                SPI receive timeout.
 *   @arg  ErrorInvalidParameter:       pvBuf == NULL or u32Len == 0UL
 * @note   -No NSS pin active and inactive operation in 3-wire mode. Add operations of NSS pin depending on your application.
 *         -This function only works in full duplex master mode.
 */
en_result_t SPI_Receive(CM_SPI_TypeDef *SPIx, void *pvBuf, \
                        uint32_t u32Len, uint32_t u32Timeout)
{
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_SPI_UNIT(SPIx));

    if ((pvBuf != NULL) && (u32Len != 0U))
    {
        /* Receives data in full duplex master mode. */
        enRet = SPI_TxRx(SPIx, NULL, pvBuf, u32Len, u32Timeout);
    }

    return enRet;
}

/**
 * @brief  SPI transmit and receive data.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  pvTxBuf                The pointer to the buffer which contains the data to be sent.
 *                                      If this pointer is NULL and the pvRxBuf is NOT NULL, the MOSI output high
 *                                      and the the received data will be stored in the buffer pointed by pvRxBuf.
 * @param  [out] pvRxBuf                The pointer to the buffer which the received data will be stored.
 *                                      This for full duplex transfer.
 * @param  [in]  u32Len                 The length of the data(in byte or half word) to be sent and received.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred
 *   @arg  ErrorTimeout:                SPI transmit and receive timeout.
 *   @arg  ErrorInvalidParameter:       pvRxBuf == NULL or pvRxBuf == NULL or u32Len == 0U
 * @note   SPI receives data while sending data. Only works in full duplex master mode.
 */
en_result_t SPI_TransReceive(CM_SPI_TypeDef *SPIx, const void *pvTxBuf, void *pvRxBuf, \
                             uint32_t u32Len, uint32_t u32Timeout)
{
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_SPI_UNIT(SPIx));

    if ((pvTxBuf != NULL) && (pvRxBuf != NULL) && (u32Len != 0U))
    {
        /* Transmit and receive data in full duplex master mode. */
        enRet = SPI_TxRx(SPIx, pvTxBuf, pvRxBuf, u32Len, u32Timeout);
    }

    return enRet;
}

/**
 * @brief  SPI get status of the specified flag.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  u32Flag                SPI Flag.
 *                                      This parameter can be a value of @ref SPI_Flag
 *   @arg  SPI_FLAG_OVERLOAD
 *   @arg  SPI_FLAG_IDLE
 *   @arg  SPI_FLAG_MD_FAULT
 *   @arg  SPI_FLAG_PARITY_ERR
 *   @arg  SPI_FLAG_UNDERLOAD
 *   @arg  SPI_FLAG_TX_EMPTY
 *   @arg  SPI_FLAG_RX_FULL
 *   @arg  SPI_FLAG_ALL
 * @retval An en_flag_status_t enumeration type value.
 *   @arg  Set:                         At least one of the specified status flags is set.
 *   @arg  Reset:                       None of the specified status flags is set.
 */
en_flag_status_t SPI_GetStatus(const CM_SPI_TypeDef *SPIx, uint32_t u32Flag)
{
    en_flag_status_t enRet = Reset;
    uint32_t u32Status;

    DDL_ASSERT(IS_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_BIT_MASK(u32Flag, SPI_FLAG_ALL));

    u32Status = READ_REG32(SPIx->SR);

    if ((u32Flag & SPI_FLAG_IDLE) != 0UL)
    {
        if ((u32Status & SPI_FLAG_IDLE) == 0U)
        {
            enRet = Set;
        }
    }

    u32Flag &= ((uint32_t)~SPI_FLAG_IDLE);
    if ((u32Status & u32Flag) != 0U)
    {
        enRet = Set;
    }

    return enRet;
}

/**
 * @brief  SPI clear flags.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  u32Flag                SPI flags.
 *                                      This parameter can be values of @ref SPI_Flag.
 *   @arg  SPI_FLAG_OVERLOAD
 *   @arg  SPI_FLAG_MD_FAULT
 *   @arg  SPI_FLAG_PARITY_ERR
 *   @arg  SPI_FLAG_UNDERLOAD
 *   @arg  SPI_FLAG_CLR_ALL
 * @retval None
 */
void SPI_ClearStatus(CM_SPI_TypeDef *SPIx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_BIT_MASK(u32Flag, SPI_FLAG_CLR_ALL));

    CLEAR_REG32_BIT(SPIx->SR, u32Flag);
}

/**
 * @brief  SPI specifies loopback mode.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  u32Mode                SPI loopback mode.
 *                                      This parameter can be a value of @ref SPI_Loopback_Mode
 *   @arg  SPI_LOOPBACK_INVD:           Loopback mode is invalid. Normal mode.
 *   @arg  SPI_LOOPBACK_REVERSE:        MISO data is the reverse of the data output by MOSI.
 *   @arg  SPI_LOOPBACK_NORMAL:         MISO data is the data output by MOSI.
 * @retval None
 */
void SPI_SetLoopbackMode(CM_SPI_TypeDef *SPIx, uint32_t u32Mode)
{
    DDL_ASSERT(IS_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_LOOPBACK_MD(u32Mode));

    MODIFY_REG32(SPIx->CR1, SPI_LOOPBACK_MODE_MASK, u32Mode);
}

/**
 * @brief  SPI enable or disable parity check error self diagnosis.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  enNewState             An en_functional_state_t enumeration value.
 *   @arg  Enable:                      Enable parity check error self diagnosis.
 *   @arg  Disable:                     Disable parity check error self diagnosis.
 * @retval None
 */
void SPI_ParitySelfDiagnosisCmd(CM_SPI_TypeDef *SPIx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG32_BIT(SPIx->CR1, SPI_CR1_PATE);
    }
    else
    {
        CLEAR_REG32_BIT(SPIx->CR1, SPI_CR1_PATE);
    }
}

/**
 * @}
 */

/**
 * @addtogroup SPI_Local_Functions SPI Local Functions
 * @{
 */

/**
 * @brief  SPI transmit and receive data in full duplex mode.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  pvTxBuf                The pointer to the buffer which contains the data to be sent.
 * @param  [out] pvRxBuf                The pointer to the buffer which the received data will be stored.
 * @param  [in]  u32Len                 The length of the data in byte or half word.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred
 *   @arg  ErrorTimeout:                SPI transmit and receive timeout.
 */
static en_result_t SPI_TxRx(CM_SPI_TypeDef *SPIx, const void *pvTxBuf, void *pvRxBuf, \
                            uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t u32Tmp;
    uint32_t u32DataWidth;
    uint32_t u32Count = 0U;
    en_result_t enRet = Ok;

    u32DataWidth = READ_REG32_BIT(SPIx->CFG2, SPI_DATA_WIDTH_16BIT);

    while (u32Count < u32Len)
    {
        if (pvTxBuf != NULL)
        {
            if (u32DataWidth == SPI_DATA_WIDTH_16BIT)
            {
                WRITE_REG32(SPIx->DR, ((const uint16_t *)pvTxBuf)[u32Count]);
            }
            else
            {
                WRITE_REG32(SPIx->DR, ((const uint8_t *)pvTxBuf)[u32Count]);
            }
        }
        else
        {
            WRITE_REG32(SPIx->DR, 0xFFFFU);
        }

        /* Wait TX buffer empty. */
        enRet = SPI_WaitStatus(SPIx, SPI_FLAG_TX_EMPTY, SPI_FLAG_TX_EMPTY, u32Timeout);
        if (enRet == Ok)
        {
            /* Check RX buffer. */
            enRet = SPI_WaitStatus(SPIx, SPI_FLAG_RX_FULL, SPI_FLAG_RX_FULL, u32Timeout);
            if (enRet == Ok)
            {
                /* Read RX data. */
                u32Tmp = READ_REG32(SPIx->DR);
                if (pvRxBuf != NULL)
                {
                    if (u32DataWidth == SPI_DATA_WIDTH_16BIT)
                    {
                        ((uint16_t *)pvRxBuf)[u32Count] = (uint16_t)u32Tmp;
                    }
                    else
                    {
                        ((uint8_t *)pvRxBuf)[u32Count] = (uint8_t)u32Tmp;
                    }
                }

                u32Count++;
            }
        }

        if (enRet != Ok)
        {
            break;
        }
    }

    if (enRet == Ok)
    {
        enRet = SPI_WaitStatus(SPIx, SPI_FLAG_IDLE, 0UL, u32Timeout);
    }

    return enRet;
}

/**
 * @brief  SPI send data only.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  pvBuf                  The pointer to the buffer which contains the data to be sent.
 * @param  [in]  u32Len                 The length of the data in byte or half word.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                SPI transmit timeout.
 */
static en_result_t SPI_Tx(CM_SPI_TypeDef *SPIx, const void *pvBuf, \
                          uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t u32Count = 0UL;
    uint32_t u32DataWidth;
    en_result_t enRet = Ok;

    u32DataWidth = READ_REG32_BIT(SPIx->CFG2, SPI_DATA_WIDTH_16BIT);

    while (u32Count < u32Len)
    {
        if (u32DataWidth == SPI_DATA_WIDTH_16BIT)
        {
            WRITE_REG32(SPIx->DR, ((const uint16_t *)pvBuf)[u32Count]);
        }
        else
        {
            WRITE_REG32(SPIx->DR, ((const uint8_t *)pvBuf)[u32Count]);
        }

        enRet = SPI_WaitStatus(SPIx, SPI_FLAG_TX_EMPTY, SPI_FLAG_TX_EMPTY, u32Timeout);
        if (enRet != Ok)
        {
            break;
        }

        u32Count++;
    }

    if (enRet == Ok)
    {
        enRet = SPI_WaitStatus(SPIx, SPI_FLAG_IDLE, 0UL, u32Timeout);
    }

    return enRet;
}

/**
 * @brief  SPI check status.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  u32FlagMask            Bit mask of status flag.
 * @param  [in]  u32Value               Valid value of the status.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Check status timeout.
 */
static en_result_t SPI_WaitStatus(const CM_SPI_TypeDef *SPIx, uint32_t u32FlagMask, \
                                  uint32_t u32Value, uint32_t u32Timeout)
{
    en_result_t enRet = Ok;

    while (READ_REG32_BIT(SPIx->SR, u32FlagMask) != u32Value)
    {
        if (u32Timeout == 0UL)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Timeout--;
    }

    return enRet;
}

/**
 * @}
 */

#endif /* DDL_SPI_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
