#ifndef __VOLT_GAIN_H__
#define __VOLT_GAIN_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "UserADC.h"
#include "UserTask.h"
#include "DDS.h"

extern float Gain;
extern volatile float volt_in;
extern volatile float volt_out;
void Volt_Gain_taskGetData();

#endif /* #ifndef __VOLT_GAIN_H__ */
