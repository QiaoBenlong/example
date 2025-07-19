#ifndef __USER_TASK_H__
#define __USER_TASK_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"
#include "UI.h"
#include "RGBLED.h"
#include "UserUART.h"
#include "Encoder.h"
#include "BTN.h"
#include "UserADC.h"
#include "GainCtrl.h"

#define UI_TIME 100 // UI界面刷新间隔(ms)
#define UI_INFO_TIME 3000 // INFO界面显示时间(ms)
#define RGB_LED_TIME 10 // RGBLED渐变间隔(ms)
#define UART_TIME 1000 // 串口发送间隔(ms)
#define GAIN_CTRL_TIME 10 // 增益控制间隔(ms)

extern volatile uint16_t UITick;
extern volatile uint16_t UIInfoTick;
extern volatile uint16_t RGBLEDTick;
extern volatile uint16_t UARTTick;
extern volatile uint16_t GainCtrlTick;

void UserTask_init(void);
void UserTask_loop(void);

#endif /* #ifndef __USER_TASK_H__ */
