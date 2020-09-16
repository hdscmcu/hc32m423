/**
 *******************************************************************************
 * @file  crc/crc_software/source/main.c
 * @brief Main program of CRC software for the Device Driver Library.
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
 * @addtogroup CRC_Software
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define BYTE_WIDTH1                      (1U)
#define BYTE_WIDTH2                      (2U)
#define BYTE_WIDTH4                      (4U)

#define CRC16_InitVal                 (0xFFFFU)
#define CRC32_InitVal                 (0xFFFFFFFFUL)
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static uint16_t SW_CalculateCRC16(const uint8_t *pu8Data, uint16_t u16InitValue, uint8_t ByteWidth, uint32_t Len);
static uint32_t SW_CalculateCRC32(const uint8_t *pu8Data, uint32_t u32InitValue, uint8_t ByteWidth, uint32_t Len);
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
    GPIO_Unlock();
    /* Unlock PWC registers, @ref PWC_REG_Write_Unlock_Code for details */
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
 * @brief  Main function of CRC software project
 * @param  None
 * @retval None
 */
int32_t main(void)
{
    const uint8_t  au8SrcData [3U] = {0x12U,0x21U,0U};
    const uint16_t au16SrcData[3U] = {0x1234U,0x4321U,0U};
    const uint32_t au32SrcData[3U] = {0x12345678UL,0x87654321UL,0UL};
    uint32_t u16Checksum;
    uint32_t u32Checksum;
    uint32_t u16CRCData;
    uint32_t u32CRCData;
    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();
    /* Led Init */
    BSP_LED_Init();
    /* Turn on LED_G */
    BSP_LED_On(LED_GREEN);
    /* Enable CRC peripheral clock */
    CLK_FcgPeriphClockCmd(CLK_FCG_CRC, Enable);
    /* MCU Peripheral registers write protected. */
    Peripheral_WP();
    /***************** Configuration end, application start **************/
    for (;;)
    {
        /* Calculates byte data's CRC16 checksum and CRC32 checksum. */
        u16CRCData = SW_CalculateCRC16(au8SrcData, CRC16_InitVal, BYTE_WIDTH1, sizeof(au8SrcData));
        u16Checksum  = (uint16_t)CRC_Calculate(CRC_CRC16, au8SrcData, CRC16_InitVal, sizeof(au8SrcData), CRC_DATA_WIDTH_8BIT);
        if (u16CRCData != u16Checksum)
        {
            BSP_LED_Off(LED_GREEN);
            BSP_LED_On(LED_RED);
        }
        u32CRCData = SW_CalculateCRC32(au8SrcData, CRC32_InitVal, BYTE_WIDTH1, sizeof(au8SrcData));
        u32Checksum  = CRC_Calculate(CRC_CRC32, au8SrcData, CRC32_InitVal, sizeof(au8SrcData), CRC_DATA_WIDTH_8BIT);
        if (u32CRCData != u32Checksum)
        {
            BSP_LED_Off(LED_GREEN);
            BSP_LED_On(LED_RED);
        }

        /* Calculates half word data's CRC16 checksum and CRC32 checksum. */
        u16CRCData = SW_CalculateCRC16((const uint8_t *)&au16SrcData[0], CRC16_InitVal, BYTE_WIDTH2, (sizeof(au16SrcData))/2U);
        u16Checksum  = (uint16_t)CRC_Calculate(CRC_CRC16, au16SrcData, CRC16_InitVal, (sizeof(au16SrcData))/2U, CRC_DATA_WIDTH_16BIT);
        if (u16CRCData != u16Checksum)
        {
            BSP_LED_Off(LED_GREEN);
            BSP_LED_On(LED_RED);
        }
        u32CRCData = SW_CalculateCRC32((const uint8_t *)&au16SrcData[0], CRC32_InitVal, BYTE_WIDTH2, (sizeof(au16SrcData))/2U);
        u32Checksum  = CRC_Calculate(CRC_CRC32, au16SrcData, CRC32_InitVal, (sizeof(au16SrcData))/2U, CRC_DATA_WIDTH_16BIT);
        if (u32CRCData != u32Checksum)
        {
            BSP_LED_Off(LED_GREEN);
            BSP_LED_On(LED_RED);
        }

        /* Calculates word data's CRC16 checksum and CRC32 checksum. */
        u16CRCData = SW_CalculateCRC16((const uint8_t *)&au32SrcData[0], CRC16_InitVal, BYTE_WIDTH4, (sizeof(au32SrcData))/4U);
        u16Checksum  = (uint16_t)CRC_Calculate(CRC_CRC16, au32SrcData, CRC16_InitVal, (sizeof(au32SrcData))/4U, CRC_DATA_WIDTH_32BIT);
        if (u16CRCData != u16Checksum)
        {
            BSP_LED_Off(LED_GREEN);
            BSP_LED_On(LED_RED);
        }
        u32CRCData = SW_CalculateCRC32((const uint8_t *)&au32SrcData[0], CRC32_InitVal,BYTE_WIDTH4, (sizeof(au32SrcData))/4U);
        u32Checksum  = CRC_Calculate(CRC_CRC32, au32SrcData, CRC32_InitVal, (sizeof(au32SrcData))/4U, CRC_DATA_WIDTH_32BIT);
        if (u32CRCData != u32Checksum)
        {
            BSP_LED_Off(LED_GREEN);
            BSP_LED_On(LED_RED);
        }
    }
}

/**
 * @brief CRC-16 calculation.
 * @param  [in] pu8Data               Pointer to the buffer containing the data to be computed.
 * @param  [in] u16InitValue          Initialize the CRC calculation.
 * @param  [in] u8ByteWidth           Byte width of the data.
 * @param  [in] u32Len                The length of the data to be computed.
 * @retval crc
 */
uint16_t SW_CalculateCRC16(const uint8_t *pu8Data, uint16_t u16InitValue, uint8_t u8ByteWidth, uint32_t u32Len)
{
    uint8_t i;
    uint8_t j;
    uint16_t crc = u16InitValue; /* Initial value */
    uint32_t u32Temp = (uint32_t)pu8Data;
    while (u32Len > 0UL)
    {
        i = u8ByteWidth;
        while (i > 0U)
        {
            crc ^= *(uint8_t *)u32Temp;
            u32Temp++;
            for (j = 0U; j < 8U; j++)
            {
                if ((crc & 0x1UL) != 0UL)
                {
                    crc >>= 1U;
                    crc ^= 0x8408U; /* 0x8408 = reverse 0x1021 */
                }
                else
                {
                    crc >>= 1U;
                }
            }
            i--;
       }
       u32Len--;
    }
    crc =~crc;
    return crc;
}

/**
 * @brief CRC-32 calculation.
 * @param  [in] pu8Data               Pointer to the buffer containing the data to be computed.
 * @param  [in] u32InitValue          Initialize the CRC calculation.
 * @param  [in] u8ByteWidth           Byte width of the data.
 * @param  [in] u32Len                The length of the data to be computed.
 * @retval crc
 */
uint32_t SW_CalculateCRC32(const uint8_t *pu8Data, uint32_t u32InitValue, uint8_t u8ByteWidth, uint32_t u32Len)
{
    uint8_t i;
    uint8_t j;
    uint32_t crc = u32InitValue;  /* Initial value */
    uint32_t u32Temp = (uint32_t)pu8Data;
    while (u32Len > 0UL)
    {
        i = u8ByteWidth;
        while (i > 0U)
        {
            crc ^= *(uint8_t *)u32Temp;
            u32Temp++;
            for (j = 0U; j < 8U; j++)
            {
                if ((crc & 0x1UL) != 0UL)
                {
                    crc = (crc >> 1U) ^ 0xEDB88320UL; /*0xEDB88320= reverse 0x04C11DB7*/
                }
                else
                {
                    crc = (crc >> 1U);
                }
            }
            i--;
        }
        u32Len--;
    }
    crc =~crc;
    return crc;
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
