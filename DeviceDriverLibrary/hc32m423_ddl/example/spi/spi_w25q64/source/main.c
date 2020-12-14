/**
 *******************************************************************************
 * @file  spi/spi_w25q64/source/main.c
 * @brief Main program for read and write W25Q64 via SPI.
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
#include "w25qxx.h"
/**
 * @addtogroup HC32M423_DDL_Examples
 * @{
 */

/**
 * @addtogroup SPI_W25Q64
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define APP_W25Q64_ADDR             (4096UL * 0UL)
#define APP_BUF_SIZE                (512UL)

#define APP_TIMEOUT_VALUE           (100000UL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);

static void AppLoadData(void);
static en_result_t AppProgramVerify(void);
static en_result_t AppEraseVerify(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t m_au8WriteBuffer[APP_BUF_SIZE];
static uint8_t m_au8ReadBuffer[APP_BUF_SIZE];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of spi_w25q64 project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* MCU Peripheral registers write unprotected. */
    Peripheral_WE();
    /* Configure the system clock to PLLH@80MHz. */
    BSP_CLK_Init();
    /* W25Q64 initialization. */
    W25QXX_Init();
    /* LED initialization. */
    BSP_LED_Init();
    /* MCU Peripheral registers write protected. */
    Peripheral_WP();

    /***************** Configuration end, application start **************/
    /* Read JEDEC ID: 0xEF4017 */
    W25QXX_ReadID(W25Q_JEDEC_ID, 0U, m_au8ReadBuffer, 3U);
    BSP_LED_On(LED_BLUE);
    for (;;)
    {
        (void)W25QXX_EraseSector(APP_W25Q64_ADDR, APP_TIMEOUT_VALUE);
        W25QXX_ReadData(APP_W25Q64_ADDR, m_au8ReadBuffer, APP_BUF_SIZE);
        if (AppEraseVerify() != Ok)
        {
            /* Erase verification error. */
            BSP_LED_On(LED_RED);
            BSP_LED_Off(LED_BLUE);
            while (1U);
        }
        AppLoadData();
        (void)W25QXX_WriteData(APP_W25Q64_ADDR, m_au8WriteBuffer, \
                               APP_BUF_SIZE, APP_TIMEOUT_VALUE);
        W25QXX_ReadData(APP_W25Q64_ADDR, m_au8ReadBuffer, APP_BUF_SIZE);
        if (AppProgramVerify() != Ok)
        {
            /* Program verification error. */
            BSP_LED_On(LED_RED);
            BSP_LED_Off(LED_BLUE);
            while (1U);
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
    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
    /* Unlock all EFM registers */
    EFM_Unlock();
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
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Load data for test.
 * @param  None
 * @retval None
 */
static void AppLoadData(void)
{
    uint32_t i;
    static uint32_t u32Count = 0UL;
    for (i=0UL; i<APP_BUF_SIZE; i++)
    {
        m_au8WriteBuffer[i] = (uint8_t)(u32Count + i);
    }
    u32Count++;
}

/**
 * @brief  Program verification for test.
 * @param  None
 * @retval None
 */
static en_result_t AppProgramVerify(void)
{
    uint32_t i;
    en_result_t enRet = Ok;

    for (i=0UL; i<APP_BUF_SIZE; i++)
    {
        if (m_au8ReadBuffer[i] != m_au8WriteBuffer[i])
        {
            enRet = Error;
            break;
        }
    }

    return enRet;
}

/**
 * @brief  Erase verification for test.
 * @param  None
 * @retval None
 */
static en_result_t AppEraseVerify(void)
{
    uint32_t i;
    en_result_t enRet = Ok;

    for (i=0UL; i<APP_BUF_SIZE; i++)
    {
        if (m_au8ReadBuffer[i] != 0xFFU)
        {
            enRet = Error;
            break;
        }
    }

    return enRet;
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
