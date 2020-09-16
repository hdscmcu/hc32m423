/**
 *******************************************************************************
 * @file  hc32m423_crc.c
 * @brief This file provides firmware functions to manage the Cyclic Redundancy
 *        Check(CRC).
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
#include "hc32m423_crc.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CRC CRC
 * @brief Cyclic Redundancy Check Driver Library
 * @{
 */

#if (DDL_CRC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CRC_Local_Macros CRC Local Macros
 * @{
 */

/**
 * @defgroup CRC_Check_Parameters_Validity CRC check parameters validity
 * @{
 */
/*! Parameter validity check for CRC protocol. */
#define IS_CRC_PROTOCOL(x)                                                     \
(   ((x) == CRC_CRC16)                      ||                                 \
    ((x) == CRC_CRC32))

/*! Parameter validity check for CRC data width. */
#define IS_CRC_DATA_WIDTH(x)                                                   \
(   ((x) == CRC_DATA_WIDTH_8BIT)            ||                                 \
    ((x) == CRC_DATA_WIDTH_16BIT)           ||                                 \
    ((x) == CRC_DATA_WIDTH_32BIT))
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
 * @defgroup CRC_Local_Functions CRC Local Functions
 * @{
 */
static void CRC_8BitWrite(const uint8_t au8Data[], uint32_t u32Len);
static void CRC_16BitWrite(const uint16_t au16Data[], uint32_t u32Len);
static void CRC_32BitWrite(const uint32_t au32Data[], uint32_t u32Len);

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
 * @defgroup CRC_Global_Functions CRC Global Functions
 * @{
 */

/**
 * @brief  CRC16 calculation.
 * @param  [in] u32CrcProtocol          CRC protocol control bit.
 *                                      This parameter can be a value of @ref CRC_Protocol_Control_Bit
 * @param  [in] pvData                  Pointer to the buffer containing the data to be computed.
 * @param  [in] u32InitValue            Initialize the CRC calculation.
 * @param  [in] u32Len                  The length(counted in bytes or half word or word, depending on
 *                                      the bit width) of the data to be computed.
 * @param  [in] u8DataWidth             Bit width of the data.
 *   @arg  CRC_DATA_WIDTH_8BIT:         8  Bit.
 *   @arg  CRC_DATA_WIDTH_16BIT:        16 Bit.
 *   @arg  CRC_DATA_WIDTH_32BIT:        32 Bit.
 * @retval CRC checksum.
 */
uint32_t CRC_Calculate(uint32_t u32CrcProtocol,
                       const void *pvData,
                       uint32_t u32InitValue,
                       uint32_t u32Len,
                       uint8_t u8DataWidth)
{
    uint32_t u32CheckSum = 0UL;

    if ((pvData != NULL) && (u32Len != 0U))
    {
        DDL_ASSERT(IS_CRC_PROTOCOL(u32CrcProtocol));
        DDL_ASSERT(IS_CRC_DATA_WIDTH(u8DataWidth));
        /* Set operation mode (CRC16 or CRC32) */
        WRITE_REG32(CM_CRC->CR, u32CrcProtocol);
        /* Set initial value */
        if (u32CrcProtocol == CRC_CRC32)
        {
            WRITE_REG32(CM_CRC->RESLT, u32InitValue);
        }
        else
        {
            WRITE_REG16(CM_CRC->RESLT, u32InitValue);
        }
        /* Write data */
        if (u8DataWidth == CRC_DATA_WIDTH_8BIT)
        {
            CRC_8BitWrite(pvData, u32Len);
        }
        else if (u8DataWidth == CRC_DATA_WIDTH_16BIT)
        {
            CRC_16BitWrite(pvData, u32Len);
        }
        else
        {
            CRC_32BitWrite(pvData, u32Len);
        }
        /* Get checksum */
        if (u32CrcProtocol == CRC_CRC32)
        {
            u32CheckSum = READ_REG32(CM_CRC->RESLT);
        }
        else
        {
            u32CheckSum = READ_REG16(CM_CRC->RESLT);
        }
    }

    return u32CheckSum;
}

/**
 * @brief  CRC check.
 * @param  [in] u32CrcProtocol        CRC protocol control bit.
 *                                    This parameter can be a value of @ref CRC_Protocol_Control_Bit
 * @param  [in] u32CheckSum           The checksum of the data pointed by pointer pvData.
 * @param  [in] pvData                Pointer to the buffer containing the data to be checked.
 * @param  [in] u32InitValue          Initialize the CRC calculation.
 * @param  [in] u32Len                The length(counted in bytes or half word or word, depending on
 *                                    the bit width) of the data to be computed.
 * @param  [in] u8DataWidth           Bit width of the data.
 *   @arg  CRC_DATA_WIDTH_8BIT:       8  Bit.
 *   @arg  CRC_DATA_WIDTH_16BIT:      16 Bit.
 *   @arg  CRC_DATA_WIDTH_32BIT:      32 Bit.
 * @retval A en_flag_status_t value.
 *   @arg  Set:                     CRC checks success.
 *   @arg  Reset:                   CRC checks failed.
 */
en_flag_status_t CRC_Check(uint32_t u32CrcProtocol,
                           uint32_t u32CheckSum,
                           const void *pvData,
                           uint32_t u32InitValue,
                           uint32_t u32Len,
                           uint8_t u8DataWidth)
{
    en_flag_status_t enFlag = Reset;
    uint32_t u32DataAddr = (uint32_t)&CM_CRC->DAT0;
    if ((pvData != NULL) && (u32Len != 0U))
    {
        DDL_ASSERT(IS_CRC_PROTOCOL(u32CrcProtocol));
        DDL_ASSERT(IS_CRC_DATA_WIDTH(u8DataWidth));
        /* Set operation mode (CRC16 or CRC32) */
        WRITE_REG32(CM_CRC->CR, u32CrcProtocol);
        /* Set initial value */
        if (u32CrcProtocol == CRC_CRC32)
        {
            WRITE_REG32(CM_CRC->RESLT, u32InitValue);
        }
        else
        {
            WRITE_REG16(CM_CRC->RESLT, u32InitValue);
        }
        /* Write data */
        if (u8DataWidth == CRC_DATA_WIDTH_8BIT)
        {
            CRC_8BitWrite(pvData, u32Len);
        }
        else if (u8DataWidth == CRC_DATA_WIDTH_16BIT)
        {
            CRC_16BitWrite(pvData, u32Len);
        }
        else
        {
            CRC_32BitWrite(pvData, u32Len);
        }
        /* Write checksum */
        if (u32CrcProtocol == CRC_CRC32)
        {
            RW_MEM32(u32DataAddr) = u32CheckSum;
        }
        else
        {
            RW_MEM16(u32DataAddr) = (uint16_t)u32CheckSum;
        }
        /* Get flag */
        if (READ_REG32_BIT(CM_CRC->CR, CRC_CR_FLAG) != 0UL)
        {
            enFlag = Set;
        }
    }
    return enFlag;
}

/**
 * @}
 */

/**
 * @addtogroup CRC_Local_Functions CRC Local Functions
 * @{
 */

/**
 * @brief  Write CRC data register in bytes.
 * @param  [in] au8Data          The buffer for writing.
 * @param  [in] u32Len           The length of data the in bytes.
 * @retval None
 */
static void CRC_8BitWrite(const uint8_t au8Data[], uint32_t u32Len)
{
    uint32_t i;
    const uint32_t u32DataAddr = (uint32_t)(&CM_CRC->DAT0);
    for (i = 0UL; i < u32Len; i++)
    {
        RW_MEM8(u32DataAddr) = au8Data[i];
    }
}

/**
 * @brief  Write CRC data register in half words.
 * @param  [in] au16Data         The buffer for writing.
 * @param  [in] u32Len           The length of the data in half words.
 * @retval None
 */
static void CRC_16BitWrite(const uint16_t au16Data[], uint32_t u32Len)
{
    uint32_t i;
    const uint32_t u32DataAddr = (uint32_t)(&CM_CRC->DAT0);
    for (i = 0UL; i < u32Len; i++)
    {
        RW_MEM16(u32DataAddr) = au16Data[i];
    }
}

/**
 * @brief  Write CRC data register in words.
 * @param  [in] au32Data         The buffer for writing.
 * @param  [in] u32Len           The length of the data in words.
 * @retval None
 */
static void CRC_32BitWrite(const uint32_t au32Data[], uint32_t u32Len)
{
    uint32_t i;
    const uint32_t u32DataAddr = (uint32_t)(&CM_CRC->DAT0);
    for (i = 0UL; i < u32Len; i++)
    {
        RW_MEM32(u32DataAddr) = au32Data[i];
    }
}
/**
 * @}
 */

#endif /* DDL_CRC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
