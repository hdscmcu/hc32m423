/**
 *******************************************************************************
 * @file  hc32m423_gpio.c
 * @brief This file provides firmware functions to manage the General Purpose
 *        Input/Output(GPIO).
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
#include "hc32m423_gpio.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_GPIO GPIO
 * @brief GPIO Driver Library
 * @{
 */

#if (DDL_GPIO_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GPIO_Local_Macros GPIO Local Macros
 * @{
 */
/**
 * @defgroup GPIO_Registers_Reset_Value GPIO Registers Reset Value
 * @{
 */
#define GPIO_PSPCR_RST_VALUE                (0x001FU)
#define GPIO_PCCR_RST_VALUE                 (0x4000U)
#define GPIO_PINAER_RST_VALUE               (0x0000U)
/**
 * @}
 */

/**
 * @defgroup GPIO_Check_Parameters_Validity GPIO Check Parameters Validity
 * @{
 */
/* Parameter validity check for pin state. */
#define IS_GPIO_PIN_STAT(state)                                                 \
(   ((state) == PIN_STAT_RST)                   ||                              \
    ((state) == PIN_STAT_SET))

/* Parameter validity check for pin mode. */
#define IS_GPIO_DIR(dir)                                                        \
(   ((dir) == PIN_DIR_IN)                       ||                              \
    ((dir) == PIN_DIR_OUT))

/* Parameter validity check for pin output type. */
#define IS_GPIO_OUT_TYPE(type)                                                  \
(   ((type) == PIN_OUT_TYPE_CMOS)               ||                              \
    ((type) == PIN_OUT_TYPE_NMOS))

/* Parameter validity check for pin driver capacity. */
#define IS_GPIO_PIN_DRV(drv)                                                    \
(   ((drv) == PIN_NORMAL_DRV)                   ||                              \
    ((drv) == PIN_HIGH_DRV))

/* Parameter validity check for pin latch function. */
#define IS_GPIO_LATCH(latch)                                                    \
(   ((latch) == PIN_LATCH_OFF)                  ||                              \
    ((latch) == PIN_LATCH_ON))

/* Parameter validity check for internal pull-up resistor. */
#define IS_GPIO_PIN_PU(pu)                                                      \
(   ((pu) == PIN_PU_OFF)                        ||                              \
    ((pu) == PIN_PU_ON))

/* Parameter validity check for pin state invert. */
#define IS_GPIO_PIN_INVT(invert)                                                \
(   ((invert) == PIN_INVT_OFF)                  ||                              \
    ((invert) == PIN_INVT_ON))

/* Parameter validity check for pin input type. */
#define IS_GPIO_IN_TYPE(type)                                                   \
(   ((type) == PIN_IN_TYPE_SMT)                 ||                              \
    ((type) == PIN_IN_TYPE_CMOS))

/* Parameter validity check for external interrupt function. */
#define IS_GPIO_EXTINT(extint)                                                  \
(   ((extint) == PIN_EXTINT_OFF)                ||                              \
    ((extint) == PIN_EXTINT_ON))

/* Parameter validity check for pin number. */
#define IS_GPIO_PIN(pin)        ((pin) != 0x00U)

/* Parameter validity check for get pin index. */
#define IS_GET_GPIO_PIN(pin)                                                    \
(   ((pin) == GPIO_PIN_0)                       ||                              \
    ((pin) == GPIO_PIN_1)                       ||                              \
    ((pin) == GPIO_PIN_2)                       ||                              \
    ((pin) == GPIO_PIN_3)                       ||                              \
    ((pin) == GPIO_PIN_4)                       ||                              \
    ((pin) == GPIO_PIN_5)                       ||                              \
    ((pin) == GPIO_PIN_6)                       ||                              \
    ((pin) == GPIO_PIN_7))

/* Parameter validity check for port source. */
#define IS_GPIO_PORT(port)                                                      \
(   ((port) != 0x00U)                           &&                              \
    (((port) | GPIO_PORT_MASK) == GPIO_PORT_MASK))

/* Parameter validity check for port source. */
#define IS_GPIO_PORT_SRC(port)                                                  \
(   ((port) == GPIO_PORT_0)                     ||                              \
    ((port) == GPIO_PORT_1)                     ||                              \
    ((port) == GPIO_PORT_2)                     ||                              \
    ((port) == GPIO_PORT_3)                     ||                              \
    ((port) == GPIO_PORT_4)                     ||                              \
    ((port) == GPIO_PORT_5)                     ||                              \
    ((port) == GPIO_PORT_7)                     ||                              \
    ((port) == GPIO_PORT_9)                     ||                              \
    ((port) == GPIO_PORT_A)                     ||                              \
    ((port) == GPIO_PORT_B)                     ||                              \
    ((port) == GPIO_PORT_D)                     ||                              \
    ((port) == GPIO_PORT_E))

/* Parameter validity check for pin function. */
#define IS_GPIO_FUNC(func)                                                      \
(   ((func) == GPIO_FUNC_0)                     ||                              \
    ((func) == GPIO_FUNC_1)                     ||                              \
    ((func) == GPIO_FUNC_2)                     ||                              \
    ((func) == GPIO_FUNC_3)                     ||                              \
    ((func) == GPIO_FUNC_4)                     ||                              \
    ((func) == GPIO_FUNC_5)                     ||                              \
    ((func) == GPIO_FUNC_6)                     ||                              \
    ((func) == GPIO_FUNC_7))

/* Parameter validity check for debug pin definition. */
#define IS_GPIO_DEBUG_PORT(port)                                                \
(   ((port) != 0x00U)                           &&                              \
    (((port) | GPIO_PIN_DEBUG_JTAG) == GPIO_PIN_DEBUG_JTAG))

/* Parameter validity check for pin read wait cycle. */
#define IS_GPIO_RD_WAIT(wait)                                                   \
(   ((wait) == GPIO_RD_WAIT0)                   ||                              \
    ((wait) == GPIO_RD_WAIT1)                   ||                              \
    ((wait) == GPIO_RD_WAIT2)                   ||                              \
    ((wait) == GPIO_RD_WAIT3))

/* Parameter validity check for GPIO register lock status. */
#define IS_GPIO_UNLOCK()            (GPIO_PWPR_WE == (CM_GPIO->PWPR & GPIO_PWPR_WE))

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

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Functions GPIO Global Functions
 * @{
 */

/**
 * @brief  Initialize GPIO.
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @param  [in] u8Pin: GPIO_PIN_x, x can be (0~7) to select the PIN index
 * @param  [in] pstcGpioInit: Pointer to a stc_gpio_init_t structure that
 *                            contains configuration information.
 * @retval An en_result_t enumeration value
 *         Ok: GPIO initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t GPIO_Init(uint8_t u8Port, uint8_t u8Pin, const stc_gpio_init_t *pstcGpioInit)
{
    __IO uint16_t *PCRx;
    uint8_t u8PinPos;
    uint16_t u16PCRVal;
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcGpioInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_GPIO_UNLOCK());
        DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));
        DDL_ASSERT(IS_GPIO_PIN(u8Pin));
        DDL_ASSERT(IS_GPIO_PIN_STAT(pstcGpioInit->u16PinState));
        DDL_ASSERT(IS_GPIO_DIR(pstcGpioInit->u16PinDir));
        DDL_ASSERT(IS_GPIO_OUT_TYPE(pstcGpioInit->u16PinOutputType));
        DDL_ASSERT(IS_GPIO_PIN_DRV(pstcGpioInit->u16PinDrv));
        DDL_ASSERT(IS_GPIO_LATCH(pstcGpioInit->u16Latch));
        DDL_ASSERT(IS_GPIO_PIN_PU(pstcGpioInit->u16PullUp));
        DDL_ASSERT(IS_GPIO_PIN_INVT(pstcGpioInit->u16Invert));
        DDL_ASSERT(IS_GPIO_IN_TYPE(pstcGpioInit->u16PinInputType));
        DDL_ASSERT(IS_GPIO_EXTINT(pstcGpioInit->u16ExtInt));

        for (u8PinPos = 0U; u8PinPos < 8U; u8PinPos++)
        {
            if ((u8Pin & (1UL<<u8PinPos)) != 0U)
            {
                PCRx = (__IO uint16_t *)((uint32_t)(&CM_GPIO->PCR00) +              \
                                  (u8Port * 0x20UL) + (u8PinPos * 4UL));

                u16PCRVal = pstcGpioInit->u16ExtInt | pstcGpioInit->u16PinInputType |  \
                            pstcGpioInit->u16Invert | pstcGpioInit->u16PullUp   |   \
                            pstcGpioInit->u16Latch  | pstcGpioInit->u16PinDrv   |   \
                            pstcGpioInit->u16PinOutputType | pstcGpioInit->u16PinState | \
                            pstcGpioInit->u16PinDir;
                WRITE_REG16(*PCRx, u16PCRVal);
            }
        }
    }
    return enRet;
}

/**
 * @brief  De-init GPIO register to default value
 * @param  None
 * @retval None
 */
void GPIO_DeInit(void)
{
    stc_gpio_init_t stcGpioInit;
    (void)GPIO_StructInit(&stcGpioInit);

    /* PORT register unprotect */
    WRITE_REG16(CM_GPIO->PWPR, GPIO_REG_UNPROTECT);

    /* PORT0 reset */
    (void)GPIO_Init(GPIO_PORT_0, (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2), &stcGpioInit);
    /* PORT1 reset */
    (void)GPIO_Init(GPIO_PORT_1, (GPIO_PIN_0 | GPIO_PIN_1), &stcGpioInit);
    /* PORT2 reset */
    (void)GPIO_Init(GPIO_PORT_2, (GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4), &stcGpioInit);
    /* PORT3 reset */
    (void)GPIO_Init(GPIO_PORT_3,                                                \
             (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6 |  \
              GPIO_PIN_7), &stcGpioInit);
    /* PORT4 reset */
    (void)GPIO_Init(GPIO_PORT_4, GPIO_PIN_ALL, &stcGpioInit);
    /* PORT5 reset */
    (void)GPIO_Init(GPIO_PORT_5, GPIO_PIN_0, &stcGpioInit);
    /* PORT7 reset */
    (void)GPIO_Init(GPIO_PORT_7,                                                \
              (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | \
               GPIO_PIN_5 | GPIO_PIN_6), &stcGpioInit);
    /* PORT9 reset */
    (void)GPIO_Init(GPIO_PORT_9, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |        \
                    GPIO_PIN_4), &stcGpioInit);
    /* PORTA reset */
    (void)GPIO_Init(GPIO_PORT_A, (GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |        \
                    GPIO_PIN_5), &stcGpioInit);
    /* PORTB reset */
    (void)GPIO_Init(GPIO_PORT_B, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTD reset */
    (void)GPIO_Init(GPIO_PORT_D,                                                \
              (GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7), \
              &stcGpioInit);
    /* PORTE reset */
    (void)GPIO_Init(GPIO_PORT_E, GPIO_PIN_0, &stcGpioInit);

    /* PORT global register reset */
    WRITE_REG16(CM_GPIO->PSPCR, GPIO_PSPCR_RST_VALUE);
    WRITE_REG16(CM_GPIO->PCCR, GPIO_PCCR_RST_VALUE);
    WRITE_REG16(CM_GPIO->PINAER, GPIO_PINAER_RST_VALUE);

    /* PORT registers protected */
    WRITE_REG16(CM_GPIO->PWPR, GPIO_REG_PROTECT);
}

/**
 * @brief  Initialize GPIO. Fill each pstcGpioInit with default value
 * @param  [in] pstcGpioInit: Pointer to a stc_gpio_init_t structure that
 *                            contains configuration information.
 * @retval An en_result_t enumeration value
 *         Ok: GPIO structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t GPIO_StructInit(stc_gpio_init_t *pstcGpioInit)
{
    en_result_t enRet = Ok;
    /* Check if pointer is NULL */
    if (NULL == pstcGpioInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Reset GPIO init structure parameters values */
        pstcGpioInit->u16PinState   = PIN_STAT_RST;
        pstcGpioInit->u16PinDir     = PIN_DIR_IN;
        pstcGpioInit->u16PinOutputType = PIN_OUT_TYPE_CMOS;
        pstcGpioInit->u16PinDrv     = PIN_NORMAL_DRV;
        pstcGpioInit->u16Latch      = PIN_LATCH_OFF;
        pstcGpioInit->u16PullUp     = PIN_PU_OFF;
        pstcGpioInit->u16Invert     = PIN_INVT_OFF;
        pstcGpioInit->u16PinInputType  = PIN_IN_TYPE_SMT;
        pstcGpioInit->u16ExtInt     = PIN_EXTINT_OFF;
    }
    return enRet;
}

/**
 * @brief  GPIO debug port configure. Set debug pins to GPIO
 * @param  [in] u16DebugPort
 *   @arg  GPIO_PIN_SWDIO
 *   @arg  GPIO_PIN_SWCLK
 *   @arg  GPIO_PIN_SWO
 *   @arg  GPIO_PIN_DEBUG_SWD
 *   @arg  GPIO_PIN_TCK
 *   @arg  GPIO_PIN_TMS
 *   @arg  GPIO_PIN_TDO
 *   @arg  GPIO_PIN_TDI
 *   @arg  GPIO_PIN_TRST
 *   @arg  GPIO_PIN_DEBUG_JTAG
 * @param  [in] enNewState
 *   @arg  Enable, set to debug port (SWD/JTAG)
 *   @arg  Disable, set to GPIO
 * @retval None
 */
void GPIO_SetDebugPort(uint16_t u16DebugPort, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_DEBUG_PORT(u16DebugPort));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_GPIO_UNLOCK());

    if (Enable == enNewState)
    {
        SET_REG16_BIT(CM_GPIO->PSPCR, u16DebugPort);
    }
    else
    {
        CLEAR_REG16_BIT(CM_GPIO->PSPCR, u16DebugPort);
    }
}

/**
 * @brief  Set specified Port Pin function
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @param  [in] u8Pin: GPIO_PIN_x, x can be (0~7) to select the PIN index
 * @param  [in] u8Func: GPIO_FUNC_x, x can be selected from GPIO function definitions
 * @retval None
 */
void GPIO_SetFunc(uint8_t u8Port, uint8_t u8Pin, uint8_t u8Func)
{
    __IO uint16_t *PFSRx;
    uint8_t u8PinPos;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u8Pin));
    DDL_ASSERT(IS_GPIO_FUNC(u8Func));
    DDL_ASSERT(IS_GPIO_UNLOCK());

    for (u8PinPos = 0U; u8PinPos < 8U; u8PinPos ++)
    {
        if ((u8Pin & (1UL<<u8PinPos)) != 0U)
        {
            PFSRx = (__IO uint16_t *)((uint32_t)(&CM_GPIO->PFSR00) +            \
                                      (u8Port * 0x20UL) + (u8PinPos * 4UL));
            WRITE_REG16(*PFSRx, u8Func);
        }
    }
}

/**
 * @brief  Initialize GPIO.
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @param  [in] u8Pin: GPIO_PIN_x, x can be (0~7) to select the PIN index
 * @param  [in] enNewState
 *   @arg  Enable, set specified pin output enable
 *   @arg  Disable, set specified pin output disable
 * @retval None
 */
void GPIO_OE(uint8_t u8Port, uint8_t u8Pin, en_functional_state_t enNewState)
{
    __IO uint8_t *POERx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u8Pin));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    POERx = (__IO uint8_t *)((uint32_t)(&CM_GPIO->POER0) + u8Port);
    if (Enable == enNewState)
    {
        SET_REG8_BIT(*POERx, u8Pin);
    }
    else
    {
        CLEAR_REG8_BIT(*POERx, u8Pin);
    }
}

/**
 * @brief  GPIO read wait cycle configure.
 * @param  [in] u16ReadWait
 *   @arg  GPIO_RD_WAIT0: 0  ~ 32MHz
 *   @arg  GPIO_RD_WAIT1: 32 ~ 60MHz
 *   @arg  GPIO_RD_WAIT2: 64 ~ 80MHz
 *   @arg  GPIO_RD_WAIT3: 64 ~ 80MHz
 * @retval None
 */
void GPIO_SetReadWaitCycle(uint16_t u16ReadWait)
{
    DDL_ASSERT(IS_GPIO_RD_WAIT(u16ReadWait));
    DDL_ASSERT(IS_GPIO_UNLOCK());

    MODIFY_REG16(CM_GPIO->PCCR, GPIO_PCCR_RDWT, u16ReadWait);
}

/**
 * @brief  GPIO input MOS always ON configure.
 * @param  [in] u16PortIndex: Port index
 *   @arg  GPIO_PORT_0_IDX
 *   @arg  GPIO_PORT_1_IDX
 *   @arg  GPIO_PORT_2_IDX
 *   @arg  GPIO_PORT_3_IDX
 *   @arg  GPIO_PORT_4_IDX
 *   @arg  GPIO_PORT_5_IDX
 *   @arg  GPIO_PORT_7_IDX
 *   @arg  GPIO_PORT_9_IDX
 *   @arg  GPIO_PORT_A_IDX
 *   @arg  GPIO_PORT_B_IDX
 *   @arg  GPIO_PORT_D_IDX
 *   @arg  GPIO_PORT_E_IDX
 *   @arg  GPIO_PORT_ALL
 * @param  [in] enNewState
 *   @arg  Enable, set input MOS always ON
 *   @arg  Disable, set input MOS turns on while read operation
 * @retval None
 */
void GPIO_InputMOSCmd(uint16_t u16PortIndex, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_GPIO_PORT(u16PortIndex));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_GPIO_UNLOCK());

    if (Enable == enNewState)
    {
        SET_REG16_BIT(CM_GPIO->PINAER, u16PortIndex);
    }
    else
    {
        CLEAR_REG16_BIT(CM_GPIO->PINAER, u16PortIndex);
    }
}

/**
 * @brief  Read specified GPIO input data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @param  [in] u8Pin: GPIO_PIN_x, x can be (0~7) to select the PIN index
 * @retval An en_pin_state_t enumeration value
 *         Pin_Reset, Specified GPIO port pin is reset
 *         Pin_Set, Specified GPIO port pin is set
 */
en_pin_state_t GPIO_ReadInputPins(uint8_t u8Port, uint8_t u8Pin)
{
    const __IO uint8_t *PIDx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));
    DDL_ASSERT(IS_GET_GPIO_PIN(u8Pin));

    PIDx = (__IO uint8_t *)((uint32_t)(&CM_GPIO->PIDR0) + u8Port);

    return ((READ_REG8(*PIDx) & (u8Pin)) != 0U) ? Pin_Set : Pin_Reset;
}

/**
 * @brief  Read specified GPIO input data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @retval Specified GPIO port input value
 */
uint8_t GPIO_ReadInputPort(uint8_t u8Port)
{
    const __IO uint8_t *PIDRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));

    PIDRx = (__IO uint8_t *)((uint32_t)(&CM_GPIO->PIDR0) + u8Port);

    return READ_REG8(*PIDRx);
}

/**
 * @brief  Read specified GPIO output data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @param  [in] u8Pin: GPIO_PIN_x, x can be (0~7) to select the PIN index
 * @retval An en_pin_state_t enumeration value
 *         Reset, Specified GPIO port pin output value is reset
 *         Set, Specified GPIO port pin output value is set
 */
en_pin_state_t GPIO_ReadOutputPins(uint8_t u8Port, uint8_t u8Pin)
{
    const __IO uint8_t *PODx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));
    DDL_ASSERT(IS_GET_GPIO_PIN(u8Pin));

    PODx = (__IO uint8_t *)((uint32_t)(&CM_GPIO->PODR0) + u8Port);

    return ((READ_REG8(*PODx) & (u8Pin)) != 0U) ? Pin_Set : Pin_Reset;
}

/**
 * @brief  Read specified GPIO output data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @retval Specified GPIO port output value
 */
uint8_t GPIO_ReadOutputPort(uint8_t u8Port)
{
    const __IO uint8_t *PODRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));

    PODRx = (__IO uint8_t *)((uint32_t)(&CM_GPIO->PODR0) + u8Port);

    return READ_REG8(*PODRx);
}

/**
 * @brief  Set specified GPIO output data port pin
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @param  [in] u8Pin: GPIO_PIN_x, x can be (0~7) to select the PIN index
 * @retval None
 */
void GPIO_SetPins(uint8_t u8Port, uint8_t u8Pin)
{
    __IO uint8_t *POSRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u8Pin));

    POSRx = (__IO uint8_t *)((uint32_t)(&CM_GPIO->POSR0) + u8Port);
    SET_REG8_BIT(*POSRx, u8Pin);
}

/**
 * @brief  Reset specified GPIO output data port pin
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @param  [in] u8Pin: GPIO_PIN_x, x can be (0~7) to select the PIN index
 * @retval None
 */
void GPIO_ResetPins(uint8_t u8Port, uint8_t u8Pin)
{
    __IO uint8_t *PORRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u8Pin));

    PORRx = (__IO uint8_t *)((uint32_t)(&CM_GPIO->PORR0) + u8Port);
    SET_REG8_BIT(*PORRx, u8Pin);
}

/**
 * @brief  Write specified GPIO data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @param  [in] u8PortValue: Pin output value
 *   @arg  PIN_STAT_RST
 *   @arg  PIN_STAT_SET
 * @retval None
 */
void GPIO_WritePort(uint8_t u8Port, uint8_t u8PortValue)
{
    __IO uint8_t *PODRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));

    PODRx = (__IO uint8_t *)((uint32_t)(&CM_GPIO->PODR0) + u8Port);
    WRITE_REG8(*PODRx, u8PortValue);
}

/**
 * @brief  Toggle specified GPIO output data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be (0~5, A,B,D,E) to select the GPIO peripheral
 * @param  [in] u8Pin: GPIO_PIN_x, x can be (0~7) to select the PIN index
 * @retval None
 */
void GPIO_TogglePins(uint8_t u8Port, uint8_t u8Pin)
{
    __IO uint8_t *POTRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SRC(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u8Pin));

    POTRx = (__IO uint8_t *)((uint32_t)(&CM_GPIO->POTR0) + u8Port);
    SET_REG8_BIT(*POTRx, u8Pin);
}

/**
 * @}
 */

#endif /* DDL_GPIO_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
