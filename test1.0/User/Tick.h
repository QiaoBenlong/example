#ifndef __TICK_H__
#define __TICK_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "UserTask.h"
#include "Encoder.h"
#include "BTN.h"
#include "UI.h"
extern volatile uint32_t Tick;
/**
 * @brief 延时(使用SysTick中断计时)
 * @param t 延时时间(ms)
*/
void Tick_delay(uint32_t t);

void SysTick_Handler(void);

#endif /* #ifndef __TICK_H__ */
