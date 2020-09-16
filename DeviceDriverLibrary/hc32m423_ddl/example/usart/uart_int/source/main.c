/**
 *******************************************************************************
 * @file  usart/uart_int/source/main.c
 * @brief This example demonstrates UART data receive and transfer by interrupt.
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
 * @addtogroup USART_UART_Interrupt
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief  Ring buffer structure definition
 */
typedef struct
{
    uint16_t u16Capacity;
    __IO uint16_t u16UsedSize;
    uint16_t u16In;
    uint16_t u16Out;
    uint8_t  au8Buf[500];
} stc_ring_buf_t;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* UART RX/TX Port/Pin definition */
#define USART_RX_PORT                   (GPIO_PORT_7)
#define USART_RX_PIN                    (GPIO_PIN_1)      /* P71: USART3_RX */
#define USART_RX_GPIO_FUNC              (GPIO_FUNC_5_USART)

#define USART_TX_PORT                   (GPIO_PORT_7)
#define USART_TX_PIN                    (GPIO_PIN_2)      /* P72: USART3_TX */
#define USART_TX_GPIO_FUNC              (GPIO_FUNC_5_USART)

/* UART unit definition */
#define USART_UNIT                      (CM_USART3)
#define USART_FUNC_CLK_GATE             (CLK_FCG_UART3)

/* UART unit interrupt definition */
#define USART_RX_ERR_INT_SRC            (INT_USART3_EI)
#define USART_RX_ERR_IRQn               (INT000_IRQn)

#define USART_RXNE_INT_SRC              (INT_USART3_RI)
#define USART_RXNE_IRQn                 (INT001_IRQn)

#define USART_TXE_INT_SRC               (INT_USART3_TI)
#define USART_TXE_IRQn                  (INT002_IRQn)

#define USART_TC_INT_SRC                (INT_USART3_TCI)
#define USART_TC_IRQn                   (INT003_IRQn)

/* Ring buffer size */
#define IS_RING_BUF_EMPYT(x)            (0U == ((x)->u16UsedSize))

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
static en_result_t RingBufWrite(stc_ring_buf_t *pstcBuf, uint8_t u8Data);
static en_result_t RingBufRead(stc_ring_buf_t *pstcBuf, uint8_t *pu8Data);
static void InstalIrqHandler(const stc_irq_signin_config_t *pstcConfig,
                                    uint32_t u32Priority);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static stc_ring_buf_t m_stcRingBuf = {
    .u16In = 0,
    .u16Out = 0,
    .u16UsedSize = 0,
    .u16Capacity = sizeof (m_stcRingBuf.au8Buf),
};

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
 * @brief  USART transmit data register empty IRQ callback.
 * @param  None
 * @retval None
 */
static void USART_TxEmpty_IrqCallback(void)
{
    uint8_t u8Data = 0U;

    if (Ok == RingBufRead(&m_stcRingBuf, &u8Data))
    {
        USART_WriteData(USART_UNIT, (uint16_t)u8Data);
    }

    if (IS_RING_BUF_EMPYT(&m_stcRingBuf))
    {
        USART_FuncCmd(USART_UNIT, USART_INT_TX_EMPTY, Disable);
        USART_FuncCmd(USART_UNIT, USART_INT_TX_CPLT, Enable);
    }
}

/**
 * @brief  USART transmit complete IRQ callback.
 * @param  None
 * @retval None
 */
static void USART_TxComplete_IrqCallback(void)
{
    USART_FuncCmd(USART_UNIT, (USART_TX | USART_INT_TX_CPLT), Disable);
}

/**
 * @brief  USART RX IRQ callback
 * @param  None
 * @retval None
 */
static void USART_Rx_IrqCallback(void)
{
    const uint16_t u16Data = USART_ReadData(USART_UNIT);

    (void)RingBufWrite(&m_stcRingBuf, (uint8_t)u16Data);
}

/**
 * @brief  USART error IRQ callback.
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
 * @brief  Write ring buffer.
 * @param  [in] pstcBuf              Pointer to a @ref stc_ring_buf_t structure
 * @param  [in] u8Data                  Data to write
 * @retval An en_result_t enumeration value:
 *           - Ok: Write success.
 *           - ErrorBufferFull: Buffer is full.
 */
static en_result_t RingBufWrite(stc_ring_buf_t *pstcBuf, uint8_t u8Data)
{
    en_result_t enRet = Ok;

    if (pstcBuf->u16UsedSize >= pstcBuf->u16Capacity)
    {
        enRet = ErrorBufferFull;
    }
    else
    {
        pstcBuf->au8Buf[pstcBuf->u16In] = u8Data;
        pstcBuf->u16In++;
        pstcBuf->u16In %= pstcBuf->u16Capacity;
        pstcBuf->u16UsedSize++;
    }

    return enRet;
}

/**
 * @brief  Write ring buffer.
 * @param  [in] pstcBuf              Pointer to a @ref stc_ring_buf_t structure
 * @param  [in] pu8Data                 Pointer to data buffer to read
 * @retval An en_result_t enumeration value:
 *           - Ok: Write success.
 *           - ErrorBufferEmpty: Buffer is empty.
 */
static en_result_t RingBufRead(stc_ring_buf_t *pstcBuf, uint8_t *pu8Data)
{
    en_result_t enRet = ErrorBufferEmpty;

    if (pstcBuf->u16UsedSize > 0U)
    {
        *pu8Data = pstcBuf->au8Buf[pstcBuf->u16Out];
        pstcBuf->u16Out++;
        pstcBuf->u16Out %= pstcBuf->u16Capacity;
        pstcBuf->u16UsedSize--;
        enRet = Ok;
    }

    return enRet;
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
 * @brief  Main function of UART interrupt project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
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

    /* Register RX IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = USART_RXNE_IRQn;
    stcIrqConfig.enIntSrc = USART_RXNE_INT_SRC;
    stcIrqConfig.pfnCallback = &USART_Rx_IrqCallback;
    InstalIrqHandler(&stcIrqConfig, DDL_IRQ_PRI00);

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

    /* Enable RX function */
    USART_FuncCmd(USART_UNIT, (USART_RX | USART_INT_RX), Enable);

    for (;;)
    {
        if (!IS_RING_BUF_EMPYT(&m_stcRingBuf))
        {
            USART_FuncCmd(USART_UNIT, (USART_TX | USART_INT_TX_EMPTY), Enable);
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
