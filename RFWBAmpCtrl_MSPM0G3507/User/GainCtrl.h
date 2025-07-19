#ifndef __GAIN_CTRL_H__
#define __GAIN_CTRL_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "UserADC.h"
#include "UI.h"

// AD8310模块参数设定
#define SLOPE 0.024F // 检波斜率(V/dB)
#define INTERCEPT (-95.0F) // 检波截距(dBm@50Ω)
// 电压(V)转为功率(dBm@50Ω)
#define VOLTAGE_TO_POWER(x) (x / SLOPE + INTERCEPT)

#define GAIN_SET_MIN -5.0F // 增益设定最小值
#define GAIN_SET_MAX 65.0F // 增益设定最大值
#define GAIN_TOLERANCE 0.5F // 增益容差(dB)

#define MOVING_AVER_N 1 // 移动平均次数

#define CTRL_VAL_MIN 665 // 控制量最小值
#define CTRL_VAL_MAX 920 // 控制量最大值

extern float GainSet;
extern float GainReal;
extern float PowerIn;
extern float PowerOut;

float movingAverage(float* q, int len, float new);
void GainCtrl_getCtrlVal(void);

void GainCtrl_taskGetData(void);
void GainCtrl_taskCtrl(void);

#endif /* #ifndef __GAIN_CTRL_H__ */
