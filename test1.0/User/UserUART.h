#ifndef __USER_UART_H__
#define __USER_UART_H__

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "ti_msp_dl_config.h"
#include "DDS.h"

#define RX_MAX_SIZE 64 // 串口接收最大长度

extern volatile uint8_t RxData[RX_MAX_SIZE];
extern volatile uint8_t RxPos;
extern volatile uint8_t num_str[RX_MAX_SIZE + 1]; // 数字字符数组

void UART2_init(void);
int UART0_sendStr(const char* str);
int UART2_sendStr(const char* str);
void UART0_printf(char* fmt, ...);
void UART2_printf(char* fmt, ...);
#endif /* #ifndef __USER_UART_H__ */
