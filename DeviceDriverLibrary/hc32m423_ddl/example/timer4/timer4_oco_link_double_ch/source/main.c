/**
 *******************************************************************************
 * @file  timer4/timer4_oco_link_double_ch/source/main.c
 * @brief This example demonstrates how to use the link double channel of Timer4
 *        OCO function.
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
 * @addtogroup TMR4_OCO_Link_Double_Channels
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Wave I/O Port/Pin definition */
#define WAVE_IO_PORT                    (GPIO_PORT_7)
#define WAVE_IO_PIN                     (GPIO_PIN_1)
#define WAVE_IO_TOGGLE()                do {        \
    GPIO_TogglePins(WAVE_IO_PORT, WAVE_IO_PIN);     \
} while(0)

/* TMR4 unit& fcg & counter period value definition */
#define TMR4_UNIT                       (CM_TMR4)
#define TMR4_FUNC_CLK_GATE              (CLK_FCG_TMR4)
#define TMR4_CNT_PERIOD_VALUE(div)      ((uint16_t)((Tmr4PclkFreq() /  (1UL << (uint32_t)(div)) / 4UL))) /* Period_Value(250ms) */

/* TMR4 OCO Channel definition */
#define TMR4_OCO_HIGH_CH                (TMR4_OCO_CH_UH)
#define TMR4_OCO_LOW_CH                 (TMR4_OCO_HIGH_CH + 1UL)

/* TMR4 OCO interrupt source definition */
#define TMR4_OCO_HIGH_CH_INT_SRC        (INT_TMR4_GCMUH)
#define TMR4_OCO_LOW_CH_INT_SRC         (INT_TMR4_GCMUL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);
static void WaveIoConfig(void);
static uint32_t Tmr4PclkFreq(void);
static void TMR4_OCO_IrqCallback(void);
static void InstalIrqHandler(const stc_irq_signin_config_t *pstcConfig,
                                 uint32_t u32Priority);

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
 * @brief  Configure Wave I/O.
 * @param  None
 * @retval None
 */
static void WaveIoConfig(void)
{
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STAT_RST;
    (void)GPIO_Init(WAVE_IO_PORT, WAVE_IO_PIN, &stcGpioInit);
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
 * @brief  TMR4 OCO match interrupt handler callback.
 * @param  None
 * @retval None
 */
static void TMR4_OCO_IrqCallback(void)
{
    static uint16_t m_u16OcoPolarity = TMR4_OCO_INVD_LOW;
    const uint16_t u16CurrentPolarity = TMR4_OCO_GetPolarity(TMR4_UNIT, TMR4_OCO_LOW_CH);

    if (m_u16OcoPolarity != u16CurrentPolarity)
    {
        WAVE_IO_TOGGLE();
        m_u16OcoPolarity = u16CurrentPolarity;
    }

    TMR4_OCO_ClearStatus(TMR4_UNIT, TMR4_OCO_LOW_CH);
    TMR4_OCO_ClearStatus(TMR4_UNIT, TMR4_OCO_LOW_CH - 1UL);
}

/**
 * @brief  Instal IRQ handler.
 * @param  [in] pstcConfig      Pointer to struct @ref stc_irq_signin_config_t
 * @param  [in] u32Priority     Interrupt priority
 * @retval None
 */
static void InstalIrqHandler(const stc_irq_signin_config_t *pstcConfig,
                                 uint32_t u32Priority)
{
    if (NULL != pstcConfig)
    {
        (void)INTC_IrqSignIn(pstcConfig);
        NVIC_ClearPendingIRQ(pstcConfig->enIRQn);
        NVIC_SetPriority(pstcConfig->enIRQn, u32Priority);
        NVIC_EnableIRQ(pstcConfig->enIRQn);
    }
}

/**
 * @brief  Main function of TMR4 OCO link double channels
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_irq_signin_config_t stcIrqConfig;
    stc_tmr4_cnt_init_t stcTmr4CntInit;
    stc_tmr4_oco_init_t stcTmr4OcoInit;
    stc_oco_high_ch_compare_mode_t stcHighChCmpMode;
    stc_oco_low_ch_compare_mode_t stcLowChCmpMode;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize clock. */
    BSP_CLK_Init();

    /* Configure Wave I/O. */
    WaveIoConfig();

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(TMR4_FUNC_CLK_GATE, Enable);

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /************************* Configure TMR4 counter *************************/
    (void)TMR4_CNT_StructInit(&stcTmr4CntInit);
    stcTmr4CntInit.u16ClockDiv = TMR4_CNT_CLK_DIV1024;
    stcTmr4CntInit.u16PeriodValue = TMR4_CNT_PERIOD_VALUE(stcTmr4CntInit.u16ClockDiv);
    (void)TMR4_CNT_Init(TMR4_UNIT, &stcTmr4CntInit);

    /************************* Configure TMR4 OCO *****************************/
    /* Initialize TMR4 OCO structure */
    (void)TMR4_OCO_StructInit(&stcTmr4OcoInit);

    /* TMR4 OCO high/low channel: initialize */
    stcTmr4OcoInit.u16CompareValue = stcTmr4CntInit.u16PeriodValue / 4U;
    (void)TMR4_OCO_Init(TMR4_UNIT, TMR4_OCO_HIGH_CH, &stcTmr4OcoInit);

    stcTmr4OcoInit.u16CompareValue = (stcTmr4CntInit.u16PeriodValue / 4U) * 3U;
    (void)TMR4_OCO_Init(TMR4_UNIT, TMR4_OCO_LOW_CH, &stcTmr4OcoInit);

    /* TMR4 OCO high channel: compare mode OCMR[15:0] = 0x000F = b 0000 0000 0000 1111 */
    stcHighChCmpMode.OCMRx_f.OCFDCH = TMR4_OCO_OCF_SET; /* bit[0]      1  */
    stcHighChCmpMode.OCMRx_f.OCFPKH = TMR4_OCO_OCF_SET; /* bit[1]      1  */
    stcHighChCmpMode.OCMRx_f.OCFUCH = TMR4_OCO_OCF_SET; /* bit[2]      1  */
    stcHighChCmpMode.OCMRx_f.OCFZRH = TMR4_OCO_OCF_SET; /* bit[3]      1  */
    stcHighChCmpMode.OCMRx_f.OPDCH  = TMR4_OCO_HOLD;    /* Bit[5:4]    00 */
    stcHighChCmpMode.OCMRx_f.OPPKH  = TMR4_OCO_HOLD;    /* Bit[7:6]    00 */
    stcHighChCmpMode.OCMRx_f.OPUCH  = TMR4_OCO_HOLD;    /* Bit[9:8]    00 */
    stcHighChCmpMode.OCMRx_f.OPZRH  = TMR4_OCO_HOLD;    /* Bit[11:10]  00 */
    stcHighChCmpMode.OCMRx_f.OPNPKH = TMR4_OCO_HOLD;    /* Bit[13:12]  00 */
    stcHighChCmpMode.OCMRx_f.OPNZRH = TMR4_OCO_HOLD;    /* Bit[15:14]  00 */
    (void)TMR4_OCO_SetHighChCompareMode(TMR4_UNIT, TMR4_OCO_HIGH_CH, &stcHighChCmpMode);  /* Set OCO high channel compare mode */

    /* TMR4 OCO low channel: compare mode OCMR[31:0] Ox FFFF 0FFF = b 1111 1111 1111 1111   0000 1111 1111 1111 */
    stcLowChCmpMode.OCMRx_f.OCFDCL  = TMR4_OCO_OCF_SET; /* bit[0]      1  */
    stcLowChCmpMode.OCMRx_f.OCFPKL  = TMR4_OCO_OCF_SET; /* bit[1]      1  */
    stcLowChCmpMode.OCMRx_f.OCFUCL  = TMR4_OCO_OCF_SET; /* bit[2]      1  */
    stcLowChCmpMode.OCMRx_f.OCFZRL  = TMR4_OCO_OCF_SET; /* bit[3]      1  */
    stcLowChCmpMode.OCMRx_f.OPDCL   = TMR4_OCO_INVT;    /* bit[5:4]    11 */
    stcLowChCmpMode.OCMRx_f.OPPKL   = TMR4_OCO_INVT;    /* bit[7:6]    11 */
    stcLowChCmpMode.OCMRx_f.OPUCL   = TMR4_OCO_INVT;    /* bit[9:8]    11 */
    stcLowChCmpMode.OCMRx_f.OPZRL   = TMR4_OCO_INVT;    /* bit[11:10]  11 */
    stcLowChCmpMode.OCMRx_f.OPNPKL  = TMR4_OCO_HOLD;    /* bit[13:12]  00 */
    stcLowChCmpMode.OCMRx_f.OPNZRL  = TMR4_OCO_HOLD;    /* bit[15:14]  00 */
    stcLowChCmpMode.OCMRx_f.EOPNDCL = TMR4_OCO_INVT;    /* bit[17:16]  00 */
    stcLowChCmpMode.OCMRx_f.EOPNUCL = TMR4_OCO_INVT;    /* bit[19:18]  00 */
    stcLowChCmpMode.OCMRx_f.EOPDCL  = TMR4_OCO_INVT;    /* bit[21:20]  11 */
    stcLowChCmpMode.OCMRx_f.EOPPKL  = TMR4_OCO_INVT;    /* bit[23:22]  11 */
    stcLowChCmpMode.OCMRx_f.EOPUCL  = TMR4_OCO_INVT;    /* bit[25:24]  11 */
    stcLowChCmpMode.OCMRx_f.EOPZRL  = TMR4_OCO_INVT;    /* bit[27:26]  11 */
    stcLowChCmpMode.OCMRx_f.EOPNPKL = TMR4_OCO_INVT;    /* bit[29:28]  11 */
    stcLowChCmpMode.OCMRx_f.EOPNZRL = TMR4_OCO_INVT;    /* bit[31:30]  11 */
    (void)TMR4_OCO_SetLowChCompareMode(TMR4_UNIT, TMR4_OCO_LOW_CH, &stcLowChCmpMode);  /* Set OCO low channel compare mode */

    /* TMR4 OCO high/low channel: enable interrupt */
    TMR4_OCO_IntCmd(TMR4_UNIT, TMR4_OCO_HIGH_CH, Enable);
    TMR4_OCO_IntCmd(TMR4_UNIT, TMR4_OCO_LOW_CH, Enable);

    /* TMR4 OCO high/low channel: register IRQ handler && configure NVIC. */
    stcIrqConfig.enIRQn = INT000_IRQn;
    stcIrqConfig.enIntSrc = TMR4_OCO_HIGH_CH_INT_SRC;
    stcIrqConfig.pfnCallback = &TMR4_OCO_IrqCallback;
    InstalIrqHandler(&stcIrqConfig, DDL_IRQ_PRI_DEFAULT);

    stcIrqConfig.enIRQn = INT001_IRQn;
    stcIrqConfig.enIntSrc = TMR4_OCO_LOW_CH_INT_SRC;
    stcIrqConfig.pfnCallback = &TMR4_OCO_IrqCallback;
    InstalIrqHandler(&stcIrqConfig, DDL_IRQ_PRI_DEFAULT);

    /* TMR4 OCO: enable */
    TMR4_OCO_Cmd(TMR4_UNIT, TMR4_OCO_HIGH_CH, Enable);
    TMR4_OCO_Cmd(TMR4_UNIT, TMR4_OCO_LOW_CH, Enable);

    /* Start TMR4 counter. */
    TMR4_CNT_Start(TMR4_UNIT);

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
