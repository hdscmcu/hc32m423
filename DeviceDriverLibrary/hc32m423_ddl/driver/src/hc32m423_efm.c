/**
 *******************************************************************************
 * @file  hc32m423_efm.c
 * @brief This file provides firmware functions to manage the Embedded Flash
 *        Memory (EFM).
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
#include "hc32m423_efm.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_EFM EFM
 * @brief EFM Driver Library
 * @{
 */

#if (DDL_EFM_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EFM_Local_Macros EFM Local Macros
 * @{
 */
#define EFM_PGM_TIMEOUT              (HCLK_VALUE / 20000UL)   /* EFM Program timeout */
#define EFM_ERASE_TIMEOUT            (HCLK_VALUE / 20UL)      /* EFM Erase timeout */
#define EFM_SEQ_PGM_TIMEOUT          (HCLK_VALUE / 200000UL) /* EFM Sequence Program timeout */

/**
 * @defgroup EFM_Configuration_Bit_Mask EFM Configuration Bit Mask
 * @{
 */
#define EFM_CACHE_MASK             (EFM_FRMC_CRST | EFM_FRMC_ICHE | EFM_FRMC_DCHE)
#define EFM_FLAG_MASK              (EFM_FLAG_PEWERR | EFM_FLAG_PEPRTERR | \
                                    EFM_FLAG_PGMISMTCHERR | EFM_FLAG_OPTEND |\
                                    EFM_FLAG_COLERR | EFM_FLAG_RDY)

#define EFM_CLR_FLAG_MASK          (EFM_FLAG_PEWERR | EFM_FLAG_PEPRTERR | \
                                    EFM_FLAG_PGMISMTCHERR | EFM_FLAG_OPTEND   | \
                                    EFM_FLAG_COLERR)

#define EFM_INT_MASK               (EFM_INT_EOP | EFM_INT_PEERR | EFM_INT_RDCOLERR)
/**
 * @}
 */

/**
 * @defgroup EFM_Check_Parameters_Validity EFM Check Parameters Validity
 * @{
 */

/*! Parameter validity check for flash latency. */
#define IS_VALID_EFM_WAIT_CYCLE(x)                                             \
(   ((x) == EFM_WAIT_CYCLE0)                ||                                 \
    ((x) == EFM_WAIT_CYCLE1)                ||                                 \
    ((x) == EFM_WAIT_CYCLE2)                ||                                 \
    ((x) == EFM_WAIT_CYCLE3)                ||                                 \
    ((x) == EFM_WAIT_CYCLE4)                ||                                 \
    ((x) == EFM_WAIT_CYCLE5)                ||                                 \
    ((x) == EFM_WAIT_CYCLE6)                ||                                 \
    ((x) == EFM_WAIT_CYCLE7))

/*! Parameter validity check for operate mode. */
#define IS_VALID_EFM_OPERATE_MD(x)                                             \
(   ((x) == EFM_MD_PGM_SINGLE)              ||                                 \
    ((x) == EFM_MD_PGM_READBACK)            ||                                 \
    ((x) == EFM_MD_PGM_SEQ)                 ||                                 \
    ((x) == EFM_MD_ERASE_SECT)              ||                                 \
    ((x) == EFM_MD_ERASE_CHIP)              ||                                 \
    ((x) == EFM_MD_READONLY))

/*! Parameter validity check for flash interrupt select. */
#define IS_VALID_EFM_INT_SEL(x)                                                \
(   ((x) != 0x0UL)                          &&                                 \
    (((x) | EFM_INT_MASK) == EFM_INT_MASK))

/*! Parameter validity check for flash flag. */
#define IS_VALID_EFM_FLAG(x)                                                   \
(   ((x) != 0x0UL)                          &&                                 \
    (((x) | EFM_FLAG_MASK) == EFM_FLAG_MASK))

/*! Parameter validity check for flash clear flag. */
#define IS_VALID_EFM_CLRFLAG(x)                                                \
(   ((x) != 0x0UL)                          &&                                 \
    (((x) | EFM_CLR_FLAG_MASK) == EFM_CLR_FLAG_MASK))

/*! Parameter validity check for bus state while flash program or erase. */
#define IS_VALID_EFM_BUS_STATUS(x)                                             \
(   ((x) == EFM_BUS_BUSY)                   ||                                 \
    ((x) == EFM_BUS_RELEASE))

/*! Parameter validity check for efm data cache reset function. */
#define IS_VALID_EFM_CACHERST_FUNC(x)                                          \
(   ((x) == EFM_CACHE_RST_ON)               ||                                 \
    ((x) == EFM_CACHE_RST_OFF))

/*! Parameter validity check for efm instruction cache function. */
#define IS_VALID_EFM_INSCACHE_FUNC(x)                                          \
(   ((x) == EFM_INSTR_CACHE_ON)             ||                                 \
    ((x) == EFM_INSTR_CACHE_OFF))

/*! Parameter validity check for efm data cache function. */
#define IS_VALID_EFM_DATACACHE_FUNC(x)                                         \
(   ((x) == EFM_DATA_CACHE_ON)              ||                                 \
    ((x) == EFM_DATA_CACHE_OFF))

/*! Parameter validity check for efm address. */
#define IS_VALID_EFM_ADDR(x)                             ((x) <= EFM_END_ADDR)

/*! Check EFM lock status. */
#define IS_VALID_EFM_UNLOCK()                  (CM_EFM->FAPRT == 0x00000001UL)
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
 * @defgroup EFM_Global_Functions EFM Global Functions
 * @{
 */

/**
 * @brief  Enable or disable EFM.
 * @param  [in] enNewState          The new state of the flash.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    if (enNewState == Enable)
    {
        WRITE_REG32(bCM_EFM->FSTP_b.FSTP, 0x0U);
    }
    else
    {
        WRITE_REG32(bCM_EFM->FSTP_b.FSTP, 0x1U);
    }
}

/**
 * @brief  Init efm config structure with default value.
 * @param  [in] pstcEfmInit         The pointer of efm config structure.
 *   @arg  u32WaitCycle:            Specifies the efm read wait cycles.
 *   @arg  u32CacheReset:           Specifies the cache data reset on or off
 *   @arg  u32InstrCache:           Specifies the instruction cache on or off.
 *   @arg  u32DataCache:            Specifies the data cache on or off.
 *   @arg  u32BusStatus:            Specifies the bus status busy or release while program & erase.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t EFM_StructInit(stc_efm_init_t *pstcEfmInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcEfmInit)
    {
        /* Configure to default value */
        pstcEfmInit->u32WaitCycle  = EFM_WAIT_CYCLE0;
        pstcEfmInit->u32CacheReset = EFM_CACHE_RST_OFF;
        pstcEfmInit->u32InstrCache = EFM_INSTR_CACHE_OFF;
        pstcEfmInit->u32DataCache  = EFM_DATA_CACHE_OFF;
        pstcEfmInit->u32BusStatus  = EFM_BUS_BUSY;
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Efm initialize.
 * @param  [in] pstcEfmInit         The pointer of efm config structure.
 *   @arg  u32WaitCycle:            Specifies the efm cycles.
 *   @arg  u32CacheRst:             Specifies the cache data reset on or off.
 *   @arg  u32InstrCache:           Specifies the instruction cache on or off.
 *   @arg  u32DataCache:            Specifies the data cache on or off.
 *   @arg  u32BusStatus:            Specifies the bus status busy or release while program & erase.
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure success
 *           - ErrorInvalidParameter: Invalid parameter
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_Init(const stc_efm_init_t *pstcEfmInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcEfmInit)
    {
        /* Param valid check */
        DDL_ASSERT(IS_VALID_EFM_UNLOCK());
        DDL_ASSERT(IS_VALID_EFM_WAIT_CYCLE(pstcEfmInit->u32WaitCycle));
        DDL_ASSERT(IS_VALID_EFM_BUS_STATUS(pstcEfmInit->u32BusStatus));
        DDL_ASSERT(IS_VALID_EFM_CACHERST_FUNC(pstcEfmInit->u32CacheReset));
        DDL_ASSERT(IS_VALID_EFM_INSCACHE_FUNC(pstcEfmInit->u32InstrCache));
        DDL_ASSERT(IS_VALID_EFM_DATACACHE_FUNC(pstcEfmInit->u32DataCache));

        /* Config efm. */
        MODIFY_REG32(CM_EFM->FRMC, (EFM_FRMC_FLWT | EFM_FRMC_ICHE | EFM_FRMC_DCHE | EFM_FRMC_CRST),
                     pstcEfmInit->u32WaitCycle | pstcEfmInit->u32DataCache |
                     pstcEfmInit->u32InstrCache | pstcEfmInit->u32CacheReset);
        MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_BUSHLDCTL, pstcEfmInit->u32BusStatus);
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Set the efm read wait cycles.
 * @param  [in] u32WaitCycle           Specifies the efm read wait cycles.
 *  This parameter can be one of the following values:
 *   @arg  EFM_WAIT_CYCLE0:            Don't insert read wait cycle
 *   @arg  EFM_WAIT_CYCLE1:            Insert 1 read wait cycles
 *   @arg  EFM_WAIT_CYCLE2:            Insert 2 read wait cycles
 *   @arg  EFM_WAIT_CYCLE3:            Insert 3 read wait cycles
 *   @arg  EFM_WAIT_CYCLE4:            Insert 4 read wait cycles
 *   @arg  EFM_WAIT_CYCLE5:            Insert 5 read wait cycles
 *   @arg  EFM_WAIT_CYCLE6:            Insert 6 read wait cycles
 *   @arg  EFM_WAIT_CYCLE7:            Insert 7 read wait cycles
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_SetWaitCycle(uint32_t u32WaitCycle)
{
    /* Param valid check */
    DDL_ASSERT(IS_VALID_EFM_WAIT_CYCLE(u32WaitCycle));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    /* Set the code latency value. */
    MODIFY_REG32(CM_EFM->FRMC, EFM_FRMC_FLWT, u32WaitCycle);
}

/**
 * @brief  Enable or disable the flash cache data reset.
 * @param  [in] enNewState             The new state of the flash cache data reset.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_CacheDataResetCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    WRITE_REG32(bCM_EFM->FRMC_b.CRST, enNewState);
}

/**
 * @brief  Enable or disable the flash instruction cache.
 * @param  [in] enNewState                The new state of the flash instruction cache.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_InstrCacheCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    WRITE_REG32(bCM_EFM->FRMC_b.ICHE, enNewState);
}

/**
 * @brief  Enable or disable the flash data cache.
 * @param  [in] enNewState                The new state of the flash data cache.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_DataCacheCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    WRITE_REG32(bCM_EFM->FRMC_b.DCHE, enNewState);
}

/**
 * @brief  Set the FLASH erase program mode .
 * @param  [in] u32Mode                 Specifies the flash mode.
 *  This parameter can be one of the following values:
 *   @arg  EFM_MD_PGM_SINGLE:           Program single
 *   @arg  EFM_MD_PGM_READBACK:         Program and read back
 *   @arg  EFM_MD_PGM_SEQ:              Program sequence at sequence
 *   @arg  EFM_MD_ERASE_SECT:           Sector erase
 *   @arg  EFM_MD_ERASE_CHIP:           Chip erase
 *   @arg  EFM_MD_READONLY:             Read only
 * @retval An en_result_t enumeration value:
 *         - Ok: Success
 *         - ErrorTimeout: Process timeout
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_SetOperateMode(uint32_t u32Mode)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout = 0UL;
    DDL_ASSERT(IS_VALID_EFM_OPERATE_MD(u32Mode));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    while (EFM_GetStatus(EFM_FLAG_RDY) != Set)
    {
        u32Timeout++;
        if (u32Timeout > EFM_SEQ_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if (enRet == Ok)
    {
        /* Enable operate mode modified. */
        SET_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
        /* Set the program or erase mode. */
        MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, u32Mode);
        /* Disable operate mode modified. */
        CLEAR_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    }
    return enRet;
}

/**
 * @brief  Enable or Disable EFM interrupt.
 * @param  [in] u32EfmInt               Specifies the flash interrupt.
 *  This parameter can be of the following values:
 *   @arg  EFM_INT_EOP:                 End of EFM Operation Interrupt source
 *   @arg  EFM_INT_PEERR:               Program/erase error Interrupt source
 *   @arg  EFM_INT_RDCOLERR:            Read collide error Interrupt source
 * @param  [in] enNewState              The new state of specified interrupt.
 *  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_IntCmd(uint32_t u32EfmInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_EFM_INT_SEL(u32EfmInt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    if(Enable == enNewState)
    {
        SET_REG32_BIT(CM_EFM->FITE, u32EfmInt);
    }
    else
    {
        CLEAR_REG32_BIT(CM_EFM->FITE, u32EfmInt);
    }
}

/**
 * @brief  Checks whether the specified FLASH flag is set or not.
 * @param  [in] u32Flag                  Specifies the flash flag.
 *  This parameter can be one of the following values:
 *   @arg  EFM_FLAG_PEWERR:              Flash write protect error flag.
 *   @arg  EFM_FLAG_PEPRTERR:            Flash program protect area error flag.
 *   @arg  EFM_FLAG_PGMISMTCHERR:        Flash program miss match flag.
 *   @arg  EFM_FLAG_OPTEND:              Flash end of program flag.
 *   @arg  EFM_FLAG_COLERR:              Flash read write error flag.
 *   @arg  EFM_FLAG_RDY:                 Flash ready flag.
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Interrupt flag is set
 *           - Reset: Interrupt flag is reset
 */
en_flag_status_t EFM_GetStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_VALID_EFM_FLAG(u32Flag));
    return ((0UL == READ_REG32_BIT(CM_EFM->FSR, u32Flag)) ? Reset :Set);
}

/**
 * @brief  Clear the flag.
 * @param  [in] u32Flag                  Specifies the FLASH flag to clear.
 *  This parameter can be one of the following values:
 *   @arg  EFM_FLAG_PEWERR:              Clear Flash write protect error flag.
 *   @arg  EFM_FLAG_PEPRTERR:            Clear Flash program protect area error flag.
 *   @arg  EFM_FLAG_PGMISMTCH:           Clear Flash program miss match flag.
 *   @arg  EFM_FLAG_OPTEND:              Clear Flash end of program flag.
 *   @arg  EFM_FLAG_COLERR:              Clear Flash read write error flag.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_ClearStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_VALID_EFM_CLRFLAG(u32Flag));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    SET_REG32_BIT(CM_EFM->FSCLR, u32Flag);
}

/**
 * @brief  Set flash protect area.
 * @param  [in] u32StartAddr       Start address of protect area.
 * @param  [in] u32EndAddr         End address of protect area.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_SetWindowProtectAddr(uint32_t u32StartAddr, uint32_t u32EndAddr)
{
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32StartAddr));
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32EndAddr));
    /* Set protect area start address */
    WRITE_REG32(CM_EFM->FPMTSW, u32StartAddr);
    /* Set protect area end address */
    WRITE_REG32(CM_EFM->FPMTEW, u32EndAddr);
}

/**
 * @brief  Set bus state while flash program or erase.
 * @param  [in] u32Status          Specifies the new bus status while flash program or erase.
 *  This parameter can be one of the following values:
 *   @arg  EFM_BUS_BUSY            Bus busy while flash program or erase.
 *   @arg  EFM_BUS_RELEASE         Bus release while flash program or erase.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_SetBusStatus(uint32_t u32Status)
{
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_BUS_STATUS(u32Status));

    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_BUSHLDCTL, u32Status);
}

/**
 * @brief  Flash single program mode(word).
 * @param  [in] u32Addr            The specified program address.
 * @param  [in] u32Data            The specified program data.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - Error: program error
 *           - ErrorTimeout: program error timeout
 * @note  The address should be word align.
 *        Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_Program32(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t enRet = Ok;
    uint32_t u32Tmp;
    uint32_t u32Timeout = 0UL;

    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_ADDRESS_ALIGN_WORD(u32Addr));

    /* Clear the error flag. */
    EFM_ClearStatus(EFM_CLR_FLAG_MASK);
    /* Get chche status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Enable operate mode modified. */
    SET_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    /* Set single program mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_SINGLE);
    /* program data. */
    RW_MEM32(u32Addr) = (uint32_t)u32Data;
    while(Set != EFM_GetStatus(EFM_FLAG_RDY))
    {
        u32Timeout ++;
        if(u32Timeout >= EFM_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if(u32Data != RW_MEM32(u32Addr))
    {
        enRet = Error;
    }
    /* CLear the end of operate flag */
    EFM_ClearStatus(EFM_FLAG_OPTEND);
    /* Recover CACHE function */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_MASK, u32Tmp);
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Disable operate mode modified. */
    CLEAR_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    return enRet;
}

/**
 * @brief  Flash single program mode(half word).
 * @param  [in] u32Addr           The specified program address.
 * @param  [in] u16Data           The specified program data.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - Error: program error
 *           - ErrorTimeout: program error timeout
 * @note  The address should be half word align.
 *        Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_Program16(uint32_t u32Addr, uint16_t u16Data)
{
    en_result_t enRet = Ok;
    uint32_t u32Tmp;
    uint32_t u32Timeout = 0UL;

    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_ADDRESS_ALIGN_HALFWORD(u32Addr));

    /* Clear the error flag. */
    EFM_ClearStatus(EFM_CLR_FLAG_MASK);
    /* Get chche status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Enable operate mode modified. */
    SET_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    /* Set single program mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_SINGLE);
    /* program data. */
    RW_MEM16(u32Addr) = u16Data;
    while(Set != EFM_GetStatus(EFM_FLAG_RDY))
    {
        u32Timeout ++;
        if(u32Timeout >= EFM_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    /* CLear the end of operate flag */
    EFM_ClearStatus(EFM_FLAG_OPTEND);
    if(u16Data != RW_MEM16(u32Addr))
    {
        enRet = Error;
    }
    /* Recover CACHE function */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_MASK, u32Tmp);
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Disable operate mode modified. */
    CLEAR_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);

    return enRet;
}

/**
 * @brief  Flash single program with read back(word).
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Data                   The specified program data.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - Error: program error
 *           - ErrorTimeout: program error timeout
 * @note  The address should be half word align.
 *        Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_ProgramReadBack32(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t enRet = Ok;
    uint32_t u32Tmp;
    uint32_t u32Timeout = 0UL;

    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_ADDRESS_ALIGN_WORD(u32Addr));

    /* Clear the error flag. */
    EFM_ClearStatus(EFM_CLR_FLAG_MASK);
    /* Get chche status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Enable operate mode modified. */
    SET_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    /* Set program and read back mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_READBACK);
    /* program data. */
    RW_MEM32(u32Addr) = u32Data;

    while(Set != EFM_GetStatus(EFM_FLAG_RDY))
    {
        u32Timeout ++;
        if(u32Timeout >= EFM_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    /* CLear the end of operate flag */
    EFM_ClearStatus(EFM_FLAG_OPTEND);
    if(Set == EFM_GetStatus(EFM_FLAG_PGMISMTCHERR))
    {
        /* Clear flag PGMISMTCH */
        EFM_ClearStatus(EFM_FLAG_PGMISMTCHERR);
        enRet = Error;
    }
    /* Recover CACHE function */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_MASK, u32Tmp);
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Disable operate mode modified. */
    CLEAR_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);

    return enRet;
}

/**
 * @brief  Flash single program with read back(half word).
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u16Data                   The specified program data.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - Error: program error
 *           - ErrorTimeout: program error timeout
 * @note  The address should be half word align.
 *        Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_ProgramReadBack16(uint32_t u32Addr, uint16_t u16Data)
{
    en_result_t enRet = Ok;
    uint32_t u32Tmp;
    uint32_t u32Timeout = 0UL;

    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_ADDRESS_ALIGN_HALFWORD(u32Addr));

    /* Clear the error flag. */
    EFM_ClearStatus(EFM_CLR_FLAG_MASK);
    /* Get chche status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Enable operate mode modified. */
    SET_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    /* Set program and read back mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_READBACK);
    /* program data. */
    RW_MEM16(u32Addr) = u16Data;

    while(Set != EFM_GetStatus(EFM_FLAG_RDY))
    {
        u32Timeout ++;
        if(u32Timeout > EFM_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if(Set == EFM_GetStatus(EFM_FLAG_PGMISMTCHERR))
    {
        /* Clear flag PGMISMTCH */
        EFM_ClearStatus(EFM_FLAG_PGMISMTCHERR);
        enRet = Error;
    }
    /* CLear the end of operate flag */
    EFM_ClearStatus(EFM_FLAG_OPTEND);
    /* Recover CACHE function */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_MASK, u32Tmp);
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Disable operate mode modified. */
    CLEAR_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);

    return enRet;
}

/**
 * @brief  Flash sequence program(half word).
 * @param  [in] u32Addr            The specified program address.
 * @param  [in] u32Len             The length of specified program data.
 * @param  [in] pu16Buf            The pointer to specified program data.
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - ErrorInvalidParameter: invalid parameter
 *         - ErrorTimeout: program error timeout
 * @note  The address should be half word align.
 *        Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_SeqProgram16(uint32_t u32Addr, uint32_t u32Len, const uint16_t *pu16Buf)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout;
    uint32_t u32Tmp;
    uint32_t u32TempAddr = u32Addr;
    uint32_t u32pSrc = (uint32_t )pu16Buf;

    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_ADDRESS_ALIGN_HALFWORD(u32Addr));

    /* Clear the error flag. */
    EFM_ClearStatus(EFM_CLR_FLAG_MASK);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Enable operate mode modified. */
    SET_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    /* Set sequence program mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_SEQ);
    /* program data. */
    while(u32Len > 0UL)
    {
        RW_MEM16(u32TempAddr) = RW_MEM16(u32pSrc);
        u32TempAddr += 2U;
        u32pSrc += 2U;
        u32Timeout = 0UL;
        /* wait operate end. */
        while(Set != EFM_GetStatus(EFM_FLAG_OPTEND))
        {
            u32Timeout++;
            if (u32Timeout >= EFM_SEQ_PGM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        /* Clear end flag. */
        EFM_ClearStatus(EFM_FLAG_OPTEND);
        if (enRet != Ok)
        {
            break;
        }
        u32Len--;
    }
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Disable operate mode modified. */
    CLEAR_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    u32Timeout = 0UL;
    while(Set != EFM_GetStatus(EFM_FLAG_RDY))
    {
        u32Timeout ++;
        if(u32Timeout > EFM_SEQ_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    /* Clear the end of operate flag */
    EFM_ClearStatus(EFM_FLAG_OPTEND);
    /* Recover CACHE */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_MASK, u32Tmp);

    return enRet;
}

/**
 * @brief  Flash sequence program(word).
 * @param  [in] u32Addr            The specified program address.
 * @param  [in] u32Len             The length of specified program data.
 * @param  [in] pu32Buf            The pointer to specified program data.
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - ErrorInvalidParameter: invalid parameter
 *         - ErrorTimeout: program error timeout
 * @note  The address should be half word align.
 *        Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_SeqProgram32(uint32_t u32Addr, uint32_t u32Len, const uint32_t *pu32Buf)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout;
    uint32_t u32Tmp;
    uint32_t u32TempAddr = u32Addr;
    uint32_t u32pSrc = (uint32_t )pu32Buf;

    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_ADDRESS_ALIGN_HALFWORD(u32Addr));

    /* Clear the error flag. */
    EFM_ClearStatus(EFM_CLR_FLAG_MASK);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Enable operate mode modified. */
    SET_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    /* Set sequence program mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_SEQ);
    /* program data. */
    while(u32Len > 0UL)
    {
        RW_MEM32(u32TempAddr) = RW_MEM32(u32pSrc);
        u32TempAddr += 4U;
        u32pSrc += 4U;
        u32Timeout = 0UL;
        /* wait operate end. */
        while(Set != EFM_GetStatus(EFM_FLAG_OPTEND))
        {
            u32Timeout++;
            if (u32Timeout >= EFM_SEQ_PGM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        /* Clear end flag. */
        EFM_ClearStatus(EFM_FLAG_OPTEND);
        if (enRet != Ok)
        {
            break;
        }
        u32Len--;
    }
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Disable operate mode modified. */
    CLEAR_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    u32Timeout = 0UL;
    while(Set != EFM_GetStatus(EFM_FLAG_RDY))
    {
        u32Timeout ++;
        if(u32Timeout > EFM_SEQ_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    /* Clear the end of operate flag */
    EFM_ClearStatus(EFM_FLAG_OPTEND);
    /* Recover CACHE */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_MASK, u32Tmp);

    return enRet;
}

/**
 * @brief  Flash sector erase.
 * @param  [in] u32Addr                   The address in the specified sector.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - ErrorTimeout: program error timeout
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_SectorErase(uint32_t u32Addr)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout = 0UL;
    uint32_t u32Tmp;

    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));

    /* Clear the error flag. */
    EFM_ClearStatus(EFM_CLR_FLAG_MASK);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Enable operate mode modified. */
    SET_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    /* Set sector erase mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_ERASE_SECT);
    RW_MEM32(u32Addr & 0xFFFFFFFCUL) = (uint32_t)0x0UL;
    while(Set != EFM_GetStatus(EFM_FLAG_RDY))
    {
        u32Timeout ++;
        if(u32Timeout >= EFM_ERASE_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    /* Clear the end of operate flag */
    EFM_ClearStatus(EFM_FLAG_OPTEND);
    /* Recover CACHE */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_MASK, u32Tmp);
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Disable operate mode modified. */
    CLEAR_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);

    return enRet;
}

/**
 * @brief  Flash chip erase.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - ErrorTimeout: program error timeout
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_ChipErase(void)
{
    en_result_t enRet = Ok;
    uint32_t u32Tmp;
    uint32_t u32Timeout = 0UL;

    /* Clear the error flag. */
    EFM_ClearStatus(EFM_CLR_FLAG_MASK);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_MASK);
    /* Enable operate mode modified. */
    SET_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);
    /* Set sector erase mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_ERASE_CHIP);
    RW_MEM32(EFM_ADRR_SECT20) = 0x0UL;

    while(Set != EFM_GetStatus(EFM_FLAG_RDY))
    {
        u32Timeout ++;
        if(u32Timeout >= EFM_ERASE_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    /* Clear the end of operate flag */
    EFM_ClearStatus(EFM_FLAG_OPTEND);
    /* Recover CACHE */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_MASK, u32Tmp);
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Disable operate mode modified. */
    CLEAR_REG32_BIT(CM_EFM->FWMC, EFM_FWMC_PEMODE);

    return enRet;
}

/**
 * @brief  Read unique ID.
 * @param  [out] stcUID      Get the unique ID
 * @retval An en_result_t enumeration value:
 *         - Ok: Get success
 *         - ErrorInvalidParameter: Invalid parameter
 */
en_result_t EFM_GetUID(stc_efm_unique_id_t *stcUID)
{
    en_result_t enRet = ErrorInvalidParameter;
    if (stcUID != NULL)
    {
        stcUID->u32UniqueID0 = READ_REG32(CM_EFM->UQID0);
        stcUID->u32UniqueID1 = READ_REG32(CM_EFM->UQID1);
        stcUID->u32UniqueID2 = READ_REG32(CM_EFM->UQID2);
        stcUID->u32UniqueID3 = READ_REG32(CM_EFM->UQID3);
        enRet = Ok;
    }
    return enRet;
}

/**
 * @}
 */

#endif  /* DDL_EFM_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
