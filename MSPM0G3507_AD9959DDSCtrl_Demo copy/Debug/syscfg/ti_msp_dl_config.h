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



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);

void SYSCFG_DL_SYSTICK_init(void);


#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
