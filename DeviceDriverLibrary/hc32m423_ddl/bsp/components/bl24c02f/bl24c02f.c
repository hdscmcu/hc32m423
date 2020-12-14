/**
 *******************************************************************************
 * @file  bl24c02f.c
 * @brief This midware file provides firmware functions to BL24C02F EEPROM.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-15       CDT             First version
   2020-11-16       CDT             Fix bug and optimize code for I2C driver and example
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
#include "bl24c02f.h"
#include "ev_hc32m423_lqfp64_bl24c02f.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/** @defgroup BL24C02F EEPROM Driver for BL24C02F
  * @{
  */

#if (BSP_BL24C02F_ENABLE == BSP_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup BL24C02F_Local_Macros BL24C02F Local Macros
 * @{
 */
#define BL24C02F_ADDR               (0x50U)
#define BL24C02F_PAGE_SIZE          (16U)

#define BL24C02F_MEM_SIZE           (256UL)
#define BL24C02F_WAIT_TIMEOUT       (1000UL)
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
 * @defgroup BL24C02F_Local_Functions BL24C02F Local Functions
 * @{
 */
static en_result_t BL24C02F_I2C_GetStatus(void);
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
 * @defgroup BL24C02F_Global_Functions BL24C02F Global Functions
 * @{
 */

/**
 * @brief  Initializes I2C for BL24C02F.
 * @param  None
 * @retval An en_result_t enumeration value:
 *         @arg Ok: Initialize success
 *         @arg ErrorInvalidParameter: Invalid parameter
 */
en_result_t BL24C02F_Init(void)
{
    return BSP_BL24C02F_I2C_Init();
}

/**
 * @brief  BL24C02F read block of data.
 * @param  [in] u8ReadAddr:         The start address of the data to be read.
 * @param  [in] au8ReadBuf:         The pointer to the buffer contains the data to be stored.
 * @param  [in] u32NumByte:         Buffer size in byte.
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Read successfully
 *         @arg Error:              Read failed
 */
en_result_t BL24C02F_ReadBuf(uint8_t u8ReadAddr, uint8_t au8ReadBuf[], uint32_t u32NumByte)
{
    en_result_t enRet;
    uint8_t u8MemAddrTemp = u8ReadAddr;

    if((u8ReadAddr + u32NumByte) > BL24C02F_MEM_SIZE)
    {
        return Error;
    }

    BSP_BL24C02F_I2C_Cmd(Enable);
    BSP_BL24C02F_I2C_SWReset();

    enRet = BSP_BL24C02F_I2C_Start();

    if(Ok == enRet)
    {
        enRet = BSP_BL24C02F_I2C_TransAddr(BL24C02F_ADDR, I2C_DIR_TX);

        if(Ok == enRet)
        {
            enRet = BSP_BL24C02F_I2C_TransData(&u8MemAddrTemp, 1U);
            if(Ok == enRet)
            {
                enRet = BSP_BL24C02F_I2C_Restart();
                if(Ok == enRet)
                {
                    if(1UL == u32NumByte)
                    {
                        BSP_BL24C02F_I2C_AckConfig(I2C_NACK);
                    }

                    enRet = BSP_BL24C02F_I2C_TransAddr(BL24C02F_ADDR, I2C_DIR_RX);
                    if(Ok == enRet)
                    {
                        enRet = BSP_BL24C02F_I2C_ReceiveDataAndStop(au8ReadBuf, u32NumByte);
                    }

                    BSP_BL24C02F_I2C_AckConfig(I2C_ACK);
                }

            }
        }
    }

    if(Ok != enRet)
    {
        (void)BSP_BL24C02F_I2C_Stop();
    }

    BSP_BL24C02F_I2C_Cmd(Disable);
    return enRet;
}

/**
 * @brief  BL24C02F write page data.
 * @param  [in] u8WriteAddr:        The start address of the data to be write.
 * @param  [in] au8WriteBuf:        The pointer to the buffer contains the data to be write.
 * @param  [in] u32NumByte:         Buffer size in byte.
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Write successfully
 *         @arg Error:              Write failed
 *         @arg ErrorTimeout:       Time out
 * @note   This function don't check if the data write is whthin one page
 */
en_result_t BL24C02F_WritePage(uint8_t u8WriteAddr, const uint8_t au8WriteBuf[], uint32_t u32NumByte)
{
    en_result_t enRet;
    uint8_t u8MemAddrTemp = u8WriteAddr;

    if((u8WriteAddr + u32NumByte) > BL24C02F_MEM_SIZE)
    {
        return Error;
    }

    BSP_BL24C02F_I2C_Cmd(Enable);
    BSP_BL24C02F_I2C_SWReset();

    enRet = BSP_BL24C02F_I2C_Start();
    if(Ok == enRet)
    {
        enRet = BSP_BL24C02F_I2C_TransAddr(BL24C02F_ADDR, I2C_DIR_TX);

        if(Ok == enRet)
        {
            enRet = BSP_BL24C02F_I2C_TransData(&u8MemAddrTemp, 1U);
            if(Ok == enRet)
            {
                enRet = BSP_BL24C02F_I2C_TransData(au8WriteBuf, u32NumByte);
            }
        }
    }

    (void)BSP_BL24C02F_I2C_Stop();

    BSP_BL24C02F_I2C_Cmd(Disable);

    if(Ok != BL24C02F_I2C_WaitIdle())
    {
        enRet = ErrorTimeout;
    }
    return enRet;
}

/**
 * @brief  BL24C02F write block of data.
 * @param  [in] u8WriteAddr:        The start address of the data to be write.
 * @param  [in] au8WriteBuf:        The pointer to the buffer contains the data to be write.
 * @param  [in] u32NumByte:         Buffer size in byte.
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Write successfully
 *         @arg Error:              Write failed
 *         @arg ErrorTimeout:       Time out
 */
en_result_t BL24C02F_WriteBuf(uint8_t u8WriteAddr, const uint8_t au8WriteBuf[], uint32_t u32NumByte)
{
    uint32_t u32PageNum;
    uint8_t u8SingleNumStart;
    uint8_t u8SingleNumEnd;
    uint32_t u32NumRemainTemp = u32NumByte;
    uint32_t u32WriteOffset = 0UL;
    uint8_t u8WriteAddrTemp = u8WriteAddr;
    en_result_t enRet = Ok;

    if((u8WriteAddr + u32NumByte) > BL24C02F_MEM_SIZE)
    {
        return Error;
    }

    /* If start write address is align with page size */
    if(0U == (u8WriteAddrTemp % BL24C02F_PAGE_SIZE))
    {
        /* If Write number is less than page size */
        if(u32NumByte < BL24C02F_PAGE_SIZE)
        {
            u8SingleNumStart = (uint8_t)u32NumByte;
        }
        /* If Write number is more than page size */
        else
        {
            u8SingleNumStart = 0U;
        }
        u32NumRemainTemp -= (uint32_t)u8SingleNumStart;
    }
    /* If start write address is not align with page size */
    else
    {
        u8SingleNumStart = (BL24C02F_PAGE_SIZE - (u8WriteAddrTemp % BL24C02F_PAGE_SIZE));
        if((uint32_t)u8SingleNumStart > u32NumByte)
        {
            u8SingleNumStart = (uint8_t)u32NumByte;
        }
        u32NumRemainTemp -= (uint32_t)u8SingleNumStart;
    }

    u32PageNum = u32NumRemainTemp / BL24C02F_PAGE_SIZE;
    u8SingleNumEnd = (uint8_t)(u32NumRemainTemp % BL24C02F_PAGE_SIZE);

    if(0UL != u8SingleNumStart)
    {
        enRet = BL24C02F_WritePage(u8WriteAddrTemp, (const uint8_t*)(&au8WriteBuf[0] + u32WriteOffset), (uint32_t)u8SingleNumStart);
        u8WriteAddrTemp += u8SingleNumStart;
        u32WriteOffset += (uint32_t)u8SingleNumStart;
    }

    if(Ok == enRet)
    {
        if(0UL != u32PageNum)
        {
            for(uint32_t i=0UL; i<u32PageNum; i++)
            {
                enRet = BL24C02F_WritePage(u8WriteAddrTemp, (const uint8_t*)(&au8WriteBuf[0] + u32WriteOffset), BL24C02F_PAGE_SIZE);
                u8WriteAddrTemp += BL24C02F_PAGE_SIZE;
                u32WriteOffset += BL24C02F_PAGE_SIZE;
                if(Ok != enRet)
                {
                    break;
                }
            }
        }

        if(Ok == enRet)
        {
            if(0UL != u8SingleNumEnd)
            {
                enRet = BL24C02F_WritePage(u8WriteAddrTemp, (const uint8_t*)(&au8WriteBuf[0] + u32WriteOffset), (uint32_t)u8SingleNumEnd);
            }
        }
    }

    return enRet;
}

/**
 * @brief  BL24C02F wait idle.
 * @param  None
 * @retval en_result_t           Enumeration value:
 *         @arg Ok:                 Wait idle ok
 *         @arg ErrorTimeout:       Wait idle time out
 */
en_result_t BL24C02F_I2C_WaitIdle(void)
{
    en_result_t enRet = Ok;
    __IO uint32_t u32Tmp = 0UL;
    while(Ok != BL24C02F_I2C_GetStatus())
    {
       if(BL24C02F_WAIT_TIMEOUT == u32Tmp++)
       {
           enRet = ErrorTimeout;
       }
    }
    return enRet;
}

/**
 * @}
 */

/**
 * @addtogroup BL24C02F_Local_Functions BL24C02F Local Functions
 * @{
 */

/**
 * @brief  BL24C02F write block of data.
 * @param  None
 * @retval en_result_t           Enumeration value:
 *         @arg Ok:                 Idle
 *         @arg Error:              Busy
 *         @arg ErrorTimeout:       Time out
 */
static en_result_t BL24C02F_I2C_GetStatus(void)
{
    en_result_t enRet;

    BSP_BL24C02F_I2C_Cmd(Enable);
    BSP_BL24C02F_I2C_SWReset();

    enRet = BSP_BL24C02F_I2C_Start();
    if(Ok == enRet)
    {
        enRet = BSP_BL24C02F_I2C_TransAddr(BL24C02F_ADDR, I2C_DIR_TX);

        if(Ok == enRet)
        {
            if(Set == BSP_BL24C02F_I2C_GetAckStatus())
            {
                enRet = Error;
            }
        }
    }

    (void)BSP_BL24C02F_I2C_Stop();

    BSP_BL24C02F_I2C_Cmd(Disable);
    return enRet;
}

/**
 * @}
 */

#endif /* BSP_BL24C02F_ENABLE */

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
