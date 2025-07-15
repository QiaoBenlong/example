#ifndef __BTN_H__
#define __BTN_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "DDS.h"
#include "Encoder.h"

#define BTN_LEFT_PRESS  (DL_GPIO_readPins(GPIO_BTN_PORT, GPIO_BTN_LEFT_PIN) == 0)
#define BTN_DOWN_PRESS  (DL_GPIO_readPins(GPIO_BTN_PORT, GPIO_BTN_DOWN_PIN) == 0)
#define BTN_RIGHT_PRESS (DL_GPIO_readPins(GPIO_BTN_PORT, GPIO_BTN_RIGHT_PIN) == 0)
#define BTN_UP_PRESS    (DL_GPIO_readPins(GPIO_BTN_PORT, GPIO_BTN_UP_PIN) == 0)
#define BTN_MID_PRESS   (DL_GPIO_readPins(GPIO_BTN_PORT, GPIO_BTN_MID_PIN) == 0)

#define BTN_DEBOUNCE_TIME 250 // 按键消抖时间(ms)

// 按键数据
typedef struct BTNData_t {
    uint8_t left;
    uint8_t down;
    uint8_t right;
    uint8_t up;
    uint8_t mid;
} BTNData_t;

// 按键消抖倒计时
typedef struct BTNTick_t {
    uint16_t left;
    uint16_t down;
    uint16_t right;
    uint16_t up;
    uint16_t mid;
} BTNTick_t;

extern BTNTick_t BTNTick;
extern BTNData_t BTNData;
void BTN_getData(BTNData_t* data);

#endif /* #ifndef __BTN_H__ */
