/**
 *******************************************************************************
 * @file  icg/wdt_reset_hw_startup/source/main.c
 * @brief Main program of ICG WDT Reset for the Device Driver Library.
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
 * @addtogroup ICG_WDT_Reset
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* WDT count period definition */
#define WDT_COUNT_PERIOD                        (65536UL)

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
 * @brief  Main function of ICG WDT Reset.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /**
     ***************************************************************************
     @brief Modify hc32m423_icg.h file of define
     @verbatim
     #define ICG7_RB_WDT_AUTST                  ICG_WDT_RST_START
     #define ICG7_RB_WDT_ITS                    ICG_WDT_EXP_TYPE_RST
     #define ICG7_RB_WDT_PERI                   ICG_WDT_CNT_PERIOD65536
     #define ICG7_RB_WDT_CKS                    ICG_WDT_CLK_DIV1024
     #define ICG7_RB_WDT_WDPT                   ICG_WDT_RANGE_0TO25PCT
     #define ICG7_RB_WDT_SLTPOFF                ICG_WDT_LPM_CNT_STOP
     @endverbatim
     ***************************************************************************
     */
    uint32_t u32CmpVal;
    uint16_t u16ResetSrc = 0U;

    /* Peripheral registers write unprotected */
    Peripheral_WE();
    /* Configure BSP */
    BSP_CLK_Init();
    BSP_LED_Init();
    BSP_KEY_Init(BSP_KEY_MD_EXTINT);
    /* Configure UART */
    (void)DDL_PrintfInit();
    /* Get RMU information */
    if (Set == RMU_GetStatus(RMU_RST_WDT))
    {
        u16ResetSrc = RMU_RST_WDT;
        BSP_LED_On(LED_RED);
    }
    RMU_ClearStatus();
    /* Count period=65536,range=0%-25% */
    u32CmpVal = WDT_COUNT_PERIOD / 4U;
    /* Peripheral registers write protected */
    Peripheral_WP();

    for (;;)
    {
        if (Set == BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_EXTINT))
        {
            u32CmpVal = WDT_COUNT_PERIOD / 2U;
        }

        if (WDT_GetCountValue() < u32CmpVal)
        {
            WDT_Feed();
            /* Wait for the count value to update */
            DDL_DelayMS(10UL);
            if (0U == u16ResetSrc)
            {
                BSP_LED_Toggle(LED_GREEN);
            }
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
