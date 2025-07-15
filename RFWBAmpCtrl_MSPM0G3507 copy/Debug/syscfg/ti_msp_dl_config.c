/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerG_backupConfig gPWM_LED_RGBackup;
DL_TimerG_backupConfig gPWM_GAINBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_LED_RG_init();
    SYSCFG_DL_PWM_LED_B_init();
    SYSCFG_DL_PWM_GAIN_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_UART_2_init();
    SYSCFG_DL_ADC0_init();
    SYSCFG_DL_ADC1_init();
    SYSCFG_DL_SYSTICK_init();
    /* Ensure backup structures have no valid state */
	gPWM_LED_RGBackup.backupRdy 	= false;
	gPWM_GAINBackup.backupRdy 	= false;


}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_saveConfiguration(PWM_LED_RG_INST, &gPWM_LED_RGBackup);
	retStatus &= DL_TimerG_saveConfiguration(PWM_GAIN_INST, &gPWM_GAINBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_restoreConfiguration(PWM_LED_RG_INST, &gPWM_LED_RGBackup, false);
	retStatus &= DL_TimerG_restoreConfiguration(PWM_GAIN_INST, &gPWM_GAINBackup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(PWM_LED_RG_INST);
    DL_TimerG_reset(PWM_LED_B_INST);
    DL_TimerG_reset(PWM_GAIN_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_UART_Main_reset(UART_2_INST);
    DL_ADC12_reset(ADC0_INST);
    DL_ADC12_reset(ADC1_INST);


    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(PWM_LED_RG_INST);
    DL_TimerG_enablePower(PWM_LED_B_INST);
    DL_TimerG_enablePower(PWM_GAIN_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_UART_Main_enablePower(UART_2_INST);
    DL_ADC12_enablePower(ADC0_INST);
    DL_ADC12_enablePower(ADC1_INST);

    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralInputFunction(GPIO_HFCLKIN_IOMUX, GPIO_HFCLKIN_IOMUX_FUNC);

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_LED_RG_C0_IOMUX,GPIO_PWM_LED_RG_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_LED_RG_C0_PORT, GPIO_PWM_LED_RG_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_LED_RG_C1_IOMUX,GPIO_PWM_LED_RG_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_LED_RG_C1_PORT, GPIO_PWM_LED_RG_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_LED_B_C1_IOMUX,GPIO_PWM_LED_B_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_LED_B_C1_PORT, GPIO_PWM_LED_B_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_GAIN_C0_IOMUX,GPIO_PWM_GAIN_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_GAIN_C0_PORT, GPIO_PWM_GAIN_C0_PIN);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_2_IOMUX_TX, GPIO_UART_2_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_2_IOMUX_RX, GPIO_UART_2_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalInputFeatures(GPIO_BTN_LEFT_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_BTN_DOWN_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_BTN_RIGHT_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_BTN_UP_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_BTN_MID_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInput(GPIO_ENC_ENC_A_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_ENC_ENC_B_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_ENC_ENC_SW_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_DDS_DDS_SCLK_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_DDS_DDS_SDIO0_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_DDS_DDS_CS_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_DDS_DDS_UPDATE_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_DDS_DDS_RST_IOMUX);

    DL_GPIO_clearPins(GPIOA, GPIO_DDS_DDS_SCLK_PIN |
		GPIO_DDS_DDS_UPDATE_PIN |
		GPIO_DDS_DDS_RST_PIN);
    DL_GPIO_enableOutput(GPIOA, GPIO_DDS_DDS_SCLK_PIN |
		GPIO_DDS_DDS_UPDATE_PIN |
		GPIO_DDS_DDS_RST_PIN);
    DL_GPIO_clearPins(GPIOB, GPIO_DDS_DDS_SDIO0_PIN |
		GPIO_DDS_DDS_CS_PIN);
    DL_GPIO_enableOutput(GPIOB, GPIO_DDS_DDS_SDIO0_PIN |
		GPIO_DDS_DDS_CS_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOB, DL_GPIO_PIN_15_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOB, GPIO_ENC_ENC_A_PIN);
    DL_GPIO_enableInterrupt(GPIOB, GPIO_ENC_ENC_A_PIN);

}


static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq              = DL_SYSCTL_SYSPLL_INPUT_FREQ_32_48_MHZ,
	.rDivClk2x              = 1,
	.rDivClk1               = 0,
	.rDivClk0               = 0,
	.enableCLK2x            = DL_SYSCTL_SYSPLL_CLK2X_DISABLE,
	.enableCLK1             = DL_SYSCTL_SYSPLL_CLK1_DISABLE,
	.enableCLK0             = DL_SYSCTL_SYSPLL_CLK0_ENABLE,
	.sysPLLMCLK             = DL_SYSCTL_SYSPLL_MCLK_CLK0,
	.sysPLLRef              = DL_SYSCTL_SYSPLL_REF_HFCLK,
	.qDiv                   = 3,
	.pDiv                   = DL_SYSCTL_SYSPLL_PDIV_1
};
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
    DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
    DL_SYSCTL_setHFCLKSourceHFCLKIN();
    DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *) &gSYSPLLConfig);
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);
    DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);

}


/*
 * Timer clock configuration to be sourced by  / 1 (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   80000000 Hz = 80000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_LED_RGClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gPWM_LED_RGConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 1023,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_LED_RG_init(void) {

    DL_TimerG_setClockConfig(
        PWM_LED_RG_INST, (DL_TimerG_ClockConfig *) &gPWM_LED_RGClockConfig);

    DL_TimerG_initPWMMode(
        PWM_LED_RG_INST, (DL_TimerG_PWMConfig *) &gPWM_LED_RGConfig);

    DL_TimerG_setCaptureCompareOutCtl(PWM_LED_RG_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_LED_RG_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_LED_RG_INST, 511, DL_TIMER_CC_0_INDEX);

    DL_TimerG_setCaptureCompareOutCtl(PWM_LED_RG_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_LED_RG_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_LED_RG_INST, 511, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(PWM_LED_RG_INST);


    
    DL_TimerG_setCCPDirection(PWM_LED_RG_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}
/*
 * Timer clock configuration to be sourced by  / 1 (40000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   40000000 Hz = 40000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_LED_BClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gPWM_LED_BConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 1023,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_LED_B_init(void) {

    DL_TimerG_setClockConfig(
        PWM_LED_B_INST, (DL_TimerG_ClockConfig *) &gPWM_LED_BClockConfig);

    DL_TimerG_initPWMMode(
        PWM_LED_B_INST, (DL_TimerG_PWMConfig *) &gPWM_LED_BConfig);

    DL_TimerG_setCaptureCompareOutCtl(PWM_LED_B_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_LED_B_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_LED_B_INST, 511, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(PWM_LED_B_INST);


    
    DL_TimerG_setCCPDirection(PWM_LED_B_INST , DL_TIMER_CC1_OUTPUT );


}
/*
 * Timer clock configuration to be sourced by  / 1 (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   80000000 Hz = 80000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_GAINClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gPWM_GAINConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1023,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_GAIN_init(void) {

    DL_TimerG_setClockConfig(
        PWM_GAIN_INST, (DL_TimerG_ClockConfig *) &gPWM_GAINClockConfig);

    DL_TimerG_initPWMMode(
        PWM_GAIN_INST, (DL_TimerG_PWMConfig *) &gPWM_GAINConfig);

    DL_TimerG_setCaptureCompareOutCtl(PWM_GAIN_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_GAIN_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_GAIN_INST, 511, DL_TIMER_CC_0_INDEX);

    DL_TimerG_enableClock(PWM_GAIN_INST);


    
    DL_TimerG_setCCPDirection(PWM_GAIN_INST , DL_TIMER_CC0_OUTPUT );


}



static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9599.81
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_40_MHZ_9600_BAUD, UART_0_FBRD_40_MHZ_9600_BAUD);



    DL_UART_Main_enable(UART_0_INST);
}

static const DL_UART_Main_ClockConfig gUART_2ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_2Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_2_init(void)
{
    DL_UART_Main_setClockConfig(UART_2_INST, (DL_UART_Main_ClockConfig *) &gUART_2ClockConfig);

    DL_UART_Main_init(UART_2_INST, (DL_UART_Main_Config *) &gUART_2Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9599.81
     */
    DL_UART_Main_setOversampling(UART_2_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_2_INST, UART_2_IBRD_40_MHZ_9600_BAUD, UART_2_FBRD_40_MHZ_9600_BAUD);



    DL_UART_Main_enable(UART_2_INST);
}

/* ADC0 Initialization */
static const DL_ADC12_ClockConfig gADC0ClockConfig = {
    .clockSel       = DL_ADC12_CLOCK_HFCLK,
    .divideRatio    = DL_ADC12_CLOCK_DIVIDE_1,
    .freqRange      = DL_ADC12_CLOCK_FREQ_RANGE_32_TO_40,
};
SYSCONFIG_WEAK void SYSCFG_DL_ADC0_init(void)
{
    DL_ADC12_setClockConfig(ADC0_INST, (DL_ADC12_ClockConfig *) &gADC0ClockConfig);

    DL_ADC12_initSeqSample(ADC0_INST,
        DL_ADC12_REPEAT_MODE_ENABLED, DL_ADC12_SAMPLING_SOURCE_AUTO, DL_ADC12_TRIG_SRC_SOFTWARE,
        DL_ADC12_SEQ_START_ADDR_00, DL_ADC12_SEQ_END_ADDR_01, DL_ADC12_SAMP_CONV_RES_12_BIT,
        DL_ADC12_SAMP_CONV_DATA_FORMAT_UNSIGNED);
    DL_ADC12_configConversionMem(ADC0_INST, ADC0_ADCMEM_0,
        DL_ADC12_INPUT_CHAN_0, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_DISABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_AUTO_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_configConversionMem(ADC0_INST, ADC0_ADCMEM_1,
        DL_ADC12_INPUT_CHAN_1, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_DISABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_AUTO_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_setSampleTime0(ADC0_INST,400);
    /* Enable ADC12 interrupt */
    DL_ADC12_clearInterruptStatus(ADC0_INST,(DL_ADC12_INTERRUPT_MEM1_RESULT_LOADED));
    DL_ADC12_enableInterrupt(ADC0_INST,(DL_ADC12_INTERRUPT_MEM1_RESULT_LOADED));
    DL_ADC12_enableConversions(ADC0_INST);
}
/* ADC1 Initialization */
static const DL_ADC12_ClockConfig gADC1ClockConfig = {
    .clockSel       = DL_ADC12_CLOCK_HFCLK,
    .divideRatio    = DL_ADC12_CLOCK_DIVIDE_1,
    .freqRange      = DL_ADC12_CLOCK_FREQ_RANGE_32_TO_40,
};
SYSCONFIG_WEAK void SYSCFG_DL_ADC1_init(void)
{
    DL_ADC12_setClockConfig(ADC1_INST, (DL_ADC12_ClockConfig *) &gADC1ClockConfig);
    DL_ADC12_configConversionMem(ADC1_INST, ADC1_ADCMEM_0,
        DL_ADC12_INPUT_CHAN_0, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_DISABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_AUTO_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_setSampleTime0(ADC1_INST,400);
    /* Enable ADC12 interrupt */
    DL_ADC12_clearInterruptStatus(ADC1_INST,(DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED));
    DL_ADC12_enableInterrupt(ADC1_INST,(DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED));
    DL_ADC12_enableConversions(ADC1_INST);
}

SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void)
{
    /*
     * Initializes the SysTick period to 1.00 ms,
     * enables the interrupt, and starts the SysTick Timer
     */
    DL_SYSTICK_config(80000);
}

