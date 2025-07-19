#include "UserTask.h"

volatile uint16_t UITick = 0;
volatile uint16_t UIInfoTick = UI_INFO_TIME; // INFO界面显示倒计时
volatile uint16_t RGBLEDTick = 0;
volatile uint16_t UARTTick = 0;
volatile uint16_t GainCtrlTick = 0;

void UserTask_init(void) {
    UserADC_init();
    ENC_init();
    UI_init();
}

void UserTask_loop(void) {
    UI_taskBTN();
    UI_taskENC();
    if (UITick >= UI_TIME) {
        UITick = 0;
        if (UIInfoTick) UIPage = PAGE_INFO;
        else UIPage = PAGE_DATA;
        UI_taskShow();
    }

    if (RGBLEDTick >= RGB_LED_TIME) {
        RGBLEDTick = 0;
        RGBLED_taskRainbow();
    }
    
    if (UARTTick >= UART_TIME) {
        UARTTick = 0;
        //UART0_printf("Tick = %ld\n", Tick);
    }

    if (GainCtrlTick >= GAIN_CTRL_TIME) {
        GainCtrlTick = 0;
        GainCtrl_taskGetData();
        GainCtrl_taskCtrl();
    }
}
