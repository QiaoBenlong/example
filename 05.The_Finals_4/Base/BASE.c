#include <msp430g2553.h>
#include<stdint.h>
#include "BASE.h"
extern int16_t adcbuff[128];

/* *************************************************************
  *@ brief  nms???????
  *@ param  k???????????????
  *@ retval ??
  *@comment ????????????????????????????????????j???С
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
//    adc采样引脚初始化
        //P1REN &= ~BIT0;

    P2DIR &= ~BIT4;//Rom_out引脚初始化
    P2DIR |= BIT0+BIT1+BIT2+BIT3+BIT5;
    P1DIR |=BIT5+BIT6+BIT7;
    //LCD引脚初始化



}

/*
 * @brief 初始化系统时钟
 * @param 无
 * @retval 无
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

void InitTimer1(double freq)//自适应采样
{
    TA1CTL |= TASSEL_2;//
    TA1CTL |= MC_1;//
    TA1CCR0 = (int32_t)(16*1000000/(freq*99/100))-1;//
    TA1CTL |= TAIE;
}

void InitTimer1_wave()//针对4-5khz初始化
{
    TA1CTL |= TASSEL_2;//
    TA1CTL |= MC_1;//

    //79

//    TA1CCR0 = 132;
    TA1CCR0 = 79;
    TA1CTL |= TAIE;
}


/*
 * @brief 初始化系统时钟
 * @param 无
 * @retval 无
 * by zheng.hao@bupt.edu.cn
 */
//void InitTimer1(void)
//{
//       /*设置时钟源为SMCLK*/
//       TA1CTL |= TASSEL_2;
//       /*设置工作模式为Up Mode*/
//       TA1CTL |= MC_1;
//       /*设置定时间隔*/
//       TA1CCR0 = 49999;//50ms
//       /*开启TAIFG中断*/
//       TA1CTL |= TAIE;
//       /*TA1,CCR2用于捕捉功能*/
//       TA1CCTL2 |= CAP;
//       /*上升沿捕捉*/
//       TA1CCTL2 |= CM_1;
//
//       /*P2.5作为捕捉输入(CCI2B)*/
//       TA1CCTL2 |= CCIS0;
////       P2SEL |= BIT5;
//
//       /*允许捕捉比较中断*/
//       TA1CCTL2 |= CCIE;
//}

//void InitTimer0(void)
//{
//       /*设置时钟源为SMCLK*/
//       TA0CTL |= TASSEL_2;
//       /*设置工作模式为Up Mode*/
//       TA0CTL |= MC_1;
//       /*设置定时间隔*/
//       TA0CCR0 = 49999;//50ms
//       /*开启TAIFG中断*/
//       TA0CTL |= TAIE;
//
//       /*TA1,CCR2用于捕捉功能*/
//       TA0CCTL1 |= CAP;
//       /*上升沿捕捉*/
//       TA0CCTL1 |= CM0;
//       /*P2.6作为捕捉输入(CCI1B)*/
//       TA0CCTL1 |= CCIS0;
//       P2SEL |= BIT6;
//       /*允许捕捉比较中断*/
//       TA0CCTL1 |= CCIE;
//}






void InitSystemClock(void)
{
    /*配置DCO为16MHz*/
    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    /*配置SMCLK的时钟源为DCO*/
    BCSCTL2 &= ~SELS;
    /*SMCLK的分频系数置为1*/
    BCSCTL2 &= ~(DIVS0 | DIVS1);
}

/*
 * @brief 开始ADC转换
 * @param 无
 * @retval 无
 * by zheng.hao@bupt.edu.cn
 */
void StartADCConvert(void)
{
      ADC10CTL0 |= ADC10SC|ENC; // 开始转换
      while(ADC10CTL1&ADC10BUSY); // 等待转换完成
}


 /*
  * @brief 初始化定时器
  * @param 无
  * @retval 无
  * by shenmengfei@bupt.edu.cn
  */
 void Interrupt(void)
 {
     /*初始化按键所在IO口P1.3为输入*/
      P1DIR &= ~BIT3;
      /*使能P1.3口的上拉电阻*/
      P1REN |= BIT3;
      P1OUT |= BIT3;
      /*打开P1.3口中断*/
      P1IE |= BIT3;
      /*设定为下降沿触发*/
      P1IES |= BIT3;
      /*清除中断标志位*/
      P1IFG &= ~BIT3;

//      /*初始化按键所在IO口P2.5为输入*/
//       P2DIR &= ~BIT5;
//       /*使能P2.5口的上拉电阻*/
//       P2REN |= BIT5;
//       P2OUT |= BIT5;
//       /*打开P2.5口中断*/
//       P2IE |= BIT5;
//       /*设定为下降沿触发*/
//       P2IES |= BIT5;
//       /*清除中断标志位*/
//       P2IFG &= ~BIT5;


      /*打开全局中断*/
      __bis_SR_register(GIE);
 }


/*
 * @brief 初始化ADC,并设置ADCADC转换结果存入adcbuff数组里
 * @param 无
 * @retval 无
 * by zheng.hao@bupt.edu.cn
 */
void InitADC(short choose)
{
          /*设置ADC时钟MCLK*/
//    ADC10CTL1 |= ADC10SSEL_2;
          ADC10CTL1 |= ADC10SSEL_0;
          /*设置ADC基准源*/
          switch(choose)
          {
              case 1:ADC10CTL0 |= SREF_0;break;/*ADC基准选择Vcc*/
              case 2:ADC10CTL0 |= SREF_0;break;/*ADC基准选择Vcc*/
              case 3:ADC10CTL0 |= SREF_1;ADC10CTL0 |= REF2_5V;/*ADC基准选择2.5V*/break;
              default:ADC10CTL0 |= SREF_1;ADC10CTL0 |= REF2_5V;break;
          }
          /*设置ADC采样保持时间16CLK*/
          ADC10CTL0 |= ADC10SHT_2;
          /*设置ADC采样速率200k*/
          ADC10CTL0 |= ADC10SR;
          /*开启基准*/
          ADC10CTL0 |= REFON;
          /*选择ADC输入通道A4*/
          ADC10CTL1 |= INCH_4;
          /*允许A4模拟输入*/
          ADC10AE0 |= 1<<4;
          /*DTC传输模式*/
          ADC10DTC0 |= ADC10CT;
          /*传输次数*/
          ADC10DTC1 = 128;
          /*起始地址*/
          ADC10SA = (uint16_t)(adcbuff);

          /*开启ADC*/
          ADC10CTL0 |= ADC10ON;

          /*允许转换*/
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
