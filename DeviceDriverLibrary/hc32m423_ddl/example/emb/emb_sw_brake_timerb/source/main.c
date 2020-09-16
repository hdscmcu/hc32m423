/**
 *******************************************************************************
 * @file  emb/emb_sw_brake_timerb/source/main.c
 * @brief This example demonstrates how to use the software brake function of
 *        EMB function.
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
 * @addtogroup EMB_Software_Brake_TMRB
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
#define FUNC_CLK_GATE                   (CLK_FCG_EMB | CLK_FCG_TMRB)

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
 * @brief  Main function of EMB software brake TMRB
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
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

    /* MCU Peripheral registers write protected */
    Peripheral_WP();

    /* Configure TMRB PWM. */
    TmrbPwmConfig();

    /* Set TMRB PWM polarity when EMB occur */
    EMB_SetTmrbPwmPolarity(EMB_UNIT, EMB_TMRB_PWM_LOW);

    for (;;)
    {
        while (Set != KeyState())
        {
        }

        /* Software start brake signal */
        EMB_SWBrake(EMB_UNIT, Enable);

        while (Set != KeyState())
        {
        }

        /* Software stop brake signal */
        EMB_SWBrake(EMB_UNIT, Disable);
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
