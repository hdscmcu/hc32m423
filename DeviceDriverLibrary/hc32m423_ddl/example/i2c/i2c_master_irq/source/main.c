/**
 *******************************************************************************
 * @file  i2c/i2c_master_irq/source/main.c
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
 * @addtogroup I2C_Master_Irq
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
    Mode_Send = 0U,
    Mode_Rev = 1U,
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
#define DEVICE_ADDR                     (0x06U)

/* Define port and pin for SDA and SCL */
#define I2C_SCL_PORT                    (GPIO_PORT_7)
#define I2C_SCL_PIN                     (GPIO_PIN_5)
#define I2C_SDA_PORT                    (GPIO_PORT_7)
#define I2C_SDA_PIN                     (GPIO_PIN_6)
#define I2C_GPIO_FUNC                   (GPIO_FUNC_7_I2C)

#define KEY1_PORT                       (GPIO_PORT_0)
#define KEY1_PIN                        (GPIO_PIN_2)

#define TIMEOUT                         (0x10000UL)

/* Define Write and read data length for the example */
#define TEST_DATA_LEN                   (256U)
/* Define i2c baudrate */
#define I2C_BAUDRATE                    (400000UL)

/* I2C interrupt source and number define */
#define I2C_MASTER_EEI_IRQn             (I2C_EEI_IRQn)
#define I2C_MASTER_TXI_IRQn             (I2C_TXI_IRQn)
#define I2C_MASTER_RXI_IRQn             (I2C_RXI_IRQn)
#define I2C_MASTER_TEI_IRQn             (I2C_TEI_IRQn)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void BufWrite(uint8_t au8Buf[], uint8_t u8Data);
static uint8_t BufRead(uint8_t au8Buf[]);
static void Master_Start(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8TxBuf[TEST_DATA_LEN];
static uint8_t u8RxBuf[TEST_DATA_LEN];
static stc_i2c_communication_t stcI2cCom;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Wait key short press.
 * @param  None
 * @retval None
 */
static void WaitKeyShortPress(void)
{
    /* Wait key up */
    while(Pin_Set != GPIO_ReadInputPins(KEY1_PORT, KEY1_PIN))
    {
        ;
    }
    DDL_DelayMS(5U);

    /* Wait key down */
    while(Pin_Reset != GPIO_ReadInputPins(KEY1_PORT, KEY1_PIN))
    {
        ;
    }
    DDL_DelayMS(5U);

    /* Wait key up */
    while(Pin_Set != GPIO_ReadInputPins(KEY1_PORT, KEY1_PIN))
    {
        ;
    }
    DDL_DelayMS(5U);
}

/**
 * @brief  Master send data kick start via interrupt .
 * @param  au8Data               Data array
 * @param  u32Size               Data size
 * @retval en_result_t           Enumeration value:
 *         @arg Ok:                    Success
 *         @arg OperationInProgress:   Busy
 */
static en_result_t I2C_Master_Transmit_IT(uint8_t au8Data[], uint32_t u32Size)
{
    en_result_t enRet = Ok;

    if(I2C_ComIdle == stcI2cCom.enComStatus)
    {
        stcI2cCom.enComStatus = I2C_ComBusy;

        stcI2cCom.u32DataIndex = 0U;
        stcI2cCom.enMode = Mode_Send;
        stcI2cCom.u32Length = u32Size;
        stcI2cCom.pBuf = au8Data;

        /* General start condition */
        Master_Start();
    }
    else
    {
        enRet = OperationInProgress;
    }

    return enRet;
}

/**
 * @brief  Master Rev data kick start via interrupt .
 * @param  au8Data               Data array
 * @param  u32Size               Data size
 * @retval en_result_t           Enumeration value:
 *         @arg Ok:                    Success
 *         @arg OperationInProgress:   Busy
 */
static en_result_t I2C_Master_Receive_IT(uint8_t au8Data[], uint32_t u32Size)
{
    en_result_t enRet = Ok;

    if(I2C_ComIdle == stcI2cCom.enComStatus)
    {
        stcI2cCom.enComStatus = I2C_ComBusy;
        stcI2cCom.u32DataIndex = 0U;
        stcI2cCom.enMode = Mode_Rev;
        stcI2cCom.u32Length = u32Size;
        stcI2cCom.pBuf = au8Data;

        /* General start condition */
        Master_Start();
    }
    else
    {
        enRet = OperationInProgress;
    }

    return enRet;
}

/**
 * @brief   Initialize the I2C peripheral for master
 * @param   None
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Success
 *         @arg ErrorInvalidParameter:  Invalid parameter
 */
static en_result_t Master_Initialize(void)
{
    en_result_t enRet;
    stc_i2c_init_t stcI2cInit;
    float32_t fErr;

    I2C_DeInit(I2C_UNIT);

    stcI2cCom.enComStatus = I2C_ComIdle;

    (void)I2C_StructInit(&stcI2cInit);
    stcI2cInit.u32Baudrate = I2C_BAUDRATE;
    stcI2cInit.u32ClockDiv = I2C_CLK_DIV4;
    stcI2cInit.u32SclTime = 5U;
    enRet = I2C_Init(I2C_UNIT, &stcI2cInit, &fErr);
    if(Ok == enRet)
    {
        /*NVIC configuration for interrupt */
        NVIC_ClearPendingIRQ(I2C_MASTER_RXI_IRQn);
        NVIC_SetPriority(I2C_MASTER_RXI_IRQn, DDL_IRQ_PRI03);
        NVIC_EnableIRQ(I2C_MASTER_RXI_IRQn);

        NVIC_ClearPendingIRQ(I2C_MASTER_TXI_IRQn);
        NVIC_SetPriority(I2C_MASTER_TXI_IRQn, DDL_IRQ_PRI03);
        NVIC_EnableIRQ(I2C_MASTER_TXI_IRQn);

        NVIC_ClearPendingIRQ(I2C_MASTER_TEI_IRQn);
        NVIC_SetPriority(I2C_MASTER_TEI_IRQn, DDL_IRQ_PRI03);
        NVIC_EnableIRQ(I2C_MASTER_TEI_IRQn);

        NVIC_ClearPendingIRQ(I2C_MASTER_EEI_IRQn);
        NVIC_SetPriority(I2C_MASTER_EEI_IRQn, DDL_IRQ_PRI03);
        NVIC_EnableIRQ(I2C_MASTER_EEI_IRQn);

        I2C_BusWaitCmd(I2C_UNIT, Enable);
    }
    return enRet;
}

/**
 * @brief  Send Start condition.
 * @param  None
 * @retval None
 */
static void Master_Start(void)
{
    /* I2C function command */
    I2C_Cmd(I2C_UNIT, Enable);
    /* Config startf and slave address match interrupt function*/
    I2C_IntCmd(I2C_UNIT, I2C_INT_START | I2C_INT_MATCH_ADDR0, Enable);

    I2C_SWResetCmd(I2C_UNIT, Enable);
    I2C_SWResetCmd(I2C_UNIT, Disable);
    /* generate start signal */
    I2C_GenerateStart(I2C_UNIT);
}

/**
 * @brief   Send slave address
 * @param   [in]  u8Addr     The slave address
 * @param   [in]  u8Dir      Can be I2C_DIR_TX or I2C_DIR_RX
 * @retval None
 */
static void Master_SendAddr(uint8_t u8Addr, uint8_t u8Dir)
{
    /* Send I2C address */
    I2C_WriteData(I2C_UNIT, (u8Addr << 1u) | u8Dir);
}

/**
 * @brief   I2C EEI(communication error or event) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_Error_IrqHandler(void)
{
    /* If starf flag valid */
    if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_START))
    {
        I2C_ClearStatus(I2C_UNIT, I2C_FLAG_START | I2C_FLAG_NACKF);
        I2C_IntCmd(I2C_UNIT, I2C_INT_STOP | I2C_INT_NACK, Enable);

        if(Mode_Send == stcI2cCom.enMode)
        {
            /* Enable TEI interrupt which indicate address transfer end */
            I2C_IntCmd(I2C_UNIT, I2C_FLAG_TX_CPLT, Enable);

            Master_SendAddr(DEVICE_ADDR, I2C_DIR_TX);
        }
        else
        {
            /* if read data length is 1 */
            if(stcI2cCom.u32Length == 1U)
            {
                I2C_AckConfig(I2C_UNIT, I2C_NACK);
            }

            /* Enable RXI interrupt which indicate data receive buffer full */
            I2C_IntCmd(I2C_UNIT, I2C_FLAG_RX_FULL, Enable);

            Master_SendAddr(DEVICE_ADDR, I2C_DIR_RX);
        }
    }

    /* If NACK interrupt occurred */
    if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_ACKR))
    {
        /* clear NACK flag*/
        I2C_ClearStatus(I2C_UNIT, I2C_FLAG_NACKF);

        /* Stop tx or rx process*/
        I2C_IntCmd(I2C_UNIT, I2C_INT_TX_EMPTY | I2C_INT_RX_FULL | I2C_INT_TX_CPLT | I2C_INT_NACK, Disable);

        /* Generate stop condition */
        I2C_GenerateStop(I2C_UNIT);
    }

    if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_STOP))
    {
        /* Disable Stop flag interrupt */
        I2C_IntCmd(I2C_UNIT, I2C_INT_STOP | I2C_INT_TX_EMPTY | I2C_INT_RX_FULL | I2C_INT_TX_CPLT | I2C_INT_NACK, Disable);
        I2C_ClearStatus(I2C_UNIT, I2C_FLAG_STOP);
        I2C_Cmd(I2C_UNIT, Disable);

        /* Communication finished */
        stcI2cCom.enComStatus = I2C_ComIdle;
    }
}

/**
 * @brief   I2C TXI(transfer buffer empty) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_TxEmpty_IrqHandler(void)
{
    if(stcI2cCom.u32DataIndex <= (stcI2cCom.u32Length - 1u))
    {
        I2C_WriteData(I2C_UNIT, BufRead(stcI2cCom.pBuf));
    }
    else
    {
        I2C_IntCmd(I2C_UNIT, I2C_INT_TX_EMPTY, Disable);
        I2C_IntCmd(I2C_UNIT, I2C_INT_TX_CPLT, Enable);
    }
}

/**
 * @brief   I2C RXI(receive buffer full) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_RxEnd_IrqHandler(void)
{
    if(stcI2cCom.u32Length >= 2U)
    {
        if(stcI2cCom.u32DataIndex == (stcI2cCom.u32Length - 2U))
        {
            I2C_AckConfig(I2C_UNIT, I2C_NACK);
        }
    }

    if(stcI2cCom.u32DataIndex == (stcI2cCom.u32Length - 1U))
    {
        /* Enable Stop flag interrupt */
        I2C_IntCmd(I2C_UNIT, I2C_INT_STOP, Enable);
        /* Disable TXI interrupt */
        I2C_IntCmd(I2C_UNIT, I2C_INT_RX_FULL, Disable);

        /* Generate stop condition */
        I2C_GenerateStop(I2C_UNIT);

        I2C_AckConfig(I2C_UNIT, I2C_ACK);
    }

    BufWrite(stcI2cCom.pBuf, I2C_ReadData(I2C_UNIT));
}

/**
 * @brief   I2C TEI(Transfer end) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_TxEnd_IrqHandler(void)
{
    I2C_IntCmd(I2C_UNIT, I2C_INT_TX_CPLT, Disable);

    if(stcI2cCom.u32DataIndex == 0u)
    {
        /* Indicate address send finished */
        if(Set == I2C_GetStatus(I2C_UNIT, I2C_FLAG_TRA))
        {
            /* If Address send receive ACK */
            if(Reset == I2C_GetStatus(I2C_UNIT, I2C_FLAG_ACKR))
            {
                /* Config tx buffer empty interrupt function*/
                I2C_IntCmd(I2C_UNIT, I2C_INT_TX_EMPTY, Enable);
                /* Need transfer first data here */
                I2C_WriteData(I2C_UNIT, BufRead(stcI2cCom.pBuf));
            }
            else
            {
                I2C_IntCmd(I2C_UNIT, I2C_INT_NACK, Disable);
                /* Generate stop if receive NACK */
                I2C_IntCmd(I2C_UNIT, I2C_INT_STOP, Enable);
                /* Generate stop condition */
                I2C_GenerateStop(I2C_UNIT);
            }
        }
    }
    else
    {
        /* Data Send finish */
        I2C_IntCmd(I2C_UNIT, I2C_INT_STOP, Enable);
        /* Generate stop condition */
        I2C_GenerateStop(I2C_UNIT);
    }
}

/**
 * @brief   static function for buffer write.
 * @param   [in]   au8Buf     Buffer pointer
 * @param   [in]   u8Data     The data to be write.
 * @retval  None
 */
static void BufWrite(uint8_t au8Buf[], uint8_t u8Data)
{
    if(stcI2cCom.u32DataIndex >= TEST_DATA_LEN)
    {
        /* error */
        for(;;)
        {
            ;
        }
    }
    au8Buf[stcI2cCom.u32DataIndex] = u8Data;
    stcI2cCom.u32DataIndex++;
}

/**
 * @brief   Static function for buffer read.
 * @param   [in]   au8Buf[]   Buffer pointer
 * @retval  uint8_t  The data read out from buffer.
 */
static uint8_t BufRead(uint8_t au8Buf[])
{
    uint8_t temp;
    if(stcI2cCom.u32DataIndex >= TEST_DATA_LEN)
    {
        /* error */
        for(;;)
        {
            ;
        }
    }
    temp = au8Buf[stcI2cCom.u32DataIndex];
    stcI2cCom.u32DataIndex++;

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
 * @brief  Main function of i2c_master_irq project
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
        u8TxBuf[i] = (uint8_t)i;
    }
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
    if(Ok != Master_Initialize())
    {
        /* Initialieze error*/
        BSP_LED_On(LED_RED);
        Peripheral_WP();

        for(;;)
        {
            ;
        }
    }

    /* Short press key SW1 */
    WaitKeyShortPress();

    /* I2C master data write */
    while(Ok != I2C_Master_Transmit_IT(u8TxBuf, TEST_DATA_LEN))
    {
        ;
    }

    /* Wait communicaiton finished*/
    while(I2C_ComBusy == stcI2cCom.enComStatus)
    {
        if(TIMEOUT == i)
        {
            /* Communication time out*/
            BSP_LED_Toggle(LED_RED);
            for(;;)
            {
                ;
            }
        }
        i++;
    }

    /* 5mS delay for device*/
    DDL_DelayMS(1U);

    while(Ok != I2C_Master_Receive_IT(u8RxBuf, TEST_DATA_LEN))
    {
        ;
    }

    i = 0UL;
    /* Wait communicaiton finished*/
    while(I2C_ComBusy == stcI2cCom.enComStatus)
    {
        if(TIMEOUT == i)
        {
            /* Communication time out*/
            BSP_LED_Toggle(LED_RED);
            for(;;)
            {
                ;
            }
        }
        i++;
    }

    /* Compare the data */
    for(i=0U; i<TEST_DATA_LEN; i++)
    {
        if(u8TxBuf[i] != u8RxBuf[i])
        {
            /* Data write error*/
            BSP_LED_On(LED_RED);
            Peripheral_WP();
            for(;;)
            {
                ;
            }
        }
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
