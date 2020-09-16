/**
 *******************************************************************************
 * @file  hc32m423_tmr0.c
 * @brief This file provides firmware functions to manage the TMR0
 *        (TMR0).
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
#include "hc32m423_tmr0.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TMR0 TMR0
 * @brief TMR0 Driver Library
 * @{
 */

#if (DDL_TMR0_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Locxal pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR0_Local_Macros TMR0 Local Macros
 * @{
 */
#define TMR0_BCONR_INIT_MASK             (TMR0_BCONR_CAPMDA | TMR0_BCONR_CKDIVA | \
                                         TMR0_BCONR_HICPA  | TMR0_BCONR_HSTAA  | \
                                         TMR0_BCONR_HSTPA  | TMR0_BCONR_HCLEA  | \
                                         TMR0_BCONR_SYNCLKA)

#define TMR0_HWTRIG_FUNC_MASK           (TMR0_START_COND_EVT | \
                                         TMR0_CLR_COND_EVT   | \
                                         TMR0_STOP_COND_EVT)

#define TMR0_CHB_POS                    (16U)
#define TMR0_OFFSET(ch)                 ((ch) * TMR0_CHB_POS)
/**
 * @defgroup TMR0_Check_Parameters_Validity TMR0 Check Parameters Validity
 * @{
 */
/*! Parameter validity check for TMR0 unit */
#define IS_VALID_UNIT(x)                                                       \
(   ((x) == CM_TMR0_1)                             ||                          \
    ((x) == CM_TMR0_2))

/*! Parameter validity check for TMR0 channel */
#define IS_VALID_CH(x)                                                    \
(   ((x) == TMR0_CH_A)                             ||                          \
    ((x) == TMR0_CH_B))

/*! Parameter validity check for clock division */
#define IS_VALID_CLK_DIV(x)                                               \
(   ((x) == TMR0_CLK_DIV1)                         ||                          \
    ((x) == TMR0_CLK_DIV2)                         ||                          \
    ((x) == TMR0_CLK_DIV4)                         ||                          \
    ((x) == TMR0_CLK_DIV8)                         ||                          \
    ((x) == TMR0_CLK_DIV16)                        ||                          \
    ((x) == TMR0_CLK_DIV32)                        ||                          \
    ((x) == TMR0_CLK_DIV64)                        ||                          \
    ((x) == TMR0_CLK_DIV128)                       ||                          \
    ((x) == TMR0_CLK_DIV256)                       ||                          \
    ((x) == TMR0_CLK_DIV512)                       ||                          \
    ((x) == TMR0_CLK_DIV1024))

/*! Parameter validity check for clock source */
#define IS_VALID_CLK_SRC(x)                                                    \
(   ((x) == TMR0_SYNC_CLK_PCLK)                    ||                          \
    ((x) == TMR0_SYNC_CLK_HWTRIG))

/*! Parameter validity check for hardware trigger */
#define IS_VALID_HWTRG_FUNC(x)                                                 \
(   ((x) != 0x0U)                                  &&                          \
    (((x) | TMR0_HWTRIG_FUNC_MASK) == TMR0_HWTRIG_FUNC_MASK))

/*! Parameter validity check for TMR0 function */
#define IS_VALID_TMR0_FUNC(x)                                                  \
(   ((x) == TMR0_FUNC_CMP)                         ||                          \
    ((x) == TMR0_FUNC_CAPT))
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
 * @defgroup TMR0_Global_Functions TMR0 Global Functions
 * @{
 */

/**
 * @brief  Tmr0 peripheral initialization structure clear
 * @param  [out] pstcTmr0Init       Tmr0 function structure
 *   @arg  See the structure definition for @ref stc_tmr0_init_t
 * @retval Ok: Success
 * @retval ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_StructInit(stc_tmr0_init_t* pstcTmr0Init)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcTmr0Init != NULL)
    {
        pstcTmr0Init->u32ClockDiv = TMR0_CLK_DIV1;
        pstcTmr0Init->u32ClockSrc = TMR0_SYNC_CLK_PCLK;
        pstcTmr0Init->u16PeriodValue = 0xFFFFU;
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Tmr0 peripheral function initialize
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u32Ch            TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] pstcTmr0Init     TMR0 function base parameter structure
 *   @arg  See the structure definition for @ref stc_tmr0_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_Init(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch, \
                      const stc_tmr0_init_t* pstcTmr0Init)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32TempCh = u32Ch;
    uint32_t u32Temp;
    uint32_t u32CMPRAddr;
    if (pstcTmr0Init != NULL)
    {
        DDL_ASSERT(IS_VALID_UNIT(TMR0x));
        DDL_ASSERT(IS_VALID_CH(u32TempCh));
        DDL_ASSERT(IS_VALID_CLK_DIV(pstcTmr0Init->u32ClockDiv));
        DDL_ASSERT(IS_VALID_CLK_SRC(pstcTmr0Init->u32ClockSrc));

        u32Temp = u32TempCh * 4UL;
        u32CMPRAddr = (uint32_t)(&TMR0x->CMPAR) + u32Temp;
        RW_MEM32(u32CMPRAddr) = pstcTmr0Init->u16PeriodValue;

        u32Temp = pstcTmr0Init->u32ClockDiv | pstcTmr0Init->u32ClockSrc;

        u32TempCh = TMR0_OFFSET(u32TempCh);
        /* Config mode, clock source */
        MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_INIT_MASK << u32TempCh), (u32Temp << u32TempCh));
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Get Tmr0 status (STFLR)
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u32Ch            TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval Set: Flag is set
 *         Reset: Flag is reset
 */
en_flag_status_t TMR0_GetStatus(const CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch)
{
    en_flag_status_t enRet = Reset;
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    if (READ_REG32_BIT(TMR0x->STFLR, (TMR0_STFLR_CMFA << u32TempCh)) != 0U)
    {
        enRet = Set;
    }
    return enRet;
}

/**
 * @brief  Clear Tmr0 status (STFLR)
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u32Ch            TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval None
 */
void TMR0_ClearStatus(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    /*Clear the Flag*/
    CLEAR_REG32_BIT(TMR0x->STFLR, TMR0_STFLR_CMFA << u32TempCh);
}

/**
 * @brief  Start TMR0
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u32Ch            TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval None
 */
void TMR0_Start(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    SET_REG32_BIT(TMR0x->BCONR, TMR0_BCONR_CSTA <<u32TempCh);
}

/**
 * @brief  Stop TMR0
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u32Ch            TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval None
 */
void TMR0_Stop(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    CLEAR_REG32_BIT(TMR0x->BCONR, TMR0_BCONR_CSTA <<u32TempCh);
}

/**
 * @brief  Tmr0 interrupt function command
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u32Ch            TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] enNewState       Disable or Enable the function
 * @retval None
 */
void TMR0_IntCmd(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch, \
                 en_functional_state_t enNewState)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_INTENA << u32TempCh), \
                 ((uint32_t)enNewState << TMR0_BCONR_INTENA_POS) << u32TempCh);
}

/**
 * @brief  Get Tmr0 counter value
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u32Ch            TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval The counter register data
 */
uint16_t TMR0_GetCountValue(const CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch)
{
    uint16_t u16CntVal;
    uint32_t u32CNTRAddr;
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));

    u32CNTRAddr = (uint32_t)&TMR0x->CNTAR + (u32TempCh * 4UL);
    u16CntVal = (uint16_t)RW_MEM32(u32CNTRAddr);
    return u16CntVal;
}

/**
 * @brief  Set Tmr0 counter value
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u32Ch            TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u16Value         The data to write to the counter register
 * @retval None
 * @note   Setting the count requires stop tmr0
 */
void TMR0_SetCountValue(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch, uint16_t u16Value)
{
    uint32_t u32CNTRAddr;
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));

    u32CNTRAddr = (uint32_t)&TMR0x->CNTAR + (u32TempCh * 4UL);
    RW_MEM32(u32CNTRAddr) = (uint32_t)u16Value;
}

/**
 * @brief  Get Tmr0 compare value
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u32Ch            TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval The compare register data
 */
uint16_t TMR0_GetCompareValue(const CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch)
{
    uint16_t u16CmpVal;
    uint32_t u32CMPRAddr;
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));

    u32CMPRAddr = (uint32_t)&TMR0x->CMPAR + (u32TempCh * 4UL);
    u16CmpVal = (uint16_t)RW_MEM32(u32CMPRAddr);
    return u16CmpVal;
}

/**
 * @brief  Set Tmr0 compare value
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] u32Ch            TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u16Value         The data to write to the compare register
 * @retval None
 */
void TMR0_SetCompareValue(CM_TMR0_TypeDef* TMR0x, uint32_t u32Ch, uint16_t u16Value)
{
    uint32_t u32CMPRAddr;
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));

    u32CMPRAddr = (uint32_t)&TMR0x->CMPAR + (u32TempCh * 4UL);
    RW_MEM32(u32CMPRAddr) = (uint32_t)u16Value;
}

/**
 * @brief  Set clock source.
 * @param  [in] TMR0x               Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:               TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:               TMR0 unit 2 instance register base
 * @param  [in] u32Ch               TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32Src              Specifies the clock source
 * This parameter can be a value of the following:
 *   @arg  TMR0_SYNC_CLK_PCLK:      Synchronous clock source: PCLK1.
 *   @arg  TMR0_SYNC_CLK_INTHWTRIG: Synchronous clock source: Hardware Trigger Event.
 * @retval None.
 */
void TMR0_SetClockSrc(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Src)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));
    DDL_ASSERT(IS_VALID_CLK_SRC(u32Src));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_SYNCLKA << u32TempCh), (u32Src << u32TempCh));
}

/**
 * @brief  Set the division of the clock source.
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u32Ch              TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32Div             Specifies the clock source division
 * This parameter can be a value of the following:
 *   @arg  TMR0_CLK_DIV1:          Clock source.
 *   @arg  TMR0_CLK_DIV2:          Clock source / 2.
 *   @arg  TMR0_CLK_DIV4:          Clock source / 4.
 *   @arg  TMR0_CLK_DIV8:          Clock source / 8.
 *   @arg  TMR0_CLK_DIV16:         Clock source / 16.
 *   @arg  TMR0_CLK_DIV32:         Clock source / 32.
 *   @arg  TMR0_CLK_DIV64:         Clock source / 64.
 *   @arg  TMR0_CLK_DIV128:        Clock source / 128.
 *   @arg  TMR0_CLK_DIV256:        Clock source / 256.
 *   @arg  TMR0_CLK_DIV512:        Clock source / 512.
 *   @arg  TMR0_CLK_DIV1024:       Clock source / 1024.
 * @retval None.
 */
void TMR0_SetClockDiv(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Div)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));
    DDL_ASSERT(IS_VALID_CLK_DIV(u32Div));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_CKDIVA << u32TempCh), (u32Div << u32TempCh));
}

/**
 * @brief  Enable or disable HardWare trigger function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u32Ch              TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] enNewState         Disable or Enable the function
 * @retval None
 */
void TMR0_HWCaptureCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, \
                           en_functional_state_t enNewState)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    if(enNewState == Enable)
    {
        SET_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HICPA << u32TempCh));
    }
    else
    {
        CLEAR_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HICPA << u32TempCh));
    }
}

/**
 * @brief  Enable or disable HardWare trigger start function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u32Ch              TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] enNewState         Disable or Enable the function
 * @retval None
 */
void TMR0_HWStartCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, \
                         en_functional_state_t enNewState)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    if(enNewState == Enable)
    {
        SET_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HSTAA << u32TempCh));
    }
    else
    {
        CLEAR_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HSTAA << u32TempCh));
    }
}

/**
 * @brief  Enable or disable HardWare trigger stop function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u32Ch              TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] enNewState         Disable or Enable the function
 * @retval None
 */
void TMR0_HWStopCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, \
                        en_functional_state_t enNewState)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    if(enNewState == Enable)
    {
        SET_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HSTPA << u32TempCh));
    }
    else
    {
        CLEAR_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HSTPA << u32TempCh));
    }
}

/**
 * @brief  Enable or disable HardWare trigger clear function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u32Ch              TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] enNewState         Disable or Enable the function
 * @retval None
 */
void TMR0_HWClearCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, \
                         en_functional_state_t enNewState)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    if(enNewState == Enable)
    {
        SET_REG32_BIT(TMR0x->BCONR, TMR0_BCONR_HCLEA << u32TempCh);
    }
    else
    {
        CLEAR_REG32_BIT(TMR0x->BCONR, TMR0_BCONR_HCLEA << u32TempCh);
    }
}

/**
 * @brief  Set Tmr0 Function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:              TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:              TMR0 unit 2 instance register base
 * @param  [in] u32Ch              TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32Func            Select TMR0 function
 *   @arg  TMR0_FUNC_CMP:          Select the Compare function for TMR0
 *   @arg  TMR0_FUNC_CAPT:         Select the Capture function for TMR0
 * @retval None
 */
void TMR0_SetFunc(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Func)
{
    uint32_t u32TempCh = u32Ch;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CH(u32TempCh));
    DDL_ASSERT(IS_VALID_TMR0_FUNC(u32Func));

    u32TempCh = TMR0_OFFSET(u32TempCh);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_CAPMDA << u32TempCh), (u32Func << u32TempCh));
}

/**
 * @brief  De-Initialize TMR0 function
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *  @arg CM_TMR0_1:              TMR0 unit 1 instance register base
 *  @arg CM_TMR0_2:              TMR0 unit 2 instance register base
 * @retval None
 */
void TMR0_DeInit(CM_TMR0_TypeDef* TMR0x)
{
    WRITE_REG32(TMR0x->CMPAR, 0x0000FFFFUL);
    WRITE_REG32(TMR0x->CMPBR, 0x0000FFFFUL);
    WRITE_REG32(TMR0x->CNTAR, 0UL);
    WRITE_REG32(TMR0x->CNTBR, 0UL);
    WRITE_REG32(TMR0x->STFLR, 0UL);
    WRITE_REG32(TMR0x->BCONR, 0UL);
}

/**
 * @brief  Set external trigger source for Tmr0
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_TMR0_1:            TMR0 unit 1 instance register base
 *   @arg  CM_TMR0_2:            TMR0 unit 2 instance register base
 * @param  [in] enEvent          External event source, @ref en_event_src_t
 * @retval None
 */
void TMR0_SetTriggerSrc(const CM_TMR0_TypeDef* TMR0x, en_event_src_t enEvent)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    if(TMR0x == CM_TMR0_1)
    {
        CM_AOS->TMR00_HTSSR = (uint32_t)enEvent;
    }
    else
    {
        CM_AOS->TMR01_HTSSR = (uint32_t)enEvent;
    }
}

/**
 * @}
 */

#endif /* DDL_TMR0_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
