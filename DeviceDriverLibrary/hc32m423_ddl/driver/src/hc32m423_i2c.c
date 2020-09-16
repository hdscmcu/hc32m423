/**
 *******************************************************************************
 * @file  hc32m423_i2c.c
 * @brief This file provides firmware functions to manage the Inter-Integrated
 *        Circuit(I2C).
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
#include "hc32m423_i2c.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_I2C I2C
 * @brief I2C Driver Library
 * @{
 */

#if (DDL_I2C_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup I2C_Local_Macros I2C Local Macros
 * @{
 */

#define I2C_BAUDRATE_MAX                (400000UL)

#define I2C_SMBUS_CONFIG_CLR_MASK       (I2C_CR1_SMBALRTEN                     \
                                         | I2C_CR1_SMBDEFAULTEN                \
                                         | I2C_CR1_SMBHOSTEN)

#define I2C_FLAG_MASK                   (I2C_FLAG_START                        \
                                         | I2C_FLAG_MATCH_ADDR0                \
                                         | I2C_FLAG_MATCH_ADDR1                \
                                         | I2C_FLAG_TX_CPLT                    \
                                         | I2C_FLAG_STOP                       \
                                         | I2C_FLAG_RX_FULL                    \
                                         | I2C_FLAG_TX_EMPTY                   \
                                         | I2C_FLAG_ARBITRATE_FAIL             \
                                         | I2C_FLAG_ACK                        \
                                         | I2C_FLAG_NACK                       \
                                         | I2C_FLAG_MASTER                     \
                                         | I2C_FLAG_BUSY                       \
                                         | I2C_FLAG_TX                         \
                                         | I2C_FLAG_GENERAL_CALL               \
                                         | I2C_FLAG_SMBUS_DEFAULT_MATCH        \
                                         | I2C_FLAG_SMBUS_HOST_MATCH           \
                                         | I2C_FLAG_SMBUS_ALARM_MATCH)

#define I2C_CLR_FLAG_MASK               (I2C_FLAG_START                        \
                                         | I2C_FLAG_MATCH_ADDR0                \
                                         | I2C_FLAG_MATCH_ADDR1                \
                                         | I2C_FLAG_TX_CPLT                    \
                                         | I2C_FLAG_STOP                       \
                                         | I2C_FLAG_RX_FULL                    \
                                         | I2C_FLAG_TX_EMPTY                   \
                                         | I2C_FLAG_ARBITRATE_FAIL             \
                                         | I2C_FLAG_NACK                       \
                                         | I2C_FLAG_GENERAL_CALL               \
                                         | I2C_FLAG_SMBUS_DEFAULT_MATCH        \
                                         | I2C_FLAG_SMBUS_HOST_MATCH           \
                                         | I2C_FLAG_SMBUS_ALARM_MATCH)

#define I2C_INT_MASK                    (I2C_INT_START                         \
                                         | I2C_INT_MATCH_ADDR0                 \
                                         | I2C_INT_MATCH_ADDR1                 \
                                         | I2C_INT_TX_CPLT                     \
                                         | I2C_INT_STOP                        \
                                         | I2C_INT_RX_FULL                     \
                                         | I2C_INT_TX_EMPTY                    \
                                         | I2C_INT_ARBITRATE_FAIL              \
                                         | I2C_INT_NACK                        \
                                         | I2C_INT_GENERAL_CALL                \
                                         | I2C_INT_SMBUS_DEFAULT_MATCH         \
                                         | I2C_INT_SMBUS_HOST_MATCH            \
                                         | I2C_INT_SMBUS_ALARM_MATCH)


#define I2C_SCL_HIGHT_LOW_LVL_SUM_MAX   ((float32_t)0x1F * (float32_t)2)

/**
 * @defgroup I2C_Check_Parameters_Validity I2C Check Parameters Validity
 * @{
 */
#define IS_I2C_UNIT(x)                  ((x) == CM_I2C)

#define IS_I2C_DIG_FILTER_CLK(x)        ((x) <= I2C_DIG_FILTER_CLK_DIV4)

#define IS_I2C_SPEED(x)                                                        \
(   ((x) != 0U)                                     &&                         \
    ((x) <= I2C_BAUDRATE_MAX))

#define IS_I2C_FLAG(x)                                                         \
(   ((x) != 0U)                                     &&                         \
    (((x) | I2C_FLAG_MASK) == I2C_FLAG_MASK))

#define IS_I2C_CLR_FLAG(x)                                                     \
(   ((x) != 0U)                                     &&                         \
    (((x) | I2C_CLR_FLAG_MASK) == I2C_CLR_FLAG_MASK))

#define IS_I2C_INT_FLAG(x)                                                     \
(   ((x) != 0U)                                     &&                         \
    (((x) | I2C_INT_MASK) == I2C_INT_MASK))

#define IS_I2C_SMBUS_CONFIG(x)                                                 \
(   ((x) != 0U)                                     &&                         \
    (((x) | I2C_SMBUS_CONFIG_CLR_MASK) == I2C_SMBUS_CONFIG_CLR_MASK))

#define IS_I2C_ADDR(mode, addr)                                                \
(   ((I2C_ADDR_7BIT == (mode)) && ((addr) <= 0x7FU))        ||                 \
    ((I2C_ADDR_10BIT == (mode)) && ((addr) <= 0x3FFU))      ||                 \
    (I2C_ADDR_DISABLE == (mode)))

#define IS_I2C_ADDR_NUM(x)                                                     \
(   ((x) == I2C_ADDR0)                              ||                         \
    ((x) == I2C_ADDR1))

#define IS_I2C_CLK_DIV(x)                                                      \
(   ((x) == I2C_CLK_DIV1)                           ||                         \
    ((x) == I2C_CLK_DIV2)                           ||                         \
    ((x) == I2C_CLK_DIV4)                           ||                         \
    ((x) == I2C_CLK_DIV8)                           ||                         \
    ((x) == I2C_CLK_DIV16)                          ||                         \
    ((x) == I2C_CLK_DIV32)                          ||                         \
    ((x) == I2C_CLK_DIV64)                          ||                         \
    ((x) == I2C_CLK_DIV128))

#define IS_I2C_MD(x)                                                           \
(   ((x) == I2C_MASTER)                             ||                         \
    ((x) == I2C_SLAVE))

#define IS_I2C_TX_RX(x)                                                        \
(   ((x) == I2C_TX)                                 ||                         \
    ((x) == I2C_RX))

#define IS_I2C_ACK_CONFIG(x)                                                   \
(   ((x) == I2C_ACK)                                ||                         \
    ((x) == I2C_NACK))

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
 * @defgroup I2C_Global_Functions I2C Global Functions
 * @{
 */

/**
 * @brief  Try to wait a status of specified flags
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32Flag             Specify the flags to check
 *         This parameter can be any combination of the following values:
 *         @arg I2C_FLAG_START          : Start condition detected flag
 *         @arg I2C_FLAG_MATCH_ADDR0    : Address 0 detected flag
 *         @arg I2C_FLAG_MATCH_ADDR1    : Address 1 detected flag
 *         @arg I2C_FLAG_TX_CPLT        : Transfer end flag
 *         @arg I2C_FLAG_STOP           : Stop condition detected flag
 *         @arg I2C_FLAG_RX_FULL        : Receive buffer full flag
 *         @arg I2C_FLAG_TX_EMPTY       : Transfer buffer empty flag
 *         @arg I2C_FLAG_ARBITRATE_FAIL : Arbitration fails flag
 *         @arg I2C_FLAG_ACK            : ACK detected flag
 *         @arg I2C_FLAG_NACK           : NACK detected flag
 *         @arg I2C_FLAG_MASTER         : Master mode flag
 *         @arg I2C_FLAG_BUSY           : Bus busy status flag
 *         @arg I2C_FLAG_TX             : Transfer mode flag
 *         @arg I2C_FLAG_GENERAL_CALL   : General call detected flag
 *         @arg I2C_FLAG_SMBUS_DEFAULT_MATCH: Smbus default address detected flag
 *         @arg I2C_FLAG_SMBUS_HOST_MATCH   : Smbus host address detected flag
 *         @arg I2C_FLAG_SMBUS_ALARM_MATCH  : Smbus alarm address detected flag
 * @param  [in] enStatus            Expected status
 *         @arg Set:                Wait flag set
 *         @arg Reset:              Wait flag reset
 * @param  [in] u32Timeout          Maximum count of trying to get a status of a
 *                                  flag in status register
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Successfully gotten the expected status of the specified flags
 *         @arg ErrorTimeout:       Failed to get expected status of specified flags
 */
en_result_t I2C_WaitStatus(const CM_I2C_TypeDef *I2Cx, uint32_t u32Flag, en_flag_status_t enStatus, uint32_t u32Timeout)
{
    en_result_t enRet = ErrorTimeout;
    uint32_t u32RegStatusBit;

    for(;;)
    {
        u32RegStatusBit = (READ_REG32_BIT(I2Cx->SR, u32Flag));
        if(((enStatus == Set) && (u32Flag == u32RegStatusBit))
           || ((enStatus == Reset) && (0UL == u32RegStatusBit)))
        {
            enRet = Ok;
        }

        if((Ok == enRet) || (0UL == u32Timeout))
        {
            break;
        }
        else
        {
            u32Timeout--;
        }
    }

    return enRet;
}

/**
 * @brief  I2C generate start condition
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @retval None
 */
void I2C_GenerateStart(CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    SET_REG32_BIT(I2Cx->CR1, I2C_CR1_START);
}

/**
 * @brief  I2C generate restart condition
 * @param  [in]  I2Cx               Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  CM_I2C:                  I2C instance register base.
 * @retval None
 */
void I2C_GenerateReStart(CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    SET_REG32_BIT(I2Cx->CR1, I2C_CR1_RESTART);
}

/**
 * @brief  I2C generate stop condition
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @retval None
 */
void I2C_GenerateStop(CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    SET_REG32_BIT(I2Cx->CR1, I2C_CR1_STOP);
}

/**
 * @brief  Set the baudrate for I2C peripheral.
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] pstcI2cInit         Pointer to I2C config structure  @ref stc_i2c_init_t
 *         @arg pstcI2cInit->u32ClockDiv: Division of Pclk1, reference as:
 *              step1: calculate div = (Pclk1/Baudrate/(68+2*dnfsum+SclTime)
 *                     Pclk1    -- Pclk1
 *                     Baudrate -- baudrate of i2c
 *                     SclTime  -- =(SCL rising time + SCL falling time)/period of i2c clock
 *                                 according to i2c bus hardware parameter.
 *                     dnfsum   -- 0 if digital filter off;
 *                                 Filter capacity if digital filter on(1 ~ 4)
 *              step2: chose a division item which is similar and bigger than div
 *                     from @ref I2C_Clock_Division.
 *         @arg pstcI2cInit->u32Baudrate : Baudrate configuration
 *         @arg pstcI2cInit->u32SclTime : Indicate SCL pin rising and falling
 *              time, should be number of T(i2c clock period time)
 * @param  [out] pf32Error          Baudrate error
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Configurate success
 *         @arg ErrorInvalidParameter:  Invalid parameter
 */
en_result_t I2C_BaudrateConfig(CM_I2C_TypeDef *I2Cx, const stc_i2c_init_t* pstcI2cInit, float32_t *pf32Error)
{
    en_result_t enRet = Ok;
    uint32_t u32Pclk1;
    uint32_t I2cDivClk;
    uint32_t SclCnt;
    uint32_t Baudrate;
    uint32_t dnfsum = 0UL;
    uint32_t divsum = 2UL;
    float32_t WidthTotal;
    float32_t SumTotal;
    float32_t WidthHL;
    float32_t fErr = 0.0F;

    if ((NULL == pstcI2cInit) || (NULL == pf32Error))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_I2C_UNIT(I2Cx));
        DDL_ASSERT(IS_I2C_SPEED(pstcI2cInit->u32Baudrate));
        DDL_ASSERT(IS_I2C_CLK_DIV(pstcI2cInit->u32ClockDiv));

        /* Get configuration for i2c */
        u32Pclk1 = SystemCoreClock >> (CM_CMU->SCFGR & CMU_SCFGR_PCLK1S);
        I2cDivClk = 1UL << pstcI2cInit->u32ClockDiv;
        SclCnt = pstcI2cInit->u32SclTime;
        Baudrate = pstcI2cInit->u32Baudrate;

        /* Judge digital filter status*/
        if(0U != READ_REG32_BIT(I2Cx->FLTR, I2C_FLTR_DNFEN))
        {
            dnfsum = (READ_REG32_BIT(I2Cx->FLTR, I2C_FLTR_DNF) >> I2C_FLTR_DNF_POS) + 1U;
        }

        /* Judge if clock divider on*/
        if(I2C_CLK_DIV1 == I2cDivClk)
        {
            divsum = 3UL;
        }

        WidthTotal = (float32_t)u32Pclk1 / (float32_t)Baudrate / (float32_t)I2cDivClk;
        SumTotal = (2.0F*(float32_t)divsum) + (2.0F*(float32_t)dnfsum) + (float32_t)SclCnt;
        WidthHL = WidthTotal - SumTotal;

        if(WidthTotal <= SumTotal)
        {
            /* Err, Should set a smaller division value for pstcI2cInit->u32ClockDiv */
            enRet = ErrorInvalidParameter;
        }
        else
        {
            if(WidthHL > I2C_SCL_HIGHT_LOW_LVL_SUM_MAX)
            {
                /* Err, Should set a bigger division value for pstcI2cInit->u32ClockDiv */
                enRet = ErrorInvalidParameter;
            }
            else
            {
                fErr = (WidthHL - (float32_t)((uint32_t)WidthHL)) / WidthHL;
                WRITE_REG32(I2Cx->CCR,                                              \
                            (pstcI2cInit->u32ClockDiv << I2C_CCR_CKDIV_POS) |       \
                            (((uint32_t)WidthHL/2U) << I2C_CCR_SLOWW_POS)   |       \
                            (((uint32_t)WidthHL - (((uint32_t)WidthHL)/2U)) << I2C_CCR_SHIGHW_POS));
            }
        }
    }

    if((NULL != pf32Error) && (Ok == enRet))
    {
        *pf32Error = fErr;
    }

    return enRet;
}

/**
 * @brief  De-initialize I2C unit
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @retval None
 */
void I2C_DeInit(CM_I2C_TypeDef *I2Cx)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    /* Reset peripheral register and internal status*/
    CLEAR_REG32_BIT(I2Cx->CR1,I2C_CR1_PE);
    SET_REG32_BIT(I2Cx->CR1,I2C_CR1_SWRST);
}

/**
 * @brief  Initialize I2C peripheral according to the structure
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] pstcI2cInit         Pointer to I2C Initialize structure @ref stc_i2c_init_t
 *         @arg pstcI2cInit->u32ClockDiv: Division of Pclk1, reference as:
 *              step1: calculate div = (Pclk1/Baudrate/(68+2*dnfsum+SclTime)
 *                     Pclk1 -- Pclk1
 *                     Baudrate -- baudrate of i2c
 *                     SclTime -- =(SCL rising time + SCL falling time)/period of i2c clock
 *                                according to i2c bus hardware parameter.
 *                     dnfsum -- 0 if ditital filter off;
 *                               Filter capacity if ditital filter on(1 ~ 4)
 *              step2: chose a division item which is similar and bigger than div
 *                     from @ref I2C_Clock_Division.
 *         @arg pstcI2cInit->u32Baudrate : Baudrate configuration
 *         @arg pstcI2cInit->u32SclTime : Indicate SCL pin rising and falling
 *              time, should be number of T(i2c clock period time)
 * @param  [out] pf32Error          Baudrate error
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Configurate success
 *         @arg ErrorInvalidParameter:  Invalid parameter
 */
en_result_t I2C_Init(CM_I2C_TypeDef *I2Cx, const stc_i2c_init_t* pstcI2cInit, float32_t *pf32Error)
{
    en_result_t enRet;

    if (NULL == pstcI2cInit )
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_I2C_UNIT(I2Cx));
        DDL_ASSERT(IS_I2C_SPEED(pstcI2cInit->u32Baudrate));
        DDL_ASSERT(IS_I2C_CLK_DIV(pstcI2cInit->u32ClockDiv));

        /* Register and internal status reset */
        CLEAR_REG32_BIT(I2Cx->CR1,I2C_CR1_PE);
        SET_REG32_BIT(I2Cx->CR1,I2C_CR1_SWRST);
        SET_REG32_BIT(I2Cx->CR1,I2C_CR1_PE);

        /* I2C baudrate config */
        enRet = I2C_BaudrateConfig(I2Cx, pstcI2cInit, pf32Error);

        /* Disable global broadcast address function */
        CLEAR_REG32_BIT(I2Cx->CR1,I2C_CR1_GCEN);

        /* Release software reset */
        CLEAR_REG32_BIT(I2Cx->CR1,I2C_CR1_SWRST);
        /* Disable I2C peripheral */
        CLEAR_REG32_BIT(I2Cx->CR1,I2C_CR1_PE);
    }
    return enRet;
}

/**
 * @brief  I2C slave address config
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32AddrNum          I2C address 0 or address 1 @ref I2C_Address_Num
 *         @arg I2C_ADDR0:          Address number 0
 *         @arg I2C_ADDR1:          Address number 1
 * @param  [in] u32AddrMode         Address mode configuration @ref I2C_Addr_Config
 *                                  This parameter can be one of the following values:
 *         @arg I2C_ADDR_DISABLE:   Slave address invalid.
 *         @arg I2C_ADDR_7BIT:      Slave address 7 bit mode.
 *         @arg I2C_ADDR_10BIT:     Slave address 10 bit mode.
 * @param  [in] u32Addr             The slave address
 * @retval None
 */
void I2C_SlaveAddrConfig(CM_I2C_TypeDef* I2Cx, uint32_t u32AddrNum, uint32_t u32AddrMode, uint32_t u32Addr)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_ADDR_NUM(u32AddrNum));
    DDL_ASSERT(IS_I2C_ADDR(u32AddrMode, u32Addr));

    __IO uint32_t* const pu32SLRx = (__IO uint32_t*)((uint32_t)&I2Cx->SLR0 + (u32AddrNum * 4UL));

    if(I2C_ADDR_DISABLE == u32AddrMode)
    {
        CLEAR_REG32_BIT(*pu32SLRx, I2C_SLR0_SLADDR0EN);
    }
    else
    {
        if(I2C_ADDR_10BIT == u32AddrMode)
        {
            WRITE_REG32(*pu32SLRx, u32AddrMode + u32Addr);
        }
        else
        {
            WRITE_REG32(*pu32SLRx, u32AddrMode + (u32Addr << 1U));
        }
    }
}

/**
 * @brief  Manually set I2C master or slave mode
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32Mode             Specify I2C in master or slave mode. @ref I2C_Mode
 *         This parameter can be one of the following values:
 *         @arg I2C_MASTER:         I2C master mode.
 *         @arg I2C_SLAVE:          I2C slave mode.
 * @retval None
 */
void I2C_SetMode(CM_I2C_TypeDef* I2Cx, uint32_t u32Mode)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_MD(u32Mode));

    MODIFY_REG32(I2Cx->SR, I2C_SR_MSL, u32Mode);
}

/**
 * @brief  Manually set I2C tx or rx
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32TxRx             Specifies I2C in tx or rx mode. @ref I2C_Tx_Rx
 *         This parameter can be one of the following values:
 *         @arg I2C_TX:             I2C transfer mode.
 *         @arg I2C_RX:             I2C receive mode.
 * @retval None
 */
void I2C_SetTxRx(CM_I2C_TypeDef* I2Cx, uint32_t u32TxRx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_TX_RX(u32TxRx));

    MODIFY_REG32(I2Cx->SR, I2C_SR_TRA, u32TxRx);
}

/**
 * @brief  I2C function command
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] enNewState          The function new state.
 *         @arg Enable:             Enable I2C.
 *         @arg Disable:            Disable i2C.
 * @retval None
 */
void I2C_Cmd(CM_I2C_TypeDef *I2Cx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_PE, (uint32_t)enNewState << I2C_CR1_PE_POS);
}

/**
 * @brief I2C fast ACK config
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] enNewState          The function new state.
 *         @arg Enable:             Enable Fast ACK.
 *         @arg Disable:            Disable Fast ACK.
 * @retval None
 */
void I2C_FastAckCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(I2Cx->CR1, I2C_CR1_FACKEN);
    }
    else
    {
        SET_REG32_BIT(I2Cx->CR1, I2C_CR1_FACKEN);
    }
}

/**
 * @brief  I2C SMBUS function configuration
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32SmbusConfig      Indicate the SMBUS address match function configuration.
 *         This parameter can be one or any combination of the following values: @ref I2C_Smbus_Match_Config
 *         @arg I2C_SMBUS_MATCH_ALRT   : Smbus alarm address
 *         @arg I2C_SMBUS_MATCH_DEFAULT: Smbus default address
 *         @arg I2C_SMBUS_MATCH_HOST   : Smbus host address address
 * @param  [in] enNewState          The function new state.
 *         @arg Enable:             Enable Smbus address match function which is indicate by u32SmbusConfig.
 *         @arg Disable:            Disable Smbus address match function which is indicate by u32SmbusConfig.
 * @retval None
 */
void I2C_SmbusConfig(CM_I2C_TypeDef* I2Cx, uint32_t u32SmbusConfig, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_SMBUS_CONFIG(u32SmbusConfig));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(I2Cx->CR1, u32SmbusConfig);
    }
    else
    {
        CLEAR_REG32_BIT(I2Cx->CR1, u32SmbusConfig);
    }
}

/**
 * @brief  I2C SMBUS function command
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] enNewState          The function new state.
 *         @arg Enable:             Enable Smbus function.
 *         @arg Disable:            Disable Smbus function.
 * @retval None
 */
void I2C_SmBusCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_SMBUS, (uint32_t)enNewState << I2C_CR1_SMBUS_POS);
}

/**
 * @brief  I2C digital filter function configuration
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32FilterClock      Chose the digital filter mode, @ref I2C_Digital_Filter_Clock
 *         This parameter can be one of the following values:
 *         @arg I2C_DIG_FILTER_CLK_DIV1: I2C clock/1
 *         @arg I2C_DIG_FILTER_CLK_DIV2: I2C clock/2
 *         @arg I2C_DIG_FILTER_CLK_DIV3: I2C clock/3
 *         @arg I2C_DIG_FILTER_CLK_DIV4: I2C clock/4
 * @retval None
 */
void I2C_DigitalFilterConfig(CM_I2C_TypeDef* I2Cx, uint32_t u32FilterClock)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_DIG_FILTER_CLK(u32FilterClock));

    MODIFY_REG32(I2Cx->FLTR, I2C_FLTR_DNF, u32FilterClock);
}

/**
 * @brief  I2C digital filter command
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] enNewState          The function new state.
 *         @arg Enable:             Enable I2C digital filter.
 *         @arg Disable:            Disable I2C digital filter.
 * @retval None
 */
void I2C_DigitalFilterCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->FLTR, I2C_FLTR_DNFEN, (uint32_t)enNewState << I2C_FLTR_DNFEN_POS);
}

/**
 * @brief  I2C analog filter function command
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] enNewState          The function new state.
 *         @arg Enable:             Enable I2C analog filter.
 *         @arg Disable:            Disable I2C analog filter.
 * @retval None
 */
void I2C_AnalogFilterCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->FLTR, I2C_FLTR_ANFEN, (uint32_t)enNewState << I2C_FLTR_ANFEN_POS);
}

/**
 * @brief  I2C general call command
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] enNewState          The function new state.
 *         @arg Enable:             Enable I2C general call.
 *         @arg Disable:            Disable I2C general call.
 * @retval None
 */
void I2C_GeneralCallCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_GCEN, (uint32_t)enNewState << I2C_CR1_GCEN_POS);
}

/**
 * @brief  I2C flags status get
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32Flag             Specifies the flag to check, This parameter
 *                                  can be one or any combination of the
 *                                  following values
 *         @arg I2C_FLAG_START              : Start condition detected flag
 *         @arg I2C_FLAG_MATCH_ADDR0        : Address 0 detected flag
 *         @arg I2C_FLAG_MATCH_ADDR1        : Address 1 detected flag
 *         @arg I2C_FLAG_TX_CPLT            : Transfer complete flag
 *         @arg I2C_FLAG_STOP               : Stop condition detected flag
 *         @arg I2C_FLAG_RX_FULL            : Receive buffer full flag
 *         @arg I2C_FLAG_TX_EMPTY           : Transfer buffer empty flag
 *         @arg I2C_FLAG_ARBITRATE_FAIL     : Arbitration fails flag
 *         @arg I2C_FLAG_ACK                : ACK detected flag
 *         @arg I2C_FLAG_NACK               : NACK detected flag
 *         @arg I2C_FLAG_MASTER             : Master mode flag
 *         @arg I2C_FLAG_BUSY               : Bus busy status flag
 *         @arg I2C_FLAG_TX                 : Transfer mode flag
 *         @arg I2C_FLAG_GENERAL_CALL       : General call detected flag
 *         @arg I2C_FLAG_SMBUS_DEFAULT_MATCH: Smbus default address detected flag
 *         @arg I2C_FLAG_SMBUS_HOST_MATCH   : Smbus host address detected flag
 *         @arg I2C_FLAG_SMBUS_ALARM_MATCH  : Smbus alarm address detected flag
 * @retval The status of the I2C status flag, may be Set or Reset.
 */
en_flag_status_t I2C_GetStatus(const CM_I2C_TypeDef* I2Cx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_FLAG(u32Flag));

    return ((0UL != READ_REG32_BIT(I2Cx->SR, u32Flag)) ? Set : Reset);
}

/**
 * @brief  Clear I2C flags
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32Flag             Specifies the flag to clear, This parameter
 *                                  can be any combination of the following values
 *         @arg I2C_FLAG_START              : Start flag clear
 *         @arg I2C_FLAG_MATCH_ADDR0        : Address 0 detected flag clear
 *         @arg I2C_FLAG_MATCH_ADDR1        : Address 1 detected flag clear
 *         @arg I2C_FLAG_TX_CPLT            : Transfer end flag clear
 *         @arg I2C_FLAG_STOP               : Stop flag clear
 *         @arg I2C_FLAG_RX_FULL            : Receive buffer full flag clear
 *         @arg I2C_FLAG_TX_EMPTY           : Transfer buffer empty flag clear
 *         @arg I2C_FLAG_ARBITRATE_FAIL     : Arbitration fails flag clear
 *         @arg I2C_FLAG_NACK               : Nack detected flag clear
 *         @arg I2C_FLAG_GENERAL_CALL       : General call address detected flag clear
 *         @arg I2C_FLAG_SMBUS_DEFAULT_MATCH: Smbus default address detected flag clear
 *         @arg I2C_FLAG_SMBUS_HOST_MATCH   : Smbus host address detected flag clear
 *         @arg I2C_FLAG_SMBUS_ALARM_MATCH  : Smbus alarm address detected flag clear
 * @retval None
 */
void I2C_ClearStatus(CM_I2C_TypeDef* I2Cx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_CLR_FLAG(u32Flag));

    WRITE_REG32(I2Cx->CLR, u32Flag);
}

/**
 * @brief  I2C software reset function command
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] enNewState          The function new state.
 *         @arg Enable:             Enable I2C software reset.
 *         @arg Disable:            Disable I2C software reset.
 * @retval None
 */
void I2C_SWResetCmd(CM_I2C_TypeDef* I2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_SWRST, (uint32_t)enNewState << I2C_CR1_SWRST_POS);
}

/**
 * @brief  I2C interrupt command
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32IntType          Specifies the I2C interrupts sources to be configuration
 *         This parameter can be any combination of the following values: @ref I2C_Int_Flag
 *         @arg I2C_INT_START              : Start flag interrupt
 *         @arg I2C_INT_MATCH_ADDR0        : Address 0 detected interrupt
 *         @arg I2C_INT_MATCH_ADDR1        : Address 1 detected interrupt
 *         @arg I2C_INT_TX_CPLT            : Transfer end interrupt
 *         @arg I2C_INT_STOP               : Stop flag interrupt
 *         @arg I2C_INT_RX_FULL            : Receive buffer full interrupt
 *         @arg I2C_INT_TX_EMPTY           : Transfer buffer empty interrupt
 *         @arg I2C_INT_ARBITRATE_FAIL     : Arbitration fails interrupt
 *         @arg I2C_INT_NACK               : NACK flag detected interrupt
 *         @arg I2C_INT_GENERAL_CALL       : General call address detected interrupt
 *         @arg I2C_INT_SMBUS_DEFAULT_MATCH: Smbus default address detected interrupt
 *         @arg I2C_INT_SMBUS_HOST_MATCH   : Smbus host address detected interrupt
 *         @arg I2C_INT_SMBUS_ALARM_MATCH  : Smbus alarm address detected interrupt
 * @param  [in] enNewState          The function new state.
 *         @arg Enable:             Enable I2C interrupt.
 *         @arg Disable:            Disable I2C interrupt.
 * @retval None
 */
void I2C_IntCmd(CM_I2C_TypeDef* I2Cx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_INT_FLAG(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(I2Cx->CR2, u32IntType);
    }
    else
    {
        CLEAR_REG32_BIT(I2Cx->CR2, u32IntType);
    }
}

/**
 * @brief  I2C send data
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u8Data              The data to be send
 * @retval None
 */
void I2C_WriteData(CM_I2C_TypeDef* I2Cx, uint8_t u8Data)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    WRITE_REG8(I2Cx->DTR, u8Data);
}

/**
 * @brief  I2C read data from register
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @retval The value of the received data
 */
uint8_t I2C_ReadData(const CM_I2C_TypeDef *I2Cx)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    return READ_REG8(I2Cx->DRR);
}

/**
 * @brief  I2C ACK status configuration
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32AckConfig        I2C ACK configurate.
 *         @arg I2C_ACK:            Send ACK after date received.
 *         @arg I2C_NACK:           Send NACK after date received.
 * @retval None
 */
void I2C_AckConfig(CM_I2C_TypeDef* I2Cx, uint32_t u32AckConfig)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));
    DDL_ASSERT(IS_I2C_ACK_CONFIG(u32AckConfig));

    MODIFY_REG32(I2Cx->CR1, I2C_CR1_ACK, u32AckConfig);
}

/**
 * @brief  I2Cx start
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32Timeout          Maximum count of trying to get a status of a
 *                                  flag in status register
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Start success
 *         @arg ErrorTimeout:       Start time out
 */
en_result_t I2C_Start(CM_I2C_TypeDef* I2Cx, uint32_t u32Timeout)
{
    en_result_t enRet;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    enRet = I2C_WaitStatus(I2Cx, I2C_FLAG_BUSY, Reset, u32Timeout);

    if(Ok == enRet)
    {
        /* generate start signal */
        I2C_GenerateStart(I2Cx);
        /* Judge if start success*/
        enRet = I2C_WaitStatus(I2Cx, (I2C_FLAG_BUSY | I2C_FLAG_START), Set, u32Timeout);
    }

    return enRet;
}

/**
 * @brief  I2Cx restart
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32Timeout          Maximum count of trying to get a status of a
 *                                  flag in status register
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Restart successfully
 *         @arg ErrorTimeout:       Restart time out
 */
en_result_t I2C_Restart(CM_I2C_TypeDef* I2Cx, uint32_t u32Timeout)
{
    en_result_t enRet;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    /* Clear start status flag */
    I2C_ClearStatus(I2Cx, I2C_FLAG_START);
    /* Send restart condition */
    I2C_GenerateReStart(I2Cx);
    /* Judge if start success*/
    enRet = I2C_WaitStatus(I2Cx, (I2C_FLAG_BUSY | I2C_FLAG_START), Set, u32Timeout);

    return enRet;
}

/**
 * @brief  I2Cx send address
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u8Addr              The address to be sent
 * @param  [in] u32Timeout          Maximum count of trying to get a status of a
 *                                  flag in status register
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Send successfully
 *         @arg ErrorTimeout:       Send address time out
 */
en_result_t I2C_AddrTrans(CM_I2C_TypeDef* I2Cx, uint8_t u8Addr, uint32_t u32Timeout)
{
    en_result_t enRet;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    enRet = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_EMPTY, Set, u32Timeout);

    if(Ok == enRet)
    {
        /* Send I2C address */
        I2C_WriteData(I2Cx, u8Addr);

        if(0U == (u8Addr & 0x01U))
        {
            /* If in master transfer process, Need wait transfer end */
            enRet = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_CPLT, Set, u32Timeout);

            if(enRet == Ok)
            {
                enRet = I2C_WaitStatus(I2Cx, I2C_FLAG_ACK, Reset, u32Timeout);
            }
        }
    }

    return enRet;
}

/**
 * @brief  I2Cx send data
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] au8TxData           The data array to be sent
 * @param  [in] u32Size             Number of data in array pau8TxData
 * @param  [in] u32Timeout          Maximum count of trying to get a status of a
 *                                  flag in status register
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Send successfully
 *         @arg ErrorTimeout:       Send data time out
 *         @arg ErrorInvalidParameter: au8TxData is NULL
 */
en_result_t I2C_DataTrans(CM_I2C_TypeDef* I2Cx, uint8_t const au8TxData[], uint32_t u32Size, uint32_t u32Timeout)
{
    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    en_result_t enRet = Ok;
    uint32_t u32Cnt = 0UL;

    if(au8TxData != NULL)
    {
        while((u32Cnt != u32Size) && (enRet == Ok))
        {
            /* Wait tx buffer empty */
            enRet = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_EMPTY, Set, u32Timeout);

            if(enRet == Ok)
            {
                /* Send one byte data */
                I2C_WriteData(I2Cx, au8TxData[u32Cnt]);
                u32Cnt++;
                /* Wait transfer end*/
                enRet = I2C_WaitStatus(I2Cx, I2C_FLAG_TX_CPLT, Set, u32Timeout);

                if(enRet == Ok)
                {
                    if(u32Cnt != u32Size)
                    {
                        enRet = I2C_WaitStatus(I2Cx, I2C_FLAG_ACK, Reset, u32Timeout);
                    }
                }
            }
        }
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }

    return enRet;
}

/**
 * @brief  I2Cx receive data
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [out] au8RxData          Array to hold the received data
 * @param  [in] u32Size             Number of data to be received
 * @param  [in] u32Timeout          Maximum count of trying to get a status of a
 *                                  flag in status register
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Receive successfully
 *         @arg ErrorTimeout:       Receive data time out
 *         @arg ErrorInvalidParameter: au8RxData is NULL
 */
en_result_t I2C_DataReceive(CM_I2C_TypeDef* I2Cx, uint8_t au8RxData[], uint32_t u32Size, uint32_t u32Timeout)
{
    en_result_t enRet = Ok;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    if(au8RxData != NULL)
    {
        uint32_t u32FastAckEn = READ_REG32_BIT(I2Cx->CR1, I2C_CR1_FACKEN);
        for(uint32_t i=0UL; i<u32Size; i++)
        {
            if(((i == (u32Size - 1UL)) && (0UL == u32FastAckEn)))
            {
                I2C_AckConfig(I2Cx, I2C_NACK);
            }

            enRet = I2C_WaitStatus(I2Cx, I2C_FLAG_RX_FULL, Set, u32Timeout);

            if(enRet == Ok)
            {
                 /* read data from register */
                au8RxData[i] = I2C_ReadData(I2Cx);
                /* manually send ack and nack if FACKEN is set to 1(1:manually ack;0:fast ack) */
                if(0UL != u32FastAckEn)
                {
                    if(i != (u32Size - 1UL))
                    {
                        I2C_AckConfig(I2Cx, I2C_ACK);
                    }
                    else
                    {
                        I2C_AckConfig(I2Cx, I2C_NACK);
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }

    return enRet;
}

/**
 * @brief  I2Cx stop
 * @param  [in] I2Cx                Pointer to I2C instance register base.
 *                                  This parameter can be a value of the following:
 *         @arg CM_I2C:             I2C instance register base.
 * @param  [in] u32Timeout          Maximum count of trying to get a status of a
 *                                  flag in status register
 * @retval en_result_t              Enumeration value:
 *         @arg Ok:                 Stop successfully
 *         @arg ErrorTimeout:       Stop time out
 */
en_result_t I2C_Stop(CM_I2C_TypeDef* I2Cx, uint32_t u32Timeout)
{
    en_result_t enRet;

    DDL_ASSERT(IS_I2C_UNIT(I2Cx));

    /* Clear stop flag */
    while((Set == I2C_GetStatus(I2Cx, I2C_FLAG_STOP)) && (u32Timeout > 0UL))
    {
        I2C_ClearStatus(I2Cx, I2C_FLAG_STOP);
        u32Timeout--;
    }
    I2C_GenerateStop(I2Cx);
    /* Wait stop flag */
    enRet = I2C_WaitStatus(I2Cx, I2C_FLAG_STOP, Set, u32Timeout);

    return enRet;
}

/**
 * @brief  Initialize structure stc_i2c_init_t variable with default value.
 * @param  [out] pstcI2cInit            Pointer to a stc_i2c_init_t structure variable
 *                                      which will be initialized.
 *         @arg See the struct @ref stc_i2c_init_t.
 * @retval en_result_t
 */
en_result_t I2C_StructInit(stc_i2c_init_t* pstcI2cInit)
{
    en_result_t enRet = Ok;
    if (pstcI2cInit == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcI2cInit->u32Baudrate = 50000UL;
        pstcI2cInit->u32SclTime = 0UL;
    }

    return enRet;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
