#ifndef __USER_TASK_H__
#define __USER_TASK_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"
#include "RGBLED.h"
#include "UserUART.h"
#include "Encoder.h"
#include "BTN.h"
#include "adc.h"

#define RGB_LED_TIME 10 // RGBLED渐变间隔(ms)
#define UART_TIME 1000 // 串口发送间隔(ms)

extern volatile uint16_t RGBLEDTick;
extern volatile uint16_t UARTTick;

void UserTask_init(void);
void UserTask_loop(void);

#endif /* #ifndef __USER_TASK_H__ */
