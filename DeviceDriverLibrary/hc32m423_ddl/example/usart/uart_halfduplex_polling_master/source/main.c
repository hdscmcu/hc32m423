/**
 *******************************************************************************
 * @file  usart/uart_halfduplex_polling_master/source/main.c
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
 * @addtogroup USART_UART_Halfduplex_Polling_Master
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
#define USART_MASTER_UNIT               (CM_USART2)
#define USART_FUNC_CLK_GATE             (CLK_FCG_UART2)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static en_flag_status_t KeyState(void);
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
 * @brief  Get key state
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Set: Released after key is pressed
 *           - Reset: Key isn't pressed
 */
static en_flag_status_t KeyState(void)
{
    en_flag_status_t enKeyState = Reset;

    if (Set == BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_GPIO))
    {
        DDL_DelayMS(20UL);

        if (Set == BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_GPIO))
        {
            while (Set == BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_GPIO))
            {
            }
            enKeyState = Set;
        }
    }

    return enKeyState;
}

/**
 * @brief  USART RX error process function.
 * @param  None
 * @retval None
 */
static void UartRxErrProcess(void)
{
    if (Set == USART_GetStatus(USART_MASTER_UNIT, (USART_FLAG_PARITY_ERR | USART_FLAG_FRAME_ERR | USART_FLAG_OVERRUN)))
    {
        if (Set == USART_GetStatus(USART_MASTER_UNIT, (USART_FLAG_PARITY_ERR | USART_FLAG_FRAME_ERR)))
        {
            (void)USART_ReadData(USART_MASTER_UNIT);
        }

        USART_ClearStatus(USART_MASTER_UNIT, (USART_FLAG_PARITY_ERR | \
                                              USART_FLAG_FRAME_ERR | \
                                              USART_FLAG_OVERRUN));
    }
}

/**
 * @brief  Main function of UART halfduplex polling master project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint8_t u8MasterRxData;
    uint8_t u8MasterTxData = 0U;
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

    /* Initialize LED. */
    BSP_LED_Init();

    /* Initialize UART for debug print function. */
    (void)DDL_PrintfInit();

    /* Configure USART TX pin. */
    GPIO_SetFunc(USART_TX_PORT, USART_TX_PIN, USART_TX_GPIO_FUNC);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(USART_FUNC_CLK_GATE, Enable);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Initialize UART function. */
    (void)USART_HalfDuplex_Init(USART_MASTER_UNIT, &stcUartInit);

    for (;;)
    {
        /* Wait key release */
        while (Reset == KeyState())
        {
        }

        /* Enable TX function && Disable RX function */
        USART_FuncCmd(USART_MASTER_UNIT, USART_RX, Disable);
        USART_FuncCmd(USART_MASTER_UNIT, USART_TX, Enable);

        /* Master unit send data */
        USART_WriteData(USART_MASTER_UNIT, (uint16_t)u8MasterTxData);

        /* Wait Tx complete */
        while (Reset == USART_GetStatus(USART_MASTER_UNIT, USART_FLAG_TX_CPLT))
        {
        }

        /* Enable RX function && Disable TX function*/
        USART_FuncCmd(USART_MASTER_UNIT, USART_RX, Enable);
        USART_FuncCmd(USART_MASTER_UNIT, USART_TX, Disable);

        /* Wait Rx data register no empty */
        while (Reset == USART_GetStatus(USART_MASTER_UNIT, USART_FLAG_RX_FULL))
        {
        }

        u8MasterRxData = (uint8_t)USART_ReadData(USART_MASTER_UNIT);

        if (u8MasterRxData == u8MasterTxData)
        {
            BSP_LED_Off(LED_RED);
            BSP_LED_Toggle(LED_GREEN);
        }
        else
        {
            BSP_LED_On(LED_RED);
            BSP_LED_Off(LED_GREEN);
        }

        (void)printf("Master send:%d; master receive:%d \r\n", u8MasterTxData, u8MasterRxData);

        u8MasterTxData++;

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
