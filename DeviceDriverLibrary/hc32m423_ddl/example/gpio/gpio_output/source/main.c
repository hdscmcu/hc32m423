/**
 *******************************************************************************
 * @file  gpio/gpio_output/source/main.c
 * @brief Main program of GPIO for the Device Driver Library.
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
 * @addtogroup GPIO_OUTPUT
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define LED_R_PORT      (GPIO_PORT_A)
#define LED_G_PORT      (GPIO_PORT_A)
#define LED_B_PORT      (GPIO_PORT_1)

#define LED_R_PIN       (GPIO_PIN_4)
#define LED_G_PIN       (GPIO_PIN_5)
#define LED_B_PIN       (GPIO_PIN_0)

#define LED_R_ON()      (GPIO_ResetPins(LED_R_PORT, LED_R_PIN))
#define LED_G_ON()      (GPIO_ResetPins(LED_G_PORT, LED_G_PIN))
#define LED_B_ON()      (GPIO_ResetPins(LED_B_PORT, LED_B_PIN))

#define LED_R_OFF()     (GPIO_SetPins(LED_R_PORT, LED_R_PIN))
#define LED_G_OFF()     (GPIO_SetPins(LED_G_PORT, LED_G_PIN))
#define LED_B_OFF()     (GPIO_SetPins(LED_B_PORT, LED_B_PIN))

#define LED_R_TOGGLE()  (GPIO_TogglePins(LED_R_PORT, LED_R_PIN))
#define LED_G_TOGGLE()  (GPIO_TogglePins(LED_G_PORT, LED_G_PIN))
#define LED_B_TOGGLE()  (GPIO_TogglePins(LED_B_PORT, LED_B_PIN))
#define LED_RGB_TOGGLE()                                                        \
                        {LED_R_TOGGLE();LED_G_TOGGLE();LED_B_TOGGLE();}

#define LED_RGB_ON()    {LED_R_ON();LED_G_ON();LED_B_ON();}
#define LED_RGB_OFF()   {LED_R_OFF();LED_G_OFF();LED_B_OFF();}

#define DLY_MS  (500UL)

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
//    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Unlock all EFM registers */
//    EFM_Unlock();
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
//    EFM_Lock();
}

/**
 * @brief  Main function of GPIO project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_gpio_init_t stcGpioInit;

    Peripheral_WE();

    GPIO_StructInit(&stcGpioInit);

    /* RGB LED initialize */
    GPIO_StructInit(&stcGpioInit);
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);
    GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
    GPIO_Init(LED_B_PORT, LED_B_PIN, &stcGpioInit);

    Peripheral_WP();

    /* "Turn off" LED before set to output */
    LED_RGB_OFF();

    /* Output enable */
    GPIO_OE(LED_R_PORT, LED_R_PIN, Enable);
    GPIO_OE(LED_G_PORT, LED_G_PIN, Enable);
    GPIO_OE(LED_B_PORT, LED_B_PIN, Enable);

    for(;;)
    {
        /* LED Red */
        LED_R_ON();
        DDL_DelayMS(DLY_MS);
        LED_R_OFF();
        DDL_DelayMS(DLY_MS);

        /* LED Green */
        LED_G_ON();
        DDL_DelayMS(DLY_MS);
        LED_G_OFF();
        DDL_DelayMS(DLY_MS);

        /* LED Blue */
        LED_B_ON();
        DDL_DelayMS(DLY_MS);
        LED_B_OFF();
        DDL_DelayMS(DLY_MS);

        /* LED Red/Green/Bule */
        LED_RGB_ON();
        DDL_DelayMS(DLY_MS);
        LED_RGB_OFF();
        DDL_DelayMS(DLY_MS);

        /* De-init port if necessary */
        //GPIO_DeInit();
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
