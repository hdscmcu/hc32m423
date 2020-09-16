/**
 *******************************************************************************
 * @file  usart/uart_halfduplex_int_slave/source/main.c
 * @brief This example demonstrates UART half-duplex data receive and transfer
 *        by interrupt mode.
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
 * @addtogroup USART_UART_Halfduplex_Interrupt_Slave
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

/* UART unit interrupt definition */
#define USART_RX_ERR_INT_SRC            (INT_USART2_EI)
#define USART_RX_ERR_IRQn               (INT000_IRQn)

#define USART_RXNE_INT_SRC              (INT_USART2_RI)
#define USART_RXNE_IRQn                 (INT001_IRQn)

#define USART_TXE_INT_SRC               (INT_USART2_TI)
#define USART_TXE_IRQn                  (INT002_IRQn)

#define USART_TC_INT_SRC                (INT_USART2_TCI)
#define USART_TC_IRQn                   (INT003_IRQn)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static void USART_TxEmpty_IrqCallback(void);
static void USART_TxComplete_IrqCallback(void);
static void USART_Rx_IrqCallback(void);
static void USART_RxErr_IrqCallback(void);
static void InstalIrqHandler(const stc_irq_signin_config_t *pstcConfig,
                                    uint32_t u32Priority);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t m_u8UartSlaveRxData = 0U;

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
 * @brief  UART slave unit TX Complete IRQ callback.
 * @param  None.
 * @retval None
 */
static void USART_TxEmpty_IrqCallback(void)
{
    USART_WriteData(USART_SLAVE_UNIT, (uint16_t)m_u8UartSlaveRxData);

    /* Disable TX empty interrupt function */
    USART_FuncCmd(USART_SLAVE_UNIT, USART_INT_TX_EMPTY, Disable);

    /* Enable TC interrupt function */
    USART_FuncCmd(USART_SLAVE_UNIT, USART_INT_TX_CPLT, Enable);
}

/**
 * @brief  UART slave unit TX Complete IRQ callback.
 * @param  None.
 * @retval None
 */
static void USART_TxComplete_IrqCallback(void)
{
    /* Disable TX & TC interrupt function*/
    USART_FuncCmd(USART_SLAVE_UNIT, (USART_TX | USART_INT_TX_CPLT), Disable);

    /* Enable RX & RX no empty interrupt function*/
    USART_FuncCmd(USART_SLAVE_UNIT, (USART_RX | USART_INT_RX), Enable);
}

/**
 * @brief  UART slave unit RX IRQ callback.
 * @param  None
 * @retval None
 */
static void USART_Rx_IrqCallback(void)
{
    m_u8UartSlaveRxData = (uint8_t)USART_ReadData(USART_SLAVE_UNIT);

    /* Disable RX & RX no empty interrupt function */
    USART_FuncCmd(USART_SLAVE_UNIT, (USART_RX | USART_INT_RX), Disable);

    /* Enable TX & TX Empty interrupt function*/
    USART_FuncCmd(USART_SLAVE_UNIT, (USART_TX | USART_INT_TX_EMPTY), Enable);
}

/**
 * @brief  UART slave RX error IRQ callback.
 * @param  None
 * @retval None
 */
static void USART_RxErr_IrqCallback(void)
{
    if (Set == USART_GetStatus(USART_SLAVE_UNIT, (USART_FLAG_PARITY_ERR | USART_FLAG_FRAME_ERR)))
    {
        (void)USART_ReadData(USART_SLAVE_UNIT);
    }

    USART_ClearStatus(USART_SLAVE_UNIT, (USART_FLAG_PARITY_ERR | \
                                         USART_FLAG_FRAME_ERR | \
                                         USART_FLAG_OVERRUN));
}

/**
 * @brief  Instal IRQ handler.
 * @param  [in] pstcConfig      Pointer to struct @ref stc_irq_signin_config_t
 * @param  [in] u32Priority     Interrupt priority
 * @retval None
 */
static void InstalIrqHandler(const stc_irq_signin_config_t *pstcConfig,
                                    uint32_t u32Priority)
{
    if (NULL != pstcConfig)
    {
        (void)INTC_IrqSignIn(pstcConfig);
        NVIC_ClearPendingIRQ(pstcConfig->enIRQn);
        NVIC_SetPriority(pstcConfig->enIRQn, u32Priority);
        NVIC_EnableIRQ(pstcConfig->enIRQn);
    }
}

/**
 * @brief  Main function of UART halfduplex interrupt slave project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_irq_signin_config_t stcIrqConfig;
    const stc_usart_uart_init_t stcUartInit = {
        .u32Baudrate = 19200,
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

    /* Initialize USART half-duplex function. */
    (void)USART_HalfDuplex_Init(USART_SLAVE_UNIT, &stcUartInit);

    /* Register RX IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = USART_RXNE_IRQn;
    stcIrqConfig.enIntSrc = USART_RXNE_INT_SRC;
    stcIrqConfig.pfnCallback = &USART_Rx_IrqCallback;
    InstalIrqHandler(&stcIrqConfig, DDL_IRQ_PRI00);

    /* Register RX error IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = USART_RX_ERR_IRQn;
    stcIrqConfig.enIntSrc = USART_RX_ERR_INT_SRC;
    stcIrqConfig.pfnCallback = &USART_RxErr_IrqCallback;
    InstalIrqHandler(&stcIrqConfig, DDL_IRQ_PRI_DEFAULT);

    /* Register TX IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = USART_TXE_IRQn;
    stcIrqConfig.enIntSrc = USART_TXE_INT_SRC;
    stcIrqConfig.pfnCallback = &USART_TxEmpty_IrqCallback;
    InstalIrqHandler(&stcIrqConfig, DDL_IRQ_PRI_DEFAULT);

    /* Register TC IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = USART_TC_IRQn;
    stcIrqConfig.enIntSrc = USART_TC_INT_SRC;
    stcIrqConfig.pfnCallback = &USART_TxComplete_IrqCallback;
    InstalIrqHandler(&stcIrqConfig, DDL_IRQ_PRI_DEFAULT);

    /* Enable RX function && RX interrupt function */
    USART_FuncCmd(USART_SLAVE_UNIT, (USART_RX | USART_INT_RX), Enable);

    for (;;)
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
