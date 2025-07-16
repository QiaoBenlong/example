#ifndef __USER_ADC_H__
#define __USER_ADC_H__

#include <stdint.h>
#include <math.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"

/// 环形缓存长度
#define ADC_RECV_LEN    10

#define ADC_VAL_TO_LOAD(x) ((108.9 * (float)x ) / (12288 - 3.3 * (float)x) ) - 0.8

void UserADC_init(void);
void UserADC0_TASK(void);
void UserADC1_TASK(void);

/** 三路平均值循环缓存 */
extern volatile uint16_t length0 ;
extern volatile uint16_t length1 ;
extern volatile float central_freq ;
extern volatile float load ;

extern volatile uint16_t indx0 ;
extern volatile uint16_t indx1 ;

#endif /* #ifndef __USER_ADC_H__ */
