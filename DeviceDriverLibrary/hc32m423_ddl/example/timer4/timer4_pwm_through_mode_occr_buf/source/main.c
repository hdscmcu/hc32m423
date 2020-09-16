/**
 *******************************************************************************
 * @file  timer4/timer4_pwm_through_mode_occr_buf/source/main.c
 * @brief This example demonstrates how to use the through mode function of
 *        Timer4 PWM function and enable OCCR buffer function.
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
 * @addtogroup TMR4_PWM_Through_Mode_With_OCCR_Buffer
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* TIM4 PWM Port/Pin definition */
#define TIM4_OXH_PORT                   (GPIO_PORT_7)
#define TIM4_OXH_PIN                    (GPIO_PIN_1)
#define TIM4_OXH_GPIO_FUNC              (GPIO_FUNC_2_TIM4)

/* TMR4 unit && interrupt number && fcg && counter period value definition */
#define TMR4_UNIT                       (CM_TMR4)
#define TMR4_CNT_UDF_IRQn               (INT000_IRQn)
#define TMR4_CNT_UDF_INT                (INT_TMR4_GUDF)
#define TMR4_FUNC_CLK_GATE              (CLK_FCG_TMR4)
#define TMR4_CNT_PERIOD_VALUE(div)      ((uint16_t)(Tmr4PclkFreq() / (1UL << (uint32_t)(div)) / 4UL)) /* Period_Value(250ms) */

/* TMR4 OCO Channel definition */
#define TMR4_OCO_HIGH_CH                (TMR4_OCO_CH_UH)

#define TMR4_OCO_CMP_BUF_SIZE           (3U)

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
static void TMR4_ZeroMatch_IrqCallback(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint16_t m_u16OcoCmpValueIdx = 0U;
static uint16_t m_au16OcoCmpValue[TMR4_OCO_CMP_BUF_SIZE];

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
static uint32_t Tmr4PclkFreq(void)
{
    stc_clock_freq_t stcClockFreq;

    (void)CLK_GetClockFreq(&stcClockFreq);
    return stcClockFreq.u32Pclk1Freq;
}

/**
 * @brief  TMR4 Counter zero match interrupt handler callback.
 * @param  None
 * @retval None
 */
static void TMR4_ZeroMatch_IrqCallback(void)
{
    TMR4_CNT_ClearStatus(TMR4_UNIT, TMR4_CNT_FLAG_ZERO);
    TMR4_OCO_SetCompareValue(TMR4_UNIT, TMR4_OCO_HIGH_CH, m_au16OcoCmpValue[m_u16OcoCmpValueIdx]);

    ++m_u16OcoCmpValueIdx;

    if (m_u16OcoCmpValueIdx >= TMR4_OCO_CMP_BUF_SIZE)
    {
        m_u16OcoCmpValueIdx = 0U;
    }
}

/**
 * @brief  Main function of TMR4 PWM through mode with OCCR buffer
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t u32PwmCh;
    stc_irq_signin_config_t stcIrqConfig;
    stc_tmr4_cnt_init_t stcTmr4CntInit;
    stc_tmr4_oco_init_t stcTmr4OcoInit;
    stc_tmr4_pwm_init_t stcTmr4PwmInit;
    stc_oco_high_ch_compare_mode_t stcHighChCmpMode;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize clock. */
    BSP_CLK_Init();

    /* Initialize PWM I/O */
    GPIO_SetFunc(TIM4_OXH_PORT, TIM4_OXH_PIN, TIM4_OXH_GPIO_FUNC);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(TMR4_FUNC_CLK_GATE, Enable);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /************************* Configure TMR4 counter *************************/
    /* TMR4 counter: initialize */
    (void)TMR4_CNT_StructInit(&stcTmr4CntInit);
    stcTmr4CntInit.u16ClockDiv = TMR4_CNT_CLK_DIV1024;
    stcTmr4CntInit.u16PeriodValue = TMR4_CNT_PERIOD_VALUE(stcTmr4CntInit.u16ClockDiv);
    (void)TMR4_CNT_Init(TMR4_UNIT, &stcTmr4CntInit);
    TMR4_CNT_IntCmd(TMR4_UNIT, TMR4_CNT_INT_ZERO, Enable);

    /* TMR4 counter: register IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = TMR4_CNT_UDF_IRQn;
    stcIrqConfig.enIntSrc = TMR4_CNT_UDF_INT;
    stcIrqConfig.pfnCallback = &TMR4_ZeroMatch_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqConfig);
    NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
    NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(stcIrqConfig.enIRQn);

    /************************* Configure TMR4 OCO *****************************/
    /* Set OCO compare value buffer */
    m_au16OcoCmpValue[0] = 1U * (stcTmr4CntInit.u16PeriodValue / 4U);
    m_au16OcoCmpValue[1] = 2U * (stcTmr4CntInit.u16PeriodValue / 4U);
    m_au16OcoCmpValue[2] = 3U * (stcTmr4CntInit.u16PeriodValue / 4U);

    /* TMR4 OCO high channel: initialize */
    (void)TMR4_OCO_StructInit(&stcTmr4OcoInit);
    stcTmr4OcoInit.u16CompareValueBufCond = TMR4_OCO_BUF_COND_OVF;
    stcTmr4OcoInit.u16CompareValue = m_au16OcoCmpValue[m_u16OcoCmpValueIdx];
    (void)TMR4_OCO_Init(TMR4_UNIT, TMR4_OCO_HIGH_CH, &stcTmr4OcoInit);

    m_u16OcoCmpValueIdx++;

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

    /* Enable TMR4 OCO high channel */
    TMR4_OCO_Cmd(TMR4_UNIT, TMR4_OCO_HIGH_CH, Enable);

    /************************* Configure TMR4 PWM *****************************/
    /* TMR4 PWM: get pwm couple channel */
    u32PwmCh = TMR4_PWM_CH(TMR4_OCO_HIGH_CH);

    /* TMR4 PWM: initialize  */
    (void)TMR4_PWM_StructInit(&stcTmr4PwmInit);
    (void)TMR4_PWM_Init(TMR4_UNIT, u32PwmCh, &stcTmr4PwmInit);

    /* Start TMR4 counter. */
    TMR4_CNT_Start(TMR4_UNIT);

    /* Set OCO compare value */
    TMR4_OCO_SetCompareValue(TMR4_UNIT, TMR4_OCO_HIGH_CH, m_au16OcoCmpValue[m_u16OcoCmpValueIdx]);

    m_u16OcoCmpValueIdx++;

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
