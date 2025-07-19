#ifndef __USER_UART_H__
#define __USER_UART_H__

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "ti_msp_dl_config.h"

#define RX_MAX_SIZE 64 // 串口接收最大长度

extern volatile uint8_t RxData[RX_MAX_SIZE];
extern volatile uint8_t RxPos;

int UART0_sendStr(const char* str);
int UART2_sendStr(const char* str);
void UART0_printf(char* fmt, ...);
void UART2_printf(char* fmt, ...);

#endif /* #ifndef __USER_UART_H__ */
