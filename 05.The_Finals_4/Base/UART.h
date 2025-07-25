/*
 * UART.h
 *
 *  Created on: 2023Äê2ÔÂ25ÈÕ
 *      Author: continuation
 */

#ifndef BASE_UART_H_
#define BASE_UART_H_
#include <stdint.h>
void InitUART(void);
void UARTSendString(uint8_t *pbuff,uint8_t num);
void PrintNumber(int16_t num);
void UART_Show_FFT_Result(int16_t* adcbuff,int flag);
//void UART_Show_THD_Result(int32_t* thdbuff,int item);
void UART_Show_ADC_Result(int16_t* adcbuff,int flag);
//void UART_Show_THD(float* thdbuff,int num);
void UART_Show_Spectrum(int32_t* adcbuff,int num);
#endif /* BASE_UART_H_ */
