/**
 *******************************************************************************
 * @file  efm/efm_sequence_program/source/main.c
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
 * @addtogroup EFM_Sequence_Program
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

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
    //GPIO_Unlock();
    /* Lock CLK, PWC registers, @ref PWC_REG_Write_Unlock_Code for details */
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
    //GPIO_Lock();
    /* Lock CLK, PWC, LVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    //PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    EFM_Lock();
}
/**
 * @brief  Main function of EFM sequence program project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_efm_init_t stcEfmInit;
    const uint16_t au16TestBuf[30U] = {0x1234U,0x2345U,0x3456U,0x4567U,0x5678U,\
                                       0x6789U,0x789AU,0x89ABU,0x9ABCU,0xABCDU,\
                                       0xBCDEU,0xCDEFU,0x0123U,0x1100U,0x2233U,\
                                       0x4455U,0x6677U,0x8899U,0x1112U,0x2223U,\
                                       0x3334U,0x4445U,0x5556U,0x6667U,0x7778U,\
                                       0x8889U,0x9990U,0x0001U,0xAAABU,0xBBBCU};
    const uint32_t au32TestBuf[30U] = {0x12345678UL,0x23456789UL,0x3456789AUL,\
                                       0x456789ABUL,0x56789ABCUL,0x6789ABCDUL,\
                                       0x789ABCDEUL,0x89ABCDEFUL,0x11222211UL,\
                                       0x22333322UL,0x33444433UL,0x44555544UL,\
                                       0x55666655UL,0x66777766UL,0x77888877UL,\
                                       0x88999988UL,0x99AAAA99UL,0xAABBBBAAUL,\
                                       0xBBCCCCBBUL,0xCCDDDDCCUL,0xDDEEEEDDUL,\
                                       0xEEFFFFEEUL,0x09876543UL,0x98765432UL,\
                                       0x87654321UL,0xAB234DCAUL,0x9ABC456CUL,\
                                       0x78C3B42AUL,0x9127AC31UL,0x89BCC531UL};

    /* MCU Peripheral registers write unprotected */
    Peripheral_WE();
    /* Clock initialize  HCLK = 80MHZ */
    BSP_CLK_Init();
    /* Enable flash. */
    EFM_Cmd(Enable);
    /* EFM default config. */
    (void)EFM_StructInit(&stcEfmInit);
    stcEfmInit.u32BusStatus = EFM_BUS_RELEASE;
    stcEfmInit.u32WaitCycle = EFM_WAIT_CYCLE3;
    (void)EFM_Init(&stcEfmInit);

    /* Wait flash ready. */
    while(Set != EFM_GetStatus(EFM_FLAG_RDY))
    {
        ;
    }
    /* Erase sector 15 140. */
    (void)EFM_SectorErase(EFM_ADRR_SECT20);
    (void)EFM_SectorErase(EFM_ADRR_SECT140);

    /* Sequence program(word). */
    (void)EFM_SeqProgram32(EFM_ADRR_SECT20, (sizeof(au32TestBuf))/4UL, au32TestBuf);

    /* Sequence program(half word). */
    (void)EFM_SeqProgram16(EFM_ADRR_SECT140, (sizeof(au16TestBuf))/2UL, au16TestBuf);

    /* Chip Erase */
    (void)EFM_ChipErase();

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
