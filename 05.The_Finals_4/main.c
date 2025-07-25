#include <msp430.h> 
#include "LCD.h"
#include<BASE.h>
#include <stdint.h>
#include"UART.h"
#include <string.h>
#include"measure.h"
#include"menu.h"
#include<FFT.h>


//测量频率和占空比
unsigned int Forward_Posedge_Flag = 1, Counting_Flag=0, Negedge_Flag=0;
unsigned long int Posedge1_data=0,Posedge2_data=0,Negedge_data=0;
uint32_t fre=0;
int num=0;
int num1=0,num2=0;

//adc采样数据
int16_t adcbuff[128]={0};
int32_t *adcbuff2 = &adcbuff;
uint8_t cnt = 0;
//菜单辅助

short x_1_5=2;
short start=0;

void Calculate_Data()
{
    Posedge2_data =  Posedge2_data + 65536 * (num1+num2);
    fre = 16000000 / (Posedge2_data - Posedge1_data) ;
}





/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    InitSystemClock();
    GPIO_Init();
    initial_lcd();
    Interrupt();
//    InitUART();
    clear_screen();
    display_start();


    double Vpp=0;
//    uint16_t fre_num={0};

    while(1)
    {
        clear_screen();

        switch(x_1_5)
        {
            case 1://显示频率
            {
//                x_1_5++;
                InitTimer0();
                while(x_1_5==1)
                {
                    __bis_SR_register(GIE);
                    display_show_Freq(fre);
                    _delay_cycles(5000);
                }
                Close_Timer();
            }
            break;
            case 2://显示幅度
            {
                ADC_Undersampling(2,fre);
                __bis_SR_register(GIE);
                InitADC(1);

                while(x_1_5==2)
                {
                    if(cnt==128)
                    {
                       clear_screen();
                       int16_t max=adcbuff[1];
                       int16_t min=adcbuff[1];
                       int i;
                       for(i=0;i<128;i++)
                       {
                           if(max<adcbuff[i])
                               max=adcbuff[i];
                           if(min>adcbuff[i])
                               min=adcbuff[i];
                       }
                       Vpp=(max-min)*3.5/1024;
                       display_GB2312_string(3,5,"Amplitude:");
                       display_float(5,40,Vpp/2);
                       display_GB2312_string(5,95,"V");
                       delay_nms(5000);
                    }
                    cnt=0;
                    delay_nms(5000);
                 }


              }
            break;
            case 3://显示波形
            {

                ADC_Undersampling(2,fre);
                InitADC(3);
                while(x_1_5==3)
                {
                    if(cnt==128)
                    {
                        clear_screen();
                        display_1(adcbuff,adcbuff2,120,1);
                        delay_nms(5000);
                    }
                    cnt=0;
                    delay_nms(20000);
                }
            }
            break;
            case 4://显示频谱
            {
//                    int a=0;
//                    for(a=0;a<128;a++)
//                    {
//                        adcbuff[a]=0;
//                    }
//                Close_Timer();
                ADC_Undersampling(4,fre);
                InitADC(3);
                short on_show=1;
                while(x_1_5==4)
                {

                    delay_nms(5000);
                    if(cnt==128)
                    {
                        clear_screen();
                        fft();
                        Modulo();
                        display_1(adcbuff,adcbuff2,60,2);
                    }
                    cnt=0;
                    delay_nms(20000);
                }
                x_1_5=5;
            }
            break;
            case 5:
            {
                InitUART();
                display_GB2312_string(4,14,"串口显示数据");
                while(x_1_5==5)
                {
                        UARTSendString("Frequence(Hz):\n",15);
//                        PrintNumber(fre_num);
                        UARTSendString("Amplitude(mV):\n",14);
                        PrintNumber(Vpp*1000/2);
                        UARTSendString("THD:\n",5);
                        delay_nms(800);
                }
//                    delay_nms(8000);
            }
            break;
            default:break;
        }
        Close_Timer();
         Interrupt();
         delay_nms(50000);
        }

    return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
    if(P1IFG & BIT3)//
    {
        __delay_cycles(10000);           //延时消抖 所传递参数为cpu周期
        P1IFG &= ~BIT3;//
        if((P1IN & BIT3)==0)
        {
            if(start)
                x_1_5=(x_1_5)%5+1;
            start=1;
        }

    }
}


#pragma vector = TIMER1_A1_VECTOR
__interrupt void Time_Tick(void)
{
    switch(TA1IV)
        {
        case 0x0A:
            if(cnt < 128)
            {
                StartADCConvert();
                cnt++;
            }
            break;
        default:break;
        }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    if(TA0CCTL0 & CCI)
     {

        if(Forward_Posedge_Flag)  //First rising edge captured
            {
                Posedge1_data = TA0CCR0;
                Forward_Posedge_Flag = 0;
                Counting_Flag = 1;

            }
        else if(Counting_Flag = 1 && Negedge_Flag==1) //Second rising edge captured
            {
                TA0CTL &=TAIE;
                TA0CCTL0 &= ~(COV+CCIE);
                Posedge2_data =  TA0CCR0;

                Calculate_Data();
                Counting_Flag = 0;
                Posedge1_data = 0;
                Posedge2_data = 0;
                Negedge_data = 0;
                Forward_Posedge_Flag = 1;
                Negedge_Flag=0;
                num=0;
                num1=0;
                num2=0;
                TA0CTL= TASSEL_2 + TACLR + MC_2 + TAIE;
                TA0CCTL0 = CM_3 + CCIS_0 + SCS + CAP + CCIE ;
                __bic_SR_register_on_exit(GIE);  // Exit LPM0 on return to main

            }
    }
    else
    {
        // Falling Edge was captured
        if(Counting_Flag==1 && Negedge_Flag==0)
        {
            Negedge_data =  TA0CCR0;
            Negedge_Flag = 1;
        }
    }

}

#pragma vector = TIMER0_A1_VECTOR                //TAIFG中断
__interrupt void Timer_A_IV(void)
{
    if(TA0IV==0X0A)
    {
        num= num+1;
        if(Counting_Flag == 1 && Negedge_Flag==0)
        {
            num1++;
        }
        else if(Counting_Flag == 1 && Negedge_Flag==1)
        {
            num2++;
        }
    }
}

