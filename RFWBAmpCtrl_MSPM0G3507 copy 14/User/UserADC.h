// #ifndef __USER_ADC_H__
// #define __USER_ADC_H__

// #include <stdint.h>
// #include <math.h>
// #include "ti_msp_dl_config.h"
// #include "Tick.h"

// /// 环形缓存长度
// #define ADC_RECV_LEN    10

// #define ADC_VAL_TO_LOAD(x) ((108.9 * (float)x ) / (12288 - 3.3 * (float)x) ) - 0.8

// void UserADC_init(void);
// void UserADC0_TASK(void);
// void UserADC1_TASK(void);

// /** 三路平均值循环缓存 */
// extern volatile uint16_t length0 ;
// extern volatile uint16_t length1 ;
// extern volatile float central_freq ;
// extern volatile float load ;

// extern volatile uint16_t indx0 ;
// extern volatile uint16_t indx1 ;

// #endif /* #ifndef __USER_ADC_H__ */

#ifndef __USER_ADC_H__
#define __USER_ADC_H__

#include <stdint.h>
#include <math.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"

#define ADC_VREF 3.3F // ADC基准电压
// ADC值转为电压(V)
#define ADC_VAL_TO_VOLTAGE(x) ((float)x * ADC_VREF / 4096)

void UserADC_init(void);
void UserTask_ADC(void);
void UserTask_ADC1(void);

extern volatile bool gCheckADC;
extern volatile bool gCheckADC1;
extern volatile uint16_t gAdcResult;
extern volatile float amp_measured;
extern volatile float getADC[];
extern volatile float Vol_temp;
extern volatile float Vol_R; 
extern volatile float Vol_AC;
extern volatile int sampleCnt;
extern volatile int Cnt;
extern volatile float sum;
extern volatile float v1;
extern volatile float v2;
extern volatile float v3;
extern volatile uint16_t gAdcResult1;
extern volatile uint16_t gAdcResult2;
extern volatile uint16_t gAdcResult3;
extern volatile uint16_t gAdcResult4;
extern volatile uint16_t gAdc_R;
extern volatile uint16_t gAdc_AC;
extern volatile float sum1;
extern volatile float sampleCnt1;
extern volatile int Cnt1;
extern volatile float amp_length[];


// void UserADC_init(void);
// void UserADC0_start(void);
// void UserADC1_start(void);
// uint16_t UserADC0_getData(uint32_t timeout);
// uint16_t UserADC1_getData(uint32_t timeout);
#endif /* #ifndef __USER_ADC_H__ */
