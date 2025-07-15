#include "UserUART.h"
#include "UI.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_uart_main.h"
#include "ti_msp_dl_config.h"

volatile uint8_t RxData[RX_MAX_SIZE] = {'\0'};
volatile uint8_t RxPos = 0;

char temp_str[RX_MAX_SIZE];//调试用的
volatile uint8_t received_data = '0';         //便于调试观察
volatile uint8_t num_str[RX_MAX_SIZE + 1];    // 数字字符数组
volatile uint16_t num_index = 0;              // 数组索引

corrent_operating_t corrent_operating = initial; //当前工作状态

void UART2_init(){
    NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
}

int UART0_sendStr(const char* str) {
    int count = 0;
    while (*str) {
        DL_UART_transmitDataBlocking(UART_0_INST, *str);
        str++;
        count++;
    }
    return count;
}

int UART2_sendStr(const char* str) {
    int count = 0;
    while (*str) {
        DL_UART_transmitDataBlocking(UART_2_INST, *str);
        str++;
        count++;
    }
    return count;
}

void UART0_printf(char* fmt, ...) {
    static char buf[256];
    int len;
    va_list args;
    va_start(args, fmt);
    len = vsprintf(buf, fmt, args);
    va_end(args);
    UART0_sendStr(buf);
}

void UART2_printf(char* fmt, ...) {
    static char buf[256];
    int len;
    va_list args;
    va_start(args, fmt);
    len = vsprintf(buf, fmt, args);
    va_end(args);
    UART2_sendStr(buf);
}

// 串口接收中断
void UART0_IRQHandler(void) {
    if (DL_UART_getPendingInterrupt(UART_0_INST) == DL_UART_IIDX_RX) {
        if (RxPos < RX_MAX_SIZE - 1) {
            RxData[RxPos] = DL_UART_receiveData(UART_0_INST);
            RxData[RxPos + 1] = '\0';
            RxPos++;
        }
    }
}
// 接受串口
void UART2_IRQHandler(void) {
    if (DL_UART_Main_getPendingInterrupt(UART_2_INST) == DL_UART_MAIN_IIDX_RX) {
        received_data = DL_UART_Main_receiveData(UART_2_INST); 
        //先进入测量模式
        if(received_data == 0x30)
            corrent_operating = waiting_length;
        if(received_data == 0x31)
            corrent_operating = waiting_load;
    }
}

