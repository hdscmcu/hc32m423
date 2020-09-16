/**
 *******************************************************************************
 * @file  efm/efm_base/source/main.c
 * @brief Main program of EFM for the Device Driver Library.
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
 * @addtogroup EFM_Base
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define EFM_TEST_DATA_16BIT      (0x95A1U)
#define EFM_TEST_DATA_32BIT      (0x5A5A5A5AUL)
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void Peripheral_WE(void);
static void Peripheral_WP(void);

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
    /* Lock CLK, PWC, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    //PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
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
    /* Lock CLK, PWC, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    //PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    //EFM_Lock();
}
/**
 * @brief  Main function of EFM base project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_efm_init_t stcEfmInit;
    uint32_t u32Addr = EFM_ADRR_SECT80;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();
    /* Led Init */
    BSP_LED_Init();
    /* Turn on LED_G */
    BSP_LED_On(LED_GREEN);
    /* Enable EFM. */
    EFM_Cmd(Enable);
    /* EFM default config. */
    (void)EFM_StructInit(&stcEfmInit);
    (void)EFM_Init(&stcEfmInit);
    /* Wait flash ready. */
    while(Set != EFM_GetStatus(EFM_FLAG_RDY))
    {
        ;
    }

    /* Sector80 remove write protection (0x0000A000 - 0x0000A200)*/
    EFM_SetWindowProtectAddr(EFM_ADRR_SECT80, EFM_ADRR_SECT81);
    /* Erase sector 80. */
    (void)EFM_SectorErase(EFM_ADRR_SECT80);

    /**********Single program mode**********/
    /* program word */
    if (Ok != EFM_Program32(u32Addr, EFM_TEST_DATA_32BIT))
    {
        BSP_LED_Off(LED_GREEN);
    }
    u32Addr += 4UL;
    /* Program half word */
    if (Ok != EFM_Program16(u32Addr, EFM_TEST_DATA_16BIT))
    {
        BSP_LED_Off(LED_GREEN);
    }
    u32Addr += 4UL;
    /*******Program and read back mode********/
    /* Program word */
    if (Ok != EFM_ProgramReadBack32(u32Addr, EFM_TEST_DATA_32BIT))
    {
        BSP_LED_Off(LED_GREEN);
    }
    u32Addr += 4UL;
    /* Program half word */
    if(Ok != EFM_ProgramReadBack16(u32Addr, EFM_TEST_DATA_16BIT))
    {
        BSP_LED_Off(LED_GREEN);
    }
    /* MCU Peripheral registers write protected. */
    Peripheral_WP();

    for (;;)
    {
        ;
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
