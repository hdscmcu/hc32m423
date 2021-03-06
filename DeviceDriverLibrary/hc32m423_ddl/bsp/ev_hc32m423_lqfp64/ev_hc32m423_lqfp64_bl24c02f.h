/**
 *******************************************************************************
 * @file  ev_hc32m423_lqfp64_bl24c02f.h
 * @brief This file contains all the functions prototypes of the
          ev_hc32m423_lqfp64_bl24c02f driver library.
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
#ifndef __EV_HC32M423_LQFP64_BL24C02F_H__
#define __EV_HC32M423_LQFP64_BL24C02F_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "bl24c02f.h"
#include "hc32_ddl.h"

/**
 * @addtogroup BSP
 * @{
 */

/** @addtogroup EV_HC32M423_LQFP64
  * @{
  */

/** @addtogroup EV_HC32M423_LQFP64_BL24C02F
  * @{
  */

#if ((BSP_BL24C02F_ENABLE == BSP_ON) && \
     (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32M423_LQFP64_BL24C02F_Global_Macros BSP BL24C02F Global Macros
 * @{
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
 * @defgroup EV_HC32M423_LQFP64_BL24C02F_Global_Functions BL24C02F EEPROM Global Functions
 * @{
 */

en_result_t BSP_BL24C02F_I2C_Init(void);

en_result_t BSP_BL24C02F_I2C_Start(void);
en_result_t BSP_BL24C02F_I2C_Restart(void);
en_result_t BSP_BL24C02F_I2C_Stop(void);

en_result_t BSP_BL24C02F_I2C_TransAddr(uint8_t u8Addr, uint8_t u8Dir);
en_result_t BSP_BL24C02F_I2C_TransData(uint8_t const au8TxData[], uint32_t u32Size);
en_result_t BSP_BL24C02F_I2C_ReceiveDataAndStop(uint8_t au8RxData[], uint32_t u32Size);

void BSP_BL24C02F_I2C_SWReset(void);
void BSP_BL24C02F_I2C_Cmd(en_functional_state_t enNewState);
void BSP_BL24C02F_I2C_AckConfig(uint32_t u32AckConfig);
en_flag_status_t BSP_BL24C02F_I2C_GetAckStatus(void);
/**
 * @}
 */

#endif /* BSP_BL24C02F_ENABLE && (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423) */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __EV_HC32M423_LQFP64_BL24C02F_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
