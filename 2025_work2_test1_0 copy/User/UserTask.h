#ifndef __USER_TASK_H__
#define __USER_TASK_H__

#include <stdint.h>
#include "UserTask.h"
#include "ti_msp_dl_config.h"
#include "Tick.h"
#include "DDS.h"
#include "Encoder.h"
#include "BTN.h"
#include "UserADC.h"
#include "GET_FREQ.h"

#define DDS_SWEEP_TIME 10 // DDS扫描间隔(ms)
#define UI_TIME 50
#define ADC_TIME 100

#define FREQ_TO_LENGTH(x) (9.93e9f / (float)x ) * 1.5754 - 139.14

typedef enum loaded_t {
    Open,     
    Res,
    Cap,    
} loaded_t;

extern volatile uint16_t SweepTick;
extern loaded_t loaded;

void UserTask_init(void);
void UserTask_loop(void);

#endif /* #ifndef __USER_TASK_H__ */
