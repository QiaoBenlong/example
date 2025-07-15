#ifndef __UI_H__
#define __UI_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "UserUART.h"
#include "UserTask.h"
#include "Encoder.h"
#include "BTN.h"
#include "DDS.h"
#include "UserADC.h"

// UI界面
typedef enum UIPage_t {
    PAGE_INFO, // 信息界面
    PAGE_DATA,  // 数据界面
} UIPage_t;


extern UIPage_t UIPage;
extern volatile uint16_t UITick;
void UI_init(void);
void UI_taskShow(void);
void draw_picture(void);

#endif /* #ifndef __UI_H__ */
