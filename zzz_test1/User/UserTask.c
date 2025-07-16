#include "UserTask.h"

volatile uint16_t RGBLEDTick = 0;
volatile uint16_t UARTTick = 0;

int ENCCount = 0;
BTNData_t BTNData = {0};

void UserTask_init(void) {
    ENC_init();
    adc_init();
}

void UserTask_loop(void) {
    ENCCount += ENC_getIncVal();
    if (ENC_getSW()) {
        UART_printf("Encoder SW Pressed\n");
    }

    BTN_getData(&BTNData);
    if (BTNData.left) {
        TJC_UART_printf("page1.t0.txt=\"按键-左\"%c%c%c",0xff,0xff,0xff);
        UART_printf("Left Pressed\n");
    }
    if (BTNData.down) {
        TJC_UART_printf("page1.t0.txt=\"按键-下\"%c%c%c",0xff,0xff,0xff);
        UART_printf("Down Pressed\n");
    }
    if (BTNData.right) {
        TJC_UART_printf("page1.t0.txt=\"按键-右\"%c%c%c",0xff,0xff,0xff);
        UART_printf("Right Pressed\n");
    }
    if (BTNData.up) {
        TJC_UART_printf("page1.t0.txt=\"按键-上\"%c%c%c",0xff,0xff,0xff);
        UART_printf("Up Pressed\n");
    }
    if (BTNData.mid){
        TJC_UART_printf("page1.t0.txt=\"按键-中\"%c%c%c",0xff,0xff,0xff);
        UART_printf("Mid Pressed\n");
    }

    if (RGBLEDTick >= RGB_LED_TIME) {
        RGBLEDTick = 0;
        RGBLED_taskRainbow();
    }
    
    if (UARTTick >= UART_TIME) {
        UARTTick = 0;
        UART_printf("Hello World!  ");
        UART_printf("Tick = %ld  ", Tick);
        UART_printf("ENCCount = %d\n", ENCCount);
    }
}
