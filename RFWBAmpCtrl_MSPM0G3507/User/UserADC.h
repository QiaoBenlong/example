#ifndef __USER_ADC_H__
#define __USER_ADC_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"

#define ADC_VREF 3.3F // ADC基准电压
// ADC值转为电压(V)
#define ADC_VAL_TO_VOLTAGE(x) ((float)x * ADC_VREF / 4096)

void UserADC_init(void);
void UserADC0_start(void);
void UserADC1_start(void);
uint16_t UserADC0_getData(uint32_t timeout);
uint16_t UserADC1_getData(uint32_t timeout);

#endif /* #ifndef __USER_ADC_H__ */
