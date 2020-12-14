/**
 *******************************************************************************
 * @file  hc32m423_utility.c
 * @brief This file provides utility functions for DDL.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-15       CDT             First version
   2020-12-03       CDT             Fixed SysTick_Delay function overflow handling
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
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_UTILITY UTILITY
 * @brief DDL Utility Driver
 * @{
 */

#if (DDL_UTILITY_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup UTILITY_Local_Macros UTILITY Local Macros
 * @{
 */

#if (DDL_PRINT_ENABLE == DDL_ON)
/**
 * @defgroup DDL UART channel/fcg/pin/baudrate definition
 * @{
 */
#define DDL_UART_CH                     (CM_USART3)
#define DDL_UART_PWC_FCG                (CMU_FCG_USART3)
#define DDL_UART_GPIO_TX_PFSR           (CM_GPIO->PFSR72)  /* P72: USART3_TX */
#define DDL_UART_GPIO_TX_FUNC           (5U)               /* GPIO function: USART3_TX */
#define DDL_UART_BAUDRATE               (115200UL)
/**
 * @}
 */
#endif

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
 * @addtogroup UTILITY_Local_Functions UTILITY Local Functions
 * @{
 */

#if (DDL_PRINT_ENABLE == DDL_ON)

static en_result_t UartPutChar(CM_USART_TypeDef *USARTx, char cData);
static en_result_t UartCalculateBaudrate(const CM_USART_TypeDef *USARTx,
                                            uint32_t u32Baudrate,
                                            uint32_t *pu32ClockDiv,
                                            uint32_t *pu32BrrValue,
                                            float32_t *pf32Error);
#endif

/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup UTILITY_Local_Variables UTILITY Local Variables
 * @{
 */

static uint32_t m_u32TickStep = 0UL;
static __IO uint32_t m_u32TickCount = 0UL;

/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup UTILITY_Global_Functions UTILITY Global Functions
 * @{
 */

/**
 * @brief Delay function, delay ms approximately
 * @param [in] u32Count                 ms
 * @retval None
 */
void DDL_DelayMS(uint32_t u32Count)
{
    __IO uint32_t i;
    const uint32_t u32Cycle = HCLK_VALUE / 10000UL;

    for (; u32Count > 0UL; u32Count--)
    {
        i = u32Cycle;
        while (i-- > 0UL)
        {
            ;
        }
    }
}

/**
 * @brief Delay function, delay us approximately
 * @param [in] u32Count                 us
 * @retval None
 */
void DDL_DelayUS(uint32_t u32Count)
{
    __IO uint32_t i;
    const uint32_t u32Cycle = HCLK_VALUE / 10000000UL;

    for (; u32Count > 0UL; u32Count--)
    {
        i = u32Cycle;
        while (i-- > 0UL)
        {
            ;
        }
    }
}

/**
 * @brief This function Initializes the interrupt frequency of the SysTick.
 * @param [in] u32Freq                  SysTick interrupt frequency (1 to 1000).
 * @retval An en_result_t enumeration value:
 *           - Ok: SysTick Initializes succeed
 *           - Error: SysTick Initializes failed
 */
__WEAKDEF en_result_t SysTick_Init(uint32_t u32Freq)
{
    en_result_t enRet = Error;

    if ((0UL != u32Freq) && (u32Freq <= 1000UL))
    {
        m_u32TickStep = 1000UL / u32Freq;
        /* Configure the SysTick interrupt */
        if (0UL == SysTick_Config(HCLK_VALUE / u32Freq))
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief This function provides minimum delay (in milliseconds).
 * @param [in] u32Delay                 Delay specifies the delay time.
 * @retval None
 */
__WEAKDEF void SysTick_Delay(uint32_t u32Delay)
{
    const uint32_t tickMax = 0xFFFFFFFFUL - (0xFFFFFFFFUL % m_u32TickStep);
    const uint32_t tickStart = SysTick_GetTick();
    uint32_t tickEnd;

    /* Add a freq to guarantee minimum wait */
    if ((u32Delay >= tickMax) || ((tickMax - u32Delay) < m_u32TickStep))
    {
        tickEnd = tickMax;
    }
    else
    {
        tickEnd = u32Delay + m_u32TickStep;
    }

    while ((SysTick_GetTick() - tickStart) < tickEnd)
    {
    }
}

/**
 * @brief This function is called to increment a global variable "u32TickCount".
 * @note  This variable is incremented in SysTick ISR.
 * @param None
 * @retval None
 */
__WEAKDEF void SysTick_IncTick(void)
{
    m_u32TickCount += m_u32TickStep;
}

/**
 * @brief Provides a tick value in millisecond.
 * @param None
 * @retval Tick value
 */
__WEAKDEF uint32_t SysTick_GetTick(void)
{
    return m_u32TickCount;
}

/**
 * @brief Suspend SysTick increment.
 * @param None
 * @retval None
 */
__WEAKDEF void SysTick_Suspend(void)
{
    /* Disable SysTick Interrupt */
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

/**
 * @brief Resume SysTick increment.
 * @param None
 * @retval None
 */
__WEAKDEF void SysTick_Resume(void)
{
    /* Enable SysTick Interrupt */
    SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}

#ifdef __DEBUG
/**
 * @brief DDL assert error handle function
 * @param [in] file                     Point to the current assert the wrong file.
 * @param [in] line                     Point line assert the wrong file in the current.
 * @retval None
 */
__WEAKDEF void DDL_AssertHandler(const char *file, int line)
{
    /* Users can re-implement this function to print information */
#if (DDL_PRINT_ENABLE == DDL_ON)
    (void)printf("Wrong parameters value: file %s on line %d\r\n", file, line);
#endif

    for (;;)
    {
        ;
    }
}
#endif /* __DEBUG */

#if (DDL_PRINT_ENABLE == DDL_ON)

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
/**
 * @brief  Re-target fputc function.
 * @param  [in] ch
 * @param  [in] f
 * @retval int32_t
 */
int32_t fputc(int32_t ch, FILE *f)
{
    (void)f;  /* Prevent unused argument compilation warning */

    return (Ok == UartPutChar(DDL_UART_CH, (char)ch)) ? ch: -1;
}

#elif defined ( __GNUC__ ) && !defined (__CC_ARM)
/**
 * @brief  Re-target _write function.
 * @param  [in] fd
 * @param  [in] data
 * @param  [in] size
 * @retval int32_t
 */
int32_t _write(int fd, char data[], int32_t size)
{
    int32_t i = -1;

    if (NULL != data)
    {
        (void)fd;  /* Prevent unused argument compilation warning */

        for (i = 0; i < size; i++)
        {
            if (Ok != UartPutChar(DDL_UART_CH, data[i]))
            {
                break;
            }
        }
    }

    return i ? i : -1;
}

#else
/**
 * @brief  Re-target fputc function.
 * @param  [in] ch
 * @param  [in] f
 * @retval int32_t
 */
int32_t fputc(int32_t ch, FILE *f)
{
    (void)f;  /* Prevent unused argument compilation warning */

    return (Ok == UartPutChar(DDL_UART_CH, (char)ch)) ? ch: -1;
}
#endif

/**
 * @brief  Initialize UART for debug printf function
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - Error: Don't permit write the GPIO configuration register or set baudrate unsuccessfully
 */
en_result_t DDL_PrintfInit(void)
{
    uint32_t u32ClockDiv;
    uint32_t u32BrrValue;
    en_result_t enRet = Error;

    /* Check whether permit write GPIO register */
    if (0U != READ_REG16_BIT(CM_GPIO->PWPR, GPIO_PWPR_WE))
    {
        /* Configure USART TX pin. */
        MODIFY_REG16(DDL_UART_GPIO_TX_PFSR, GPIO_PFSR_FSEL, DDL_UART_GPIO_TX_FUNC);

        /* Enable USART function clock gate */
        CLEAR_REG32_BIT(CM_CMU->FCG, DDL_UART_PWC_FCG);

        /***********************************************************************
         * Configure UART
         ***********************************************************************
         * Baud rate: 115200
         * Bit direction: LSB
         * Data bits: 8
         * Stop bits: 1
         * Parity: None
         * Sampling bits: 8
         **********************************************************************/
        /* Set CR1 */
        WRITE_REG32(DDL_UART_CH->CR1, (USART_CR1_CPE | \
                                       USART_CR1_CORE | \
                                       USART_CR1_CFE | \
                                       USART_CR1_OVER8 | \
                                       USART_CR1_NFE | \
                                       USART_CR1_SBS));

        /* Set CR2: reset value */
        WRITE_REG32(DDL_UART_CH->CR2, 0x00UL);

        /* Set CR3: reset value */
        WRITE_REG32(DDL_UART_CH->CR3, 0x00UL);

        /* Set baudrate */
        enRet = UartCalculateBaudrate(DDL_UART_CH, \
                                      DDL_UART_BAUDRATE, \
                                      &u32ClockDiv, \
                                      &u32BrrValue, \
                                      NULL);
        if (Ok == enRet)
        {
            /* Set clock prescaler */
            WRITE_REG32(DDL_UART_CH->PR, u32ClockDiv);

            /* Set USART_BRR register value */
            WRITE_REG32(DDL_UART_CH->BRR, u32BrrValue);

            /* Enable TX function */
            SET_REG32_BIT(DDL_UART_CH->CR1, USART_CR1_TE);
        }
    }

    return enRet;
}
#endif /* DDL_PRINT_ENABLE */

/**
 * @}
 */

/**
 * @defgroup UTILITY_Local_Functions UTILITY Local Functions
 * @{
 */
#if (DDL_PRINT_ENABLE == DDL_ON)

/**
 * @brief  UART transmit.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:            USART unit 1 instance register base
 *           @arg CM_USART2:            USART unit 2 instance register base
 *           @arg CM_USART3:            USART unit 3 instance register base
 *           @arg CM_USART4:            USART unit 4 instance register base
 * @param  [in] cData                   The data for transmitting
 * @retval An en_result_t enumeration value:
 *           - Ok: Send successfully
 *           - ErrorTimeout: Send timeout
 */
static en_result_t UartPutChar(CM_USART_TypeDef *USARTx, char cData)
{
    uint32_t u32TxEmpty;
    en_result_t enRet = Ok;
    __IO uint32_t u32Timeout = (HCLK_VALUE / DDL_UART_BAUDRATE);

    /* Wait TX data register empty */
    do
    {
        u32Timeout--;
        u32TxEmpty = READ_REG32_BIT(USARTx->SR, USART_SR_TXE);
    } while ((u32Timeout > 0UL) && (0UL == u32TxEmpty));

    if (0UL != u32TxEmpty)
    {
        WRITE_REG32(USARTx->DR, (uint32_t)cData);
    }
    else
    {
        enRet = ErrorTimeout;
    }

    return enRet;
}

/**
 * @brief  Set UART baudrate.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USART1:            USART unit 1 instance register base
 *           @arg CM_USART2:            USART unit 2 instance register base
 *           @arg CM_USART3:            USART unit 3 instance register base
 *           @arg CM_USART4:            USART unit 4 instance register base
 * @param  [in] u32Baudrate             UART baudrate
 * @param  [out] pu32ClockDiv           Pointer to buffer for USART clock division value
 * @param  [out] pu32BrrValue           Pointer to buffer for BRR register value
 * @param  [out] pf32Error              E(%) baudrate error rate
 * @retval An en_result_t enumeration value:
 *           - Ok: Set successfully
 *           - Error: Baudrate set unsuccessfully
 */
static en_result_t UartCalculateBaudrate(const CM_USART_TypeDef *USARTx,
                                            uint32_t u32Baudrate,
                                            uint32_t *pu32ClockDiv,
                                            uint32_t *pu32BrrValue,
                                            float32_t *pf32Error)
{
    uint32_t B;
    uint32_t C = 0UL;
    uint32_t OVER8;
    uint32_t DIV_Integer = 0UL;
    uint32_t u32CR1;
    uint32_t PCLK;
    uint32_t u32PCLKDiv;
    uint32_t u32Temp;
    float32_t f32Error;
    en_result_t enRet = ErrorInvalidParameter;

    if (u32Baudrate > 0UL)
    {
        u32CR1 = READ_REG32(USARTx->CR1);
        if (0UL == (u32CR1 & USART_CR1_MS))
        {
            B = u32Baudrate;
            OVER8 = ((u32CR1 & USART_CR1_OVER8) != 0UL) ? 1UL : 0UL;

            PCLK = (SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS));

            for (u32PCLKDiv = 0UL; u32PCLKDiv <= USART_PR_PSC; u32PCLKDiv++)
            {
                C = (PCLK / (1UL << (u32PCLKDiv * 2UL)));

                /* UART Mode Calculation Formula */
                /* B = C / (8 * (2 - OVER8) * (DIV_Integer + 1)) */
                DIV_Integer = ((((C * 10UL) / (B * 8UL * (2UL - OVER8))) + 5UL) / 10UL) - 1UL;

                if (DIV_Integer <= 255UL)
                {
                    break;
                }
            }

            /* Check validation : DIV_Integer */
            if (DIV_Integer <= 255UL)
            {
                *pu32BrrValue = (DIV_Integer << USART_BRR_DIV_INTEGER_POS);
                *pu32ClockDiv = u32PCLKDiv;

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
        else
        {
            enRet = ErrorInvalidMode;
        }
    }

    return enRet;
}


#endif /* DDL_PRINT_ENABLE */

/**
 * @}
 */

#endif /* DDL_UTILITY_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
