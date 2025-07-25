/*
 * measure.c
 *
 *  Created on: 2023年3月8日
 *      Author: continuation
 */




#include <msp430.h>
#include <stdint.h>
#include<BASE.h>
#include<math.h>

//extern unsigned int Forward_Posedge_Flag,Counting_Fla,Negedge_Flag;
//extern unsigned long int Posedge1_data,Posedge2_data,Negedge_data;
//extern double fre, duty_cycle;
//extern int num; //测试用
//extern int num1,num2;
//extern int16_t adcbuff[128];


float get_vpp(int16_t* adcbuff,int num)
{
    int16_t max=adcbuff[0];
    int16_t min=adcbuff[0];
    int i;

    for(i=0;i<num;i++)
    {
        if(max<adcbuff[i])
            max=adcbuff[i];
        if(min>adcbuff[i])
            min=adcbuff[i];
    }

    float vpp=(max-min)*2.5/1024;
    return vpp;
}

//double get_rms_1(int16_t* adcbuff,int num)
//{
//    int16_t max=adcbuff[0];
//    int16_t min=adcbuff[0];
//
//    int max_index[10]={0};
//    int min_index[10]={0};
//    int max_num=0;
//    int min_num=0;
//    int n;
////    int64_t result=0;
//    double rms=0;
//
//    int i;
//    for(i=0;i<num;i++)
//    {
//        if(max<adcbuff[i])
//            max=adcbuff[i];
//
//        if(min>adcbuff[i])
//            min=adcbuff[i];
//    }//找出最大最小值
//
//    for(i=0;i<num;i++)
//    {
//        if(max==adcbuff[i])
//            max_index[max_num++]=i;
//
//        if(min==adcbuff[i])
//            min_index[min_num++]=i;
//    }//获得最大最小值下标索引
//    for(i=0;i<3;i++)
//    {
//        if(min_index[i]-max_index[0]>20)
//            break;
//    }
//    n=i;
//
//    for(i=max_index[0];i<=min_index[n];i++)
//    {
//        rms+=((double)adcbuff[i]*2.5/1024)*((double)adcbuff[i]*2.5/1024);
//    }
//
//    return sqrt(rms)/(n-max_index[0]);
//}

//double get_rms_2(int16_t* adcbuff,int num)
//{
//    int16_t max=adcbuff[0];
//    int16_t min=adcbuff[0];
//    //    int64_t result=0;
//
//    int i;
//    for(i=0;i<num;i++)
//    {
//        if(max<adcbuff[i])
//            max=adcbuff[i];
//
//        if(min>adcbuff[i])
//            min=adcbuff[i];
//    }//找出最大最小值
//
//    double rms=(max-min)*2.5/1024.0;
//
//    return rms/2.0/sqrt(2);
//
//}

void get_vpp_rms(int16_t* adcbuff,int num,double* Vpp,double* Vrms)
{
    int16_t max=adcbuff[0];
    int16_t min=adcbuff[0];
    int i;
    for(i=0;i<num;i++)
    {
        if(max<adcbuff[i])
            max=adcbuff[i];
        if(min>adcbuff[i])
            min=adcbuff[i];
    }
    *Vpp=(max-min)*2.5/1024;
    *Vrms=*Vpp/2.0/sqrt(2);
}


//void Calculate_Data()
//{
//    Posedge2_data =  Posedge2_data + 65536 * (num1+num2);
//    Negedge_data = Negedge_data +  65536 * num1;
//
//    fre = 16000000.0 / (Posedge2_data - Posedge1_data) ;
//
//    duty_cycle = ((double)(Negedge_data - Posedge1_data)) / ((double)(Posedge2_data - Posedge1_data)) ;
//
////    pulse_width = ( Negedge_data - Posedge1_data) / 16.0 ; //unit:us
//
//}


void ADC_Undersampling(short flag,double fre)
{
    if(flag==2||flag==4)
        InitTimer1_wave();
    else if(flag==3)
        InitTimer1(fre);
}
