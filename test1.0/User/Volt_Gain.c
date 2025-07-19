#include "Volt_Gain.h"

float Gain = 0;  // 实际增益(dB)
volatile float volt_out, volt_in = 0;
volatile uint16_t inADCVal, outADCVal =0;//初始ADC取值

void Volt_Gain_taskGetData() {
    UserADC0_start();
    UserADC1_start();
    inADCVal = UserADC0_getData(5);
    outADCVal = UserADC0_getData(5);
    volt_in = ADC_VAL_TO_VOLTAGE(inADCVal);
    volt_out = ADC_VAL_TO_VOLTAGE(outADCVal);
    Gain = 20 * log10(volt_in / (volt_out / 2));//题目要求如此
}




