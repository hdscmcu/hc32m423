/**
 *******************************************************************************
 * @file  ev_hc32m423_lqfp64_bl24c02f.c
 * @brief This file provides firmware functions for EEPROM BL24C02F.
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
#include "ev_hc32m423_lqfp64_bl24c02f.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32M423_LQFP64
 * @{
 */

/** @defgroup EV_HC32M423_LQFP64_BL24C02F HC32M423 EVB BL24C02F
  * @{
  */

#if ((BSP_BL24C02F_ENABLE == BSP_ON) && \
     (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423))

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32M423_LQFP64_BL24C02F_Local_Macros BSP BL24C02F Local Macros
 * @{
 */

/* I2C unit define */
#define BSP_BL24C02F_I2C_UNIT           (CM_I2C)
#define BSP_BL24C02F_I2C_UNIT_CLOCK     (CLK_FCG_IIC)

/* Define port and pin for SDA and SCL */
#define BSP_I2C_SCL_PORT                (GPIO_PORT_7)
#define BSP_I2C_SCL_PIN                 (GPIO_PIN_5)
#define BSP_I2C_SDA_PORT                (GPIO_PORT_7)
#define BSP_I2C_SDA_PIN                 (GPIO_PIN_6)

/* Define i2c baudrate */
#define BSP_I2C_BAUDRATE                (400000UL)

#define BSP_BL24C02F_TIMEOUT            (0x15000U)

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

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
en_result_t BSP_BL24C02F_I2C_Init(void)
{
    stc_i2c_init_t stcI2cInit;
    float32_t fErr;
    en_result_t enRet;

    /* Initialize I2C port*/
    GPIO_SetFunc(BSP_I2C_SCL_PORT, BSP_I2C_SCL_PIN, GPIO_FUNC_7_I2C);
    GPIO_SetFunc(BSP_I2C_SDA_PORT, BSP_I2C_SDA_PIN, GPIO_FUNC_7_I2C);

    /* Enable I2C Peripheral*/
    CLK_FcgPeriphClockCmd(BSP_BL24C02F_I2C_UNIT_CLOCK, Enable);

    I2C_DeInit(BSP_BL24C02F_I2C_UNIT);

    (void)I2C_StructInit(&stcI2cInit);
    stcI2cInit.u32Baudrate = BSP_I2C_BAUDRATE;
    stcI2cInit.u32SclTime = 5U;
    stcI2cInit.u32ClockDiv = I2C_CLK_DIV4;
    enRet = I2C_Init(BSP_BL24C02F_I2C_UNIT, &stcI2cInit, &fErr);

    if(Ok == enRet)
    {
        I2C_BusWaitCmd(BSP_BL24C02F_I2C_UNIT, Enable);
    }

    return enRet;
}

/**
 * @brief  BL24C02F I2C start
 * @param  None
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Start success
 *         @arg ErrorTimeout:       Start time out
 */
en_result_t BSP_BL24C02F_I2C_Start(void)
{
    return I2C_Start(BSP_BL24C02F_I2C_UNIT, BSP_BL24C02F_TIMEOUT);
}

/**
 * @brief  BL24C02F I2C restart
 * @param  None
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Restart success
 *         @arg ErrorTimeout:       Restart time out
 */
en_result_t BSP_BL24C02F_I2C_Restart(void)
{
    return I2C_Restart(BSP_BL24C02F_I2C_UNIT, BSP_BL24C02F_TIMEOUT);
}

/**
 * @brief  BL24C02F send device address
 * @param  [in] u8Addr              The device address to be sent
 * @param  [in] u8Dir               Transfer direction, This parameter can be
 *                                  one of the following values:
 *         @arg I2C_DIR_TX
 *         @arg I2C_DIR_RX
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Send successfully
 *         @arg ErrorTimeout:       Send address time out
 */
en_result_t BSP_BL24C02F_I2C_TransAddr(uint8_t u8Addr, uint8_t u8Dir)
{
    return I2C_TransAddr(BSP_BL24C02F_I2C_UNIT, u8Addr, u8Dir, BSP_BL24C02F_TIMEOUT);
}

/**
 * @brief  BL24C02F send data
 * @param  [in] au8TxData           The data array to be sent
 * @param  [in] u32Size             Number of data in array pau8TxData
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Send successfully
 *         @arg ErrorTimeout:       Send data time out
 *         @arg ErrorInvalidParameter: au8TxData is NULL
 */
en_result_t BSP_BL24C02F_I2C_TransData(uint8_t const au8TxData[], uint32_t u32Size)
{
    return I2C_TransData(BSP_BL24C02F_I2C_UNIT, au8TxData, u32Size, BSP_BL24C02F_TIMEOUT);
}

/**
 * @brief  BL24C02F receive data
 * @param  [out] au8RxData          Array to hold the received data
 * @param  [in] u32Size             Number of data to be received
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Receive successfully
 *         @arg ErrorTimeout:       Receive data time out
 *         @arg ErrorInvalidParameter: au8RxData is NULL
 */
en_result_t BSP_BL24C02F_I2C_ReceiveDataAndStop(uint8_t au8RxData[], uint32_t u32Size)
{
    return I2C_MasterReceiveDataAndStop(BSP_BL24C02F_I2C_UNIT, au8RxData, u32Size, BSP_BL24C02F_TIMEOUT);
}

/**
 * @brief  BL24C02F I2C stop
 * @param  None
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Stop successfully
 *         @arg ErrorTimeout:       Stop time out
 */
en_result_t BSP_BL24C02F_I2C_Stop(void)
{
    return I2C_Stop(BSP_BL24C02F_I2C_UNIT, BSP_BL24C02F_TIMEOUT);
}

/**
 * @brief  BL24C02F I2C software reset
 * @param  None
 * @retval None
 */
void BSP_BL24C02F_I2C_SWReset(void)
{
    I2C_SWResetCmd(BSP_BL24C02F_I2C_UNIT, Enable);
    I2C_SWResetCmd(BSP_BL24C02F_I2C_UNIT, Disable);
}

/**
 * @brief  BL24C02F I2C command
 * @param  [in] enNewState          The function new state.
 *         @arg Enable:             Enable I2C.
 *         @arg Disable:            Disable i2C.
 * @retval None
 */
void BSP_BL24C02F_I2C_Cmd(en_functional_state_t enNewState)
{
    I2C_Cmd(BSP_BL24C02F_I2C_UNIT, enNewState);
}

/**
 * @brief  BL24C02F I2C ACK config
 * @param  [in] u32AckConfig        I2C ACK configurate.
 *         @arg I2C_ACK:            Send ACK after date received.
 *         @arg I2C_NACK:           Send NACK after date received.
 * @retval None
 */
void BSP_BL24C02F_I2C_AckConfig(uint32_t u32AckConfig)
{
    I2C_AckConfig(BSP_BL24C02F_I2C_UNIT, u32AckConfig);
}

/**
 * @brief  BL24C02F I2C ACK config
 * @param  None
 * @retval en_flag_status_t         The status of the I2C status flag, may be Set or Reset.
 */
en_flag_status_t BSP_BL24C02F_I2C_GetAckStatus(void)
{
    return I2C_GetStatus(BSP_BL24C02F_I2C_UNIT, I2C_FLAG_ACKR);
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

#endif /* BSP_BL24C02F_ENABLE && (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423) */

/**
 * @}
 */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
