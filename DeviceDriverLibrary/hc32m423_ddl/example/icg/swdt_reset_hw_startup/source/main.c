/**
 *******************************************************************************
 * @file  icg/swdt_reset_hw_startup/source/main.c
 * @brief Main program of ICG SWDT Reset for the Device Driver Library.
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
 * @addtogroup ICG_SWDT_Reset
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* SWDT count period definition */
#define SWDT_COUNT_PERIOD                       (16384U)

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
 * @brief  Main function of ICG SWDT Reset.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /**
     ***************************************************************************
     @brief Modify hc32m423_icg.h file of define
     @verbatim
     #define ICG0_RB_SWDT_AUTS                  ICG_SWDT_RST_START
     #define ICG0_RB_SWDT_ITS                   ICG_SWDT_EXP_TYPE_RST
     #define ICG0_RB_SWDT_PERI                  ICG_SWDT_CNT_PERIOD16384
     #define ICG0_RB_SWDT_CKS                   ICG_SWDT_CLK_DIV1
     #define ICG0_RB_SWDT_WDPT                  ICG_SWDT_RANGE_0TO25PCT
     #define ICG0_RB_SWDT_SLTPOFF               ICG_SWDT_LPM_CNT_STOP
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
    if (Set == RMU_GetStatus(RMU_RST_SWDT))
    {
        u16ResetSrc = RMU_RST_SWDT;
        BSP_LED_On(LED_RED);
    }
    RMU_ClearStatus();
    /* Count period=16384,range=0%-25% */
    u32CmpVal = SWDT_COUNT_PERIOD / 4U;
    /* Peripheral registers write protected */
    Peripheral_WP();

    for (;;)
    {
        if (Set == BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_EXTINT))
        {
            u32CmpVal = SWDT_COUNT_PERIOD / 2U;
        }

        if (SWDT_GetCountValue() < u32CmpVal)
        {
            SWDT_Feed();
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
