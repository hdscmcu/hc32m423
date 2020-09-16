/**
 *******************************************************************************
 * @file  usart/uart_dma/source/main.c
 * @brief This example demonstrates UART data receive and transfer by DMA.
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
 * @addtogroup USART_UART_DMA
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* DMA Unit/Channel/Interrupt definition */
#define DMA_UNIT                        (CM_DMA)
#define DMA_CH                          (DMA_CH0)
#define DMA_EVT_SRC                     (EVT_USART3_RI)
#define DMA_FUNC_CLK_GATE               (CLK_FCG_DMA | CLK_FCG_AOS)

/* UART unit definition */
#define USART_UNIT                      (CM_USART3)
#define USART_FUNC_CLK_GATE             (CLK_FCG_UART3)

/* UART unit interrupt definition */
#define USART_RX_ERR_INT_SRC            (INT_USART3_EI)
#define USART_RX_ERR_IRQn               (INT000_IRQn)

/* UART RX/TX Port/Pin definition */
#define USART_RX_PORT                   (GPIO_PORT_7)
#define USART_RX_PIN                    (GPIO_PIN_1)      /* P71: USART3_RX */
#define USART_RX_GPIO_FUNC              (GPIO_FUNC_5_USART)

#define USART_TX_PORT                   (GPIO_PORT_7)
#define USART_TX_PIN                    (GPIO_PIN_2)      /* P72: USART3_TX */
#define USART_TX_GPIO_FUNC              (GPIO_FUNC_5_USART)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static en_result_t DmaConfig(void);

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
 * @brief  Initialize DMA.
 * @param  None
 * @retval en_result_t
 */
static en_result_t DmaConfig(void)
{
    en_result_t enRet;
    stc_dma_init_t stcDmaInit;

    /* DMA&AOS FCG enable */
    CLK_FcgPeriphClockCmd(DMA_FUNC_CLK_GATE, Enable);

    (void)DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32BlockSize = 1UL;
    stcDmaInit.u32TransCount = 0UL;
    stcDmaInit.u32DataWidth = DMA_DATA_WIDTH_8BIT;
    stcDmaInit.u32DestAddr = (uint32_t)(&USART_UNIT->DR);
    stcDmaInit.u32SrcAddr = ((uint32_t)(&USART_UNIT->DR) + 2UL);
    stcDmaInit.u32SrcAddrMode = DMA_SRC_ADDR_MD_FIX;
    stcDmaInit.u32DestAddrMode = DMA_DEST_ADDR_MD_FIX;
    enRet = DMA_Init(DMA_UNIT, DMA_CH, &stcDmaInit);
    if (Ok == enRet)
    {
        /* Set DMA trigger source */
        DMA_SetTriggerSrc(DMA_UNIT, DMA_CH, DMA_EVT_SRC);

        /* DMA channel enable */
        DMA_ChCmd(DMA_UNIT, DMA_CH, Enable);

        /* DMA module enable */
        DMA_Cmd(DMA_UNIT, Enable);
    }

    return enRet;
}

/**
 * @brief  Main function of UART interrupt project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
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

    /* DMA config. */
    (void)DmaConfig();

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

    /* Enable RX/TX function */
    USART_FuncCmd(USART_UNIT, (USART_RX | USART_TX), Enable);

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
