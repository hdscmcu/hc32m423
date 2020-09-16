/**
 *******************************************************************************
 * @file  hc32m423_efm.h
 * @brief This file contains all the functions prototypes of the EFM driver
 *        library.
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
#ifndef __HC32M423_EFM_H__
#define __HC32M423_EFM_H__

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
 * @addtogroup DDL_EFM
 * @{
 */

#if (DDL_EFM_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EFM_Global_Types EFM Global Types
 * @{
 */

/**
 * @brief EFM configure structure
 */
typedef struct
{
    uint32_t            u32WaitCycle;   /*!< Specifies the efm read wait cycles.
                                            This parameter can be a value of @ref EFM_Wait_Cycle.              */

    uint32_t            u32CacheReset;  /*!< Specifies the cache data reset on or off.
                                            This parameter can be a value of @ref EFM_CacheRst_Func.       */

    uint32_t            u32InstrCache;  /*!< Specifies the instruction cache on or off.
                                            This parameter can be a value of @ref EFM_InstrCache_Func.       */

    uint32_t            u32DataCache;   /*!< Specifies the data cache on or off.
                                            This parameter can be a value of @ref EFM_DataCache_Func.        */

    uint32_t            u32BusStatus;   /*!< Specifies the bus status busy or release while program & erase.
                                            This parameter can be a value of @ref EFM_Bus_Status.            */
} stc_efm_init_t;

/**
 * @brief EFM unique ID definition
 */
typedef struct
{
    uint32_t            u32UniqueID0;      /*!< unique ID 0.       */
    uint32_t            u32UniqueID1;      /*!< unique ID 1.       */
    uint32_t            u32UniqueID2;      /*!< unique ID 2.       */
    uint32_t            u32UniqueID3;      /*!< unique ID 3.       */
} stc_efm_unique_id_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EFM_Global_Macros EFM Global Macros
 * @{
 */

/**
 * @defgroup EFM_Address EFM address area
 * @{
 */
#define EFM_START_ADDR              (0x00000000UL)  /*!< Flash start address */
#define EFM_END_ADDR                (0x0001FFFFUL)  /*!< Flash end address */
/**
 * @}
 */

/**
 * @defgroup EFM_Sector_Address EFM Sector Address
 * @{
 */
#define EFM_ADRR_SECT0            (0x00000000UL)   /*!< Sector 0 */
#define EFM_ADRR_SECT1            (0x00000200UL)   /*!< Sector 1 */
#define EFM_ADRR_SECT2            (0x00000400UL)   /*!< Sector 2 */
#define EFM_ADRR_SECT3            (0x00000600UL)   /*!< Sector 3 */
#define EFM_ADRR_SECT4            (0x00000800UL)   /*!< Sector 4 */
#define EFM_ADRR_SECT5            (0x00000A00UL)   /*!< Sector 5 */
#define EFM_ADRR_SECT6            (0x00000C00UL)   /*!< Sector 6 */
#define EFM_ADRR_SECT7            (0x00000E00UL)   /*!< Sector 7 */
#define EFM_ADRR_SECT8            (0x00001000UL)   /*!< Sector 8 */
#define EFM_ADRR_SECT9            (0x00001200UL)   /*!< Sector 9 */
#define EFM_ADRR_SECT10           (0x00001400UL)   /*!< Sector 10 */
#define EFM_ADRR_SECT11           (0x00001600UL)   /*!< Sector 11 */
#define EFM_ADRR_SECT12           (0x00001800UL)   /*!< Sector 12 */
#define EFM_ADRR_SECT13           (0x00001A00UL)   /*!< Sector 13 */
#define EFM_ADRR_SECT14           (0x00001C00UL)   /*!< Sector 14 */
#define EFM_ADRR_SECT15           (0x00001E00UL)   /*!< Sector 15 */
#define EFM_ADRR_SECT16           (0x00002000UL)   /*!< Sector 16 */
#define EFM_ADRR_SECT17           (0x00002200UL)   /*!< Sector 17 */
#define EFM_ADRR_SECT18           (0x00002400UL)   /*!< Sector 18 */
#define EFM_ADRR_SECT19           (0x00002600UL)   /*!< Sector 19 */
#define EFM_ADRR_SECT20           (0x00002800UL)   /*!< Sector 20 */
#define EFM_ADRR_SECT21           (0x00002A00UL)   /*!< Sector 21 */
#define EFM_ADRR_SECT22           (0x00002C00UL)   /*!< Sector 22 */
#define EFM_ADRR_SECT23           (0x00002E00UL)   /*!< Sector 23 */
#define EFM_ADRR_SECT24           (0x00003000UL)   /*!< Sector 24 */
#define EFM_ADRR_SECT25           (0x00003200UL)   /*!< Sector 25 */
#define EFM_ADRR_SECT26           (0x00003400UL)   /*!< Sector 26 */
#define EFM_ADRR_SECT27           (0x00003600UL)   /*!< Sector 27 */
#define EFM_ADRR_SECT28           (0x00003800UL)   /*!< Sector 28 */
#define EFM_ADRR_SECT29           (0x00003A00UL)   /*!< Sector 29 */
#define EFM_ADRR_SECT30           (0x00003C00UL)   /*!< Sector 30 */
#define EFM_ADRR_SECT31           (0x00003E00UL)   /*!< Sector 31 */
#define EFM_ADRR_SECT32           (0x00004000UL)   /*!< Sector 32 */
#define EFM_ADRR_SECT33           (0x00004200UL)   /*!< Sector 33 */
#define EFM_ADRR_SECT34           (0x00004400UL)   /*!< Sector 34 */
#define EFM_ADRR_SECT35           (0x00004600UL)   /*!< Sector 35 */
#define EFM_ADRR_SECT36           (0x00004800UL)   /*!< Sector 36 */
#define EFM_ADRR_SECT37           (0x00004A00UL)   /*!< Sector 37 */
#define EFM_ADRR_SECT38           (0x00004C00UL)   /*!< Sector 38 */
#define EFM_ADRR_SECT39           (0x00004E00UL)   /*!< Sector 39 */
#define EFM_ADRR_SECT40           (0x00005000UL)   /*!< Sector 40 */
#define EFM_ADRR_SECT41           (0x00005200UL)   /*!< Sector 41 */
#define EFM_ADRR_SECT42           (0x00005400UL)   /*!< Sector 42 */
#define EFM_ADRR_SECT43           (0x00005600UL)   /*!< Sector 43 */
#define EFM_ADRR_SECT44           (0x00005800UL)   /*!< Sector 44 */
#define EFM_ADRR_SECT45           (0x00005A00UL)   /*!< Sector 45 */
#define EFM_ADRR_SECT46           (0x00005C00UL)   /*!< Sector 46 */
#define EFM_ADRR_SECT47           (0x00005E00UL)   /*!< Sector 47 */
#define EFM_ADRR_SECT48           (0x00006000UL)   /*!< Sector 48 */
#define EFM_ADRR_SECT49           (0x00006200UL)   /*!< Sector 49 */
#define EFM_ADRR_SECT50           (0x00006400UL)   /*!< Sector 50 */
#define EFM_ADRR_SECT51           (0x00006600UL)   /*!< Sector 51 */
#define EFM_ADRR_SECT52           (0x00006800UL)   /*!< Sector 52 */
#define EFM_ADRR_SECT53           (0x00006A00UL)   /*!< Sector 53 */
#define EFM_ADRR_SECT54           (0x00006C00UL)   /*!< Sector 54 */
#define EFM_ADRR_SECT55           (0x00006E00UL)   /*!< Sector 55 */
#define EFM_ADRR_SECT56           (0x00007000UL)   /*!< Sector 56 */
#define EFM_ADRR_SECT57           (0x00007200UL)   /*!< Sector 57 */
#define EFM_ADRR_SECT58           (0x00007400UL)   /*!< Sector 58 */
#define EFM_ADRR_SECT59           (0x00007600UL)   /*!< Sector 59 */
#define EFM_ADRR_SECT60           (0x00007800UL)   /*!< Sector 60 */
#define EFM_ADRR_SECT61           (0x00007A00UL)   /*!< Sector 61 */
#define EFM_ADRR_SECT62           (0x00007C00UL)   /*!< Sector 62 */
#define EFM_ADRR_SECT63           (0x00007E00UL)   /*!< Sector 63 */
#define EFM_ADRR_SECT64           (0x00008000UL)   /*!< Sector 64 */
#define EFM_ADRR_SECT65           (0x00008200UL)   /*!< Sector 65 */
#define EFM_ADRR_SECT66           (0x00008400UL)   /*!< Sector 66 */
#define EFM_ADRR_SECT67           (0x00008600UL)   /*!< Sector 67 */
#define EFM_ADRR_SECT68           (0x00008800UL)   /*!< Sector 68 */
#define EFM_ADRR_SECT69           (0x00008A00UL)   /*!< Sector 69 */
#define EFM_ADRR_SECT70           (0x00008C00UL)   /*!< Sector 70 */
#define EFM_ADRR_SECT71           (0x00008E00UL)   /*!< Sector 71 */
#define EFM_ADRR_SECT72           (0x00009000UL)   /*!< Sector 72 */
#define EFM_ADRR_SECT73           (0x00009200UL)   /*!< Sector 73 */
#define EFM_ADRR_SECT74           (0x00009400UL)   /*!< Sector 74 */
#define EFM_ADRR_SECT75           (0x00009600UL)   /*!< Sector 75 */
#define EFM_ADRR_SECT76           (0x00009800UL)   /*!< Sector 76 */
#define EFM_ADRR_SECT77           (0x00009A00UL)   /*!< Sector 77 */
#define EFM_ADRR_SECT78           (0x00009C00UL)   /*!< Sector 78 */
#define EFM_ADRR_SECT79           (0x00009E00UL)   /*!< Sector 79 */
#define EFM_ADRR_SECT80           (0x0000A000UL)   /*!< Sector 80 */
#define EFM_ADRR_SECT81           (0x0000A200UL)   /*!< Sector 81 */
#define EFM_ADRR_SECT82           (0x0000A400UL)   /*!< Sector 82 */
#define EFM_ADRR_SECT83           (0x0000A600UL)   /*!< Sector 83 */
#define EFM_ADRR_SECT84           (0x0000A800UL)   /*!< Sector 84 */
#define EFM_ADRR_SECT85           (0x0000AA00UL)   /*!< Sector 85 */
#define EFM_ADRR_SECT86           (0x0000AC00UL)   /*!< Sector 86 */
#define EFM_ADRR_SECT87           (0x0000AE00UL)   /*!< Sector 87 */
#define EFM_ADRR_SECT88           (0x0000B000UL)   /*!< Sector 88 */
#define EFM_ADRR_SECT89           (0x0000B200UL)   /*!< Sector 89 */
#define EFM_ADRR_SECT90           (0x0000B400UL)   /*!< Sector 90 */
#define EFM_ADRR_SECT91           (0x0000B600UL)   /*!< Sector 91 */
#define EFM_ADRR_SECT92           (0x0000B800UL)   /*!< Sector 92 */
#define EFM_ADRR_SECT93           (0x0000BA00UL)   /*!< Sector 93 */
#define EFM_ADRR_SECT94           (0x0000BC00UL)   /*!< Sector 94 */
#define EFM_ADRR_SECT95           (0x0000BE00UL)   /*!< Sector 95 */
#define EFM_ADRR_SECT96           (0x0000C000UL)   /*!< Sector 96 */
#define EFM_ADRR_SECT97           (0x0000C200UL)   /*!< Sector 97 */
#define EFM_ADRR_SECT98           (0x0000C400UL)   /*!< Sector 98 */
#define EFM_ADRR_SECT99           (0x0000C600UL)   /*!< Sector 99 */
#define EFM_ADRR_SECT100          (0x0000C800UL)   /*!< Sector 100 */
#define EFM_ADRR_SECT101          (0x0000CA00UL)   /*!< Sector 101 */
#define EFM_ADRR_SECT102          (0x0000CC00UL)   /*!< Sector 102 */
#define EFM_ADRR_SECT103          (0x0000CE00UL)   /*!< Sector 103 */
#define EFM_ADRR_SECT104          (0x0000D000UL)   /*!< Sector 104 */
#define EFM_ADRR_SECT105          (0x0000D200UL)   /*!< Sector 105 */
#define EFM_ADRR_SECT106          (0x0000D400UL)   /*!< Sector 106 */
#define EFM_ADRR_SECT107          (0x0000D600UL)   /*!< Sector 107 */
#define EFM_ADRR_SECT108          (0x0000D800UL)   /*!< Sector 108 */
#define EFM_ADRR_SECT109          (0x0000DA00UL)   /*!< Sector 109 */
#define EFM_ADRR_SECT110          (0x0000DC00UL)   /*!< Sector 110 */
#define EFM_ADRR_SECT111          (0x0000DE00UL)   /*!< Sector 111 */
#define EFM_ADRR_SECT112          (0x0000E000UL)   /*!< Sector 112 */
#define EFM_ADRR_SECT113          (0x0000E200UL)   /*!< Sector 113 */
#define EFM_ADRR_SECT114          (0x0000E400UL)   /*!< Sector 114 */
#define EFM_ADRR_SECT115          (0x0000E600UL)   /*!< Sector 115 */
#define EFM_ADRR_SECT116          (0x0000E800UL)   /*!< Sector 116 */
#define EFM_ADRR_SECT117          (0x0000EA00UL)   /*!< Sector 117 */
#define EFM_ADRR_SECT118          (0x0000EC00UL)   /*!< Sector 118 */
#define EFM_ADRR_SECT119          (0x0000EE00UL)   /*!< Sector 119 */
#define EFM_ADRR_SECT120          (0x0000F000UL)   /*!< Sector 120 */
#define EFM_ADRR_SECT121          (0x0000F200UL)   /*!< Sector 121 */
#define EFM_ADRR_SECT122          (0x0000F400UL)   /*!< Sector 122 */
#define EFM_ADRR_SECT123          (0x0000F600UL)   /*!< Sector 123 */
#define EFM_ADRR_SECT124          (0x0000F800UL)   /*!< Sector 124 */
#define EFM_ADRR_SECT125          (0x0000FA00UL)   /*!< Sector 125 */
#define EFM_ADRR_SECT126          (0x0000FC00UL)   /*!< Sector 126 */
#define EFM_ADRR_SECT127          (0x0000FE00UL)   /*!< Sector 127 */
#define EFM_ADRR_SECT128          (0x00010000UL)   /*!< Sector 128 */
#define EFM_ADRR_SECT129          (0x00010200UL)   /*!< Sector 129 */
#define EFM_ADRR_SECT130          (0x00010400UL)   /*!< Sector 130 */
#define EFM_ADRR_SECT131          (0x00010600UL)   /*!< Sector 131 */
#define EFM_ADRR_SECT132          (0x00010800UL)   /*!< Sector 132 */
#define EFM_ADRR_SECT133          (0x00010A00UL)   /*!< Sector 133 */
#define EFM_ADRR_SECT134          (0x00010C00UL)   /*!< Sector 134 */
#define EFM_ADRR_SECT135          (0x00010E00UL)   /*!< Sector 135 */
#define EFM_ADRR_SECT136          (0x00011000UL)   /*!< Sector 136 */
#define EFM_ADRR_SECT137          (0x00011200UL)   /*!< Sector 137 */
#define EFM_ADRR_SECT138          (0x00011400UL)   /*!< Sector 138 */
#define EFM_ADRR_SECT139          (0x00011600UL)   /*!< Sector 139 */
#define EFM_ADRR_SECT140          (0x00011800UL)   /*!< Sector 140 */
#define EFM_ADRR_SECT141          (0x00011A00UL)   /*!< Sector 141 */
#define EFM_ADRR_SECT142          (0x00011C00UL)   /*!< Sector 142 */
#define EFM_ADRR_SECT143          (0x00011E00UL)   /*!< Sector 143 */
#define EFM_ADRR_SECT144          (0x00012000UL)   /*!< Sector 144 */
#define EFM_ADRR_SECT145          (0x00012200UL)   /*!< Sector 145 */
#define EFM_ADRR_SECT146          (0x00012400UL)   /*!< Sector 146 */
#define EFM_ADRR_SECT147          (0x00012600UL)   /*!< Sector 147 */
#define EFM_ADRR_SECT148          (0x00012800UL)   /*!< Sector 148 */
#define EFM_ADRR_SECT149          (0x00012A00UL)   /*!< Sector 149 */
#define EFM_ADRR_SECT150          (0x00012C00UL)   /*!< Sector 150 */
#define EFM_ADRR_SECT151          (0x00012E00UL)   /*!< Sector 151 */
#define EFM_ADRR_SECT152          (0x00013000UL)   /*!< Sector 152 */
#define EFM_ADRR_SECT153          (0x00013200UL)   /*!< Sector 153 */
#define EFM_ADRR_SECT154          (0x00013400UL)   /*!< Sector 154 */
#define EFM_ADRR_SECT155          (0x00013600UL)   /*!< Sector 155 */
#define EFM_ADRR_SECT156          (0x00013800UL)   /*!< Sector 156 */
#define EFM_ADRR_SECT157          (0x00013A00UL)   /*!< Sector 157 */
#define EFM_ADRR_SECT158          (0x00013C00UL)   /*!< Sector 158 */
#define EFM_ADRR_SECT159          (0x00013E00UL)   /*!< Sector 159 */
#define EFM_ADRR_SECT160          (0x00014000UL)   /*!< Sector 160 */
#define EFM_ADRR_SECT161          (0x00014200UL)   /*!< Sector 161 */
#define EFM_ADRR_SECT162          (0x00014400UL)   /*!< Sector 162 */
#define EFM_ADRR_SECT163          (0x00014600UL)   /*!< Sector 163 */
#define EFM_ADRR_SECT164          (0x00014800UL)   /*!< Sector 164 */
#define EFM_ADRR_SECT165          (0x00014A00UL)   /*!< Sector 165 */
#define EFM_ADRR_SECT166          (0x00014C00UL)   /*!< Sector 166 */
#define EFM_ADRR_SECT167          (0x00014E00UL)   /*!< Sector 167 */
#define EFM_ADRR_SECT168          (0x00015000UL)   /*!< Sector 168 */
#define EFM_ADRR_SECT169          (0x00015200UL)   /*!< Sector 169 */
#define EFM_ADRR_SECT170          (0x00015400UL)   /*!< Sector 170 */
#define EFM_ADRR_SECT171          (0x00015600UL)   /*!< Sector 171 */
#define EFM_ADRR_SECT172          (0x00015800UL)   /*!< Sector 172 */
#define EFM_ADRR_SECT173          (0x00015A00UL)   /*!< Sector 173 */
#define EFM_ADRR_SECT174          (0x00015C00UL)   /*!< Sector 174 */
#define EFM_ADRR_SECT175          (0x00015E00UL)   /*!< Sector 175 */
#define EFM_ADRR_SECT176          (0x00016000UL)   /*!< Sector 176 */
#define EFM_ADRR_SECT177          (0x00016200UL)   /*!< Sector 177 */
#define EFM_ADRR_SECT178          (0x00016400UL)   /*!< Sector 178 */
#define EFM_ADRR_SECT179          (0x00016600UL)   /*!< Sector 179 */
#define EFM_ADRR_SECT180          (0x00016800UL)   /*!< Sector 180 */
#define EFM_ADRR_SECT181          (0x00016A00UL)   /*!< Sector 181 */
#define EFM_ADRR_SECT182          (0x00016C00UL)   /*!< Sector 182 */
#define EFM_ADRR_SECT183          (0x00016E00UL)   /*!< Sector 183 */
#define EFM_ADRR_SECT184          (0x00017000UL)   /*!< Sector 184 */
#define EFM_ADRR_SECT185          (0x00017200UL)   /*!< Sector 185 */
#define EFM_ADRR_SECT186          (0x00017400UL)   /*!< Sector 186 */
#define EFM_ADRR_SECT187          (0x00017600UL)   /*!< Sector 187 */
#define EFM_ADRR_SECT188          (0x00017800UL)   /*!< Sector 188 */
#define EFM_ADRR_SECT189          (0x00017A00UL)   /*!< Sector 189 */
#define EFM_ADRR_SECT190          (0x00017C00UL)   /*!< Sector 190 */
#define EFM_ADRR_SECT191          (0x00017E00UL)   /*!< Sector 191 */
#define EFM_ADRR_SECT192          (0x00018000UL)   /*!< Sector 192 */
#define EFM_ADRR_SECT193          (0x00018200UL)   /*!< Sector 193 */
#define EFM_ADRR_SECT194          (0x00018400UL)   /*!< Sector 194 */
#define EFM_ADRR_SECT195          (0x00018600UL)   /*!< Sector 195 */
#define EFM_ADRR_SECT196          (0x00018800UL)   /*!< Sector 196 */
#define EFM_ADRR_SECT197          (0x00018A00UL)   /*!< Sector 197 */
#define EFM_ADRR_SECT198          (0x00018C00UL)   /*!< Sector 198 */
#define EFM_ADRR_SECT199          (0x00018E00UL)   /*!< Sector 199 */
#define EFM_ADRR_SECT200          (0x00019000UL)   /*!< Sector 200 */
#define EFM_ADRR_SECT201          (0x00019200UL)   /*!< Sector 201 */
#define EFM_ADRR_SECT202          (0x00019400UL)   /*!< Sector 202 */
#define EFM_ADRR_SECT203          (0x00019600UL)   /*!< Sector 203 */
#define EFM_ADRR_SECT204          (0x00019800UL)   /*!< Sector 204 */
#define EFM_ADRR_SECT205          (0x00019A00UL)   /*!< Sector 205 */
#define EFM_ADRR_SECT206          (0x00019C00UL)   /*!< Sector 206 */
#define EFM_ADRR_SECT207          (0x00019E00UL)   /*!< Sector 207 */
#define EFM_ADRR_SECT208          (0x0001A000UL)   /*!< Sector 208 */
#define EFM_ADRR_SECT209          (0x0001A200UL)   /*!< Sector 209 */
#define EFM_ADRR_SECT210          (0x0001A400UL)   /*!< Sector 210 */
#define EFM_ADRR_SECT211          (0x0001A600UL)   /*!< Sector 211 */
#define EFM_ADRR_SECT212          (0x0001A800UL)   /*!< Sector 212 */
#define EFM_ADRR_SECT213          (0x0001AA00UL)   /*!< Sector 213 */
#define EFM_ADRR_SECT214          (0x0001AC00UL)   /*!< Sector 214 */
#define EFM_ADRR_SECT215          (0x0001AE00UL)   /*!< Sector 215 */
#define EFM_ADRR_SECT216          (0x0001B000UL)   /*!< Sector 216 */
#define EFM_ADRR_SECT217          (0x0001B200UL)   /*!< Sector 217 */
#define EFM_ADRR_SECT218          (0x0001B400UL)   /*!< Sector 218 */
#define EFM_ADRR_SECT219          (0x0001B600UL)   /*!< Sector 219 */
#define EFM_ADRR_SECT220          (0x0001B800UL)   /*!< Sector 220 */
#define EFM_ADRR_SECT221          (0x0001BA00UL)   /*!< Sector 221 */
#define EFM_ADRR_SECT222          (0x0001BC00UL)   /*!< Sector 222 */
#define EFM_ADRR_SECT223          (0x0001BE00UL)   /*!< Sector 223 */
#define EFM_ADRR_SECT224          (0x0001C000UL)   /*!< Sector 224 */
#define EFM_ADRR_SECT225          (0x0001C200UL)   /*!< Sector 225 */
#define EFM_ADRR_SECT226          (0x0001C400UL)   /*!< Sector 226 */
#define EFM_ADRR_SECT227          (0x0001C600UL)   /*!< Sector 227 */
#define EFM_ADRR_SECT228          (0x0001C800UL)   /*!< Sector 228 */
#define EFM_ADRR_SECT229          (0x0001CA00UL)   /*!< Sector 229 */
#define EFM_ADRR_SECT230          (0x0001CC00UL)   /*!< Sector 230 */
#define EFM_ADRR_SECT231          (0x0001CE00UL)   /*!< Sector 231 */
#define EFM_ADRR_SECT232          (0x0001D000UL)   /*!< Sector 232 */
#define EFM_ADRR_SECT233          (0x0001D200UL)   /*!< Sector 233 */
#define EFM_ADRR_SECT234          (0x0001D400UL)   /*!< Sector 234 */
#define EFM_ADRR_SECT235          (0x0001D600UL)   /*!< Sector 235 */
#define EFM_ADRR_SECT236          (0x0001D800UL)   /*!< Sector 236 */
#define EFM_ADRR_SECT237          (0x0001DA00UL)   /*!< Sector 237 */
#define EFM_ADRR_SECT238          (0x0001DC00UL)   /*!< Sector 238 */
#define EFM_ADRR_SECT239          (0x0001DE00UL)   /*!< Sector 239 */
#define EFM_ADRR_SECT240          (0x0001E000UL)   /*!< Sector 240 */
#define EFM_ADRR_SECT241          (0x0001E200UL)   /*!< Sector 241 */
#define EFM_ADRR_SECT242          (0x0001E400UL)   /*!< Sector 242 */
#define EFM_ADRR_SECT243          (0x0001E600UL)   /*!< Sector 243 */
#define EFM_ADRR_SECT244          (0x0001E800UL)   /*!< Sector 244 */
#define EFM_ADRR_SECT245          (0x0001EA00UL)   /*!< Sector 245 */
#define EFM_ADRR_SECT246          (0x0001EC00UL)   /*!< Sector 246 */
#define EFM_ADRR_SECT247          (0x0001EE00UL)   /*!< Sector 247 */
#define EFM_ADRR_SECT248          (0x0001F000UL)   /*!< Sector 248 */
#define EFM_ADRR_SECT249          (0x0001F200UL)   /*!< Sector 249 */
#define EFM_ADRR_SECT250          (0x0001F400UL)   /*!< Sector 250 */
#define EFM_ADRR_SECT251          (0x0001F600UL)   /*!< Sector 251 */
#define EFM_ADRR_SECT252          (0x0001F800UL)   /*!< Sector 252 */
#define EFM_ADRR_SECT253          (0x0001FA00UL)   /*!< Sector 253 */
#define EFM_ADRR_SECT254          (0x0001FC00UL)   /*!< Sector 254 */
#define EFM_ADRR_SECT255          (0x0001FE00UL)   /*!< Sector 255 */
/**
 * @}
 */

/**
 * @defgroup EFM_Wait_Cycle EFM Wait Cycle
 * @{
 */
#define EFM_WAIT_CYCLE0            (0x00000000UL)   /*!< Don't insert read wait cycle */
#define EFM_WAIT_CYCLE1            (0x00000001UL)   /*!< Insert 1 read wait cycles */
#define EFM_WAIT_CYCLE2            (0x00000002UL)   /*!< Insert 2 read wait cycles */
#define EFM_WAIT_CYCLE3            (0x00000003UL)   /*!< Insert 3 read wait cycles */
#define EFM_WAIT_CYCLE4            (0x00000004UL)   /*!< Insert 4 read wait cycles */
#define EFM_WAIT_CYCLE5            (0x00000005UL)   /*!< Insert 5 read wait cycles */
#define EFM_WAIT_CYCLE6            (0x00000006UL)   /*!< Insert 6 read wait cycles */
#define EFM_WAIT_CYCLE7            (0x00000007UL)   /*!< Insert 7 read wait cycles */
/**
 * @}
 */

/**
 * @defgroup EFM_CacheRst_Func EFM cache data reset function
 * @{
 */
#define EFM_CACHE_RST_ON           (EFM_FRMC_CRST)  /*!< Enable cache data reset function */
#define EFM_CACHE_RST_OFF          (0x00000000UL)   /*!< Disable cache data reset function */
/**
 * @}
 */

/**
 * @defgroup EFM_InstrCache_Func EFM instruction cache function
 * @{
 */
#define EFM_INSTR_CACHE_ON         (EFM_FRMC_ICHE)  /*!< Enable instruction cache function */
#define EFM_INSTR_CACHE_OFF        (0x00000000UL)   /*!< Disable instruction cache function */
/**
 * @}
 */

/**
 * @defgroup EFM_DataCache_Func EFM data cache function
 * @{
 */
#define EFM_DATA_CACHE_ON          (EFM_FRMC_DCHE)  /*!< Enable data cache function */
#define EFM_DATA_CACHE_OFF         (0x00000000UL)   /*!< Disable data cache function */
/**
 * @}
 */

/**
 * @defgroup EFM_Bus_Status EFM Bus status while flash program or erase
 * @{
 */
#define EFM_BUS_BUSY               (0x00000000UL)       /*!< Bus busy while flash program or erase */
#define EFM_BUS_RELEASE            (EFM_FWMC_BUSHLDCTL) /*!< Bus release while flash program or erase */
/**
 * @}
 */

/**
 * @defgroup EFM_Mode EFM program or erase mode definition
 * @{
 */
#define EFM_MD_PGM_SINGLE          (0x00000010UL)       /*!< Program single mode */
#define EFM_MD_PGM_READBACK        (0x00000020UL)       /*!< Program and read back mode */
#define EFM_MD_PGM_SEQ             (0x00000030UL)       /*!< Program sequence mode */
#define EFM_MD_ERASE_SECT          (0x00000040UL)       /*!< Sector erase */
#define EFM_MD_ERASE_CHIP          (0x00000050UL)       /*!< Chip erase */
#define EFM_MD_READONLY            (0x00000000UL)       /*!< Read only */
/**
 * @}
 */

/**
 * @defgroup EFM_Flag EFM Flag definition
 * @{
 */
#define EFM_FLAG_PEWERR            (EFM_FSR_PEWERR)     /*!< EFM Programming/erase error flag.              */
#define EFM_FLAG_PEPRTERR          (EFM_FSR_PEPRTERR)   /*!< EFM Programming/erase protect area error flag. */
#define EFM_FLAG_PGMISMTCHERR      (EFM_FSR_PGMISMTCH)  /*!< EFM Programming miss match error flag         */
#define EFM_FLAG_OPTEND            (EFM_FSR_OPTEND)     /*!< EFM End of Operation flag.                     */
#define EFM_FLAG_COLERR            (EFM_FSR_RDCOLERR)   /*!< EFM Read collide error flag.                   */
#define EFM_FLAG_RDY               (EFM_FSR_RDY)        /*!< EFM ready flag.                                */
/**
 * @}
 */

/**
 * @defgroup EFM_Interrupt_definition EFM Interrupt definition
 * @{
 */
#define EFM_INT_EOP                (EFM_FITE_OPTENDITE)      /*!< End of EFM operation Interrupt      */
#define EFM_INT_PEERR              (EFM_FITE_PEERRITE)       /*!< Program/erase error Interrupt       */
#define EFM_INT_RDCOLERR           (EFM_FITE_RDCOLERRITE)    /*!< Read collide error Interrupt        */
/**
 * @}
 */

/**
 * @defgroup EFM_Keys EFM Keys
 * @{
 */
#define EFM_KEY1                   (0x0123U)
#define EFM_KEY2                   (0x3210U)
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
 * @addtogroup EFM_Global_Functions
 * @{
 */

/**
 * @brief  EFM Protect Unlock.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EFM_Unlock(void)
{
    WRITE_REG32(CM_EFM->FAPRT, EFM_KEY1);
    WRITE_REG32(CM_EFM->FAPRT, EFM_KEY2);
}

/**
 * @brief  EFM Protect Lock.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EFM_Lock(void)
{
    WRITE_REG32(CM_EFM->FAPRT, 0x12345678UL);
}

void EFM_Cmd(en_functional_state_t enNewState);
void EFM_SetWaitCycle(uint32_t u32WaitCycle);
void EFM_SetBusStatus(uint32_t u32Status);
void EFM_DataCacheCmd(en_functional_state_t enNewState);
void EFM_CacheDataResetCmd(en_functional_state_t enNewState);
void EFM_InstrCacheCmd(en_functional_state_t enNewState);
void EFM_SetWindowProtectAddr(uint32_t u32StartAddr, uint32_t u32EndAddr);
void EFM_IntCmd(uint32_t u32EfmInt, en_functional_state_t enNewState);
void EFM_ClearStatus(uint32_t u32Flag);

en_result_t EFM_StructInit(stc_efm_init_t *pstcEfmInit);
en_result_t EFM_Init(const stc_efm_init_t *pstcEfmInit);
en_result_t EFM_Program32(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_Program16(uint32_t u32Addr, uint16_t u16Data);
en_result_t EFM_ProgramReadBack32(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_ProgramReadBack16(uint32_t u32Addr, uint16_t u16Data);
en_result_t EFM_SeqProgram32(uint32_t u32Addr, uint32_t u32Len, const uint32_t *pu32Buf);
en_result_t EFM_SeqProgram16(uint32_t u32Addr, uint32_t u32Len, const uint16_t *pu16Buf);
en_result_t EFM_SectorErase(uint32_t u32Addr);
en_result_t EFM_ChipErase(void);
en_result_t EFM_SetOperateMode(uint32_t u32Mode);

en_flag_status_t EFM_GetStatus(uint32_t u32Flag);
en_result_t EFM_GetUID(stc_efm_unique_id_t *stcUID);
/**
 * @}
 */

#endif /* DDL_EFM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_EFM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
