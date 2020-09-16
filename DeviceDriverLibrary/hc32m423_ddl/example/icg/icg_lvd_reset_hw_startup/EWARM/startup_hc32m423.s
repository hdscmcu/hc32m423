;*******************************************************************************
; Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
;
; This software is owned and published by:
; Huada Semiconductor Co.,Ltd ("HDSC").
;
; BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
; BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
;
; This software contains source code for use with HDSC
; components. This software is licensed by HDSC to be adapted only
; for use in systems utilizing HDSC components. HDSC shall not be
; responsible for misuse or illegal use of this software for devices not
; supported herein. HDSC is providing this software "AS IS" and will
; not be responsible for issues arising from incorrect user implementation
; of the software.
;
; Disclaimer:
; HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
; REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
; ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
; WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
; WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
; WARRANTY OF NONINFRINGEMENT.
; HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
; NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
; LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
; LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
; INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
; INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
; SAVINGS OR PROFITS,
; EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
; YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
; INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
; FROM, THE SOFTWARE.
;
; This software may be replicated in part or whole for the licensed use,
; with the restriction that this Disclaimer and Copyright notice must be
; included with each copy of this software, whether used in part or whole,
; at all times.
;/
;/*****************************************************************************/
;/*  Startup for IAR                                                          */
;/*  Version     V1.0                                                         */
;/*  Date        2020-02-01                                                   */
;/*  Target-mcu  HC32M423                                                     */
;/*****************************************************************************/


                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                SECTION .intvec:CODE:NOROOT(2)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table

                SECTION .intvec:CODE:NOROOT(2)
                DATA
__vector_table
                DCD     sfe(CSTACK)               ; Top of Stack
                DCD     Reset_Handler             ; Reset
                DCD     NMI_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     MemManage_Handler         ; MemManage Fault
                DCD     BusFault_Handler          ; Bus Fault
                DCD     UsageFault_Handler        ; Usage Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     DebugMon_Handler          ; Debug Monitor
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

; Numbered IRQ handler vectors

; Note: renaming to device dependent ISR function names are done in
;      (section "IRQ name definition for all type MCUs")
                DCD     IRQ000_Handler
                DCD     IRQ001_Handler
                DCD     IRQ002_Handler
                DCD     IRQ003_Handler
                DCD     IRQ004_Handler
                DCD     IRQ005_Handler
                DCD     IRQ006_Handler
                DCD     IRQ007_Handler
                DCD     IRQ008_Handler
                DCD     IRQ009_Handler
                DCD     IRQ010_Handler
                DCD     IRQ011_Handler
                DCD     IRQ012_Handler
                DCD     IRQ013_Handler
                DCD     IRQ014_Handler
                DCD     IRQ015_Handler
                DCD     IRQ016_Handler
                DCD     IRQ017_Handler
                DCD     IRQ018_Handler
                DCD     IRQ019_Handler
                DCD     IRQ020_Handler
                DCD     IRQ021_Handler
                DCD     IRQ022_Handler
                DCD     IRQ023_Handler
                DCD     IRQ024_Handler
                DCD     IRQ025_Handler
                DCD     IRQ026_Handler
                DCD     IRQ027_Handler
                DCD     IRQ028_Handler
                DCD     IRQ029_Handler
                DCD     IRQ030_Handler
                DCD     IRQ031_Handler
                DCD     IRQ032_Handler
                DCD     IRQ033_Handler
                DCD     IRQ034_Handler
                DCD     IRQ035_Handler
                DCD     IRQ036_Handler
                DCD     IRQ037_Handler
                DCD     IRQ038_Handler
                DCD     IRQ039_Handler
                DCD     IRQ040_Handler
                DCD     IRQ041_Handler
                DCD     IRQ042_Handler
                DCD     IRQ043_Handler
                DCD     IRQ044_Handler
                DCD     IRQ045_Handler
                DCD     IRQ046_Handler
                DCD     IRQ047_Handler
                DCD     IRQ048_Handler
                DCD     IRQ049_Handler
                DCD     IRQ050_Handler
                DCD     IRQ051_Handler
                DCD     IRQ052_Handler
                DCD     IRQ053_Handler
                DCD     IRQ054_Handler
                DCD     IRQ055_Handler
                DCD     IRQ056_Handler
                DCD     IRQ057_Handler
                DCD     IRQ058_Handler
                DCD     IRQ059_Handler
                DCD     IRQ060_Handler
                DCD     IRQ061_Handler
                DCD     IRQ062_Handler
                DCD     IRQ063_Handler
                DCD     IRQ064_Handler
                DCD     IRQ065_Handler
                DCD     IRQ066_Handler
                DCD     IRQ067_Handler
                DCD     IRQ068_Handler
                DCD     IRQ069_Handler
                DCD     IRQ070_Handler
                DCD     IRQ071_Handler
                DCD     IRQ072_Handler
                DCD     IRQ073_Handler
                DCD     IRQ074_Handler
                DCD     IRQ075_Handler
                DCD     IRQ076_Handler
                DCD     IRQ077_Handler
                DCD     IRQ078_Handler
                DCD     IRQ079_Handler
                DCD     IRQ080_Handler
                DCD     IRQ081_Handler
                DCD     IRQ082_Handler
                DCD     IRQ083_Handler
                DCD     IRQ084_Handler
                DCD     IRQ085_Handler
                DCD     IRQ086_Handler
                DCD     IRQ087_Handler
                DCD     IRQ088_Handler
                DCD     IRQ089_Handler
                DCD     IRQ090_Handler
                DCD     IRQ091_Handler
                DCD     IRQ092_Handler
                DCD     IRQ093_Handler
                DCD     IRQ094_Handler
                DCD     IRQ095_Handler
                DCD     IRQ096_Handler
                DCD     IRQ097_Handler
                DCD     IRQ098_Handler
                DCD     IRQ099_Handler
                DCD     IRQ100_Handler


                THUMB
; Dummy Exception Handlers (infinite loops which can be modified)

                PUBWEAK Reset_Handler
                SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
;                LDR     R2, =0x40014020 ; PWC_FPRC
;                LDR     R0, =0xA502
;                STR     R0, [R2]        ; PWC_FPRC = 0xA502
;
;                MOVS    R0, #1
;                LDR     R1, =0x42280190 ; PWC_RAMCR_RPERDIS
;                STRB    R0, [R1]        ; PWC_RAMCR_RPERDIS = 1
;
;                LDR     R0, =0xA500
;                STR     R0, [R2]        ; PWC_FPRC = 0xA500

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0

                PUBWEAK NMI_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
                B       NMI_Handler

                PUBWEAK HardFault_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
                B       HardFault_Handler

                PUBWEAK MemManage_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
MemManage_Handler
                B       MemManage_Handler

                PUBWEAK BusFault_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
BusFault_Handler
                B       BusFault_Handler

                PUBWEAK UsageFault_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
UsageFault_Handler
                B       UsageFault_Handler

                PUBWEAK SVC_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
                B       SVC_Handler

                PUBWEAK DebugMon_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DebugMon_Handler
                B       DebugMon_Handler

                PUBWEAK PendSV_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
                B       PendSV_Handler

                PUBWEAK SysTick_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
                B       SysTick_Handler

                PUBWEAK IRQ000_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ000_Handler
                B       IRQ000_Handler

                PUBWEAK IRQ001_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ001_Handler
                B       IRQ001_Handler

                PUBWEAK IRQ002_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ002_Handler
                B       IRQ002_Handler

                PUBWEAK IRQ003_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ003_Handler
                B       IRQ003_Handler

                PUBWEAK IRQ004_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ004_Handler
                B       IRQ004_Handler

                PUBWEAK IRQ005_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ005_Handler
                B       IRQ005_Handler

                PUBWEAK IRQ006_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ006_Handler
                B       IRQ006_Handler

                PUBWEAK IRQ007_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ007_Handler
                B       IRQ007_Handler

                PUBWEAK IRQ008_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ008_Handler
                B       IRQ008_Handler

                PUBWEAK IRQ009_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ009_Handler
                B       IRQ009_Handler

                PUBWEAK IRQ010_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ010_Handler
                B       IRQ010_Handler

                PUBWEAK IRQ011_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ011_Handler
                B       IRQ011_Handler

                PUBWEAK IRQ012_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ012_Handler
                B       IRQ012_Handler

                PUBWEAK IRQ013_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ013_Handler
                B       IRQ013_Handler

                PUBWEAK IRQ014_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ014_Handler
                B       IRQ014_Handler

                PUBWEAK IRQ015_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ015_Handler
                B       IRQ015_Handler

                PUBWEAK IRQ016_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ016_Handler
                B       IRQ016_Handler

                PUBWEAK IRQ017_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ017_Handler
                B       IRQ017_Handler

                PUBWEAK IRQ018_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ018_Handler
                B       IRQ018_Handler

                PUBWEAK IRQ019_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ019_Handler
                B       IRQ019_Handler

                PUBWEAK IRQ020_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ020_Handler
                B       IRQ020_Handler

                PUBWEAK IRQ021_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ021_Handler
                B       IRQ021_Handler

                PUBWEAK IRQ022_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ022_Handler
                B       IRQ022_Handler

                PUBWEAK IRQ023_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ023_Handler
                B       IRQ023_Handler

                PUBWEAK IRQ024_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ024_Handler
                B       IRQ024_Handler

                PUBWEAK IRQ025_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ025_Handler
                B       IRQ025_Handler

                PUBWEAK IRQ026_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ026_Handler
                B       IRQ026_Handler

                PUBWEAK IRQ027_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ027_Handler
                B       IRQ027_Handler

                PUBWEAK IRQ028_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ028_Handler
                B       IRQ028_Handler

                PUBWEAK IRQ029_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ029_Handler
                B       IRQ029_Handler

                PUBWEAK IRQ030_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ030_Handler
                B       IRQ030_Handler

                PUBWEAK IRQ031_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ031_Handler
                B       IRQ031_Handler

                PUBWEAK IRQ032_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ032_Handler
                B       IRQ032_Handler

                PUBWEAK IRQ033_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ033_Handler
                B       IRQ033_Handler

                PUBWEAK IRQ034_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ034_Handler
                B       IRQ034_Handler

                PUBWEAK IRQ035_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ035_Handler
                B       IRQ035_Handler

                PUBWEAK IRQ036_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ036_Handler
                B       IRQ036_Handler

                PUBWEAK IRQ037_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ037_Handler
                B       IRQ037_Handler

                PUBWEAK IRQ038_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ038_Handler
                B       IRQ038_Handler

                PUBWEAK IRQ039_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ039_Handler
                B       IRQ039_Handler

                PUBWEAK IRQ040_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ040_Handler
                B       IRQ040_Handler

                PUBWEAK IRQ041_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ041_Handler
                B       IRQ041_Handler

                PUBWEAK IRQ042_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ042_Handler
                B       IRQ042_Handler

                PUBWEAK IRQ043_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ043_Handler
                B       IRQ043_Handler

                PUBWEAK IRQ044_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ044_Handler
                B       IRQ044_Handler

                PUBWEAK IRQ045_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ045_Handler
                B       IRQ045_Handler

                PUBWEAK IRQ046_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ046_Handler
                B       IRQ046_Handler

                PUBWEAK IRQ047_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ047_Handler
                B       IRQ047_Handler

                PUBWEAK IRQ048_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ048_Handler
                B       IRQ048_Handler

                PUBWEAK IRQ049_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ049_Handler
                B       IRQ049_Handler

                PUBWEAK IRQ050_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ050_Handler
                B       IRQ050_Handler

                PUBWEAK IRQ051_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ051_Handler
                B       IRQ051_Handler

                PUBWEAK IRQ052_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ052_Handler
                B       IRQ052_Handler

                PUBWEAK IRQ053_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ053_Handler
                B       IRQ053_Handler

                PUBWEAK IRQ054_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ054_Handler
                B       IRQ054_Handler

                PUBWEAK IRQ055_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ055_Handler
                B       IRQ055_Handler

                PUBWEAK IRQ056_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ056_Handler
                B       IRQ056_Handler

                PUBWEAK IRQ057_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ057_Handler
                B       IRQ057_Handler

                PUBWEAK IRQ058_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ058_Handler
                B       IRQ058_Handler

                PUBWEAK IRQ059_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ059_Handler
                B       IRQ059_Handler

                PUBWEAK IRQ060_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ060_Handler
                B       IRQ060_Handler

                PUBWEAK IRQ061_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ061_Handler
                B       IRQ061_Handler

                PUBWEAK IRQ062_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ062_Handler
                B       IRQ062_Handler

                PUBWEAK IRQ063_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ063_Handler
                B       IRQ063_Handler

                PUBWEAK IRQ064_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ064_Handler
                B       IRQ064_Handler

                PUBWEAK IRQ065_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ065_Handler
                B       IRQ065_Handler

                PUBWEAK IRQ066_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ066_Handler
                B       IRQ066_Handler

                PUBWEAK IRQ067_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ067_Handler
                B       IRQ067_Handler

                PUBWEAK IRQ068_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ068_Handler
                B       IRQ068_Handler

                PUBWEAK IRQ069_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ069_Handler
                B       IRQ069_Handler

                PUBWEAK IRQ070_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ070_Handler
                B       IRQ070_Handler

                PUBWEAK IRQ071_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ071_Handler
                B       IRQ071_Handler

                PUBWEAK IRQ072_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ072_Handler
                B       IRQ072_Handler

                PUBWEAK IRQ073_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ073_Handler
                B       IRQ073_Handler

                PUBWEAK IRQ074_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ074_Handler
                B       IRQ074_Handler

                PUBWEAK IRQ075_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ075_Handler
                B       IRQ075_Handler

                PUBWEAK IRQ076_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ076_Handler
                B       IRQ076_Handler

                PUBWEAK IRQ077_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ077_Handler
                B       IRQ077_Handler

                PUBWEAK IRQ078_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ078_Handler
                B       IRQ078_Handler

                PUBWEAK IRQ079_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ079_Handler
                B       IRQ079_Handler

                PUBWEAK IRQ080_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ080_Handler
                B       IRQ080_Handler

                PUBWEAK IRQ081_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ081_Handler
                B       IRQ081_Handler

                PUBWEAK IRQ082_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ082_Handler
                B       IRQ082_Handler

                PUBWEAK IRQ083_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ083_Handler
                B       IRQ083_Handler

                PUBWEAK IRQ084_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ084_Handler
                B       IRQ084_Handler

                PUBWEAK IRQ085_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ085_Handler
                B       IRQ085_Handler

                PUBWEAK IRQ086_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ086_Handler
                B       IRQ086_Handler

                PUBWEAK IRQ087_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ087_Handler
                B       IRQ087_Handler

                PUBWEAK IRQ088_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ088_Handler
                B       IRQ088_Handler

                PUBWEAK IRQ089_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ089_Handler
                B       IRQ089_Handler

                PUBWEAK IRQ090_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ090_Handler
                B       IRQ090_Handler

                PUBWEAK IRQ091_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ091_Handler
                B       IRQ091_Handler

                PUBWEAK IRQ092_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ092_Handler
                B       IRQ092_Handler

                PUBWEAK IRQ093_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ093_Handler
                B       IRQ093_Handler

                PUBWEAK IRQ094_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ094_Handler
                B       IRQ094_Handler

                PUBWEAK IRQ095_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ095_Handler
                B       IRQ095_Handler

                PUBWEAK IRQ096_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ096_Handler
                B       IRQ096_Handler

                PUBWEAK IRQ097_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ097_Handler
                B       IRQ097_Handler

                PUBWEAK IRQ098_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ098_Handler
                B       IRQ098_Handler

                PUBWEAK IRQ099_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ099_Handler
                B       IRQ099_Handler

                PUBWEAK IRQ100_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ100_Handler
                B       IRQ100_Handler

                END
