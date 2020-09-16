/**
 *******************************************************************************
 * @file  extint_nmi_swint/ekey/source/main.c
 * @brief Main program EXTINT_NMI for the Device Driver Library.
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
 * @addtogroup EXTINT_NMI_SWI
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* KEY1 EXTINT5 */
#define KEY1_INT_CH     (EXTINT_CH05)
#define KEY1_INT_PORT   (GPIO_PORT_0)
#define KEY1_INT_PIN    (GPIO_PIN_2)
#define KEY1_INT_SRC    (INT_PORT_EIRQ5)
#define KEY1_INT_IRQn   (EXTINT_PORT_EIRQ5_IRQn)
/* KEY2 EXTINT4 */
#define KEY2_INT_CH     (EXTINT_CH04)
#define KEY2_INT_PORT   (GPIO_PORT_0)
#define KEY2_INT_PIN    (GPIO_PIN_1)
#define KEY2_INT_SRC    (INT_PORT_EIRQ4)
#define KEY2_INT_IRQn   (EXTINT_PORT_EIRQ4_IRQn)
/* KEY3 NMI Pin */
#define KEY3_INT_PORT   (GPIO_PORT_E)
#define KEY3_INT_PIN    (GPIO_PIN_2)
/* KEY4 EXTINT7 */
#define KEY4_INT_CH     (EXTINT_CH07)
#define KEY4_INT_PORT   (GPIO_PORT_D)
#define KEY4_INT_PIN    (GPIO_PIN_7)
#define KEY4_INT_SRC    (INT_PORT_EIRQ7)
#define KEY4_INT_IRQn   (INT000_IRQn)

/* Software interrupt Ch.14 */
#define SWINT_CH        (INTC_SWIER_SWIE14)
#define SWINT_IRQn      (SWINT14_IRQn)

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
static void KEY4_IrqCallback(void);
static void NMI_IrqCallback(void);
static void KEY1_Init(void);
static void KEY2_Init(void);
static void KEY3_Init(void);
static void KEY4_Init(void);
static void NMI_EXTINT_FilterBConfig(void);
static void SWInt_Init(void);

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
    /* Unlock PWC, CLK, LVD, RMU registers, @ref PWC_REG_Write_Unlock_Code for details */
//    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Unlock all EFM registers */
//    EFM_Unlock();
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
    /* Lock PWC, CLK, LVD, RMU registers, @ref PWC_REG_Write_Unlock_Code for details */
//    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
//    EFM_Lock();
}

/**
 * @brief  KEY1 (SW1, External interrupt Ch.5) ISR
 * @param  None
 * @retval None
 */
void ExtInt05_SWInt13_IrqHandler(void)
{
   if (Set == EXTINT_GetExtIntStatus(KEY1_INT_CH))
   {
        EXTINT_ClearExtIntStatus(KEY1_INT_CH);
        BSP_LED_Toggle(LED_RED);
   }
}

/**
 * @brief  KEY2 (SW2, External interrupt Ch.4) ISR
 * @param  None
 * @retval None
 */
void ExtInt04_SWInt12_IrqHandler(void)
{
   if (Set == EXTINT_GetExtIntStatus(KEY2_INT_CH))
   {
        EXTINT_ClearExtIntStatus(KEY2_INT_CH);
        BSP_LED_Toggle(LED_GREEN);
   }
}

/**
 * @brief  KEY4 (SW4, External interrupt Ch.7) callback function
 * @param  None
 * @retval None
 */
static void KEY4_IrqCallback(void)
{
   if (Set == EXTINT_GetExtIntStatus(KEY4_INT_CH))
   {
        EXTINT_ClearExtIntStatus(KEY4_INT_CH);
        BSP_LED_Toggle(LED_RED | LED_GREEN | LED_BLUE);
   }
}

/**
 * @brief  Software interrupt Ch.14 callback function
 * @param  None
 * @retval None
 */
void ExtInt06_SWInt14_IrqHandler(void)
{
    INTC_SWIntCmd(SWINT_CH, Disable);
    BSP_LED_Toggle(LED_RED | LED_GREEN | LED_BLUE);

}

/**
 * @brief  NMI IRQ callback function
 * @param  None
 * @retval None
 */
static void NMI_IrqCallback(void)
{
    /* KEY3(SW3) NMI pin */
    if (Set == NMI_GetNmiStatus(INTC_NMIFR_NMIFR))
    {
        NMI_ClearNmiStatus(INTC_NMIFR_NMIFR);
        BSP_LED_Toggle(LED_BLUE);
    }
    if (Set == NMI_GetNmiStatus(INTC_NMIFR_SWDTFR))
    {
        NMI_ClearNmiStatus(INTC_NMIFR_SWDTFR);
    }
    if (Set == NMI_GetNmiStatus(INTC_NMIFR_PVD1FR))
    {
        NMI_ClearNmiStatus(INTC_NMIFR_PVD1FR);
    }
    if (Set == NMI_GetNmiStatus(INTC_NMIFR_PVD2FR))
    {
        NMI_ClearNmiStatus(INTC_NMIFR_PVD2FR);
    }
    if (Set == NMI_GetNmiStatus(INTC_NMIFR_XTALSTPFR))
    {
        NMI_ClearNmiStatus(INTC_NMIFR_XTALSTPFR);
    }
    if (Set == NMI_GetNmiStatus(INTC_NMIFR_REPFR))
    {
        NMI_ClearNmiStatus(INTC_NMIFR_REPFR);
    }
    if (Set == NMI_GetNmiStatus(INTC_NMIFR_WDTFR))
    {
        NMI_ClearNmiStatus(INTC_NMIFR_WDTFR);
    }
}

/**
 * @brief  KEY1(SW1) initialize.
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
 * @brief  KEY2(SW2) initialize.
 * @param  None
 * @retval None
 */
static void KEY2_Init(void)
{
    stc_extint_init_t stcExtIntInit;
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    /* KEY2 initialize */
    stcGpioInit.u16ExtInt = PIN_EXTINT_ON;
    (void)GPIO_Init(KEY2_INT_PORT, KEY2_INT_PIN, &stcGpioInit);

    (void)EXTINT_StructInit(&stcExtIntInit);

    /* EXTINT Channel 4 (KEY2) configure */
    stcExtIntInit.u32ExtIntFilterA    = EXTINT_FILTER_A_ON;
    stcExtIntInit.u32ExtIntFilterAClock  = EXTINT_FILTER_A_CLK_DIV8;
    stcExtIntInit.u32ExtIntLevel  = EXTINT_TRIG_RISING;
    (void)EXTINT_Init(KEY2_INT_CH, &stcExtIntInit);

    /* IRQ No.012, fixed entry for EXTINT4(KEY2) */
    NVIC_ClearPendingIRQ(KEY2_INT_IRQn);
    NVIC_SetPriority(KEY2_INT_IRQn, DDL_IRQ_PRI15);
    NVIC_EnableIRQ(KEY2_INT_IRQn);
}

/**
 * @brief  KEY3(SW3) initialize.
 * @param  None
 * @retval None
 */
static void KEY3_Init(void)
{
    stc_nmi_init_t stcNmiInit;

    /* NMI Pin interrupt configure */
    (void)NMI_StructInit(&stcNmiInit);
    stcNmiInit.u32NmiFilterAClockDiv = NMI_FILTER_A_CLK_DIV64;
    stcNmiInit.u32NmiFilterA    = NMI_FILTER_A_ON;
    stcNmiInit.u32NmiTrigger    = NMI_TRIG_FALLING;
    stcNmiInit.u32NmiSrc        = NMI_SRC_NMI_PIN;
    stcNmiInit.pfnNmiCallback   = &NMI_IrqCallback;
    (void)NMI_Init(&stcNmiInit);
}

/**
 * @brief  KEY4(SW4) initialize.
 * @param  None
 * @retval None
 */
static void KEY4_Init(void)
{
    stc_extint_init_t stcExtIntInit;
    stc_gpio_init_t stcGpioInit;
    stc_irq_signin_config_t stcIrqSignin;

    (void)GPIO_StructInit(&stcGpioInit);
    /* KEY4 initialize */
    stcGpioInit.u16ExtInt = PIN_EXTINT_ON;
    (void)GPIO_Init(KEY4_INT_PORT, KEY4_INT_PIN, &stcGpioInit);

    (void)EXTINT_StructInit(&stcExtIntInit);

    /* EXTINT Channel 7 (KEY4) configure */
    stcExtIntInit.u32ExtIntFilterA= EXTINT_FILTER_A_ON;
    stcExtIntInit.u32ExtIntFilterAClock  = EXTINT_FILTER_A_CLK_DIV32;
    stcExtIntInit.u32ExtIntLevel  = EXTINT_TRIG_BOTH;
    (void)EXTINT_Init(KEY4_INT_CH, &stcExtIntInit);

    /* Set IRQ No.0 as the external interrupt Channel 7 (KEY4) entry */
    stcIrqSignin.enIRQn       = KEY4_INT_IRQn;
    stcIrqSignin.enIntSrc     = KEY4_INT_SRC;
    stcIrqSignin.pfnCallback  = &KEY4_IrqCallback;
    if (Ok != INTC_IrqSignIn(&stcIrqSignin))
    {
        // check parameter
        for(;;)
        {
            ;
        }
    }
    /* IRQ000_Handler for KEY4 */
    NVIC_ClearPendingIRQ(KEY4_INT_IRQn);
    NVIC_SetPriority(KEY4_INT_IRQn, DDL_IRQ_PRI03);
    NVIC_EnableIRQ(KEY4_INT_IRQn);
}

static void NMI_EXTINT_FilterBConfig(void)
{
    NMI_EXTINT_SetFilterBClockTime(NMI_EXTINT_FILTER_B_2US);

    NMI_FilterBCmd(Enable);

    EXTINT_FilterBCmd((KEY1_INT_CH | KEY2_INT_CH |KEY4_INT_CH), Enable);

}

/**
 * @brief  Software interrupt initialize.
 * @param  None
 * @retval None
 */
static void SWInt_Init(void)
{
    /* Software interrupt Ch.14 */
    /* NVIC configure */
    NVIC_ClearPendingIRQ(SWINT_IRQn);
    NVIC_SetPriority(SWINT_IRQn, DDL_IRQ_PRI15);
    NVIC_EnableIRQ(SWINT_IRQn);
}

/**
 * @brief  Main function of EXTINT_NMI project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    Peripheral_WE();

    BSP_LED_Init();

    KEY1_Init();
    KEY2_Init();
    KEY3_Init();
    KEY4_Init();
    NMI_EXTINT_FilterBConfig();
    SWInt_Init();

    Peripheral_WP();

    /* Software interrupt will occur immediately once enable */
    /* Share entry for EXTINT06 and SWINT_14*/
    INTC_SWIntCmd(SWINT_CH, Enable);

    for(;;)
    {
        ;// wait KEY1(SW1)/KEY2(SW2)/KEY3(NMI)(SW3)/KEY4(SW4) key pressed
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
