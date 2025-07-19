#include "UserADC.h"

volatile uint16_t ADC0Data = 0;
volatile uint16_t ADC1Data = 0;
volatile uint8_t ADC0DataValid = 0;
volatile uint8_t ADC1DataValid = 0;

void UserADC_init(void) {
    NVIC_EnableIRQ(ADC0_INST_INT_IRQN);
    NVIC_EnableIRQ(ADC1_INST_INT_IRQN);
}

void UserADC0_start(void) {
    ADC0DataValid = 0;
    DL_ADC12_startConversion(ADC0_INST);
}

void UserADC1_start(void) {
    ADC1DataValid = 0;
    DL_ADC12_startConversion(ADC1_INST);
}

uint16_t UserADC0_getData(uint32_t timeout) {
    uint32_t startTime = Tick;
    while (!ADC0DataValid) {
        if (Tick - startTime >= timeout) return 0;
    }
    return ADC0Data;
}

uint16_t UserADC1_getData(uint32_t timeout) {
    uint32_t startTime = Tick;
    while (!ADC1DataValid) {
        if (Tick - startTime >= timeout) return 0;
    }
    return ADC1Data;
}

// ADC0中断服务函数
void ADC0_IRQHandler(void) {
    if (DL_ADC12_getPendingInterrupt(ADC0_INST) == DL_ADC12_IIDX_MEM0_RESULT_LOADED) {
        ADC0Data = DL_ADC12_getMemResult(ADC0_INST, ADC0_ADCMEM_0);
        ADC0DataValid = 1;
        DL_ADC12_enableConversions(ADC0_INST);
    }
}

// ADC1中断服务函数
void ADC1_IRQHandler(void) {
    if (DL_ADC12_getPendingInterrupt(ADC1_INST) == DL_ADC12_IIDX_MEM0_RESULT_LOADED) {
        ADC1Data = DL_ADC12_getMemResult(ADC1_INST, ADC1_ADCMEM_0);
        ADC1DataValid = 1;
        DL_ADC12_enableConversions(ADC1_INST);
    }
}
