/**
 *******************************************************************************
 * @file  hc32m423_i2c.h
 * @brief Head file for I2C module.
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-15       CDT             First version
   2020-11-16       CDT             Fix bug and optimize code for I2C driver and example
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
#ifndef __HC32M423_I2C_H__
#define __HC32M423_I2C_H__

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
 * @addtogroup DDL_I2C
 * @{
 */

#if (DDL_I2C_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup I2C_Global_Types I2C Global Types
 * @{
 */

/**
 * @brief I2c configuration structure
 */
typedef struct
{
    uint32_t u32ClockDiv;    /*!< I2C clock division for Pclk1 */
    uint32_t u32Baudrate;    /*!< I2C baudrate config*/
    uint32_t u32SclTime;     /*!< The SCL rising and falling time, count of Pclk1 */
}stc_i2c_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup I2C_Global_Macros I2C Global Macros
 * @{
 */

/** @defgroup I2C_Trans_Dir I2C transfer direction
  * @{
  */
#define I2C_DIR_TX                    (0x0U)
#define I2C_DIR_RX                    (0x1U)
/**
 * @}
 */

/**
 * @defgroup I2C_Addr_Config I2C Address configurate
 * @{
 */
#define I2C_ADDR_DISABLE              (0U)
#define I2C_ADDR_7BIT                 (I2C_SLR0_SLADDR0EN)
#define I2C_ADDR_10BIT                (I2C_SLR0_ADDRMOD0 | I2C_SLR0_SLADDR0EN)
/**
 * @}
 */

/**
 * @defgroup I2C_Clock_Division I2C clock division
 * @{
 */
#define I2C_CLK_DIV1                  (0UL)  /* Pclk1/1 */
#define I2C_CLK_DIV2                  (1UL)  /* Pclk1/2 */
#define I2C_CLK_DIV4                  (2UL)  /* Pclk1/4 */
#define I2C_CLK_DIV8                  (3UL)  /* Pclk1/8 */
#define I2C_CLK_DIV16                 (4UL)  /* Pclk1/16 */
#define I2C_CLK_DIV32                 (5UL)  /* Pclk1/32 */
#define I2C_CLK_DIV64                 (6UL)  /* Pclk1/64 */
#define I2C_CLK_DIV128                (7UL)  /* Pclk1/128 */
/**
 * @}
 */

/**
 * @defgroup I2C_Address_Num I2C address number
 * @{
 */
#define I2C_ADDR0                     (0UL)
#define I2C_ADDR1                     (1UL)
/**
 * @}
 */

/**
 * @defgroup I2C_Ack_Config I2C ACK configurate
 * @{
 */
#define I2C_ACK                       (0UL)
#define I2C_NACK                      (I2C_CR1_ACK)
/**
 * @}
 */

/**
 * @defgroup I2C_Smbus_Match_Config I2C Smbus address match configurate
 * @{
 */
#define I2C_SMBUS_MATCH_ALARM         (I2C_CR1_SMBALRTEN)
#define I2C_SMBUS_MATCH_DEFAULT       (I2C_CR1_SMBDEFAULTEN)
#define I2C_SMBUS_MATCH_HOST          (I2C_CR1_SMBHOSTEN)
/**
 * @}
 */

/**
 * @defgroup I2C_Digital_Filter_Clock I2C digital filter Clock
 * @{
 */
#define I2C_DIG_FILTER_CLK_DIV1       (0UL << I2C_FLTR_DNF_POS) /* I2C Clock/1 */
#define I2C_DIG_FILTER_CLK_DIV2       (1UL << I2C_FLTR_DNF_POS) /* I2C Clock/2 */
#define I2C_DIG_FILTER_CLK_DIV3       (2UL << I2C_FLTR_DNF_POS) /* I2C Clock/3 */
#define I2C_DIG_FILTER_CLK_DIV4       (3UL << I2C_FLTR_DNF_POS) /* I2C Clock/4 */
/**
 * @}
 */

/**
 * @defgroup I2C_Flag I2C Flag
 * @{
 */
#define I2C_FLAG_START                (I2C_SR_STARTF)
#define I2C_FLAG_MATCH_ADDR0          (I2C_SR_SLADDR0F)
#define I2C_FLAG_MATCH_ADDR1          (I2C_SR_SLADDR1F)
#define I2C_FLAG_TX_CPLT              (I2C_SR_TENDF)
#define I2C_FLAG_STOP                 (I2C_SR_STOPF)
#define I2C_FLAG_RX_FULL              (I2C_SR_RFULLF)
#define I2C_FLAG_TX_EMPTY             (I2C_SR_TEMPTYF)
#define I2C_FLAG_ARBITRATE_FAIL       (I2C_SR_ARLOF)
#define I2C_FLAG_ACKR                 (I2C_SR_ACKRF)
#define I2C_FLAG_NACKF                (I2C_SR_NACKF)
#define I2C_FLAG_MASTER               (I2C_SR_MSL)
#define I2C_FLAG_BUSY                 (I2C_SR_BUSY)
#define I2C_FLAG_TRA                  (I2C_SR_TRA)
#define I2C_FLAG_GENERAL_CALL         (I2C_SR_GENCALLF)
#define I2C_FLAG_SMBUS_DEFAULT_MATCH  (I2C_SR_SMBDEFAULTF)
#define I2C_FLAG_SMBUS_HOST_MATCH     (I2C_SR_SMBHOSTF)
#define I2C_FLAG_SMBUS_ALARM_MATCH    (I2C_SR_SMBALRTF)
/**
 * @}
 */

/**
 * @defgroup I2C_Int_Flag I2C interrupt flag bits
 * @{
 */
#define I2C_INT_START                 (I2C_CR2_STARTIE)
#define I2C_INT_MATCH_ADDR0           (I2C_CR2_SLADDR0IE)
#define I2C_INT_MATCH_ADDR1           (I2C_CR2_SLADDR1IE)
#define I2C_INT_TX_CPLT               (I2C_CR2_TENDIE)
#define I2C_INT_STOP                  (I2C_CR2_STOPIE)
#define I2C_INT_RX_FULL               (I2C_CR2_RFULLIE)
#define I2C_INT_TX_EMPTY              (I2C_CR2_TEMPTYIE)
#define I2C_INT_ARBITRATE_FAIL        (I2C_CR2_ARLOIE)
#define I2C_INT_NACK                  (I2C_CR2_NACKIE)
#define I2C_INT_GENERAL_CALL          (I2C_CR2_GENCALLIE)
#define I2C_INT_SMBUS_DEFAULT_MATCH   (I2C_CR2_SMBDEFAULTIE)
#define I2C_INT_SMBUS_HOST_MATCH      (I2C_CR2_SMBHOSTIE)
#define I2C_INT_SMBUS_ALARM_MATCH     (I2C_CR2_SMBALRTIE)
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
 * @addtogroup I2C_Global_Functions
 * @{
 */

/* Initialization and Configuration **********************************/
en_result_t I2C_StructInit(stc_i2c_init_t* pstcI2cInit);
en_result_t I2C_BaudrateConfig(CM_I2C_TypeDef *I2Cx, const stc_i2c_init_t* pstcI2cInit, float32_t *pf32Error);
void I2C_DeInit(CM_I2C_TypeDef *I2Cx);
en_result_t I2C_Init(CM_I2C_TypeDef *I2Cx, const stc_i2c_init_t* pstcI2cInit, float32_t *pf32Error);
void I2C_SlaveAddrConfig(CM_I2C_TypeDef* I2Cx, uint32_t u32AddrNum, uint32_t u32AddrMode, uint32_t u32Addr);
void I2C_Cmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState);
void I2C_FastAckCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_BusWaitCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);

void I2C_SmbusConfig(CM_I2C_TypeDef* I2Cx, uint32_t u32SmbusConfig, en_functional_state_t enNewState);
void I2C_SmBusCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);

void I2C_DigitalFilterConfig(CM_I2C_TypeDef* I2Cx, uint32_t u32FilterClock);
void I2C_DigitalFilterCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_AnalogFilterCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);

void I2C_GeneralCallCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_SWResetCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState);
void I2C_IntCmd(CM_I2C_TypeDef* I2Cx, uint32_t u32IntType, en_functional_state_t enNewState);

/* Start/Restart/Stop ************************************************/
void I2C_GenerateStart(CM_I2C_TypeDef *I2Cx);
void I2C_GenerateReStart(CM_I2C_TypeDef *I2Cx);
void I2C_GenerateStop(CM_I2C_TypeDef *I2Cx);

/* Status management *************************************************/
en_flag_status_t I2C_GetStatus(const CM_I2C_TypeDef* I2Cx, uint32_t u32Flag);
void I2C_ClearStatus(CM_I2C_TypeDef* I2Cx, uint32_t u32Flag);

/* Data transfer ************************************  ***************/
void I2C_WriteData(CM_I2C_TypeDef* I2Cx, uint8_t u8Data);
uint8_t I2C_ReadData(const CM_I2C_TypeDef *I2Cx);
void I2C_AckConfig(CM_I2C_TypeDef* I2Cx, uint32_t u32AckConfig);

/* High level functions for reference ********************************/
en_result_t I2C_Start(CM_I2C_TypeDef* I2Cx, uint32_t u32Timeout);
en_result_t I2C_Restart(CM_I2C_TypeDef* I2Cx, uint32_t u32Timeout);
en_result_t I2C_TransAddr(CM_I2C_TypeDef* I2Cx, uint16_t u16Addr, uint8_t u8Dir, uint32_t u32Timeout);
en_result_t I2C_Trans10BitAddr(CM_I2C_TypeDef* I2Cx, uint16_t u16Addr, uint8_t u8Dir, uint32_t u32Timeout);
en_result_t I2C_TransData(CM_I2C_TypeDef* I2Cx, uint8_t const au8TxData[], uint32_t u32Size, uint32_t u32Timeout);
en_result_t I2C_ReceiveData(CM_I2C_TypeDef* I2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout);
en_result_t I2C_MasterReceiveDataAndStop(CM_I2C_TypeDef* I2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout);
en_result_t I2C_Stop(CM_I2C_TypeDef* I2Cx, uint32_t u32Timeout);
en_result_t I2C_WaitStatus(const CM_I2C_TypeDef *I2Cx, uint32_t u32Flag, en_flag_status_t enStatus, uint32_t u32Timeout);

/**
 * @}
 */

#endif /* DDL_I2C_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_I2C_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
