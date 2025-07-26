#ifndef __UI_H__
#define __UI_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "UserUART.h"
#include "UserTask.h"
#include "Encoder.h"
#include "BTN.h"


#define CONSTRAIN(x, min, max) (x < min ? min : (x > max ? max : x))
#define CONSTRAIN_ABOVE(x, min) (x < min ? min : x)
#define CONSTRAIN_BELOW(x, max) (x > max ? max : x)

// UI界面
typedef enum UIPage_t {
    PAGE_INFO, // 信息界面
    PAGE_DATA  // 数据界面
} UIPage_t;

extern UIPage_t UIPage;

void UI_init(void);
void UI_taskShow1(void);
void UI_taskShow2(void);
void UI_taskShow3(void);
void UI_taskBTN(void);
void UI_taskENC(void);

#endif /* #ifndef __UI_H__ */
