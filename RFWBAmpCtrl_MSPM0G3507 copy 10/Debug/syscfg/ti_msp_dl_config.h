/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFCLKIN_PORT                                                  GPIOA
#define GPIO_HFCLKIN_PIN                                           DL_GPIO_PIN_6
#define GPIO_HFCLKIN_IOMUX                                       (IOMUX_PINCM11)
#define GPIO_HFCLKIN_IOMUX_FUNC                  IOMUX_PINCM11_PF_SYSCTL_HFCLKIN
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_LED_RG */
#define PWM_LED_RG_INST                                                    TIMG7
#define PWM_LED_RG_INST_IRQHandler                              TIMG7_IRQHandler
#define PWM_LED_RG_INST_INT_IRQN                                (TIMG7_INT_IRQn)
#define PWM_LED_RG_INST_CLK_FREQ                                        80000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_LED_RG_C0_PORT                                            GPIOA
#define GPIO_PWM_LED_RG_C0_PIN                                     DL_GPIO_PIN_3
#define GPIO_PWM_LED_RG_C0_IOMUX                                  (IOMUX_PINCM8)
#define GPIO_PWM_LED_RG_C0_IOMUX_FUNC                 IOMUX_PINCM8_PF_TIMG7_CCP0
#define GPIO_PWM_LED_RG_C0_IDX                               DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_LED_RG_C1_PORT                                            GPIOA
#define GPIO_PWM_LED_RG_C1_PIN                                     DL_GPIO_PIN_2
#define GPIO_PWM_LED_RG_C1_IOMUX                                  (IOMUX_PINCM7)
#define GPIO_PWM_LED_RG_C1_IOMUX_FUNC                 IOMUX_PINCM7_PF_TIMG7_CCP1
#define GPIO_PWM_LED_RG_C1_IDX                               DL_TIMER_CC_1_INDEX

/* Defines for PWM_LED_B */
#define PWM_LED_B_INST                                                     TIMG8
#define PWM_LED_B_INST_IRQHandler                               TIMG8_IRQHandler
#define PWM_LED_B_INST_INT_IRQN                                 (TIMG8_INT_IRQn)
#define PWM_LED_B_INST_CLK_FREQ                                         40000000
/* GPIO defines for channel 1 */
#define GPIO_PWM_LED_B_C1_PORT                                             GPIOA
#define GPIO_PWM_LED_B_C1_PIN                                      DL_GPIO_PIN_4
#define GPIO_PWM_LED_B_C1_IOMUX                                   (IOMUX_PINCM9)
#define GPIO_PWM_LED_B_C1_IOMUX_FUNC                  IOMUX_PINCM9_PF_TIMG8_CCP1
#define GPIO_PWM_LED_B_C1_IDX                                DL_TIMER_CC_1_INDEX

/* Defines for PWM_GAIN */
#define PWM_GAIN_INST                                                      TIMG6
#define PWM_GAIN_INST_IRQHandler                                TIMG6_IRQHandler
#define PWM_GAIN_INST_INT_IRQN                                  (TIMG6_INT_IRQn)
#define PWM_GAIN_INST_CLK_FREQ                                          80000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_GAIN_C0_PORT                                              GPIOA
#define GPIO_PWM_GAIN_C0_PIN                                      DL_GPIO_PIN_21
#define GPIO_PWM_GAIN_C0_IOMUX                                   (IOMUX_PINCM46)
#define GPIO_PWM_GAIN_C0_IOMUX_FUNC                  IOMUX_PINCM46_PF_TIMG6_CCP0
#define GPIO_PWM_GAIN_C0_IDX                                 DL_TIMER_CC_0_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA1)
#define TIMER_0_INST_IRQHandler                                 TIMA1_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA1_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (58593U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMA0)
#define TIMER_1_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                         (15624U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_40_MHZ_9600_BAUD                                       (260)
#define UART_0_FBRD_40_MHZ_9600_BAUD                                        (27)
/* Defines for UART_2 */
#define UART_2_INST                                                        UART2
#define UART_2_INST_IRQHandler                                  UART2_IRQHandler
#define UART_2_INST_INT_IRQN                                      UART2_INT_IRQn
#define GPIO_UART_2_RX_PORT                                                GPIOB
#define GPIO_UART_2_TX_PORT                                                GPIOB
#define GPIO_UART_2_RX_PIN                                        DL_GPIO_PIN_18
#define GPIO_UART_2_TX_PIN                                        DL_GPIO_PIN_17
#define GPIO_UART_2_IOMUX_RX                                     (IOMUX_PINCM44)
#define GPIO_UART_2_IOMUX_TX                                     (IOMUX_PINCM43)
#define GPIO_UART_2_IOMUX_RX_FUNC                      IOMUX_PINCM44_PF_UART2_RX
#define GPIO_UART_2_IOMUX_TX_FUNC                      IOMUX_PINCM43_PF_UART2_TX
#define UART_2_BAUD_RATE                                                  (9600)
#define UART_2_IBRD_40_MHZ_9600_BAUD                                       (260)
#define UART_2_FBRD_40_MHZ_9600_BAUD                                        (27)





/* Defines for ADC1 */
#define ADC1_INST                                                           ADC1
#define ADC1_INST_IRQHandler                                     ADC1_IRQHandler
#define ADC1_INST_INT_IRQN                                       (ADC1_INT_IRQn)
#define ADC1_ADCMEM_0                                         DL_ADC12_MEM_IDX_0
#define ADC1_ADCMEM_0_REF                        DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC1_ADCMEM_0_REF_VOLTAGE_V                                          3.3
#define ADC1_ADCMEM_1                                         DL_ADC12_MEM_IDX_1
#define ADC1_ADCMEM_1_REF                        DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC1_ADCMEM_1_REF_VOLTAGE_V                                          3.3
#define ADC1_ADCMEM_2                                         DL_ADC12_MEM_IDX_2
#define ADC1_ADCMEM_2_REF                        DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC1_ADCMEM_2_REF_VOLTAGE_V                                          3.3
#define ADC1_ADCMEM_3                                         DL_ADC12_MEM_IDX_3
#define ADC1_ADCMEM_3_REF                        DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC1_ADCMEM_3_REF_VOLTAGE_V                                          3.3
#define GPIO_ADC1_C0_PORT                                                  GPIOA
#define GPIO_ADC1_C0_PIN                                          DL_GPIO_PIN_15
#define GPIO_ADC1_C1_PORT                                                  GPIOA
#define GPIO_ADC1_C1_PIN                                          DL_GPIO_PIN_16
#define GPIO_ADC1_C2_PORT                                                  GPIOA
#define GPIO_ADC1_C2_PIN                                          DL_GPIO_PIN_17
#define GPIO_ADC1_C6_PORT                                                  GPIOB
#define GPIO_ADC1_C6_PIN                                          DL_GPIO_PIN_19

/* Defines for ADC0 */
#define ADC0_INST                                                           ADC0
#define ADC0_INST_IRQHandler                                     ADC0_IRQHandler
#define ADC0_INST_INT_IRQN                                       (ADC0_INT_IRQn)
#define ADC0_ADCMEM_0                                         DL_ADC12_MEM_IDX_0
#define ADC0_ADCMEM_0_REF                        DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC0_ADCMEM_0_REF_VOLTAGE_V                                          3.3
#define GPIO_ADC0_C2_PORT                                                  GPIOA
#define GPIO_ADC0_C2_PIN                                          DL_GPIO_PIN_25



/* Port definition for Pin Group GPIO_BTN */
#define GPIO_BTN_PORT                                                    (GPIOB)

/* Defines for LEFT: GPIOB.6 with pinCMx 23 on package pin 20 */
#define GPIO_BTN_LEFT_PIN                                        (DL_GPIO_PIN_6)
#define GPIO_BTN_LEFT_IOMUX                                      (IOMUX_PINCM23)
/* Defines for DOWN: GPIOB.7 with pinCMx 24 on package pin 21 */
#define GPIO_BTN_DOWN_PIN                                        (DL_GPIO_PIN_7)
#define GPIO_BTN_DOWN_IOMUX                                      (IOMUX_PINCM24)
/* Defines for RIGHT: GPIOB.8 with pinCMx 25 on package pin 22 */
#define GPIO_BTN_RIGHT_PIN                                       (DL_GPIO_PIN_8)
#define GPIO_BTN_RIGHT_IOMUX                                     (IOMUX_PINCM25)
/* Defines for UP: GPIOB.9 with pinCMx 26 on package pin 23 */
#define GPIO_BTN_UP_PIN                                          (DL_GPIO_PIN_9)
#define GPIO_BTN_UP_IOMUX                                        (IOMUX_PINCM26)
/* Defines for MID: GPIOB.14 with pinCMx 31 on package pin 24 */
#define GPIO_BTN_MID_PIN                                        (DL_GPIO_PIN_14)
#define GPIO_BTN_MID_IOMUX                                       (IOMUX_PINCM31)
/* Defines for ENC_A: GPIOB.15 with pinCMx 32 on package pin 25 */
#define GPIO_ENC_ENC_A_PORT                                              (GPIOB)
// pins affected by this interrupt request:["ENC_A"]
#define GPIO_ENC_INT_IRQN                                       (GPIOB_INT_IRQn)
#define GPIO_ENC_INT_IIDX                       (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define GPIO_ENC_ENC_A_IIDX                                 (DL_GPIO_IIDX_DIO15)
#define GPIO_ENC_ENC_A_PIN                                      (DL_GPIO_PIN_15)
#define GPIO_ENC_ENC_A_IOMUX                                     (IOMUX_PINCM32)
/* Defines for ENC_B: GPIOB.16 with pinCMx 33 on package pin 26 */
#define GPIO_ENC_ENC_B_PORT                                              (GPIOB)
#define GPIO_ENC_ENC_B_PIN                                      (DL_GPIO_PIN_16)
#define GPIO_ENC_ENC_B_IOMUX                                     (IOMUX_PINCM33)
/* Defines for ENC_SW: GPIOA.12 with pinCMx 34 on package pin 27 */
#define GPIO_ENC_ENC_SW_PORT                                             (GPIOA)
#define GPIO_ENC_ENC_SW_PIN                                     (DL_GPIO_PIN_12)
#define GPIO_ENC_ENC_SW_IOMUX                                    (IOMUX_PINCM34)
/* Defines for DDS_SCLK: GPIOA.7 with pinCMx 14 on package pin 13 */
#define GPIO_DDS_DDS_SCLK_PORT                                           (GPIOA)
#define GPIO_DDS_DDS_SCLK_PIN                                    (DL_GPIO_PIN_7)
#define GPIO_DDS_DDS_SCLK_IOMUX                                  (IOMUX_PINCM14)
/* Defines for DDS_SDIO0: GPIOB.2 with pinCMx 15 on package pin 14 */
#define GPIO_DDS_DDS_SDIO0_PORT                                          (GPIOB)
#define GPIO_DDS_DDS_SDIO0_PIN                                   (DL_GPIO_PIN_2)
#define GPIO_DDS_DDS_SDIO0_IOMUX                                 (IOMUX_PINCM15)
/* Defines for DDS_CS: GPIOB.3 with pinCMx 16 on package pin 15 */
#define GPIO_DDS_DDS_CS_PORT                                             (GPIOB)
#define GPIO_DDS_DDS_CS_PIN                                      (DL_GPIO_PIN_3)
#define GPIO_DDS_DDS_CS_IOMUX                                    (IOMUX_PINCM16)
/* Defines for DDS_UPDATE: GPIOA.8 with pinCMx 19 on package pin 16 */
#define GPIO_DDS_DDS_UPDATE_PORT                                         (GPIOA)
#define GPIO_DDS_DDS_UPDATE_PIN                                  (DL_GPIO_PIN_8)
#define GPIO_DDS_DDS_UPDATE_IOMUX                                (IOMUX_PINCM19)
/* Defines for DDS_RST: GPIOA.9 with pinCMx 20 on package pin 17 */
#define GPIO_DDS_DDS_RST_PORT                                            (GPIOA)
#define GPIO_DDS_DDS_RST_PIN                                     (DL_GPIO_PIN_9)
#define GPIO_DDS_DDS_RST_IOMUX                                   (IOMUX_PINCM20)
/* Port definition for Pin Group GPIO_RELAY */
#define GPIO_RELAY_PORT                                                  (GPIOA)

/* Defines for relay1: GPIOA.22 with pinCMx 47 on package pin 40 */
#define GPIO_RELAY_relay1_PIN                                   (DL_GPIO_PIN_22)
#define GPIO_RELAY_relay1_IOMUX                                  (IOMUX_PINCM47)
/* Defines for relay2: GPIOA.5 with pinCMx 10 on package pin 11 */
#define GPIO_RELAY_relay2_PIN                                    (DL_GPIO_PIN_5)
#define GPIO_RELAY_relay2_IOMUX                                  (IOMUX_PINCM10)
/* Port definition for Pin Group GPIO_RFC */
#define GPIO_RFC_PORT                                                    (GPIOA)

/* Defines for UP_B: GPIOA.0 with pinCMx 1 on package pin 1 */
#define GPIO_RFC_UP_B_PIN                                        (DL_GPIO_PIN_0)
#define GPIO_RFC_UP_B_IOMUX                                       (IOMUX_PINCM1)
/* Defines for UP_A: GPIOA.1 with pinCMx 2 on package pin 2 */
#define GPIO_RFC_UP_A_PIN                                        (DL_GPIO_PIN_1)
#define GPIO_RFC_UP_A_IOMUX                                       (IOMUX_PINCM2)
/* Defines for DOWN_B: GPIOA.28 with pinCMx 3 on package pin 3 */
#define GPIO_RFC_DOWN_B_PIN                                     (DL_GPIO_PIN_28)
#define GPIO_RFC_DOWN_B_IOMUX                                     (IOMUX_PINCM3)
/* Defines for DOWN_A: GPIOA.31 with pinCMx 6 on package pin 5 */
#define GPIO_RFC_DOWN_A_PIN                                     (DL_GPIO_PIN_31)
#define GPIO_RFC_DOWN_A_IOMUX                                     (IOMUX_PINCM6)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_LED_RG_init(void);
void SYSCFG_DL_PWM_LED_B_init(void);
void SYSCFG_DL_PWM_GAIN_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_2_init(void);
void SYSCFG_DL_ADC1_init(void);
void SYSCFG_DL_ADC0_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
