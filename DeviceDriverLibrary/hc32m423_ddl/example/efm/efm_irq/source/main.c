/**
 *******************************************************************************
 * @file  efm/efm_irq/source/main.c
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
 * @addtogroup EFM_Irq
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define EFM_IRQn                (EFM_PEERR_IRQn)
#define EFM_WIN_START_ADDR      (EFM_ADRR_SECT100)
#define EFM_WIN_END_ADDR        (EFM_ADRR_SECT102)
#define EFM_TEST_DATA           (0x5A5A5A5AUL)

#define SW1_PORT                (GPIO_PORT_0)
#define SW1_PIN                 (GPIO_PIN_2)
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void IRQ_Config(void);
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
 * @brief  Main function of EFM irq project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_efm_init_t stcEfmInit;
    uint32_t u32Addr = EFM_WIN_START_ADDR;

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();
    /* Led Init */
    BSP_LED_Init();
    /* Turn on LED_G */
    BSP_LED_On(LED_GREEN);
    /*Configure IRQ handler && NVIC*/
    IRQ_Config();
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
    /* Set windows protect address. */
    EFM_SetWindowProtectAddr(EFM_WIN_START_ADDR, EFM_WIN_END_ADDR);
    /* Enable program & erase err interrupt. */
    EFM_IntCmd(EFM_INT_PEERR, Enable);
    /* Erase sector 100. */
    (void)EFM_SectorErase(EFM_ADRR_SECT100);
    /* Program between windows address. */
    (void)EFM_Program32(u32Addr,EFM_TEST_DATA);
    /* SW1 */
    while(Pin_Reset != GPIO_ReadInputPins(SW1_PORT, SW1_PIN))
    {
        ;
    }
    /* Program out of windows address. */
    u32Addr = EFM_WIN_START_ADDR - 4UL;
    (void)EFM_Program32(u32Addr,EFM_TEST_DATA);
    /* MCU Peripheral registers write protected. */
    Peripheral_WP();
    for (;;)
    {
        ;
    }
}

/**
 * @brief  EFM Program/Erase Error IRQ callback
 * @param  None
 * @retval None
 */
void EFM_ProgramEraseError_IrqHandler(void)
{
    /* Turn off LED_G */
    BSP_LED_Off(LED_GREEN);
    /* Turn on LED_R */
    BSP_LED_On(LED_RED);
    /* Clear Flag */
    EFM_ClearStatus(EFM_FLAG_PEPRTERR);
}

/**
 * @brief  Configure IRQ handler && NVIC.
 * @param  None
 * @retval None
 */
static void IRQ_Config(void)
{
    stc_irq_signin_config_t stcIrqRegCfg;

    /* Register IRQ handler && configure NVIC. */
    stcIrqRegCfg.enIRQn = EFM_IRQn;
    NVIC_ClearPendingIRQ(stcIrqRegCfg.enIRQn);
    NVIC_SetPriority(stcIrqRegCfg.enIRQn, DDL_IRQ_PRI15);
    NVIC_EnableIRQ(stcIrqRegCfg.enIRQn);
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
