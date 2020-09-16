/**
 *******************************************************************************
 * @file  emb/emb_cmp_brake_timerb/source/main.c
 * @brief This example demonstrates how to use CMP brake function of EMB
 *        function.
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
 * @addtogroup EMB_CMP_Brake_TMRB
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* EMB unit for TMRB definition */
#define EMB_UNIT                        (CM_EMB1)

/* Function clock gate definition */
#define FUNC_CLK_GATE                   (CLK_FCG_CMP | CLK_FCG_EMB | CLK_FCG_TMRB)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static uint32_t TmrbPclkFreq(void);
static void TmrbPwmConfig(void);
static void EMB_IrqCallback(void);

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
 * @brief  Get TMR4 PCLK frequency.
 * @param  None
 * @retval None
 */
static uint32_t TmrbPclkFreq(void)
{
    stc_clock_freq_t stcClockFreq;

    (void)CLK_GetClockFreq(&stcClockFreq);
    return stcClockFreq.u32Pclk1Freq;
}

/**
 * @brief  Configure TMRB PWM
 * @param  None
 * @retval None
 */
static void TmrbPwmConfig(void)
{
    stc_tmrb_init_t stcTmrbInit;
    stc_tmrb_pwm_init_t stcTmrbPwmInit;

    /* Initialize TMRB. */
    stcTmrbInit.u16CountMode = TMRB_MD_SAWTOOTH;
    stcTmrbInit.u16ClockDiv = TMRB_CLK_DIV1024;
    stcTmrbInit.u16CountDir = TMRB_DIR_UP;
    stcTmrbInit.u16PeriodValue = ((uint16_t)(TmrbPclkFreq() / (1024UL) / 2UL)); /* Period_Value(500ms) */
    (void)TMRB_Init(CM_TMRB, &stcTmrbInit);

    /* Initialize TMRB PWM structure */
    (void)TMRB_PWM_StructInit(&stcTmrbPwmInit);
    stcTmrbPwmInit.u16CompareValue = (stcTmrbInit.u16PeriodValue/2U);
    stcTmrbPwmInit.u16StartPolarity = TMRB_PWM_HIGH;
    stcTmrbPwmInit.u16StopPolarity = TMRB_PWM_HIGH;
    stcTmrbPwmInit.u16MatchPolarity = TMRB_PWM_INVT;
    stcTmrbPwmInit.u16PeriodPolarity = TMRB_PWM_HOLD;

    /* Initialize TMRB odd/even channel pwm function. */
    (void)TMRB_PWM_Init(CM_TMRB, TMRB_CH1, &stcTmrbPwmInit);
    (void)TMRB_PWM_Init(CM_TMRB, TMRB_CH2, &stcTmrbPwmInit);

    /* Enable PWM port output */
    TMRB_PWM_Cmd(CM_TMRB, TMRB_CH1, Enable);
    TMRB_PWM_Cmd(CM_TMRB, TMRB_CH2, Enable);

    /* Start TMRB counter. */
    TMRB_Start(CM_TMRB);
}

/**
 * @brief  Configure CMP
 * @param  None
 * @retval None
 */
static void CmpConfig(void)
{
    stc_cmp_init_t stcCmpCfg;

    /* Port function configuration */
    GPIO_SetFunc(GPIO_PORT_4, GPIO_PIN_0, GPIO_FUNC_1_ANA); /* IVCMP1_0:P40 */

    /* Clear structure */
    (void)CMP_StructInit(&stcCmpCfg);

    /* De-initialize CMP unit */
    CMP_DeInit(CM_CMP1);

    /* Configuration for normal compare function */
    stcCmpCfg.u8CompareVoltage = CMP_CMP_VOLT_IVCMPx_0;
    stcCmpCfg.u8RefVoltage = CMP_REF_VOLT_DAC;
    stcCmpCfg.u8OutDetectEdges = CMP_DETECT_EDGE_BOTH;
    stcCmpCfg.u8OutFilter = CMP_OUT_FILTER_CLK_DIV32;
    stcCmpCfg.u8OutPolarity = CMP_OUT_POLARITY_REVS;
    (void)CMP_NormalModeInit(CM_CMP1, &stcCmpCfg);

    /* Config 8 bit DAC for reference voltage */
    CMP_DAC_RightAlignWriteData(0x7FU);
    CMP_DAC_SetAlign(CMP_DAC_ALIGN_RIGHT);
    CMP_DAC_Cmd(Enable);

    /* Enable Voltage compare output port VCOUT function */
    CMP_VCOUTCmd(CM_CMP1, Enable);

    /* Enable CMP output */
    CMP_OutputCmd(CM_CMP1, Enable);
}

/**
 * @brief  EMB IRQ callback function.
 * @param  None
 * @retval None
 */
static void EMB_IrqCallback(void)
{
    if(Set == EMB_GetStatus(EMB_UNIT, EMB_FLAG_CMP))
    {
        EMB_ClearStatus(EMB_UNIT, EMB_FLAG_CMP);  /* Clear CMP Brake */
    }
}

/**
 * @brief  Main function of EMB CMP brake TMRB
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_emb_tmrb_init_t stcEmbInit;
    stc_irq_signin_config_t stcIrqConfig;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize system clock. */
    BSP_CLK_Init();

    /* Initialize key. */
    BSP_KEY_Init(BSP_KEY_MD_GPIO);

    /* Configure TIM_<t>_PWMn(n=1~4). */
    GPIO_SetFunc(GPIO_PORT_7, GPIO_PIN_2, GPIO_FUNC_3_TIMB1); /* P72: TIMB_1_PWM1 */
    GPIO_SetFunc(GPIO_PORT_7, GPIO_PIN_5, GPIO_FUNC_3_TIMB1); /* P75: TIMB_1_PWM2 */

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNC_CLK_GATE, Enable);

    /* Configure CMP. */
    CmpConfig();

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Configure TMRB PWM. */
    TmrbPwmConfig();

    /* EMB: initialize */
    (void)EMB_TmrbStructInit(&stcEmbInit);
    stcEmbInit.u32Cmp1 = EMB_CMP1_ENABLE;
    stcEmbInit.u32EmbPolarity = EMB_TMRB_PWM_LOW;
    (void)EMB_TmrbInit(EMB_UNIT, &stcEmbInit);

    /* EMB: enable interrupt */
    EMB_IntCmd(EMB_UNIT, EMB_INT_CMP, Enable);

    /* EMB: register IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = INT000_IRQn;
    stcIrqConfig.enIntSrc = INT_EMB;
    stcIrqConfig.pfnCallback = &EMB_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqConfig);
    NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
    NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(stcIrqConfig.enIRQn);

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
