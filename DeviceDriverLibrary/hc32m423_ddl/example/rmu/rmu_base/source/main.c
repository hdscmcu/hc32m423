/**
 *******************************************************************************
 * @file  rmu/rmu_base/source/main.c
 * @brief Main program of RMU for the Device Driver Library.
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
 * @addtogroup RMU_base
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Test reset mode enum*/
#define RESET_WDT                       (0U)
#define RESET_XTALERR                   (1U)
#define RESET_SOFTWARERST               (2U)
#define RESET_LVD                       (3U)
#define RESET_CLKFREQERR                (4U)

/* Modify for test reset mode */
#define TEST_RESET_MODE                 (RESET_WDT)
#if (TEST_RESET_MODE == RESET_CLKFREQERR)
/* (((TAR_FREQ/TAR_DIV)/(REF_FREQ/REF_DIV))* 90UL)/100UL ~ (((TAR_FREQ/TAR_DIV)/(REF_FREQ/REF_DIV))* 110UL)/100UL */
    #define ClockLowerLimit             (6000U)
    #define ClockUpperLimit             (7000U)
    #define REF_FREQ                    (FCM_REF_CLK_XTAL)
    #define REF_DIV                     (FCM_REF_CLK_DIV8192)
    #define TAR_FREQ                    (FCM_TARGET_CLK_MRC)
    #define TAR_DIV                     (FCM_TARGET_CLK_DIV1)
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void PrintResetMode(void);
static void MakeReset(void);
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
    /* Lock CLK, PWC registers, @ref PWC_REG_Write_Unlock_Code for details */
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
    //GPIO_Lock();
    /* Lock CLK, PWC, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    //PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    //EFM_Lock();
}
/**
 * @brief  Main function of RMU base project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Unlock peripherals or registers */
    Peripheral_WE();
    /* Config system clock. HClK = 80MHZ */
    BSP_CLK_Init();
    /* Config uart for debug information */
    (void)DDL_PrintfInit();
    /* Printf reset cause */
    PrintResetMode();
    (void)printf("\nPress SW1 to config reset condition.\n");
    /* Wait short press SW1 */
    while(Pin_Reset != GPIO_ReadInputPins(GPIO_PORT_0, GPIO_PIN_2))
    {
        ;
    }
    while(Pin_Set != GPIO_ReadInputPins(GPIO_PORT_0, GPIO_PIN_2))
    {
        ;
    }
    /* Clear reset cause */
    RMU_ClearStatus();
    MakeReset();
    /* Lock peripherals or registers */
    Peripheral_WP();
    /* Reset condition configuration finished */
    for (;;)
    {
        ;
    }
}

/**
 * @brief  Print reset information.
 * @param  None
 * @retval None
 */
static void PrintResetMode(void)
{
    if (Set == RMU_GetStatus(RMU_RST_MX))
    {
        (void)printf("Multiplex reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_CPU_LOCKUP))
    {
        (void)printf("M4 Lockup reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_XTAL_ERR))
    {
        (void)printf("Xtal error reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_CLK_ERR))
    {
        (void)printf("Clk frequence error reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_RAM_PARITY_ERR))
    {
        (void)printf("Ram parity error reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_SW))
    {
        (void)printf("Software reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_SWDT))
    {
        (void)printf("Special watchdog timer reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_WDT))
    {
        (void)printf("Watchdog timer reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_LVD2))
    {
        (void)printf("Low voltage Detection 2 reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_LVD1))
    {
        (void)printf("Low voltage Detection 1 reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_LVD0))
    {
        (void)printf("Low voltage Detection 0 reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_RST_PIN))
    {
        (void)printf("Reset pin reset.\r\n");
    }
    if (Set == RMU_GetStatus(RMU_RST_PWR_ON))
    {
        (void)printf("Power on reset.\r\n");
    }
}

/**
 * @brief  Make reset condition for test
 * @param  [in]  None
 * @retval None
 */
static void MakeReset(void)
{
#if (TEST_RESET_MODE == RESET_XTALERR)
    /* Config XTAL status detect error reset on*/
    stc_clock_xtalstd_init_t stcXtalStdCfg;
    stcXtalStdCfg.u8XtalStdState = CLK_XTALSTD_ON;
    stcXtalStdCfg.u8XtalStdExceptionType = CLK_XTALSTD_EXP_TYPE_RST;
    stcXtalStdCfg.u8XtalStdInt = CLK_XTALSTD_INT_OFF;
    stcXtalStdCfg.u8XtalStdRst = CLK_XTALSTD_RST_ON;
    (void)CLK_XtalStdInit(&stcXtalStdCfg);

#elif (TEST_RESET_MODE == RESET_SOFTWARERST)
    /* Software reset MCU */
    NVIC_SystemReset();

#elif (TEST_RESET_MODE == RESET_WDT)
    /* Config Watchdog timer */
    stc_wdt_init_t stcWdtInit;
    stcWdtInit.u32CountPeriod = WDT_CNT_PERIOD65536;
    stcWdtInit.u32ClockDiv = WDT_CLK_DIV1024;
    stcWdtInit.u32RefreshRange = WDT_RANGE_0TO100PCT;
    stcWdtInit.u32LPMCount = WDT_LPM_CNT_STOP;
    stcWdtInit.u32ExceptionType = WDT_EXP_TYPE_RST;

    (void)WDT_Init(&stcWdtInit);
    WDT_Feed();

#elif (TEST_RESET_MODE == RESET_LVD)
    stc_pwc_lvd_init_t  stcPwcLvdInit;
    (void)PWC_LVD_StructInit(&stcPwcLvdInit);
    /* Config LVD1 */
    stcPwcLvdInit.u32CompareOutput = PWC_LVD_CMP_OUTPUT_ENABLE;
    stcPwcLvdInit.u32ExceptionType = PWC_LVD_EXP_TYPE_RST;
    /* LVD voltage threshold falling 2.79V and rising 2.87V */
    stcPwcLvdInit.u32ThresholdVoltage = PWC_LVD_THRESHOLD_LVL7;
    stcPwcLvdInit.u32FilterEnable = PWC_LVD_FILTER_ENABLE;
    stcPwcLvdInit.u32FilterClock = PWC_LVD_FILTER_CLK_DIV4;
    stcPwcLvdInit.u32LvdDetectEdge = PWC_LVD_EDGE_BOTH;
    (void)PWC_LVD_Init(PWC_LVD1, &stcPwcLvdInit);
    PWC_LVD_IntResetCmd(PWC_LVD1, Enable);
    /* Enable LVD1 */
    PWC_LVD_Cmd(PWC_LVD1, Enable);

    /* Config LVD2 */
    stcPwcLvdInit.u32CompareOutput = PWC_LVD_CMP_OUTPUT_ENABLE;
    stcPwcLvdInit.u32ExceptionType = PWC_LVD_EXP_TYPE_RST;
    /* LVD voltage threshold falling 2.68V and rising 2.75V */
    stcPwcLvdInit.u32ThresholdVoltage = PWC_LVD_THRESHOLD_LVL8;
    stcPwcLvdInit.u32FilterEnable = PWC_LVD_FILTER_ENABLE;
    stcPwcLvdInit.u32FilterClock = PWC_LVD_FILTER_CLK_DIV4;
    stcPwcLvdInit.u32LvdDetectEdge = PWC_LVD_EDGE_BOTH;
    (void)PWC_LVD_Init(PWC_LVD2, &stcPwcLvdInit);
    PWC_LVD_IntResetCmd(PWC_LVD2, Enable);
    /* Enable LVD2 */
    PWC_LVD_Cmd(PWC_LVD2, Enable);

    (void)printf("LVD reset on, please make the power supply voltage lower than 2.6V\r\n");

#elif (TEST_RESET_MODE == RESET_CLKFREQERR)
    stc_fcm_init_t  stcFcmInit;
    (void)CLK_XtalCmd(Enable);
    /* Enable FCM peripheral */
    CLK_FcgPeriphClockCmd(CLK_FCG_FCM,Enable);
    (void)FCM_StructInit(&stcFcmInit);
    stcFcmInit.u16LowerLimit = ClockLowerLimit;
    stcFcmInit.u16UpperLimit = ClockUpperLimit;
    stcFcmInit.u32RefClock   = REF_FREQ;
    stcFcmInit.u32RefClockDiv = REF_DIV;
    stcFcmInit.u32RefClockEdge = FCM_REF_CLK_RISING;
    stcFcmInit.u32ExceptionType = FCM_EXP_TYPE_RST;
    stcFcmInit.u32TargetClock = TAR_FREQ;
    stcFcmInit.u32TargetClockDiv = TAR_DIV;
    (void)FCM_Init(&stcFcmInit);
    FCM_ResetCmd(Enable);

    /* Enable FCM function */
    FCM_Cmd(Enable);
#endif
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
