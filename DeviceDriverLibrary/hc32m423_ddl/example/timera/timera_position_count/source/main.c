/**
 *******************************************************************************
 * @file  timera/timera_position_count/source/main.c
 * @brief Main program of Timera Position Count for the Device Driver Library.
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
 * @addtogroup TMRA_Position_Count
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Timera unit3 definition */
#define TMRA_UNIT3                      (CM_TMRA_3)
#define TMRA_UNIT3_CLK                  (CLK_FCG_TMRA_3)
#define TMRA_UNIT3_PERIOD_VALUE         (1000U)

/* Timera unit3 CLKA Port/Pin definition */
#define TMRA_UNIT3_CLKA_PORT            (GPIO_PORT_7)
#define TMRA_UNIT3_CLKA_PIN             (GPIO_PIN_4)
#define TMRA_UNIT3_CLKA_FUNC            (GPIO_FUNC_4_TIMA3_CLKA)

/* Timera unit3 CLKB Port/Pin definition */
#define TMRA_UNIT3_CLKB_PORT            (GPIO_PORT_7)
#define TMRA_UNIT3_CLKB_PIN             (GPIO_PIN_3)
#define TMRA_UNIT3_CLKB_FUNC            (GPIO_FUNC_4_TIMA3_CLKB)

/* Timera unit1 definition */
#define TMRA_UNIT1                      (CM_TMRA_1)
#define TMRA_UNIT1_CLK                  (CLK_FCG_TMRA_1)
#define TMRA_UNIT1_CLK_DIV              (128U)
#define TMRA_UNIT1_INT_FREQ             (1000U)
/* Period value = 10ms */
#define TMRA_UNIT1_PERIOD_VALUE         ((uint16_t)(HCLK_VALUE/TMRA_UNIT1_CLK_DIV/TMRA_UNIT1_INT_FREQ) - 1U)

#define TMRA_UNIT1_CH1_PORT             (GPIO_PORT_9)
#define TMRA_UNIT1_CH1_PIN              (GPIO_PIN_4)
#define TMRA_UNIT1_CH1_FUNC             (GPIO_FUNC_7_TIMA1_PWM1)

/* Timera unit2 definition */
#define TMRA_UNIT2                      (CM_TMRA_2)
#define TMRA_UNIT2_CLK                  (CLK_FCG_TMRA_2)
#define TMRA_UNIT2_CLK_DIV              (128U)
#define TMRA_UNIT2_INT_FREQ             (1000U)
/* Period value = 10ms */
#define TMRA_UNIT2_PERIOD_VALUE         ((uint16_t)(HCLK_VALUE/TMRA_UNIT2_CLK_DIV/TMRA_UNIT2_INT_FREQ) - 1U)

#define TMRA_UNIT2_CH1_PORT             (GPIO_PORT_1)
#define TMRA_UNIT2_CH1_PIN              (GPIO_PIN_1)
#define TMRA_UNIT2_CH1_FUNC             (GPIO_FUNC_7_TIMA2_PWM1)

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
 * @brief  Overflow interrupt callback for Timera unit3.
 * @param  None
 * @retval None
 */
void TMRA_3_Ovf_IrqHandler(void)
{
    BSP_LED_Toggle(LED_GREEN);
    TMRA_ClearStatus(TMRA_UNIT3, TMRA_FLAG_OVF);
}

/**
 * @brief  Underflow interrupt callback for Timera unit3.
 * @param  None
 * @retval None
 */
void TMRA_3_Udf_IrqHandler(void)
{
    BSP_LED_Toggle(LED_RED);
    TMRA_ClearStatus(TMRA_UNIT3, TMRA_FLAG_UDF);
}

/**
 * @brief  Configure the encoder of Timera.
 * @param  None
 * @retval None
 */
static void TMRA_EncoderConfig(void)
{
    stc_tmra_init_t stcTmraInit;

    /* Configure encoder pin of Timera */
    GPIO_SetFunc(TMRA_UNIT3_CLKA_PORT, TMRA_UNIT3_CLKA_PIN, TMRA_UNIT3_CLKA_FUNC);
    GPIO_SetFunc(TMRA_UNIT3_CLKB_PORT, TMRA_UNIT3_CLKB_PIN, TMRA_UNIT3_CLKB_FUNC);

    /* Configure peripheral clock */
    CLK_FcgPeriphClockCmd(TMRA_UNIT3_CLK, Enable);

    (void)TMRA_StructInit(&stcTmraInit);
    /* Configure structure of timera unit3 */
    stcTmraInit.u16PeriodValue = TMRA_UNIT3_PERIOD_VALUE;
    (void)TMRA_Init(TMRA_UNIT3, &stcTmraInit);
    TMRA_IntCmd(TMRA_UNIT3, (TMRA_INT_OVF | TMRA_INT_UDF), Enable);

    /* Configure encoder function */
    TMRA_HWCountUpCondCmd(TMRA_UNIT3, TMRA_CNT_UP_COND_CLKBH_CLKAR, Enable);
    TMRA_HWCountDownCondCmd(TMRA_UNIT3, TMRA_CNT_DOWN_COND_CLKBL_CLKAR, Enable);
    /* Configure the input filter of CLKA and CLKB */
    TMRA_SetFilterClockDiv(TMRA_UNIT3, TMRA_PIN_CLKA, TMRA_FILTER_CLK_DIV4);
    TMRA_FilterCmd(TMRA_UNIT3, TMRA_PIN_CLKA, Enable);
    TMRA_SetFilterClockDiv(TMRA_UNIT3, TMRA_PIN_CLKB, TMRA_FILTER_CLK_DIV4);
    TMRA_FilterCmd(TMRA_UNIT3, TMRA_PIN_CLKB, Enable);

    /* Configure overflow interrupt of timera unit3 */
    NVIC_ClearPendingIRQ(TMRA_3_OVF_IRQn);
    NVIC_SetPriority(TMRA_3_OVF_IRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(TMRA_3_OVF_IRQn);
    /* Configure underflow interrupt of timera unit3 */
    NVIC_ClearPendingIRQ(TMRA_3_UDF_IRQn);
    NVIC_SetPriority(TMRA_3_UDF_IRQn, DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(TMRA_3_UDF_IRQn);

    /* Start unit3 of timera */
    TMRA_Start(TMRA_UNIT3);
}

/**
 * @brief  Configure the pwm output of Timera.
 * @param  None
 * @retval None
 */
static void TMRA_PwmConfig(void)
{
    stc_tmra_init_t stcTmraInit;
    stc_tmra_pwm_init_t stcPwmInit;

    /* Configure pwm pin of Timera */
    GPIO_SetFunc(TMRA_UNIT1_CH1_PORT, TMRA_UNIT1_CH1_PIN, TMRA_UNIT1_CH1_FUNC);
    GPIO_SetFunc(TMRA_UNIT2_CH1_PORT, TMRA_UNIT2_CH1_PIN, TMRA_UNIT2_CH1_FUNC);

    /* Configure peripheral clock */
    CLK_FcgPeriphClockCmd((TMRA_UNIT1_CLK | TMRA_UNIT2_CLK), Enable);

    (void)TMRA_StructInit(&stcTmraInit);
    /* Configure structure of timera unit1 */
    stcTmraInit.u16ClockDiv    = TMRA_CLK_DIV128;
    stcTmraInit.u16CountMode   = TMRA_MD_SAWTOOTH;
    stcTmraInit.u16CountDir    = TMRA_DIR_UP;
    stcTmraInit.u16PeriodValue = TMRA_UNIT1_PERIOD_VALUE;
    (void)TMRA_Init(TMRA_UNIT1, &stcTmraInit);
    /* Configure structure of timera unit2 */
    stcTmraInit.u16PeriodValue = TMRA_UNIT2_PERIOD_VALUE;
    (void)TMRA_Init(TMRA_UNIT2, &stcTmraInit);

    /* Configure compare structure of timera unit1 */
    (void)TMRA_PWM_StructInit(&stcPwmInit);
    stcPwmInit.u16CompareValue   = TMRA_UNIT1_PERIOD_VALUE / 4U;
    stcPwmInit.u16StartPolarity  = TMRA_PWM_LOW;
    stcPwmInit.u16StopPolarity   = TMRA_PWM_LOW;
    stcPwmInit.u16MatchPolarity  = TMRA_PWM_HIGH;
    stcPwmInit.u16PeriodPolarity = TMRA_PWM_LOW;
    (void)TMRA_PWM_Init(TMRA_UNIT1, TMRA_CH1, &stcPwmInit);
    TMRA_PWM_Cmd(TMRA_UNIT1, TMRA_CH1, Enable);
    /* Configure compare structure of timera unit2 */
    stcPwmInit.u16CompareValue   = TMRA_UNIT2_PERIOD_VALUE / 2U;
    (void)TMRA_PWM_Init(TMRA_UNIT2, TMRA_CH1, &stcPwmInit);
    TMRA_PWM_Cmd(TMRA_UNIT2, TMRA_CH1, Enable);

    /* Enable the sync start function of timera unit2 */
    TMRA_SyncStartCmd(TMRA_UNIT2, Enable);
    /* Start unit1 of timera and sync start unit2 of timera */
    TMRA_Start(TMRA_UNIT1);
}

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
//    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Main function of Timera Position Count.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint8_t u8OutputPhase = 0U;

    /* Peripheral registers write unprotected */
    Peripheral_WE();
    /* Configure BSP */
    BSP_CLK_Init();
    BSP_LED_Init();
    BSP_KEY_Init(BSP_KEY_MD_EXTINT);
    /* Configure UART */
    (void)DDL_PrintfInit();
    /* Configure Timera */
    TMRA_EncoderConfig();
    TMRA_PwmConfig();
    /* Peripheral registers write protected */
    Peripheral_WP();

    for (;;)
    {
        if (Set == BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_EXTINT))
        {
            if (0U == u8OutputPhase)
            {
                u8OutputPhase = 1U;
                TMRA_SetCompareValue(TMRA_UNIT1, TMRA_CH1, (TMRA_UNIT1_PERIOD_VALUE / 2U));
                TMRA_SetCompareValue(TMRA_UNIT2, TMRA_CH1, (TMRA_UNIT2_PERIOD_VALUE / 4U));
            }
            else
            {
                u8OutputPhase = 0U;
                TMRA_SetCompareValue(TMRA_UNIT1, TMRA_CH1, (TMRA_UNIT1_PERIOD_VALUE / 4U));
                TMRA_SetCompareValue(TMRA_UNIT2, TMRA_CH1, (TMRA_UNIT2_PERIOD_VALUE / 2U));
            }
            BSP_LED_Off(LED_RED);
            BSP_LED_Off(LED_GREEN);
        }
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
