/**
 *******************************************************************************
 * @file  usart/clocksync_polling/source/main.c
 * @brief This example demonstrates CLKSYNC data receive and transfer by polling.
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
 * @addtogroup USART_Clocksync_Polling
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

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

/* USART unit definition */
#define USART_UNIT                      (CM_USART2)
#define USART_FUNC_CLK_GATE             (CLK_FCG_UART2)

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
 * @brief  Main function of CLKSYNC polling project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_usart_clocksync_init_t stcClockSyncInit;
    /* Buffer used for transmission */
    const uint8_t au8TxBuffer[] = "CLKSYNC TX/RX example: Communication between two boards using usart interface!";
    /* Buffer used for reception */
    uint8_t au8RxBuffer[(ARRAY_SZ(au8TxBuffer))];

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
    stcClockSyncInit.u32Baudrate = 115200UL;
    stcClockSyncInit.u32ClockDiv = USART_CLK_DIV4;
    stcClockSyncInit.u32ClockMode = USART_INTERNCLK_OUTPUT;
#else
    stcClockSyncInit.u32ClockMode = USART_EXTCLK;
#endif
    (void)USART_ClockSync_Init(USART_UNIT, &stcClockSyncInit);

    /* Enable RX/TX function */
    USART_FuncCmd(USART_UNIT, (USART_RX | USART_TX), Enable);

    /* User key */
    while (Reset == KeyState())
    {
    }

    /* Start the transmission process*/
    (void)USART_ClockSync_TransReceive(USART_UNIT, au8TxBuffer, au8RxBuffer, (ARRAY_SZ(au8TxBuffer)), USART_TIMEOUT_MAX);

    /* Compare m_u8TxBuffer and m_u8RxBuffer data */
    if (memcmp(au8TxBuffer, au8RxBuffer, (ARRAY_SZ(au8TxBuffer))) == 0)
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
