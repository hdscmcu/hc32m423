/**
 *******************************************************************************
 * @file  ctc/ctc_ctcref_trimming/source/main.c
 * @brief This example demonstrates CTC trimming by CTCREF pin clock source.
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
 * @addtogroup CTC_CTCREF_Trimming
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* MCO port/pin */
#define MCO_PORT                        (GPIO_PORT_D)
#define MCO_PIN                         (GPIO_PIN_3)
#define MCO_GPIO_FUNC                   (GPIO_FUNC_1_MCO)

/* CTCREF port/pin */
#define CTCREF_PORT                     (GPIO_PORT_B)
#define CTCREF_PIN                      (GPIO_PIN_3)
#define CTCREF_GPIO_FUNC                (GPIO_FUNC_1_CTCREF)

/* CTC reference clock selection */
#define CTC_REF_CLK_SRC                 (CTC_REF_CLK_CTCREF)

/* CTC reference clock freqency */
#define CTC_REF_CLK_FREQ                (8000000UL)     /* 8MHz */

/* Internal high speed RC freqency */
#define CTC_TRIM_HRC_FREQ               (CTC_TRIM_HRC_16M)

/* CTC TRMVAL value */
#define CTC_TRIM_VALUE                  (0x21UL)        /* -31 */

/* Function clock gate definition  */
#define FUNC_CLK_GATE                   (CLK_FCG_CTC)

/* Function clock gate definition  */
#define FUNC_GENERATE_CTCREF_CLK        (0U)
#define FUNC_TRIM_HRC_CLK               (1U)

#define PROJCET_FUNC                    (FUNC_GENERATE_CTCREF_CLK)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);

static void SystemClockConfig(void);
#if (PROJCET_FUNC == FUNC_TRIM_HRC_CLK)
static void CTC_IrqCallback(void);
#endif

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
 * @brief  Configure system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clock_xtal_init_t stcXTALInit;

    /************************** Configure XTAL clock **************************/
    stcXTALInit.u8XtalState = CLK_XTAL_ON;
    stcXTALInit.u8XtalMode = CLK_XTAL_MD_OSC;
    stcXTALInit.u8XtalDrv = CLK_XTAL_DRV_HIGH;
    stcXTALInit.u8XtalSupSpeedDrv = CLK_XTAL_SUPSPEEDDRV_OFF;
    stcXTALInit.u8XtalStb = CLK_XTALSTB_2POW8;
    (void)CLK_XtalInit(&stcXTALInit);

    /*********************** Switch system clock to XTAL **********************/
    CLK_SetSysclkSrc(CLK_SYSCLK_SRC_XTAL);
}

#if (PROJCET_FUNC == FUNC_TRIM_HRC_CLK)
/**
 * @brief  CTC error IRQ callback.
 * @param  None.
 * @retval None
 */
static void CTC_IrqCallback(void)
{
    BSP_LED_On(LED_RED);
}
#endif

/**
 * @brief  Main function of CTC CTCREF pin clock trimming project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
#if (PROJCET_FUNC == FUNC_TRIM_HRC_CLK)
    uint8_t u8InitTrimValue;
    uint8_t u8TrimmingValue;
    stc_irq_signin_config_t stcIrqConfig;
    stc_ctc_init_t stcCtcInit = {
        .u32HrcFreq = CTC_TRIM_HRC_FREQ,
        .u32RefClockFreq = CTC_REF_CLK_FREQ,
        .u32RefClockSrc = CTC_REF_CLK_SRC,
        .u32RefClockDiv = CTC_REF_CLK_DIV4096,
        .f32ToleranceDeviation = 0.01F,
        .u32TrimValue = CTC_TRIM_VALUE,
    };
#endif

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();

    /* Initialize system clock. */
    SystemClockConfig();

    /* Confiure clock output pin */
    GPIO_SetFunc(MCO_PORT, MCO_PIN, MCO_GPIO_FUNC);

#if (PROJCET_FUNC == FUNC_GENERATE_CTCREF_CLK)
    {
        /* Confiure clock output XTAL clock */
        CLK_MCOConfig(CLK_MCO_SRC_XTAL, CLK_MCO_DIV1);

        /* MCO output enable */
        CLK_MCOCmd(Enable);

        /* MCU Peripheral registers write protected */
        Peripheral_WP();
    }
#else
    {
        /* Confiure clock output HCR clock */
        CLK_MCOConfig(CLK_MCO_SRC_HRC, CLK_MCO_DIV1);

        /* MCO output enable */
        CLK_MCOCmd(Enable);

        /* HRC output */
        (void)CLK_HrcCmd(Enable);

        /* Initialize UART for debug print function. */
        (void)DDL_PrintfInit();

        /* Initialize LED. */
        BSP_LED_Init();

        /* Initialize key. */
        BSP_KEY_Init(BSP_KEY_MD_GPIO);

        /* Confiure CTCREF pin */
        GPIO_SetDebugPort(GPIO_PIN_SWO, Disable);
        GPIO_SetFunc(CTCREF_PORT, CTCREF_PIN, CTCREF_GPIO_FUNC);

        /* Enable peripheral clock */
        CLK_FcgPeriphClockCmd(FUNC_CLK_GATE, Enable);

        /* MCU Peripheral registers write protected */
        Peripheral_WP();

        /* Wait CTC stop. */
        while (Set == CTC_GetStatus(CTC_FLAG_BUSY))
        {
        }

        /* Initialize CTC function. */
        (void)CTC_Init(&stcCtcInit);

        /* Register CTC error IRQ handler && configure NVIC. */
        stcIrqConfig.enIRQn = INT000_IRQn;
        stcIrqConfig.enIntSrc = INT_CTC_ERR;
        stcIrqConfig.pfnCallback = &CTC_IrqCallback;
        (void)INTC_IrqSignIn(&stcIrqConfig);
        NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
        NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRI_DEFAULT);
        NVIC_EnableIRQ(stcIrqConfig.enIRQn);

        CTC_IntCmd(Enable);

        /* User key : SW1 */
        while (Set != BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_GPIO))
        {
        }

        u8InitTrimValue = (uint8_t)CTC_GetTrimValue();

        CTC_Start();

        while (Set != CTC_GetStatus(CTC_FLAG_TRIM_OK))
        {
        }

        u8TrimmingValue = (uint8_t)CTC_GetTrimValue();

        CTC_Stop();

        /* Wait CTC stop. */
        while (Set == CTC_GetStatus(CTC_FLAG_BUSY))
        {
        }

        (void)printf("Init triming value is 0x%02X; Triming result is 0x%02X. \r\n", u8InitTrimValue, u8TrimmingValue);

        BSP_LED_On(LED_GREEN);
    }
#endif

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
