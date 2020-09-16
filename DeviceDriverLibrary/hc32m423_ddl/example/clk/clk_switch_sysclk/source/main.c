/**
 *******************************************************************************
 * @file  clk/clk_switch_sysclk/source/main.c
 * @brief Main program of CLK for the Device Driver Library.
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
 * @addtogroup CLK_Switch_sysclk
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define MCO_PORT                (GPIO_PORT_7)
#define MCO_PIN                 (GPIO_PIN_0)
#define MCO_GPIO_FUNC           (GPIO_FUNC_1_MCO)

#define EXAMPLE_PLL_SRC_XTAL    (0UL)
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static en_result_t XtalInit(void);
static void Peripheral_WE(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Wait SW1 key short press.
 * @param  None
 * @retval None
 */
static void WaitSw1_ShortPress(void)
{
    /* Wait key up */
    while(Pin_Set != GPIO_ReadInputPins(GPIO_PORT_0, GPIO_PIN_2))
    {
        ;
    }
    DDL_DelayMS(5UL);

    /* Wait key down */
    while(Pin_Reset != GPIO_ReadInputPins(GPIO_PORT_0, GPIO_PIN_2))
    {
        ;
    }
    DDL_DelayMS(5UL);

    /* Wait key up */
    while(Pin_Set != GPIO_ReadInputPins(GPIO_PORT_0, GPIO_PIN_2))
    {
        ;
    }
    DDL_DelayMS(5UL);
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
    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
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
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Xtal initialize
 * @param  None
 * @retval None
 */
static en_result_t XtalInit(void)
{
    stc_clock_xtal_init_t stcXtalInit;

    /* Xtal config */
    (void)CLK_XtalStructInit(&stcXtalInit);
    stcXtalInit.u8XtalState   = CLK_XTAL_ON;
    stcXtalInit.u8XtalMode    = CLK_XTAL_MD_OSC;
    stcXtalInit.u8XtalDrv     = CLK_XTAL_DRV_HIGH;
    stcXtalInit.u8XtalSupSpeedDrv  = CLK_XTAL_SUPSPEEDDRV_ON;
    stcXtalInit.u8XtalStb     = CLK_XTALSTB_2POW8;
    return CLK_XtalInit(&stcXtalInit);
}

/**
 * @brief  Main function of CLK project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_clock_pll_init_t stcPLLInit;

    /* Register write unprotected for some required peripherals. */
    Peripheral_WE();
    /* LED init */
    BSP_LED_Init();

    /* Configure clock output system clock */
    CLK_MCOConfig(CLK_MCO_SRC_HCLK, CLK_MCO_DIV16);
    /* Configure clock output pin */
    GPIO_SetFunc(MCO_PORT, MCO_PIN, MCO_GPIO_FUNC);
    /* MCO output enable */
    CLK_MCOCmd(Enable);

    if(Ok != XtalInit())
    {
        /* Xtal initial failed */
        BSP_LED_On(LED_RED);
    }

    /* HCLK  Max 80MHz */
    /* PCLK1, PCLK4 Max 80MHz */
    CLK_ClockDiv(CLK_CATE_ALL, (CLK_PCLK1_DIV1 | CLK_PCLK4_DIV1 | CLK_HCLK_DIV1));

    (void)CLK_PLLStructInit(&stcPLLInit);
    /* VCO = 8/2*40 = 160MHz*/
    stcPLLInit.u8PLLState = CLK_PLL_ON;
    stcPLLInit.PLLCFGR = 0UL;

#if (EXAMPLE_PLL_SRC_XTAL)
    /* XTAL frequency 8M / 2 * 40 / 2 = 80M */
    stcPLLInit.PLLCFGR_f.PLLM = 2UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLN = 40UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLP = 2UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_XTAL;
#else
    /* if bCM_EFM->HRCCFGR_b.HRCFREQS3 = 0 , PLL frequency = PLL Hrc in 64M / 8 * 30 / 3 = 80M
       if bCM_EFM->HRCCFGR_b.HRCFREQS3 = 1 , PLL frequency = PLL Hrc in 48M / 8 * 30 / 3 = 60M  */
    stcPLLInit.PLLCFGR_f.PLLM = 8UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLN = 30UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLP = 3UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_HRC;
#endif
    if(Ok != CLK_PLLInit(&stcPLLInit))
    {
        /* PLL initial failed */
        BSP_LED_On(LED_RED);
    }

    /* 3-wait @ 80MHz */
    EFM_SetWaitCycle(EFM_WAIT_CYCLE3);
    while(EFM_WAIT_CYCLE3 != READ_REG32_BIT(CM_EFM->FRMC, EFM_FRMC_FLWT))
    {
        ;
    }

    /* MRC output */
    (void)CLK_MrcCmd(Enable);
    CLK_SetSysclkSrc(CLK_SYSCLK_SRC_MRC);

    WaitSw1_ShortPress();
    /* HRC output */
    (void)CLK_HrcCmd(Enable);
    CLK_SetSysclkSrc(CLK_SYSCLK_SRC_HRC);

    WaitSw1_ShortPress();
    /* LRC output */
    (void)CLK_LrcCmd(Enable);
    CLK_SetSysclkSrc(CLK_SYSCLK_SRC_LRC);

    WaitSw1_ShortPress();
    /* Xtal output */
    (void)CLK_XtalCmd(Enable);
    CLK_SetSysclkSrc(CLK_SYSCLK_SRC_XTAL);

    WaitSw1_ShortPress();
    /* PLLH output */
    (void)CLK_PLLCmd(Enable);
    CLK_SetSysclkSrc(CLK_SYSCLK_SRC_PLL);

    Peripheral_WP();

    for(;;)
    {
        ;
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
