/**
 *******************************************************************************
 * @file  timera/timera_output_compare/source/main.c
 * @brief Main program of Timera Output Compare for the Device Driver Library.
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
 * @addtogroup TMRA_Output_Compare
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* KEY1(SW1) Port/Pin definition */
#define KEY1_EVT_SRC                    (EVT_PORT_EIRQ5)

/* Timera unit definition */
#define TMRA_UNIT4                      (CM_TMRA_4)
#define TMRA_UNIT4_CLK                  (CLK_FCG_TMRA_4)
#define TMRA_UNIT4_CLK_DIV              (256U)
#define TMRA_UNIT4_INT_FREQ             (100U)
/* Period value = 10ms */
#define TMRA_UNIT4_PERIOD_VALUE         ((uint16_t)(HCLK_VALUE/TMRA_UNIT4_CLK_DIV/TMRA_UNIT4_INT_FREQ))

/* Timera channel 1 Port/Pin definition */
#define TMRA_UNIT4_CH1_PORT             (GPIO_PORT_9)
#define TMRA_UNIT4_CH1_PIN              (GPIO_PIN_2)
#define TMRA_UNIT4_CH1_FUNC             (GPIO_FUNC_4_TIMA4_PWM1)

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
 * @brief  Configure Timera function.
 * @param  None
 * @retval None
 */
static void TMRA_Config(void)
{
    stc_tmra_init_t stcTmraInit;
    stc_tmra_pwm_init_t stcPwmInit;

    /* Configure pwm pin of Timera */
    GPIO_SetFunc(TMRA_UNIT4_CH1_PORT, TMRA_UNIT4_CH1_PIN, TMRA_UNIT4_CH1_FUNC);

    /* Configure peripheral clock */
    CLK_FcgPeriphClockCmd((TMRA_UNIT4_CLK | CLK_FCG_AOS), Enable);

    (void)TMRA_StructInit(&stcTmraInit);
    /* Configure structure of timera unit4 */
    stcTmraInit.u16ClockDiv    = TMRA_CLK_DIV256;
    stcTmraInit.u16CountMode   = TMRA_MD_TRIANGLE;
    stcTmraInit.u16PeriodValue = TMRA_UNIT4_PERIOD_VALUE;
    (void)TMRA_Init(TMRA_UNIT4, &stcTmraInit);

    /* Set started/stoped event source */
    TMRA_SetTriggerSrc(TMRA_EVT_USAGE_CNT, KEY1_EVT_SRC);
    TMRA_HWStartCondCmd(TMRA_UNIT4, TMRA_START_COND_EVT, Enable);
    /* Configure compare structure of timera unit4 */
    (void)TMRA_PWM_StructInit(&stcPwmInit);
    stcPwmInit.u16CompareValue   = 0U;
    stcPwmInit.u16StartPolarity  = TMRA_PWM_LOW;
    stcPwmInit.u16StopPolarity   = TMRA_PWM_LOW;
    stcPwmInit.u16MatchPolarity  = TMRA_PWM_LOW;
    stcPwmInit.u16PeriodPolarity = TMRA_PWM_HIGH;
    (void)TMRA_PWM_Init(TMRA_UNIT4, TMRA_CH1, &stcPwmInit);
    TMRA_PWM_Cmd(TMRA_UNIT4, TMRA_CH1, Enable);
    /* Set transfer condition for buffer */
    TMRA_SetCompareBufCond(TMRA_UNIT4, TMRA_BUF_COND_PEAK);
    TMRA_CompareBufCmd(TMRA_UNIT4, Enable);
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
 * @brief  Main function of Timera Output Compare.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint8_t u8TimerState = 0U;
    uint16_t u16PeriodValue;
    uint16_t u16CmpValue = 0U;

    /* Peripheral registers write unprotected */
    Peripheral_WE();
    /* Configure BSP */
    BSP_CLK_Init();
    BSP_LED_Init();
    BSP_KEY_Init(BSP_KEY_MD_EXTINT);
    /* Configure UART */
    (void)DDL_PrintfInit();
    /* Configure Timera */
    TMRA_Config();
    /* Peripheral registers write protected */
    Peripheral_WP();
    /* Get period value of Timera */
    u16PeriodValue = TMRA_GetPeriodValue(TMRA_UNIT4);

    for (;;)
    {
        if (Set == BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_EXTINT))
        {
            if (0U == u8TimerState)
            {
                u8TimerState = 1U;
                BSP_LED_On(LED_RED);
                TMRA_HWStartCondCmd(TMRA_UNIT4, TMRA_START_COND_EVT, Disable);
                TMRA_HWStopCondCmd(TMRA_UNIT4, TMRA_STOP_COND_EVT, Enable);
            }
            else
            {
                u8TimerState = 0U;
                BSP_LED_Off(LED_RED);
                TMRA_HWStopCondCmd(TMRA_UNIT4, TMRA_STOP_COND_EVT, Disable);
                TMRA_HWStartCondCmd(TMRA_UNIT4, TMRA_START_COND_EVT, Enable);
            }            
        }

        if (Set == BSP_KEY_GetStatus(BSP_KEY_2, BSP_KEY_MD_EXTINT))
        {
            u16CmpValue += u16PeriodValue / 20U;
            if (u16CmpValue > u16PeriodValue)
            {
                u16CmpValue = 0U;
            }
            TMRA_SetCompareValue(TMRA_UNIT4, TMRA_CH2, u16CmpValue);
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
