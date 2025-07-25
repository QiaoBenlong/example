/*
 * measure.h
 *
 *  Created on: 2023Äê3ÔÂ8ÈÕ
 *      Author: continuation
 */

#ifndef MEASURE_MEASURE_H_
#define MEASURE_MEASURE_H_


float get_vpp(int16_t* adcbuff,int num);
//void Calculate_Data();
int ADC();
void ADC_Undersampling(short flag,double fre);
double get_rms_1(int16_t* adcbuff,int num);
double get_rms_2(int16_t* adcbuff,int num);
void get_vpp_rms(int16_t* adcbuff,int num,double* Vpp,double* Vrms);
#endif /* MEASURE_MEASURE_H_ */
