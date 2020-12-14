/**
 *******************************************************************************
 * @file  i2c/i2c_slave_polling/source/main.c
 * @brief Main program of I2C for the Device Driver Library.
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
#include "hc32_ddl.h"

/**
 * @addtogroup HC32M423_DDL_Examples
 * @{
 */

/**
 * @addtogroup I2C_Slave_Polling
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define I2C_UNIT                        (CM_I2C)

/* Define slave device address for example */
#define DEVICE_ADDRESS                  (0x06U)
//#define I2C_10BITS_ADDRESS              (1U)

/* Define port and pin for SDA and SCL */
#define I2C_SCL_PORT                    (GPIO_PORT_7)
#define I2C_SCL_PIN                     (GPIO_PIN_5)
#define I2C_SDA_PORT                    (GPIO_PORT_7)
#define I2C_SDA_PIN                     (GPIO_PIN_6)
#define I2C_GPIO_FUNC                   (GPIO_FUNC_7_I2C)

#define TIMEOUT                         (0x14000U)

/* Define Write and read data length for the example */
#define TEST_DATA_LEN                   (256U)
/* Define i2c baudrate */
#define I2C_BAUDRATE                    (400000UL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8RxBuf[TEST_DATA_LEN];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Slave receive data
 *
 * @param  au8Data               Data array
 * @param  u32Size               Data size
 * @param  u32Timeout            Time out count
 * @retval en_result_t           Enumeration value:
 *         @arg Ok:                 Success
 *         @arg Error:              Failed
 *         @arg ErrorTimeout:       Time out
 */
static en_result_t I2C_Slave_Receive(uint8_t au8Data[], uint32_t u32Size, uint32_t u32Timeout)
{
    en_result_t enRet;
    /* clear all status */

    I2C_Cmd(I2C_UNIT, Enable);

    /* Clear status */
    I2C_ClearStatus(I2C_UNIT, I2C_FLAG_STOP|I2C_FLAG_NACKF);

    /* Wait slave address matched */
    while(Reset == I2C_GetStatus(I2C_UNIT, I2C_FLAG_MATCH_ADDR0))
    {
        ;
    }
    I2C_ClearStatus(I2C_UNIT, I2C_FLAG_MATCH_ADDR0);

    if(Reset == I2C_GetStatus(I2C_UNIT, I2C_FLAG_TRA))
    {
        /* Slave receive data*/
        enRet = I2C_ReceiveData(I2C_UNIT, au8Data, u32Size, u32Timeout);

        if((Ok == enRet) || (ErrorTimeout == enRet))
        {
            /* Wait stop condition */
            enRet = I2C_WaitStatus(I2C_UNIT, I2C_FLAG_STOP, Set, u32Timeout);
        }
    }
    else
    {
        enRet = Error;
    }

    I2C_Cmd(I2C_UNIT, Disable);
    return enRet;
}

/**
 * @brief  Slave transmit data
 **
 * @param  au8Data               Data array
 * @param  u32Size               Data size
 * @param  u32Timeout            Time out count
 * @retval en_result_t           Enumeration value:
 *         @arg Ok:                 Success
 *         @arg Error:              Failed
 *         @arg ErrorTimeout:       Time out
 */
static en_result_t I2C_Slave_Transmit(uint8_t au8Data[], uint32_t u32Size, uint32_t u32Timeout)
{
    en_result_t enRet;

    I2C_Cmd(I2C_UNIT, Enable);

    /* Clear status */
    I2C_ClearStatus(I2C_UNIT, I2C_FLAG_STOP|I2C_FLAG_NACKF);

    /* Wait slave address matched */
    while(Reset == I2C_GetStatus(I2C_UNIT, I2C_FLAG_MATCH_ADDR0))
    {
        ;
    }
    I2C_ClearStatus(I2C_UNIT, I2C_FLAG_MATCH_ADDR0);

#ifdef I2C_10BITS_ADDRESS
    /* Wait slave address matched */
    while(Reset == I2C_GetStatus(I2C_UNIT, I2C_FLAG_MATCH_ADDR0))
    {
        ;
    }
    I2C_ClearStatus(I2C_UNIT, I2C_FLAG_MATCH_ADDR0);
#endif

    if(Reset == I2C_GetStatus(I2C_UNIT, I2C_FLAG_TRA))
    {
        enRet = Error;
    }
    else
    {
        enRet = I2C_TransData(I2C_UNIT, au8Data, u32Size, u32Timeout);

        if((Ok == enRet) || (ErrorTimeout == enRet))
        {
            /* Release SCL pin */
            (void)I2C_ReadData(I2C_UNIT);

            /* Wait stop condition */
            enRet = I2C_WaitStatus(I2C_UNIT, I2C_FLAG_STOP, Set, u32Timeout);
        }
    }

    I2C_Cmd(I2C_UNIT, Disable);
    return enRet;
}


/**
 * @brief  Initialize the I2C peripheral for slave
 * @param  None
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Success
 *         @arg ErrorInvalidParameter:  Invalid parameter
 */
static en_result_t Slave_Initialize(void)
{
    en_result_t enRet;
    stc_i2c_init_t stcI2cInit;
    float32_t fErr;

    I2C_DeInit(I2C_UNIT);

    (void)I2C_StructInit(&stcI2cInit);
    stcI2cInit.u32Baudrate = I2C_BAUDRATE;
    stcI2cInit.u32ClockDiv = I2C_CLK_DIV4;
    stcI2cInit.u32SclTime = 5U;
    enRet = I2C_Init(I2C_UNIT, &stcI2cInit, &fErr);

    if(Ok == enRet)
    {
        /* Set slave address*/
        #ifdef I2C_10BITS_ADDRESS
        I2C_SlaveAddrConfig(I2C_UNIT, I2C_ADDR0, I2C_ADDR_10BIT, DEVICE_ADDRESS);
        #else
        I2C_SlaveAddrConfig(I2C_UNIT, I2C_ADDR0, I2C_ADDR_7BIT, DEVICE_ADDRESS);
        #endif
    }
    return enRet;
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
    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1|PWC_UNLOCK_CODE_2);
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
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1|PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Main function of i2c_slave_polling project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t i;

    /* Register write unprotected for some required peripherals. */
    Peripheral_WE();
    /* System clock Init */
    BSP_CLK_Init();
    /* LED init */
    BSP_LED_Init();

    /* Test buffer initialize */
    for(i=0U; i<TEST_DATA_LEN; i++)
    {
        u8RxBuf[i] = 0U;
    }

    /* Initialize I2C port*/
    GPIO_SetFunc(I2C_SCL_PORT, I2C_SCL_PIN, I2C_GPIO_FUNC);
    GPIO_SetFunc(I2C_SDA_PORT, I2C_SDA_PIN, I2C_GPIO_FUNC);

    /* Enable I2C Peripheral*/
    CLK_FcgPeriphClockCmd(CLK_FCG_IIC, Enable);

    /* Initialize I2C peripheral and enable function*/
    if(Ok != Slave_Initialize())
    {
        /* Initialieze error*/
        BSP_LED_On(LED_RED);
        Peripheral_WP();
        for(;;)
        {
            ;
        }
    }

    for(;;)
    {
        if(Ok == I2C_Slave_Receive(u8RxBuf, TEST_DATA_LEN, TIMEOUT))
        {
            if(Ok != I2C_Slave_Transmit(u8RxBuf, TEST_DATA_LEN, TIMEOUT))
            {
                /* Failed */
                break;
            }
        }
        else
        {
            /* Failed */
            break;
        }
    }

    /* Communication failed */
    BSP_LED_Off(LED_GREEN);
    BSP_LED_On(LED_RED);
    Peripheral_WP();
    for(;;)
    {
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
