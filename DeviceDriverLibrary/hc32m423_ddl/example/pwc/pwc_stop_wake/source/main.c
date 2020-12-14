/**
 *******************************************************************************
 * @file  pwc/pwc_stop_wake/source/main.c
 * @brief Main program of PWC for the Device Driver Library.
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
 * @addtogroup PWC_Stop_wake
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define DELAY_TIME      (5000U)

/* KEY1 EXTINT5 */
#define KEY1_INT_CH     (EXTINT_CH05)
#define KEY1_INT_PORT   (GPIO_PORT_0)
#define KEY1_INT_PIN    (GPIO_PIN_2)
#define KEY1_INT_SRC    (INT_PORT_EIRQ5)
#define KEY1_INT_IRQn   (EXTINT_PORT_EIRQ5_IRQn)

/* KEY2 GPIO */
#define KEY2_PORT       (GPIO_PORT_0)
#define KEY2_PIN        (GPIO_PIN_1)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static __IO uint8_t u8IntCnt = 0U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  KEY1 (External interrupt Ch.5) ISR
 * @param  None
 * @retval None
 */
void ExtInt05_SWInt13_IrqHandler(void)
{
    if (Set == EXTINT_GetExtIntStatus(KEY1_INT_CH))
    {
        EXTINT_ClearExtIntStatus(KEY1_INT_CH);
        u8IntCnt++;
    }
}
/**
 * @brief  KEY1 initialize.
 * @param  None
 * @retval None
 */
static void KEY1_Init(void)
{
    stc_extint_init_t stcExtIntInit;
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    /* KEY1, KEY2, KEY4 initialize */
    stcGpioInit.u16ExtInt = PIN_EXTINT_ON;
    (void)GPIO_Init(KEY1_INT_PORT, KEY1_INT_PIN, &stcGpioInit);

    (void)EXTINT_StructInit(&stcExtIntInit);

    /* EXTINT Channel 5 (KEY1) configure */
    stcExtIntInit.u32ExtIntFilterA      = EXTINT_FILTER_A_ON;
    stcExtIntInit.u32ExtIntFilterAClock = EXTINT_FILTER_A_CLK_DIV1;
    stcExtIntInit.u32ExtIntLevel        = EXTINT_TRIG_FALLING;
    (void)EXTINT_Init(KEY1_INT_CH, &stcExtIntInit);

    /* NVIC configure */
    /* IRQ No.013, fixed entry for EXTINT5(KEY1) */
    NVIC_ClearPendingIRQ(KEY1_INT_IRQn);
    NVIC_SetPriority(KEY1_INT_IRQn, DDL_IRQ_PRI14);
    NVIC_EnableIRQ(KEY1_INT_IRQn);
}

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
    /* Unlock PWC, CLK, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
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
    //GPIO_Lock();
    /* Lock PWC, CLK, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Lock(PWC_UNLOCK_CODE_0);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Main function of CLK project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_pwc_stop_mode_t  stcPwcStopConfig;

    /* Register write unprotected for some required peripherals. */
    Peripheral_WE();
    /* LED init */
    BSP_LED_Init();

    KEY1_Init();

    /* Config stop mode, disable high precision POR */
    stcPwcStopConfig.u8HighPrecisionPOR = PWC_HIGH_PRECISION_POR_DISABLE;
    stcPwcStopConfig.u8AwakeClock = PWC_SYSCLK_FIX;
    stcPwcStopConfig.u8WaitFlash = PWC_WAIT_FLASH_ENABLE;

    (void)PWC_StopConfig(&stcPwcStopConfig);

    /* Config EIRQ5 as stop mode wake-up source */
    INTC_WakeupSrcCmd(INTC_WUPEN_EIRQWUEN_5, Enable);

    /* Key SW2 */
    while(Pin_Reset != GPIO_ReadInputPins(KEY2_PORT, KEY2_PIN))
    {
        ;
    }

    BSP_LED_On(LED_RED);

    Peripheral_WP();
    PWC_EnterStopMode();

    for(;;)
    {
        if(0U != (u8IntCnt % 2U))
        {
            BSP_LED_Off(LED_RED);
            BSP_LED_On(LED_GREEN);
        }
        else
        {
            BSP_LED_On(LED_RED);
            BSP_LED_Off(LED_GREEN);
            PWC_EnterStopMode();
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
