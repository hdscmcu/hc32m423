/**
 *******************************************************************************
 * @file  hc32m423_pwc.c
 * @brief This file provides firmware functions to manage the Power Contorl(PWC).
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
#include "hc32m423_pwc.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_PWC PWC
 * @brief Power Control Driver Library
 * @{
 */

#if (DDL_PWC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup PWC_Local_Macros PWC Local Macros
 * @{
 */
#define PWC_LVD2_REG_SHIFT          (16UL)
#define PWC_LVD1_REG_MASK           (0x0000FFFFUL)
#define PWC_LVD2_REG_MASK           (0xFFFF0000UL)

#define PWC_RAM_PARITY_FLAG_MASK    (PWC_FLAG_CACHE_PARITY_ERR |               \
                                     PWC_FLAG_HRAM_PARITY_ERR  |               \
                                     PWC_FLAG_RAM_PARITY_ERR)

#define PWC_CLK_LDO_MASK            (PWC_LDO_PLL               |               \
                                     PWC_LDO_HRC)

#define PWC_CLK_LDO_FLAG_SHIFT      (5U)
/* Delay for LDO flag about 1mS */
#define PWC_CLK_LDO_FLAG_TIMEOUT    (SystemCoreClock / 1000UL)

/**
 * @defgroup PWC_Check_Parameters_Validity PWC Check Parameters Validity
 * @{
 */
/*  Check PWC register lock status. */
#define IS_PWC_UNLOCK()             ((CM_PWC->FPRC & PWC_FPRC_PWRWE) == PWC_FPRC_PWRWE)

/*  Check PWC LVD register lock status. */
#define IS_LVD_UNLOCK()             ((CM_PWC->FPRC & PWC_FPRC_LVRWE) == PWC_FPRC_LVRWE)

/*  Parameter validity check for Ram Parity error flag. */
#define IS_PWC_RAM_PARITY_ERR_FLAG(x)                                          \
(   ((x) != 0x00U)                                  &&                         \
    (((x) | PWC_RAM_PARITY_FLAG_MASK) == PWC_RAM_PARITY_FLAG_MASK))

/*  Parameter validity check for stop mode high precision POR. */
#define IS_PWC_STOP_HIGH_PRECISION_POR(x)                                      \
(   ((x) == PWC_HIGH_PRECISION_POR_ENABLE)          ||                         \
    ((x) == PWC_HIGH_PRECISION_POR_DISABLE))

/*  Parameter validity check for system clock after stop mode awake. */
#define IS_PWC_STOP_SYSCLK_AWAKE(x)                                            \
(   ((x) == PWC_SYSCLK_FIX)                         ||                         \
    ((x) == PWC_SYSCLK_MRC))

/*  Parameter validity check for wait flash function after stop mode awake. */
#define IS_PWC_WAIT_FLASH_AWAKE(x)                                             \
(   ((x) == PWC_WAIT_FLASH_ENABLE)                  ||                         \
    ((x) == PWC_WAIT_FLASH_DISABLE))

/*  Parameter validity check for PWC clock LDO select. */
#define IS_PWC_LDO_SEL(x)                                                      \
(   ((x) != 0x00U)                                  &&                         \
    (((x) | PWC_CLK_LDO_MASK) == PWC_CLK_LDO_MASK))

/*  Parameter validity check for monitor power select. */
#define IS_PWC_MON_PWR_SEL(x)                                                  \
(   ((x) == PWC_MON_PWR_IREF)                       ||                         \
    ((x) == PWC_MON_PWR_TSENSOR))

/*  Parameter validity check for PWC LVD unit. */
#define IS_PWC_LVD_UNIT(x)                                                     \
(   ((x) == PWC_LVD0)                               ||                         \
    ((x) == PWC_LVD1)                               ||                         \
    ((x) == PWC_LVD2))

/*  Parameter validity check for PWC LVD normal unit. */
#define IS_PWC_LVD_NORMAL_UNIT(x)                                              \
(   ((x) == PWC_LVD1)                               ||                         \
    ((x) == PWC_LVD2))

/*  Parameter validity check for PWC LVD special unit. */
#define IS_PWC_LVD_SPECIAL_UNIT(x)                                             \
(   ((x) == PWC_LVD0))

/*  Parameter validity check for PWC LVD voltage threshold for LVD1 and LVD2. */
#define IS_PWC_LVD_VOLT_THRESHOLD(x)                                           \
(   ((x) == PWC_LVD_THRESHOLD_LVL0)                 ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL1)                 ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL2)                 ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL3)                 ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL4)                 ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL5)                 ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL6)                 ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL7)                 ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL8)                 ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL9)                 ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL10)                ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL11)                ||                         \
    ((x) == PWC_LVD_THRESHOLD_LVL12)                ||                         \
    ((x) == PWC_LVD_THRESHOLD_EXT_INPUT))

/*  Parameter validity check for PWC LVD digital filter clock. */
#define IS_PWC_LVD_FILTER_CLK(x)                                               \
(   ((x) == PWC_LVD_FILTER_CLK_DIV4)                ||                         \
    ((x) == PWC_LVD_FILTER_CLK_DIV2)                ||                         \
    ((x) == PWC_LVD_FILTER_CLK_DIV1)                ||                         \
    ((x) == PWC_LVD_FILTER_CLK_MUL2))

/*  Parameter validity check for LVD interrupt mode. */
#define IS_PWC_LVD_INT_MD(x)                                                   \
(   ((x) == PWC_LVD_INT_NORMAL)                     ||                         \
    ((x) == PWC_LVD_INT_NMI))

/*  Parameter validity check for LVD detect edge. */
#define IS_PWC_LVD_DETECT_EDGE(x)                                              \
(   ((x) == PWC_LVD_EDGE_FALLING)                   ||                         \
    ((x) == PWC_LVD_EDGE_RISING)                    ||                         \
    ((x) == PWC_LVD_EDGE_BOTH))

/*  Parameter validity check for PWC LVD Comparer Output. */
#define IS_PWC_LVD_CMP_OUTPUT(x)                                               \
(   ((x) == PWC_LVD_CMP_OUTPUT_DISABLE)             ||                         \
    ((x) == PWC_LVD_CMP_OUTPUT_ENABLE))

/*  Parameter validity check for PWC LVD external input. */
#define IS_PWC_LVD2_EXT_INPUT(x)                                               \
(   ((x) == PWC_LVD2_EXT_INPUT_DISABLE)             ||                         \
    ((x) == PWC_LVD2_EXT_INPUT_ENABLE))

/*  Parameter validity check for PWC LVD digital filter. */
#define IS_PWC_LVD_FILTER(x)                                                   \
(   ((x) == PWC_LVD_FILTER_ENABLE)                  ||                         \
    ((x) == PWC_LVD_FILTER_DISABLE))

/*  Parameter validity check for PWC LVD exception type. */
#define IS_PWC_LVD_EXP_TYPE(x)                                              \
(   ((x) == PWC_LVD_EXP_TYPE_INT)                        ||                         \
    ((x) == PWC_LVD_EXP_TYPE_RST))

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

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Functions PWC Global Functions
 * @{
 */

/**
 * @brief  Initialize config structure with default value.
 * @param  [in] pstcStopConfig  The pointer of stop initialize structure.
 *    @arg u8HighPrecisionPOR:  Specifies the high precision POR on or off in stop mode. @ref PWC_HPOR_Config
 *    @arg u8AwakeClock:        Specifies the system clock after stop mode awake. @ref PWC_Sysclk_Awake
 *    @arg u8WaitFlash:         Specifies the wait flash function after stop mode awake. @ref PWC_WaitFlash_Config
 * @retval en_result_t          Enumeration value
 *    @arg Ok:                  Initialize success
 *    @arg ErrorInvalidParameter: Invalid parameter
 */
en_result_t PWC_StopStructInit(stc_pwc_stop_mode_t* pstcStopConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcStopConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcStopConfig->u8HighPrecisionPOR = PWC_HIGH_PRECISION_POR_ENABLE;
        pstcStopConfig->u8AwakeClock = PWC_SYSCLK_FIX;
        pstcStopConfig->u8WaitFlash = PWC_WAIT_FLASH_ENABLE;
    }
    return enRet;
}

/**
 * @brief  Config the stop mode.
 * @param  [in] pstcStopConfig  The pointer of stop config.
 *    @arg u8HighPrecisionPOR:  Specifies the high POR on or off in stop mode. @ref PWC_HPOR_Config
 *    @arg u8AwakeClock:        Specifies the system clock after stop mode awake. @ref PWC_Sysclk_Awake
 *    @arg u8WaitFlash:         Specifies the wait flash function after stop mode awake. @ref PWC_WaitFlash_Config
 * @retval en_result_t          Enumeration value
 *    @arg Ok:                  Initialize success
 *    @arg ErrorInvalidParameter: Invalid parameter
 */
en_result_t PWC_StopConfig(const stc_pwc_stop_mode_t* pstcStopConfig)
{
    en_result_t enRet = Ok;

    if(NULL == pstcStopConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter valid check */
        DDL_ASSERT(IS_PWC_STOP_HIGH_PRECISION_POR(pstcStopConfig->u8HighPrecisionPOR));
        DDL_ASSERT(IS_PWC_STOP_SYSCLK_AWAKE(pstcStopConfig->u8AwakeClock));
        DDL_ASSERT(IS_PWC_WAIT_FLASH_AWAKE(pstcStopConfig->u8WaitFlash));
        DDL_ASSERT(IS_PWC_UNLOCK());

        /* Config the stop mode */
        MODIFY_REG8(CM_PWC->STPMCR,    \
                    (PWC_STPMCR_HAPORDIS | PWC_STPMCR_CKSMRC | PWC_STPMCR_FLNWT), \
                    (pstcStopConfig->u8HighPrecisionPOR | pstcStopConfig->u8AwakeClock | pstcStopConfig->u8WaitFlash));
    }
    return enRet;
}

/**
 * @brief  Enter stop mode.
 * @param  None
 * @retval None
 */
void PWC_EnterStopMode(void)
{
    DDL_ASSERT(IS_PWC_UNLOCK());

    SET_REG8_BIT(CM_PWC->STPMCR, PWC_STPMCR_STOP);

     __WFI();
}

/**
 * @brief  Enter sleep mode.
 * @param  None
 * @retval None
 */
void PWC_EnterSleepMode(void)
{
    DDL_ASSERT(IS_PWC_UNLOCK());

    CLEAR_REG8_BIT(CM_PWC->STPMCR, PWC_STPMCR_STOP);

     __WFI();
}

/**
 * @brief  Power driver config when system switch high speed(>32KHz) to low speed(32KHz).
 * @param  None
 * @retval None
 * @note   The function can reduce power dissipation for system. The function
 *         should be called after system clock changed to low speed.
 */
void PWC_HighSpeedToLowSpeed(void)
{
    DDL_ASSERT(IS_PWC_UNLOCK());

    CLEAR_REG16_BIT(CM_PWC->PWRC, PWC_PWRC_PWDRV | PWC_PWRC_ACTV);

    /* Delay 30uS*/
    DDL_DelayUS(30UL);
}

/**
 * @brief  Power driver config when switch low speed(32KHz) to high speed(>32KHz).
 * @param  None
 * @retval None
 * @note   The function should be called before enter high speed mode.
 */
void PWC_LowSpeedToHighSpeed(void)
{
    DDL_ASSERT(IS_PWC_UNLOCK());

    SET_REG16_BIT(CM_PWC->PWRC, PWC_PWRC_PWDRV | PWC_PWRC_ACTV);

    /* Delay 30uS*/
    DDL_DelayUS(30UL);
}

/**
 * @brief  PWC Clock LDO command.
 * @param  [in] u16ClockLDO     PWC command LDO select @ref PWC_Clock_LDO.
 *         This parameter can be one or any combination of the following values:
 *    @arg PWC_LDO_PLL:         PLL LDO
 *    @arg PWC_LDO_HRC:         HRC LDO
 * @param  [in] enNewState
 *    @arg Enable:              Enable the clock LDO.
 *    @arg Disable:             Disable the clock LDO.
 * @retval None
 */
void PWC_ClockLDOCmd(uint16_t u16ClockLDO, en_functional_state_t enNewState)
{
    uint32_t u32Timeout = 0UL;
    uint16_t u16ReadFlag;
    DDL_ASSERT(IS_PWC_LDO_SEL(u16ClockLDO));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCK());

    if(Enable == enNewState)
    {
        SET_REG16_BIT(CM_PWC->PWRC, u16ClockLDO);
        u16ReadFlag = u16ClockLDO << PWC_CLK_LDO_FLAG_SHIFT;
        /* Wait 30uS after Flag set */
        while( READ_REG16_BIT(CM_PWC->PWRC, u16ReadFlag) != u16ReadFlag)
        {
            /* Wait time out */
            if(u32Timeout++ >= PWC_CLK_LDO_FLAG_TIMEOUT)
            {
                break;
            }
        }
        DDL_DelayUS(30UL);
    }
    else
    {
        CLEAR_REG16_BIT(CM_PWC->PWRC, u16ClockLDO);
    }
}

/**
 * @brief  Get PWC clock LDO status.
 * @param  [in] u16ClockLDO     PWC command LDO select @ref PWC_Clock_LDO.
 *         This parameter can be one or any combination of the following values:
 *    @arg PWC_LDO_PLL:         PLL LDO
 *    @arg PWC_LDO_HRC:         HRC LDO
 * @retval en_flag_status_t     Enumeration value:
 *    @arg Set:                 Flag is set
 *    @arg Reset:               Flag is reset
 */
en_flag_status_t PWC_GetClockLDOStatus(uint16_t u16ClockLDO)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LDO_SEL(u16ClockLDO));

    return ((READ_REG16_BIT(CM_PWC->PWRC, u16ClockLDO))? Set : Reset);
}

/**
 * @brief  Dynamic voltage command.
 * @param  [in] enNewState
 *    @arg Enable:              High driver voltage enable.
 *    @arg Disable:             High driver voltage disable.
 * @retval None
 * @note   The High driver voltage should be enable before system clock switch
 *         to the clock which is quicker than 72MHz.
 */
void PWC_DynamicVoltageCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCK());

    if(Enable == enNewState)
    {
        CLEAR_REG16_BIT(CM_PWC->PWRC, PWC_PWRC_DVS);
    }
    else
    {
        SET_REG16_BIT(CM_PWC->PWRC, PWC_PWRC_DVS);
    }

    /* Delay 30uS*/
    DDL_DelayUS(30UL);
}

/**
 * @brief  PWC power monitor command.
 * @param  [in] enNewState
 *    @arg Enable:              High driver voltage enable.
 *    @arg Disable:             High driver voltage disable.
 * @retval None
 * @note   This monitor power is used for ADC and output to REGC pin.
 */
void PWC_MonitorPowerCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCK());

    if(Enable == enNewState)
    {
        SET_REG8_BIT(CM_PWC->PWRMONR, PWC_PWRMONR_PWMONE);
    }
    else
    {
        CLEAR_REG8_BIT(CM_PWC->PWRMONR, PWC_PWRMONR_PWMONE);
    }
}

/**
 * @brief  PWC power monitor voltage config.
 * @param  [in] u8PowerSelect   PWC power monitor voltage config @ref PWC_Monitor_Power.
 *         This parameter can be one of the following values
 *    @arg PWC_MON_PWR_IREF:    Monitor internal reference voltage of power supply
 *    @arg PWC_MON_PWR_TSENSOR: Monitor temperature sensor voltage
 * @retval None
 * @note   This monitor power is used for ADC and output to REGC pin.
 */
void PWC_MonitorPwrSelect(uint8_t u8PowerSelect)
{
    DDL_ASSERT(IS_PWC_MON_PWR_SEL(u8PowerSelect));
    DDL_ASSERT(IS_PWC_UNLOCK());

    MODIFY_REG8(CM_PWC->PWRMONR, PWC_PWRMONR_PWMONSEL, u8PowerSelect);
}

/**
 * @brief  Get the ram parity error check flag.
 * @param  [in] u8Flag          PWC Ram Parity flag @ref PWC_Ram_Parity_Error_Flag
 *         This parameter can be one or any combination of the configure items,
 *    @arg PWC_FLAG_CACHE_PARITY_ERR: Cache Ram parity error flag
 *    @arg PWC_FLAG_HRAM_PARITY_ERR:  High RAM parity error flag
 *    @arg PWC_FLAG_RAM_PARITY_ERR:   RAM parity error flag
 * @retval en_flag_status_t     Enumeration value
 *    @arg Set:                 Flag is set
 *    @arg Reset:               Flag is reset
 */
en_flag_status_t PWC_RAM_GetStatus(uint8_t u8Flag)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_RAM_PARITY_ERR_FLAG(u8Flag));

    return ((READ_REG8_BIT(CM_PWC->RAMCR, u8Flag)) ? Set : Reset);
}

/**
 * @brief  Clear the ram parity check flag.
 * @param  [in] u8Flag                PWC Ram Parity flag @ref PWC_Ram_Parity_Error_Flag
 *         This parameter can be one or any combination of the configure items,
 *    @arg PWC_FLAG_CACHE_PARITY_ERR: Cache Ram parity error flag
 *    @arg PWC_FLAG_HRAM_PARITY_ERR:  High RAM parity error flag
 *    @arg PWC_FLAG_RAM_PARITY_ERR:   RAM parity error flag
 * @retval None
 */
void PWC_RAM_ClearStatus(uint8_t u8Flag)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_RAM_PARITY_ERR_FLAG(u8Flag));
    DDL_ASSERT(IS_PWC_UNLOCK());

    CLEAR_REG8_BIT(CM_PWC->RAMCR, u8Flag);
}

/**
 * @brief  The Ram Parity error reset function command.
 * @param  [in] enNewState      The new state of the Ram Parity error reset.
 *    @arg Enable:              Function enable.
 *    @arg Disable:             Function disable.
 * @retval None
 */
void PWC_RAM_ResetCmd(en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCK());

    if(Enable == enNewState)
    {
        WRITE_REG32(bCM_PWC->RAMCR_b.RPERDIS, 0UL);
    }
    else
    {
        WRITE_REG32(bCM_PWC->RAMCR_b.RPERDIS, 1UL);
    }
}

/**
 * @brief  Enable or disable the Low Voltage Detector(for LVD1 and LVD2).
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @param  [in] enNewState      The new state of the LVD.
 *    @arg This parameter can be: Enable or Disable.
 * @retval None
 * @note   The function should be call before LVD interrupt and reset cmd.
 */
void PWC_LVD_Cmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_LVD_UNLOCK());

    if (PWC_LVD1 == u32Unit)
    {
        WRITE_REG32(bCM_PWC->LVDCR0_b.L1EN, enNewState);
    }
    else
    {
        WRITE_REG32(bCM_PWC->LVDCR0_b.L2EN, enNewState);
    }
}

/**
 * @brief  Enable or disable the Low Voltage Detector analog compare output.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD0:            PWC LVD unit 0
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @param  [in] enNewState      The new state of the LVD analog output.
 *    @arg This parameter can be: Enable or Disable.
 * @retval None
 * @note   The function should be call before LVD interrupt and reset command.
 */
void PWC_LVD_CompareOutputCmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_LVD_UNLOCK());

    if(PWC_LVD0 == u32Unit)
    {
        WRITE_REG32(bCM_PWC->LVDCSR1_b.L0CMPOE, enNewState);
    }
    else
    {
        if(PWC_LVD1 == u32Unit)
        {
            WRITE_REG32(bCM_PWC->LVDCR0_b.L1CMPOE, enNewState);
        }
        else
        {
            WRITE_REG32(bCM_PWC->LVDCR0_b.L2CMPOE, enNewState);
        }
    }
}

/**
 * @brief  Enable or disable the Low Voltage Detector digital filter function.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @param  [in] enNewState      The new state of the LVD analog output.
 *    @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_LVD_DigitalFilterCmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    uint32_t u32RegWrite;
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_LVD_UNLOCK());

    u32RegWrite = ((Enable == enNewState) ? 0x00UL : 0x01UL);
    if (PWC_LVD1 == u32Unit)
    {
        WRITE_REG32(bCM_PWC->LVDCR0_b.L1NFDIS, u32RegWrite);
    }
    else
    {
        WRITE_REG32(bCM_PWC->LVDCR0_b.L2NFDIS, u32RegWrite);
    }
}

/**
 * @brief  Low Voltage Detector digital filter clock configure.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @param  [in] u32FilterClock  LVD filter clock. @ref PWC_LVD_Filter_Clock_Div
 *    @arg PWC_LVD_FILTER_CLK_DIV4: Filter clock is 0.25 * LRC.
 *    @arg PWC_LVD_FILTER_CLK_DIV2: Filter clock is 0.5 * LRC.
 *    @arg PWC_LVD_FILTER_CLK_DIV1: Filter clock is 1 * LRC.
 *    @arg PWC_LVD_FILTER_CLK_MUL2: Filter clock is 2 * LRC.
 * @retval None
 */
void PWC_LVD_SetFilterClockDiv(uint32_t u32Unit, uint32_t u32FilterClock)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));
    DDL_ASSERT(IS_PWC_LVD_FILTER_CLK(u32FilterClock));
    DDL_ASSERT(IS_LVD_UNLOCK());

    if (PWC_LVD1 == u32Unit)
    {
        MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVDCR0_L1NFS, u32FilterClock);
    }
    else
    {
        MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVDCR0_L2NFS, u32FilterClock << PWC_LVD2_REG_SHIFT);
    }
}

/**
 * @brief  Select LVD exception type
 * @param  [in] u32Unit             PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:                PWC LVD unit 1
 *    @arg PWC_LVD2:                PWC LVD unit 2
 * @param  [in] u32ExceptionType    Interrupt or reset.
 *    @arg PWC_LVD_EXP_TYPE_INT:    Select LVD interrupt.
 *    @arg PWC_LVD_EXP_TYPE_RST:    Select LVD reset.
 * @retval None
 */
void PWC_LVD_SetExceptionType(uint32_t u32Unit, uint32_t u32ExceptionType)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));
    DDL_ASSERT(IS_PWC_LVD_EXP_TYPE(u32ExceptionType));
    DDL_ASSERT(IS_LVD_UNLOCK());

    if (PWC_LVD1 == u32Unit)
    {
        MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVDCR0_L1IRS, u32ExceptionType);
    }
    else
    {
        MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVDCR0_L2IRS, u32ExceptionType << PWC_LVD2_REG_SHIFT);
    }
}

/**
 * @brief  LVD interrupt mode configurate.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @param  [in] u32IntMode      The interrupt mode.
 *    @arg PWC_LVD_INT_NORMAL:  LVD interrupt normal interrupt.
 *    @arg PWC_LVD_INT_NMI:     LVD interrupt NMI interrupt.
 * @retval None
 */
void PWC_LVD_SetIntMode(uint32_t u32Unit, uint32_t u32IntMode)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));
    DDL_ASSERT(IS_PWC_LVD_INT_MD(u32IntMode));
    DDL_ASSERT(IS_LVD_UNLOCK());

    if (PWC_LVD1 == u32Unit)
    {
        MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVDCR0_L1NMIS, u32IntMode);
    }
    else
    {
        MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVDCR0_L2NMIS, u32IntMode << PWC_LVD2_REG_SHIFT);
    }
}

/**
 * @brief  Set LVD threshold voltage.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @param  [in] u32VoltageThreshold     Compare voltage threshold
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD_THRESHOLD_LVL0 :     LVD voltage threshold falling 4.29V and rising 4.39V
 *    @arg PWC_LVD_THRESHOLD_LVL1 :     LVD voltage threshold falling 4.14V and rising 4.23V
 *    @arg PWC_LVD_THRESHOLD_LVL2 :     LVD voltage threshold falling 4.02V and rising 4.14V
 *    @arg PWC_LVD_THRESHOLD_LVL3 :     LVD voltage threshold falling 3.84V and rising 3.96V
 *    @arg PWC_LVD_THRESHOLD_LVL4 :     LVD voltage threshold falling 3.10V and rising 3.20V
 *    @arg PWC_LVD_THRESHOLD_LVL5 :     LVD voltage threshold falling 3.00V and rising 3.09V
 *    @arg PWC_LVD_THRESHOLD_LVL6 :     LVD voltage threshold falling 2.90V and rising 2.99V
 *    @arg PWC_LVD_THRESHOLD_LVL7 :     LVD voltage threshold falling 2.79V and rising 2.87V
 *    @arg PWC_LVD_THRESHOLD_LVL8 :     LVD voltage threshold falling 2.68V and rising 2.75V
 *    @arg PWC_LVD_THRESHOLD_LVL9 :     LVD voltage threshold falling 2.34V and rising 2.41V
 *    @arg PWC_LVD_THRESHOLD_LVL10:     LVD voltage threshold falling 2.14V and rising 2.21V
 *    @arg PWC_LVD_THRESHOLD_LVL11:     LVD voltage threshold falling 1.94V and rising 2.01V
 *    @arg PWC_LVD_THRESHOLD_LVL12:     LVD voltage threshold falling 1.84V and rising 1.90V
 *    @arg PWC_LVD_THRESHOLD_EXT_INPUT: LVD use external input reference voltage
 * @retval en_result_t                  Enumeration value
 *    @arg Ok:                  Config success
 *    @arg ErrorInvalidParameter: Invalid parameter
 * @note   The parameter PWC_LVD_EXT_INPUT only PWC_LVD2 is valid.
 */
en_result_t PWC_LVD_SetVoltageThreshold(uint32_t u32Unit, uint32_t u32VoltageThreshold)
{
    en_result_t enRet = Ok;

    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));
    DDL_ASSERT(IS_PWC_LVD_VOLT_THRESHOLD(u32VoltageThreshold));
    DDL_ASSERT(IS_LVD_UNLOCK());

    if ((PWC_LVD1 == u32Unit) && (PWC_LVD_THRESHOLD_EXT_INPUT == u32VoltageThreshold))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        if (PWC_LVD1 == u32Unit)
        {
            MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVDCR0_L1LVL, u32VoltageThreshold);
        }
        else
        {
            MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVDCR0_L2LVL, u32VoltageThreshold << PWC_LVD2_REG_SHIFT);
        }
    }
    return enRet;
}

/**
 * @brief  Set LVD edge.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @param  [in] u32Edge         Detect edge
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD_EDGE_RISING:  Rising edge valid for LVD
 *    @arg PWC_LVD_EDGE_FALLING: Falling edge valid for LVD
 *    @arg PWC_LVD_EDGE_BOTH:    Both edge valid for LVD
 * @retval None
 */
void PWC_LVD_SetEdge(uint32_t u32Unit, uint32_t u32Edge)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));
    DDL_ASSERT(IS_PWC_LVD_DETECT_EDGE(u32Edge));
    DDL_ASSERT(IS_LVD_UNLOCK());

    if (PWC_LVD1 == u32Unit)
    {
        MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVDCR0_L1IEGS, u32Edge);
    }
    else
    {
        MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVDCR0_L2IEGS, u32Edge << PWC_LVD2_REG_SHIFT);
    }
}

/**
 * @brief  Enable or disable the Low Voltage Detector external input.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @param  [in] enNewState      The new state of the LVD reset function.
 *    @arg Enable:              Enable external input.
 *    @arg Disable:             Disable external input.
 * @retval None
 * @note   Only LVD2 support external input.
 */
void PWC_LVD_ExtInputCmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(PWC_LVD2 == u32Unit);
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_LVD_UNLOCK());

    WRITE_REG32(bCM_PWC->LVDCR0_b.EXVCCINEN, enNewState);
}

/**
 * @brief  Enable or disable the Low Voltage Detector interrupt and reset.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @param  [in] enNewState      The new state of the LVD interrupt and reset function.
 *    @arg Enable:              Enable interrupt and reset.
 *    @arg Disable:             Disable interrupt and reset.
 * @retval None
 * @note   Interrupt and reset function can be commanded after LVD command
 */
void PWC_LVD_IntResetCmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_LVD_UNLOCK());

    if (PWC_LVD1 == u32Unit)
    {
        WRITE_REG32(bCM_PWC->LVDCR0_b.L1IRE, enNewState);
    }
    else
    {
        WRITE_REG32(bCM_PWC->LVDCR0_b.L2IRE, enNewState);
    }
}

/**
 * @brief  De-Initialize PWC LVD function.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @retval None
 */
void PWC_LVD_DeInit(uint32_t u32Unit)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));
    DDL_ASSERT(IS_LVD_UNLOCK());

    if (PWC_LVD1 == u32Unit)
    {
        CLEAR_REG32_BIT(CM_PWC->LVDCR0, PWC_LVD1_REG_MASK);
        WRITE_REG32(bCM_PWC->LVDCSR1_b.L1DETF, 0UL);
    }
    else
    {
        CLEAR_REG32_BIT(CM_PWC->LVDCR0, PWC_LVD2_REG_MASK);
        WRITE_REG32(bCM_PWC->LVDCSR1_b.L2DETF, 0UL);
    }
}

/**
 * @brief  Initialize PWC LVD function.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @param  [in] pstcLvdInit     Pointer to a @ref stc_pwc_lvd_init_t structure.
 * @retval An en_result_t enumeration value
 *    @arg Ok:                  Initialize success
 *    @arg ErrorInvalidParameter: Invalid parameter
 */
en_result_t PWC_LVD_Init(uint32_t u32Unit, const stc_pwc_lvd_init_t* pstcLvdInit)
{
    en_result_t enRet = Ok;

    if (pstcLvdInit == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter valid check */
        DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));
        DDL_ASSERT(IS_PWC_LVD_CMP_OUTPUT(pstcLvdInit->u32CompareOutput));
        DDL_ASSERT(IS_PWC_LVD2_EXT_INPUT(pstcLvdInit->u32ExtInput));
        DDL_ASSERT(IS_PWC_LVD_FILTER(pstcLvdInit->u32FilterEnable));
        DDL_ASSERT(IS_PWC_LVD_FILTER_CLK(pstcLvdInit->u32FilterClock));
        DDL_ASSERT(IS_PWC_LVD_VOLT_THRESHOLD(pstcLvdInit->u32ThresholdVoltage));
        DDL_ASSERT(IS_PWC_LVD_EXP_TYPE(pstcLvdInit->u32ExceptionType));
        DDL_ASSERT(IS_PWC_LVD_INT_MD(pstcLvdInit->u32IntMode));
        DDL_ASSERT(IS_PWC_LVD_DETECT_EDGE(pstcLvdInit->u32LvdDetectEdge));

        if ((PWC_LVD1 == u32Unit) && (PWC_LVD2_EXT_INPUT_ENABLE == pstcLvdInit->u32ExtInput))
        {
            enRet = ErrorInvalidParameter;
        }
        else
        {
            DDL_ASSERT(IS_LVD_UNLOCK());
            if (PWC_LVD1 == u32Unit)
            {
                /* Config */
                MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVD1_REG_MASK,
                            pstcLvdInit->u32FilterEnable |
                            pstcLvdInit->u32FilterClock |
                            pstcLvdInit->u32ThresholdVoltage |
                            pstcLvdInit->u32ExceptionType |
                            pstcLvdInit->u32IntMode |
                            pstcLvdInit->u32LvdDetectEdge);

                /* Enable Analog compare */
                WRITE_REG32(bCM_PWC->LVDCR0_b.L1CMPOE,
                            pstcLvdInit->u32CompareOutput >> PWC_LVDCR0_L1CMPOE_POS);
            }
            else
            {
                /* Config */
                MODIFY_REG32(CM_PWC->LVDCR0, PWC_LVD2_REG_MASK,
                            ((pstcLvdInit->u32FilterEnable |
                            pstcLvdInit->u32FilterClock |
                            pstcLvdInit->u32ThresholdVoltage |
                            pstcLvdInit->u32ExceptionType |
                            pstcLvdInit->u32IntMode |
                            pstcLvdInit->u32LvdDetectEdge) << PWC_LVD2_REG_SHIFT)
                            | pstcLvdInit->u32ExtInput);

                /* Enable Analog compare */
                WRITE_REG32(bCM_PWC->LVDCR0_b.L2CMPOE,
                            pstcLvdInit->u32CompareOutput >> PWC_LVDCR0_L1CMPOE_POS);
            }
        }
    }
    return enRet;
}

/**
 * @brief  Set the fields of structure stc_pwc_lvd_init_t to default values.
 * @param  [out] pstcLvdInit    Pointer to a @ref stc_pwc_lvd_init_t structure.
 * @retval en_result_t          Enumeration value
 *    @arg Ok:                  Initialize success
 *    @arg ErrorInvalidParameter: Invalid parameter
 */
en_result_t PWC_LVD_StructInit(stc_pwc_lvd_init_t* pstcLvdInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcLvdInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcLvdInit->u32CompareOutput = PWC_LVD_CMP_OUTPUT_DISABLE;
        pstcLvdInit->u32ExtInput = PWC_LVD2_EXT_INPUT_DISABLE;
        pstcLvdInit->u32FilterEnable = PWC_LVD_FILTER_DISABLE;
        pstcLvdInit->u32FilterClock = PWC_LVD_FILTER_CLK_DIV4;
        pstcLvdInit->u32ThresholdVoltage = PWC_LVD_THRESHOLD_LVL0;
        pstcLvdInit->u32ExceptionType = PWC_LVD_EXP_TYPE_INT;
        pstcLvdInit->u32IntMode = PWC_LVD_INT_NORMAL;
        pstcLvdInit->u32LvdDetectEdge = PWC_LVD_EDGE_RISING;
    }
    return enRet;
}

/**
 * @brief  Get LVD compare result.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD0:            PWC LVD unit 0
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @retval uint8_t
 *    @arg PWC_LVD_CMP_VCC_LESS_LVD:    VCC < VLVD
 *    @arg PWC_LVD_CMP_VCC_GREATER_LVD: VCC = VLVD or LVD is invalid
 */
uint8_t PWC_LVD_GetCompareResult(uint32_t u32Unit)
{
    uint8_t u8Result = PWC_LVD_CMP_VCC_LESS_LVD;
    uint8_t u8DetectBit;

    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_UNIT(u32Unit));

    if(PWC_LVD0 == u32Unit)
    {
        u8DetectBit = PWC_LVDCSR1_L0MON;
    }
    else
    {
        if(PWC_LVD1 == u32Unit)
        {
            u8DetectBit = PWC_LVDCSR1_L1MON;
        }
        else
        {
            u8DetectBit = PWC_LVDCSR1_L2MON;
        }
    }

    if (0U != (READ_REG8_BIT(CM_PWC->LVDCSR1, u8DetectBit)))
    {
        u8Result = PWC_LVD_CMP_VCC_GREATER_LVD;
    }
    return u8Result;
}

/**
 * @brief  Get LVD detect flag.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @retval An en_flag_status_t  Enumeration value
 *    @arg Set:                 Flag is set
 *    @arg Reset:               Flag is reset
 */
en_flag_status_t PWC_LVD_GetDetectFlag(uint32_t u32Unit)
{
    en_flag_status_t enFlagStat = Reset;
    uint8_t u8DetectBit;

    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));

    if(PWC_LVD1 == u32Unit)
    {
        u8DetectBit = PWC_LVDCSR1_L1DETF;
    }
    else
    {
        u8DetectBit = PWC_LVDCSR1_L2DETF;
    }

    if (0U != (READ_REG8_BIT(CM_PWC->LVDCSR1, u8DetectBit)))
    {
        enFlagStat = Set;
    }

    return enFlagStat;
}

/**
 * @brief  Clear LVD detect flag.
 * @param  [in] u32Unit         PWC LVD unit number
 *         This parameter can be one of the following values:
 *    @arg PWC_LVD1:            PWC LVD unit 1
 *    @arg PWC_LVD2:            PWC LVD unit 2
 * @retval None
 */
void PWC_LVD_ClearDetectFlag(uint32_t u32Unit)
{
    uint8_t u8ClearBit;
    /* Parameter valid check */
    DDL_ASSERT(IS_PWC_LVD_NORMAL_UNIT(u32Unit));
    DDL_ASSERT(IS_LVD_UNLOCK());

    if(PWC_LVD1 == u32Unit)
    {
        u8ClearBit = PWC_LVDCSR1_L1DETF;
    }
    else
    {
        u8ClearBit = PWC_LVDCSR1_L2DETF;
    }

    CLEAR_REG8_BIT(CM_PWC->LVDCSR1, u8ClearBit);
}

/**
 * @brief  Enable or disable the Debug.
 * @param  [in] enNewState      The new state of the Debug.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_DebugCmd(en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCK());

    WRITE_REG32(bCM_PWC->DBGC_b.DBGEN, enNewState);
}

/**
 * @}
 */

#endif  /* DDL_PWC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
