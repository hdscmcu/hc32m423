/**
 *******************************************************************************
 * @file  hc32m423_gpio.h
 * @brief This file contains all the functions prototypes of the GPIO driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-15       CDT             First version
   2020-10-27       CDT             Revise debug port definition
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
#ifndef __HC32M423_GPIO_H__
#define __HC32M423_GPIO_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_GPIO
 * @{
 */

#if (DDL_GPIO_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Types GPIO Global Types
 * @{
 */

/**
 * @brief  GPIO Pin Set and Reset enumeration
 */
typedef enum
{
    Pin_Reset = 0U,           /*!< Pin reset    */
    Pin_Set                   /*!< Pin set      */
} en_pin_state_t;

/**
 * @brief  GPIO Init structure definition
 */
typedef struct
{
    uint16_t u16PinState;       /*!< Set pin state to High or Low, @ref GPIO_PinState_Sel for details     */
    uint16_t u16PinDir;         /*!< Pin direction setting, @ref GPIO_PinDir_Sel for details              */
    uint16_t u16PinOutputType;  /*!< Output type setting, @ref GPIO_PinOutType_Sel for details            */
    uint16_t u16PinDrv;         /*!< Pin drive capacity setting, @ref GPIO_PinDrv_Sel for details         */
    uint16_t u16Latch;          /*!< Pin latch setting, @ref GPIO_PinLatch_Sel for details                */
    uint16_t u16PullUp;         /*!< Internal pull-up resistor setting, @ref GPIO_PinPU_Sel for details   */
    uint16_t u16Invert;         /*!< Pin input/output invert setting, @ref GPIO_PinInvert_Sel             */
    uint16_t u16PinInputType;   /*!< Input type setting, @ref GPIO_PinInType_Sel                          */
    uint16_t u16ExtInt;         /*!< External interrupt pin setting, @ref GPIO_PinExInt_Sel for details   */
} stc_gpio_init_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Macros GPIO Global Macros
 * @{
 */

/** @defgroup GPIO_pins_define GPIO pin source
 * @{
 */
#define GPIO_PIN_0                  (0x01U)     /*!< Pin 0 selected    */
#define GPIO_PIN_1                  (0x02U)     /*!< Pin 1 selected    */
#define GPIO_PIN_2                  (0x04U)     /*!< Pin 2 selected    */
#define GPIO_PIN_3                  (0x08U)     /*!< Pin 3 selected    */
#define GPIO_PIN_4                  (0x10U)     /*!< Pin 4 selected    */
#define GPIO_PIN_5                  (0x20U)     /*!< Pin 5 selected    */
#define GPIO_PIN_6                  (0x40U)     /*!< Pin 6 selected    */
#define GPIO_PIN_7                  (0x80U)     /*!< Pin 7 selected    */
#define GPIO_PIN_ALL                (0xFFU)     /*!< All pins selected */
#define GPIO_PIN_MASK               (0xFFU)     /*!< PIN mask */
/**
 * @}
 */

/** @defgroup GPIO_Port_source GPIO port source
  * @{
  */
#define GPIO_PORT_0                 (0x00U)     /*!< Port 0 selected  */
#define GPIO_PORT_1                 (0x01U)     /*!< Port 1 selected  */
#define GPIO_PORT_2                 (0x02U)     /*!< Port 2 selected  */
#define GPIO_PORT_3                 (0x03U)     /*!< Port 3 selected  */
#define GPIO_PORT_4                 (0x04U)     /*!< Port 4 selected  */
#define GPIO_PORT_5                 (0x05U)     /*!< Port 5 selected  */
#define GPIO_PORT_7                 (0x07U)     /*!< Port 7 selected  */
#define GPIO_PORT_9                 (0x09U)     /*!< Port 9 selected  */
#define GPIO_PORT_A                 (0x0AU)     /*!< Port A selected  */
#define GPIO_PORT_B                 (0x0BU)     /*!< Port B selected  */
#define GPIO_PORT_D                 (0x0DU)     /*!< Port D selected  */
#define GPIO_PORT_E                 (0x0EU)     /*!< Port E selected  */
/**
 * @}
 */

/** @defgroup GPIO_Port_index GPIO port index
 * @{
 */
#define GPIO_PORT_0_IDX             (0x0001U)   /*!< Port 0 index */
#define GPIO_PORT_1_IDX             (0x0002U)   /*!< Port 1 index */
#define GPIO_PORT_2_IDX             (0x0004U)   /*!< Port 2 index */
#define GPIO_PORT_3_IDX             (0x0008U)   /*!< Port 3 index */
#define GPIO_PORT_4_IDX             (0x0010U)   /*!< Port 4 index */
#define GPIO_PORT_5_IDX             (0x0020U)   /*!< Port 5 index */
#define GPIO_PORT_7_IDX             (0x0080U)   /*!< Port 7 index */
#define GPIO_PORT_9_IDX             (0x0200U)   /*!< Port 9 index */
#define GPIO_PORT_A_IDX             (0x0300U)   /*!< Port A index */
#define GPIO_PORT_B_IDX             (0x0400U)   /*!< Port B index */
#define GPIO_PORT_D_IDX             (0x2000U)   /*!< Port D index */
#define GPIO_PORT_E_IDX             (0x4000U)   /*!< Port E index */
#define GPIO_PORT_ALL               (0x6EBFU)   /*!< All ports */
#define GPIO_PORT_MASK              (0x6EBFU)   /*!< Ports mask */
/**
 * @}
 */

/**
 * @}
 */

/** @defgroup GPIO_function_selection_define GPIO function selection
 * @{
 */
/** @defgroup GPIO_PinFunction0 GPIO Function 0 selection
 * @{
 */
#define GPIO_FUNC_0             (0x00U)
#define GPIO_FUNC_0_GPO         (GPIO_FUNC_0)   /* GPIO function */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction1 GPIO Function 1 selection
 * @{
 */
#define GPIO_FUNC_1             (0x01U)
#define GPIO_FUNC_1_ANA         (GPIO_FUNC_1)   /*!< Analog function */
#define GPIO_FUNC_1_ADTRG       (GPIO_FUNC_1)   /*!< ADC external trigger */
#define GPIO_FUNC_1_ADST        (GPIO_FUNC_1)   /*!< ADC convert status */
#define GPIO_FUNC_1_CTCREF      (GPIO_FUNC_1)   /*!< Reference input pin for internal \
                                                    clock trimming controller */
#define GPIO_FUNC_1_MCO         (GPIO_FUNC_1)   /*!< MCO output */
#define GPIO_FUNC_1_VCOUT       (GPIO_FUNC_1)   /*!< Voltage comparator output */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction2 GPIO Function 2 selection
 * @{
 */
#define GPIO_FUNC_2             (0x02U)
#define GPIO_FUNC_2_EMB         (GPIO_FUNC_2)   /*!< EMB */
#define GPIO_FUNC_2_EMB_IN0     (GPIO_FUNC_2)   /*!< EMB input port 0 */
#define GPIO_FUNC_2_EMB_IN1     (GPIO_FUNC_2)   /*!< EMB input port 1 */
#define GPIO_FUNC_2_EMB_IN2     (GPIO_FUNC_2)   /*!< EMB input port 2 */
#define GPIO_FUNC_2_TIM4        (GPIO_FUNC_2)   /*!< Timer 4 uint 1 */
#define GPIO_FUNC_2_TIM4_CLK    (GPIO_FUNC_2)   /*!< Timer 4 unit 1 clock input */
#define GPIO_FUNC_2_TIM4_OUH    (GPIO_FUNC_2)   /*!< Timer 4 uint 1 U-phase output high */
#define GPIO_FUNC_2_TIM4_OUL    (GPIO_FUNC_2)   /*!< Timer 4 uint 1 U-phase output low */
#define GPIO_FUNC_2_TIM4_OVH    (GPIO_FUNC_2)   /*!< Timer 4 uint 1 V-phase output high */
#define GPIO_FUNC_2_TIM4_OVL    (GPIO_FUNC_2)   /*!< Timer 4 uint 1 V-phase output low */
#define GPIO_FUNC_2_TIM4_OWH    (GPIO_FUNC_2)   /*!< Timer 4 uint 1 W-phase output high */
#define GPIO_FUNC_2_TIM4_OWL    (GPIO_FUNC_2)   /*!< Timer 4 uint 1 W-phase output low */
#define GPIO_FUNC_2_TIM4_ADSM   (GPIO_FUNC_2)   /*!< Timer 4 uint 1 special event */
#define GPIO_FUNC_2_TIM4_PCT    (GPIO_FUNC_2)   /*!< Timer 4 uint 1 basetimer count direction indicator */
#define GPIO_FUNC_2_FCMREF      (GPIO_FUNC_2)   /*!< FCM */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction3 GPIO Function 3 selection
 * @{
 */
#define GPIO_FUNC_3                 (0x03U)
#define GPIO_FUNC_3_TIMB1           (GPIO_FUNC_3)   /*!< Timer B unit 1 */
#define GPIO_FUNC_3_TIMB1_PWM1      (GPIO_FUNC_3)   /*!< Timer B unit 1 channel 1 PWM output */
#define GPIO_FUNC_3_TIMB1_PWM2      (GPIO_FUNC_3)   /*!< Timer B unit 1 channel 2 PWM output */
#define GPIO_FUNC_3_TIMB1_PWM3      (GPIO_FUNC_3)   /*!< Timer B unit 1 channel 3 PWM output */
#define GPIO_FUNC_3_TIMB1_PWM4      (GPIO_FUNC_3)   /*!< Timer B unit 1 channel 4 PWM output */
#define GPIO_FUNC_3_USART3          (GPIO_FUNC_3)   /*!< USART3 */
#define GPIO_FUNC_3_USART3_CTS_RTS  (GPIO_FUNC_3)   /*!< USART3 CTS/RTS */
#define GPIO_FUNC_3_USART3_CK       (GPIO_FUNC_3)   /*!< USART3 CK */
#define GPIO_FUNC_3_USART3_RX       (GPIO_FUNC_3)   /*!< USART3 RX */
#define GPIO_FUNC_3_USART3_TX       (GPIO_FUNC_3)   /*!< USART3 TX */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction4 GPIO Function 4 selection
 * @{
 */
#define GPIO_FUNC_4                 (0x04U)
#define GPIO_FUNC_4_TIMA3           (GPIO_FUNC_4)   /*!< Timer A unit 3 */
#define GPIO_FUNC_4_TIMA3_PWM1      (GPIO_FUNC_4)   /*!< Timer A unit 3 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA3_PWM2      (GPIO_FUNC_4)   /*!< Timer A unit 3 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA3_CLKA      (GPIO_FUNC_4)   /*!< Timer A unit 3 clock A */
#define GPIO_FUNC_4_TIMA3_CLKB      (GPIO_FUNC_4)   /*!< Timer A unit 3 clock B */
#define GPIO_FUNC_4_TIMA3_TRIG      (GPIO_FUNC_4)   /*!< Timer A unit 3 trigger */
#define GPIO_FUNC_4_TIMA4           (GPIO_FUNC_4)   /*!< Timer A unit 4 */
#define GPIO_FUNC_4_TIMA4_PWM1      (GPIO_FUNC_4)   /*!< Timer A unit 4 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA4_PWM2      (GPIO_FUNC_4)   /*!< Timer A unit 4 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA4_CLKA      (GPIO_FUNC_4)   /*!< Timer A unit 4 clock A */
#define GPIO_FUNC_4_TIMA4_CLKB      (GPIO_FUNC_4)   /*!< Timer A unit 4 clock B */
#define GPIO_FUNC_4_TIMA4_TRIG      (GPIO_FUNC_4)   /*!< Timer A unit 4 trigger */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction5 GPIO Function 5 selection
 * @{
 */
#define GPIO_FUNC_5                 (0x05U)
#define GPIO_FUNC_5_USART           (GPIO_FUNC_5)     /*!< USART  */
#define GPIO_FUNC_5_USART1          (GPIO_FUNC_5)     /*!< USART1 */
#define GPIO_FUNC_5_USART1_CK       (GPIO_FUNC_5)     /*!< USART1 CK */
#define GPIO_FUNC_5_USART1_TX       (GPIO_FUNC_5)     /*!< USART1 TX */
#define GPIO_FUNC_5_USART1_RX       (GPIO_FUNC_5)     /*!< USART1 RX */
#define GPIO_FUNC_5_USART1_CST_RTS  (GPIO_FUNC_5)     /*!< USART1 CTS/RTS */
#define GPIO_FUNC_5_USART2          (GPIO_FUNC_5)     /*!< USART2 */
#define GPIO_FUNC_5_USART2_CK       (GPIO_FUNC_5)     /*!< USART2 CK */
#define GPIO_FUNC_5_USART2_RX       (GPIO_FUNC_5)     /*!< USART2 RX */
#define GPIO_FUNC_5_USART2_TX       (GPIO_FUNC_5)     /*!< USART2 TX */
#define GPIO_FUNC_5_USART2_CST_RTS  (GPIO_FUNC_5)     /*!< USART  CTS/RTS */
#define GPIO_FUNC_5_USART3          (GPIO_FUNC_5)     /*!< USART3 */
#define GPIO_FUNC_5_USART3_CK       (GPIO_FUNC_5)     /*!< USART3 CK */
#define GPIO_FUNC_5_USART3_RX       (GPIO_FUNC_5)     /*!< USART3 RX */
#define GPIO_FUNC_5_USART3_TX       (GPIO_FUNC_5)     /*!< USART3 TX */
#define GPIO_FUNC_5_USART3_CST_RTS  (GPIO_FUNC_5)     /*!< USART3 CTS/RTS */
#define GPIO_FUNC_5_USART4          (GPIO_FUNC_5)     /*!< USART4 */
#define GPIO_FUNC_5_USART4_CK       (GPIO_FUNC_5)     /*!< USART4 CK */
#define GPIO_FUNC_5_USART4_RX       (GPIO_FUNC_5)     /*!< USART4 RX */
#define GPIO_FUNC_5_USART4_TX       (GPIO_FUNC_5)     /*!< USART4 TX */
#define GPIO_FUNC_5_USART4_CST_RTS  (GPIO_FUNC_5)     /*!< USART4 CTS/RTS */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction6 GPIO Function 6 selection
 * @{
 */
#define GPIO_FUNC_6             (0x06U)
#define GPIO_FUNC_6_SPI         (GPIO_FUNC_6)     /*!< SPI */
#define GPIO_FUNC_6_SPI_NSS0    (GPIO_FUNC_6)     /*!< SPI NSS0 */
#define GPIO_FUNC_6_SPI_SCK     (GPIO_FUNC_6)     /*!< SPI SCK */
#define GPIO_FUNC_6_SPI_MOSI    (GPIO_FUNC_6)     /*!< SPI MOSI */
#define GPIO_FUNC_6_SPI_MISO    (GPIO_FUNC_6)     /*!< SPI MISO */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction7 GPIO Function 7 selection
 * @{
 */
#define GPIO_FUNC_7             (0x07U)
#define GPIO_FUNC_7_I2C         (GPIO_FUNC_7)   /*!< I2C */
#define GPIO_FUNC_7_I2C_SDA     (GPIO_FUNC_7)   /*!< I2C SDA */
#define GPIO_FUNC_7_I2C_SCL     (GPIO_FUNC_7)   /*!< I2C SCL */
#define GPIO_FUNC_7_TIMA1       (GPIO_FUNC_7)   /*!< Timer A unit 1 */
#define GPIO_FUNC_7_TIMA1_PWM1  (GPIO_FUNC_7)   /*!< Timer A unit 1 channel 1 PWM output */
#define GPIO_FUNC_7_TIMA1_CLKA  (GPIO_FUNC_7)   /*!< Timer A unit 1 clock A */
#define GPIO_FUNC_7_TIMA1_TRIG  (GPIO_FUNC_7)   /*!< Timer A unit 1 trigger */
#define GPIO_FUNC_7_TIMA2       (GPIO_FUNC_7)   /*!< Timer A unit 2 */
#define GPIO_FUNC_7_TIMA2_PWM1  (GPIO_FUNC_7)   /*!< Timer A unit 2 channel 1 PWM output */
#define GPIO_FUNC_7_TIMA2_CLKA  (GPIO_FUNC_7)   /*!< Timer A unit 2 clock A */
#define GPIO_FUNC_7_TIMA2_TRIG  (GPIO_FUNC_7)   /*!< Timer A unit 2 trigger */
/**
 * @}
 */

/** @defgroup GPIO_DebugPin_Sel GPIO Debug pin selection
 * @{
 */
#define GPIO_PIN_SWCLK          (0x01U)
#define GPIO_PIN_SWDIO          (0x02U)
#define GPIO_PIN_SWO            (0x04U)
#define GPIO_PIN_DEBUG_SWD      (0x07U)

#define GPIO_PIN_TCK            (0x01U)
#define GPIO_PIN_TMS            (0x02U)
#define GPIO_PIN_TDO            (0x04U)
#define GPIO_PIN_TDI            (0x08U)
#define GPIO_PIN_TRST           (0x10U)
#define GPIO_PIN_DEBUG_JTAG     (0x1FU)
/**
 * @}
 */

/** @defgroup GPIO_ReadCycle_Sel GPIO pin read wait cycle selection
 * @{
 */
#define GPIO_RD_WAIT0           ((uint16_t)(0x00UL << GPIO_PCCR_RDWT_POS))
#define GPIO_RD_WAIT1           ((uint16_t)(0x01UL << GPIO_PCCR_RDWT_POS))
#define GPIO_RD_WAIT2           ((uint16_t)(0x02UL << GPIO_PCCR_RDWT_POS))
#define GPIO_RD_WAIT3           ((uint16_t)(0x03UL << GPIO_PCCR_RDWT_POS))
/**
 * @}
 */

/**
 * @defgroup GPIO_PinState_Sel GPIO pin output state selection
 * @{
 */
#define PIN_STAT_RST            (0U)
#define PIN_STAT_SET            (GPIO_PCR_POUT)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinDir_Sel GPIO pin input/output direction selection
 * @{
 */
#define PIN_DIR_IN              (0U)
#define PIN_DIR_OUT             (GPIO_PCR_POUTE)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinOutType_Sel GPIO pin output type selection
 * @{
 */
#define PIN_OUT_TYPE_CMOS       (0U)
#define PIN_OUT_TYPE_NMOS       (GPIO_PCR_NOD)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinDrv_Sel GPIO Pin drive capacity selection
 * @{
 */
#define PIN_NORMAL_DRV          (0U)
#define PIN_HIGH_DRV            (GPIO_PCR_DRV)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinLatch_Sel GPIO Pin output latch selection
 * @{
 */
#define PIN_LATCH_OFF           (0U)
#define PIN_LATCH_ON            (GPIO_PCR_LTE)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinPU_Sel GPIO Pin internal pull-up resistor selection
 * @{
 */
#define PIN_PU_OFF              (0U)
#define PIN_PU_ON               (GPIO_PCR_PUU)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinInvert_Sel GPIO Pin I/O invert selection
 * @{
 */
#define PIN_INVT_OFF            (0U)
#define PIN_INVT_ON             (GPIO_PCR_INVE)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinInType_Sel GPIO Pin input type selection
 * @{
 */
#define PIN_IN_TYPE_SMT         (0U)
#define PIN_IN_TYPE_CMOS        (GPIO_PCR_CINSEL)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinExInt_Sel GPIO Pin external interrupt selection
 * @{
 */
#define PIN_EXTINT_OFF          (0U)
#define PIN_EXTINT_ON           (GPIO_PCR_INTE)
/**
 * @}
 */

/**
 * @defgroup GPIO_Register_Protect GPIO Registers Protect Code
 * @{
 */
#define GPIO_REG_UNPROTECT      (0xA501U)
#define GPIO_REG_PROTECT        (0xA500U)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup GPIO_Global_Functions
 * @{
 */
/**
 * @brief  GPIO lock. PSPCR, PCCR, PINAER, PCRxy, PFSRxy write disable
 * @param  None
 *
 * @retval None
 */
__STATIC_INLINE void GPIO_Lock(void)
{
    WRITE_REG16(CM_GPIO->PWPR, GPIO_REG_PROTECT);
}

/**
 * @brief  GPIO unlock. PSPCR, PCCR, PINAER, PCRxy, PFSRxy write enable
 * @param  None
 *
 * @retval None
 */
__STATIC_INLINE void GPIO_Unlock(void)
{
    WRITE_REG16(CM_GPIO->PWPR, GPIO_REG_UNPROTECT);
}

en_result_t GPIO_Init(uint8_t u8Port, uint8_t u8Pin, const stc_gpio_init_t *pstcGpioInit);
void GPIO_DeInit(void);
void GPIO_Unlock(void);
void GPIO_Lock(void);
en_result_t GPIO_StructInit(stc_gpio_init_t *pstcGpioInit);
void GPIO_SetDebugPort(uint16_t u16DebugPort, en_functional_state_t enNewState);
void GPIO_SetFunc(uint8_t u8Port, uint8_t u8Pin, uint8_t u8Func);
void GPIO_SetReadWaitCycle(uint16_t u16ReadWait);
void GPIO_InputMOSCmd(uint16_t u16PortIndex, en_functional_state_t enNewState);
void GPIO_OE(uint8_t u8Port, uint8_t u8Pin, en_functional_state_t enNewState);
/* port pin */
en_pin_state_t GPIO_ReadInputPins(uint8_t u8Port, uint8_t u8Pin);
uint8_t GPIO_ReadInputPort(uint8_t u8Port);
en_pin_state_t GPIO_ReadOutputPins(uint8_t u8Port, uint8_t u8Pin);
uint8_t GPIO_ReadOutputPort(uint8_t u8Port);
void GPIO_SetPins(uint8_t u8Port, uint8_t u8Pin);
void GPIO_ResetPins(uint8_t u8Port, uint8_t u8Pin);
void GPIO_WritePort(uint8_t u8Port, uint8_t u8PortValue);
void GPIO_TogglePins(uint8_t u8Port, uint8_t u8Pin);

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

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_GPIO_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
