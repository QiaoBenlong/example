#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "UI.h"
#include "UserUART.h"

#define ENC_SW_PRESS (DL_GPIO_readPins(GPIO_ENC_ENC_SW_PORT, GPIO_ENC_ENC_SW_PIN) == 0)
#define ENC_SW_DEBOUNCE_TIME 100 // 旋转编码器按钮消抖时间(ms) 

extern volatile uint8_t ENCSWTick;

void ENC_init(void);
int ENC_getIncVal(void);
uint8_t ENC_getSW(void);
void ENC_TASK(void);

extern volatile float step_size;//步长增量
extern volatile uint16_t enc_number; //按键次数 用于选择控制数据的类型
extern volatile int outset;//编码器增量

#endif /* #ifndef __ENCODER_H__ */
