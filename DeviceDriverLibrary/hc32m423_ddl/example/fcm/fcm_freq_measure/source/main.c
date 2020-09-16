/**
 *******************************************************************************
 * @file  fcm/fcm_freq_measure/source/main.c
 * @brief FCM main program example for the Device Driver Library.
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
 * @addtogroup FCM
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define REF_FREQ            (XTAL_VALUE)
#define REF_DIV             (1024U)
#define REF_DIV_LCLK        (8192U)
#define TAR_FREQ            (MRC_VALUE)
#define TAR_DIV             (1U)
#define TAR_DIV_PLLP        (32U)

#define FCM_SWDTLRC_ON      (0UL)
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
static char const *TargetClock;
static uint8_t u8FcmStatFinish = 0U;

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
    PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
    /* Lock all EFM registers */
    EFM_Lock();
}

/**
 * @brief  FCM frequency error IRQ callback
 * @param  None
 * @retval None
 */
void FCM_Error_IrqHandler(void)
{
    (void)printf ("Error\n");
    FCM_Cmd(Disable);
    FCM_ClearStatus(FCM_FLAG_ERR);
    u8FcmStatFinish = 1U;
}

/**
 * @brief  FCM measure counter overflow IRQ callback
 * @param  None
 * @retval None
 */
void FCM_Ovf_IrqHandler(void)
{
    (void)printf ("Overflow\n");
    FCM_Cmd(Disable);
    FCM_ClearStatus(FCM_FLAG_OVF);
    u8FcmStatFinish = 1U;
}

/**
 * @brief  FCM measure end IRQ callback
 * @param  None
 * @retval None
 */
void FCM_End_IrqHandler(void)
{
    uint16_t u16FcmCnt = FCM_GetCountValue();

    FCM_Cmd(Disable);
    if (FCM_TARGET_CLK_PLLP == READ_REG32_BIT(CM_FCM->MCCR, ( FCM_MCCR_MCKS)))
    {
        (void)printf ("%s freq. is %ld KHz\n" , TargetClock, ((((REF_FREQ /1000UL) * u16FcmCnt) / REF_DIV)*TAR_DIV_PLLP));
    }
    else if(FCM_TARGET_CLK_LRC == READ_REG32_BIT(CM_FCM->MCCR, ( FCM_MCCR_MCKS)))
    {
        (void)printf ("%s freq. is %ld KHz\n" , TargetClock, ((((REF_FREQ /1000UL) * u16FcmCnt) / REF_DIV_LCLK)*TAR_DIV));
    }
    else if(FCM_TARGET_CLK_SWDTLRC == READ_REG32_BIT(CM_FCM->MCCR, ( FCM_MCCR_MCKS)))
    {
        (void)printf ("%s freq. is %ld KHz\n" , TargetClock, ((((REF_FREQ /1000UL) * u16FcmCnt) / REF_DIV_LCLK)*TAR_DIV));
    }
    else
    {
        (void)printf ("%s freq. is %ld KHz\n" , TargetClock, ((((REF_FREQ /1000UL) * u16FcmCnt) / REF_DIV)*TAR_DIV));
    }
    FCM_ClearStatus(FCM_FLAG_END);
    u8FcmStatFinish = 1U;
}

/**
 * @brief  FCM frequency error interrupt init
 * @param  None
 * @retval None
 */
static void FcmErrorIntInit(void)
{
    /* NVIC config */
    NVIC_ClearPendingIRQ(FCM_FERRI_IRQn);
    NVIC_SetPriority(FCM_FERRI_IRQn,DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(FCM_FERRI_IRQn);

}

/**
 * @brief  FCM measure end interrupt init
 * @param  None
 * @retval None
 */
static void FcmEndIntInit(void)
{
    /* NVIC config */
    NVIC_ClearPendingIRQ(FCM_MENDI_IRQn);
    NVIC_SetPriority(FCM_MENDI_IRQn,DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(FCM_MENDI_IRQn);
}

/**
 * @brief  FCM counter overflow interrupt init
 * @param  None
 * @retval None
 */
static void FcmOvfIntInit(void)
{
    /* NVIC config */
    NVIC_ClearPendingIRQ(FCM_COVFI_IRQn);
    NVIC_SetPriority(FCM_COVFI_IRQn,DDL_IRQ_PRI_DEFAULT);
    NVIC_EnableIRQ(FCM_COVFI_IRQn);
}

/**
 * @brief  FCM init
 * @param  [in] u32TraClk Target clock type selection.
 *   @arg  FCM_TARGET_CLK_XTAL
 *   @arg  FCM_TARGET_CLK_HRC
 *   @arg  FCM_TARGET_CLK_LRC
 *   @arg  FCM_TARGET_CLK_SWDTLRC
 *   @arg  FCM_TARGET_CLK_PCLK1
 *   @arg  FCM_TARGET_CLK_MRC
 *   @arg  FCM_TARGET_CLK_PLLP
 * @param  [in] u32TarClkFreq Target clock frequency.
 * @retval None
 */
static void TargetClockFcmInit(uint32_t u32TraClk, uint32_t u32TarClkFreq)
{
    stc_fcm_init_t stcFcmInit;

    (void)FCM_StructInit(&stcFcmInit);
    stcFcmInit.u32RefClock     = FCM_REF_CLK_XTAL;
    stcFcmInit.u32RefClockEdge = FCM_REF_CLK_RISING;
    stcFcmInit.u32TargetClock  = u32TraClk;
    stcFcmInit.u32ExceptionType = FCM_EXP_TYPE_INT;
    if(FCM_TARGET_CLK_PLLP == u32TraClk)
    {
        stcFcmInit.u32RefClockDiv  = FCM_REF_CLK_DIV1024;
        stcFcmInit.u32TargetClockDiv  = FCM_TARGET_CLK_DIV32;
        /* idea count value = (tar_freq/tar_div)/(ref_freq/ref_div) */
        stcFcmInit.u16LowerLimit = (uint16_t)((((u32TarClkFreq/TAR_DIV_PLLP)/(REF_FREQ/REF_DIV))* 97UL)/100UL);
        stcFcmInit.u16UpperLimit = (uint16_t)((((u32TarClkFreq/TAR_DIV_PLLP)/(REF_FREQ/REF_DIV))* 103UL)/100UL);
    }
    else if((FCM_TARGET_CLK_LRC == u32TraClk) || (FCM_TARGET_CLK_SWDTLRC == u32TraClk))
    {
        stcFcmInit.u32RefClockDiv  = FCM_REF_CLK_DIV8192;
        stcFcmInit.u32TargetClockDiv  = FCM_TARGET_CLK_DIV1;
        /* idea count value = (tar_freq/tar_div)/(ref_freq/ref_div) */
        stcFcmInit.u16LowerLimit = (uint16_t)((((u32TarClkFreq/TAR_DIV)/(REF_FREQ/REF_DIV_LCLK))* 97UL)/100UL);
        stcFcmInit.u16UpperLimit = (uint16_t)((((u32TarClkFreq/TAR_DIV)/(REF_FREQ/REF_DIV_LCLK))* 103UL)/100UL);

    }
    else
    {
        stcFcmInit.u32RefClockDiv  = FCM_REF_CLK_DIV1024;
        stcFcmInit.u32TargetClockDiv  = FCM_TARGET_CLK_DIV1;
        /* idea count value = (tar_freq/tar_div)/(ref_freq/ref_div) */
        stcFcmInit.u16LowerLimit = (uint16_t)((((u32TarClkFreq/TAR_DIV)/(REF_FREQ/REF_DIV))* 97UL)/100UL);
        stcFcmInit.u16UpperLimit = (uint16_t)((((u32TarClkFreq/TAR_DIV)/(REF_FREQ/REF_DIV))* 103UL)/100UL);
    }

    (void)FCM_Init(&stcFcmInit);
    FCM_IntCmd(FCM_INT_ERR | FCM_INT_END | FCM_INT_OVF, Enable);
}

/**
 * @brief  FCM reference clock init
 * @param  None
 * @retval en_result_t
 */
static en_result_t RefClockInit(void)
{
    stc_clock_xtal_init_t stcXtalInit;

    (void)CLK_XtalStructInit(&stcXtalInit);

    stcXtalInit.u8XtalState   = CLK_XTAL_ON;
    stcXtalInit.u8XtalMode    = CLK_XTAL_MD_OSC;
    stcXtalInit.u8XtalDrv     = CLK_XTAL_DRV_HIGH;
    stcXtalInit.u8XtalSupSpeedDrv  = CLK_XTAL_SUPSPEEDDRV_ON;
    stcXtalInit.u8XtalStb     = CLK_XTALSTB_2POW8;
    return CLK_XtalInit(&stcXtalInit);
}

/**
 * @brief  FCM target clock init, including HRC, LRC, RTCLRC, PLLH, PLLA,
 *         XTAL, XTAL32
 * @param  None
 * @retval None
 */
static void TargetClockInit(void)
{
    stc_clock_pll_init_t stcPLLInit;

    if(Ok != CLK_HrcCmd(Enable))
    {
        /* Hrc command failed */
        BSP_LED_On(LED_RED);
    }
    if(Ok != CLK_MrcCmd(Enable))
    {
        /* Mrc command failed */
        BSP_LED_On(LED_RED);
    }
    if(Ok != CLK_LrcCmd(Enable))
    {
        /* Lrc command failed */
        BSP_LED_On(LED_RED);
    }

    /* HCLK  Max 80MHz */
    /* PCLK1, PCLK4 Max 80MHz */
    CLK_ClockDiv(CLK_CATE_ALL, (CLK_PCLK1_DIV1 | CLK_PCLK4_DIV1 | CLK_HCLK_DIV1));

    /* PLL config */
    (void)CLK_PLLStructInit(&stcPLLInit);
    /* VCO = 8/2*40 = 160MHz*/
    stcPLLInit.u8PLLState = CLK_PLL_ON;
    stcPLLInit.PLLCFGR = 0UL;
    stcPLLInit.PLLCFGR_f.PLLM = 2UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLN = 40UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLP = 2UL - 1UL;
    stcPLLInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_XTAL;
    (void)CLK_PLLInit(&stcPLLInit);
}

/**
 * @brief  Wait Key SW1 press
 * @param  None
 * @retval None
 */
static void WaitKeyPress(void)
{
    while(Set != BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_GPIO))
    {
        DDL_DelayMS(10UL);
        SWDT_Feed();
    }
    while(Reset != BSP_KEY_GetStatus(BSP_KEY_1, BSP_KEY_MD_GPIO))
    {
        DDL_DelayMS(10UL);
        SWDT_Feed();
    }
}

/**
 * @brief  Main function of FCM project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Register write unprotected for some required peripherals. */
    Peripheral_WE();

    BSP_KEY_Init(BSP_KEY_MD_GPIO);

    CLK_FcgPeriphClockCmd(CLK_FCG_FCM, Enable);

    TargetClockInit();
    if(Ok != RefClockInit())
    {
        /* Reference clock intial failed */
        BSP_LED_On(LED_RED);
    }
    FcmErrorIntInit();
    FcmEndIntInit();
    FcmOvfIntInit();

    (void)DDL_PrintfInit();

    /* Register write protected for some required peripherals. */
    Peripheral_WP();

    (void)printf("XTAL=8MHz divided by 1024 is used as the reference clock for this demo.\n");


    for(;;)
    {
        /* HRC */
        WaitKeyPress();
        TargetClock = "HRC";
        TargetClockFcmInit(FCM_TARGET_CLK_HRC, HRC_VALUE);
        FCM_Cmd(Enable);
        while(0U == u8FcmStatFinish)
        {
            ;
        }
        u8FcmStatFinish = 0U;

        /* LRC */
        WaitKeyPress();
        (void)printf("XTAL=8MHz divided by 8192 is used as the reference clock for this clock.\n");
        TargetClock = "LRC";
        TargetClockFcmInit(FCM_TARGET_CLK_LRC, LRC_VALUE);
        FCM_Cmd(Enable);
        while(0U == u8FcmStatFinish)
        {
            ;
        }
        u8FcmStatFinish = 0U;
#if (FCM_SWDTLRC_ON)
        /* SWDTLRC */
        WaitKeyPress();
        printf("XTAL=8MHz divided by 8192 is used as the reference clock for this clock.\n");
        TargetClock = "SWDTLRC";
        TargetClockFcmInit(FCM_TARGET_CLK_SWDTLRC, SWDTLRC_VALUE);
        FCM_Cmd(Enable);
        while(0U == u8FcmStatFinish)
        {
            ;
        }
        u8FcmStatFinish = 0U;
#endif
        /* PCLK1 */
        WaitKeyPress();
        TargetClock = "PCLK1(SYSCLK=8MHz)";
        TargetClockFcmInit(FCM_TARGET_CLK_PCLK1, 8UL*1000UL*1000UL);
        FCM_Cmd(Enable);
        while(0U == u8FcmStatFinish)
        {
            ;
        }
        u8FcmStatFinish = 0U;

        /* MRC */
        WaitKeyPress();
        TargetClock = "MRC";
        TargetClockFcmInit(FCM_TARGET_CLK_MRC, MRC_VALUE);
        FCM_Cmd(Enable);
        while(0U == u8FcmStatFinish)
        {
            ;
        }
        u8FcmStatFinish = 0U;

        /* PLL */
        WaitKeyPress();
        TargetClock = "PLLP(VCO=160MHz div2)";
        TargetClockFcmInit(FCM_TARGET_CLK_PLLP, 80UL*1000UL*1000UL);
        FCM_Cmd(Enable);
        while(0U == u8FcmStatFinish)
        {
            ;
        }
        u8FcmStatFinish = 0U;
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
