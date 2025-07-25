#include <stdint.h>
#include <msp430g2553.h>
#include <math.h>
#include <string.h>
/*
 * UART.c
 *
 *  Created on: 2023��2��25��
 *      Author: continuation
 */

/*
 * @fn:     void InitUART(void)
 * @brief:  ��ʼ�����ڣ��������ò����ʣ�����λ��У��λ��
 * @para:   none
 * @return: none
 * @comment:��ʼ������
 */
void InitUART(void)
{
//UART��ʼ��
    P1DIR|=BIT1;
    P1DIR|=BIT2;

    /*��λUSCI_Ax*/
    UCA0CTL1 |= UCSWRST;

    /*ѡ��USCI_AxΪUARTģʽ*/
    UCA0CTL0 &= ~UCSYNC;

    /*����UARTʱ��ԴΪSMCLK*/
    UCA0CTL1 |= UCSSEL1;

    /*���ò�����Ϊ9600@16MHz*/
    UCA0BR0 = 130;
    UCA0BR1 = 6;
    UCA0MCTL = 12;
    /*ʹ�ܶ˿ڸ���*/
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;
    /*�����λλ��ʹ��UART*/
    UCA0CTL1 &= ~UCSWRST;
}
/*
 * @fn:     void UARTSendString(uint8_t *pbuff,uint8_t num)
 * @brief:  ͨ�����ڷ����ַ���
 * @para:   pbuff:ָ��Ҫ�����ַ�����ָ��
 *          num:Ҫ���͵��ַ�����
 * @return: none
 * @comment:ͨ�����ڷ����ַ���
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
 * @brief:  ͨ�����ڷ�������
 * @para:   num:����
 * @return: none
 * @comment:ͨ�����ڷ�������
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
  * @brief չʾADC������Ľ�������ݺͲ���ͼ��Ҫͬʱչʾ
  * @param ��
  * @retval ��
  * by shenmengfei@bupt.edu.cn
  */
void UART_Show_ADC_Result(int16_t* adcbuff,int flag)
{
// չʾ��������
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
// չʾ����
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
         //���ηָ��ߣ��ô�������ʾ���θ����
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
  * @brief չʾfft��Ľ��������(1)��Ƶ��ͼ(��1)����ͬʱչʾ
  * @param ��
  * @retval ��
  * by shenmengfei@bupt.edu.cn
  */
void UART_Show_FFT_Result(int16_t* adcbuff,int flag)
{
           int i;
           if(flag==0)
           {
    // չʾfft����
              UARTSendString("begin\n",6);
              for(i=0;i<128;i++)
              {
                 PrintNumber(adcbuff[i]);
              }
           }
           else
           {
   //// չʾ����
              uint8_t tmp[6] = {0x03,0xfc,0,0,0xfc,0x03};

              UARTSendString("begin",6);
              for(i=0;i<128;i++)
              {

                  tmp[3] = adcbuff[i] >> 8;
                  tmp[2] = adcbuff[i] & 0xff;

                 //PrintNumber(adcbuff[i]);
                  UARTSendString(tmp, 6);

              }
   //���ηָ��ߣ��ô�������ʾ���θ����
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
//  * @brief չʾ���������ǰ���г���ķ�ֵ
//  * @param ��
//  * @retval ��
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
    //// չʾƵ��
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
//    //// չʾ����
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
