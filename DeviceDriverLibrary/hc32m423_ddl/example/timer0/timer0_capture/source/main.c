/**
 *******************************************************************************
 * @file  timer0/timer0_capture/source/main.c
 * @brief Main program of TIMER0 for the Device Driver Library.
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
 * @addtogroup TMR0_Capture
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define SW1_INT_PORT                (GPIO_PORT_0)
#define SW1_INT_PIN                 (GPIO_PIN_2)
#define SW1_INT_CH                  (EXTINT_CH05)

#define TMR0_UNITx                  (CM_TMR0_2)
#define TMR0_CHx                    (TMR0_CH_B)
#define TMR0_EVT_SRC                (EVT_PORT_EIRQ5)
#define TMR0_CAPT_CNT_MAX           (2U)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void IRQ_Config(void);
static void TMR0_Config(void);
static void Peripheral_WE(void);
static void Peripheral_WP(void);
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
    /* Unlock CLK registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Unlock(PWC_UNLOCK_CODE_0);
    /* Unlock all EFM registers */
    //EFM_Unlock();
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
    /* Lock CLK registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Lock(PWC_UNLOCK_CODE_0);
    /* Lock all EFM registers */
    //EFM_Lock();
}

/**
 * @brief  Main function of TIMER0 capture project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();
    /* Led Init */
    BSP_LED_Init();
    /* Config uart for debug information */
    (void)DDL_PrintfInit();
    /* Enable AOS peripheral */
    CLK_FcgPeriphClockCmd(CLK_FCG_AOS, Enable);

    /* Configure EXINT && NVIC */
    IRQ_Config();
    /* Configure TMR0 */
    TMR0_Config();
    /* Timer function kick start */
    TMR0_Start(TMR0_UNITx, TMR0_CHx);

    /* MCU Peripheral registers write protected. */
    Peripheral_WP();
    for (;;)
    {
        ;
    }
}

/**
 * @brief  Configure EXINT && NVIC.
 * @param  None
 * @retval None
 */
static void IRQ_Config(void)
{
    stc_irq_signin_config_t stcIrqRegCfg;
    stc_gpio_init_t stcGpioInit;
    stc_extint_init_t stcExtIntInit;

    /* Register IRQ handler && configure NVIC. */
    stcIrqRegCfg.enIRQn = TMR0_2_GCMB_IRQn;
    NVIC_ClearPendingIRQ(stcIrqRegCfg.enIRQn);
    NVIC_SetPriority(stcIrqRegCfg.enIRQn, DDL_IRQ_PRI15);
    NVIC_EnableIRQ(stcIrqRegCfg.enIRQn);

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExtInt = PIN_EXTINT_ON;
    (void)GPIO_Init(SW1_INT_PORT, SW1_INT_PIN, &stcGpioInit);

    /* EXTINT Channel 5 (SW1) configure */
    stcExtIntInit.u32ExtIntFilterA = EXTINT_FILTER_A_ON;
    stcExtIntInit.u32ExtIntFilterAClock = EXTINT_FILTER_A_CLK_DIV8;
    stcExtIntInit.u32ExtIntLevel  = EXTINT_TRIG_BOTH;
    (void)EXTINT_Init(SW1_INT_CH, &stcExtIntInit);
}

/**
 * @brief  Configure TMR0.
 * @param  None
 * @retval None
 */
static void TMR0_Config(void)
{
    stc_tmr0_init_t stcTmr0Init;
    /* Enable tmr0 peripheral clock */
    CLK_FcgPeriphClockCmd(CLK_FCG_TMR0_2, Enable);

    /* TMR0 base timer function initialize */
    (void)TMR0_StructInit(&stcTmr0Init);
    stcTmr0Init.u32ClockDiv = TMR0_CLK_DIV1024; /* Config clock division */
    stcTmr0Init.u32ClockSrc = TMR0_SYNC_CLK_PCLK; /* Chose clock source */
    stcTmr0Init.u16PeriodValue = 0xFFFFU; /* Set period value */
    (void)TMR0_Init(TMR0_UNITx, TMR0_CHx, &stcTmr0Init);
    /* Set count value */
    TMR0_SetCountValue(TMR0_UNITx, TMR0_CHx, 0x0U);
    /* Set internal hardware capture source */
    TMR0_SetTriggerSrc(TMR0_UNITx, TMR0_EVT_SRC);
    /* Enable HardWare trigger function */
    TMR0_HWCaptureCondCmd(TMR0_UNITx, TMR0_CHx, Enable);
    /* Set capture function */
    TMR0_SetFunc(TMR0_UNITx, TMR0_CHx, TMR0_FUNC_CAPT);
    /* Tmr0 interrupt function enable */
    TMR0_IntCmd(TMR0_UNITx, TMR0_CHx, Enable);
}

/**
 * @brief  TMR0 compare IRQ callback
 * @param  None
 * @retval None
 */
void TMR0_2_CmpB_IrqHandler(void)
{
    uint32_t u32Tmr0CaptData;
    u32Tmr0CaptData = TMR0_GetCompareValue(TMR0_UNITx, TMR0_CHx);
    /* Turn on LED_G */
    BSP_LED_On(LED_GREEN);
    /* Finish tmr0 capture */
    TMR0_Stop(TMR0_UNITx, TMR0_CHx);
    /* Print capture data */
    (void)printf("TMR0 capture data is %u\n", (unsigned int)u32Tmr0CaptData);
    /* Tmr0 interrupt function disable */
    TMR0_IntCmd(TMR0_UNITx, TMR0_CHx, Disable);
    /* Clear flag */
    TMR0_ClearStatus(TMR0_UNITx, TMR0_CHx);
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
