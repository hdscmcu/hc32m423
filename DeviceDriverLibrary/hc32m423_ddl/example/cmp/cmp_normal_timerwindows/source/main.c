/**
 *******************************************************************************
 * @file  cmp/cmp_normal_timerwindows/source/main.c
 * @brief Main program of CMP for the Device Driver Library.
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
 * @addtogroup CMP_Normal_TimerWindows
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CMP_TEST_UNIT                   (CM_CMP3)

/* Define port and pin for CMP */
/* VCOUT3*/
#define CMP_VCOUT3_PORT                 (GPIO_PORT_A)
#define CMP_VCOUT3_PIN                  (GPIO_PIN_2)
/* IVCMP1_0 */
#define IVCMP3_0_PORT                   (GPIO_PORT_4)
#define IVCMP3_0_PIN                    (GPIO_PIN_2)
/* IREF1 */
#define IVREF1_PORT                     (GPIO_PORT_1)
#define IVREF1_PIN                      (GPIO_PIN_1)

/* TIM4 PWM Port/Pin definition */
#define TIM4_OXH_PORT                   (GPIO_PORT_7)
#define TIM4_OXH_PIN                    (GPIO_PIN_1)
#define TIM4_OXH_GPIO_FUNC              (GPIO_FUNC_2_TIM4)

#define TIM4_OXL_PORT                   (GPIO_PORT_7)
#define TIM4_OXL_PIN                    (GPIO_PIN_4)
#define TIM4_OXL_GPIO_FUNC              (GPIO_FUNC_2_TIM4)

/* TMR4 unit && fcg && counter period value definition */
#define TMR4_UNIT                       (CM_TMR4)
#define TMR4_FUNCTION_CLK_GATE          (CLK_FCG_TMR4)
#define TMR4_CNT_PERIOD_VALUE(div)      ((uint16_t)(Tmr4PclkFreq() / (1UL << (uint32_t)(div)) / 4UL)) /* Period_Value(250ms) */

/* TMR4 OCO Channel definition */
#define TMR4_OCO_HIGH_CH                (TMR4_OCO_CH_UH)

/* TMR4 PWM get channel by OCO high channel */
#define TMR4_PWM_CH(x)                  (((x) == TMR4_OCO_CH_UH) ? TMR4_PWM_CH_U : \
                                         (((x) == TMR4_OCO_CH_VH) ? TMR4_PWM_CH_V : TMR4_PWM_CH_W))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static uint32_t Tmr4PclkFreq(void);
static void timer4_pwm_Init(void);

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
    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1|PWC_UNLOCK_CODE_2);
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
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1|PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Get TMR4 PCLK frequency.
 * @param  None
 * @retval None
 */
static uint32_t Tmr4PclkFreq(void)
{
    stc_clock_freq_t stcClkFreq;

    (void)CLK_GetClockFreq(&stcClkFreq);
    return stcClkFreq.u32Pclk1Freq;
}

/**
 * @brief  Timer4 initialize for CMP timer window function.
 * @param  None
 * @retval None
 */
static void timer4_pwm_Init(void)
{
    uint32_t u32PwmCh;
    const uint32_t u32OcoLowCh = TMR4_OCO_HIGH_CH + 1UL;
    stc_tmr4_cnt_init_t stcTmr4CntInit;
    stc_tmr4_oco_init_t stcTmr4OcoInit;
    stc_tmr4_pwm_init_t stcTmr4PwmInit;
    stc_oco_high_ch_compare_mode_t stcHighChCmpMode;
    stc_oco_low_ch_compare_mode_t stcLowChCmpMode;

    /* Initialize PWM I/O */
    GPIO_SetFunc(TIM4_OXH_PORT, TIM4_OXH_PIN, TIM4_OXH_GPIO_FUNC);
    GPIO_SetFunc(TIM4_OXL_PORT, TIM4_OXL_PIN, TIM4_OXL_GPIO_FUNC);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(TMR4_FUNCTION_CLK_GATE, Enable);

    /************************* Configure TMR4 counter *************************/
    /* TMR4 counter: initialize */
    (void)TMR4_CNT_StructInit(&stcTmr4CntInit);
    stcTmr4CntInit.u16ClockDiv = TMR4_CNT_CLK_DIV1024;
    stcTmr4CntInit.u16PeriodValue = TMR4_CNT_PERIOD_VALUE(stcTmr4CntInit.u16ClockDiv);
    (void)TMR4_CNT_Init(TMR4_UNIT, &stcTmr4CntInit);

    /************************* Configure TMR4 OCO *****************************/
    /* TMR4 OCO channel: initialize TMR4 structure */
    (void)TMR4_OCO_StructInit(&stcTmr4OcoInit);
    stcTmr4OcoInit.u16CompareValue = (stcTmr4CntInit.u16PeriodValue/2U);

    /* TMR4 OCO channel: initialize channel */
    (void)TMR4_OCO_Init(TMR4_UNIT, TMR4_OCO_HIGH_CH, &stcTmr4OcoInit);
    (void)TMR4_OCO_Init(TMR4_UNIT, u32OcoLowCh, &stcTmr4OcoInit);

    /* TMR4 OCO high channel: compare mode OCMR[15:0] = 0x0FFF = b 0000 1111 1111 1111 */
    stcHighChCmpMode.OCMRx_f.OCFDCH = TMR4_OCO_OCF_SET; /* bit[0]     1  */
    stcHighChCmpMode.OCMRx_f.OCFPKH = TMR4_OCO_OCF_SET; /* bit[1]     1  */
    stcHighChCmpMode.OCMRx_f.OCFUCH = TMR4_OCO_OCF_SET; /* bit[2]     1  */
    stcHighChCmpMode.OCMRx_f.OCFZRH = TMR4_OCO_OCF_SET; /* bit[3]     1  */
    stcHighChCmpMode.OCMRx_f.OPDCH  = TMR4_OCO_INVT;    /* Bit[5:4]   11 */
    stcHighChCmpMode.OCMRx_f.OPPKH  = TMR4_OCO_INVT;    /* Bit[7:6]   11 */
    stcHighChCmpMode.OCMRx_f.OPUCH  = TMR4_OCO_INVT;    /* Bit[9:8]   11 */
    stcHighChCmpMode.OCMRx_f.OPZRH  = TMR4_OCO_INVT;    /* Bit[11:10] 11 */
    stcHighChCmpMode.OCMRx_f.OPNPKH = TMR4_OCO_HOLD;    /* Bit[13:12] 00 */
    stcHighChCmpMode.OCMRx_f.OPNZRH = TMR4_OCO_HOLD;    /* Bit[15:14] 00 */
    (void)TMR4_OCO_SetHighChCompareMode(TMR4_UNIT, TMR4_OCO_HIGH_CH, &stcHighChCmpMode);  /* Set OCO high channel compare mode */

    /* TMR4 OCO low channel: compare mode OCMR[31:0] 0x0FF0 0FFF = b 0000 1111 1111 0000   0000 1111 1111 1111 */
    stcLowChCmpMode.OCMRx_f.OCFDCL  = TMR4_OCO_OCF_SET; /* bit[0]     1  */
    stcLowChCmpMode.OCMRx_f.OCFPKL  = TMR4_OCO_OCF_SET; /* bit[1]     1  */
    stcLowChCmpMode.OCMRx_f.OCFUCL  = TMR4_OCO_OCF_SET; /* bit[2]     1  */
    stcLowChCmpMode.OCMRx_f.OCFZRL  = TMR4_OCO_OCF_SET; /* bit[3]     1  */
    stcLowChCmpMode.OCMRx_f.OPDCL   = TMR4_OCO_INVT;    /* bit[5:4]   11 */
    stcLowChCmpMode.OCMRx_f.OPPKL   = TMR4_OCO_INVT;    /* bit[7:6]   11 */
    stcLowChCmpMode.OCMRx_f.OPUCL   = TMR4_OCO_INVT;    /* bit[9:8]   11 */
    stcLowChCmpMode.OCMRx_f.OPZRL   = TMR4_OCO_INVT;    /* bit[11:10] 11 */
    stcLowChCmpMode.OCMRx_f.OPNPKL  = TMR4_OCO_HOLD;    /* bit[13:12] 00 */
    stcLowChCmpMode.OCMRx_f.OPNZRL  = TMR4_OCO_HOLD;    /* bit[15:14] 00 */
    stcLowChCmpMode.OCMRx_f.EOPNDCL = TMR4_OCO_HOLD;    /* bit[17:16] 00 */
    stcLowChCmpMode.OCMRx_f.EOPNUCL = TMR4_OCO_HOLD;    /* bit[19:18] 00 */
    stcLowChCmpMode.OCMRx_f.EOPDCL  = TMR4_OCO_INVT;    /* bit[21:20] 11 */
    stcLowChCmpMode.OCMRx_f.EOPPKL  = TMR4_OCO_INVT;    /* bit[23:22] 11 */
    stcLowChCmpMode.OCMRx_f.EOPUCL  = TMR4_OCO_INVT;    /* bit[25:24] 11 */
    stcLowChCmpMode.OCMRx_f.EOPZRL  = TMR4_OCO_INVT;    /* bit[27:26] 11 */
    stcLowChCmpMode.OCMRx_f.EOPNPKL = TMR4_OCO_HOLD;    /* bit[29:28] 00 */
    stcLowChCmpMode.OCMRx_f.EOPNZRL = TMR4_OCO_HOLD;    /* bit[31:30] 00 */
    (void)TMR4_OCO_SetLowChCompareMode(TMR4_UNIT, u32OcoLowCh, &stcLowChCmpMode);  /* Set OCO low channel compare mode */

    /* TMR4 OCO: enable */
    TMR4_OCO_Cmd(TMR4_UNIT, TMR4_OCO_HIGH_CH, Enable);
    TMR4_OCO_Cmd(TMR4_UNIT, u32OcoLowCh, Enable);

    /************************* Configure TMR4 PWM *****************************/
    /* TMR4 PWM: get pwm couple channel */
    u32PwmCh = TMR4_PWM_CH(TMR4_OCO_HIGH_CH);

    /* TMR4 PWM: initialize */
    (void)TMR4_PWM_StructInit(&stcTmr4PwmInit);
    stcTmr4PwmInit.u16Mode = TMR4_PWM_MD_THROUGH;
    (void)TMR4_PWM_Init(TMR4_UNIT, u32PwmCh, &stcTmr4PwmInit);

    /* Start TMR4 counter. */
    TMR4_CNT_Start(TMR4_UNIT);
}

/**
 * @brief  Main function of cmp_normal_timerwindows project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_cmp_init_t stcCmpCfg;
    stc_cmp_timerwindows_t stcTimerWindowsIni;

    /* Register write unprotected for some required peripherals. */
    Peripheral_WE();
    /* System clock Init */
    BSP_CLK_Init();

    /* Port function configuration */
    GPIO_SetFunc(CMP_VCOUT3_PORT, CMP_VCOUT3_PIN, GPIO_FUNC_1_VCOUT);
    GPIO_SetFunc(IVCMP3_0_PORT, IVCMP3_0_PIN, GPIO_FUNC_1_ANA);
    //GPIO_SetFunc(IVREF1_PORT, IVREF1_PIN, GPIO_FUNC_1_ANA);

    /* Enable peripheral clock for CMP*/
    CLK_FcgPeriphClockCmd(CLK_FCG_CMP, Enable);

    /* Clear structure */
    (void)CMP_StructInit(&stcCmpCfg);
    /* De-initialize CMP unit */
    CMP_DeInit(CMP_TEST_UNIT);

    /* Configuration for normal compare function */
    stcCmpCfg.u8CompareVoltage = CMP_CMP_VOLT_IVCMPx_0;
    stcCmpCfg.u8RefVoltage = CMP_REF_VOLT_DAC;
    stcCmpCfg.u8OutDetectEdges = CMP_DETECT_EDGE_BOTH;
    stcCmpCfg.u8OutFilter = CMP_OUT_FILTER_CLK_DIV8;
    stcCmpCfg.u8OutPolarity = CMP_OUT_POLARITY_NORMAL;
    (void)CMP_NormalModeInit(CMP_TEST_UNIT, &stcCmpCfg);

    /* 8 bit DAC config and command */
    CMP_DAC_RightAlignWriteData(0x7FU);
    CMP_DAC_SetAlign(CMP_DAC_ALIGN_RIGHT);
    CMP_DAC_Cmd(Enable);
    DDL_DelayMS(5U);

    /* Enable VCOUT if need */
    CMP_VCOUTCmd(CMP_TEST_UNIT, Enable);

    /* Timer windows function configuration if need */
    stcTimerWindowsIni.u8TimerWinSignal = CMP_TMR_WIN_TIM4_OUH;
    stcTimerWindowsIni.u8TimerWinValidLevel = CMP_TMR_WIN_SIGNAL_VALID_HIGH;
    stcTimerWindowsIni.u8TWInvalidLevel = CMP_TMR_WIN_INVD_OUT_HIGH;
    (void)CMP_TimerWindowConfig(CMP_TEST_UNIT, &stcTimerWindowsIni);
    CMP_TimerWindowCmd(CMP_TEST_UNIT, Enable);

    /* Initialize timer4 pwm output */
    timer4_pwm_Init();

    /* Enable CMP output */
    CMP_OutputCmd(CMP_TEST_UNIT, Enable);

    /* Register write protected */
    Peripheral_WP();

    /* Configuration finished */
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
