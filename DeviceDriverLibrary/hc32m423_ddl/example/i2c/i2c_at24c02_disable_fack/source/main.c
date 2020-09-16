/**
 *******************************************************************************
 * @file  i2c/i2c_master_polling/source/main.c
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
 * @addtogroup I2C_At24c02
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define I2C_UNIT                        (CM_I2C)

/* Define E2PROM device address */
#define E2_ADDRESS                      (0x50U)
/* AT24C02 page length is 8byte*/
#define E2_PAGE_LEN                     (16U)

/* Define port and pin for SDA and SCL */
#define I2C_SCL_PORT                    (GPIO_PORT_7)
#define I2C_SCL_PIN                     (GPIO_PIN_5)
#define I2C_SDA_PORT                    (GPIO_PORT_7)
#define I2C_SDA_PIN                     (GPIO_PIN_6)

#define GENERATE_START                  (0x00U)
#define GENERATE_RESTART                (0x01U)

#define E2_ADDRESS_W                    (0x00U)
#define E2_ADDRESS_R                    (0x01U)

/* Define test address for read and write */
#define DATA_TEST_ADDR                  (0x00U)
/* Define Write and read data length for the example */
#define TEST_DATA_LEN                   (128U)
/* Define i2c baudrate */
#define I2C_BAUDRATE                    (400000UL)

#define KEY1_PORT                       (GPIO_PORT_0)
#define KEY1_PIN                        (GPIO_PIN_2)

#define TIMEOUT                         (0x15000U)

/**
 * Wait time for eeprom.
 * specification is 5ms, but you may enlarg it according to compilation options
 */
#define E2_WAIT_CNT                     (5UL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WP(void);
static void Peripheral_WE(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8TxBuf[TEST_DATA_LEN];
static uint8_t u8RxBuf[TEST_DATA_LEN];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Send Start condition.
 * @param  None
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Success
 *         @arg ErrorTimeout:       Time out
 */
static en_result_t E2_Start(void)
{
    return I2C_Start(I2C_UNIT,TIMEOUT);
}

/**
 * @brief  Send Restart condition.
 * @param  None
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Success
 *         @arg ErrorTimeout:       Time out
 */
static en_result_t E2_Restart(void)
{
    return I2C_Restart(I2C_UNIT,TIMEOUT);
}

/**
 * @brief  Send e2prom device address.
 * @param  [in] u8Addr              The slave address
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Success
 *         @arg ErrorTimeout:       Time out
 */
static en_result_t E2_SendAddr(uint8_t u8Addr)
{
    return I2C_AddrTrans(I2C_UNIT, u8Addr, TIMEOUT);
}

/**
 * @brief  Send data address to e2prom
 * @param  [in] u8DataAdr           Data address to be send
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Success
 *         @arg ErrorTimeout:       Time out
 */
static en_result_t E2_SendDataAdr(uint8_t u8DataAdr)
{
    return I2C_DataTrans(I2C_UNIT, &u8DataAdr, 1U, TIMEOUT);
}

/**
 * @brief  Send data to e2prom
 * @param  [in] pu8TxData           Pointer to the data buffer
 * @param  [in] u32Size             Data size
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Success
 *         @arg ErrorTimeout:       Time out
 *         @arg ErrorInvalidParameter: pTxData is NULL
 */
static en_result_t E2_WriteData(const uint8_t *pu8TxData, uint32_t u32Size)
{
    return I2C_DataTrans(I2C_UNIT, pu8TxData, u32Size, TIMEOUT);
}

/**
 * @brief  Receive data from e2prom
 * @param  [in] pu8RxData           Pointer to the data buffer
 * @param  [in] u32Size             Data size
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Success
 *         @arg ErrorTimeout:       Time out
 *         @arg ErrorInvalidParameter: pRxData is NULL
 */
static en_result_t E2_RevData(uint8_t *pu8RxData, uint32_t u32Size)
{
    return I2C_DataReceive(I2C_UNIT, pu8RxData, u32Size, TIMEOUT);
}

/**
 * @brief  General stop condition to e2prom
 * @param  None
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Success
 *         @arg ErrorTimeout:       Time out
 */
static en_result_t E2_Stop(void)
{
    return I2C_Stop(I2C_UNIT,TIMEOUT);
}

/**
 * @brief  Initialize the I2C peripheral for e2prom
 * @param  None
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Success
 *         @arg ErrorInvalidParameter:  Invalid parameter
 */
static en_result_t E2_Initialize(void)
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

    I2C_Cmd(I2C_UNIT, Enable);
    I2C_FastAckCmd(I2C_UNIT, Disable);

    return enRet;
}

/**
 * @brief   Judge the result. LED0 toggle when result is error status.
 * @param   [in]  enRet    Result to be judged
 * @retval  None
 */
static void JudgeResult(en_result_t enRet)
{
    if(Ok != enRet)
    {
        /* Data write error*/
        BSP_LED_On(LED_RED);
        Peripheral_WP();
        for(;;)
        {
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
 * @brief  Main function of i2c_at24c02 project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{

    uint32_t i;
    en_result_t enRet;

    /* Register write unprotected for some required peripherals. */
    Peripheral_WE();
    /* System clock Init */
    BSP_CLK_Init();
    /* LED init */
    BSP_LED_Init();

    /* Test buffer initialize */
    for(i=0UL; i<E2_PAGE_LEN; i++)
    {
        u8TxBuf[i] = (uint8_t)i+1U;
    }

    /* Initialize I2C port*/
    GPIO_SetFunc(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_FUNC_7_I2C);
    GPIO_SetFunc(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_FUNC_7_I2C);

    /* Enable I2C Peripheral*/
    CLK_FcgPeriphClockCmd(CLK_FCG_IIC, Enable);

    /* Initialize I2C peripheral and enable function*/
    if(Ok != E2_Initialize())
    {
        /* Initialieze error*/
        BSP_LED_On(LED_RED);
        Peripheral_WP();
        for(;;)
        {
            ;
        }
    }

    /* E2prom byte write*/
    enRet = E2_Start();
    JudgeResult(enRet);
    enRet = E2_SendAddr((uint8_t)(E2_ADDRESS<<1U)|E2_ADDRESS_W);
    JudgeResult(enRet);
    enRet = E2_SendDataAdr(DATA_TEST_ADDR);
    JudgeResult(enRet);
    enRet = E2_WriteData(u8TxBuf, 1U);
    JudgeResult(enRet);
    enRet = E2_Stop();
    JudgeResult(enRet);

    /* 5mS delay for e2prom*/
    DDL_DelayMS(E2_WAIT_CNT);

    /* E2prom random read*/
    enRet = E2_Start();
    JudgeResult(enRet);
    enRet = E2_SendAddr((uint8_t)(E2_ADDRESS<<1U)|E2_ADDRESS_W);
    JudgeResult(enRet);
    enRet = E2_SendDataAdr(DATA_TEST_ADDR);
    JudgeResult(enRet);

    enRet = E2_Restart();
    JudgeResult(enRet);
    enRet = E2_SendAddr((uint8_t)(E2_ADDRESS<<1U)|E2_ADDRESS_R);
    JudgeResult(enRet);
    enRet = E2_RevData(u8RxBuf, 1U);
    JudgeResult(enRet);
    enRet = E2_Stop();
    JudgeResult(enRet);

    /* Compare the data */
    if(0x01U != u8RxBuf[0])
    {
        /* e2prom byte write error*/
        for(;;)
        {
            DDL_DelayMS(500UL);
        }
    }

    /* 5mS delay for e2prom*/
    DDL_DelayMS(E2_WAIT_CNT);
    /* E2prom page write*/
    enRet = E2_Start();
    JudgeResult(enRet);
    enRet = E2_SendAddr((uint8_t)(E2_ADDRESS<<1U)|E2_ADDRESS_W);
    JudgeResult(enRet);
    enRet = E2_SendDataAdr(DATA_TEST_ADDR);
    JudgeResult(enRet);
    enRet = E2_WriteData(u8TxBuf, E2_PAGE_LEN);
    JudgeResult(enRet);
    enRet = E2_Stop();
    JudgeResult(enRet);

    /* 5mS delay for e2prom*/
    DDL_DelayMS(E2_WAIT_CNT);

    /* E2prom sequential read*/
    enRet = E2_Start();
    JudgeResult(enRet);
    enRet = E2_SendAddr((uint8_t)(E2_ADDRESS<<1U)|E2_ADDRESS_W);
    JudgeResult(enRet);
    enRet = E2_SendDataAdr(DATA_TEST_ADDR);
    JudgeResult(enRet);

    enRet = E2_Restart();
    JudgeResult(enRet);
    enRet = E2_SendAddr((uint8_t)(E2_ADDRESS<<1U)|E2_ADDRESS_R);
    JudgeResult(enRet);
    enRet = E2_RevData(u8RxBuf, E2_PAGE_LEN);
    JudgeResult(enRet);
    enRet = E2_Stop();
    JudgeResult(enRet);

    /* Compare the data */
    for(i=0UL; i<E2_PAGE_LEN; i++)
    {
        if(u8TxBuf[i] != u8RxBuf[i])
        {
            /* e2prom page write error*/
            for(;;)
            {
                DDL_DelayMS(500UL);
            }
        }
    }

    /* e2prom sample success*/
    /* Communication finished */
    BSP_LED_Off(LED_RED);
    BSP_LED_On(LED_GREEN);
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
