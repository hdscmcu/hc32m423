/**
 *******************************************************************************
 * @file  system_hc32m423.c
 * @brief This file provides two functions and one global variable to be called
 *        from  user application
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
#include "hc32_common.h"

/**
 * @addtogroup CMSIS
 * @{
 */

/**
 * @addtogroup HC32M423_System
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('define')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define EFM_HRCCFGR_HRCFREQS_012       (EFM_HRCCFGR_HRCFREQS_0 | EFM_HRCCFGR_HRCFREQS_1 | EFM_HRCCFGR_HRCFREQS_2)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/**
 * @addtogroup HC32M423_System_Global_Variable
 * @{
 */

/*!< System clock frequency (Core clock) */
__NO_INIT uint32_t SystemCoreClock;
/*!< High speed RC frequency (HCR clock) */
__NO_INIT uint32_t HRC_VALUE;
/*!< High speed RC frequency table */
const uint32_t au32HrcFreqTable[8] = {HRC_64MHz_VALUE,
                                     HRC_32MHz_VALUE,
                                     HRC_16MHz_VALUE,
                                     HRC_8MHz_VALUE,
                                     HRC_4MHz_VALUE,
                                     HRC_2MHz_VALUE,
                                     HRC_2MHz_VALUE,
                                     HRC_2MHz_VALUE};

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
 * @addtogroup HC32M423_System_Global_Functions
 * @{
 */

/**
 * @brief  Setup the microcontroller system. Initialize the System and update
 *         the SystemCoreClock variable.
 * @param  None
 * @retval None
 */
void SystemInit(void)
{
    /* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
#endif
    SystemCoreClockUpdate();
}

/**
 * @brief  Update HRC frequency according to Clock Register Values.
 * @param  None
 * @retval HRC frequency
 */
static uint32_t HrcUpdate(void)
{
    uint32_t u32Hrc_value;

    u32Hrc_value = au32HrcFreqTable[CM_EFM->HRCCFGR & EFM_HRCCFGR_HRCFREQS_012];

    if(EFM_HRCCFGR_HRCFREQS_3 == (CM_EFM->HRCCFGR & EFM_HRCCFGR_HRCFREQS_3))
    {
        u32Hrc_value = (u32Hrc_value*3U)/4U;
    }

    return u32Hrc_value;
}

/**
 * @brief  Update PLL frequency according to Clock Register Values.
 * @param  None
 * @retval PLL frequency
 */
static uint32_t PllUpdate(void)
{
    uint32_t pll_value;
    uint32_t pllsrc_value;
    uint32_t plln;
    uint32_t pllp;
    uint32_t pllm;
    uint32_t pll_hrc_in;

    if(0UL == bCM_EFM->HRCCFGR_b.HRCFREQS3)
    {
        pll_hrc_in = CLK_PLL_SRC_XTAL_FREQ_64M;
    }
    else
    {
        pll_hrc_in = CLK_PLL_SRC_XTAL_FREQ_48M;
    }

    /* PLL clock source frequency */
    pllsrc_value = (0UL == (CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLSRC)) ? XTAL_VALUE : pll_hrc_in;

    /* PLLPCLK = ((pllsrc / pllm) * plln) / pllp */
    plln = (CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLN) >> CMU_PLLCFGR_PLLN_POS;
    pllp = (CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLP) >> CMU_PLLCFGR_PLLP_POS;
    pllm = (CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLM);
    pll_value = (((pllsrc_value) / (pllm + 1UL)) * (plln + 1UL)) / (pllp + 1UL);

    return pll_value;
}

/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 * @param  None
 * @retval None
 */
void SystemCoreClockUpdate(void)
{
    uint8_t u8SysClkSrc;
    uint32_t u32SysClk = 0UL;
    uint32_t u32SysClkDiv;

    /* Updata HRC Value */
    HRC_VALUE = HrcUpdate();

    u8SysClkSrc = CM_CMU->CKSWR & CMU_CKSWR_CKSW;
    switch(u8SysClkSrc)
    {
        case 0x00U:  /* use internal high speed RC */
            u32SysClk = HRC_VALUE;
            break;
        case 0x01U:  /* use internal middle speed RC */
            u32SysClk = MRC_VALUE;
            break;
        case 0x02U:  /* use internal low speed RC */
            u32SysClk = LRC_VALUE;
            break;
        case 0x03U:  /* use external high speed RC */
            u32SysClk = XTAL_VALUE;
            break;
        case 0x05U:  /* use PLL */
            u32SysClk = PllUpdate();
            break;
        default:
            break;
    }

    u32SysClkDiv = ((CM_CMU->SCFGR & CMU_SCFGR_HCLKS) >> CMU_SCFGR_HCLKS_POS);
    SystemCoreClock = (u32SysClk << u32SysClkDiv);
}

#if (defined (__CC_ARM) || defined (__CLANG_ARM)) || \
    (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
extern int32_t $Super$$main(void);
/* re-define main function: keil */
int $Sub$$main(void)
{
    SystemCoreClockUpdate();
    $Super$$main();
    return 0;
}
#endif

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
 * EOF (not truncated)
 ******************************************************************************/
