/**
 *******************************************************************************
 * @file  hc32m423_spi.h
 * @brief This file contains all the functions prototypes of the SPI driver
 *        library.
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
#ifndef __HC32M423_SPI_H__
#define __HC32M423_SPI_H__

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
 * @addtogroup DDL_SPI
 * @{
 */

#if (DDL_SPI_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Types SPI Global Types
 * @{
 */

/**
 * @brief Structure definition of SPI initialization.
 */
typedef struct
{
    uint32_t u32WireMode;           /*!< SPI wire mode, 3 wire mode or 4 wire mode.
                                         This parameter can be a value of @ref SPI_Wire_Mode */
    uint32_t u32TransMode;          /*!< SPI transfer mode, send only or full duplex.
                                         This parameter can be a value of @ref SPI_Trans_Mode */
    uint32_t u32MasterSlave;        /*!< SPI master/slave mode.
                                         This parameter can be a value of @ref SPI_Master_Slave_Mode */
    uint32_t u32Parity;             /*!< SPI parity check selection.
                                         This parameter can be a value of @ref SPI_Parity_Check */
    uint32_t u32NssActiveLevel;     /*!< SPI NSS pin active level, active low or active high.
                                         This parameter can be a value of @ref SPI_NSS_Active_Level */
    uint32_t u32SpiMode;            /*!< SPI standard mode.
                                         This parameter can be a value of @ref SPI_Standard_Mode */
    uint32_t u32ClockDiv;           /*!< SPI clock divider(baud rate prescaler).
                                         This parameter can be a value of @ref SPI_Clock_Divider */
    uint32_t u32DataWidth;          /*!< SPI data width, 8 bit or 16 bit.
                                         This parameter can be a value of @ref SPI_Data_Width */
    uint32_t u32FirstBit;           /*!< MSB first or LSB first.
                                         This parameter can be a value of @ref SPI_First_Bit */
} stc_spi_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Macros SPI Global Macros
 * @{
 */

/**
 * @defgroup SPI_Wire_Mode SPI Wire Mode
 * @{
 */
#define SPI_4WIRE                   (0UL)
#define SPI_3WIRE                   (SPI_CR1_SPIMDS)
/**
 * @}
 */

/**
 * @defgroup SPI_Trans_Mode SPI Transmission Mode
 * @{
 */
#define SPI_FULL_DUPLEX             (0UL)                   /*!< Full duplex. */
#define SPI_SEND_ONLY               (SPI_CR1_TXMDS)         /*!< Send only. */
/**
 * @}
 */

/**
 * @defgroup SPI_Master_Slave_Mode SPI Master Slave Mode
 * @{
 */
#define SPI_SLAVE                   (0UL)
#define SPI_MASTER                  (SPI_CR1_MSTR)
/**
 * @}
 */

/**
 * @defgroup SPI_Loopback_Mode SPI Loopback Mode
 * @note Loopback mode is mainly used for parity self-diagnosis in 4-wire full-duplex mode.
 * @{
 */
#define SPI_LOOPBACK_INVD           (0UL)                   /*!< Loopback mode is invalid. Normal mode.*/
#define SPI_LOOPBACK_REVERSE        (SPI_CR1_SPLPBK)        /*!< MISO data is the reverse of the data output by MOSI. */
#define SPI_LOOPBACK_NORMAL         (SPI_CR1_SPLPBK2)       /*!< MISO data is the data output by MOSI. */
/**
 * @}
 */

/**
 * @defgroup SPI_Interrupt_Type SPI Interrupt Type
 * @{
 */
#define SPI_INT_ERR                 (SPI_CR1_EIE)           /*!< Including overload, underload and parity error. */
#define SPI_INT_TX_EMPTY            (SPI_CR1_TXIE)
#define SPI_INT_RX_FULL             (SPI_CR1_RXIE)
#define SPI_INT_IDLE                (SPI_CR1_IDIE)
#define SPI_INT_ALL                 (SPI_INT_ERR      | \
                                     SPI_INT_TX_EMPTY | \
                                     SPI_INT_RX_FULL  | \
                                     SPI_INT_IDLE)
/**
 * @}
 */

/**
 * @defgroup SPI_Parity_Check SPI Parity Check
 * @{
 */
#define SPI_PARITY_NONE             (0UL)                   /*!< Parity check invalid. */
#define SPI_PARITY_EVEN             (SPI_CR1_PAE)           /*!< Parity check selection even parity. */
#define SPI_PARITY_ODD              (SPI_CR1_PAE | \
                                     SPI_CR1_PAOE)          /*!< Parity check selection odd parity. */
/**
 * @}
 */

/**
 * @defgroup SPI_NSS_Active_Level SPI NSS Active Level
 * @{
 */
#define SPI_NSS_ACTIVE_LOW          (0UL)                   /*!< NSS pin active low. */
#define SPI_NSS_ACTIVE_HIGH         (SPI_CFG1_SS0PV)        /*!< NSS pin active high. */
/**
 * @}
 */

/**
 * @defgroup SPI_Standard_Mode SPI Standard Mode
 * @{
 */
#define SPI_MD0                     (0UL)
#define SPI_MD1                     (SPI_CFG2_CPHA)
#define SPI_MD2                     (SPI_CFG2_CPOL)
#define SPI_MD3                     (SPI_CFG2_CPOL | \
                                     SPI_CFG2_CPHA)
/**
 * @}
 */

/**
 * @defgroup SPI_Clock_Divider SPI Clock Divider
 * @{
 */
#define SPI_CLK_DIV2                (0UL)                           /*!< SPI baud rate is PCLK1/2. */
#define SPI_CLK_DIV4                (0x1UL << SPI_CFG2_MBR_POS)     /*!< SPI baud rate is PCLK1/4. */
#define SPI_CLK_DIV8                (0x2UL << SPI_CFG2_MBR_POS)     /*!< SPI baud rate is PCLK1/8. */
#define SPI_CLK_DIV16               (0x3UL << SPI_CFG2_MBR_POS)     /*!< SPI baud rate is PCLK1/16. */
#define SPI_CLK_DIV32               (0x4UL << SPI_CFG2_MBR_POS)     /*!< SPI baud rate is PCLK1/32. */
#define SPI_CLK_DIV64               (0x5UL << SPI_CFG2_MBR_POS)     /*!< SPI baud rate is PCLK1/64. */
#define SPI_CLK_DIV128              (0x6UL << SPI_CFG2_MBR_POS)     /*!< SPI baud rate is PCLK1/128. */
#define SPI_CLK_DIV256              (0x7UL << SPI_CFG2_MBR_POS)     /*!< SPI baud rate is PCLK1/256. */
/**
 * @}
 */

/**
 * @defgroup SPI_Data_Width SPI Data Size
 * @{
 */
#define SPI_DATA_WIDTH_8BIT         (0UL)
#define SPI_DATA_WIDTH_16BIT        (SPI_CFG2_DSIZE)
/**
 * @}
 */

/**
 * @defgroup SPI_First_Bit SPI First Bit
 * @{
 */
#define SPI_FIRST_BIT_MSB           (0UL)
#define SPI_FIRST_BIT_LSB           (SPI_CFG2_LSBF)
/**
 * @}
 */

/**
 * @defgroup SPI_Flag SPI Flag
 * @{
 */
#define SPI_FLAG_OVERLOAD           (SPI_SR_OVRERF)
#define SPI_FLAG_IDLE               (SPI_SR_IDLNF)
#define SPI_FLAG_MD_FAULT           (SPI_SR_MODFERF)
#define SPI_FLAG_PARITY_ERR         (SPI_SR_PERF)
#define SPI_FLAG_UNDERLOAD          (SPI_SR_UDRERF)
#define SPI_FLAG_TX_EMPTY           (SPI_SR_TDEF)       /*!< This flag is set when the data in the data register     \
                                                             is copied into the shift register, but the transmission \
                                                             of the data bit may not have been completed. */
#define SPI_FLAG_RX_FULL            (SPI_SR_RDFF)       /*!< When this flag is set, it indicates that a data was received. */

#define SPI_FLAG_ALL                (SPI_FLAG_OVERLOAD   | \
                                     SPI_FLAG_IDLE       | \
                                     SPI_FLAG_MD_FAULT   | \
                                     SPI_FLAG_PARITY_ERR | \
                                     SPI_FLAG_UNDERLOAD  | \
                                     SPI_FLAG_TX_EMPTY   | \
                                     SPI_FLAG_RX_FULL)

#define SPI_FLAG_CLR_ALL            (SPI_FLAG_OVERLOAD   | \
                                     SPI_FLAG_MD_FAULT   | \
                                     SPI_FLAG_PARITY_ERR | \
                                     SPI_FLAG_UNDERLOAD)
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
 * @addtogroup SPI_Global_Functions
 * @{
 */

/**
 * @brief  Read SPI data register.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @retval A 32-bit data of SPI data register.
 */
__STATIC_INLINE uint32_t SPI_ReadData(const CM_SPI_TypeDef *SPIx)
{
    //DDL_ASSERT(IS_SPI_UNIT(SPIx));
    return SPIx->DR;
}

/**
 * @brief  Write SPI data register.
 * @param  [in]  SPIx                   Pointer to SPI instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_SPI:                      SPI unit instance register base.
 * @param  [in]  u32Data                The data will be written to the data register.
 * @retval None.
 */
__STATIC_INLINE void SPI_WriteData(CM_SPI_TypeDef *SPIx, uint32_t u32Data)
{
    //DDL_ASSERT(IS_SPI_UNIT(SPIx));
    WRITE_REG32(SPIx->DR, u32Data);
}

en_result_t SPI_Init(CM_SPI_TypeDef *SPIx, const stc_spi_init_t *pstcSpiInit);
void SPI_DeInit(CM_SPI_TypeDef *SPIx);
en_result_t SPI_StructInit(stc_spi_init_t *pstcSpiInit);

void SPI_IntCmd(CM_SPI_TypeDef *SPIx, uint32_t u32IntType, en_functional_state_t enNewState);
void SPI_Cmd(CM_SPI_TypeDef *SPIx, en_functional_state_t enNewState);

void SPI_ModeFaultDetectCmd(CM_SPI_TypeDef *SPIx, en_functional_state_t enNewState);

en_result_t SPI_Trans(CM_SPI_TypeDef *SPIx, const void *pvBuf, \
                      uint32_t u32Len, uint32_t u32Timeout);
en_result_t SPI_Receive(CM_SPI_TypeDef *SPIx, void *pvBuf, \
                        uint32_t u32Len, uint32_t u32Timeout);
en_result_t SPI_TransReceive(CM_SPI_TypeDef *SPIx, const void *pvTxBuf, void *pvRxBuf, \
                             uint32_t u32Len, uint32_t u32Timeout);

en_flag_status_t SPI_GetStatus(const CM_SPI_TypeDef *SPIx, uint32_t u32Flag);
void SPI_ClearStatus(CM_SPI_TypeDef *SPIx, uint32_t u32Flag);

void SPI_SetLoopbackMode(CM_SPI_TypeDef *SPIx, uint32_t u32Mode);
void SPI_ParitySelfDiagnosisCmd(CM_SPI_TypeDef *SPIx, en_functional_state_t enNewState);

uint32_t SPI_ReadData(const CM_SPI_TypeDef *SPIx);
void SPI_WriteData(CM_SPI_TypeDef *SPIx, uint32_t u32Data);

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

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_SPI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
