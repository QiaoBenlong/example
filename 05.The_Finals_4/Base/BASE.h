/*
 * BASE.h
 *
 *  Created on: 2022??11??19??
 *      Author: continuation
 */

#ifndef BASE_BASE_H_
#define BASE_BASE_H_
#include <stdint.h>
void delay_nms(unsigned int k);
void GPIO_Init(void);
void InitSystemClock(void);
void InitADC(short choose);
void StartADCConvert(void);
void Interrupt(void);
void InitTimer0(void);
void InitTimer1(double freq);
void InitTimer1_wave();
void Close_Timer();
#endif /* BASE_BASE_H_ */
