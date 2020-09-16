/**
 *******************************************************************************
 * @file  timera/timera_input_capture/source/main.c
 * @brief Main program of Timera Input Capture for the Device Driver Library.
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
 * @addtogroup TMRA_Input_Capture
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* KEY1(SW1) Port/Pin definition */
#define KEY1_EVT_PORT                   (GPIO_PORT_0)
#define KEY1_EVT_PIN                    (GPIO_PIN_2)
#define KEY1_EVT_SRC                    (EVT_PORT_EIRQ5)

/* Timera unit definition */
#define TMRA_UNIT4                      (CM_TMRA_4)
#define TMRA_UNIT4_CLK                  (CLK_FCG_TMRA_4)
#define TMRA_UNIT4_CLK_DIV              (256U)
#define TMRA_UNIT4_INT_FREQ             (100U)
/* Period value = 10ms */
#define TMRA_UNIT4_PERIOD_VALUE         ((uint16_t)(HCLK_VALUE/TMRA_UNIT4_CLK_DIV/TMRA_UNIT4_INT_FREQ) - 1U)

/* Timera channel 1 Port/Pin definition */
#define TMRA_UNIT4_CH1_PORT             (GPIO_PORT_9)
#define TMRA_UNIT4_CH1_PIN              (GPIO_PIN_2)
#define TMRA_UNIT4_CH1_FUNC             (GPIO_FUNC_4_TIMA4_PWM1)

/* Timera channel 2 Port/Pin definition */
#define TMRA_UNIT4_CH2_PORT             (GPIO_PORT_9)
#define TMRA_UNIT4_CH2_PIN              (GPIO_PIN_3)
#define TMRA_UNIT4_CH2_FUNC             (GPIO_FUNC_4_TIMA4_PWM2)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Compare interrupt callback for Timera unit4.
 * @param  None
 * @retval None
 */
void TMRA_4_Cmp_IrqHandler(void)
{
    /* Capture channel 1 */
    if (Set == TMRA_GetStatus(TMRA_UNIT4, TMRA_FLAG_CMP1))
    {
        BSP_LED_Toggle(LED_RED);
        TMRA_ClearStatus(TMRA_UNIT4, TMRA_FLAG_CMP1);
    }
    /* Capture channel 2 */
    if (Set == TMRA_GetStatus(TMRA_UNIT4, TMRA_FLAG_CMP2))
    {
        BSP_LED_Toggle(LED_GREEN);
        TMRA_ClearStatus(TMRA_UNIT4, TMRA_FLAG_CMP2);
    }
}

/**
 * @brief  Configure Timera function.
 * @param  None
 * @retval None
 */
static void TMRA_Config(void)
{
    stc_tmra_init_t stcTmraInit;
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PullUp = PIN_PU_ON;
    (void)GPIO_Init(TMRA_UNIT4_CH1_PORT, TMRA_UNIT4_CH1_PIN, &stcGpioInit);
    (void)GPIO_Init(TMRA_UNIT4_CH2_PORT, TMRA_UNIT4_CH2_PIN, &stcGpioInit);
    /* Configure capture pin of Timera */
    GPIO_SetFunc(TMRA_UNIT4_CH1_PORT, TMRA_UNIT4_CH1_PIN, TMRA_UNIT4_CH1_FUNC);
    GPIO_SetFunc(TMRA_UNIT4_CH2_PORT, TMRA_UNIT4_CH2_PIN, TMRA_UNIT4_CH2_FUNC);

    /* Configure peripheral clock */
    CLK_FcgPeriphClockCmd((TMRA_UNIT4_CLK | CLK_FCG_AOS), Enable);

    (void)TMRA_StructInit(&stcTmraInit);
    /* Configure structure of timera unit4 */
    stcTmraInit.u16ClockDiv    = TMRA_CLK_DIV256;
    stcTmraInit.u16CountMode   = TMRA_MD_SAWTOOTH;
    stcTmraInit.u16CountDir    = TMRA_DIR_UP;
    stcTmraInit.u16PeriodValue = TMRA_UNIT4_PERIOD_VALUE;
    (void)TMRA_Init(TMRA_UNIT4, &stcTmraInit);
    TMRA_IntCmd(TMRA_UNIT4, (TMRA_INT_CMP1 | TMRA_INT_CMP2), Enable);

    /* Set captured event source */
    TMRA_SetTriggerSrc(TMRA_EVT_USAGE_CAPT, KEY1_EVT_SRC);
    /* Configure capture function of channel 1 */
    TMRA_SetFunc(TMRA_UNIT4, TMRA_CH1, TMRA_FUNC_CAPT);
    TMRA_HWCaptureCondCmd(TMRA_UNIT4, TMRA_CH1, (TMRA_CAPT_COND_PWMF | TMRA_CAPT_COND_EVT), Enable);
    TMRA_SetFilterClockDiv(TMRA_UNIT4, TMRA_PIN_PWM1, TMRA_FILTER_CLK_DIV4);
    TMRA_FilterCmd(TMRA_UNIT4, TMRA_PIN_PWM1, Enable);

    /* Configure capture function of channel 2 */
    TMRA_SetFunc(TMRA_UNIT4, TMRA_CH2, TMRA_FUNC_CAPT);
    TMRA_HWCaptureCondCmd(TMRA_UNIT4, TMRA_CH2, (TMRA_CAPT_COND_PWMF | TMRA_CAPT_COND_EVT), Enable);
    TMRA_SetFilterClockDiv(TMRA_UNIT4, TMRA_PIN_PWM2, TMRA_FILTER_CLK_DIV4);
    TMRA_FilterCmd(TMRA_UNIT4, TMRA_PIN_PWM2, Enable);

    /* Configure interrupt of timera unit4 */
    NVIC_ClearPendingIRQ(TMRA_4_CMP_IRQn);
    NVIC_SetPriority(TMRA_4_CMP_IRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(TMRA_4_CMP_IRQn);
}

/**
 * @brief  KEY1(SW1) initialize.
 * @param  None
 * @retval None
 */
static void KEY1_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    /* KEY1 initialize */
    stcGpioInit.u16ExtInt = PIN_EXTINT_ON;
    (void)GPIO_Init(KEY1_EVT_PORT, KEY1_EVT_PIN, &stcGpioInit);
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
    GPIO_Lock();
    /* Lock PWC, CLK, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
//    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Main function of Timera Input Capture.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Peripheral registers write unprotected */
    Peripheral_WE();
    /* Configure BSP */
    BSP_CLK_Init();
    BSP_LED_Init();
    /* Configure KEY1 */
    KEY1_Init();
    /* Configure UART */
    (void)DDL_PrintfInit();
    /* Configure Timera */
    TMRA_Config();
    /* Peripheral registers write protected */
    Peripheral_WP();
    /* Start unit4 of timera */
    TMRA_Start(TMRA_UNIT4);

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
