/**
 *******************************************************************************
 * @file  i2c/i2c_slave_irq/source/main.c
 * @brief Main program of I2C for the Device Driver Library.
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
 * @addtogroup I2C_Slave_Irq
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

/* Define port and pin for SDA and SCL */
#define I2C_SCL_PORT                    (GPIO_PORT_7)
#define I2C_SCL_PIN                     (GPIO_PIN_5)
#define I2C_SDA_PORT                    (GPIO_PORT_7)
#define I2C_SDA_PIN                     (GPIO_PIN_6)

#define TIMEOUT                         (0x10000UL)

#define ADDRESS_W                       (0x00U)
#define ADDRESS_R                       (0x01U)

/* Define Write and read data length for the example */
#define TEST_DATA_LEN                   (128U)
/* Define i2c baudrate */
#define I2C_BAUDRATE                    (400000UL)

/* I2C interrupt source and number define */
#define I2C_SLAVE_EEI_IRQn              (I2C_EEI_IRQn)
#define I2C_SLAVE_TXI_IRQn              (I2C_TXI_IRQn)
#define I2C_SLAVE_RXI_IRQn              (I2C_RXI_IRQn)
#define I2C_SLAVE_TEI_IRQn              (I2C_TEI_IRQn)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static en_result_t Slave_Initialize(void);
static void BufWrite(uint8_t u8Data);
static uint8_t BufRead(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8RxBuf[TEST_DATA_LEN];
static uint32_t u32DataInOffset = 0UL;
static uint32_t u32DataOutOffset = 0UL;
static __IO uint8_t u8FinishFlag = 0U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief   Initialize the I2C peripheral for slave
 * @param   None
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
    stcI2cInit.u32SclTime = 5U;
    stcI2cInit.u32ClockDiv = I2C_CLK_DIV4;
    enRet = I2C_Init(I2C_UNIT, &stcI2cInit, &fErr);

    if(Ok == enRet)
    {
        /* Set slave address*/
        #ifdef I2C_10BITS_ADDRESS
        I2C_SlaveAddrConfig(I2C_UNIT, I2C_ADDR0, I2C_ADDR_10BIT, DEVICE_ADDRESS);
        #else
        I2C_SlaveAddrConfig(I2C_UNIT, I2C_ADDR0, I2C_ADDR_7BIT, DEVICE_ADDRESS);
        #endif

        /*NVIC configuration for interrupt */
        NVIC_ClearPendingIRQ(I2C_SLAVE_RXI_IRQn);
        NVIC_SetPriority(I2C_SLAVE_RXI_IRQn, DDL_IRQ_PRI03);
        NVIC_EnableIRQ(I2C_SLAVE_RXI_IRQn);

        NVIC_ClearPendingIRQ(I2C_SLAVE_TXI_IRQn);
        NVIC_SetPriority(I2C_SLAVE_TXI_IRQn, DDL_IRQ_PRI03);
        NVIC_EnableIRQ(I2C_SLAVE_TXI_IRQn);

        NVIC_ClearPendingIRQ(I2C_SLAVE_TEI_IRQn);
        NVIC_SetPriority(I2C_SLAVE_TEI_IRQn, DDL_IRQ_PRI03);
        NVIC_EnableIRQ(I2C_SLAVE_TEI_IRQn);

        NVIC_ClearPendingIRQ(I2C_SLAVE_EEI_IRQn);
        NVIC_SetPriority(I2C_SLAVE_EEI_IRQn, DDL_IRQ_PRI03);
        NVIC_EnableIRQ(I2C_SLAVE_EEI_IRQn);

        /* I2C function command */
        I2C_Cmd(I2C_UNIT, Enable);

        /* Config slave address match interrupt function*/
        I2C_IntCmd(I2C_UNIT, I2C_INT_MATCH_ADDR0, Enable);
    }

    return enRet;
}

/**
 * @brief   I2C EEI(communication error or event) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_Error_IrqHandler(void)
{
    /* If address flag valid */
    if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_MATCH_ADDR0))
    {
        I2C_ClearStatus(I2C_UNIT, I2C_FLAG_MATCH_ADDR0);
        /* Enable Tx or Rx function*/
        if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_TX))
        {
            /* Config tx buffer empty interrupt function*/
            I2C_IntCmd(I2C_UNIT, I2C_INT_TX_EMPTY, Enable);
            /* Write the first data to DTR immediately */
            I2C_WriteData(I2C_UNIT, BufRead());
        }
        else
        {
            /* Config rx buffer full interrupt function*/
            I2C_IntCmd(I2C_UNIT, I2C_INT_RX_FULL, Enable);
        }

        /* Enable stop and NACK interrupt */
        I2C_IntCmd(I2C_UNIT, I2C_INT_STOP | I2C_INT_NACK, Enable);
    }

    /* If NACK interrupt occurred */
    if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_ACK))
    {
        /* clear NACK flag*/
        I2C_ClearStatus(I2C_UNIT, I2C_FLAG_NACK);
        /* Stop tx or rx process*/
        if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_TX))
        {
            /* Config tx buffer empty interrupt function disable*/
            I2C_IntCmd(I2C_UNIT, I2C_INT_TX_EMPTY, Disable);

            /* Read DRR register to release SCL*/
            (void)I2C_ReadData(I2C_UNIT);
        }
        else
        {
            /* Config rx buffer full interrupt function disable */
            I2C_IntCmd(I2C_UNIT, I2C_INT_RX_FULL, Disable);
        }
    }

    /* If stop interrupt occurred */
    if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_STOP))
    {
        /* Disable all interrupt enable flag except SLADDR0IE*/
        I2C_IntCmd(I2C_UNIT,
                   I2C_INT_TX_EMPTY |  I2C_INT_RX_FULL |                       \
                   I2C_INT_STOP | I2C_INT_NACK,                            \
                   Disable);
        /* Clear STOPF flag */
        I2C_ClearStatus(I2C_UNIT, I2C_FLAG_STOP);
        /* Communication finished */
        u8FinishFlag = 1U;
    }
}

/**
 * @brief   I2C TXI(transfer buffer empty) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_TxEmpty_IrqHandler(void)
{
    if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_TX_EMPTY))
    {
        if(u32DataOutOffset < TEST_DATA_LEN)
        {
            I2C_WriteData(I2C_UNIT, BufRead());
        }
        else
        {
            /* Disable TXI interrupt */
            I2C_IntCmd(I2C_UNIT, I2C_INT_TX_EMPTY, Disable);
            /* Enable TEI interrupt */
            I2C_IntCmd(I2C_UNIT, I2C_INT_TX_CPLT, Enable);
        }
    }
}

/**
 * @brief   I2C RXI(receive buffer full) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_RxEnd_IrqHandler(void)
{
    if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_RX_FULL))
    {
        BufWrite(I2C_ReadData(I2C_UNIT));
    }
}

/**
 * @brief   I2C TEI(transfer end) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_TxEnd_IrqHandler(void)
{
    if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_TX_CPLT))
    {
        /* Dummy read for release SCL */
        (void)I2C_ReadData(I2C_UNIT);
    }
}

/**
 * @brief   static function for buffer write.
 * @param   [in]   u8Data the data to be write.
 * @retval  None
 */
static void BufWrite(uint8_t u8Data)
{
    if(u32DataInOffset >= TEST_DATA_LEN)
    {
        /* Error */
        for(;;)
        {
            ;
        }
    }
    u8RxBuf[u32DataInOffset] = u8Data;
    u32DataInOffset++;
}

/**
 * @brief   Static function for buffer read.
 * @param   None
 * @retval  uint8_t  The data read out from buffer.
 */
static uint8_t BufRead(void)
{
    uint8_t temp;
    if(u32DataOutOffset >= TEST_DATA_LEN)
    {
        /* Error */
        for(;;)
        {
            ;
        }
    }
    temp = u8RxBuf[u32DataOutOffset];
    u32DataOutOffset++;

    return temp;
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
 * @brief  Main function of i2c_slave_irq project
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
    GPIO_SetFunc(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_FUNC_7_I2C);
    GPIO_SetFunc(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_FUNC_7_I2C);

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

    /* Wait communicaiton finished*/
    while(0U == u8FinishFlag)
    {
        ;
    }

    /* Communication finished */
    BSP_LED_Off(LED_RED);
    BSP_LED_On(LED_GREEN);
    Peripheral_WP();
    for(;;)
    {
        ;
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
