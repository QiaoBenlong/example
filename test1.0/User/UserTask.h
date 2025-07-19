#ifndef __USER_TASK_H__
#define __USER_TASK_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"
#include "DDS.h"
#include "Encoder.h"
#include "BTN.h"
#include "UserADC.h"

#define DDS_SWEEP_TIME 20 // DDS扫描间隔(ms)
#define UI_TIME 100
extern volatile uint16_t SweepTick;

void UserTask_init(void);
void UserTask_loop(void);

#endif /* #ifndef __USER_TASK_H__ */
