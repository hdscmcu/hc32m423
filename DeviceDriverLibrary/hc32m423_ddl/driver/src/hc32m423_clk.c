/**
 *******************************************************************************
 * @file  hc32m423_clk.c
 * @brief This file provides firmware functions to manage the Clock(CLK).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-15       CDT             First version
   2020-11-06       CDT             Fix bug for CLK_SetSysclkSrc() and CLK_ClockDiv()
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
#include "hc32m423_clk.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CLK CLK
 * @brief Clock Driver Library
 * @{
 */

#if (DDL_CLK_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CLK_Local_Macros CLK Local Macros
 * @{
 */

#define CLK_XTAL_TIMEOUT                (0x20000UL)
#define CLK_HRC_TIMEOUT                 (0x1000UL)
#define CLK_MRC_TIMEOUT                 (0x1000UL)
#define CLK_LRC_TIMEOUT                 (0x1000UL)
#define CLK_PLL_TIMEOUT                 (0x80000UL)

#define CLK_PLLP_DIV_MIN                (2UL)
#define CLK_PLLP_DIV_MAX                (4UL)

#define CLK_PLLN_MUL_MIN                (10UL)
#define CLK_PLLN_MUL_MAX                (60UL)

#define CLK_PLLM_DIV_MIN                (1UL)
#define CLK_PLLM_DIV_MAX                (8UL)

#define CLK_PLL_VCO_IN_MIN              (4UL*1000UL*1000UL)
#define CLK_PLL_VCO_IN_MAX              (125UL*100UL*1000UL)

#define CLK_PLL_VCO_OUT_MIN             (120UL*1000UL*1000UL)
#define CLK_PLL_VCO_OUT_MAX             (240UL*1000UL*1000UL)

#define CLK_PLL_FREQ_MIN                (30UL*1000UL*1000UL)
#define CLK_PLL_FREQ_MAX                (80UL*1000UL*1000UL)

#define CLK_PLLP_DEFAULT                (0x01UL)
#define CLK_PLLN_DEFAULT                (0x09UL)
#define CLK_PLLM_DEFAULT                (0x00UL)

#define CLK_FCG_DEFAULT                 (0xFFFFFFFFUL)

/* Stable waiting time while switching system clock.   */
/* @note Approx. about 1us based on 80M frequency.     */
#define CLK_SYSCLK_SW_STABLE            (80000000UL/1000000UL)

#define CLK_FCG_CTL_MASK               (CLK_FCG_ADC    |  \
                                        CLK_FCG_CTC    |  \
                                        CLK_FCG_CMP    |  \
                                        CLK_FCG_AOS    |  \
                                        CLK_FCG_DMA    |  \
                                        CLK_FCG_CRC    |  \
                                        CLK_FCG_TMRA_1 |  \
                                        CLK_FCG_TMRA_2 |  \
                                        CLK_FCG_TMRA_3 |  \
                                        CLK_FCG_TMRA_4 |  \
                                        CLK_FCG_TMR0_1 |  \
                                        CLK_FCG_TMR0_2 |  \
                                        CLK_FCG_TMR4   |  \
                                        CLK_FCG_TMRB   |  \
                                        CLK_FCG_EMB    |  \
                                        CLK_FCG_FCM    |  \
                                        CLK_FCG_DCU    |  \
                                        CLK_FCG_UART1  |  \
                                        CLK_FCG_UART2  |  \
                                        CLK_FCG_UART3  |  \
                                        CLK_FCG_UART4  |  \
                                        CLK_FCG_IIC    |  \
                                        CLK_FCG_SPI)

/**
 * @defgroup CLK_Check_Parameters_Validity CLK Check Parameters Validity
 * @{
 */

/*  Check CLK register lock status. */
#define IS_CLK_UNLOCKED()       ((CM_PWC->FPRC & PWC_FPRC_CKRWE) == PWC_FPRC_CKRWE)

/* Parameter valid check for Xtal state */
#define IS_CLK_XTAL_STAT(stat)                                                 \
(   ((stat) == CLK_XTAL_OFF)                        ||                         \
    ((stat) == CLK_XTAL_ON))

/* Parameter valid check for Xtal mode */
#define IS_CLK_XTAL_MD(mode)                                                   \
(   ((mode) == CLK_XTAL_MD_OSC)                     ||                         \
    ((mode) == CLK_XTAL_MD_EXT_CLK))

/* Parameter valid check for Xtal super speed driver state */
#define IS_CLK_XTAL_SUPSPEEDDRV_STAT(stat)                                     \
(   ((stat) == CLK_XTAL_SUPSPEEDDRV_ON)             ||                         \
    ((stat) == CLK_XTAL_SUPSPEEDDRV_OFF))

/* Parameter valid check for Xtal driver ability mode */
#define IS_CLK_XTAL_DRV_MD(mode)                                               \
(   ((mode) == CLK_XTAL_DRV_HIGH)                   ||                         \
    ((mode) == CLK_XTAL_DRV_MID)                    ||                         \
    ((mode) == CLK_XTAL_DRV_LOW)                    ||                         \
    ((mode) == CLK_XTAL_DRV_ULOW))

/* Parameter valid check for Xtal stable time selection */
#define IS_CLK_XTALSTB_SEL(sel)                                                \
(   ((sel) == CLK_XTALSTB_2POW8)                    ||                         \
    ((sel) == CLK_XTALSTB_2POW9 )                   ||                         \
    ((sel) == CLK_XTALSTB_2POW10)                   ||                         \
    ((sel) == CLK_XTALSTB_2POW11)                   ||                         \
    ((sel) == CLK_XTALSTB_2POW13)                   ||                         \
    ((sel) == CLK_XTALSTB_2POW15)                   ||                         \
    ((sel) == CLK_XTALSTB_2POW16)                   ||                         \
    ((sel) == CLK_XTALSTB_2POW17))

/* Parameter valid check for CLK stable flag. */
#define IS_CLK_STB_FLAG(flag)                                                  \
(   ((flag) != 0x00U)                               &&                         \
    (((flag) | CLK_STB_FLAG_MASK) == CLK_STB_FLAG_MASK))

/* Parameter validity check for PLL M divide */
#define IS_CLK_PLLM_DIV(m)                                                     \
(   (CLK_PLLM_DIV_MIN <= (m))                       &&                         \
    (CLK_PLLM_DIV_MAX >= (m)))

/* Parameter validity check for PLL N multi- */
#define IS_CLK_PLLN_MUL(n)                                                     \
(   (CLK_PLLN_MUL_MIN <= (n))                       &&                         \
    (CLK_PLLN_MUL_MAX >= (n)))

/* Parameter validity check for PLL P divide */
#define IS_CLK_PLLP_DIV(p)                                                     \
(   (CLK_PLLP_DIV_MIN <= (p))                       &&                         \
    (CLK_PLLP_DIV_MAX >= (p)))

/* Parameter validity check for PLL input source */
#define IS_CLK_PLL_SRC(src)                                                    \
(   ((src) == CLK_PLLSRC_XTAL)                      ||                         \
    ((src) == CLK_PLLSRC_HRC))

/* Parameter validity check for PLL_input freq./PLLM(vco_in) */
#define IS_CLK_PLL_VCO_IN(vco_in)                                              \
(   (CLK_PLL_VCO_IN_MIN <= (vco_in))                &&                         \
    (CLK_PLL_VCO_IN_MAX >= (vco_in)))

/* Parameter validity check for PLL vco_in*PLLN(vco_out) */
#define IS_CLK_PLL_VCO_OUT(vco_out)                                            \
(   (CLK_PLL_VCO_OUT_MIN <= (vco_out))              &&                         \
    (CLK_PLL_VCO_OUT_MAX >= (vco_out)))

/* Parameter validity check for PLL frequency range */
#define IS_CLK_PLL_FREQ(freq)                                                  \
(   (CLK_PLL_FREQ_MIN <= (freq))                    &&                         \
    (CLK_PLL_FREQ_MAX >= (freq)))

/* Parameter valid check for PLL state */
#define IS_CLK_PLL_STAT(stat)                                                  \
(   ((stat) == CLK_PLL_OFF)                         ||                         \
    ((stat) == CLK_PLL_ON))

/* Parameter valid check for system clock source */
#define IS_CLK_SYSCLK_SRC(src)                                                 \
(   ((src) == CLK_SYSCLK_SRC_HRC)                   ||                         \
    ((src) == CLK_SYSCLK_SRC_MRC)                   ||                         \
    ((src) == CLK_SYSCLK_SRC_LRC)                   ||                         \
    ((src) == CLK_SYSCLK_SRC_XTAL)                  ||                         \
    ((src) == CLK_SYSCLK_SRC_PLL))

/* Parameter valid check for clock category */
#define IS_CLK_CATE(cate)       (((cate) & CLK_CATE_ALL) != (uint8_t)(0x00U))

/* Parameter valid check for Hclk divider */
#define IS_CLK_HCLK_DIV(div)                                                   \
(   ((div) == CLK_HCLK_DIV1)                        ||                         \
    ((div) == CLK_HCLK_DIV2)                        ||                         \
    ((div) == CLK_HCLK_DIV4)                        ||                         \
    ((div) == CLK_HCLK_DIV8)                        ||                         \
    ((div) == CLK_HCLK_DIV16)                       ||                         \
    ((div) == CLK_HCLK_DIV32)                       ||                         \
    ((div) == CLK_HCLK_DIV64))

/* Parameter valid check for Pclk1 divider */
#define IS_CLK_PCLK1_DIV(div)                                                  \
(   ((div) == CLK_PCLK1_DIV1)                       ||                         \
    ((div) == CLK_PCLK1_DIV2)                       ||                         \
    ((div) == CLK_PCLK1_DIV4)                       ||                         \
    ((div) == CLK_PCLK1_DIV8)                       ||                         \
    ((div) == CLK_PCLK1_DIV16)                      ||                         \
    ((div) == CLK_PCLK1_DIV32)                      ||                         \
    ((div) == CLK_PCLK1_DIV64))

/* Parameter valid check for Pclk4 divider */
#define IS_CLK_PCLK4_DIV(div)                                                  \
(   ((div) == CLK_PCLK4_DIV1)                       ||                         \
    ((div) == CLK_PCLK4_DIV2)                       ||                         \
    ((div) == CLK_PCLK4_DIV4)                       ||                         \
    ((div) == CLK_PCLK4_DIV8)                       ||                         \
    ((div) == CLK_PCLK4_DIV16)                      ||                         \
    ((div) == CLK_PCLK4_DIV32)                      ||                         \
    ((div) == CLK_PCLK4_DIV64))

/* Parameter valid check for TPIU clock divider */
#define IS_CLK_TPIU_CLK_DIV(div)                                               \
(   ((div) == CLK_TPIU_CLK_DIV1)                    ||                         \
    ((div) == CLK_TPIU_CLK_DIV2)                    ||                         \
    ((div) == CLK_TPIU_CLK_DIV4))

/* Parameter valid check for CLK MCO clock source. */
#define IS_CLK_MCO_SRC(src)                                                    \
(   ((src) == CLK_MCO_SRC_HRC)                      ||                         \
    ((src) == CLK_MCO_SRC_MRC)                      ||                         \
    ((src) == CLK_MCO_SRC_LRC)                      ||                         \
    ((src) == CLK_MCO_SRC_XTAL)                     ||                         \
    ((src) == CLK_MCO_SRC_PLLP)                     ||                         \
    ((src) == CLK_MCO_SRC_HCLK)                     ||                         \
    ((src) == CLK_MCO_SRC_SWDT))

/* Parameter valid check for CLK MCO clock Prescaler. */
#define IS_CLK_MCO_DIV(div)                                                    \
(   ((div) == CLK_MCO_DIV1)                         ||                         \
    ((div) == CLK_MCO_DIV2)                         ||                         \
    ((div) == CLK_MCO_DIV4)                         ||                         \
    ((div) == CLK_MCO_DIV8)                         ||                         \
    ((div) == CLK_MCO_DIV16)                        ||                         \
    ((div) == CLK_MCO_DIV32)                        ||                         \
    ((div) == CLK_MCO_DIV64)                        ||                         \
    ((div) == CLK_MCO_DIV128))

/* Parameter valid check for Hrc frequency */
#define IS_CLK_HRC_FREQ_SEL(sel)                                               \
 (  ((sel) == CLK_HRC_64M)                          ||                         \
    ((sel) == CLK_HRC_32M)                          ||                         \
    ((sel) == CLK_HRC_16M)                          ||                         \
    ((sel) == CLK_HRC_8M)                           ||                         \
    ((sel) == CLK_HRC_4M)                           ||                         \
    ((sel) == CLK_HRC_2M)                           ||                         \
    ((sel) == CLK_HRC_48M)                          ||                         \
    ((sel) == CLK_HRC_24M)                          ||                         \
    ((sel) == CLK_HRC_12M)                          ||                         \
    ((sel) == CLK_HRC_6M)                           ||                         \
    ((sel) == CLK_HRC_3M)                           ||                         \
    ((sel) == CLK_HRC_1P5M))

/* Parameter valid check for ADC clock divider */
#define IS_ADCCLK_DIV(div)                                                     \
(   ((div) == CLK_ADCCLK_PCLK4_DIV1)                ||                         \
    ((div) == CLK_ADCCLK_PCLK4_DIV2)                ||                         \
    ((div) == CLK_ADCCLK_PCLK4_DIV3)                ||                         \
    ((div) == CLK_ADCCLK_PCLK4_DIV4)                ||                         \
    ((div) == CLK_ADCCLK_PCLK4_DIV5)                ||                         \
    ((div) == CLK_ADCCLK_PCLK4_DIV6)                ||                         \
    ((div) == CLK_ADCCLK_PCLK4_DIV7)                ||                         \
    ((div) == CLK_ADCCLK_PCLK4_DIV8))

/* Parameter valid check for clock fcg command bit */
#define IS_CLK_FCG_CTL_FLAG(flag)                                              \
(   ((flag) != 0x00U)                               &&                         \
    (((flag) | CLK_FCG_CTL_MASK) == CLK_FCG_CTL_MASK))

/* Parameter valid check for XTALSTD state */
#define IS_CLK_XTALSTD_STAT(stat)                                              \
(   ((stat) == CLK_XTALSTD_OFF)                     ||                         \
    ((stat) == CLK_XTALSTD_ON))

/* Parameter valid check for XTALSTD exception type */
#define IS_CLK_XTALSTD_EXP_TYPE(type)                                          \
(   ((type) == CLK_XTALSTD_EXP_TYPE_RST)            ||                         \
    ((type) == CLK_XTALSTD_EXP_TYPE_INT))

/* Parameter valid check for XTALSTD interrupt state */
#define IS_CLK_XTALSTD_INT_STAT(stat)                                          \
(   ((stat) == CLK_XTALSTD_INT_OFF)                 ||                         \
    ((stat) == CLK_XTALSTD_INT_ON))

/* Parameter valid check for XTALSTD reset state */
#define IS_CLK_XTALSTD_RST_STAT(stat)                                          \
(   ((stat) == CLK_XTALSTD_RST_OFF)                 ||                         \
    ((stat) == CLK_XTALSTD_RST_ON))

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
static uint32_t Get_TargetClockFreq(uint8_t u8Clock);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup CLK_Local_Functions CLK Local Functions
 * @{
 */
/**
 * @brief  Get target clock frequency.
 * @param  [in] u8Clock             Specifies the source of clock.
 *                                  @ref CLK_System_Clock_Src
 *         This parameter can be one of the following values:
 *   @arg  CLK_SYSCLK_SRC_HRC
 *   @arg  CLK_SYSCLK_SRC_XTAL
 *   @arg  CLK_SYSCLK_SRC_LRC
 *   @arg  CLK_SYSCLK_SRC_MRC
 *   @arg  CLK_SYSCLK_SRC_PLL
 * @retval uint32_t
 */
static uint32_t Get_TargetClockFreq(uint8_t u8Clock)
{
    uint32_t u32Freq;
    uint32_t plln;
    uint32_t pllp;
    uint32_t pllm;
    uint32_t pll_hrc_in;

    switch(u8Clock)
    {
        case CLK_SYSCLK_SRC_HRC:
            /* Hrc used as system clock. */
            u32Freq = HRC_VALUE;
            break;
        case CLK_SYSCLK_SRC_MRC:
            /* Mrc used as system clock. */
            u32Freq = MRC_VALUE;
            break;
        case CLK_SYSCLK_SRC_LRC:
            /* Lrc used as system clock. */
            u32Freq = LRC_VALUE;
            break;
        case CLK_SYSCLK_SRC_XTAL:
            /* Xtal used as system clock. */
            u32Freq = XTAL_VALUE;
            break;
        default:
            /* PLL is used as system clock. */
            pllp = (uint32_t)((CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLP) >> CMU_PLLCFGR_PLLP_POS);
            plln = (uint32_t)((CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLN) >> CMU_PLLCFGR_PLLN_POS);
            pllm = (uint32_t)((CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLM) >> CMU_PLLCFGR_PLLM_POS);

            /* fpll = ((pllin / pllm) * plln) / pllp */
            if (CLK_PLLSRC_XTAL == READ_REG32_BIT(CM_CMU->PLLCFGR, CMU_PLLCFGR_PLLSRC))
            {
                u32Freq = ((XTAL_VALUE/(pllm + 1UL))*(plln + 1UL))/(pllp + 1UL);
            }
            else
            {
                if(0UL == bCM_EFM->HRCCFGR_b.HRCFREQS3)
                {
                    pll_hrc_in = CLK_PLL_SRC_XTAL_FREQ_64M;
                }
                else
                {
                    pll_hrc_in = CLK_PLL_SRC_XTAL_FREQ_48M;
                }
                u32Freq = ((pll_hrc_in/(pllm + 1UL))*(plln + 1UL))/(pllp + 1UL);
            }
            break;
    }
    return u32Freq;
}
/**
 * @}
 */

/**
 * @defgroup CLK_Global_Functions CLK Global Functions
 * @{
 */
/**
  * @brief  Resets the CLK clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *            - Lrc Mrc ON and Mrc used as system clock source
  *            - Hrc OFF
  *            - Xtal OFF
  *            - SysClk divider set to 1.
  *            - MCO OFF
  *            - PLL OFF
  * @param  None
  * @retval None
  */
void CLK_DeInit(void)
{
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Reset peripheral clock */
    WRITE_REG32(CM_CMU->FCG, 0xFFFFFFFFUL);

    /* Enable Mrc */
    WRITE_REG8(CM_CMU->MRCCR, 0x00U);
    while (timeout <= CLK_MRC_TIMEOUT)
    {
        timeout++;
    }
    /* Reset the system clock source */
    WRITE_REG8(CM_CMU->CKSWR, 0x01U);

    /* Reset clock divider */
    WRITE_REG32(CM_CMU->SCFGR, 0x00000000UL);

    /* Reset MCO */
    WRITE_REG8(CM_CMU->MCOCFGR, 0x00U);

    /* Reset XTALSTD */
    WRITE_REG8(CM_CMU->XTALSTDCR, 0x00U);

    /* Reset PLL */
    WRITE_REG8(CM_CMU->PLLCR, 0x01U);

    /* Reset Lrc Hrc Xtal */
    WRITE_REG8(CM_CMU->LRCCR, 0x00U);
    WRITE_REG8(CM_CMU->HRCCR, 0x01U);
    WRITE_REG8(CM_CMU->XTALCR, 0x01U);

    /* Update system clock */
    SystemCoreClockUpdate();
}

/**
 * @brief  Init Xtal initial structure with default value.
 * @param  [in] pstcXtalInit        Specifies the Parameter of Xtal.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok: Initialize success
 *   @arg  ErrorInvalidParameter: NULL pointer
 */
en_result_t CLK_XtalStructInit(stc_clock_xtal_init_t* pstcXtalInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcXtalInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcXtalInit->u8XtalState = CLK_XTAL_OFF;
        pstcXtalInit->u8XtalMode = CLK_XTAL_MD_OSC;
        pstcXtalInit->u8XtalDrv = CLK_XTAL_DRV_HIGH;
        pstcXtalInit->u8XtalSupSpeedDrv = CLK_XTAL_SUPSPEEDDRV_ON;
        pstcXtalInit->u8XtalStb = CLK_XTALSTB_2POW8;
    }

    return enRet;
}

/**
 * @brief  Xtal initialize.
 * @param  [in] pstcXtalInit        Specifies the Xtal initial config.
 *   @arg  u8XtalState : The new state of the Xtal. @ref CLK_Xtal_Func_Switch
 *   @arg  u8XtalDrv   : The Xtal drive ability. @ref CLK_Xtal_Drv
 *   @arg  u8XtalSupSpeedDrv : The Xtal super speed drive on or off. @ref CLK_Xtal_SuperSpeed_Drv
 *   @arg  u8XtalMode  : The Xtal mode selection osc or extclk. @ref CLK_Xtal_Mode
 *   @arg  u8XtalStb   : The Xtal stable time selection. @ref CLK_Xtal_Stable_Time
 * @retval en_result_t
 *   @arg  Ok: Xtal initial successfully.
 *   @arg  ErrorTimeout: XTAL operate timeout.
 *   @arg  ErrorNotReady: Xtal is the system clock or as the PLL source clock,
 *                        CANNOT stop it.
 *   @arg  ErrorInvalidParameter: NULL pointer.
 * @note   DO NOT STOP Xtal while using it as system clock.
 */
en_result_t CLK_XtalInit(const stc_clock_xtal_init_t *pstcXtalInit)
{
    en_result_t enRet;

    if (pstcXtalInit == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameters check */
        DDL_ASSERT(IS_CLK_XTAL_STAT(pstcXtalInit->u8XtalState));
        DDL_ASSERT(IS_CLK_XTAL_MD(pstcXtalInit->u8XtalMode));
        DDL_ASSERT(IS_CLK_XTAL_DRV_MD(pstcXtalInit->u8XtalDrv));
        DDL_ASSERT(IS_CLK_XTAL_SUPSPEEDDRV_STAT(pstcXtalInit->u8XtalSupSpeedDrv));
        DDL_ASSERT(IS_CLK_XTALSTB_SEL(pstcXtalInit->u8XtalStb));
        DDL_ASSERT(IS_CLK_UNLOCKED());

        WRITE_REG8(CM_CMU->XTALSTBCR, pstcXtalInit->u8XtalStb);
        WRITE_REG8(CM_CMU->XTALCFGR, (pstcXtalInit->u8XtalSupSpeedDrv |     \
                                    pstcXtalInit->u8XtalDrv |               \
                                    pstcXtalInit->u8XtalMode));
        if(CLK_XTAL_ON == pstcXtalInit->u8XtalState)
        {
            enRet = CLK_XtalCmd(Enable);
        }
        else
        {
            enRet = CLK_XtalCmd(Disable);
        }
    }

    return enRet;
}

/**
 * @brief  Xtal function enable/disbale.
 * @param  [in] enNewState          Specifies the new state of Xtal.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *   @arg  Ok: Xtal operate successfully
 *   @arg  ErrorNotReady: Xtal is the system clock or as the PLL source clock,
 *                        CANNOT stop it.
 *   @arg  ErrorTimeout: Xtal operate timeout.
 * @note   DO NOT STOP Xtal while using it as system clock or as the PLL source clock.
 */
en_result_t CLK_XtalCmd(en_functional_state_t enNewState)
{

    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        if (CLK_SYSCLK_SRC_XTAL == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = ErrorNotReady;
        }
        /* Xtal as PLL clock source and PLL is working */
        else
        {
            if (0UL == READ_REG32(bCM_CMU->PLLCFGR_b.PLLSRC))
            {
               if (0UL == READ_REG32(bCM_CMU->PLLCR_b.PLLOFF))
               {
                    /* PLL is ON */
                    enRet = ErrorNotReady;
               }
               else
               {
                    WRITE_REG32(bCM_CMU->XTALCR_b.XTALSTP, CLK_XTAL_OFF);
               }
            }
            else
            {
                WRITE_REG32(bCM_CMU->XTALCR_b.XTALSTP, CLK_XTAL_OFF);
            }
        }
    }
    else
    {
        WRITE_REG32(bCM_CMU->XTALCR_b.XTALSTP, CLK_XTAL_ON);

        enRet = ErrorTimeout;
        while (timeout <= CLK_XTAL_TIMEOUT)
        {
            if (Set == CLK_GetStableStatus(CMU_OSCSTBSR_XTALSTBF))
            {
                enRet = Ok;
                break;
            }
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  PLL/Xtal/Hrc stable flag read.
 * @param  [in] u8StableFlag        Specifies the stable flag to be read. @ref CLK_STB_Flag
 *   @arg  CLK_STB_FLAG_HRCSTB
 *   @arg  CLK_STB_FLAG_XTALSTB
 *   @arg  CLK_STB_FLAG_PLLHSTB
 * @retval en_flag_status_t
 */
en_flag_status_t CLK_GetStableStatus(uint8_t u8StableFlag)
{
    DDL_ASSERT(IS_CLK_STB_FLAG(u8StableFlag));

    return ((0U != (READ_REG8_BIT(CM_CMU->OSCSTBSR, u8StableFlag)))? Set : Reset);
}

/**
 * @brief  Hrc function enable/disbale.
 * @param  [in] enNewState          Specifies the new state of Hrc.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *   @arg  Ok: Hrc operate successfully
 *   @arg  ErrorNotReady: Hrc is the system clock or as the PLL source clock,
 *                        CANNOT stop it.
 *   @arg  ErrorTimeout: Hrc operate timeout
 * @note   DO NOT STOP Hrc while using it as system clock or as the PLL source clock.
 */
en_result_t CLK_HrcCmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        if (CLK_SYSCLK_SRC_HRC == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = ErrorNotReady;
        }
        /* Hrc as PLL clock source and PLL is working */
        else
        {
            if (1UL == READ_REG32(bCM_CMU->PLLCFGR_b.PLLSRC))
            {
                if (0UL == READ_REG32(bCM_CMU->PLLCR_b.PLLOFF))
                {
                    enRet = ErrorNotReady;
                }
                else
                {
                    WRITE_REG32(bCM_CMU->HRCCR_b.HRCSTP, CLK_HRC_OFF);
                }
            }
            else
            {
                WRITE_REG32(bCM_CMU->HRCCR_b.HRCSTP, CLK_HRC_OFF);
            }
        }
    }
    else
    {
        WRITE_REG32(bCM_CMU->HRCCR_b.HRCSTP, CLK_HRC_ON);

        enRet = ErrorTimeout;
        while (timeout <= CLK_HRC_TIMEOUT)
        {
            if (Set == CLK_GetStableStatus(CMU_OSCSTBSR_HRCSTBF))
            {
                enRet = Ok;
                break;
            }
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  Mrc function enable/disbale.
 * @param  [in] enNewState          Specifies the new state of Mrc.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *   @arg  Ok: Mrc operate successfully
 *   @arg  ErrorNotReady: Mrc is the system clock, CANNOT stop it.
 * @note   DO NOT STOP Mrc while using it as system clock.
 */
en_result_t CLK_MrcCmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        if (CLK_SYSCLK_SRC_MRC == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = ErrorNotReady;
        }
        else
        {
            WRITE_REG32(bCM_CMU->MRCCR_b.MRCSTP, CLK_MRC_OFF);
        }
    }
    else
    {
        WRITE_REG32(bCM_CMU->MRCCR_b.MRCSTP, CLK_MRC_ON);

        while (timeout <= CLK_MRC_TIMEOUT)
        {
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  Lrc function enable/disbale.
 * @param  [in] enNewState          Specifies the new state of Lrc.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *   @arg  Ok: Lrc operate successfully
 *   @arg  ErrorNotReady: Lrc is the system clock, CANNOT stop it.
 * @note   DO NOT STOP Lrc while using it as system clock.
 */
en_result_t CLK_LrcCmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        if (CLK_SYSCLK_SRC_LRC == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = ErrorNotReady;
        }
        else
        {
            WRITE_REG32(bCM_CMU->LRCCR_b.LRCSTP, CLK_LRC_OFF);
        }
    }
    else
    {
        WRITE_REG32(bCM_CMU->LRCCR_b.LRCSTP, CLK_LRC_ON);

        while (timeout <= CLK_LRC_TIMEOUT)
        {
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  PLL function enable/disbale.
 * @param  [in] enNewState          Specifies the new state of PLL.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *   @arg  Ok: PLL operate successfully
 *   @arg  ErrorTimeout: PLL operate timeout
 * @note
 */
en_result_t CLK_PLLCmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        WRITE_REG32(bCM_CMU->PLLCR_b.PLLOFF, CLK_PLL_OFF);
    }
    else
    {
        WRITE_REG32(bCM_CMU->PLLCR_b.PLLOFF, CLK_PLL_ON);

        enRet = ErrorTimeout;
        while (timeout <= CLK_PLL_TIMEOUT)
        {
            if (Set == CLK_GetStableStatus(CMU_OSCSTBSR_PLLSTBF))
            {
                enRet = Ok;
                break;
            }
            timeout++;
        }
    }
    return enRet;
}

/**
 * @brief  Init PLL initial structure with default value.
 * @param  [in] pstcPLLInit         Specifies the Parameter of PLL.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok: Initialize success
 *   @arg  ErrorInvalidParameter: NULL pointer
 */
en_result_t CLK_PLLStructInit(stc_clock_pll_init_t* pstcPLLInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcPLLInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcPLLInit->PLLCFGR        = 0UL;
        pstcPLLInit->u8PLLState     = CLK_PLL_OFF;
        pstcPLLInit->PLLCFGR_f.PLLP = CLK_PLLP_DEFAULT;
        pstcPLLInit->PLLCFGR_f.PLLN = CLK_PLLN_DEFAULT;
        pstcPLLInit->PLLCFGR_f.PLLM = CLK_PLLM_DEFAULT;
        pstcPLLInit->PLLCFGR_f.PLLSRC = CLK_PLLSRC_XTAL;
    }
    return enRet;
}

/**
 * @brief  PLL Initialize.
 * @param  [in] pstcPLLInit         Specifies the structure of PLL initial config.
 *   @arg  u8PLLState : The new state of the PLL.
 *   @arg  PLLCFGR    : PLL config.
 * @retval en_result_t
 *   @arg  Ok: PLL initial successfully
 *   @arg  ErrorTimeout: PLL initial timeout
 *   @arg  ErrorInvalidParameter: NULL pointer
 * @note   The pll_input/PLLM (VCOIN) must between 4 ~ 12.5MHz.
 *         The VCOIN*PLLN (VCOOUT) is between 120 ~ 240MHz.
 *         The PLLA frequency (VCOOUT/PLLAP) is between 30 ~ 80MHz.
 */
en_result_t CLK_PLLInit(const stc_clock_pll_init_t *pstcPLLInit)
{
    en_result_t enRet;

#ifdef __DEBUG
    uint32_t u32VcoIn;
    uint32_t u32VcoOut;
    uint32_t u32PllHrcIn;
#endif

    if (NULL == pstcPLLInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
#ifdef __DEBUG
        DDL_ASSERT(IS_CLK_PLLM_DIV(pstcPLLInit->PLLCFGR_f.PLLM + 1UL));
        DDL_ASSERT(IS_CLK_PLLN_MUL(pstcPLLInit->PLLCFGR_f.PLLN + 1UL));
        DDL_ASSERT(IS_CLK_PLLP_DIV(pstcPLLInit->PLLCFGR_f.PLLP + 1UL));

        if(0UL == bCM_EFM->HRCCFGR_b.HRCFREQS3)
        {
            u32PllHrcIn = CLK_PLL_SRC_XTAL_FREQ_64M;
        }
        else
        {
            u32PllHrcIn = CLK_PLL_SRC_XTAL_FREQ_48M;
        }

        u32VcoIn = (((CLK_PLLSRC_XTAL == pstcPLLInit->PLLCFGR_f.PLLSRC) ?
                    XTAL_VALUE : u32PllHrcIn) / (pstcPLLInit->PLLCFGR_f.PLLM + 1UL));
        u32VcoOut = u32VcoIn * (pstcPLLInit->PLLCFGR_f.PLLN + 1UL);

        DDL_ASSERT(IS_CLK_PLL_VCO_IN(u32VcoIn));
        DDL_ASSERT(IS_CLK_PLL_VCO_OUT(u32VcoOut));
        DDL_ASSERT(IS_CLK_PLL_FREQ(u32VcoOut/(pstcPLLInit->PLLCFGR_f.PLLP + 1UL)));
#endif
        DDL_ASSERT(IS_CLK_PLL_STAT(pstcPLLInit->u8PLLState));
        DDL_ASSERT(IS_CLK_UNLOCKED());

        WRITE_REG32(CM_CMU->PLLCFGR, pstcPLLInit->PLLCFGR);

        if(CLK_PLL_ON == pstcPLLInit->u8PLLState)
        {
            enRet = CLK_PLLCmd(Enable);
        }
        else
        {
            enRet = CLK_PLLCmd(Disable);
        }
    }
    return enRet;
}

/**
 * @brief  Set the system clock source.
 * @param  [in] u8Src               Specifies the source of system clock.
 *                                  @ref CLK_System_Clock_Src
 *         This parameter can be one of the following values:
 *   @arg  CLK_SYSCLK_SRC_HRC  : select Hrc as system clock source
 *   @arg  CLK_SYSCLK_SRC_XTAL : select Xtal as system clock source
 *   @arg  CLK_SYSCLK_SRC_LRC  : select Lrc as system clock source
 *   @arg  CLK_SYSCLK_SRC_MRC  : select Mrc as system clock source
 *   @arg  CLK_SYSCLK_SRC_PLL  : select PLL as system clock source
 * @retval None
 */
void CLK_SetSysclkSrc(uint8_t u8Src)
{
    __IO uint32_t timeout = 0UL;
    /* backup fcg setting */
    const uint32_t fcg = READ_REG32(CM_CMU->FCG);
    uint8_t u8TmpFlag = 0U;

    DDL_ASSERT(IS_CLK_SYSCLK_SRC(u8Src));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Only current system clock source or target system clock source is PLL
    need to close fcg and open fcg during switch system clock source.
    We need to backup fcg before close them. */
    if ((CLK_SYSCLK_SRC_PLL == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW)) \
        || (CLK_SYSCLK_SRC_PLL == u8Src))
    {
        if(CLK_FCG_DEFAULT != READ_REG32(CM_CMU->FCG))
        {
            u8TmpFlag = 1U;
            /* Close fcg */
            WRITE_REG32(CM_CMU->FCG, CLK_FCG_DEFAULT);

            /* Wait stable after close fcg */
            do
            {
                timeout++;
            } while(timeout < CLK_SYSCLK_SW_STABLE);
        }
    }

    /* If SystemCore Clock >= 72MHz */
    if(Get_TargetClockFreq(u8Src) >= ((72UL*1000UL)*1000UL))
    {
        CLEAR_REG16_BIT(CM_PWC->PWRC, PWC_PWRC_DVS);
        /* Wait stable after open fcg */
        timeout = 0UL;
        do
        {
            timeout++;
        } while(timeout < CLK_SYSCLK_SW_STABLE);
    }

    /* Set system clock source */
    WRITE_REG8(CM_CMU->CKSWR, u8Src);

    if (1U == u8TmpFlag)
    {
        WRITE_REG32(CM_CMU->FCG, fcg);
        /* Wait stable after open fcg */
        timeout = 0UL;
        do
        {
            timeout++;
        } while(timeout < CLK_SYSCLK_SW_STABLE);
    }

    /* Update system clock */
    SystemCoreClockUpdate();
}

/**
 * @brief  Hclk/Pclk divide setting.
 * @param  [in] u8ClockCate         Specifies the clock to be divided. @ref CLK_CATE_Sel
 *   @arg  CLK_CATE_PCLK1: Select Pclk1 to be divided
 *   @arg  CLK_CATE_PCLK4: Select Pclk4 to be divided
 *   @arg  CLK_CATE_HCLK : Select Hclk  to be divided
 *   @arg  CLK_CATE_ALL : Select all to be divided
 * @param  [in] u32Div              Specifies the clock divide factor. @ref CLK_Hclk_Div
 *         @ref CLK_Pclk1_Div and @ref CLK_Pclk4_Div
 *   @arg  CLK_HCLK_DIV1 : Hclk no divide
 *   @arg  CLK_HCLK_DIV2 : Hclk divided by 2
 *   @arg  CLK_HCLK_DIV4 : Hclk divided by 4
 *   @arg  CLK_HCLK_DIV8 : Hclk divided by 8
 *   @arg  CLK_HCLK_DIV16: Hclk divided by 16
 *   @arg  CLK_HCLK_DIV32: Hclk divided by 32
 *   @arg  CLK_HCLK_DIV64: Hclk divided by 64
 *   @arg  CLK_PCLKx_DIV1 : PCLKx no divide
 *   @arg  CLK_PCLKx_DIV2 : PCLKx divided by 2
 *   @arg  CLK_PCLKx_DIV4 : PCLKx divided by 4
 *   @arg  CLK_PCLKx_DIV8 : PCLKx divided by 8
 *   @arg  CLK_PCLKx_DIV16: PCLKx divided by 16
 *   @arg  CLK_PCLKx_DIV32: PCLKx divided by 32
 *   @arg  CLK_PCLKx_DIV64: PCLKx divided by 64
 * @retval None
 * @note   'x' is 1 or 4 in CLK_PCLKx_DIVy
 */
void CLK_ClockDiv(uint8_t u8ClockCate, uint32_t u32Div)
{
    __IO uint32_t timeout = 0UL;
    /* backup fcg setting */
    const uint32_t fcg = READ_REG32(CM_CMU->FCG);
    uint8_t u8TmpFlag = 0U;

    DDL_ASSERT(IS_CLK_HCLK_DIV(u32Div & CMU_SCFGR_HCLKS));
    DDL_ASSERT(IS_CLK_PCLK1_DIV(u32Div & CMU_SCFGR_PCLK1S));
    DDL_ASSERT(IS_CLK_PCLK4_DIV(u32Div & CMU_SCFGR_PCLK4S));
    DDL_ASSERT(IS_CLK_CATE(u8ClockCate));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Only current system clock source or target system clock source is PLL
    need to close fcg and open fcg during switch system clock source.
    We need to backup fcg before close them. */
    if (CLK_SYSCLK_SRC_PLL == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW))
    {
        if(CLK_FCG_DEFAULT != READ_REG32(CM_CMU->FCG))
        {
            u8TmpFlag = 1U;

            /* Close fcg */
            WRITE_REG32(CM_CMU->FCG, CLK_FCG_DEFAULT);

            /* Wait stable after close fcg */
            do
            {
                timeout++;
            } while(timeout < CLK_SYSCLK_SW_STABLE);
        }
    }

    /* Pclk1 div */
    if (0U != (CLK_CATE_PCLK1 & u8ClockCate))
    {
        MODIFY_REG32(CM_CMU->SCFGR, CMU_SCFGR_PCLK1S, u32Div);
    }
    /* Pclk4 div */
    if (0U != (CLK_CATE_PCLK4 & u8ClockCate))
    {
        MODIFY_REG32(CM_CMU->SCFGR, CMU_SCFGR_PCLK4S, u32Div);
    }
    /* Hclk div */
    if (0U != (CLK_CATE_HCLK & u8ClockCate))
    {
        MODIFY_REG32(CM_CMU->SCFGR, CMU_SCFGR_HCLKS, u32Div);
    }

    if (1U == u8TmpFlag)
    {
        WRITE_REG32(CM_CMU->FCG, fcg);

        /* Wait stable after open fcg */
        timeout = 0UL;
        do
        {
            timeout++;
        } while(timeout < CLK_SYSCLK_SW_STABLE);
    }
}

/**
 * @brief  Enable or disable the TPIU clock.
 * @param  [in] enNewState          Specifies the new state of the TPIU clock.
 *   @arg  Enable:  Enable clock output.
 *   @arg  Disable: Disable clock output.
 * @retval None
 */
void CLK_TpiuClockCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG32(bCM_CMU->TPIUCKCFGR_b.TPIUCKOE, enNewState);
}

/**
 * @brief  TPIU clock divider config.
 * @param  [in] u8TpiuDiv           Specifies the TPIU clock divide factor. @ref CLK_TPIU_Div
 *   @arg  CLK_TPIU_CLK_DIV1: TPIU clock no divide
 *   @arg  CLK_TPIU_CLK_DIV2: TPIU clock divide by 2
 *   @arg  CLK_TPIU_CLK_DIV4: TPIU clock divide by 4
 * @retval None
 */
void CLK_TpiuClockConfig(uint8_t u8TpiuDiv)
{
    DDL_ASSERT(IS_CLK_TPIU_CLK_DIV(u8TpiuDiv));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    MODIFY_REG8(CM_CMU->TPIUCKCFGR, CMU_TPIUCKCFGR_TPIUCKS, u8TpiuDiv);
}

/**
 * @brief  Selects the clock source to output on MCO pin.
 * @param  [in] u8MCOSrc            Specifies the clock source to output. @ref CLK_MCO_Clock_Src.
 * @param  [in] u8MCODiv            Specifies the MCOx prescaler. @ref CLK_MCO_Clock_Prescaler.
 * @retval None
 * @note   MCO pin should be configured in alternate function mode.
 */
void CLK_MCOConfig(uint8_t u8MCOSrc, uint8_t u8MCODiv)
{
    /* Check the parameters. */
    DDL_ASSERT(IS_CLK_MCO_SRC(u8MCOSrc));
    DDL_ASSERT(IS_CLK_MCO_DIV(u8MCODiv));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Configure the MCO and Enable MCO */
    MODIFY_REG8(CM_CMU->MCOCFGR, (CMU_MCOCFGR_MCO1SEL | CMU_MCOCFGR_MCO1DIV),\
                (u8MCODiv | u8MCOSrc));
}

/**
 * @brief  Enable or Disable MCO.
 * @param  [in] enNewState          Specifies the new state of the clock output.
 *         This parameter can be one of the following values:
 *    @arg Enable:  Enable clock output.
 *    @arg Disable: Disable clock output.
 * @retval None
 */
void CLK_MCOCmd(en_functional_state_t enNewState)
{
    /* Parameters check */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Enable or disable clock output. */
    WRITE_REG32(bCM_CMU->MCOCFGR_b.MCO1EN, enNewState);
}

/**
 * @brief  Get bus clock frequency.
 * @param  [out] pstcClockFreq      Specifies the pointer to get bus frequency.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok: Initialize success
 *   @arg  ErrorInvalidParameter: NULL pointer
 */
en_result_t CLK_GetClockFreq(stc_clock_freq_t *pstcClockFreq)
{
    en_result_t enRet = Ok;

    if (NULL == pstcClockFreq)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Get system clock. */
        pstcClockFreq->u32SysclkFreq = Get_TargetClockFreq(READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW));

        /* Get hclk. */
        pstcClockFreq->u32HclkFreq = pstcClockFreq->u32SysclkFreq >> \
                    (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_HCLKS) >> CMU_SCFGR_HCLKS_POS);

        /* Get pclk1. */
        pstcClockFreq->u32Pclk1Freq = pstcClockFreq->u32SysclkFreq >> \
                    (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS);

        /* Get pclk4. */
        pstcClockFreq->u32Pclk4Freq = pstcClockFreq->u32SysclkFreq >> \
                    (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK4S) >> CMU_SCFGR_PCLK4S_POS);
    }
    return enRet;
}

/**
 * @brief  Get PLL clock frequency.
 * @param  [out] pstcPLLClockFreq specifies the pointer to get PLL frequency.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok: Initialize success
 *   @arg  ErrorInvalidParameter: NULL pointer
 */
en_result_t CLK_GetPLLClockFreq(stc_pll_clock_freq_t *pstcPLLClockFreq)
{
    en_result_t enRet = Ok;
    uint32_t plln;
    uint32_t pllm;
    uint32_t pllp;
    uint32_t pllin;

    if (NULL == pstcPLLClockFreq)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pllp = (uint32_t)((CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLP) >> CMU_PLLCFGR_PLLP_POS);
        plln = (uint32_t)((CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLN) >> CMU_PLLCFGR_PLLN_POS);
        pllm = (uint32_t)((CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLM) >> CMU_PLLCFGR_PLLM_POS);

        if (CLK_PLLSRC_XTAL == READ_REG32_BIT(CM_CMU->PLLCFGR, CMU_PLLCFGR_PLLSRC))
        {
            pllin = XTAL_VALUE;
        }
        else
        {
            if(0UL == bCM_EFM->HRCCFGR_b.HRCFREQS3)
            {
                pllin = CLK_PLL_SRC_XTAL_FREQ_64M;
            }
            else
            {
                pllin = CLK_PLL_SRC_XTAL_FREQ_48M;
            }
        }
        pstcPLLClockFreq->pllvcin = (pllin/(pllm + 1UL));
        pstcPLLClockFreq->pllvco = ((pllin/(pllm + 1UL))*(plln + 1UL));
        pstcPLLClockFreq->pllp = ((pllin/(pllm + 1UL))*(plln + 1UL))/(pllp + 1UL);
    }
    return enRet;
}

/**
 * @brief  configurate the frequency of Hrc.
 * @param  [in] u8HrcFreq           Specifies the frequency of Hrc. @ref CLK_Hrc_Freq_Sel
 *         This parameter can be one of the following values
 *   @arg  CLK_HRC_64M
 *   @arg  CLK_HRC_32M
 *   @arg  CLK_HRC_16M
 *   @arg  CLK_HRC_8M
 *   @arg  CLK_HRC_4M
 *   @arg  CLK_HRC_2M
 *   @arg  CLK_HRC_48M
 *   @arg  CLK_HRC_24M
 *   @arg  CLK_HRC_12M
 *   @arg  CLK_HRC_6M
 *   @arg  CLK_HRC_3M
 *   @arg  CLK_HRC_1P5M
 * @retval en_result_t
 *   @arg  Ok: Operate successfully
 *   @arg  Error: Can not Operate when Hrc is the source of PLL
 */
en_result_t CLK_HrcFreqConfig(uint8_t u8HrcFreq)
{
    en_result_t enRet = Ok;
    uint8_t temp;

    /* Parameters check */
    DDL_ASSERT(IS_CLK_HRC_FREQ_SEL(u8HrcFreq));
    DDL_ASSERT(IS_CLK_UNLOCKED());
    DDL_ASSERT(READ_REG32(CM_EFM->FAPRT) == 0x00000001UL);

    /* When the Hrc is used as PLL source clock in these case Hrc will not be changed */
    temp = READ_REG8_BIT(CM_CMU->PLLCR, CMU_PLLCR_PLLOFF);
    if((CLK_PLLSRC_HRC == READ_REG32_BIT(CM_CMU->PLLCFGR, CMU_PLLCFGR_PLLSRC)) && \
       (CLK_PLL_ON == temp))
    {
        enRet = Error;
    }
    else
    {
        /* Configure Hrc frequency */
        WRITE_REG8(CM_EFM->HRCCFGR, u8HrcFreq);
    }

    /* Wait Hrc stable, delay about 100uS */
    DDL_DelayUS(100UL);
    /* Update system clock */
    SystemCoreClockUpdate();

    return enRet;
}

/**
 * @brief  Select pll clock source.
 * @param  [in] u32PllSrc           The pll clock source. @ref CLK_PLL_Clock_Src
 * @retval None
 */
void CLK_SetPLLSrc(uint32_t u32PllSrc)
{
    /* Parameters check */
    DDL_ASSERT(IS_CLK_PLL_SRC(u32PllSrc));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG32(bCM_CMU->PLLCFGR_b.PLLSRC, u32PllSrc);
}

/**
 * @brief  Set the Pclk4 divider witch used as ADC clock.
 * @param  [in] u8ADCClkDiv         Specifies the divider of Pclk4. @ref CLK_ADCCLK_Div.
 * @retval None
 */
void CLK_SetADCClockDiv(uint8_t u8ADCClkDiv)
{
    /* Parameters check */
    DDL_ASSERT(IS_ADCCLK_DIV(u8ADCClkDiv));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Set system clock divider */
    WRITE_REG8(CM_CMU->ADCKSEL, u8ADCClkDiv);
}

/**
 * @brief  Enable or disable the fcg peripheral clock.
 * @note   After reset,the peripheral clock is disabled and the application
 *         software has to enable this clock before using it.
 * @param  [in] u32FcgPeriph        Specifies the peripheral in fcg. @ref CLK_FCG_Periph_Control.
 * @param  [in] enNewState          Specifies the new state of the clock output.
 *         This parameter can be one of the following values:
 *   @arg  Enable:  Enable clock output.
 *   @arg  Disable: Disable clock output.
 * @retval None
 */
void CLK_FcgPeriphClockCmd(uint32_t u32FcgPeriph, en_functional_state_t enNewState)
{
    /* Parameters check */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_FCG_CTL_FLAG(u32FcgPeriph));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(CM_CMU->FCG, u32FcgPeriph);
    }
    else
    {
        SET_REG32_BIT(CM_CMU->FCG, u32FcgPeriph);
    }
}

/**
 * @brief  Init XtalStd initial structure with default value.
 * @param  [in] pstcXtalStdInit     Specifies the Parameter of XTALSTD.
 * @retval An en_result_t enumeration value:
 *   @arg  Ok: Initialize success
 *   @arg  ErrorInvalidParameter: Invalid parameter
 */
en_result_t CLK_XtalStdStructInit(stc_clock_xtalstd_init_t* pstcXtalStdInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcXtalStdInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcXtalStdInit->u8XtalStdState = CLK_XTALSTD_OFF;
        pstcXtalStdInit->u8XtalStdExceptionType  = CLK_XTALSTD_EXP_TYPE_INT;
        pstcXtalStdInit->u8XtalStdInt   = CLK_XTALSTD_RST_OFF;
        pstcXtalStdInit->u8XtalStdRst   = CLK_XTALSTD_INT_OFF;
    }

    return enRet;
}

/**
 * @brief  Initialise the Xtal status detection.
 * @param  [in] pstcXtalStdInit     Specifies the Parameter of XTALSTD.
 *   @arg  u8XtalStdState: The new state of the XTALSTD. @ref CLK_XTALSTD_Switch
 *   @arg  u8XtalStdExceptionType:  The Xtal status detection occur interrupt or reset. @ref CLK_XTALSTD_Exception_type
 *   @arg  u8XtalStdInt:   The Xtal status detection interrupt on or off. @ref CLK_XTALSTD_Irq_Switch
 *   @arg  u8XtalStdRst:   The Xtal status detection reset on or off. @ref CLK_XTALSTD_Reset_Switch
 * @retval An en_result_t enumeration value:
 *   @arg  Ok: Initialize success
 *   @arg  ErrorInvalidParameter: Invalid parameter
 */
en_result_t CLK_XtalStdInit(const stc_clock_xtalstd_init_t* pstcXtalStdInit)
{
    en_result_t enRet = Ok;

    if (pstcXtalStdInit == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter valid check */
        DDL_ASSERT(IS_CLK_XTALSTD_STAT(pstcXtalStdInit->u8XtalStdState));
        DDL_ASSERT(IS_CLK_UNLOCKED());

        if(CLK_XTALSTD_OFF == pstcXtalStdInit->u8XtalStdState)
        {
            /* Disbale Xtal status detection */
            WRITE_REG32(bCM_CMU->XTALSTDCR_b.XTALSTDE, (uint32_t)CLK_XTALSTD_OFF);
        }
        else
        {
            /* Parameter valid check */
            DDL_ASSERT(IS_CLK_XTALSTD_EXP_TYPE(pstcXtalStdInit->u8XtalStdExceptionType));
            DDL_ASSERT(IS_CLK_XTALSTD_INT_STAT(pstcXtalStdInit->u8XtalStdInt));
            DDL_ASSERT(IS_CLK_XTALSTD_RST_STAT(pstcXtalStdInit->u8XtalStdRst));

            /* Configure and enable XTALSTD */
            WRITE_REG8(CM_CMU->XTALSTDCR, (pstcXtalStdInit->u8XtalStdState |   \
                                           pstcXtalStdInit->u8XtalStdExceptionType  |   \
                                           pstcXtalStdInit->u8XtalStdInt   |   \
                                           pstcXtalStdInit->u8XtalStdRst));
        }
    }

    return enRet;
}

/**
 * @brief  Clear the Xtal error flag.
 * @param  None
 * @retval None
 * @note   The system clock should not be Xtal before call this function.
 */
void CLK_ClearXtalStdStatus(void)
{
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if(1UL == READ_REG32(bCM_CMU->XTALSTDSR_b.XTALSTDF))
    {
        /* Clear the Xtal STD flag */
        WRITE_REG32(bCM_CMU->XTALSTDSR_b.XTALSTDF, 0UL);
    }
}

/**
 * @brief  Get the Xtal error flag.
 * @param  None
 * @retval en_flag_status_t
 */
en_flag_status_t CLK_GetXtalStdStatus(void)
{
    return ((0UL != READ_REG32(bCM_CMU->XTALSTDSR_b.XTALSTDF)) ? Set : Reset);
}

/**
 * @}
 */

#endif /* DDL_CLK_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
