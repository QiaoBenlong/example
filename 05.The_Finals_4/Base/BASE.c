#include <msp430g2553.h>
#include<stdint.h>
#include "BASE.h"
extern int16_t adcbuff[128];

/* *************************************************************
  *@ brief  nms???????
  *@ param  k???????????????
  *@ retval ??
  *@comment ????????????????????????????????????j???��
  by zheng.hao@bupt.edu.cn
*********************************************************** */
void delay_nms(unsigned int k)
{
    unsigned int i = 0;
    unsigned int j;
    for (i = 0; i <k ; i++)
    {
        for (j = 0; j<40; j++);
    }
}

/* *************************************************************
  *@ brief  ????????????
  *@ param  ??
  *@ retval ??
  *@comment ???????????????
  by zheng.hao@bupt.edu.cn
*********************************************************** */

void GPIO_Init(void)
{
    P1DIR &= ~BIT4;
//    adc�������ų�ʼ��
        //P1REN &= ~BIT0;

    P2DIR &= ~BIT4;//Rom_out���ų�ʼ��
    P2DIR |= BIT0+BIT1+BIT2+BIT3+BIT5;
    P1DIR |=BIT5+BIT6+BIT7;
    //LCD���ų�ʼ��



}

/*
 * @brief ��ʼ��ϵͳʱ��
 * @param ��
 * @retval ��
 * by zheng.hao@bupt.edu.cn
 */

//void InitTimer0(void)
//{
//    TA0CTL |= TASSEL_2;//
//    TA0CTL |= MC_1;//
//    TA0CCR0 = 119;//
//    TA0CTL |= TAIE;
//}

void InitTimer0(void)
{
//    P1DIR &= ~BIT1;
    P1SEL|=BIT1; //set input as TA0.CCI0A at P1.1
    TA0CTL = TASSEL_2 + TACLR + MC_2 + TAIE;
    TA0CCTL0  = CM_3 + CCIS_0 + SCS + CAP ;
}

void InitTimer1(double freq)//����Ӧ����
{
    TA1CTL |= TASSEL_2;//
    TA1CTL |= MC_1;//
    TA1CCR0 = (int32_t)(16*1000000/(freq*99/100))-1;//
    TA1CTL |= TAIE;
}

void InitTimer1_wave()//���4-5khz��ʼ��
{
    TA1CTL |= TASSEL_2;//
    TA1CTL |= MC_1;//

    //79

//    TA1CCR0 = 132;
    TA1CCR0 = 79;
    TA1CTL |= TAIE;
}


/*
 * @brief ��ʼ��ϵͳʱ��
 * @param ��
 * @retval ��
 * by zheng.hao@bupt.edu.cn
 */
//void InitTimer1(void)
//{
//       /*����ʱ��ԴΪSMCLK*/
//       TA1CTL |= TASSEL_2;
//       /*���ù���ģʽΪUp Mode*/
//       TA1CTL |= MC_1;
//       /*���ö�ʱ���*/
//       TA1CCR0 = 49999;//50ms
//       /*����TAIFG�ж�*/
//       TA1CTL |= TAIE;
//       /*TA1,CCR2���ڲ�׽����*/
//       TA1CCTL2 |= CAP;
//       /*�����ز�׽*/
//       TA1CCTL2 |= CM_1;
//
//       /*P2.5��Ϊ��׽����(CCI2B)*/
//       TA1CCTL2 |= CCIS0;
////       P2SEL |= BIT5;
//
//       /*����׽�Ƚ��ж�*/
//       TA1CCTL2 |= CCIE;
//}

//void InitTimer0(void)
//{
//       /*����ʱ��ԴΪSMCLK*/
//       TA0CTL |= TASSEL_2;
//       /*���ù���ģʽΪUp Mode*/
//       TA0CTL |= MC_1;
//       /*���ö�ʱ���*/
//       TA0CCR0 = 49999;//50ms
//       /*����TAIFG�ж�*/
//       TA0CTL |= TAIE;
//
//       /*TA1,CCR2���ڲ�׽����*/
//       TA0CCTL1 |= CAP;
//       /*�����ز�׽*/
//       TA0CCTL1 |= CM0;
//       /*P2.6��Ϊ��׽����(CCI1B)*/
//       TA0CCTL1 |= CCIS0;
//       P2SEL |= BIT6;
//       /*����׽�Ƚ��ж�*/
//       TA0CCTL1 |= CCIE;
//}






void InitSystemClock(void)
{
    /*����DCOΪ16MHz*/
    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    /*����SMCLK��ʱ��ԴΪDCO*/
    BCSCTL2 &= ~SELS;
    /*SMCLK�ķ�Ƶϵ����Ϊ1*/
    BCSCTL2 &= ~(DIVS0 | DIVS1);
}

/*
 * @brief ��ʼADCת��
 * @param ��
 * @retval ��
 * by zheng.hao@bupt.edu.cn
 */
void StartADCConvert(void)
{
      ADC10CTL0 |= ADC10SC|ENC; // ��ʼת��
      while(ADC10CTL1&ADC10BUSY); // �ȴ�ת�����
}


 /*
  * @brief ��ʼ����ʱ��
  * @param ��
  * @retval ��
  * by shenmengfei@bupt.edu.cn
  */
 void Interrupt(void)
 {
     /*��ʼ����������IO��P1.3Ϊ����*/
      P1DIR &= ~BIT3;
      /*ʹ��P1.3�ڵ���������*/
      P1REN |= BIT3;
      P1OUT |= BIT3;
      /*��P1.3���ж�*/
      P1IE |= BIT3;
      /*�趨Ϊ�½��ش���*/
      P1IES |= BIT3;
      /*����жϱ�־λ*/
      P1IFG &= ~BIT3;

//      /*��ʼ����������IO��P2.5Ϊ����*/
//       P2DIR &= ~BIT5;
//       /*ʹ��P2.5�ڵ���������*/
//       P2REN |= BIT5;
//       P2OUT |= BIT5;
//       /*��P2.5���ж�*/
//       P2IE |= BIT5;
//       /*�趨Ϊ�½��ش���*/
//       P2IES |= BIT5;
//       /*����жϱ�־λ*/
//       P2IFG &= ~BIT5;


      /*��ȫ���ж�*/
      __bis_SR_register(GIE);
 }


/*
 * @brief ��ʼ��ADC,������ADCADCת���������adcbuff������
 * @param ��
 * @retval ��
 * by zheng.hao@bupt.edu.cn
 */
void InitADC(short choose)
{
          /*����ADCʱ��MCLK*/
//    ADC10CTL1 |= ADC10SSEL_2;
          ADC10CTL1 |= ADC10SSEL_0;
          /*����ADC��׼Դ*/
          switch(choose)
          {
              case 1:ADC10CTL0 |= SREF_0;break;/*ADC��׼ѡ��Vcc*/
              case 2:ADC10CTL0 |= SREF_0;break;/*ADC��׼ѡ��Vcc*/
              case 3:ADC10CTL0 |= SREF_1;ADC10CTL0 |= REF2_5V;/*ADC��׼ѡ��2.5V*/break;
              default:ADC10CTL0 |= SREF_1;ADC10CTL0 |= REF2_5V;break;
          }
          /*����ADC��������ʱ��16CLK*/
          ADC10CTL0 |= ADC10SHT_2;
          /*����ADC��������200k*/
          ADC10CTL0 |= ADC10SR;
          /*������׼*/
          ADC10CTL0 |= REFON;
          /*ѡ��ADC����ͨ��A4*/
          ADC10CTL1 |= INCH_4;
          /*����A4ģ������*/
          ADC10AE0 |= 1<<4;
          /*DTC����ģʽ*/
          ADC10DTC0 |= ADC10CT;
          /*�������*/
          ADC10DTC1 = 128;
          /*��ʼ��ַ*/
          ADC10SA = (uint16_t)(adcbuff);

          /*����ADC*/
          ADC10CTL0 |= ADC10ON;

          /*����ת��*/
          ADC10CTL0 |= ENC;

}

void Close_Timer()
{
    ADC10AE0 = 0;
    ADC10CTL0 = 0;

    TA1CTL = 0;
    TA0CTL = 0;
    TA0CCTL0  = 0;
}
