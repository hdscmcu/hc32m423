/**
 *******************************************************************************
 * @file  usart/uart_polling/source/main.c
 * @brief This example demonstrates UART data receive and transfer by polling.
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
 * @addtogroup USART_UART_Polling
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* USART RX/TX Port/Pin definition */
#define USART_RX_PORT                   (GPIO_PORT_7)
#define USART_RX_PIN                    (GPIO_PIN_1)      /* P71: USART3_RX */
#define USART_RX_GPIO_FUNC              (GPIO_FUNC_5_USART)

#define USART_TX_PORT                   (GPIO_PORT_7)
#define USART_TX_PIN                    (GPIO_PIN_2)      /* P72: USART3_TX */
#define USART_TX_GPIO_FUNC              (GPIO_FUNC_5_USART)

/* USART unit definition */
#define USART_UNIT                      (CM_USART3)
#define USART_FUNC_CLK_GATE             (CLK_FCG_UART3)

/* USART interrupt definition */
#define USART_RX_ERR_INT_SRC            (INT_USART3_EI)
#define USART_RX_ERR_IRQn               (INT000_IRQn)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static void USART_RxErr_IrqCallback(void);

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
 * @brief  USART RX error IRQ callback.
 * @param  None
 * @retval None
 */
static void USART_RxErr_IrqCallback(void)
{
    if (Set == USART_GetStatus(USART_UNIT, (USART_FLAG_PARITY_ERR | USART_FLAG_FRAME_ERR)))
    {
        (void)USART_ReadData(USART_UNIT);
    }

    USART_ClearStatus(USART_UNIT, (USART_FLAG_PARITY_ERR | \
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
 * @brief  Main function of UART polling project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    __IO uint16_t u16RxData;
    stc_irq_signin_config_t stcIrqConfig;
    const stc_usart_uart_init_t stcUartInit = {
        .u32Baudrate = 115200UL,
        .u32FirstBit = USART_FIRST_BIT_LSB,
        .u32StopBit = USART_STOPBIT_1BIT,
        .u32Parity = USART_PARITY_NONE,
        .u32DataWidth = USART_DATA_WIDTH_8BIT,
        .u32ClockMode = USART_INTERNCLK_NONE_OUTPUT,
        .u32ClockDiv = USART_CLK_DIV1,
        .u32OverSampleBit = USART_OVER_SAMPLE_8BIT,
        .u32StartBitPolarity = USART_START_BIT_FALLING,
    };

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize system clock. */
    BSP_CLK_Init();

    /* Initialize LED. */
    BSP_LED_Init();

    /* Configure USART RX/TX pin. */
    GPIO_SetFunc(USART_RX_PORT, USART_RX_PIN, USART_RX_GPIO_FUNC);
    GPIO_SetFunc(USART_TX_PORT, USART_TX_PIN, USART_TX_GPIO_FUNC);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(USART_FUNC_CLK_GATE, Enable);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Initialize UART function. */
    if (Ok != USART_UART_Init(USART_UNIT, &stcUartInit))
    {
        BSP_LED_On(LED_RED);
        for (;;)
        {
        }
    }

    /* Register error IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = USART_RX_ERR_IRQn;
    stcIrqConfig.enIntSrc = USART_RX_ERR_INT_SRC;
    stcIrqConfig.pfnCallback = &USART_RxErr_IrqCallback;
    InstalIrqHandler(&stcIrqConfig, DDL_IRQ_PRI_DEFAULT);

    /* Enable RX/TX function */
    USART_FuncCmd(USART_UNIT, (USART_RX | USART_INT_RX | USART_TX), Enable);

    for (;;)
    {
        if (Set == USART_GetStatus(USART_UNIT, USART_FLAG_RX_FULL))     /* Wait Rx data register no empty */
        {
            u16RxData = USART_ReadData(USART_UNIT);

            while (Reset == USART_GetStatus(USART_UNIT, USART_FLAG_TX_EMPTY)) /* Wait Tx data register empty */
            {
            }

            USART_WriteData(USART_UNIT, u16RxData);
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
