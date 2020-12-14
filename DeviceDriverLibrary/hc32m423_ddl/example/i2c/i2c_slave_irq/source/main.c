/**
 *******************************************************************************
 * @file  i2c/i2c_slave_irq/source/main.c
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
 * @addtogroup I2C_Slave_Irq
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief I2c communication mode enum
 */
typedef enum
{
    Mode_Send = 0u,
    Mode_Rev = 1u,
}stc_i2c_com_mode_t;

/**
 * @brief I2c communication status enum
 */
typedef enum
{
    I2C_ComBusy = 0u,
    I2C_ComIdle = 1u,
}stc_i2c_com_status_t;

/**
 * @brief I2c communication structure
 */
typedef struct
{
    stc_i2c_com_mode_t    enMode;         /*!< I2C communication mode*/
    uint32_t              u32Length;      /*!< I2C communication data length*/
    uint8_t*              pBuf;           /*!< I2C communication data buffer pointer*/
    __IO uint32_t         u32DataIndex;   /*!< I2C communication data transfer index*/
    stc_i2c_com_status_t  enComStatus;    /*!< I2C communication status*/
}stc_i2c_communication_t;

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

#define TIMEOUT                         (0x10000UL)

/* Define Write and read data length for the example */
#define TEST_DATA_LEN                   (256U)
/* Define i2c baudrate */
#define I2C_BAUDRATE                    (400000UL)

/* I2C interrupt source and number define */
#define I2C_SLAVE_EEI_IRQn              (I2C_EEI_IRQn)
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
static stc_i2c_communication_t stcI2cCom;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Slave receive data
 *
 * @param  pu8RxData             Pointer to the data buffer
 * @param  u32Size               Data size
 * @retval en_result_t           Enumeration value:
 *         @arg Ok:                    Success
 *         @arg OperationInProgress:   Busy
 */
static en_result_t I2C_Slave_Receive_IT(uint8_t *pu8RxData, uint32_t u32Size)
{
    en_result_t enRet = Ok;

    if(I2C_ComIdle == stcI2cCom.enComStatus)
    {
        stcI2cCom.enComStatus = I2C_ComBusy;

        stcI2cCom.u32DataIndex = 0U;
        stcI2cCom.enMode = Mode_Rev;
        stcI2cCom.u32Length = u32Size;
        stcI2cCom.pBuf = pu8RxData;

        I2C_Cmd(I2C_UNIT, Enable);
        /* Config slave address match interrupt function*/
        I2C_IntCmd(I2C_UNIT, I2C_INT_MATCH_ADDR0, Enable);
    }
    else
    {
        enRet = OperationInProgress;
    }

    return enRet;
}

/**
 * @brief  Slave transmit data
 *
 * @param  pu8TxData             Pointer to the data buffer
 * @param  u32Size               Data size
 * @retval en_result_t           Enumeration value:
 *         @arg Ok:                    Success
 *         @arg OperationInProgress:   Busy
 */
static en_result_t I2C_Slave_Transmit_IT(uint8_t *pu8TxData, uint32_t u32Size)
{
    en_result_t enRet = Ok;

    if(I2C_ComIdle == stcI2cCom.enComStatus)
    {
        stcI2cCom.enComStatus = I2C_ComBusy;

        stcI2cCom.u32DataIndex = 0U;
        stcI2cCom.enMode = Mode_Send;
        stcI2cCom.u32Length = u32Size;
        stcI2cCom.pBuf = pu8TxData;

        I2C_Cmd(I2C_UNIT, Enable);
        /* Config slave address match interrupt function*/
        I2C_IntCmd(I2C_UNIT, I2C_INT_MATCH_ADDR0, Enable);
    }
    else
    {
        enRet = OperationInProgress;
    }

    return enRet;
}

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

    stcI2cCom.enComStatus = I2C_ComIdle;

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

        NVIC_ClearPendingIRQ(I2C_SLAVE_TEI_IRQn);
        NVIC_SetPriority(I2C_SLAVE_TEI_IRQn, DDL_IRQ_PRI03);
        NVIC_EnableIRQ(I2C_SLAVE_TEI_IRQn);

        NVIC_ClearPendingIRQ(I2C_SLAVE_EEI_IRQn);
        NVIC_SetPriority(I2C_SLAVE_EEI_IRQn, DDL_IRQ_PRI03);
        NVIC_EnableIRQ(I2C_SLAVE_EEI_IRQn);

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
        I2C_ClearStatus(I2C_UNIT, I2C_FLAG_MATCH_ADDR0 | I2C_FLAG_NACKF);

        if(Mode_Send == stcI2cCom.enMode)
        {
            if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_TRA))
            {
                /* Enable tx end interrupt function*/
                I2C_IntCmd(I2C_UNIT, I2C_FLAG_TX_CPLT, Enable);
                /* Write the first data to DTR immediately */
                I2C_WriteData(I2C_UNIT, BufRead());

                /* Enable stop and NACK interrupt */
                I2C_IntCmd(I2C_UNIT, I2C_INT_STOP | I2C_INT_NACK, Enable);
            }
        }
        else
        {
            if(Reset == I2C_GetStatus(I2C_UNIT, I2C_FLAG_TRA))
            {
                /* Config rx buffer full interrupt function*/
                I2C_IntCmd(I2C_UNIT, I2C_FLAG_RX_FULL, Enable);
                /* Enable stop and NACK interrupt */
                I2C_IntCmd(I2C_UNIT, I2C_INT_STOP | I2C_INT_NACK, Enable);
            }
        }
    }
    /* If NACK interrupt occurred */
    if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_NACKF))
    {
        /* clear NACK flag*/
        I2C_ClearStatus(I2C_UNIT, I2C_FLAG_NACKF);
        /* Stop tx or rx process*/
        if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_TRA))
        {
            /* Config tx buffer empty interrupt function disable*/
            I2C_IntCmd(I2C_UNIT, I2C_FLAG_TX_CPLT, Disable);
            I2C_ClearStatus(I2C_UNIT, I2C_FLAG_TX_CPLT);

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
                   I2C_FLAG_TX_CPLT | I2C_INT_RX_FULL |                        \
                   I2C_INT_STOP | I2C_INT_NACK,                                \
                   Disable);
        /* Clear STOPF flag */
        I2C_ClearStatus(I2C_UNIT, I2C_FLAG_STOP);

        I2C_Cmd(I2C_UNIT, Disable);
        /* Communication finished */
        stcI2cCom.enComStatus = I2C_ComIdle;
    }
}


/**
 * @brief   I2C TEI(transfer end) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_TxEnd_IrqHandler(void)
{
    if(Reset == I2C_GetStatus(I2C_UNIT, I2C_FLAG_ACKR))
    {
        I2C_WriteData(I2C_UNIT, BufRead());
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
 * @brief   static function for buffer write.
 * @param   [in]   u8Data the data to be write.
 * @retval  None
 */
static void BufWrite(uint8_t u8Data)
{
    if(stcI2cCom.u32DataIndex < stcI2cCom.u32Length)
    {
        u8RxBuf[stcI2cCom.u32DataIndex] = u8Data;
        stcI2cCom.u32DataIndex++;
    }
}

/**
 * @brief   Static function for buffer read.
 * @param   None
 * @retval  uint8_t  The data read out from buffer.
 */
static uint8_t BufRead(void)
{
    uint8_t temp;
    if(stcI2cCom.u32DataIndex < stcI2cCom.u32Length)
    {
        temp = u8RxBuf[stcI2cCom.u32DataIndex];
        stcI2cCom.u32DataIndex++;
    }
    else
    {
        temp = 0xFFu;
    }

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
        while(Ok != I2C_Slave_Receive_IT(u8RxBuf, TEST_DATA_LEN))
        {
            ;
        }

        while(I2C_ComBusy == stcI2cCom.enComStatus)
        {
            ;
        }

        while(Ok != I2C_Slave_Transmit_IT(u8RxBuf, TEST_DATA_LEN))
        {
            ;
        }

        while(I2C_ComBusy == stcI2cCom.enComStatus)
        {
            ;
        }
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
