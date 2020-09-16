/**
 *******************************************************************************
 * @file  w25qxx.h
 * @brief This file provides firmware functions to W25QXX group spi flash.
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
#ifndef __W25QXX_H__
#define __W25QXX_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/** @addtogroup W25QXX
  * @{
  */

#if (BSP_W25QXX_ENABLE == BSP_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup W25QXX_Global_Macros W25QXX Global Macros
 * @{
 */

/**
 * @defgroup W25QXX_ID W25QXX ID
 * @brief Supported W25Qxx series chips: W25Q64
 * @{
 */
#define W25Q64                              (0xEF16U)
/**
 * @}
 */

/**
 * @defgroup W25QXX_Instruction W25QXX Instruction
 * @{
 */
#define W25Q_WRITE_ENABLE                   (0x06U)
#define W25Q_VOLATILE_SR_WRITE_ENABLE       (0x50U)
#define W25Q_WRITE_DISABLE                  (0x04U)
#define W25Q_READ_STATUS_REG1               (0x05U)
#define W25Q_READ_STATUS_REG2               (0x35U)
#define W25Q_READ_STATUS_REG3               (0x15U)
#define W25Q_WRITE_STATUS_REG1              (0x01U)
#define W25Q_WRITE_STATUS_REG2              (0x31U)
#define W25Q_WRITE_STATUS_REG3              (0x11U)
#define W25Q_PAGE_PROGRAM                   (0x02U)
#define W25Q_SECTOR_ERASE                   (0x20U)
#define W25Q_BLOCK_ERASE_32K                (0x52U)
#define W25Q_BLOCK_ERASE_64K                (0xD8U)
#define W25Q_CHIP_ERASE                     (0xC7U)
#define W25Q_ERASE_PROGRAM_SUSPEND          (0x75U)
#define W25Q_ERASE_PROGRAM_RESUME           (0x7AU)
#define W25Q_POWER_DOWN                     (0xB9U)
#define W25Q_READ_DATA                      (0x03U)
#define W25Q_FAST_READ                      (0x0BU)
#define W25Q_DEVICE_ID                      (0xABU)
#define W25Q_RELEASE_POWER_DOWN             (W25Q_DEVICE_ID)
#define W25Q_MANUFACTURER_DEVICE_ID         (0x90U)
#define W25Q_JEDEC_ID                       (0x9FU)
#define W25Q_READ_UNIQUE_ID                 (0x4BU)
#define W25Q_READ_SFDP_REG                  (0x5AU)
#define W25Q_ERASE_SECURITY_REG             (0x44U)
#define W25Q_PROGRAM_SECURITY_REG           (0x42U)
#define W25Q_READ_SECURITY_REG              (0x48U)
#define W25Q_ENABLE_QPI                     (0x38U)
#define W25Q_ENABLE_RESET                   (0x66U)
#define W25Q_RESET                          (0x99U)
/**
 * @}
 */

/**
 * @defgroup W25QXX_Size W25QXX Size
 * @{
 */
#define W25Q_PAGE_SIZE                      (256UL)
#define W25Q_SECTOR_SIZE                    (1024UL * 4UL)
#define W25Q_BLOCK_SIZE                     (1024UL * 64UL)
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
 * @addtogroup W25QXX_Global_Functions W25QXX Global Functions
 * @{
 */

void W25QXX_Init(void);

void W25QXX_ReadID(uint8_t u8Instr, uint32_t u32DummyLen, \
                   uint8_t au8ID[], uint32_t u32IdLen);

uint8_t W25QXX_ReadStatus(uint8_t u8Instr);
void W25QXX_WriteStatus(uint8_t u8Instr, uint8_t u8Status);

void W25QXX_PowerDown(void);
void W25QXX_ReleasePowerDown(void);

en_result_t W25QXX_EraseChip(uint32_t u32Timeout);
en_result_t W25QXX_EraseSector(uint32_t u32SectorAddr, uint32_t u32Timeout);
en_result_t W25QXX_EraseBlock(uint8_t u8Instr, uint32_t u32BlockAddr, uint32_t u32Timeout);

en_result_t W25QXX_WriteData(uint32_t u32Addr, const uint8_t au8Buf[], \
                             uint32_t u32Len, uint32_t u32Timeout);
void W25QXX_ReadData(uint32_t u32Addr, uint8_t au8Buf[], uint32_t u32Len);

/**
 * @}
 */

#endif /* BSP_W25QXX_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __W25QXX_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
