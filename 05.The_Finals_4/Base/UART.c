#include <stdint.h>
#include <msp430g2553.h>
#include <math.h>
#include <string.h>
/*
 * UART.c
 *
 *  Created on: 2023年2月25日
 *      Author: continuation
 */

/*
 * @fn:     void InitUART(void)
 * @brief:  初始化串口，包括设置波特率，数据位，校验位等
 * @para:   none
 * @return: none
 * @comment:初始化串口
 */
void InitUART(void)
{
//UART初始化
    P1DIR|=BIT1;
    P1DIR|=BIT2;

    /*复位USCI_Ax*/
    UCA0CTL1 |= UCSWRST;

    /*选择USCI_Ax为UART模式*/
    UCA0CTL0 &= ~UCSYNC;

    /*配置UART时钟源为SMCLK*/
    UCA0CTL1 |= UCSSEL1;

    /*配置波特率为9600@16MHz*/
    UCA0BR0 = 130;
    UCA0BR1 = 6;
    UCA0MCTL = 12;
    /*使能端口复用*/
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;
    /*清除复位位，使能UART*/
    UCA0CTL1 &= ~UCSWRST;
}
/*
 * @fn:     void UARTSendString(uint8_t *pbuff,uint8_t num)
 * @brief:  通过串口发送字符串
 * @para:   pbuff:指向要发送字符串的指针
 *          num:要发送的字符个数
 * @return: none
 * @comment:通过串口发送字符串
 */
void UARTSendString(uint8_t *pbuff,uint8_t num)
{
    uint8_t cnt = 0;
    for(cnt = 0;cnt < num;cnt ++)
    {
        while(UCA0STAT & UCBUSY);
        //__delay_cycles(5000);
        UCA0TXBUF = *(pbuff + cnt);
    }
}
/*
 * @fn:     void PrintNumber(uint16_t num)
 * @brief:  通过串口发送数字
 * @para:   num:变量
 * @return: none
 * @comment:通过串口发送数字
 */
void PrintNumber(int16_t num)
{
    uint8_t buff[6] = {0,0,0,0,0,','};
    uint8_t cnt = 0;
    uint8_t sf = 0;
    if (num < 0)
    {
        num = -num;
        sf = 1;
    }
    for(cnt = 0;cnt < 5;cnt ++)
    {
        buff[4 - cnt] = (uint8_t)(num % 10 + '0');
        num /= 10;
    }
    if (sf)
    {
        UARTSendString("-",1);
    }
    UARTSendString(buff,6);
    UARTSendString("\n",1);
}

/*
  * @brief 展示ADC采样后的结果，数据和波形图不要同时展示
  * @param 无
  * @retval 无
  * by shenmengfei@bupt.edu.cn
  */
void UART_Show_ADC_Result(int16_t* adcbuff,int flag)
{
// 展示波形数据
       if(flag)
       {
           int i;
           UARTSendString("begin\n",6);
           for(i=0;i<128;i++)
           {
              PrintNumber(adcbuff[i]);
           }
       }

       else
       {
// 展示波形
         uint8_t tmp[6] = {0x03,0xfc,0,0,0xfc,0x03};
         int i;
         //UARTSendString("begin",6);
         for(i=0;i<128;i++)
         {

             tmp[3] = adcbuff[i] >> 8;
             tmp[2] = adcbuff[i] & 0xff;

            //PrintNumber(adcbuff[i]);
             UARTSendString(tmp, 6);

         }
         //波形分割线，让串口上显示波形更清楚
          for(i=0;i<10;i++)
         {

             tmp[3] = 0x00;
             tmp[2] = 255;

            //PrintNumber(adcbuff[i]);
             UARTSendString(tmp, 6);

         }

       }

}




/*
  * @brief 展示fft后的结果，数据(1)和频谱图(非1)不能同时展示
  * @param 无
  * @retval 无
  * by shenmengfei@bupt.edu.cn
  */
void UART_Show_FFT_Result(int16_t* adcbuff,int flag)
{
           int i;
           if(flag==0)
           {
    // 展示fft数据
              UARTSendString("begin\n",6);
              for(i=0;i<128;i++)
              {
                 PrintNumber(adcbuff[i]);
              }
           }
           else
           {
   //// 展示波形
              uint8_t tmp[6] = {0x03,0xfc,0,0,0xfc,0x03};

              UARTSendString("begin",6);
              for(i=0;i<128;i++)
              {

                  tmp[3] = adcbuff[i] >> 8;
                  tmp[2] = adcbuff[i] & 0xff;

                 //PrintNumber(adcbuff[i]);
                  UARTSendString(tmp, 6);

              }
   //波形分割线，让串口上显示波形更清楚
              for(i=0;i<10;i++)
             {

                 tmp[3] = 0x00;
                 tmp[2] = 255;

                //PrintNumber(adcbuff[i]);
                 UARTSendString(tmp, 6);

             }
           }


}
//
//
///*
//  * @brief 展示排序结果后的前五次谐波的幅值
//  * @param 无
//  * @retval 无
//  * by shenmengfei@bupt.edu.cn
//  */
//void UART_Show_THD_Result(int32_t* thdbuff,int item)
//{
//    int i;
//    UARTSendString("max:\n",5);
//    PrintNumber(item);
//    UARTSendString("thdbuff:\n",9);
//    for(i = 0; i < 6; i++)
//    {
//        int t = sqrtf(thdbuff[i]);
//        PrintNumber(t);
//    }
//    UARTSendString("THD:\n",5);
//    PrintNumber(thd);
//}
//
void UART_Show_Spectrum(int32_t* adcbuff,int num)
{
    //// 展示频谱
       uint8_t tmp[8] = {0x03,0xfc,0,0,0,0,0xfc,0x03};
       int i;
       float temp;
       for(i=0;i<num;i++)
       {
           temp = sqrtf(adcbuff[i]);
           memmove(tmp+2,(char *)&temp,4);
           UARTSendString(tmp, 8);
       }

}
//
//void UART_Show_THD(float* thdbuff,int num)
//{
//    //// 展示波形
//               uint8_t tmp[8] = {0x03,0xfc,0,0,0,0,0xfc,0x03};
//               int i;
//               for(i=0;i<num;i++)
//               {
//
//                   memmove(tmp+2,(char *)&thdbuff[i],4);
//                   UARTSendString(tmp, 8);
//
//               }
//
//}
