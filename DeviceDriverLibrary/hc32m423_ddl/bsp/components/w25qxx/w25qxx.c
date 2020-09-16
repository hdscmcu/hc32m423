/**
 *******************************************************************************
 * @file  w25qxx.c
 * @brief This midware file provides firmware functions to W25QXX group spi flash.
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
#include "w25qxx.h"
#include "ev_hc32m423_lqfp64_w25qxx.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/** @defgroup W25QXX Flash Driver for W25QXX
  * @{
  */

#if (BSP_W25QXX_ENABLE == BSP_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup W25QXX_Local_Macros W25QXX Local Macros
 * @{
 */

#define W25Q_STATUS_BUSY            ((uint8_t)(1UL << 0U))

#define LOAD_CMD(a, cmd, addr)      do {                                    \
                                        (a)[0U] = (cmd);                    \
                                        (a)[1U] = (uint8_t)((addr) >> 16U); \
                                        (a)[2U] = (uint8_t)((addr) >> 8U);  \
                                        (a)[3U] = (uint8_t)(addr);          \
                                    } while (0U)

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
 * @defgroup W25QXX_Local_Functions W25QXX Local Functions
 * @{
 */
static void W25QXX_WriteReg(uint8_t u8Instr,              \
                            const uint8_t au8InstrData[], \
                            uint32_t u32InstrDataLen);
static void W25QXX_ReadReg(uint8_t u8Instr,               \
                           const uint8_t au8InstrData[],  \
                           uint32_t u32InstrDataLen,      \
                           uint8_t au8RegData[],          \
                           uint32_t u32RegDataLen);

static void W25QXX_WT(uint8_t u8Instr, uint32_t u32Addr, \
                      const uint8_t au8Data[], uint32_t u32DataLen);
static void W25QXX_RD(uint8_t u8Instr, uint32_t u32Addr, \
                      uint8_t au8Data[], uint32_t u32DataLen);

static void W25QXX_WriteEnable(void);
static en_result_t W25QXX_WaitProgressDone(uint32_t u32Timeout);

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
 * @defgroup W25QXX_Global_Functions W25QXX Global Functions
 * @{
 */

/**
 * @brief  Initializes W25QXX.
 * @param  None
 * @retval None
 */
void W25QXX_Init(void)
{
    BSP_W25Q_SPI_Init();
}

/**
 * @brief  Read ID.
 * @param  [in]  u8Instr                Instruction for reading ID.
 * @param  [in]  u32DummyLen            Number of dummy byte follow behind instruction.
 * @param  [out] au8ID                  An uint8_t type array which is used to store the ID.
 * @param  [in]  u32IdLen               Number of ID byte.
 * @retval None.
 */
void W25QXX_ReadID(uint8_t u8Instr, uint32_t u32DummyLen, \
                   uint8_t au8ID[], uint32_t u32IdLen)
{
    const uint8_t au8Dummy[8U] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
    W25QXX_ReadReg(u8Instr, au8Dummy, u32DummyLen, au8ID, u32IdLen);
}

/**
 * @brief  W25QXX read status register.
 * @param  [in]  u8Instr                Instruction for reading status register.
 * @retval Value of status register.
 */
uint8_t W25QXX_ReadStatus(uint8_t u8Instr)
{
    uint8_t u8Ret = 0xFFU;
    W25QXX_ReadReg(u8Instr, NULL, 0U, &u8Ret, 1U);
    return u8Ret;
}

/**
 * @brief  W25QXX write status register.
 * @param  [in]  u8Instr                Instruction for writting status register.
 * @param  [in]  u8Status               Specified status.
 * @retval None
 */
void W25QXX_WriteStatus(uint8_t u8Instr, uint8_t u8Status)
{
    W25QXX_WriteReg(u8Instr, &u8Status, 1U);
}

/**
 * @brief  W25QXX power down.
 * @param  None
 * @retval None
 */
void W25QXX_PowerDown(void)
{
    W25QXX_WriteReg(W25Q_POWER_DOWN, NULL, 0U);
    W25QXX_DELAY_MS(1U);
}

/**
 * @brief  W25QXX release power down.
 * @param  None
 * @retval None
 */
void W25QXX_ReleasePowerDown(void)
{
    W25QXX_WriteReg(W25Q_RELEASE_POWER_DOWN, NULL, 0U);
    W25QXX_DELAY_MS(1U);
}

/**
 * @brief  W25QXX chip ease.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Wait progress done timeout.
 */
en_result_t W25QXX_EraseChip(uint32_t u32Timeout)
{
    W25QXX_WriteEnable();
    W25QXX_WriteReg(W25Q_CHIP_ERASE, NULL, 0U);
    return W25QXX_WaitProgressDone(u32Timeout);
}

/**
 * @brief  W25QXX sector ease.
 * @param  [in]  u32SectorAddr          The address of the specified sector.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Wait progress done timeout.
 */
en_result_t W25QXX_EraseSector(uint32_t u32SectorAddr, uint32_t u32Timeout)
{
    W25QXX_WriteEnable();
    W25QXX_WT(W25Q_SECTOR_ERASE, u32SectorAddr, NULL, 0U);
    return W25QXX_WaitProgressDone(u32Timeout);
}

/**
 * @brief  W25QXX block ease.
 * @param  [in]  u8Instr                Instruction for erasing block.
 * @param  [in]  u32BlockAddr           The address of the specified block.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Wait progress done timeout.
 */
en_result_t W25QXX_EraseBlock(uint8_t u8Instr, uint32_t u32BlockAddr, uint32_t u32Timeout)
{
    W25QXX_WriteEnable();
    W25QXX_WT(u8Instr, u32BlockAddr, NULL, 0U);
    return W25QXX_WaitProgressDone(u32Timeout);
}

/**
 * @brief  W25Q64 write data.
 * @param  [in]  u32Addr                Target address.
 * @param  [in]  au8Buf                 Source data buffer.
 * @param  [in]  u32Len                 Number of byte to be written.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value.
 *   @arg  ErrorInvalidParameter:       au8WriteBuf == NULL.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Wait progress done timeout.
 */
en_result_t W25QXX_WriteData(uint32_t u32Addr, const uint8_t au8Buf[], \
                             uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t u32TempSize;
    uint32_t u32AddrOfst = 0U;
    en_result_t enRet = ErrorInvalidParameter;

    if (au8Buf != NULL)
    {
        while (u32Len != 0U)
        {
            if (u32Len >= W25Q_PAGE_SIZE)
            {
                u32TempSize = W25Q_PAGE_SIZE;
            }
            else
            {
                u32TempSize = u32Len;
            }

            W25QXX_WriteEnable();
            W25QXX_WT(W25Q_PAGE_PROGRAM, u32Addr, \
                      (const uint8_t *)&au8Buf[u32AddrOfst], u32TempSize);
            enRet = W25QXX_WaitProgressDone(u32Timeout);
            if (enRet != Ok)
            {
                break;
            }
            u32Len -= u32TempSize;
            u32AddrOfst += u32TempSize;
            u32Addr += u32TempSize;
        }
    }

    return enRet;
}

/**
 * @brief  W25QXX read data.
 * @param  [in]  u32Addr                The start address of the data to be read.
 * @param  [out] au8Buf                 The pointer to the buffer contains the data to be stored.
 * @param  [in]  u32Len                 Buffer size in bytes.
 * @retval None
 */
void W25QXX_ReadData(uint32_t u32Addr, uint8_t au8Buf[], uint32_t u32Len)
{
    W25QXX_RD(W25Q_READ_DATA, u32Addr, au8Buf, u32Len);
}

/**
 * @}
 */

/**
 * @addtogroup W25QXX_Local_Functions W25QXX Local Functions
 * @{
 */

/**
 * @brief  W25QXX write register.
 * @param  [in]  u8Instr                Instruction of W25QXX.
 * @param  [in]  au8InstrData           Pointer to a buffer that contains the data following the instruction.
 * @param  [in]  u32InstrDataLen     The length of the instruction data in bytes.
 * @retval None
 */
static void W25QXX_WriteReg(uint8_t u8Instr,              \
                            const uint8_t au8InstrData[], \
                            uint32_t u32InstrDataLen)
{
    W25Q_CS_ACTIVE();
    (void)BSP_W25Q_SPI_Trans(&u8Instr, 1U);
    (void)BSP_W25Q_SPI_Trans(au8InstrData, u32InstrDataLen);
    W25Q_CS_INACTIVE();
}

/**
 * @brief  W25QXX read register.
 * @param  [in]  u8Instr                Instruction of W25QXX.
 * @param  [in]  au8InstrData           Pointer to a buffer that contains the data following the instruction.
 * @param  [in]  u32InstrDataLen        The length of the instruction data in bytes.
 * @param  [out] au8RegData             Data of the register.
 * @param  [in]  u32RegDataLen          The length of the register data.
 * @retval None
 */
static void W25QXX_ReadReg(uint8_t u8Instr,              \
                           const uint8_t au8InstrData[], \
                           uint32_t u32InstrDataLen,     \
                           uint8_t au8RegData[],         \
                           uint32_t u32RegDataLen)
{
    W25Q_CS_ACTIVE();
    (void)BSP_W25Q_SPI_Trans(&u8Instr, 1U);
    (void)BSP_W25Q_SPI_Trans(au8InstrData, u32InstrDataLen);
    (void)BSP_W25Q_SPI_Receive(au8RegData, u32RegDataLen);
    W25Q_CS_INACTIVE();
}

/**
 * @brief  W25QXX write data.
 * @param  [in]  u8Instr                Instruction of W25QXX.
 * @param  [in]  u32Addr                The start address of the data to be written.
 * @param  [in]  au8Data                The data to be written.
 * @param  [in]  u32DataLen             The length of the data in bytes.
 * @retval None
 */
static void W25QXX_WT(uint8_t u8Instr, uint32_t u32Addr, \
                      const uint8_t au8Data[], uint32_t u32DataLen)
{
    uint8_t au8Cmd[4U];

    LOAD_CMD(au8Cmd, u8Instr, u32Addr);

    W25Q_CS_ACTIVE();
    (void)BSP_W25Q_SPI_Trans(au8Cmd, 4U);
    (void)BSP_W25Q_SPI_Trans(au8Data, u32DataLen);
    W25Q_CS_INACTIVE();
}

/**
 * @brief  W25QXX read data.
 * @param  [in]  u8Instr                Instruction of W25QXX.
 * @param  [in]  u32Addr                The start address of the data to be written.
 * @param  [out] au8Data                The data to be stored.
 * @param  [in]  u32DataLen             The length of the data in bytes.
 * @retval None
 */
static void W25QXX_RD(uint8_t u8Instr, uint32_t u32Addr, \
                      uint8_t au8Data[], uint32_t u32DataLen)
{
    uint8_t au8Cmd[4U];

    LOAD_CMD(au8Cmd, u8Instr, u32Addr);

    W25Q_CS_ACTIVE();
    (void)BSP_W25Q_SPI_Trans(au8Cmd, 4U);
    (void)BSP_W25Q_SPI_Receive(au8Data, u32DataLen);
    W25Q_CS_INACTIVE();
}

/**
 * @brief  W25QXX Write Enable.
 * @param  None
 * @retval None
 */
static void W25QXX_WriteEnable(void)
{
    W25QXX_WriteReg(W25Q_WRITE_ENABLE, NULL, 0U);
}

/**
 * @brief  Wait while W25QXX is busy.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Wait progress done timeout.
 */
static en_result_t W25QXX_WaitProgressDone(uint32_t u32Timeout)
{
    uint8_t u8Status;
    uint8_t u8Instr   = W25Q_READ_STATUS_REG1;
    en_result_t enRet = ErrorTimeout;

    W25Q_CS_ACTIVE();
    (void)BSP_W25Q_SPI_Trans(&u8Instr, 1U);
    while (u32Timeout != 0U)
    {
        (void)BSP_W25Q_SPI_Receive(&u8Status, 1U);
        if ((u8Status & W25Q_STATUS_BUSY) == 0U)
        {
            enRet = Ok;
            break;
        }
        u32Timeout--;
    }
    W25Q_CS_INACTIVE();

    return enRet;
}

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

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
