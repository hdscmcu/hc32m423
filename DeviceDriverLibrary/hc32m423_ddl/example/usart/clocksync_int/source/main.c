/**
 *******************************************************************************
 * @file  usart/clocksync_int/source/main.c
 * @brief This example demonstrates CLKSYNC data receive and transfer by interrupt.
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
#include <string.h>
#include "hc32_ddl.h"

/**
 * @addtogroup HC32M423_DDL_Examples
 * @{
 */

/**
 * @addtogroup USART_Clocksync_Interrupt
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief USART buffer Structure definition
 */
typedef struct
{
    const uint8_t   *pu8TxBufPtr;       /*!< Pointer to USART Tx transfer Buffer */

    uint16_t        u16TxXferSize;      /*!< USART Tx Transfer size              */

    __IO uint16_t   u16TxXferCount;     /*!< USART Tx Transfer Counter           */

    uint8_t         *pu8RxBufPtr;       /*!< Pointer to Usart Rx transfer Buffer */

    uint16_t        u16RxXferSize;      /*!< USART Rx Transfer size              */

    __IO uint16_t   u16RxXferCount;     /*!< USART Rx Transfer Counter           */

} stc_buf_handle_t;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* CLKSYNC CK/RX/TX Port/Pin definition */
#define USART_CK_PORT                   (GPIO_PORT_B)
#define USART_CK_PIN                    (GPIO_PIN_7)      /* PB7: USART2_CK */
#define USART_CK_GPIO_FUNC              (GPIO_FUNC_5_USART)

#define USART_RX_PORT                   (GPIO_PORT_B)
#define USART_RX_PIN                    (GPIO_PIN_6)      /* PB6: USART2_RX */
#define USART_RX_GPIO_FUNC              (GPIO_FUNC_5_USART)

#define USART_TX_PORT                   (GPIO_PORT_B)
#define USART_TX_PIN                    (GPIO_PIN_5)      /* PB5: USART2_TX */
#define USART_TX_GPIO_FUNC              (GPIO_FUNC_5_USART)

/* UART unit definition */
#define USART_UNIT                      (CM_USART2)
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

/* CLKSYNC device mode definition */
#define CLKSYNC_MASTER                  (0U)
#define CLKSYNC_SLAVE                   (1U)

/* USART master or slave mode selection */
#define CLKSYNC_DEVICE_MD               (CLKSYNC_MASTER)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static en_flag_status_t KeyState(void);
static void USART_TxEmpty_IrqCallback(void);
static void USART_TxComplete_IrqCallback(void);
static void USART_Rx_IrqCallback(void);
static void USART_RxErr_IrqCallback(void);
static en_result_t CLOCKSYNC_TransReceive_INT(CM_USART_TypeDef *USARTx,
                                             stc_buf_handle_t *pstcBufHandle,
                                             const uint8_t *pu8TxData,
                                             uint8_t *pu8RxData,
                                             uint16_t u16Size);
static void CLOCKSYNC_TransmitReceive_Callback(CM_USART_TypeDef *USARTx,
                                    stc_buf_handle_t *pstcBufHandle);
static void InstalIrqHandler(const stc_irq_signin_config_t *pstcConfig,
                                    uint32_t u32Priority);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static stc_buf_handle_t m_stcBufHandle;

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
 * @brief  USART TX Empty IRQ callback.
 * @param  None.
 * @retval None
 */
static void USART_TxEmpty_IrqCallback(void)
{
    en_flag_status_t enFlag = USART_GetStatus(USART_UNIT, USART_FLAG_TX_EMPTY);
    en_functional_state_t enState = USART_GetFuncState(USART_UNIT, USART_INT_TX_EMPTY);

    if ((Set == enFlag) && (Enable == enState))
    {
        CLOCKSYNC_TransmitReceive_Callback(USART_UNIT, &m_stcBufHandle);
    }
}

/**
 * @brief  USART TX Complete IRQ callback.
 * @param  None.
 * @retval None
 */
static void USART_TxComplete_IrqCallback(void)
{
    en_flag_status_t enFlag = USART_GetStatus(USART_UNIT, USART_FLAG_TX_CPLT);
    en_functional_state_t enState = USART_GetFuncState(USART_UNIT, USART_INT_TX_CPLT);

    if ((Set == enFlag) && (Enable == enState))
    {
        CLOCKSYNC_TransmitReceive_Callback(USART_UNIT, &m_stcBufHandle);
    }
}

/**
 * @brief  USART RX IRQ callback.
 * @param  None
 * @retval None
 */
static void USART_Rx_IrqCallback(void)
{
    en_flag_status_t enFlag = USART_GetStatus(USART_UNIT, USART_FLAG_RX_FULL);
    en_functional_state_t enState = USART_GetFuncState(USART_UNIT, USART_INT_RX);

    if ((Set == enFlag) && (Enable == enState))
    {
        CLOCKSYNC_TransmitReceive_Callback(USART_UNIT, &m_stcBufHandle);
    }
}

/**
 * @brief  USART RX Error IRQ callback.
 * @param  None.
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
 * @brief  Send&&receive an amount of data in full-duplex mode (non-blocking).
 * @param  [in] USARTx                  pointer to a USART instance.
 * @param  [in] pstcBufHandle           pointer to a stc_buf_handle_t structure.
 * @param  [in] pu8TxData               Pointer to data transmitted buffer
 * @param  [out] pu8RxData              Pointer to data received buffer
 * @param  [in] u16Size                 Amount of data to be received
 * @retval An en_result_t enumeration value:
 *           - Ok: success
 *           - ErrorInvalidParameter: Invalid parameter
 */
static en_result_t CLOCKSYNC_TransReceive_INT(CM_USART_TypeDef *USARTx,
                                             stc_buf_handle_t *pstcBufHandle,
                                             const uint8_t *pu8TxData,
                                             uint8_t *pu8RxData,
                                             uint16_t u16Size)
{
    en_result_t enRet = ErrorInvalidParameter;
    const uint32_t u32Func = (USART_RX | USART_INT_RX | USART_TX);

    if ((USARTx != NULL) && (pu8TxData != NULL) && (pu8RxData != NULL) && (u16Size > 0U))
    {
        pstcBufHandle->pu8RxBufPtr = pu8RxData;
        pstcBufHandle->u16RxXferSize = u16Size;
        pstcBufHandle->u16RxXferCount = u16Size;
        pstcBufHandle->pu8TxBufPtr = pu8TxData;
        pstcBufHandle->u16TxXferSize = u16Size;
        pstcBufHandle->u16TxXferCount = u16Size;

        USART_FuncCmd(USARTx, (u32Func | USART_INT_TX_EMPTY | USART_INT_TX_CPLT), Disable);

        if (USART_EXTCLK == USART_GetClockMode(USARTx))
        {
            USART_FuncCmd(USARTx, (u32Func | USART_INT_TX_EMPTY), Enable);
        }
        else
        {
            USART_FuncCmd(USARTx, (u32Func | USART_INT_TX_CPLT), Enable);
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Send receive an amount of data in full-duplex mode (non-blocking) in IRQ handler.
 * @param  [in] USARTx                  pointer to a USART instance.
 * @param  [in] pstcBufHandle           pointer to a stc_buf_handle_t structure.
 * @retval None
 */
static void CLOCKSYNC_TransmitReceive_Callback(CM_USART_TypeDef *USARTx,
                                    stc_buf_handle_t *pstcBufHandle)
{
    if (pstcBufHandle->u16RxXferCount != 0U)
    {
        if (USART_GetStatus(USARTx, USART_FLAG_RX_FULL) != Reset)
        {
            *pstcBufHandle->pu8RxBufPtr = (uint8_t)USART_ReadData(USARTx);
            pstcBufHandle->pu8RxBufPtr++;
            pstcBufHandle->u16RxXferCount--;
        }
    }

    /* Check the latest data received */
    if (0U == pstcBufHandle->u16RxXferCount)
    {
        /* Disable the USART RXNE && Error Interrupt */
        USART_FuncCmd(USARTx, USART_INT_RX, Disable);
    }
    else
    {
        if (pstcBufHandle->u16TxXferCount != 0U)
        {
            if (USART_GetStatus(USARTx, USART_FLAG_TX_EMPTY) != Reset)
            {
                USART_WriteData(USARTx, (uint16_t)(*pstcBufHandle->pu8TxBufPtr));
                pstcBufHandle->pu8TxBufPtr++;
                pstcBufHandle->u16TxXferCount--;

                /* Check the latest data transmitted */
                if (0U == pstcBufHandle->u16TxXferCount)
                {
                    USART_FuncCmd(USARTx, (USART_INT_TX_EMPTY | USART_INT_TX_CPLT), Disable);
                }
            }
        }
    }
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
 * @brief  Main function of CLKSYNC interrupt project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint16_t u16TxXferCount;
    uint16_t u16RxXferCount;
    stc_irq_signin_config_t stcIrqConfig;
    stc_usart_clocksync_init_t stcClockSyncInit;
    /* Buffer used for transmission */
    const uint8_t au8TxData[] = "CLKSYNC TX/RX example: Communication between two boards using usart interface!";
    /* Buffer used for reception */
    uint8_t au8RxData[ARRAY_SZ(au8TxData)];

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize system clock. */
    BSP_CLK_Init();

    /* Initialize LED. */
    BSP_LED_Init();

    /* Configure USART RX/TX pin. */
    GPIO_SetFunc(USART_CK_PORT, USART_CK_PIN, USART_CK_GPIO_FUNC);
    GPIO_SetFunc(USART_RX_PORT, USART_RX_PIN, USART_RX_GPIO_FUNC);
    GPIO_SetFunc(USART_TX_PORT, USART_TX_PIN, USART_TX_GPIO_FUNC);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(USART_FUNC_CLK_GATE, Enable);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Initialize CLKSYNC function. */
    (void)USART_ClockSync_StructInit(&stcClockSyncInit);
#if (CLKSYNC_DEVICE_MD == CLKSYNC_MASTER)
    stcClockSyncInit.u32Baudrate = 38400UL;
    stcClockSyncInit.u32ClockDiv = USART_CLK_DIV4;
    stcClockSyncInit.u32ClockMode = USART_INTERNCLK_OUTPUT;
#else
    stcClockSyncInit.u32ClockMode = USART_EXTCLK;
#endif
    (void)USART_ClockSync_Init(USART_UNIT, &stcClockSyncInit);

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

    /* Enable RX/TX function */
    USART_FuncCmd(USART_UNIT, (USART_RX | USART_TX), Enable);

    /* User key */
    while (Reset == KeyState())
    {
    }

    /* Start the transmission process*/
    (void)CLOCKSYNC_TransReceive_INT(USART_UNIT, &m_stcBufHandle, au8TxData, au8RxData, (uint16_t)ARRAY_SZ(au8TxData));

    /* Wait tranmission complete */
    do
    {
        u16TxXferCount = m_stcBufHandle.u16TxXferCount;
        u16RxXferCount = m_stcBufHandle.u16RxXferCount;
    } while ((u16TxXferCount != 0U) || (u16RxXferCount != 0U));

    /* Compare m_u8TxBuffer and m_u8RxBuffer data */
    if (memcmp(au8TxData , au8RxData, (uint32_t)m_stcBufHandle.u16RxXferSize) == 0)
    {
        BSP_LED_On(LED_GREEN);
    }
    else
    {
        BSP_LED_On(LED_RED);
    }

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
