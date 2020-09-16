/**
 *******************************************************************************
 * @file  bl24c02f.c
 * @brief This midware file provides firmware functions to BL24C02F E2PROM.
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

/** @defgroup BL24C02F E2PROM Driver for BL24C02F
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
#define ADDR_WR                     (0x00U)
#define ADDR_RD                     (0x01U)

#define BL24C02F_ADDR               (0x50U)
#define BL24C02F_PAGE_SIZE          (16U)
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
    en_result_t enRet = Ok;
    uint32_t u32Ret;
    /* E2prom random read*/
    u32Ret = (uint32_t)BSP_BL24C02F_I2C_Start();
    u32Ret |= (uint32_t)BSP_BL24C02F_I2C_AddrTrans((uint8_t)(BL24C02F_ADDR << 1U) | ADDR_WR);
    u32Ret |= (uint32_t)BSP_BL24C02F_I2C_DataAddrTrans(u8ReadAddr);

    u32Ret |= (uint32_t)BSP_BL24C02F_I2C_Restart();
    u32Ret |= (uint32_t)BSP_BL24C02F_I2C_AddrTrans((uint8_t)(BL24C02F_ADDR << 1U) | ADDR_RD);
    u32Ret |= (uint32_t)BSP_BL24C02F_I2C_DataReceive(au8ReadBuf, u32NumByte);
    u32Ret |= (uint32_t)BSP_BL24C02F_I2C_Stop();

    if((uint32_t)Ok != u32Ret)
    {
        enRet = Error;
    }

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
 * @note   This function don't check if the data write is whthin one page
 */
en_result_t BL24C02F_WritePage(uint8_t u8WriteAddr, const uint8_t au8WriteBuf[], uint32_t u32NumByte)
{
    en_result_t enRet = Ok;
    uint32_t u32Ret;

    u32Ret = (uint32_t)BSP_BL24C02F_I2C_Start();
    u32Ret |= (uint32_t)BSP_BL24C02F_I2C_AddrTrans((uint8_t)(BL24C02F_ADDR<<1U) | ADDR_WR);
    u32Ret |= (uint32_t)BSP_BL24C02F_I2C_DataAddrTrans(u8WriteAddr);

    u32Ret |= (uint32_t)BSP_BL24C02F_I2C_DataTrans(au8WriteBuf, u32NumByte);
    u32Ret |= (uint32_t)BSP_BL24C02F_I2C_Stop();

    if((uint32_t)Ok != u32Ret)
    {
        enRet = Error;
    }

    return enRet;
}

/**
 * @brief  BL24C02F write block of data.
 * @param  [in] u8WriteAddr:        The start address of the data to be write.
 * @param  [in] au8WriteBuf:        The pointer to the buffer contains the data to be write.
 * @param  [in] u32NumByte:         Buffer size in byte.
 * @retval None
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

    if(0UL != u32PageNum)
    {
        for(uint32_t i=0UL; i<u32PageNum; i++)
        {
            enRet = BL24C02F_WritePage(u8WriteAddrTemp, (const uint8_t*)(&au8WriteBuf[0] + u32WriteOffset), BL24C02F_PAGE_SIZE);
            u8WriteAddrTemp += BL24C02F_PAGE_SIZE;
            u32WriteOffset += BL24C02F_PAGE_SIZE;
        }
    }

    if(0UL != u8SingleNumEnd)
    {
        enRet = BL24C02F_WritePage(u8WriteAddrTemp, (const uint8_t*)(&au8WriteBuf[0] + u32WriteOffset), (uint32_t)u8SingleNumEnd);
    }
    return enRet;
}


/**
 * @brief  BL24C02F write block of data.
 * @param  None
 * @retval en_result_t
 */
en_result_t BL24C02F_WaitReady(void)
{
    return BSP_BL24C02F_I2C_WaitReady();
}



/**
 * @}
 */

/**
 * @addtogroup BL24C02F_Local_Functions BL24C02F Local Functions
 * @{
 */



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
