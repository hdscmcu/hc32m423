/**
 *******************************************************************************
 * @file  hc32m423_interrupts.c
 * @brief This file provides firmware functions to manage the Interrupt Controller
 *        (INTC).
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
#include "hc32m423_interrupts.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_INTERRUPTS INTERRUPTS
 * @brief INTC Driver Library
 * @{
 */

#if (DDL_INTERRUPTS_ENABLE == DDL_ON) || (DDL_EXTINT_NMI_SWINT_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup INTC_Local_Macros INTC Local Macros
 * @{
 */
/**
 * @brief Maximum IRQ handler number
 */
#define IRQ_NUM_MAX             (8U)

/**
 * @brief Wakeup event enable mask
 */
#define INTC_WUPEN_MASK                                                         \
            (INTC_WUPEN_EIRQWUEN    | INTC_WUPEN_SWDTWUEN           |           \
             INTC_WUPEN_PVD1WUEN    | INTC_WUPEN_PVD2WUEN           |           \
             INTC_WUPEN_CMPI0WUEN   | INTC_WUPEN_TMR0WUEN           |           \
             INTC_WUPEN_RXWUEN)

/**
 * @brief Event enable mask
 */
#define INTC_EVT_MASK                                                           \
            (INTC_EVTER_EVTE0       | INTC_EVTER_EVTE1              |           \
             INTC_EVTER_EVTE2       | INTC_EVTER_EVTE3              |           \
             INTC_EVTER_EVTE4       | INTC_EVTER_EVTE5              |           \
             INTC_EVTER_EVTE6       | INTC_EVTER_EVTE7              |           \
             INTC_EVTER_EVTE8       | INTC_EVTER_EVTE9              |           \
             INTC_EVTER_EVTE10      | INTC_EVTER_EVTE11             |           \
             INTC_EVTER_EVTE12      | INTC_EVTER_EVTE13             |           \
             INTC_EVTER_EVTE14      | INTC_EVTER_EVTE15)

/**
 * @brief Interrupt enable mask
 */
#define INTC_INT_MASK                                                           \
            (INTC_IER_IER0          | INTC_IER_IER1                 |           \
             INTC_IER_IER2          | INTC_IER_IER3                 |           \
             INTC_IER_IER4          | INTC_IER_IER5                 |           \
             INTC_IER_IER6          | INTC_IER_IER7                 |           \
             INTC_IER_IER8          | INTC_IER_IER9                 |           \
             INTC_IER_IER10         | INTC_IER_IER11                |           \
             INTC_IER_IER12         | INTC_IER_IER13                |           \
             INTC_IER_IER14         | INTC_IER_IER15)

/**
 * @brief Software interrupt enable mask
 */
#define INTC_SWINT_MASK                                                         \
            (INTC_SWIER_SWIE0       | INTC_SWIER_SWIE1              |           \
             INTC_SWIER_SWIE2       | INTC_SWIER_SWIE3              |           \
             INTC_SWIER_SWIE4       | INTC_SWIER_SWIE5              |           \
             INTC_SWIER_SWIE6       | INTC_SWIER_SWIE7              |           \
             INTC_SWIER_SWIE8       | INTC_SWIER_SWIE9              |           \
             INTC_SWIER_SWIE10      | INTC_SWIER_SWIE11             |           \
             INTC_SWIER_SWIE12      | INTC_SWIER_SWIE13             |           \
             INTC_SWIER_SWIE14      | INTC_SWIER_SWIE15)

/**
 * @defgroup INTC_Check_Parameters_Validity INTC Check Parameters Validity
 * @{
 */
/*  Parameter validity check for wakeup source from stop mode. */
#define IS_INTC_WKUP_SRC(src)                                                   \
(   ((src) != 0x00UL)                           &&                              \
    (((src) | INTC_WUPEN_MASK) == INTC_WUPEN_MASK))

/*  Parameter validity check for event number. */
#define IS_INTC_EVT(evt)                                                        \
(   ((evt) != 0x00UL)                           &&                              \
    (((evt) | INTC_EVT_MASK) == INTC_EVT_MASK))

/*  Parameter validity check for interrupt index. */
#define IS_INTC_INT(it)                                                         \
(   ((it) != 0x00UL)                            &&                              \
    (((it) | INTC_INT_MASK) == INTC_INT_MASK))

/*  Parameter validity check for software interrupt index. */
#define IS_INTC_SWINT(swit)                                                     \
(   ((swit) != 0x00UL)                          &&                              \
    (((swit) | INTC_SWINT_MASK) == INTC_SWINT_MASK))

/*  Parameter validity check for NMI pin filter A function. */
#define IS_NMI_FAE(fae)                                                         \
(   ((fae) == NMI_FILTER_A_OFF)                 ||                              \
    ((fae) == NMI_FILTER_A_ON))

/*  Parameter validity check for NMI pin filter B function. */
#define IS_NMI_FBE(fbe)                                                         \
(   ((fbe) == NMI_FILTER_B_OFF)                 ||                              \
    ((fbe) == NMI_FILTER_B_ON))

/*  Parameter validity check for MNI pin filter A clock division. */
#define IS_NMI_FACLK(faclk)                                                     \
(   ((faclk) == NMI_FILTER_A_CLK_DIV1)          ||                              \
    ((faclk) == NMI_FILTER_A_CLK_DIV8)          ||                              \
    ((faclk) == NMI_FILTER_A_CLK_DIV32)         ||                              \
    ((faclk) == NMI_FILTER_A_CLK_DIV64))

/*  Parameter validity check for NMI pin trigger edge. */
#define IS_NMI_TRIG(trigger)                                                 \
(   ((trigger) == NMI_TRIG_FALLING)             ||                              \
    ((trigger) == NMI_TRIG_RISING))

/*  Parameter validity check for NMI trigger source. */
#define IS_NMI_SRC(src)                                                         \
(   ((src) != 0x00UL)                           &&                              \
    (((src) | NMI_SRC_MASK) == NMI_SRC_MASK))

/*  Parameter validity check for EXTINT filter A function. */
#define IS_EXTINT_FAE(fae)                                                      \
(   ((fae) == EXTINT_FILTER_A_OFF)              ||                              \
    ((fae) == EXTINT_FILTER_A_ON))

/*  Parameter validity check for EXTINT filter B function. */
#define IS_EXTINT_FBE(fbe)                                                      \
(   ((fbe) == EXTINT_FILTER_B_OFF)              ||                              \
    ((fbe) == EXTINT_FILTER_B_ON))

/*  Parameter validity check for EXTINT filter A clock division. */
#define IS_EXTINT_FACLK(faclk)                                                  \
(   ((faclk) == EXTINT_FILTER_A_CLK_DIV1)       ||                              \
    ((faclk) == EXTINT_FILTER_A_CLK_DIV8)       ||                              \
    ((faclk) == EXTINT_FILTER_A_CLK_DIV32)      ||                              \
    ((faclk) == EXTINT_FILTER_A_CLK_DIV64))

/*  Parameter validity check for EXTINT filter B clock time. */
#define IS_NMI_EXTINT_FBTIME(fbtim)                                             \
(   ((fbtim) == NMI_EXTINT_FILTER_B_500NS)      ||                              \
    ((fbtim) == NMI_EXTINT_FILTER_B_1US)        ||                              \
    ((fbtim) == NMI_EXTINT_FILTER_B_2US)        ||                              \
    ((fbtim) == NMI_EXTINT_FILTER_B_4US))

/*  Parameter validity check for EXTINT trigger edge. */
#define IS_EXTINT_TRIG(trigger)                                                 \
(   ((trigger) == EXTINT_TRIG_LOW)              ||                              \
    ((trigger) == EXTINT_TRIG_RISING)           ||                              \
    ((trigger) == EXTINT_TRIG_FALLING)          ||                              \
    ((trigger) == EXTINT_TRIG_BOTH))

/*  Parameter validity check for EXTINT channel. */
#define IS_EXTINT_CH(ch)     (((ch) & EXTINT_CH_MASK) != (uint8_t)0x00U)

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
/**
 * @defgroup INTC_Local_Variable INTC Local Variable
 * @{
 */
static func_ptr_t m_apfnIrqHandler[IRQ_NUM_MAX] = {NULL};
static func_ptr_t m_pfnNmiCallback;
/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup INTC_Global_Functions INTC Global Functions
 * @{
 */
/**
 * @brief  IRQ sign in function
 * @param  [in] pstcIrqSignConfig pointer of IRQ registration structure
 *   @arg  enIntSrc: can be any value @ref en_int_src_t
 *   @arg  enIRQn: can be any value from Int000~Int007 @ref IRQn_Type
 *   @arg  pfnCallback: Callback function
 * @retval An en_result_t enumeration value
 *         Ok: IRQ register successfully
 *         ErrorInvalidParameter: ErrorInvalidParameter: IRQ No. is out of range;
 *                                NULL pointer.
 *         ErrorUninitialized: Specified IRQ entry was signed before.
 */
en_result_t INTC_IrqSignIn(const stc_irq_signin_config_t *pstcIrqSignConfig)
{
    __IO uint32_t *INTC_SELx;
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if ((NULL == pstcIrqSignConfig) || (pstcIrqSignConfig->enIRQn > INT007_IRQn))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        INTC_SELx = (uint32_t *)((uint32_t)(&CM_INTC->SEL0) +                   \
                    (4U * (uint32_t)(pstcIrqSignConfig->enIRQn)));
        /* for MISRAC2004-12.4 */
        if (0x1FFUL == ((*INTC_SELx) & 0x1FFUL))
        {
            WRITE_REG32(*INTC_SELx, pstcIrqSignConfig->enIntSrc);
            /* Callback function */
            m_apfnIrqHandler[pstcIrqSignConfig->enIRQn] = pstcIrqSignConfig->pfnCallback;
        }
        else if ((uint32_t)(pstcIrqSignConfig->enIntSrc) == ((*INTC_SELx) & 0x1FFUL))
        {
            WRITE_REG32(*INTC_SELx, pstcIrqSignConfig->enIntSrc);
            /* Callback function */
            m_apfnIrqHandler[pstcIrqSignConfig->enIRQn] = pstcIrqSignConfig->pfnCallback;
        }
        else
        {
            enRet = ErrorUninitialized;
        }
    }
    return enRet;
}

/**
 * @brief  IRQ sign out function
 * @param  [in] enIRQn can be any value from Int000~Int007 @ref IRQn_Type
 * @retval An en_result_t enumeration value
 *         Ok: IRQ sign out successfully
 *         ErrorInvalidParameter: IRQ No. is out of range
 */
en_result_t INTC_IrqSignOut(IRQn_Type enIRQn)
{
    __IO uint32_t *INTC_SELx;
    en_result_t enRet = Ok;

    if ((enIRQn < INT000_IRQn) || (enIRQn > INT007_IRQn))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        INTC_SELx = (uint32_t *)((uint32_t)(&CM_INTC->SEL0) + (4UL * (uint32_t)enIRQn));
        WRITE_REG32(*INTC_SELx, 0x1FFUL);
        m_apfnIrqHandler[enIRQn] = NULL;
    }
    return enRet;
}

/**
 * @brief  Stop mode wake-up source configure
 * @param  [in] u32Src Wake-up source
 *   @arg  INTC_WUPEN_EIRQWUEN
 *   @arg  INTC_WUPEN_EIRQWUEN_0
 *   @arg  INTC_WUPEN_EIRQWUEN_1
 *   @arg  INTC_WUPEN_EIRQWUEN_2
 *   @arg  INTC_WUPEN_EIRQWUEN_3
 *   @arg  INTC_WUPEN_EIRQWUEN_4
 *   @arg  INTC_WUPEN_EIRQWUEN_5
 *   @arg  INTC_WUPEN_EIRQWUEN_6
 *   @arg  INTC_WUPEN_EIRQWUEN_7
 *   @arg  INTC_WUPEN_SWDTWUEN
 *   @arg  INTC_WUPEN_PVD1WUEN
 *   @arg  INTC_WUPEN_PVD2WUEN
 *   @arg  INTC_WUPEN_CMPI0WUEN
 *   @arg  INTC_WUPEN_TMR0WUEN
 *   @arg  INTC_WUPEN_RXWUEN
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding wake up source
 *   @arg  Disable: Disable corresponding wake up source
 * @retval None
 */
void INTC_WakeupSrcCmd(uint32_t u32Src, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_WKUP_SRC(u32Src));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(CM_INTC->WUPEN, u32Src);
    }
    else
    {
        CLEAR_REG32_BIT(CM_INTC->WUPEN, u32Src);
    }
}

/**
 * @brief  Event or Interrupt output configure
 * @param  [in] u32Event Event index
 *   @arg  INTC_EVTER_EVTE0
 *   @arg  INTC_EVTER_EVTE1
 *   @arg  INTC_EVTER_EVTE2
 *   @arg  INTC_EVTER_EVTE3
 *   @arg  INTC_EVTER_EVTE4
 *   @arg  INTC_EVTER_EVTE5
 *   @arg  INTC_EVTER_EVTE6
 *   @arg  INTC_EVTER_EVTE7
 *   @arg  INTC_EVTER_EVTE8
 *   @arg  INTC_EVTER_EVTE9
 *   @arg  INTC_EVTER_EVTE10
 *   @arg  INTC_EVTER_EVTE11
 *   @arg  INTC_EVTER_EVTE12
 *   @arg  INTC_EVTER_EVTE13
 *   @arg  INTC_EVTER_EVTE14
 *   @arg  INTC_EVTER_EVTE15
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding event to CPU
 *   @arg  Disable: Disable corresponding event to CPU but interrupt to NVIC
 * @retval None
 */
void INTC_EventCmd(uint32_t u32Event, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_EVT(u32Event));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(CM_INTC->EVTER, u32Event);
    }
    else
    {
        CLEAR_REG32_BIT(CM_INTC->EVTER, u32Event);
    }
}

/**
 * @brief  Interrupt function configure
 * @param  [in] u32Int Interrupt index
 *   @arg  INTC_IER_IER0
 *   @arg  INTC_IER_IER1
 *   @arg  INTC_IER_IER2
 *   @arg  INTC_IER_IER3
 *   @arg  INTC_IER_IER4
 *   @arg  INTC_IER_IER5
 *   @arg  INTC_IER_IER6
 *   @arg  INTC_IER_IER7
 *   @arg  INTC_IER_IER8
 *   @arg  INTC_IER_IER9
 *   @arg  INTC_IER_IER10
 *   @arg  INTC_IER_IER11
 *   @arg  INTC_IER_IER12
 *   @arg  INTC_IER_IER13
 *   @arg  INTC_IER_IER14
 *   @arg  INTC_IER_IER15
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding interrupt to NVIC
 *   @arg  Disable: Disable corresponding interrupt to NVIC
 * @retval None
 */
void INTC_IntCmd(uint32_t u32Int, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_INT(u32Int));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(CM_INTC->IER, u32Int);
    }
    else
    {
        CLEAR_REG32_BIT(CM_INTC->IER, u32Int);
    }
}

/**
 * @brief  Software Interrupt function configure
 * @param  [in] u32SWInt Software Interrupt index
 *   @arg  INTC_SWIER_SWIE0
 *   @arg  INTC_SWIER_SWIE1
 *   @arg  INTC_SWIER_SWIE2
 *   @arg  INTC_SWIER_SWIE3
 *   @arg  INTC_SWIER_SWIE4
 *   @arg  INTC_SWIER_SWIE5
 *   @arg  INTC_SWIER_SWIE6
 *   @arg  INTC_SWIER_SWIE7
 *   @arg  INTC_SWIER_SWIE8
 *   @arg  INTC_SWIER_SWIE9
 *   @arg  INTC_SWIER_SWIE10
 *   @arg  INTC_SWIER_SWIE11
 *   @arg  INTC_SWIER_SWIE12
 *   @arg  INTC_SWIER_SWIE13
 *   @arg  INTC_SWIER_SWIE14
 *   @arg  INTC_SWIER_SWIE15
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding software interrupt
 *   @arg  Disable: Disable corresponding software interrupt
 * @retval None
 */
void INTC_SWIntCmd(uint32_t u32SWInt, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_SWINT(u32SWInt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(CM_INTC->SWIER, u32SWInt);
    }
    else
    {
        CLEAR_REG32_BIT(CM_INTC->SWIER, u32SWInt);
    }
}

/**
 * @brief  Initialize NMI. Fill each pstcNmiInit with default value
 * @param  [in] pstcNmiInit Pointer to a stc_nmi_init_t structure that
 *                             contains configuration information.
 * @retval An en_result_t enumeration value
 *         Ok: NMI structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t NMI_StructInit(stc_nmi_init_t *pstcNmiInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcNmiInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcNmiInit->u32NmiFilterAClockDiv  = NMI_FILTER_A_CLK_DIV1;
        pstcNmiInit->u32NmiFilterA    = NMI_FILTER_A_OFF;
        pstcNmiInit->u32NmiTrigger    = NMI_TRIG_FALLING;
        pstcNmiInit->u32NmiSrc        = NMI_SRC_NMI_PIN;
        pstcNmiInit->pfnNmiCallback   = NULL;
    }
    return enRet;
}

/**
 * @brief  Initialize NMI.
 * @param  [in] pstcNmiInit Pointer to a pstcNmiInit structure that
 *                             contains configuration information.
 * @retval An en_result_t enumeration value
 *         Ok: NMI initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t NMI_Init(const stc_nmi_init_t *pstcNmiInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if ((NULL == pstcNmiInit) || (NULL == pstcNmiInit->pfnNmiCallback))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_NMI_FAE(pstcNmiInit->u32NmiFilterA));
        DDL_ASSERT(IS_NMI_FACLK(pstcNmiInit->u32NmiFilterAClockDiv));
        DDL_ASSERT(IS_NMI_TRIG(pstcNmiInit->u32NmiTrigger));
        DDL_ASSERT(IS_NMI_SRC(pstcNmiInit->u32NmiSrc));

        /* NMI pin interrupt configure */
        WRITE_REG32(CM_INTC->NMICR,                                             \
                  (pstcNmiInit->u32NmiFilterA           |                       \
                   pstcNmiInit->u32NmiFilterAClockDiv   |                       \
                   pstcNmiInit->u32NmiTrigger));

        /* Clear all NMI trigger source before set */
        WRITE_REG32(CM_INTC->NMICFR, INTC_NMICFR_MASK);

        /* NMI trigger source configure */
        WRITE_REG32(CM_INTC->NMIER, pstcNmiInit->u32NmiSrc);

        /* NMI callback function configure */
        m_pfnNmiCallback = pstcNmiInit->pfnNmiCallback;
    }
    return enRet;
}

/**
 * @brief  Get NMI trigger source flag
 * @param  [in] u32Flag NMI trigger source, @ref NMI_TriggerSrc_Sel for details
 *   @arg  NMI_SRC_NMI_PIN
 *   @arg  NMI_SRC_SWDT
 *   @arg  NMI_SRC_LVD1
 *   @arg  NMI_SRC_LVD2
 *   @arg  NMI_SRC_XTAL_STOP
 *   @arg  NMI_SRC_RAM_PARITY_ERR
 *   @arg  NMI_SRC_WDT
 * @retval An en_flag_status_t enumeration value
 *         Set: NMI is triggered by corresponding source
 *         Reset: NMI is not triggered by corresponding source
 */
en_flag_status_t NMI_GetNmiStatus(uint32_t u32Flag)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_NMI_SRC(u32Flag));

    return (0UL != (READ_REG32(CM_INTC->NMIFR) & u32Flag)) ? Set : Reset;
}

/**
 * @brief  Clear specified NMI trigger source flag
 * @param  [in] u32Flag NMI trigger source, @ref NMI_TriggerSrc_Sel for details
 *   @arg  NMI_SRC_NMI_PIN
 *   @arg  NMI_SRC_SWDT
 *   @arg  NMI_SRC_LVD1
 *   @arg  NMI_SRC_LVD2
 *   @arg  NMI_SRC_XTAL_STOP
 *   @arg  NMI_SRC_RAM_PARITY_ERR
 *   @arg  NMI_SRC_WDT
 * @retval None
 */
void NMI_ClearNmiStatus(uint32_t u32Flag)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_NMI_SRC(u32Flag));

    MODIFY_REG32(CM_INTC->NMICFR, INTC_NMICFR_MASK, u32Flag);
}

/**
 * @brief  NMI IRQ handler
 * @param  None
 * @retval None
 */
void NMI_IrqHandler(void)
{
    if (NULL != m_pfnNmiCallback)
    {
        m_pfnNmiCallback();
    }
}

/**
 * @brief  Initialize External interrupt.
 * @param  [in] u32Ch Channel of external interrupt
 *   @arg  EXTINT_CH00
 *   @arg  EXTINT_CH01
 *   @arg  EXTINT_CH02
 *   @arg  EXTINT_CH03
 *   @arg  EXTINT_CH04
 *   @arg  EXTINT_CH05
 *   @arg  EXTINT_CH06
 *   @arg  EXTINT_CH07
 * @param  [in] pstcExtIntInit Pointer to a pstcExtIntInit structure that
 *                             contains configuration information.
 * @retval An en_result_t enumeration value
 *         Ok:  EXTINT initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t EXTINT_Init(uint32_t u32Ch, const stc_extint_init_t *pstcExtIntInit)
{
    uint8_t u8ExtIntPos;
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcExtIntInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_EXTINT_FAE(pstcExtIntInit->u32ExtIntFilterA));
        DDL_ASSERT(IS_EXTINT_FACLK(pstcExtIntInit->u32ExtIntFilterAClock));
        DDL_ASSERT(IS_EXTINT_TRIG(pstcExtIntInit->u32ExtIntLevel));
        DDL_ASSERT(IS_EXTINT_CH(u32Ch));

        for (u8ExtIntPos = 0U; u8ExtIntPos < 8U; u8ExtIntPos++)
        {
            if (0UL != (u32Ch & (1UL << u8ExtIntPos)))
            {
                WRITE_REG32(*(uint32_t *)((uint32_t)(&CM_INTC->EIRQCR0) +       \
                            (4UL*u8ExtIntPos)),                                 \
                            (pstcExtIntInit->u32ExtIntFilterA       |           \
                            pstcExtIntInit->u32ExtIntFilterAClock   |           \
                            pstcExtIntInit->u32ExtIntLevel));
            }
        }
    }
    return enRet;
}

/**
 * @brief  Initialize ExtInt. Fill each pstcExtIntInit with default value
 * @param  [in] pstcExtIntInit Pointer to a pstcExtIntInit structure
 *                              that contains configuration information.
 * @retval An en_result_t enumeration value
 *         Ok: EXTINT structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t EXTINT_StructInit(stc_extint_init_t *pstcExtIntInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcExtIntInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcExtIntInit->u32ExtIntFilterA      = EXTINT_FILTER_A_OFF;
        pstcExtIntInit->u32ExtIntFilterAClock = EXTINT_FILTER_A_CLK_DIV1;
        pstcExtIntInit->u32ExtIntLevel        = EXTINT_TRIG_FALLING;
    }
    return enRet;
}

/**
 * @brief  Clear specified External interrupt trigger source
 * @param  [in] u32Ch External interrupt channel, @ref EXTINT_Channel_Sel for details
 *   @arg  EXTINT_CH00
 *   @arg  EXTINT_CH01
 *   @arg  EXTINT_CH02
 *   @arg  EXTINT_CH03
 *   @arg  EXTINT_CH04
 *   @arg  EXTINT_CH05
 *   @arg  EXTINT_CH06
 *   @arg  EXTINT_CH07
 * @retval None
 */
void EXTINT_ClearExtIntStatus(uint32_t u32Ch)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_EXTINT_CH(u32Ch));

    SET_REG32_BIT(CM_INTC->EIRQCFR, u32Ch);
}

/**
 * @brief  Get specified External interrupt trigger source
 * @param  [in] u32Ch External interrupt channel, @ref EXTINT_Channel_Sel for details
 *   @arg  EXTINT_CH00
 *   @arg  EXTINT_CH01
 *   @arg  EXTINT_CH02
 *   @arg  EXTINT_CH03
 *   @arg  EXTINT_CH04
 *   @arg  EXTINT_CH05
 *   @arg  EXTINT_CH06
 *   @arg  EXTINT_CH07
 * @retval An en_flag_status_t enumeration value
 *         Set: Specified channel of external interrupt is triggered
 *         Reset: Specified channel of external interrupt is not triggered
 */
en_flag_status_t EXTINT_GetExtIntStatus(uint32_t u32Ch)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_EXTINT_CH(u32Ch));

    return (0UL != (READ_REG32(CM_INTC->EIRQFR) & u32Ch)) ? Set : Reset;
}

/**
 * @brief  EXTINT filter B clock function command
 * @param  [in] u32Ch External interrupt channel, @ref EXTINT_Channel_Sel for details
 *   @arg  EXTINT_CH00
 *   @arg  EXTINT_CH01
 *   @arg  EXTINT_CH02
 *   @arg  EXTINT_CH03
 *   @arg  EXTINT_CH04
 *   @arg  EXTINT_CH05
 *   @arg  EXTINT_CH06
 *   @arg  EXTINT_CH07
 * @param  [in] enNewState The new state of EXTINT filter B clock
 *   @arg  Enable
 *   @arg  Disable
 * @retval None
 */
void EXTINT_FilterBCmd(uint32_t u32Ch, en_functional_state_t enNewState)
{
    uint8_t u8ExtIntPos;
    __IO uint32_t *EIRQCRx;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_EXTINT_CH(u32Ch));

    for (u8ExtIntPos = 0U; u8ExtIntPos < 8U; u8ExtIntPos++)
    {
        if (0UL != (u32Ch & (1UL << u8ExtIntPos)))
        {
            EIRQCRx = (__IO uint32_t *)((uint32_t)(&CM_INTC->EIRQCR0) + (4UL*u8ExtIntPos));
            MODIFY_REG32(*EIRQCRx, INTC_EIRQCR_NOCEN, enNewState);
        }
    }
}

/**
 * @brief  EXTINT filter B clock function command
 * @param  [in] enNewState The new state of NMI filter B clock
 *   @arg  Enable
 *   @arg  Disable
 * @retval None
 */
void NMI_FilterBCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_INTC->NMICR_b.NOCEN, enNewState);
}

/**
 * @brief  Set time of filter B clock
 * @param  [in] u32Time Time of filter B clock, @ref NMI_EXTINT_FilterBTim_Sel for details
 *   @arg  NMI_EXTINT_FILTER_B_500NS
 *   @arg  NMI_EXTINT_FILTER_B_1US
 *   @arg  NMI_EXTINT_FILTER_B_2US
 *   @arg  NMI_EXTINT_FILTER_B_4US
 * @retval None
 */
void NMI_EXTINT_SetFilterBClockTime(uint32_t u32Time)
{
    DDL_ASSERT(IS_NMI_EXTINT_FBTIME(u32Time));

    MODIFY_REG32(CM_INTC->NMICR, INTC_NMICR_NOCSEL, u32Time);
}

/**
 * @brief  NMI IRQ handler
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
    NMI_IrqHandler();
}

/**
 * @brief  Hard Fault IRQ handler
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
    HardFault_IrqHandler();
}

/**
 * @brief  Mem manage fault IRQ handler
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
    MemManage_IrqHandler();
}

/**
 * @brief  Bus fault IRQ handler
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
    BusFault_IrqHandler();
}

/**
 * @brief  Usage fault IRQ handler
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
    UsageFault_IrqHandler();
}

/**
 * @brief  SVCall IRQ handler
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
    SVC_IrqHandler();
}

/**
 * @brief  Debbug monitor IRQ handler
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
    DebugMon_IrqHandler();
}

/**
 * @brief  PendSV IRQ handler
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
    PendSV_IrqHandler();
}

/**
 * @brief  SysTick IRQ handler
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
    SysTick_IrqHandler();
}

/**
 * @brief  Interrupt No.000 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ000_Handler(void)
{
    m_apfnIrqHandler[INT000_IRQn]();
}

/**
 * @brief  Interrupt No.001 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ001_Handler(void)
{
    m_apfnIrqHandler[INT001_IRQn]();
}

/**
 * @brief  Interrupt No.002 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ002_Handler(void)
{
    m_apfnIrqHandler[INT002_IRQn]();
}

/**
 * @brief  Interrupt No.003 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ003_Handler(void)
{
    m_apfnIrqHandler[INT003_IRQn]();
}

/**
 * @brief  Interrupt No.004 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ004_Handler(void)
{
    m_apfnIrqHandler[INT004_IRQn]();
}

/**
 * @brief  Interrupt No.005 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ005_Handler(void)
{
    m_apfnIrqHandler[INT005_IRQn]();
}

/**
 * @brief  Interrupt No.006 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ006_Handler(void)
{
    m_apfnIrqHandler[INT006_IRQn]();
}

/**
 * @brief  Interrupt No.007 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ007_Handler(void)
{
    m_apfnIrqHandler[INT007_IRQn]();
}

/**
 * @brief  Interrupt No.008 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ008_Handler(void)
{
    ExtInt00_SWInt08_IrqHandler();
}

/**
 * @brief  Interrupt No.009 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ009_Handler(void)
{
    ExtInt01_SWInt09_IrqHandler();
}

/**
 * @brief  Interrupt No.010 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ010_Handler(void)
{
    ExtInt02_SWInt10_IrqHandler();
}

/**
 * @brief  Interrupt No.011 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ011_Handler(void)
{
    ExtInt03_SWInt11_IrqHandler();
}

/**
 * @brief  Interrupt No.012 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ012_Handler(void)
{
    ExtInt04_SWInt12_IrqHandler();
}

/**
 * @brief  Interrupt No.013 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ013_Handler(void)
{
    ExtInt05_SWInt13_IrqHandler();
}

/**
 * @brief  Interrupt No.014 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ014_Handler(void)
{
    ExtInt06_SWInt14_IrqHandler();
}

/**
 * @brief  Interrupt No.015 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ015_Handler(void)
{
    ExtInt07_SWInt15_IrqHandler();
}

/**
 * @brief  Interrupt No.016 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ016_Handler(void)
{
    DMA_TC0_IrqHandler();
}

/**
 * @brief  Interrupt No.017 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ017_Handler(void)
{
    DMA_TC1_IrqHandler();
}

/**
 * @brief  Interrupt No.018 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ018_Handler(void)
{
    DMA_TC2_IrqHandler();
}

/**
 * @brief  Interrupt No.019 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ019_Handler(void)
{
    DMA_TC3_IrqHandler();
}

/**
 * @brief  Interrupt No.020 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ020_Handler(void)
{
    DMA_BTC0_IrqHandler();
}

/**
 * @brief  Interrupt No.021 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ021_Handler(void)
{
    DMA_BTC1_IrqHandler();
}

/**
 * @brief  Interrupt No.022 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ022_Handler(void)
{
    DMA_BTC2_IrqHandler();
}

/**
 * @brief  Interrupt No.023 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ023_Handler(void)
{
    DMA_BTC3_IrqHandler();
}

/**
 * @brief  Interrupt No.024 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ024_Handler(void)
{
    DMA_Error_IrqHandler();
}

/**
 * @brief  Interrupt No.025 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ025_Handler(void)
{
    EFM_ProgramEraseError_IrqHandler();
}

/**
 * @brief  Interrupt No.026 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ026_Handler(void)
{
    EFM_ColError_IrqHandler();
}

/**
 * @brief  Interrupt No.027 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ027_Handler(void)
{
    EFM_OpEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.028 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ028_Handler(void)
{
    DCU_IrqHandler();
}

/**
 * @brief  Interrupt No.029 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ029_Handler(void)
{
    TMR0_1_CmpA_IrqHandler();
}

/**
 * @brief  Interrupt No.030 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ030_Handler(void)
{
    TMR0_1_CmpB_IrqHandler();
}

/**
 * @brief  Interrupt No.031 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ031_Handler(void)
{
    TMR0_2_CmpA_IrqHandler();
}

/**
 * @brief  Interrupt No.032 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ032_Handler(void)
{
    TMR0_2_CmpB_IrqHandler();
}

/**
 * @brief  Interrupt No.033 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ033_Handler(void)
{
    CLK_XtalStop_IrqHandler();
}

/**
 * @brief  Interrupt No.034 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ034_Handler(void)
{
    SWDT_IrqHandler();
}

/**
 * @brief  Interrupt No.035 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ035_Handler(void)
{
    TMRA_1_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.036 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ036_Handler(void)
{
    TMRA_1_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.037 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ037_Handler(void)
{
    TMRA_1_Cmp_IrqHandler();
}

/**
 * @brief  Interrupt No.038 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ038_Handler(void)
{
    TMRA_2_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.039 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ039_Handler(void)
{
    TMRA_2_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.040 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ040_Handler(void)
{
    TMRA_2_Cmp_IrqHandler();
}

/**
 * @brief  Interrupt No.041 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ041_Handler(void)
{
    TMRA_3_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.042 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ042_Handler(void)
{
    TMRA_3_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.043 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ043_Handler(void)
{
    TMRA_3_Cmp_IrqHandler();
}

/**
 * @brief  Interrupt No.044 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ044_Handler(void)
{
    TMRA_4_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.045 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ045_Handler(void)
{
    TMRA_4_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.046 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ046_Handler(void)
{
    TMRA_4_Cmp_IrqHandler();
}

/**
 * @brief  Interrupt No.047 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ047_Handler(void)
{
    TMRB_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.048 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ048_Handler(void)
{
    TMRB_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.049 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ049_Handler(void)
{
    TMRB_Cmp_IrqHandler();
}

/**
 * @brief  Interrupt No.050 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ050_Handler(void)
{
    USART1_RxError_IrqHandler();
}

/**
 * @brief  Interrupt No.051 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ051_Handler(void)
{
    USART1_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.052 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ052_Handler(void)
{
    USART1_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.053 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ053_Handler(void)
{
    USART1_TxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.054 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ054_Handler(void)
{
    USART2_RxError_IrqHandler();
}

/**
 * @brief  Interrupt No.055 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ055_Handler(void)
{
    USART2_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.056 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ056_Handler(void)
{
    USART2_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.057 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ057_Handler(void)
{
    USART2_TxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.058 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ058_Handler(void)
{
    USART3_RxError_IrqHandler();
}

/**
 * @brief  Interrupt No.059 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ059_Handler(void)
{
    USART3_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.060 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ060_Handler(void)
{
    USART3_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.061 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ061_Handler(void)
{
    USART3_TxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.062 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ062_Handler(void)
{
    USART4_RxError_IrqHandler();
}

/**
 * @brief  Interrupt No.063 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ063_Handler(void)
{
    USART4_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.064 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ064_Handler(void)
{
    USART4_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.065 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ065_Handler(void)
{
    USART4_TxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.066 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ066_Handler(void)
{
    SPI_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.067 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ067_Handler(void)
{
    SPI_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.068 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ068_Handler(void)
{
    SPI_Idle_IrqHandler();
}

/**
 * @brief  Interrupt No.069 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ069_Handler(void)
{
    SPI_Error_IrqHandler();
}

/**
 * @brief  Interrupt No.070 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ070_Handler(void)
{
    TMR4_GCmpUH_IrqHandler();
}

/**
 * @brief  Interrupt No.071 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ071_Handler(void)
{
    TMR4_GCmpUL_IrqHandler();
}

/**
 * @brief  Interrupt No.072 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ072_Handler(void)
{
    TMR4_GCmpVH_IrqHandler();
}

/**
 * @brief  Interrupt No.073 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ073_Handler(void)
{
    TMR4_GCmpVL_IrqHandler();
}

/**
 * @brief  Interrupt No.074 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ074_Handler(void)
{
    TMR4_GCmpWH_IrqHandler();
}

/**
 * @brief  Interrupt No.075 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ075_Handler(void)
{
    TMR4_GCmpWL_IrqHandler();
}

/**
 * @brief  Interrupt No.076 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ076_Handler(void)
{
    TMR4_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.077 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ077_Handler(void)
{
    TMR4_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.078 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ078_Handler(void)
{
    TMR4_ReloadU_IrqHandler();
}

/**
 * @brief  Interrupt No.079 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ079_Handler(void)
{
    TMR4_ReloadV_IrqHandler();
}

/**
 * @brief  Interrupt No.080 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ080_Handler(void)
{
    TMR4_ReloadW_IrqHandler();
}

/**
 * @brief  Interrupt No.081 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ081_Handler(void)
{
    EMB_IrqHandler();
}

/**
 * @brief  Interrupt No.082 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ082_Handler(void)
{
    CMP1_IrqHandler();
}

/**
 * @brief  Interrupt No.083 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ083_Handler(void)
{
    CMP2_IrqHandler();
}

/**
 * @brief  Interrupt No.084 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ084_Handler(void)
{
    CMP3_IrqHandler();
}

/**
 * @brief  Interrupt No.085 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ085_Handler(void)
{
    I2C_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.086 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ086_Handler(void)
{
    I2C_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.087 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ087_Handler(void)
{
    I2C_TxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.088 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ088_Handler(void)
{
    I2C_Error_IrqHandler();
}

/**
 * @brief  Interrupt No.089 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ089_Handler(void)
{
    USART1_WKUP_IrqHandler();
}

/**
 * @brief  Interrupt No.090 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ090_Handler(void)
{
    PWC_LVD1_IrqHandler();
}

/**
 * @brief  Interrupt No.091 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ091_Handler(void)
{
    PWC_LVD2_IrqHandler();
}

/**
 * @brief  Interrupt No.092 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ092_Handler(void)
{
    FCM_Error_IrqHandler();
}

/**
 * @brief  Interrupt No.093 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ093_Handler(void)
{
    FCM_End_IrqHandler();
}

/**
 * @brief  Interrupt No.094 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ094_Handler(void)
{
    FCM_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.095 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ095_Handler(void)
{
    WDT_IrqHandler();
}

/**
 * @brief  Interrupt No.096 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ096_Handler(void)
{
    CTC_IrqHandler();
}

/**
 * @brief  Interrupt No.097 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ097_Handler(void)
{
    ADC_SeqA_IrqHandler();
}

/**
 * @brief  Interrupt No.098 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ098_Handler(void)
{
    ADC_SeqB_IrqHandler();
}

/**
 * @brief  Interrupt No.099 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ099_Handler(void)
{
    ADC_ChCmp_IrqHandler();
}

/**
 * @brief  Interrupt No.100 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ100_Handler(void)
{
    ADC_SeqCmp_IrqHandler();
}

/**
 * @}
 */

/**
 * @defgroup INTC_Weakdef_Prototypes INTC weak function prototypes
 * @{
 */
__WEAKDEF void HardFault_IrqHandler(void)
{
}
__WEAKDEF void MemManage_IrqHandler(void)
{
}
__WEAKDEF void BusFault_IrqHandler(void)
{
}
__WEAKDEF void UsageFault_IrqHandler(void)
{
}
__WEAKDEF void SVC_IrqHandler(void)
{
}
__WEAKDEF void DebugMon_IrqHandler(void)
{
}
__WEAKDEF void PendSV_IrqHandler(void)
{
}
__WEAKDEF void SysTick_IrqHandler(void)
{
}
__WEAKDEF void ExtInt00_SWInt08_IrqHandler(void)
{
}
__WEAKDEF void ExtInt01_SWInt09_IrqHandler(void)
{
}
__WEAKDEF void ExtInt02_SWInt10_IrqHandler(void)
{
}
__WEAKDEF void ExtInt03_SWInt11_IrqHandler(void)
{
}
#if (BSP_OFF == BSP_INT_KEY_ENABLE)
__WEAKDEF void ExtInt04_SWInt12_IrqHandler(void)
{
}
__WEAKDEF void ExtInt05_SWInt13_IrqHandler(void)
{
}
__WEAKDEF void ExtInt07_SWInt15_IrqHandler(void)
{
}
#endif
__WEAKDEF void ExtInt06_SWInt14_IrqHandler(void)
{
}
__WEAKDEF void DMA_TC0_IrqHandler(void)
{
}
__WEAKDEF void DMA_TC1_IrqHandler(void)
{
}
__WEAKDEF void DMA_TC2_IrqHandler(void)
{
}
__WEAKDEF void DMA_TC3_IrqHandler(void)
{
}
__WEAKDEF void DMA_BTC0_IrqHandler(void)
{
}
__WEAKDEF void DMA_BTC1_IrqHandler(void)
{
}
__WEAKDEF void DMA_BTC2_IrqHandler(void)
{
}
__WEAKDEF void DMA_BTC3_IrqHandler(void)
{
}
__WEAKDEF void DMA_Error_IrqHandler(void)
{
}
__WEAKDEF void EFM_ProgramEraseError_IrqHandler(void)
{
}
__WEAKDEF void EFM_ColError_IrqHandler(void)
{
}
__WEAKDEF void EFM_OpEnd_IrqHandler(void)
{
}
__WEAKDEF void DCU_IrqHandler(void)
{
}
__WEAKDEF void TMR0_1_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR0_1_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR0_2_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR0_2_CmpB_IrqHandler(void)
{
}
__WEAKDEF void CLK_XtalStop_IrqHandler(void)
{
}
__WEAKDEF void SWDT_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRB_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRB_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRB_Cmp_IrqHandler(void)
{
}
__WEAKDEF void USART1_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART1_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART1_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART1_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART2_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART2_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART2_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART2_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART3_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART3_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART3_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART3_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART4_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART4_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART4_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART4_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void SPI_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void SPI_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI_Idle_IrqHandler(void)
{
}
__WEAKDEF void SPI_Error_IrqHandler(void)
{
}
__WEAKDEF void TMR4_GCmpUH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_GCmpUL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_GCmpVH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_GCmpVL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_GCmpWH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_GCmpWL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_ReloadU_IrqHandler(void)
{
}
__WEAKDEF void TMR4_ReloadV_IrqHandler(void)
{
}
__WEAKDEF void TMR4_ReloadW_IrqHandler(void)
{
}
__WEAKDEF void EMB_IrqHandler(void)
{
}
__WEAKDEF void CMP1_IrqHandler(void)
{
}
__WEAKDEF void CMP2_IrqHandler(void)
{
}
__WEAKDEF void CMP3_IrqHandler(void)
{
}
__WEAKDEF void I2C_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_Error_IrqHandler(void)
{
}
__WEAKDEF void USART1_WKUP_IrqHandler(void)
{
}
__WEAKDEF void PWC_LVD1_IrqHandler(void)
{
}
__WEAKDEF void PWC_LVD2_IrqHandler(void)
{
}
__WEAKDEF void FCM_Error_IrqHandler(void)
{
}
__WEAKDEF void FCM_End_IrqHandler(void)
{
}
__WEAKDEF void FCM_Ovf_IrqHandler(void)
{
}
__WEAKDEF void WDT_IrqHandler(void)
{
}
__WEAKDEF void CTC_IrqHandler(void)
{
}
__WEAKDEF void ADC_SeqA_IrqHandler(void)
{
}
__WEAKDEF void ADC_SeqB_IrqHandler(void)
{
}
__WEAKDEF void ADC_ChCmp_IrqHandler(void)
{
}
__WEAKDEF void ADC_SeqCmp_IrqHandler(void)
{
}

/**
 * @}
 */

#endif /* DDL_INTERRUPTS_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
