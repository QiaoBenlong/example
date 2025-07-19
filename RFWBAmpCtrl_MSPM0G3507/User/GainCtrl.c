#include "GainCtrl.h"

float GainSet = 0;   // 设定增益(dB)
float GainReal = 0;  // 实际增益(dB)
float GainError = 0; // 增益误差(dB)(实际-设定)
float PowerIn = 0;   // 输入功率(dBm)
float PowerOut = 0;  // 输出功率(dBm)

float PowerInMA[MOVING_AVER_N] = {0};
float PowerOutMA[MOVING_AVER_N] = {0};

float CtrlVal = 0; // 控制量

float movingAverage(float* q, int len, float new) {
    int i;
    float sum = 0;
    for (i = 0; i < len - 1; i++) {
        q[i] = q[i + 1];
        sum += q[i];
    }
    q[len - 1] = new;
    sum += new;
    return sum / len;
}

void GainCtrl_getCtrlVal(void) {
    if (GainError > GAIN_TOLERANCE) {
        CtrlVal--;
    }
    else if (GainError < -GAIN_TOLERANCE) {
        CtrlVal++;
    }
    CtrlVal = CONSTRAIN(CtrlVal, CTRL_VAL_MIN, CTRL_VAL_MAX);
}

void GainCtrl_taskGetData(void) {
    uint16_t inADCVal, outADCVal; // 输入、输出端ADC原始值
    float powerInNew, powerOutNew;
    UserADC0_start();
    UserADC1_start();
    inADCVal = UserADC0_getData(10);
    outADCVal = UserADC1_getData(10);
    powerInNew = VOLTAGE_TO_POWER(ADC_VAL_TO_VOLTAGE(inADCVal));
    powerOutNew = VOLTAGE_TO_POWER(ADC_VAL_TO_VOLTAGE(outADCVal));
    PowerIn = movingAverage(PowerInMA, MOVING_AVER_N, powerInNew);
    PowerOut = movingAverage(PowerOutMA, MOVING_AVER_N, powerOutNew);
    GainReal = PowerOut - PowerIn;
    GainError = GainReal - GainSet;
}

void GainCtrl_taskCtrl(void) {
    uint32_t compareVal;
    GainCtrl_getCtrlVal();
    compareVal = (uint32_t)CtrlVal;
    DL_TimerG_setCaptureCompareValue(PWM_GAIN_INST, compareVal, GPIO_PWM_GAIN_C0_IDX);
}
