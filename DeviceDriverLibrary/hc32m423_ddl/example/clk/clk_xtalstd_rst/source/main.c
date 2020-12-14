/**
 *******************************************************************************
 * @file  clk/clk_xtalstd_rst/source/main.c
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
 * @addtogroup CLK_Xtalstd_rst
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define XTALSTD_INT_SRC     (INT_XTAL_STOP)
#define XTALSTD_IRQn        (SWINT2_IRQn)
#define DLY_MS              (500UL)

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
 * @brief  XTAL stop detect IRQ callback function
 * @param  None
 * @retval None
 */
static void XTAL_STOP_IrqCallback(void)
{
    __IO uint8_t u8Cnt = 10U;
    BSP_LED_Off(LED_GREEN);
    do
    {
        u8Cnt--;
        BSP_LED_Toggle(LED_RED);
        DDL_DelayMS(DLY_MS);
    } while (0U != (u8Cnt));

    CLK_ClearXtalStdStatus();
}

/**
 * @brief  XTAL stop detect function init
 * @param  None
 * @retval en_result_t
 */
static en_result_t XtalStopDetctInit(void)
{
    stc_clock_xtalstd_init_t stcXtalstdInit;

    /* Enable xtal fault dectect and occur reset. */
    (void)CLK_XtalStdStructInit(&stcXtalstdInit);
    stcXtalstdInit.u8XtalStdState = CLK_XTALSTD_ON;
    stcXtalstdInit.u8XtalStdExceptionType = CLK_XTALSTD_EXP_TYPE_INT;
    stcXtalstdInit.u8XtalStdInt = CLK_XTALSTD_INT_ON;
    stcXtalstdInit.u8XtalStdRst = CLK_XTALSTD_RST_OFF;
    return CLK_XtalStdInit(&stcXtalstdInit);
}

/**
 * @brief  XTAL stop detect interrupt init
 * @param  None
 * @retval None
 */
static en_result_t XtalStopIntInit(void)
{
    en_result_t enRet = Error;
    stc_irq_signin_config_t stcIrqSignConfig;

    stcIrqSignConfig.enIntSrc   = XTALSTD_INT_SRC;
    stcIrqSignConfig.enIRQn     = XTALSTD_IRQn;
    stcIrqSignConfig.pfnCallback= &XTAL_STOP_IrqCallback;

    if(Ok == INTC_IrqSignIn(&stcIrqSignConfig))
    {
        CLK_ClearXtalStdStatus();

        /* NVIC setting */
        NVIC_ClearPendingIRQ(XTALSTD_IRQn);
        NVIC_SetPriority(XTALSTD_IRQn,DDL_IRQ_PRI03);
        NVIC_EnableIRQ(XTALSTD_IRQn);
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Main function of CLK project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Register write unprotected for some required peripherals. */
    Peripheral_WE();
    /* LED init */
    BSP_LED_Init();

    if(Ok != XtalInit())
    {
        /* Xtal initial failed */
        BSP_LED_On(LED_RED);
    }

    (void)XtalStopDetctInit();
    if(Ok != XtalStopIntInit())
    {
        /* Xtal stop interrupt initial failed */
        BSP_LED_On(LED_RED);
    }

    if(Set == RMU_GetStatus(RMU_RST_CLK_ERR))
    {
        RMU_ClearStatus();

        BSP_LED_On(LED_RED);
        BSP_LED_Off(LED_GREEN);
    }
    else
    {
        BSP_LED_On(LED_GREEN);
        BSP_LED_Off(LED_RED);
    }

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
