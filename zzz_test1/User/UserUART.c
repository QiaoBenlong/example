#include "UserUART.h"

volatile uint8_t RxData[RX_MAX_SIZE] = {'\0'};
volatile uint8_t RxPos = 0;

int UART_sendStr(const char* str) {
    int count = 0;
    while (*str) {
        DL_UART_transmitDataBlocking(UART_0_INST, *str);
        str++;
        count++;
    }
    return count;
}

int TJC_UART_sendStr(const char* str) {
    int count = 0;
    while (*str) {
        DL_UART_transmitDataBlocking(UART_2_INST, *str);
        str++;
        count++;
    }
    return count;
}

void UART_printf(char* fmt, ...) {
    static char buf[256];
    int len;
    va_list args;
    va_start(args, fmt);
    len = vsprintf(buf, fmt, args);
    va_end(args);
    UART_sendStr(buf);
}

void TJC_UART_printf(char* fmt, ...) {
    static char buf[256];
    int len;
    va_list args;
    va_start(args, fmt);
    len = vsprintf(buf, fmt, args);
    va_end(args);
    TJC_UART_sendStr(buf);
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

void UART2_IRQHandler(void) {
    if (DL_UART_getPendingInterrupt(UART_2_INST) == DL_UART_IIDX_RX) {
        if (RxPos < RX_MAX_SIZE - 1) {
            RxData[RxPos] = DL_UART_receiveData(UART_2_INST);
            RxData[RxPos + 1] = '\0';
            RxPos++;
        }
    }
}
