/**
 *******************************************************************************
 * @file  emb/emb_pwm_brake_timer4/source/main.c
 * @brief This example demonstrates how to use the PWM same phase brake function
 *        of EMB function.
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
 * @addtogroup EMB_PWM_Brake_TMR4
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* EMB unit for TMR4 definition */
#define EMB_UNIT                        (CM_EMB0)

/* Function clock gate definition */
#define FUNC_CLK_GATE                   (CLK_FCG_EMB | CLK_FCG_TMR4)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static en_flag_status_t KeyState(void);
static uint32_t Tmr4PclkFreq(void);
static void Tmr4PwmConfig(void);
static void EMB_IrqCallback(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static __IO uint8_t m_u8EmbFlag = 0U;

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
 *           - Set:   Released after key is pressed
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
 * @brief  Get TMR4 PCLK frequency.
 * @param  None
 * @retval None
 */
static uint32_t Tmr4PclkFreq(void)
{
    stc_clock_freq_t stcClockFreq;

    (void)CLK_GetClockFreq(&stcClockFreq);
    return stcClockFreq.u32Pclk1Freq;
}

/**
 * @brief  Configure TMR4 PWM
 * @param  None
 * @retval None
 */
static void Tmr4PwmConfig(void)
{
    stc_tmr4_cnt_init_t stcTmr4CntInit;
    stc_tmr4_oco_init_t stcTmr4OcoInit;
    stc_tmr4_pwm_init_t stcTmr4PwmInit;
    stc_oco_low_ch_compare_mode_t stcLowChCmpMode;
    stc_oco_high_ch_compare_mode_t stcHighChCmpMode;

    /************************* Configure TMR4 counter *************************/
    (void)TMR4_CNT_StructInit(&stcTmr4CntInit);
    stcTmr4CntInit.u16ClockDiv = TMR4_CNT_CLK_DIV1024;
    stcTmr4CntInit.u16PeriodValue = ((uint16_t)(Tmr4PclkFreq() / (1UL << (uint32_t)(stcTmr4CntInit.u16ClockDiv)) / 2UL));
    (void)TMR4_CNT_Init(CM_TMR4, &stcTmr4CntInit);

    /************************* Configure TMR4 OCO *****************************/
    /* TMR4 OCO channel: initialize channel */
    (void)TMR4_OCO_StructInit(&stcTmr4OcoInit);
    stcTmr4OcoInit.u16CompareValue = (stcTmr4CntInit.u16PeriodValue/2U);
    (void)TMR4_OCO_Init(CM_TMR4, TMR4_OCO_CH_UH, &stcTmr4OcoInit);
    (void)TMR4_OCO_Init(CM_TMR4, TMR4_OCO_CH_UL, &stcTmr4OcoInit);

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
    (void)TMR4_OCO_SetHighChCompareMode(CM_TMR4, TMR4_OCO_CH_UH, &stcHighChCmpMode);

    /* TMR4 OCO low channel: compare mode OCMR[31:0] 0x0FF0 0FFF = b 0000 1111 1111 0000   0000 1111 1111 1111 */
    stcLowChCmpMode.OCMRx_f.OCFDCL  = TMR4_OCO_OCF_SET;  /* bit[0]     1  */
    stcLowChCmpMode.OCMRx_f.OCFPKL  = TMR4_OCO_OCF_SET;  /* bit[1]     1  */
    stcLowChCmpMode.OCMRx_f.OCFUCL  = TMR4_OCO_OCF_SET;  /* bit[2]     1  */
    stcLowChCmpMode.OCMRx_f.OCFZRL  = TMR4_OCO_OCF_SET;  /* bit[3]     1  */
    stcLowChCmpMode.OCMRx_f.OPDCL   = TMR4_OCO_INVT;     /* bit[5:4]   11 */
    stcLowChCmpMode.OCMRx_f.OPPKL   = TMR4_OCO_INVT;     /* bit[7:6]   11 */
    stcLowChCmpMode.OCMRx_f.OPUCL   = TMR4_OCO_INVT;     /* bit[9:8]   11 */
    stcLowChCmpMode.OCMRx_f.OPZRL   = TMR4_OCO_INVT;     /* bit[11:10] 11 */
    stcLowChCmpMode.OCMRx_f.OPNPKL  = TMR4_OCO_HOLD;     /* bit[13:12] 00 */
    stcLowChCmpMode.OCMRx_f.OPNZRL  = TMR4_OCO_HOLD;     /* bit[15:14] 00 */
    stcLowChCmpMode.OCMRx_f.EOPNDCL = TMR4_OCO_HOLD;     /* bit[17:16] 00 */
    stcLowChCmpMode.OCMRx_f.EOPNUCL = TMR4_OCO_HOLD;     /* bit[19:18] 00 */
    stcLowChCmpMode.OCMRx_f.EOPDCL  = TMR4_OCO_INVT;     /* bit[21:20] 11 */
    stcLowChCmpMode.OCMRx_f.EOPPKL  = TMR4_OCO_INVT;     /* bit[23:22] 11 */
    stcLowChCmpMode.OCMRx_f.EOPUCL  = TMR4_OCO_INVT;     /* bit[25:24] 11 */
    stcLowChCmpMode.OCMRx_f.EOPZRL  = TMR4_OCO_INVT;     /* bit[27:26] 11 */
    stcLowChCmpMode.OCMRx_f.EOPNPKL = TMR4_OCO_HOLD;     /* bit[29:28] 00 */
    stcLowChCmpMode.OCMRx_f.EOPNZRL = TMR4_OCO_HOLD;     /* bit[31:30] 00 */
    (void)TMR4_OCO_SetLowChCompareMode(CM_TMR4, TMR4_OCO_CH_UL, &stcLowChCmpMode);

    /* TMR4 OCO: enable */
    TMR4_OCO_Cmd(CM_TMR4, TMR4_OCO_CH_UH, Enable);
    TMR4_OCO_Cmd(CM_TMR4, TMR4_OCO_CH_UL, Enable);

    /************************* Configure TMR4 PWM *****************************/
    /* TMR4 PWM: initialize */
    (void)TMR4_PWM_StructInit(&stcTmr4PwmInit);
    stcTmr4PwmInit.u16Polarity = TMR4_PWM_OXH_HOLD_OXL_INVT;
    stcTmr4PwmInit.u32OXHPortOutMode = TMR4_PWM_PORT_OUTPUT_NORMAL;
    stcTmr4PwmInit.u32OXLPortOutMode = TMR4_PWM_PORT_OUTPUT_NORMAL;
    stcTmr4PwmInit.u32OXHAbnormalPolarity = TMR4_PWM_ABNORMAL_POLARITY_LOW;
    stcTmr4PwmInit.u32OXLAbnormalPolarity = TMR4_PWM_ABNORMAL_POLARITY_LOW;
    (void)TMR4_PWM_Init(CM_TMR4, TMR4_PWM_CH_U, &stcTmr4PwmInit);

    /* TMR4 PWM: set EMB release mode output */
    TMR4_PWM_SetEmbReleaseMode(CM_TMR4, TMR4_PWM_EMB_RELEASE_MD_HW_MOE);

    /* Timer4 PWM: enable master output */
    TMR4_PWM_MasterOutputCmd(CM_TMR4, Enable);

    /* Start TMR4 counter. */
    TMR4_CNT_Start(CM_TMR4);
}

/**
 * @brief  EMB IRQ callback function.
 * @param  None
 * @retval None
 */
static void EMB_IrqCallback(void)
{
    if(Set == EMB_GetStatus(EMB_UNIT, EMB_FLAG_PWMS))
    {
        m_u8EmbFlag = 1U;

        while (Set != KeyState())
        {
        }

        TMR4_PWM_SetPolarity(CM_TMR4, TMR4_PWM_CH_U, TMR4_PWM_OXH_HOLD_OXL_INVT);

        /* Clear PWM Brake */
        EMB_ClearStatus(EMB_UNIT, EMB_FLAG_PWMS);
    }
}

/**
 * @brief  Main function of EMB PWM brake
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_emb_tmr4_init_t stcEmbInit;
    stc_irq_signin_config_t stcIrqConfig;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize system clock. */
    BSP_CLK_Init();

    /* Initialize key. */
    BSP_KEY_Init(BSP_KEY_MD_GPIO);

    /* Initialize PWM I/O */
    GPIO_SetFunc(GPIO_PORT_7, GPIO_PIN_1, GPIO_FUNC_2_TIM4);
    GPIO_SetFunc(GPIO_PORT_7, GPIO_PIN_4, GPIO_FUNC_2_TIM4);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNC_CLK_GATE, Enable);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Configure TMR4 PWM. */
    Tmr4PwmConfig();

    /* EMB: initialize */
    (void)EMB_Tmr4StructInit(&stcEmbInit);
    stcEmbInit.stcTmr4PwmU.u32Pwm = EMB_TMR4_PWM_U_ENABLE;
    stcEmbInit.stcTmr4PwmU.u32PwmLevel = EMB_DETECT_TMR4_PWM_U_BOTH_HIGH;
    (void)EMB_Tmr4Init(EMB_UNIT, &stcEmbInit);

    /* EMB: enable interrupt */
    EMB_IntCmd(EMB_UNIT, EMB_INT_PWMS, Enable);

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
        /* Wait key release */
        while (Set != KeyState())
        {
        }

        TMR4_PWM_SetPolarity(CM_TMR4, TMR4_PWM_CH_U, TMR4_PWM_OXH_HOLD_OXL_HOLD);

        while (0U == m_u8EmbFlag)
        {
        }

        m_u8EmbFlag = 0U;
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
