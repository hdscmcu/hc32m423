/**
 *******************************************************************************
 * @file  usart/uart_halfduplex_polling_slave/source/main.c
 * @brief This example demonstrates UART half-duplex data receive and transfer
 *        by polling mode.
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
 * @addtogroup USART_UART_Halfduplex_Polling_Slave
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* UART TX Port/Pin definition */
#define USART_TX_PORT                   (GPIO_PORT_B)
#define USART_TX_PIN                    (GPIO_PIN_5)      /* PB5: USART2_TX */
#define USART_TX_GPIO_FUNC              (GPIO_FUNC_5_USART)

/* UART unit definition */
#define USART_SLAVE_UNIT                (CM_USART2)
#define USART_FUNC_CLK_GATE             (CLK_FCG_UART2)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static void UartRxErrProcess(void);

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
    /* Unlock PWC, CLK registers, @ref PWC_REG_Write_Unlock_Code for details */
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
    /* Lock PWC, CLK registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  USART RX error process function.
 * @param  None
 * @retval None
 */
static void UartRxErrProcess(void)
{
    if (Set == USART_GetStatus(USART_SLAVE_UNIT, (USART_FLAG_PARITY_ERR | USART_FLAG_FRAME_ERR | USART_FLAG_OVERRUN)))
    {
        if (Set == USART_GetStatus(USART_SLAVE_UNIT, (USART_FLAG_PARITY_ERR | USART_FLAG_FRAME_ERR)))
        {
            (void)USART_ReadData(USART_SLAVE_UNIT);
        }

        USART_ClearStatus(USART_SLAVE_UNIT, (USART_FLAG_PARITY_ERR | \
                                             USART_FLAG_FRAME_ERR | \
                                             USART_FLAG_OVERRUN));
    }
}

/**
 * @brief  Main function of UART halfduplex polling slave project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint8_t u8SlaveRxData;
    const stc_usart_uart_init_t stcUartInit = {
        .u32Baudrate = 115200UL,
        .u32FirstBit = USART_FIRST_BIT_LSB,
        .u32StopBit = USART_STOPBIT_1BIT,
        .u32Parity = USART_PARITY_NONE,
        .u32DataWidth = USART_DATA_WIDTH_8BIT,
        .u32ClockMode = USART_INTERNCLK_NONE_OUTPUT,
        .u32ClockDiv = USART_CLK_DIV64,
        .u32OverSampleBit = USART_OVER_SAMPLE_8BIT,
        .u32StartBitPolarity = USART_START_BIT_FALLING,
    };

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize system clock. */
    BSP_CLK_Init();

    /* Configure USART TX pin. */
    GPIO_SetFunc(USART_TX_PORT, USART_TX_PIN, USART_TX_GPIO_FUNC);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(USART_FUNC_CLK_GATE, Enable);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Initialize UART function. */
    (void)USART_HalfDuplex_Init(USART_SLAVE_UNIT, &stcUartInit);

    /* Enable RX function */
    USART_FuncCmd(USART_SLAVE_UNIT, USART_RX, Enable);

    for (;;)
    {
        /* Wait slave unit Rx data register no empty */
        while (Reset == USART_GetStatus(USART_SLAVE_UNIT, USART_FLAG_RX_FULL))
        {
        }

        /* Slave unit receive data */
        u8SlaveRxData = (uint8_t)USART_ReadData(USART_SLAVE_UNIT);

        /* Enable slave RX function && Disable slave TX function*/
        USART_FuncCmd(USART_SLAVE_UNIT, USART_RX, Disable);
        USART_FuncCmd(USART_SLAVE_UNIT, USART_TX, Enable);

        /* Slave unit send data */
        USART_WriteData(USART_SLAVE_UNIT, (uint16_t)u8SlaveRxData);

        /* Wait slave unit Tx complete */
        while (Reset == USART_GetStatus(USART_SLAVE_UNIT, USART_FLAG_TX_CPLT))
        {
        }

        /* Enable slave RX function && Disable slave TX function*/
        USART_FuncCmd(USART_SLAVE_UNIT, USART_RX, Enable);
        USART_FuncCmd(USART_SLAVE_UNIT, USART_TX, Disable);

        /* USART error handle */
        UartRxErrProcess();
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
