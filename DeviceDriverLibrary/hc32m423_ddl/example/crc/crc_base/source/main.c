/**
 *******************************************************************************
 * @file  crc/crc_base/source/main.c
 * @brief Main program of CRC base for the Device Driver Library.
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
 * @addtogroup CRC_Base
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CRC16_InitValue                 (0xFFFFU)
#define CRC32_InitValue                 (0xFFFFFFFFUL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

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
    //GPIO_Unlock();
    /* Unlock CLK registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Unlock(PWC_UNLOCK_CODE_0);
    /* Unlock all EFM registers */
    //EFM_Unlock();
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
    //GPIO_Lock();
    /* Lock CLK registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Lock(PWC_UNLOCK_CODE_0);
    /* Lock all EFM registers */
    //EFM_Lock();
}
/**
 * @brief  Main function of CRC base project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    const uint8_t au8SrcData[1U]  = {0x12};
    const uint16_t au16SrcData[2U] = {0x2020,0x0527};
    const uint32_t au32SrcData[3U] = {0x20200527UL,0x12345678UL,0x1111FFFFUL};
    uint8_t  au8CheckData[1U];
    uint16_t au16CheckData[1U];
    uint32_t au32CheckData[1U];
    uint16_t u16Checksum;
    uint32_t u32Checksum;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();
    /* Enable CRC peripheral clock */
    CLK_FcgPeriphClockCmd(CLK_FCG_CRC, Enable);
    /* MCU Peripheral registers write protected. */
    Peripheral_WP();
    /***************** Configuration end, application start **************/
    for (;;)
    {
        /* Calculates byte data's CRC16 checksum and CRC32 checksum. */
        (void)CRC_Calculate(CRC_CRC16, au8SrcData, CRC16_InitValue, sizeof(au8SrcData), CRC_DATA_WIDTH_8BIT);
        (void)CRC_Calculate(CRC_CRC32, au8SrcData, CRC32_InitValue, sizeof(au8SrcData), CRC_DATA_WIDTH_8BIT);

        /* Calculates half word data's CRC16 checksum and CRC32 checksum. */
        (void)CRC_Calculate(CRC_CRC16, au16SrcData, CRC16_InitValue, (sizeof(au16SrcData))/2U, CRC_DATA_WIDTH_16BIT);
        (void)CRC_Calculate(CRC_CRC32, au16SrcData, CRC32_InitValue, (sizeof(au16SrcData))/2U, CRC_DATA_WIDTH_16BIT);

        /* Calculates word data's CRC16 checksum and CRC32 checksum. */
        (void)CRC_Calculate(CRC_CRC16, au32SrcData, CRC16_InitValue, (sizeof(au32SrcData))/4U, CRC_DATA_WIDTH_32BIT);
        (void)CRC_Calculate(CRC_CRC32, au32SrcData, CRC32_InitValue, (sizeof(au32SrcData))/4U, CRC_DATA_WIDTH_32BIT);

        /* Checks byte data's CRC16 checksum and CRC32 checksum. */
        au8CheckData[0U] = 0xC8U;
        u16Checksum = 0xBA3CU;
        (void)CRC_Check(CRC_CRC16, (uint32_t)u16Checksum, au8CheckData, CRC16_InitValue, sizeof(au8CheckData), CRC_DATA_WIDTH_8BIT);
        u32Checksum = 0x47BDA50FUL;
        (void)CRC_Check(CRC_CRC32, u32Checksum, au8CheckData, CRC32_InitValue, sizeof(au8CheckData), CRC_DATA_WIDTH_8BIT);

        /* Checks half word data's CRC16 checksum and CRC32 checksum. */
        au16CheckData[0U] = 0x1234U;
        u16Checksum = 0xED16U;
        (void)CRC_Check(CRC_CRC16, (uint32_t)u16Checksum, au16CheckData, CRC16_InitValue, (sizeof(au16CheckData))/2U, CRC_DATA_WIDTH_16BIT);
        u32Checksum = 0x094A9040UL;
        (void)CRC_Check(CRC_CRC32, u32Checksum, au16CheckData, CRC32_InitValue, (sizeof(au16CheckData))/2U, CRC_DATA_WIDTH_16BIT);

        /* Checks word data's CRC16 checksum and CRC32 checksum. */
        au32CheckData[0U] = 0x12345678UL;
        u16Checksum = 0xF428U;
        (void)CRC_Check(CRC_CRC16, (uint32_t)u16Checksum, au32CheckData, CRC16_InitValue, (sizeof(au32CheckData))/4U, CRC_DATA_WIDTH_32BIT);
        u32Checksum = 0xAF6D87D2UL;
        (void)CRC_Check(CRC_CRC32, u32Checksum, au32CheckData, CRC32_InitValue, (sizeof(au32CheckData))/4U, CRC_DATA_WIDTH_32BIT);
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
