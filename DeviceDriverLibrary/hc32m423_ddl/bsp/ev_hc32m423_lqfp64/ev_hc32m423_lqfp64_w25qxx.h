/**
 *******************************************************************************
 * @file  ev_hc32m423_lqfp64_w25qxx.h
 * @brief This file contains all the functions prototypes of the
          ev_hc32m423_lqfp64_w25qxx driver library.
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
#ifndef __EV_HC32M423_LQFP64_W25QXX_H__
#define __EV_HC32M423_LQFP64_W25QXX_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
//#include "ev_hc32m423_lqfp64.h"
#include "w25qxx.h"
#include "hc32_ddl.h"

/**
 * @addtogroup BSP
 * @{
 */

/** @addtogroup EV_HC32M423_LQFP64
  * @{
  */

/** @addtogroup EV_HC32M423_LQFP64_W25QXX
  * @{
  */

#if ((BSP_W25QXX_ENABLE == BSP_ON) && \
     (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32M423_LQFP64_W25QXX_Global_Macros BSP W25QXX Global Macros
 * @{
 */
/* SPI unit define */
#define W25Q_SPI_UNIT               (CM_SPI)
#define W25Q_SPI_UNIT_CLOCK         (CLK_FCG_SPI)

/* Port define */
#define W25Q_CS_PORT                (GPIO_PORT_3)
#define W25Q_CS_PIN                 (GPIO_PIN_0)

#define W25Q_SCK_PORT               (GPIO_PORT_2)
#define W25Q_SCK_PIN                (GPIO_PIN_4)
#define W25Q_SCK_FUNC               (GPIO_FUNC_6_SPI_SCK)

#define W25Q_MOSI_PORT              (GPIO_PORT_2)
#define W25Q_MOSI_PIN               (GPIO_PIN_3)
#define W25Q_MOSI_FUNC              (GPIO_FUNC_6_SPI_MOSI)

#define W25Q_MISO_PORT              (GPIO_PORT_2)
#define W25Q_MISO_PIN               (GPIO_PIN_2)
#define W25Q_MISO_FUNC              (GPIO_FUNC_6_SPI_MISO)

/* CS pin control define */
#define W25Q_CS_ACTIVE()            GPIO_ResetPins(W25Q_CS_PORT, W25Q_CS_PIN)
#define W25Q_CS_INACTIVE()          GPIO_SetPins(W25Q_CS_PORT, W25Q_CS_PIN)

#define W25QXX_DELAY_MS(x)          DDL_DelayMS((x))
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
 * @defgroup EV_HC32M423_LQFP64_W25QXX_Global_Functions HC32M423 SPI_NOR Global Functions
 * @{
 */
void BSP_W25Q_SPI_Init(void);

en_result_t BSP_W25Q_SPI_Trans(const void *pvTxBuf, uint32_t u32TxLen);
en_result_t BSP_W25Q_SPI_Receive(void *pvRxBuf, uint32_t u32RxLen);

/**
 * @}
 */

#endif /* BSP_W25QXX_ENABLE && (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423) */

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

#endif /* __EV_HC32M423_LQFP64_W25QXX_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
