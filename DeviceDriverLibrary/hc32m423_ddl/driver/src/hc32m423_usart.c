/**
 *******************************************************************************
 * @file  hc32m423_usart.c
 * @brief This file provides firmware functions to manage the USART(Universal
 *        Synchronous/Asynchronous Receiver Transmitter).
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
#include "hc32m423_usart.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_USART USART
 * @brief USART Driver Library
 * @{
 */

#if (DDL_USART_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup USART_Local_Macros USART Local Macros
 * @{
 */

/**
 * @defgroup USART_Check_Parameters_Validity USART Check Parameters Validity
 * @{
 */
#define IS_USART_UNIT(x)                                                       \
(   ((x) == CM_USART1)                          ||                             \
    ((x) == CM_USART2)                          ||                             \
    ((x) == CM_USART3)                          ||                             \
    ((x) == CM_USART4))

#define IS_USART_FUNCTION(x)                                                   \
(   ((x) != 0UL)                                &&                             \
    (((x) | USART_FUNCTION_MASK) == USART_FUNCTION_MASK))

#define IS_USART_FLAG(x)                                                       \
(   ((x) != 0UL)                                &&                             \
    (((x) | USART_FLAG_ALL) == USART_FLAG_ALL))

#define IS_USART_CLR_FLAG(x)                                                   \
(   ((x) != 0UL)                                &&                             \
    (((x) | USART_FLAG_CLR_ALL) == USART_FLAG_CLR_ALL))

#define IS_USART_TRANSMISSION_TYPE(x)                                          \
(   ((x) == USART_TRANS_ID)                     ||                             \
    ((x) == USART_TRANS_DATA))

#define IS_USART_PARITY(x)                                                     \
(   ((x) == USART_PARITY_ODD)                   ||                             \
    ((x) == USART_PARITY_EVEN)                  ||                             \
    ((x) == USART_PARITY_NONE))

#define IS_USART_DATA_WIDTH(x)                                                 \
(   ((x) == USART_DATA_WIDTH_8BIT)              ||                             \
    ((x) == USART_DATA_WIDTH_9BIT))

#define IS_USART_OVER_SAMPLE_BIT(x)                                            \
(   ((x) == USART_OVER_SAMPLE_8BIT)             ||                             \
    ((x) == USART_OVER_SAMPLE_16BIT))

#define IS_USART_FIRST_BIT(x)                                                  \
(   ((x) == USART_FIRST_BIT_MSB)                ||                             \
    ((x) == USART_FIRST_BIT_LSB))

#define IS_USART_START_BIT_POLARITY(x)                                         \
(   ((x) == USART_START_BIT_LOW)                ||                             \
    ((x) == USART_START_BIT_FALLING))

#define IS_USART_CLK_MD(x)                                                     \
(   ((x) == USART_EXTCLK)                       ||                             \
    ((x) == USART_INTERNCLK_OUTPUT)             ||                             \
    ((x) == USART_INTERNCLK_NONE_OUTPUT))

#define IS_USART_CLKSYNC_CLK_MD(x)                                             \
(   ((x) == USART_EXTCLK)                       ||                             \
    ((x) == USART_INTERNCLK_OUTPUT))

#define IS_USART_STOPBIT(x)                                                    \
(   ((x) == USART_STOPBIT_1BIT)                 ||                             \
    ((x) == USART_STOPBIT_2BIT))

#define IS_UART_DUPLEX_MD(x)                                                   \
(   ((x) == USART_HALF_DUPLEX)                  ||                             \
    ((x) == USART_FULL_DUPLEX))

#define IS_USART_HW_FLOWCTRL(x)                                                \
(   ((x) == USART_HW_FLOWCTRL_CTS)              ||                             \
    ((x) == USART_HW_FLOWCTRL_RTS))

#define IS_USART_CLK_DIV(x)                                                    \
(   ((x) == USART_CLK_DIV1)                     ||                             \
    ((x) == USART_CLK_DIV4)                     ||                             \
    ((x) == USART_CLK_DIV16)                    ||                             \
    ((x) == USART_CLK_DIV64))

#define IS_USART_DATA(x)                        ((x) <= 0x01FFUL)
/**
 * @}
 */

/**
 * @defgroup USART_function_Mask USART function mask definition
 * @{
 */
#define USART_FUNCTION_MASK                     (USART_RX          |           \
                                                 USART_TX          |           \
                                                 USART_INT_RX      |           \
                                                 USART_INT_TX_CPLT |           \
                                                 USART_INT_TX_EMPTY)
/**
 * @}
 */

/**
 * @defgroup USART_Data_Register USART Data Register
 * @{
 */
#define USART_TDRx(_UNITx_)    ((__IO uint16_t *)((uint32_t)(&((_UNITx_)->DR))))
#define USART_RDRx(_UNITx_)    ((__I uint16_t *)((uint32_t)(&((_UNITx_)->DR)) + 2UL))
/**
 * @}
 */

/**
 * @defgroup USART_Clk_Frequency USART Clk Frequency
 * @{
 */
#define USART_DIV(_UNITx_)                                                    \
(   1UL << (READ_REG32_BIT((_UNITx_)->PR, USART_PR_PSC) * 2UL))

#define PCLK_FREQ                                                              \
(   SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS))
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @addtogroup USART_Local_Functions
 * @{
 */
static en_result_t USART_WaitStatus(const CM_USART_TypeDef *USARTx,
                                    uint32_t u32Flag,
                                    en_flag_status_t enStatus,
                                    uint32_t u32Timeout);
static en_result_t UART_CalculateBaudrate(const CM_USART_TypeDef *USARTx,
                                            uint32_t u32UsartClock,
                                            uint32_t u32Baudrate,
                                            uint32_t *pu32BrrValue,
                                            float32_t *pf32Error);
static en_result_t ClockSync_CalculateBaudrate(const CM_USART_TypeDef *USARTx,
                                            uint32_t u32UsartClock,
                                            uint32_t u32Baudrate,
                                            uint32_t *pu32BrrValue,
                                            float32_t *pf32Error);
/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Functions USART Global Functions
 * @{
 */

/**
 * @brief  Initialize UART function.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] pstcUartInit        Pointer to a @ref stc_usart_uart_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcUartInit is NULL or calculating parameters is invalid
 */
en_result_t USART_UART_Init(CM_USART_TypeDef *USARTx,
                            const stc_usart_uart_init_t *pstcUartInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcUartInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_UNIT(USARTx));
        DDL_ASSERT(IS_USART_CLK_MD(pstcUartInit->u32ClockMode));
        DDL_ASSERT(IS_USART_PARITY(pstcUartInit->u32Parity));
        DDL_ASSERT(IS_USART_DATA_WIDTH(pstcUartInit->u32DataWidth));
        DDL_ASSERT(IS_USART_STOPBIT(pstcUartInit->u32StopBit));
        DDL_ASSERT(IS_USART_OVER_SAMPLE_BIT(pstcUartInit->u32OverSampleBit));
        DDL_ASSERT(IS_USART_FIRST_BIT(pstcUartInit->u32FirstBit));
        DDL_ASSERT(IS_USART_START_BIT_POLARITY(pstcUartInit->u32StartBitPolarity));
        DDL_ASSERT(IS_USART_HW_FLOWCTRL(pstcUartInit->u32HWFlowControl));

        /* Disbale TX/RX && clear flag */
        WRITE_REG32(USARTx->CR1, (USART_FLAG_CLR_ALL << USART_CR1_CPE_POS));

        /* Set CR2 */
        WRITE_REG32(USARTx->CR2, (pstcUartInit->u32ClockMode | pstcUartInit->u32StopBit));

        /* Set CR3 */
        WRITE_REG32(USARTx->CR3, pstcUartInit->u32HWFlowControl);

        /* Set CR1 */
        WRITE_REG32(USARTx->CR1, (pstcUartInit->u32Parity | \
                                  pstcUartInit->u32DataWidth | \
                                  pstcUartInit->u32OverSampleBit | \
                                  pstcUartInit->u32FirstBit | \
                                  pstcUartInit->u32StartBitPolarity));

        if (USART_EXTCLK != pstcUartInit->u32ClockMode)
        {
            DDL_ASSERT(IS_USART_CLK_DIV(pstcUartInit->u32ClockDiv));

            /* Set PR */
            WRITE_REG32(USARTx->PR, pstcUartInit->u32ClockDiv);

            /* Set baudrate */
            enRet = USART_SetBaudrate(USARTx, pstcUartInit->u32Baudrate, NULL);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Initialize UART half duplex function.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] pstcUartInit        Pointer to a @ref stc_usart_uart_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcUartInit is NULL or calculating parameters is invalid
 */
en_result_t USART_HalfDuplex_Init(CM_USART_TypeDef *USARTx,
                                    const stc_usart_uart_init_t *pstcUartInit)
{
    en_result_t enRet;

    enRet = USART_UART_Init(USARTx, pstcUartInit);
    if (Ok == enRet)
    {
        /* Set CR3: UART half duplex */
        SET_REG32_BIT(USARTx->CR3, USART_CR3_HDSEL);
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_usart_uart_init_t to default values.
 * @param  [out] pstcUartInit       Pointer to a @ref stc_usart_uart_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: The pointer pstcUartInit is NULL
 */
en_result_t USART_UART_StructInit(stc_usart_uart_init_t *pstcUartInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcUartInit)
    {
        pstcUartInit->u32Baudrate = 9600UL;
        pstcUartInit->u32ClockMode = USART_INTERNCLK_NONE_OUTPUT;
        pstcUartInit->u32ClockDiv = USART_CLK_DIV1;
        pstcUartInit->u32Parity = USART_PARITY_NONE;
        pstcUartInit->u32DataWidth = USART_DATA_WIDTH_8BIT;
        pstcUartInit->u32StopBit = USART_STOPBIT_1BIT;
        pstcUartInit->u32OverSampleBit = USART_OVER_SAMPLE_16BIT;
        pstcUartInit->u32FirstBit = USART_FIRST_BIT_LSB;
        pstcUartInit->u32StartBitPolarity = USART_START_BIT_FALLING;
        pstcUartInit->u32HWFlowControl = USART_HW_FLOWCTRL_RTS;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Initialize UART multiple processor function.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] pstcMultiProcessorInit    Pointer to a @ref stc_usart_multiprocessor_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcMultiProcessorInit is NULL or calculating parameters is invalid
 */
en_result_t USART_MultiProcessor_Init(CM_USART_TypeDef *USARTx,
                 const stc_usart_multiprocessor_init_t *pstcMultiProcessorInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcMultiProcessorInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_UNIT(USARTx));
        DDL_ASSERT(IS_USART_CLK_MD(pstcMultiProcessorInit->u32ClockMode));
        DDL_ASSERT(IS_USART_DATA_WIDTH(pstcMultiProcessorInit->u32DataWidth));
        DDL_ASSERT(IS_USART_STOPBIT(pstcMultiProcessorInit->u32StopBit));
        DDL_ASSERT(IS_USART_OVER_SAMPLE_BIT(pstcMultiProcessorInit->u32OverSampleBit));
        DDL_ASSERT(IS_USART_FIRST_BIT(pstcMultiProcessorInit->u32FirstBit));
        DDL_ASSERT(IS_USART_START_BIT_POLARITY(pstcMultiProcessorInit->u32StartBitPolarity));
        DDL_ASSERT(IS_USART_HW_FLOWCTRL(pstcMultiProcessorInit->u32HWFlowControl));

        /* Disbale TX/RX && clear flag */
        WRITE_REG32(USARTx->CR1, (USART_FLAG_CLR_ALL << USART_CR1_CPE_POS));

        /* Set CR2 */
        WRITE_REG32(USARTx->CR2, (USART_CR2_MPE | \
                                  pstcMultiProcessorInit->u32ClockMode | \
                                  pstcMultiProcessorInit->u32StopBit));

        /* Set CR3 */
        WRITE_REG32(USARTx->CR3, pstcMultiProcessorInit->u32HWFlowControl);

        /* Set CR1 */
        WRITE_REG32(USARTx->CR1, (pstcMultiProcessorInit->u32DataWidth | \
                                  pstcMultiProcessorInit->u32OverSampleBit | \
                                  pstcMultiProcessorInit->u32FirstBit | \
                                  pstcMultiProcessorInit->u32StartBitPolarity));

        if (USART_EXTCLK != pstcMultiProcessorInit->u32ClockMode)
        {
            DDL_ASSERT(IS_USART_CLK_DIV(pstcMultiProcessorInit->u32ClockDiv));

            /* Set PR */
            WRITE_REG32(USARTx->PR, pstcMultiProcessorInit->u32ClockDiv);

            /* Set baudrate */
            enRet = USART_SetBaudrate(USARTx, pstcMultiProcessorInit->u32Baudrate, NULL);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_usart_multiprocessor_init_t to default values.
 * @param  [out] pstcMultiProcessorInit       Pointer to a @ref stc_usart_multiprocessor_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: the pointer pstcMultiProcessorInit is NULL
 */
en_result_t USART_MultiProcessor_StructInit(stc_usart_multiprocessor_init_t *pstcMultiProcessorInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcMultiProcessorInit)
    {
        pstcMultiProcessorInit->u32Baudrate = 9600UL;
        pstcMultiProcessorInit->u32ClockMode = USART_INTERNCLK_NONE_OUTPUT;
        pstcMultiProcessorInit->u32ClockDiv = USART_CLK_DIV1;
        pstcMultiProcessorInit->u32DataWidth = USART_DATA_WIDTH_8BIT;
        pstcMultiProcessorInit->u32StopBit = USART_STOPBIT_1BIT;
        pstcMultiProcessorInit->u32OverSampleBit = USART_OVER_SAMPLE_16BIT;
        pstcMultiProcessorInit->u32FirstBit = USART_FIRST_BIT_LSB;
        pstcMultiProcessorInit->u32StartBitPolarity = USART_START_BIT_FALLING;
        pstcMultiProcessorInit->u32HWFlowControl = USART_HW_FLOWCTRL_RTS;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Initialize CLKSYNC function.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] pstcClockSyncInit   Pointer to a @ref stc_usart_clocksync_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcClockSyncInit is NULL or or calculating parameters is invalid
 */
en_result_t USART_ClockSync_Init(CM_USART_TypeDef *USARTx,
                                const stc_usart_clocksync_init_t *pstcClockSyncInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcClockSyncInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_UNIT(USARTx));
        DDL_ASSERT(IS_USART_CLKSYNC_CLK_MD(pstcClockSyncInit->u32ClockMode));
        DDL_ASSERT(IS_USART_FIRST_BIT(pstcClockSyncInit->u32FirstBit));
        DDL_ASSERT(IS_USART_HW_FLOWCTRL(pstcClockSyncInit->u32HWFlowControl));

        /* Disbale TX/RX && clear flag */
        WRITE_REG32(USARTx->CR1, (USART_FLAG_CLR_ALL << USART_CR1_CPE_POS));

        /* Set CR2 */
        WRITE_REG32(USARTx->CR2, pstcClockSyncInit->u32ClockMode);

        /* Set CR3 */
        WRITE_REG32(USARTx->CR3, pstcClockSyncInit->u32HWFlowControl);

        /* Set CR1 */
        WRITE_REG32(USARTx->CR1, (USART_CR1_MS | \
                                  pstcClockSyncInit->u32FirstBit | \
                                  USART_CR1_SBS));

        if (USART_EXTCLK != pstcClockSyncInit->u32ClockMode)
        {
            DDL_ASSERT(IS_USART_CLK_DIV(pstcClockSyncInit->u32ClockDiv));

            /* Set PR */
            WRITE_REG32(USARTx->PR, pstcClockSyncInit->u32ClockDiv);

            /* Set baudrate */
            enRet = USART_SetBaudrate(USARTx, pstcClockSyncInit->u32Baudrate, NULL);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_usart_clocksync_init_t to default values.
 * @param  [out] pstcClockSyncInit  Pointer to a @ref stc_usart_clocksync_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcClockSyncInit is NULL
 */
en_result_t USART_ClockSync_StructInit(stc_usart_clocksync_init_t *pstcClockSyncInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcClockSyncInit)
    {
        pstcClockSyncInit->u32Baudrate = 9600UL;
        pstcClockSyncInit->u32ClockMode = USART_INTERNCLK_NONE_OUTPUT;
        pstcClockSyncInit->u32ClockDiv = USART_CLK_DIV1;
        pstcClockSyncInit->u32FirstBit = USART_FIRST_BIT_LSB;
        pstcClockSyncInit->u32HWFlowControl = USART_HW_FLOWCTRL_RTS;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize USART function.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @retval None
 */
void USART_DeInit(CM_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    /* Configures the registers to reset value. */
    WRITE_REG32(USARTx->CR1, (USART_FLAG_CLR_ALL << USART_CR1_CPE_POS));
    WRITE_REG32(USARTx->PR, 0x00000000UL);
    WRITE_REG32(USARTx->BRR, 0x0000FF00UL);
    WRITE_REG32(USARTx->CR1, 0x80000000UL);
    WRITE_REG32(USARTx->CR2, 0x00000000UL);
    WRITE_REG32(USARTx->CR3, 0x00000000UL);
}

/**
 * @brief  Enable/disable the specified USART transmit/receive function and interrupt.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32Func             USART function type
 *         This parameter can be any composed value of the following values:
 *           @arg USART_RX:         USART RX function
 *           @arg USART_TX:         USART TX function
 *           @arg USART_INT_RX:     USART RX interrupt function
 *           @arg USART_INT_TX_CPLT:     USART transmission complete interrupt
 *           @arg USART_INT_TX_EMPTY:    Transmit data register empty interrupt
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the specified function and interrupt.
 *           @arg Disable:          Disable the specified function and interrupt.
 * @retval None
 */
void USART_FuncCmd(CM_USART_TypeDef *USARTx,
                        uint32_t u32Func,
                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_USART_FUNCTION(u32Func));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(USARTx->CR1, u32Func);
    }
    else
    {
        CLEAR_REG32_BIT(USARTx->CR1, u32Func);
    }
}

/**
 * @brief  Get USART function state.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32Func             USART function type
 *         This parameter can be one of the following values:
 *           @arg USART_RX:           USART RX function
 *           @arg USART_TX:           USART TX function
 *           @arg USART_INT_RX:       USART RX interrupt function
 *           @arg USART_INT_TX_CPLT:  USART transmission complete interrupt
 *           @arg USART_INT_TX_EMPTY: Transmit data register empty interrupt
 * @retval An en_functional_state_t enumeration value:
 *           - Enable: Enable function
 *           - Disable: Disable function
 */
en_functional_state_t USART_GetFuncState(const CM_USART_TypeDef *USARTx,
                                            uint32_t u32Func)
{
    /* Check parameters */
    DDL_ASSERT (IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_FUNCTION(u32Func));

    return ((READ_REG32_BIT(USARTx->CR1, u32Func) == 0UL) ? Disable : Enable);
}

/**
 * @brief  Get USART flag.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32Flag             USART flag
 *         This parameter can be any composed value of the following values:
 *           @arg USART_FLAG_OVERRUN:      Overrun error flag
 *           @arg USART_FLAG_RX_FULL:      Receive data register not empty flag
 *           @arg USART_FLAG_TX_CPLT:      Transmission complete flag
 *           @arg USART_FLAG_TX_EMPTY:     Transmit data register empty flag
 *           @arg USART_FLAG_FRAME_ERR:    Framing error flag
 *           @arg USART_FLAG_PARITY_ERR:   Parity error flag
 *           @arg USART_FLAG_MX_PROCESSOR: Receive processor ID flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t USART_GetStatus(const CM_USART_TypeDef *USARTx,
                                    uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_FLAG(u32Flag));

    return ((READ_REG32_BIT(USARTx->SR, u32Flag) == 0UL) ? Reset : Set);
}

/**
 * @brief  Clear USART flag.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32Flag             USART flag type
 *         This parameter can be any composed value of the following values:
 *           @arg USART_FLAG_OVERRUN:    Overrun error flag
 *           @arg USART_FLAG_FRAME_ERR:  Framing error flag
 *           @arg USART_FLAG_PARITY_ERR: Parity error flag
 * @retval None
 */
void USART_ClearStatus(CM_USART_TypeDef *USARTx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT (IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_CLR_FLAG(u32Flag));

    SET_REG32_BIT(USARTx->CR1, (u32Flag << USART_CR1_CPE_POS));
}

/**
 * @brief  Set USART parity.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32Parity           USART parity
 *         This parameter can be one of the following values:
 *           @arg USART_PARITY_NONE: Parity control disabled
 *           @arg USART_PARITY_ODD:  Parity control enabled and Odd Parity is selected
 *           @arg USART_PARITY_EVEN: Parity control enabled and Even Parity is selected
 * @retval None
 */
void USART_SetParity(CM_USART_TypeDef *USARTx, uint32_t u32Parity)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_PARITY(u32Parity));

    MODIFY_REG32(USARTx->CR1, (USART_CR1_PS | USART_CR1_PCE), u32Parity);
}

/**
 * @brief  Set USART bit direction.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32FirstBit           USART bit direction
 *         This parameter can be one of the following values:
 *           @arg USART_FIRST_BIT_MSB: MSB(Most Significant Bit)
 *           @arg USART_FIRST_BIT_LSB: LSB(Least Significant Bit)
 * @retval None
 */
void USART_SetFirstBit(CM_USART_TypeDef *USARTx, uint32_t u32FirstBit)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_FIRST_BIT(u32FirstBit));

    MODIFY_REG32(USARTx->CR1, USART_CR1_ML, u32FirstBit);
}

/**
 * @brief  Set USART stop bit.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32StopBit          USART stop bits
 *         This parameter can be one of the following values:
 *           @arg USART_STOPBIT_1BIT: 1 stop bit
 *           @arg USART_STOPBIT_2BIT: 2 stop bit
 * @retval None
 */
void USART_SetStopBit(CM_USART_TypeDef *USARTx, uint32_t u32StopBit)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_STOPBIT(u32StopBit));

    MODIFY_REG32(USARTx->CR2, USART_CR2_STOP, u32StopBit);
}

/**
 * @brief  Set USART data width.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32DataWidth        USART data width
 *         This parameter can be one of the following values:
 *           @arg USART_DATA_WIDTH_8BIT: 8 bits word width
 *           @arg USART_DATA_WIDTH_9BIT: 9 bits word width
 * @retval None
 */
void USART_SetDataWidth(CM_USART_TypeDef *USARTx, uint32_t u32DataWidth)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_DATA_WIDTH(u32DataWidth));

    MODIFY_REG32(USARTx->CR1, USART_CR1_M, u32DataWidth);
}

/**
 * @brief  Set USART oversampling bits.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32OverSampleBit    USART over sample bit
 *         This parameter can be one of the following values:
 *           @arg USART_OVER_SAMPLE_8BIT:  Oversampling by 8 bit
 *           @arg USART_OVER_SAMPLE_16BIT: Oversampling by 16 bit
 * @retval None
 */
void USART_SetOverSmapleBit(CM_USART_TypeDef *USARTx, uint32_t u32OverSampleBit)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_OVER_SAMPLE_BIT(u32OverSampleBit));

    MODIFY_REG32(USARTx->CR1, USART_CR1_OVER8, u32OverSampleBit);
}

/**
 * @brief  Get USART oversampling bits.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_OVER_SAMPLE_8BIT:  Oversampling by 8 bits
 *           @arg USART_OVER_SAMPLE_16BIT: Oversampling by 16 bits
 */
uint32_t USART_GetOverSampleBit(const CM_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    return READ_REG32_BIT(USARTx->CR1, USART_CR1_OVER8);
}

/**
 * @brief  Set USART start bit detect polarity.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32Polarity         USART start bit detect polarity
 *         This parameter can be one of the following values:
 *           @arg USART_START_BIT_LOW:     Detect RX pin low level
 *           @arg USART_START_BIT_FALLING: Detect RX pin falling edge
 * @retval None
 */
void USART_SetStartBitPolarity(CM_USART_TypeDef *USARTx, uint32_t u32Polarity)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_START_BIT_POLARITY(u32Polarity));

    MODIFY_REG32(USARTx->CR1, USART_CR1_SBS, u32Polarity);
}

/**
 * @brief  Set USART transmission type.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32Type             USART transmission content type
 *         This parameter can be one of the following values:
 *           @arg USART_TRANS_ID:   USART transmission content type is processor ID
 *           @arg USART_TRANS_DATA: USART transmission content type is frame data
 * @retval None
 */
void USART_SetTransType(CM_USART_TypeDef *USARTx, uint32_t u32Type)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_TRANSMISSION_TYPE(u32Type));

    MODIFY_REG32(USARTx->DR, USART_DR_MPID, u32Type);
}

/**
 * @brief  Set USART clock prescaler division.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32ClockDiv         USART clock prescaler division.
 *         This parameter can be one of the following values:
 *           @arg USART_CLK_DIV1:   PCLK
 *           @arg USART_CLK_DIV4:   PCLK/4
 *           @arg USART_CLK_DIV16:  PCLK/16
 *           @arg USART_CLK_DIV64:  PCLK/64
 * @retval None
 * @note   The PCLK division function is valid only when clock source is PCLK
 */
void USART_SetClockDiv(CM_USART_TypeDef *USARTx, uint32_t u32ClockDiv)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_CLK_DIV(u32ClockDiv));

    MODIFY_REG32(USARTx->PR, USART_PR_PSC, u32ClockDiv);
}

/**
 * @brief  Get USART clock prescaler division.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_CLK_DIV1:   PCLK
 *           @arg USART_CLK_DIV4:   PCLK/4
 *           @arg USART_CLK_DIV16:  PCLK/16
 *           @arg USART_CLK_DIV64:  PCLK/64
 * @note   The PCLK division function is valid only when clock source is PCLK
 */
uint32_t USART_GetClockDiv(const CM_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    return READ_REG32_BIT(USARTx->PR, (USART_PR_PSC_1 | USART_PR_PSC_0));
}

/**
 * @brief  Set USART clock mode.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32ClockMode        USART clock mode
 *         This parameter can be one of the following values:
 *           @arg USART_EXTCLK:                Select external clock source.
 *           @arg USART_INTERNCLK_OUTPUT:      Select internal clock source and output clock.
 *           @arg USART_INTERNCLK_NONE_OUTPUT: Select internal clock source and don't output clock
 * @retval None
 */
void USART_SetClockMode(CM_USART_TypeDef *USARTx, uint32_t u32ClockMode)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_CLK_MD(u32ClockMode));

    MODIFY_REG32(USARTx->CR2, USART_CR2_CLKC, u32ClockMode);
}

/**
 * @brief  Get USART clock mode.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_EXTCLK:                Select external clock source.
 *           @arg USART_INTERNCLK_OUTPUT:      Select internal clock source and output clock.
 *           @arg USART_INTERNCLK_NONE_OUTPUT: Select internal clock source and don't output clock
 */
uint32_t USART_GetClockMode(const CM_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    return READ_REG32_BIT(USARTx->CR2, USART_CR2_CLKC);
}

/**
 * @brief  Enable or disable USART noise filter.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the USART noise filter.
 *           @arg Disable:          Disable the USART noise filter.
 * @retval None
 */
void USART_FilterCmd(CM_USART_TypeDef *USARTx,
                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(USARTx->CR1, USART_CR1_NFE);
    }
    else
    {
        CLEAR_REG32_BIT(USARTx->CR1, USART_CR1_NFE);
    }
}

/**
 * @brief  Enable or disable USART silence.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable the USART silence.
 *           @arg Disable:          Disable the USART silence.
 * @retval None
 */
void USART_SilenceCmd(CM_USART_TypeDef *USARTx,
                            en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(USARTx->CR1, USART_CR1_SLME);
    }
    else
    {
        CLEAR_REG32_BIT(USARTx->CR1, USART_CR1_SLME);
    }
}

/**
 * @brief  Set UART hardware flow control CTS/RTS selection.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32HWFlowControl    USART hardware flow control CTS/RTS selection
 *         This parameter can be one of the following values:
 *           @arg USART_HW_FLOWCTRL_CTS: UART hardware flow control CTS mode
 *           @arg USART_HW_FLOWCTRL_RTS: UART hardware flow control RTS mode
 * @retval None
 */
void USART_SetHWFlowControl(CM_USART_TypeDef *USARTx,
                            uint32_t u32HWFlowControl)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_HW_FLOWCTRL(u32HWFlowControl));

    MODIFY_REG32(USARTx->CR3, USART_CR3_CTSE, u32HWFlowControl);
}

/**
 * @brief  Set USART baudrate.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32Baudrate         UART baudrate
 * @param  [out] pf32Error          E(%) baudrate error rate
 * @retval An en_result_t enumeration value:
 *           - Ok: Set successfully
 *           - ErrorInvalidParameter: Calculating baudrate parameters are invalid
 */
en_result_t USART_SetBaudrate(CM_USART_TypeDef *USARTx,
                                uint32_t u32Baudrate,
                                float32_t *pf32Error)
{
    float f32Error;
    uint32_t u32UsartClk;
    uint32_t u32UsartDiv;
    uint32_t u32BrrValue = 0UL;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameter */
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    /* Get USART clock frequency */
    u32UsartDiv = USART_DIV(USARTx);
    u32UsartClk = PCLK_FREQ / u32UsartDiv;

    if ((u32Baudrate > 0UL) && (u32UsartClk > 0UL))
    {
        if (0UL == READ_REG32_BIT(USARTx->CR1, USART_CR1_MS))
        {
            /* UART */
            enRet = UART_CalculateBaudrate(USARTx, u32UsartClk, u32Baudrate, &u32BrrValue, &f32Error);
        }
        else
        {
            /* Clock synchronization */
            enRet = ClockSync_CalculateBaudrate(USARTx, u32UsartClk, u32Baudrate, &u32BrrValue, &f32Error);
        }

        if (Ok == enRet)
        {
            if (NULL != pf32Error)
            {
                *pf32Error = f32Error;
            }

            WRITE_REG32(USARTx->BRR, u32BrrValue);
        }
    }

    return enRet;
}

/**
 * @brief  USART receive data.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @retval Receive data
 */
uint16_t USART_ReadData(const CM_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    return READ_REG16(*USART_RDRx(USARTx));
}

/**
 * @brief  USART send data.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 ** \param [in] u16Data             Transmit data
 * @retval None
 */
void USART_WriteData(CM_USART_TypeDef *USARTx, uint16_t u16Data)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_DATA(u16Data));

    WRITE_REG32(USARTx->DR, u16Data);
}

/**
 * @brief  USART send processor ID.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 ** \param [in] u16ID               Processor ID
 * @retval None
 */
void USART_WriteID(CM_USART_TypeDef *USARTx, uint16_t u16ID)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_DATA(u16ID));

    WRITE_REG32(USARTx->DR, (USART_DR_MPID | (uint32_t)u16ID));
}

/**
 * @brief  UART transmit data in polling mode.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [out] pvBuf              The pointer to data transmitted buffer
 * @param  [in]  u32Len             Amount of frame to be sent.
 * @param  [in]  u32Timeout         Timeout duration
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                      No errors occurred
 *   @arg  ErrorTimeout:            Communicate timeout.
 *   @arg  ErrorInvalidParameter:   u32Len value is 0 or au8Buf is NULL
 * @note   The function will block until the communication is completed if
 *         u32Timeout value is USART_TIMEOUT_MAX
 */
en_result_t USART_UART_Trans(CM_USART_TypeDef *USARTx,
                                    const void *pvBuf,
                                    uint32_t u32Len,
                                    uint32_t u32Timeout)
{
    uint32_t u32Count;
    uint32_t u32DataWidth;
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != pvBuf) && (u32Len > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_UNIT(USARTx));

        u32DataWidth = READ_REG32_BIT(USARTx->CR1, USART_CR1_M);

        if ((USART_DATA_WIDTH_8BIT == u32DataWidth) ||
            ((USART_DATA_WIDTH_9BIT == u32DataWidth) && IS_ADDRESS_ALIGN_HALFWORD(pvBuf)))
        {
            for (u32Count = 0UL; u32Count < u32Len; u32Count++)
            {
                if (u32DataWidth == USART_DATA_WIDTH_8BIT)
                {
                    WRITE_REG32(USARTx->DR, ((const uint8_t *)pvBuf)[u32Count]);
                }
                else
                {
                    WRITE_REG32(USARTx->DR, ((const uint16_t *)pvBuf)[u32Count]);
                }

                enRet = USART_WaitStatus(USARTx, USART_FLAG_TX_EMPTY, Set, u32Timeout);
                if (Ok != enRet)
                {
                    break;
                }
            }

            if (Ok == enRet)
            {
                enRet = USART_WaitStatus(USARTx, USART_FLAG_TX_CPLT, Set, u32Timeout);
            }
        }
    }

    return enRet;
}


/**
 * @brief  UART receive data in polling mode.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [out] pvBuf              The pointer to data received buffer
 * @param  [in]  u32Len             Amount of frame to be received.
 * @param  [in]  u32Timeout         Timeout duration
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                      No errors occurred
 *   @arg  ErrorTimeout:            Communicate timeout.
 *   @arg  ErrorInvalidParameter:   u32Len value is 0 or au8Buf is NULL
 * @note   The function will block until the communication is completed if
 *         u32Timeout value is USART_TIMEOUT_MAX
 */
en_result_t USART_UART_Receive(const CM_USART_TypeDef *USARTx,
                                    void *pvBuf,
                                    uint32_t u32Len,
                                    uint32_t u32Timeout)
{
    uint16_t u16Temp;
    uint32_t u32Count;
    uint32_t u32DataWidth;
    __I uint16_t *USART_RDR;
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != pvBuf) && (u32Len > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_UNIT(USARTx));

        USART_RDR = USART_RDRx(USARTx);
        u32DataWidth = READ_REG32_BIT(USARTx->CR1, USART_CR1_M);

        if ((USART_DATA_WIDTH_8BIT == u32DataWidth) ||
            ((USART_DATA_WIDTH_9BIT == u32DataWidth) && IS_ADDRESS_ALIGN_HALFWORD(pvBuf)))
        {
            for (u32Count = 0UL; u32Count < u32Len; u32Count++)
            {
                enRet = USART_WaitStatus(USARTx, USART_FLAG_RX_FULL, Set, u32Timeout);
                if (Ok == enRet)
                {
                    u16Temp = READ_REG16(*USART_RDR);

                    if (USART_DATA_WIDTH_8BIT == u32DataWidth)
                    {
                        ((uint8_t *)pvBuf)[u32Count] = (uint8_t)(u16Temp&0xFFU);
                    }
                    else
                    {
                        ((uint16_t *)pvBuf)[u32Count] = (uint16_t)(u16Temp&0x1FFU);
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }

    return enRet;
}

/**
 * @brief  Clock sync transmit && receive data in polling mode.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] au8Buf              The pointer to data transmitted buffer
 * @param  [in] u32Len              Amount of data to be transmitted.
 * @param  [in] u32Timeout          Timeout duration
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                      No errors occurred
 *   @arg  ErrorTimeout:            Communicate timeout.
 *   @arg  ErrorInvalidParameter:   u32Len value is 0 or au8Buf is NULL
 * @note   The function will block until the communication is completed if
 *         u32Timeout value is USART_TIMEOUT_MAX
 */
en_result_t USART_ClockSync_Trans(CM_USART_TypeDef *USARTx,
                                    const uint8_t au8Buf[],
                                    uint32_t u32Len,
                                    uint32_t u32Timeout)
{
    uint32_t i;
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != au8Buf) && (u32Len > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_UNIT(USARTx));

        for (i = 0UL; i < u32Len; i++)
        {
            WRITE_REG32(USARTx->DR, au8Buf[i]);

            /* Wait TX buffer empty. */
            enRet = USART_WaitStatus(USARTx, USART_FLAG_TX_EMPTY, Set, u32Timeout);
            if (Ok == enRet)
            {
                if (USART_GetFuncState(USARTx, USART_RX) == Enable)
                {
                    enRet = USART_WaitStatus(USARTx, USART_FLAG_RX_FULL, Set, u32Timeout);
                    if (Ok == enRet)
                    {
                        (void)USART_ReadData(USARTx);
                    }
                }
            }

            if (Ok != enRet)
            {
                break;
            }
        }

        if (Ok == enRet)
        {
            enRet = USART_WaitStatus(USARTx, USART_FLAG_TX_CPLT, Set, u32Timeout);
        }
    }

    return enRet;
}

/**
 * @brief  Clock sync receive data in polling mode.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [out] au8Buf             The pointer to data received buffer
 * @param  [in] u32Len              Amount of data to be sent and received.
 * @param  [in] u32Timeout          Timeout duration
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                      No errors occurred
 *   @arg  ErrorTimeout:            Communicate timeout.
 *   @arg  ErrorInvalidParameter:   u32Len value is 0 or au8Buf is NULL
 * @note   The function will block until the communication is completed if
 *         u32Timeout value is USART_TIMEOUT_MAX
 */
en_result_t USART_ClockSync_Receive(CM_USART_TypeDef *USARTx,
                                    uint8_t au8Buf[],
                                    uint32_t u32Len,
                                    uint32_t u32Timeout)
{
    uint32_t i;
    __I uint16_t *USART_RDR;
    en_functional_state_t enTX;
    en_functional_state_t enMasterMode;
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != au8Buf) && (u32Len > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_UNIT(USARTx));

        enRet = Ok;
        USART_RDR = USART_RDRx(USARTx);
        enTX = (READ_REG32_BIT(USARTx->CR1, USART_TX) == 0UL) ? Disable : Enable;
        enMasterMode = (USART_EXTCLK == READ_REG32_BIT(USARTx->CR2, USART_CR2_CLKC)) ? Disable:Enable;

        for (i = 0UL; i < u32Len; i++)
        {
            if ((Enable == enMasterMode) || (Enable == enTX))
            {
                WRITE_REG32(USARTx->DR, 0xFFUL);

                /* Wait TX buffer empty. */
                enRet = USART_WaitStatus(USARTx, USART_FLAG_TX_EMPTY, Set, u32Timeout);
            }

            if (Ok == enRet)
            {
                enRet = USART_WaitStatus(USARTx, USART_FLAG_RX_FULL, Set, u32Timeout);
                if (Ok == enRet)
                {
                    au8Buf[i] = (uint8_t)READ_REG16(*USART_RDR);
                }
            }

            if (Ok != enRet)
            {
                break;
            }
        }

        if (Ok == enRet)
        {
            enRet = USART_WaitStatus(USARTx, USART_FLAG_TX_CPLT, Set, u32Timeout);
        }
    }

    return enRet;
}

/**
 * @brief  Clock sync transmit && receive data in polling mode.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] au8TxBuf            The pointer to data transmitted buffer
 * @param  [out] au8RxBuf           The pointer to data received buffer
 * @param  [in] u32Len              Amount of data to be sent and received.
 * @param  [in] u32Timeout          Timeout duration
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                      No errors occurred
 *   @arg  ErrorTimeout:            Communicate timeout.
 *   @arg  ErrorInvalidParameter:   u32Len value is 0
 * @note   If au8TxBuf is NULL, dummy data(0xFF) will transmit and the received
           data will be stored in the buffer pointed by au8RxBuf.
 * @note   The function will block until the communication is completed if
 *         u32Timeout value is USART_TIMEOUT_MAX
 */
en_result_t USART_ClockSync_TransReceive(CM_USART_TypeDef *USARTx,
                                    const uint8_t au8TxBuf[],
                                    uint8_t au8RxBuf[],
                                    uint32_t u32Len,
                                    uint32_t u32Timeout)
{
    uint32_t i;
    uint8_t u8Temp;
    __IO const uint16_t *USART_RDR;
    en_result_t enRet = ErrorInvalidParameter;

    if (u32Len > 0UL)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_UNIT(USARTx));

        USART_RDR = USART_RDRx(USARTx);

        for (i = 0UL; i < u32Len; i++)
        {
            if (NULL != au8TxBuf)
            {
                WRITE_REG32(USARTx->DR, au8TxBuf[i]);
            }
            else
            {
                WRITE_REG32(USARTx->DR, 0xFFUL);
            }

            /* Wait TX buffer empty. */
            enRet = USART_WaitStatus(USARTx, USART_FLAG_TX_EMPTY, Set, u32Timeout);
            if (Ok == enRet)
            {
                enRet = USART_WaitStatus(USARTx, USART_FLAG_RX_FULL, Set, u32Timeout);
                if (Ok == enRet)
                {
                    u8Temp = (uint8_t)READ_REG16(*USART_RDR);
                    if (NULL != au8RxBuf)
                    {
                        au8RxBuf[i] = u8Temp;
                    }
                }
            }

            if (Ok != enRet)
            {
                break;
            }
        }

        if (Ok == enRet)
        {
            enRet = USART_WaitStatus(USARTx, USART_FLAG_TX_CPLT, Set, u32Timeout);
        }
    }

    return enRet;
}

/**
 * @}
 */

/**
 * @defgroup USART_Local_Functions USART Local Functions
 * @{
 */

/**
 * @brief  Try to wait the expected status of specified flags
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32Flag             USART flag
 *         This parameter can be one of the following values:
 *           @arg USART_FLAG_OVERRUN:      Overrun error flag
 *           @arg USART_FLAG_RX_FULL:      Receive data register not empty flag
 *           @arg USART_FLAG_TX_CPLT:      Transmission complete flag
 *           @arg USART_FLAG_TX_EMPTY:     Transmit data register empty flag
 *           @arg USART_FLAG_FRAME_ERR:    Framing error flag
 *           @arg USART_FLAG_PARITY_ERR:   Parity error flag
 *           @arg USART_FLAG_MX_PROCESSOR: Receive processor ID flag
 * @param  [in] enStatus            Expected status
 *         This parameter can be one of the following values:
 *         @arg Set:                Wait flag set
 *         @arg Reset:              Wait flag reset
 * @param  [in] u32Timeout          Maximum count of trying to get status
 * @retval An en_result_t enumeration value:
 *         @arg Ok:                 Wait the expected status of the specified flags
 *         @arg ErrorTimeout:       Wait timeout
 * @note   Block waiting if u32Timeout value is USART_TIMEOUT_MAX
 */
static en_result_t USART_WaitStatus(const CM_USART_TypeDef *USARTx,
                                    uint32_t u32Flag,
                                    en_flag_status_t enStatus,
                                    uint32_t u32Timeout)
{
    en_result_t enRet = Ok;
    __IO uint32_t u32TimeoutCount = 0UL;

    /* Check parameters */
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_FLAG(u32Flag));

    while (USART_GetStatus(USARTx, u32Flag) != enStatus)
    {
        /* Block checking flag if timeout value is USART_TIMEOUT_MAX */
        if ((u32TimeoutCount > u32Timeout) && (u32Timeout < USART_TIMEOUT_MAX))
        {
            enRet = ErrorTimeout;
            break;
        }

        u32TimeoutCount++;
    }

    return enRet;
}

/**
 * @brief  Calculate baudrate for UART mode.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32UsartClock       USART clock
 * @param  [in] u32Baudrate         UART baudrate
 * @param  [out] pu32BrrValue       Pointer to buffer for BRR register value
 * @param  [out] pf32Error          E(%) baudrate error rate
 * @retval An en_result_t enumeration value:
 *           - Ok: Calculate successfully
 *           - ErrorInvalidParameter: Calculating baudrate parameters are invalid
 */
static en_result_t UART_CalculateBaudrate(const CM_USART_TypeDef *USARTx,
                                            uint32_t u32UsartClock,
                                            uint32_t u32Baudrate,
                                            uint32_t *pu32BrrValue,
                                            float32_t *pf32Error)
{
    uint32_t B;
    uint32_t C;
    uint32_t OVER8;
    uint32_t DIV_Integer;
    float32_t f32Error;
    uint32_t u32Temp;
    en_result_t enRet = ErrorInvalidParameter;

    if (u32Baudrate > 0UL)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_UNIT(USARTx));

        B = u32Baudrate;
        C = u32UsartClock;
        OVER8 = (0UL != READ_REG32_BIT(USARTx->CR1, USART_CR1_OVER8)) ? 1UL : 0UL;

        /* UART Baudrate Calculation Formula */
        /* B = C / (8 * (2 - OVER8) * (DIV_Integer + 1)) */
        DIV_Integer = ((((C * 10UL) / (B * 8UL * (2UL - OVER8))) + 5UL) / 10UL) - 1UL;

        if (DIV_Integer <= 0xFFUL)
        {
            *pu32BrrValue = (DIV_Integer << USART_BRR_DIV_INTEGER_POS);

            if (NULL != pf32Error)
            {
                /* UART Baudrate Error Calculation Formula */
                /* E(%) = C / (8 * (2 - OVER8) * (DIV_Integer + 1) * B) - 1 */
                u32Temp = (8UL * (2UL - OVER8) * (DIV_Integer + 1UL) * B);
                f32Error = (float32_t)(((float64_t)C) / (float64_t)u32Temp) - 1.0F;

                *pf32Error = f32Error;
            }

            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Calculate baudrate for clock synchronization mode.
 * @param  [in] USARTx              Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:        USART unit 1 instance register base
 *           @arg CM_USART2:        USART unit 2 instance register base
 *           @arg CM_USART3:        USART unit 3 instance register base
 *           @arg CM_USART4:        USART unit 4 instance register base
 * @param  [in] u32UsartClock       USART clock
 * @param  [in] u32Baudrate         UART baudrate
 * @param  [out] pu32BrrValue       Pointer to buffer for BRR register value
 * @param  [out] pf32Error          E(%) baudrate error rate
 * @retval An en_result_t enumeration value:
 *           - Ok: Calculate successfully
 *           - ErrorInvalidParameter: Calculating baudrate parameters are invalid
 */
static en_result_t ClockSync_CalculateBaudrate(const CM_USART_TypeDef *USARTx,
                                                uint32_t u32UsartClock,
                                                uint32_t u32Baudrate,
                                                uint32_t *pu32BrrValue,
                                                float32_t *pf32Error)
{
    uint32_t B;
    uint32_t C;
    uint32_t DIV_Integer;
    float32_t f32Error;
    uint32_t u32Temp;
    en_result_t enRet = ErrorInvalidParameter;

    if (u32Baudrate > 0UL)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_UNIT(USARTx));

        if (0UL == READ_REG32_BIT(USARTx->CR1, USART_CR1_OVER8))
        {
            B = u32Baudrate;
            C = u32UsartClock;

            /* Clock Sync Baudrate Calculation Formula */
            /* B = C / (4 * (DIV_Integer + 1)) */
            DIV_Integer = ((((C * 10UL) / (B * 4UL)) + 5UL) / 10UL) - 1UL;

            if (DIV_Integer <= 0xFFUL)
            {
                *pu32BrrValue = (DIV_Integer << USART_BRR_DIV_INTEGER_POS);

                if (NULL != pf32Error)
                {
                    /* Clock Sync Baudrate Error Calculation Formula */
                    /* E(%) = C / (4 * (DIV_Integer + 1) * B) - 1 */
                    u32Temp = (4UL * (DIV_Integer + 1UL) * B);
                    f32Error = (float32_t)(((float64_t)C) / (float64_t)u32Temp) - 1.0F;

                    *pf32Error = f32Error;
                }

                enRet = Ok;
            }
        }
    }

    return enRet;
}

/**
 * @}
 */

#endif /* DDL_USART_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
