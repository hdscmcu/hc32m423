/**
 *******************************************************************************
 * @file  hc32m423_pwc.h
 * @brief This file contains all the functions prototypes of the PWC driver
 *        library.
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
#ifndef __HC32M423_PWC_H__
#define __HC32M423_PWC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_PWC
 * @{
 */

#if (DDL_PWC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Types PWC Global Types
 * @{
 */

/**
 * @brief PWC stop mode config
 */
typedef struct
{
    uint8_t u8HighPrecisionPOR;         /*!< Specifies the high POR(power on reset) on or
                                        off while stop mode. @ref PWC_HPOR_Config */
    uint8_t u8AwakeClock;               /*!< Specifies the system clock after stop mode
                                        awake. @ref PWC_Sysclk_Awake */
    uint8_t u8WaitFlash;                /*!< Specifies the wait flash stable function after
                                        stop mode awake. @ref PWC_WaitFlash_Config */
} stc_pwc_stop_mode_t;
//todo u32FilterEnable u32Filter
/**
 * @brief PWC LVD initialization structure definition
 */
typedef struct
{
    uint32_t u32CompareOutput;          /*!< Specifies the validity of the PWC LVD comparer output.
                                             This parameter can be a value of @ref PWC_LVD_Compare_Output */
    uint32_t u32ExtInput;               /*!< Specifies the validity of the PWC LVD external input (Only for LVD2).
                                             This parameter can be @ref PWC_LVD2_Ext_In */
    uint32_t u32FilterEnable;           /*!< Specifies the validity of the PWC LVD filter function.
                                             This parameter can be @ref PWC_LVD_Filter */
    uint32_t u32FilterClock;            /*!< Specifies the PWC LVD filter clock.
                                             This parameter can be a value of @ref PWC_LVD_Filter_Clock_Div */
    uint32_t u32ThresholdVoltage;       /*!< Specifies the PWC LVD detect threshole voltage.
                                             This parameter can be a value of @ref PWC_LVD_Voltage_Threshold */
    uint32_t u32ExceptionType;         /*!< Specifies Lvd trigger interrupt or reset when voltage meet the condition
                                             This parameter can be a value of @ref PWC_LVD_Exception_Type */
    uint32_t u32IntMode;                /*!< Specifies Lvd interrupt mode
                                             This parameter can be a value of @ref PWC_LVD_Interrupt_Mode */
    uint32_t u32LvdDetectEdge;          /*!< Specifies the PWC LVD detect edge.
                                             This parameter can be a value of @ref PWC_LVD_Detect_Edge */
} stc_pwc_lvd_init_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Macros PWC Global Macros
 * @{
 */

/**
 * @defgroup PWC_Ram_Parity_Error_Flag PWC Ram Parity Error Flag
 * @{
 */
#define PWC_FLAG_CACHE_PARITY_ERR   (PWC_RAMCR_CRPEF)       /*!< Cache Ram parity error flag */
#define PWC_FLAG_HRAM_PARITY_ERR    (PWC_RAMCR_HRPEF)       /*!< High RAM parity error flag  */
#define PWC_FLAG_RAM_PARITY_ERR     (PWC_RAMCR_SRPEF)       /*!< RAM parity error flag       */
/**
 * @}
 */

/**
 * @defgroup PWC_HPOR_Config PWC High Precision POR config in stop mode
 * @{
 */
#define PWC_HIGH_PRECISION_POR_ENABLE   (0x00U)                 /*!< High Precision POR is valid while in stop mode   */
#define PWC_HIGH_PRECISION_POR_DISABLE  (PWC_STPMCR_HAPORDIS)   /*!< High Precision POR is invalid while in stop mode */
/**
 * @}
 */

/**
 * @defgroup PWC_Sysclk_Awake PWC system clock after stop mode awake
 * @{
 */
#define PWC_SYSCLK_FIX              (0x00U)                 /*!< System clock is fixed after stop mode awake */
#define PWC_SYSCLK_MRC              (PWC_STPMCR_CKSMRC)     /*!< System clock is MRC after stop mode awake */
/**
 * @}
 */

/**
 * @defgroup PWC_WaitFlash_Config PWC wait flash stable function after stop mode awake
 * @{
 */
#define PWC_WAIT_FLASH_ENABLE       (0x00U)                 /*!< Wait flash stable after stop mode awake */
#define PWC_WAIT_FLASH_DISABLE      (PWC_STPMCR_FLNWT)      /*!< Do not wait flash stable after stop mode awake */
/**
 * @}
 */

/**
 * @defgroup PWC_Clock_LDO PWC PLL and HRC LDO definition
 * @{
 */
#define PWC_LDO_PLL                 (PWC_PWRC_VPLLE)        /*!< Power LDO for PLL */
#define PWC_LDO_HRC                 (PWC_PWRC_VHRCE)        /*!< Power LDO for HRC */
/**
 * @}
 */

/**
 * @defgroup PWC_Monitor_Power PWC Power Monitor voltage definition
 * @{
 */
#define PWC_MON_PWR_IREF            (0x00U)                 /*!< Monitor internal reference voltage of power supply */
#define PWC_MON_PWR_TSENSOR         (PWC_PWRMONR_PWMONSEL)  /*!< Monitor temperature sensor voltage */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Unit PWC LVD Unit definition
 * @{
 */
#define PWC_LVD0                    (0x00U)                 /*!< LVD0 */
#define PWC_LVD1                    (0x01U)                 /*!< LVD1 */
#define PWC_LVD2                    (0x02U)                 /*!< LVD2 */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Voltage_Threshold PWC LVD Voltage Threshold definition
 * @note The parameter PWC_LVD_EXT_INPUT only LVD2 is valid
 * @{
 */
#define PWC_LVD_THRESHOLD_LVL0      (0x00UL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 4.29V and rising 4.39V */
#define PWC_LVD_THRESHOLD_LVL1      (0x01UL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 4.14V and rising 4.23V */
#define PWC_LVD_THRESHOLD_LVL2      (0x02UL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 4.02V and rising 4.14V */
#define PWC_LVD_THRESHOLD_LVL3      (0x03UL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 3.84V and rising 3.96V */
#define PWC_LVD_THRESHOLD_LVL4      (0x04UL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 3.10V and rising 3.20V */
#define PWC_LVD_THRESHOLD_LVL5      (0x05UL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 3.00V and rising 3.09V */
#define PWC_LVD_THRESHOLD_LVL6      (0x06UL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 2.90V and rising 2.99V */
#define PWC_LVD_THRESHOLD_LVL7      (0x07UL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 2.79V and rising 2.87V */
#define PWC_LVD_THRESHOLD_LVL8      (0x08UL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 2.68V and rising 2.75V */
#define PWC_LVD_THRESHOLD_LVL9      (0x09UL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 2.34V and rising 2.41V */
#define PWC_LVD_THRESHOLD_LVL10     (0x0AUL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 2.14V and rising 2.21V */
#define PWC_LVD_THRESHOLD_LVL11     (0x0BUL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 1.94V and rising 2.01V */
#define PWC_LVD_THRESHOLD_LVL12     (0x0CUL << PWC_LVDCR0_L1LVL_POS) /*!< LVD voltage threshold falling 1.84V and rising 1.90V */
#define PWC_LVD_THRESHOLD_EXT_INPUT (0x0EUL << PWC_LVDCR0_L1LVL_POS) /*!< LVD use external input reference voltage */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Filter_Clock_Div PWC LVD Filter clock divider
 * @{
 */
#define PWC_LVD_FILTER_CLK_DIV4     (0x00000000UL)          /*!< 0.25 * LRC */
#define PWC_LVD_FILTER_CLK_DIV2     (PWC_LVDCR0_L1NFS_0)    /*!< 0.5 * LRC  */
#define PWC_LVD_FILTER_CLK_DIV1     (PWC_LVDCR0_L1NFS_1)    /*!< 1 * LRC */
#define PWC_LVD_FILTER_CLK_MUL2     (PWC_LVDCR0_L1NFS)      /*!< 2 * LRC */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Interrupt_Mode PWC LVD Interrupt mode
 * @{
 */
#define PWC_LVD_INT_NORMAL          (0UL)                   /*!< LVD normal interrupt */
#define PWC_LVD_INT_NMI             (PWC_LVDCR0_L1NMIS)      /*!< LVD NMI interrupt */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Detect_Edge PWC LVD detect edge
 * @{
 */
#define PWC_LVD_EDGE_RISING         (0UL)                   /*!< Rising edge */
#define PWC_LVD_EDGE_FALLING        (PWC_LVDCR0_L1IEGS_0)   /*!< Falling edge */
#define PWC_LVD_EDGE_BOTH           (PWC_LVDCR0_L1IEGS_1)   /*!< Both edge */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_Ext_In PWC LVD2 external input
 * @{
 */
#define PWC_LVD2_EXT_INPUT_DISABLE  (0x00U)                 /*!< LVD2 external input invalid */
#define PWC_LVD2_EXT_INPUT_ENABLE   (PWC_LVDCR0_EXVCCINEN)  /*!< LVD2 external input valid */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Filter LVD digital filter
 * @{
 */
#define PWC_LVD_FILTER_ENABLE       (0x00U)                 /*!< LVD digital filter on */
#define PWC_LVD_FILTER_DISABLE      (PWC_LVDCR0_L1NFDIS)    /*!< LVD digital filter off */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Exception_Type LVD exception type
 * @{
 */
#define PWC_LVD_EXP_TYPE_INT        (0x00U)                 /*!< LVD select interrupt */
#define PWC_LVD_EXP_TYPE_RST        (PWC_LVDCR0_L1IRS)      /*!< LVD select reset */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Compare_Output PWC LVD Compare Output
 * @{
 */
#define PWC_LVD_CMP_OUTPUT_DISABLE  (0x00000000UL)          /*!< LVD compare output disable */
#define PWC_LVD_CMP_OUTPUT_ENABLE   (PWC_LVDCR0_L1CMPOE)    /*!< LVD compare output enable */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Compare_Result PWC LVD Compare Result
 * @{
 */
#define PWC_LVD_CMP_VCC_LESS_LVD    (0x00U)                 /*!< VCC < VLVD */
#define PWC_LVD_CMP_VCC_GREATER_LVD (PWC_LVDCSR1_L1MON)     /*!< VCC = VLVD or LVD is invalid */
/**
 * @}
 */

/**
 * @defgroup PWC_REG_Write_Unlock_Code PWC register unlock code.
 * @brief Lock/unlock Code for each module
 *        PWC_UNLOCK_CODE_0:
 *          Below registers are locked in CLK module.
 *              ADCKSEL, XTALSTDSR, SCFGR, CKSWR, XTALCR, XTALCFGR, XTALSTBCR,
 *              HRCCR, OSCSTBSR, MCOCFGR, XTALSTDCR, FCG, LRCCR, TPIUCKCFGR,
 *              MRCCR, PLLCFGR, PLLCR
 *        PWC_UNLOCK_CODE_1:
 *          Below registers are locked in PWC module.
 *              STPMCR, PWRC, RAMCR, DBGC,
 *          Below register is locked in RMU module.
 *              RSTF0
 *        PWC_UNLOCK_CODE_2:
 *          Below registers are locked in PWC module.
 *              LVDCSR1, LVDCSR0
 * @{
 */
#define PWC_UNLOCK_CODE_0           (0xA501U)
#define PWC_UNLOCK_CODE_1           (0xA502U)
#define PWC_UNLOCK_CODE_2           (0xA508U)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup PWC_Global_Functions
 * @{
 */

/**
 * @brief  Lock PWC, CLK, RMU register.
 * @param  [in] u16Module Lock code for each module.
 *   @arg  PWC_UNLOCK_CODE_0:
 *          Below registers are locked in CLK module.
 *              ADCKSEL, XTALSTDSR, SCFGR, CKSWR, XTALCR, XTALCFGR, XTALSTBCR,
 *              HRCCR, OSCSTBSR, MCOCFGR, XTALSTDCR, FCG, LRCCR, TPIUCKCFGR,
 *              MRCCR, PLLCFGR, PLLCR
 *   @arg  PWC_UNLOCK_CODE_1:
 *          Below registers are locked in PWC module.
 *              STPMCR, PWC_PWRC, RAMCR, DBGC,
 *          Below register is locked in RMU module.
 *              RSTF0
 *   @arg  PWC_UNLOCK_CODE_2:
 *          Below registers are locked in PWC module.
 *              LVDCSR1, LVDCSR0
 * @retval None
 */
__STATIC_INLINE void PWC_Lock(uint16_t u16Module)
{
    WRITE_REG16(CM_PWC->FPRC, (0xA500U | (uint16_t)((uint16_t)(~u16Module) & (CM_PWC->FPRC))));
}

/**
 * @brief  Unlock PWC, CLK, RMU register.
 * @param  [in] u16Module Unlock code for each module.
 *   @arg  PWC_UNLOCK_CODE_0:
 *          Below registers are unlocked in CLK module.
 *              ADCKSEL, XTALSTDSR, SCFGR, CKSWR, XTALCR, XTALCFGR, XTALSTBCR,
 *              HRCCR, OSCSTBSR, MCOCFGR, XTALSTDCR, FCG, LRCCR, TPIUCKCFGR,
 *              MRCCR, PLLCFGR, PLLCR
 *   @arg  PWC_UNLOCK_CODE_1:
 *          Below registers are unlocked in PWC module.
 *              STPMCR, PWC_PWRC, RAMCR, DBGC,
 *          Below register is unlocked in RMU module.
 *              RSTF0
 *   @arg  PWC_UNLOCK_CODE_2:
 *          Below registers are unlocked in PWC module.
 *              LVDCSR1, LVDCSR0
 * @retval None
 */
__STATIC_INLINE void PWC_Unlock(uint16_t u16Module)
{
    SET_REG16_BIT(CM_PWC->FPRC, u16Module);
}

void PWC_Lock(uint16_t u16Module);
void PWC_Unlock(uint16_t u16Module);

en_result_t PWC_StopStructInit(stc_pwc_stop_mode_t* pstcStopConfig);
en_result_t PWC_StopConfig(const stc_pwc_stop_mode_t* pstcStopConfig);

void PWC_EnterStopMode(void);
void PWC_EnterSleepMode(void);

void PWC_HighSpeedToLowSpeed(void);
void PWC_LowSpeedToHighSpeed(void);

void PWC_ClockLDOCmd(uint16_t u16ClockLDO, en_functional_state_t enNewState);
en_flag_status_t PWC_GetClockLDOStatus(uint16_t u16ClockLDO);
void PWC_DynamicVoltageCmd(en_functional_state_t enNewState);

void PWC_MonitorPowerCmd(en_functional_state_t enNewState);
void PWC_MonitorPwrSelect(uint8_t u8PowerSelect);

en_flag_status_t PWC_RAM_GetStatus(uint8_t u8Flag);
void PWC_RAM_ClearStatus(uint8_t u8Flag);
void PWC_RAM_ResetCmd(en_functional_state_t enNewState);

void PWC_LVD_Cmd(uint32_t u32Unit, en_functional_state_t enNewState);
void PWC_LVD_CompareOutputCmd(uint32_t u32Unit, en_functional_state_t enNewState);
void PWC_LVD_DigitalFilterCmd(uint32_t u32Unit, en_functional_state_t enNewState);
void PWC_LVD_SetFilterClockDiv(uint32_t u32Unit, uint32_t u32FilterClock);
void PWC_LVD_SetExceptionType(uint32_t u32Unit, uint32_t u32ExceptionType);
void PWC_LVD_SetIntMode(uint32_t u32Unit, uint32_t u32IntMode);
en_result_t PWC_LVD_SetVoltageThreshold(uint32_t u32Unit, uint32_t u32VoltageThreshold);
void PWC_LVD_SetEdge(uint32_t u32Unit, uint32_t u32Edge);
void PWC_LVD_ExtInputCmd(uint32_t u32Unit, en_functional_state_t enNewState);
void PWC_LVD_IntResetCmd(uint32_t u32Unit, en_functional_state_t enNewState);

void PWC_LVD_DeInit(uint32_t u32Unit);
en_result_t PWC_LVD_Init(uint32_t u32Unit, const stc_pwc_lvd_init_t* pstcLvdInit);
en_result_t PWC_LVD_StructInit(stc_pwc_lvd_init_t* pstcLvdInit);

uint8_t PWC_LVD_GetCompareResult(uint32_t u32Unit);
en_flag_status_t PWC_LVD_GetDetectFlag(uint32_t u32Unit);
void PWC_LVD_ClearDetectFlag(uint32_t u32Unit);

void PWC_DebugCmd(en_functional_state_t enNewState);
/**
 * @}
 */

#endif /* DDL_PWC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_PWC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
