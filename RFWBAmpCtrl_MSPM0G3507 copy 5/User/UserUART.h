#ifndef __USER_UART_H__
#define __USER_UART_H__

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include "ti_msp_dl_config.h"

#define RX_MAX_SIZE 64 // 串口接收最大长度



typedef enum corrent_operating_t {
    initial,     
    waiting_length,
    waiting_load,   
    finish, 
} corrent_operating_t;//trans

extern volatile uint8_t RxData[RX_MAX_SIZE];
extern volatile uint8_t RxPos;

extern volatile uint8_t RxData[RX_MAX_SIZE];
extern volatile uint8_t RxPos;
extern volatile uint8_t num_str[RX_MAX_SIZE + 1]; // 数字字符数组
extern volatile float data_of_test;
extern corrent_operating_t corrent_operating;//trans
extern volatile float  freq_start;
extern volatile float  freq_end;
extern volatile float freq_step;
extern volatile int print_flag;
extern volatile int order_flag;
extern volatile int start_flag;

void UART2_init();
int UART0_sendStr(const char* str);
int UART2_sendStr(const char* str);
void UART0_printf(char* fmt, ...);
extern void UART2_printf(char* fmt, ...);

#endif /* #ifndef __USER_UART_H__ */
