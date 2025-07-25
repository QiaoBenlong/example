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
#include "DDS.h"



#define UI_TIME 500 // UI界面刷新间隔(ms)
#define UI_INFO_TIME 3000 // INFO界面显示时间(ms)
#define RGB_LED_TIME 10 // RGBLED渐变间隔(ms)
#define UART_TIME 1000 // 串口发送间隔(ms)
#define GAIN_CTRL_TIME 10 // 增益控制间隔(ms)
#define DDS_SWEEP_TIME 5 // DDS扫描间隔(ms)
#define DDS_SWEEP_TIME_SET  ((2000*freq_step)/(freq_end - freq_start)) * DDS_SWEEP_TIME

#define FREQ_TO_LENGTH(x) (9.93e9f / (float)x ) * 1.5754 - 139.14//加入公式

extern volatile uint16_t UITick;
extern volatile uint16_t UIInfoTick;
extern volatile uint16_t RGBLEDTick;
extern volatile uint16_t UARTTick;
extern volatile uint16_t GainCtrlTick;
extern volatile uint16_t SweepTick;
extern volatile float freq;
extern volatile int flag;
extern volatile uint16_t amp;
extern volatile int fA_flag;
extern DDS_SweepParam_t Sweep[3];


void UserTask_init(void);
void UserTask_loop(void);
void UserTask_BTN(void);
void UserTask_ENC(void);
extern void initSweepParam(void);



void AD_init(void);
void AD_loop(void);

// void initSingleToneParam(void);
// void initSweepParam(void);

#endif /* #ifndef __USER_TASK_H__ */
