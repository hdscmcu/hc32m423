/**
 *******************************************************************************
 * @file  cmp/cmp_window/source/main.c
 * @brief Main program of CMP for the Device Driver Library.
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
 * @addtogroup CMP_Window
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CMP_TEST_UNIT2                  (CM_CMP2)
#define CMP_TEST_UNIT3                  (CM_CMP3)

/* Define port and pin for CMP */
/* VCOUT2*/
#define CMP_VCOUT2_PORT                 (GPIO_PORT_2)
#define CMP_VCOUT2_PIN                  (GPIO_PIN_3)
/* IVCMP2_2 */
#define IVCMP2_2_PORT                   (GPIO_PORT_4)
#define IVCMP2_2_PIN                    (GPIO_PIN_7)
/* IREF1 */
#define IVREF1_PORT                     (GPIO_PORT_1)
#define IVREF1_PIN                      (GPIO_PIN_1)
/* IREF2 */
#define IVREF2_PORT                     (GPIO_PORT_1)
#define IVREF2_PIN                      (GPIO_PIN_0)

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
    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1|PWC_UNLOCK_CODE_2);
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
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1|PWC_UNLOCK_CODE_2);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  Main function of cmp_window project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_cmp_init_t stcCmpInit;
    /* Register write unprotected for some required peripherals. */
    Peripheral_WE();
    /* System clock Init */
    BSP_CLK_Init();

    /* Port function configuration */
    GPIO_SetFunc(CMP_VCOUT2_PORT, CMP_VCOUT2_PIN, GPIO_FUNC_1_VCOUT);
    GPIO_SetFunc(IVCMP2_2_PORT, IVCMP2_2_PIN, GPIO_FUNC_1_ANA);
    GPIO_SetFunc(IVREF1_PORT, IVREF1_PIN, GPIO_FUNC_1_ANA);
    GPIO_SetFunc(IVREF2_PORT, IVREF2_PIN, GPIO_FUNC_1_ANA);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(CLK_FCG_CMP, Enable);

    /* Clear structure */
    (void)CMP_StructInit(&stcCmpInit);
    /* De-initialize CMP unit */
    CMP_DeInit(CMP_TEST_UNIT2);
    CMP_DeInit(CMP_TEST_UNIT3);

    /* Configuration for normal compare function */
    stcCmpInit.u8WinVoltageLow = CMP_REF_VOLT_IVREF1;     /* P11 */
    stcCmpInit.u8WinVoltageHigh = CMP_REF_VOLT_IVREF2;    /* P10 */

    stcCmpInit.u8OutDetectEdges = CMP_DETECT_EDGE_BOTH;
    stcCmpInit.u8OutFilter = CMP_OUT_FILTER_CLK_DIV32;
    stcCmpInit.u8OutPolarity = CMP_OUT_POLARITY_NORMAL;
    (void)CMP_WindowModeInit(&stcCmpInit);

    /* Enable VCOUT if need */
    CMP_VCOUTCmd(CMP_TEST_UNIT2, Enable);

    /* Enable CMP output */
    CMP_OutputCmd(CMP_TEST_UNIT2, Enable);
    CMP_OutputCmd(CMP_TEST_UNIT3, Enable);

    /* Register write protected */
    Peripheral_WP();

    /* Configuration finished */
    for(;;)
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
