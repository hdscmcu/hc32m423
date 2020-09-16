/**
 *******************************************************************************
 * @file  ev_hc32m423_lqfp64.c
 * @brief This file provides firmware functions for EV_HC32M423_LQFP64 BSP
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
#include "ev_hc32m423_lqfp64.h"

/**
 * @defgroup BSP BSP
 * @{
 */

/**
 * @defgroup EV_HC32M423_LQFP64 HC32M423_LQFP64_EVB
 * @{
 */

#if (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32M423_LQFP64_Local_Macros EV_HC32M423_LQFP64 Local Macros
 * @{
 */

/**
 * @defgroup EV_HC32M423_LQFP64_LED EV_HC32M423_LQFP64 BSP LED
 * @{
 */

/**
 * @defgroup EV_HC32M423_LQFP64_LED_Number EV_HC32M423_LQFP64 LED Number
 * @{
 */
#define BSP_LED_NUM             (3U)
/**
 * @}
 */

/** @defgroup EV_HC32M423_LQFP64_LED_PortPin_Sel EV_HC32M423_LQFP64 LED port/pin definition
 * @{
 */
#define BSP_LED_RED_PORT        (GPIO_PORT_A)
#define BSP_LED_RED_PIN         (GPIO_PIN_4)
#define BSP_LED_GREEN_PORT      (GPIO_PORT_A)
#define BSP_LED_GREEN_PIN       (GPIO_PIN_5)
#define BSP_LED_BLUE_PORT       (GPIO_PORT_1)
#define BSP_LED_BLUE_PIN        (GPIO_PIN_0)
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup EV_HC32M423_LQFP64_KEY EV_HC32M423_LQFP64 KEY
 * @{
 */

/**
 * @defgroup EV_HC32M423_LQFP64_KEY_Number EV_HC32M423_LQFP64 KEY Number
 * @{
 */
#define BSP_KEY_NUM             (4U)
/**
 * @}
 */

/** @defgroup EV_HC32M423_LQFP64_KEY_PortPin_Sel EV_HC32M423_LQFP64 KEY port/pin definition
 * @{
 */
#define BSP_KEY1_PORT           (GPIO_PORT_0)
#define BSP_KEY1_PIN            (GPIO_PIN_2)
#define BSP_KEY2_PORT           (GPIO_PORT_0)
#define BSP_KEY2_PIN            (GPIO_PIN_1)
#define BSP_KEY3_PORT           (GPIO_PORT_E)
#define BSP_KEY3_PIN            (GPIO_PIN_2)
#define BSP_KEY4_PORT           (GPIO_PORT_D)
#define BSP_KEY4_PIN            (GPIO_PIN_7)
/**
 * @}
 */

/** @defgroup EV_HC32M423_LQFP64_KEY_INT_PortPin_Sel EV_HC32M423_LQFP64 KEY interrupt definition
 * @{
 */
/* KEY1 EXTINT5 */
#define BSP_KEY1_INT_CH         (EXTINT_CH05)
#define BSP_KEY1_INT_SRC        (INT_PORT_EIRQ5)
#define BSP_KEY1_INT_IRQn       (EXTINT_PORT_EIRQ5_IRQn)
/* KEY2 EXTINT4 */
#define BSP_KEY2_INT_CH         (EXTINT_CH04)
#define BSP_KEY2_INT_SRC        (INT_PORT_EIRQ4)
#define BSP_KEY2_INT_IRQn       (EXTINT_PORT_EIRQ4_IRQn)
/* KEY4 EXTINT7 */
#define BSP_KEY4_INT_CH         (EXTINT_CH07)
#define BSP_KEY4_INT_SRC        (INT_PORT_EIRQ7)
#define BSP_KEY4_INT_IRQn       (EXTINT_PORT_EIRQ7_IRQn)
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static const uint8_t BSP_LED_PORT[BSP_LED_NUM] =                               \
    {BSP_LED_RED_PORT, BSP_LED_GREEN_PORT, BSP_LED_BLUE_PORT};

static const uint8_t BSP_LED_PIN[BSP_LED_NUM] =                                \
    {BSP_LED_RED_PIN, BSP_LED_GREEN_PIN, BSP_LED_BLUE_PIN};

static const uint8_t BSP_KEY_PORT[BSP_KEY_NUM] =                               \
    {BSP_KEY1_PORT, BSP_KEY2_PORT, BSP_KEY3_PORT, BSP_KEY4_PORT};

static const uint8_t BSP_KEY_PIN[BSP_KEY_NUM] =                                \
    {BSP_KEY1_PIN, BSP_KEY2_PIN, BSP_KEY3_PIN, BSP_KEY4_PIN};

static uint32_t gu32GlobalKey = 0x00UL;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EV_HC32M423_LQFP64_Global_Functions EV_HC32M423_LQFP64 Global Functions
 * @{
 */

/**
 * @brief  LED initialize.
 * @param  None
 * @retval none
 */
void BSP_LED_Init(void)
{
    uint8_t i;
    stc_gpio_init_t stcGpioInit;

    /* Initialize GPIO structure */
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STAT_SET;

    /* Initialize RGB LED pin */
    for (i = 0U; i < BSP_LED_NUM; i++)
    {
        (void)GPIO_Init(BSP_LED_PORT[i], BSP_LED_PIN[i], &stcGpioInit);
    }
}

/**
 * @brief  Turn on LEDs.
 * @param  [in] u8Led LED
 *   @arg  LED_RED
 *   @arg  LED_GREEN
 *   @arg  LED_BLUE
 * @retval none
 */
void BSP_LED_On(uint8_t u8Led)
{
    uint8_t i;

    for (i = 0U; i < BSP_LED_NUM; i++)
    {
        if (0U != ((u8Led >> i) & 1U))
        {
            GPIO_ResetPins(BSP_LED_PORT[i], BSP_LED_PIN[i]);
        }
    }
}

/**
 * @brief  Turn off LEDs.
 * @param  [in] u8Led LED
 *   @arg  LED_RED
 *   @arg  LED_GREEN
 *   @arg  LED_BLUE
 * @retval none
 */
void BSP_LED_Off(uint8_t u8Led)
{
    uint8_t i;

    for (i = 0U; i < BSP_LED_NUM; i++)
    {
        if (0U != ((u8Led >> i) & 1U))
        {
            GPIO_SetPins(BSP_LED_PORT[i], BSP_LED_PIN[i]);
        }
    }
}

/**
 * @brief  Toggle LEDs.
 * @param  [in] u8Led LED
 *   @arg  LED_RED
 *   @arg  LED_GREEN
 *   @arg  LED_BLUE
 * @retval none
 */
void BSP_LED_Toggle(uint8_t u8Led)
{
    uint8_t i;

    for (i = 0U; i < BSP_LED_NUM; i++)
    {
        if (0U != ((u8Led >> i) & 1U))
        {
            GPIO_TogglePins(BSP_LED_PORT[i], BSP_LED_PIN[i]);
        }
    }
}

/**
 * @brief  XTAL initialize.
 * @param  None
 * @retval None
 */
static en_result_t BSP_XtalInit(void)
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
 * @brief  BSP clock initialize.
 *         Set board system clock to PLLH@80MHz
 *         Flash: 3 wait
 *         PCLK1: 80MHz
 *         PCLK4: 80MHz
 *         HCLK:  80MHz
 * @param  None
 * @retval None
 */
void BSP_CLK_Init(void)
{
    stc_clock_pll_init_t stcPLLInit;

    /* HCLK  Max 80MHz */
    /* PCLK1, PCLK4 Max 80MHz */
    CLK_ClockDiv(CLK_CATE_ALL, (CLK_PCLK1_DIV1 | CLK_PCLK4_DIV1 | CLK_HCLK_DIV1));

    (void)BSP_XtalInit();

    (void)CLK_PLLStructInit(&stcPLLInit);
    /* VCO = 8/2*40 = 160MHz*/
    stcPLLInit.u8PLLState = CLK_PLL_ON;
    stcPLLInit.PLLCFGR = 0UL;
    stcPLLInit.PLLCFGR_f.PLLM = 2UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLN = 40UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLP = 2UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_XTAL;
    (void)CLK_PLLInit(&stcPLLInit);

    /* 3-wait @ 80MHz */
    EFM_SetWaitCycle(EFM_WAIT_CYCLE3);
    while(EFM_WAIT_CYCLE3 != READ_REG32_BIT(CM_EFM->FRMC, EFM_FRMC_FLWT))
    {
        ;
    }

    /* Enable High driver volatage */
    PWC_DynamicVoltageCmd(Enable);

    CLK_SetSysclkSrc(CLK_SYSCLK_SRC_PLL);
}

/**
 * @brief  NVIC config
 * @param  [in] IRQn IRQ number
 * @param  [in] priority IRQ priority
 *   @arg  DDL_IRQ_PRI00
 *   @arg  DDL_IRQ_PRI01
 *   @arg  DDL_IRQ_PRI02
 *   @arg  DDL_IRQ_PRI03
 *   @arg  DDL_IRQ_PRI04
 *   @arg  DDL_IRQ_PRI05
 *   @arg  DDL_IRQ_PRI06
 *   @arg  DDL_IRQ_PRI07
 *   @arg  DDL_IRQ_PRI08
 *   @arg  DDL_IRQ_PRI09
 *   @arg  DDL_IRQ_PRI10
 *   @arg  DDL_IRQ_PRI11
 *   @arg  DDL_IRQ_PRI12
 *   @arg  DDL_IRQ_PRI13
 *   @arg  DDL_IRQ_PRI14
 *   @arg  DDL_IRQ_PRI15
 * @retval None
 */
static void NVIC_Config(IRQn_Type IRQn, uint32_t priority)
{
    NVIC_ClearPendingIRQ(IRQn);
    NVIC_SetPriority(IRQn, priority);
    NVIC_EnableIRQ(IRQn);
}
#if (BSP_ON == BSP_INT_KEY_ENABLE)
/**
 * @brief  KEY1 (External interrupt Ch.5) ISR
 * @param  None
 * @retval None
 */
__WEAKDEF void ExtInt05_SWInt13_IrqHandler(void)
{
    gu32GlobalKey |= 0x01UL;
    EXTINT_ClearExtIntStatus(BSP_KEY1_INT_CH);
}

/**
 * @brief  KEY2 (External interrupt Ch.4) ISR
 * @param  None
 * @retval None
 */
__WEAKDEF void ExtInt04_SWInt12_IrqHandler(void)
{
    gu32GlobalKey |= 0x02UL;
    EXTINT_ClearExtIntStatus(BSP_KEY2_INT_CH);
}

/**
 * @brief  KEY4 (External interrupt Ch.7) ISR
 * @param  None
 * @retval None
 */
__WEAKDEF void ExtInt07_SWInt15_IrqHandler(void)
{
    gu32GlobalKey |= 0x08UL;
    EXTINT_ClearExtIntStatus(BSP_KEY4_INT_CH);
}
#endif 
/**
 * @brief  NMI IRQ callback function for KEY3
 * @param  None
 * @retval None
 */
static void BSP_NMI_IrqCallback(void)
{
    if (Set == NMI_GetNmiStatus(INTC_NMIFR_NMIFR))
    {
        gu32GlobalKey |= 0x04UL;
        NMI_ClearNmiStatus(INTC_NMIFR_NMIFR);
    }
}

/**
 * @brief  BSP key initialize
 * @param  [in] u8Mode Key work mode
 *   @arg  BSP_KEY_MD_GPIO
 *   @arg  BSP_KEY_MD_EXTINT
 * @retval None
 */
void BSP_KEY_Init(uint8_t u8Mode)
{
    uint8_t i;
    stc_gpio_init_t stcGpioInit;
    stc_extint_init_t stcExtIntInit;
    stc_nmi_init_t stcNmiInit;

    (void)GPIO_StructInit(&stcGpioInit);
    if (BSP_KEY_MD_GPIO == u8Mode)
    {
        for (i = 0U; i < BSP_KEY_NUM; i++)
        {
            (void)GPIO_Init(BSP_KEY_PORT[i], BSP_KEY_PIN[i], &stcGpioInit);
        }
    }
    else if (BSP_KEY_MD_EXTINT == u8Mode)
    {
        stcGpioInit.u16ExtInt = PIN_EXTINT_ON;
        for (i = 0U; i < BSP_KEY_NUM; i++)
        {
            (void)GPIO_Init(BSP_KEY_PORT[i], BSP_KEY_PIN[i], &stcGpioInit);
        }

        (void)EXTINT_StructInit(&stcExtIntInit);
        stcExtIntInit.u32ExtIntFilterA      = EXTINT_FILTER_A_ON;
        stcExtIntInit.u32ExtIntFilterAClock = EXTINT_FILTER_A_CLK_DIV8;
        stcExtIntInit.u32ExtIntLevel        = EXTINT_TRIG_RISING;

        (void)EXTINT_Init(BSP_KEY1_INT_CH | BSP_KEY2_INT_CH | BSP_KEY4_INT_CH, &stcExtIntInit);

        EXTINT_ClearExtIntStatus(BSP_KEY1_INT_CH | BSP_KEY2_INT_CH | BSP_KEY4_INT_CH);

        NVIC_Config(BSP_KEY1_INT_IRQn, DDL_IRQ_PRI15);
        NVIC_Config(BSP_KEY2_INT_IRQn, DDL_IRQ_PRI15);
        NVIC_Config(BSP_KEY4_INT_IRQn, DDL_IRQ_PRI15);

        /* NMI Pin interrupt configure */
        (void)NMI_StructInit(&stcNmiInit);
        stcNmiInit.u32NmiFilterA        = NMI_FILTER_A_ON;
        stcNmiInit.u32NmiFilterAClockDiv= NMI_FILTER_A_CLK_DIV8;
        stcNmiInit.u32NmiTrigger        = NMI_TRIG_RISING;
        stcNmiInit.u32NmiSrc            = NMI_SRC_NMI_PIN;
        stcNmiInit.pfnNmiCallback       = &BSP_NMI_IrqCallback;
        (void)NMI_Init(&stcNmiInit);
    }
    else
    {
        /* avoid MISRAC 2012-15.7 */
        ;
    }
}

/**
 * @brief  Get BSP key status
 * @param  [in] u32Key chose one macro from below
 *   @arg  BSP_KEY_1
 *   @arg  BSP_KEY_2
 *   @arg  BSP_KEY_3
 *   @arg  BSP_KEY_4
 * @param  [in] u8Mode Key work mode
 *   @arg  BSP_KEY_MD_GPIO
 *   @arg  BSP_KEY_MD_EXTINT
 * @retval en_flag_status_t
 *   @arg  Set, Key pressed.
 *   @arg  Reset, Key released.
 */
en_flag_status_t BSP_KEY_GetStatus(uint32_t u32Key, uint8_t u8Mode)
{
    en_flag_status_t enRet = Reset;

    if (BSP_KEY_MD_GPIO == u8Mode)
    {
        enRet = (Pin_Set == GPIO_ReadInputPins(BSP_KEY_PORT[u32Key], BSP_KEY_PIN[u32Key])) ? Reset : Set;
    }
    else if (BSP_KEY_MD_EXTINT == u8Mode)
    {
        if (0UL != (gu32GlobalKey & (1UL << u32Key)))
        {
            enRet = Set;
            gu32GlobalKey &= ~(1UL << u32Key);
        }
    }
    else
    {

    }
    return enRet;
}

/**
 * @}
 */

#endif /* BSP_EV_HC32M423_LQFP64 */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
