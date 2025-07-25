#include <stdint.h>

#ifndef LCD_H_
#define LCD_H_

//// LCD与msp430g2553的接口配置
///*
//* ROM_IN -> P1.6 。。。
//* ROM_OUT -> P2.5 。。。
//* ROM_SCK -> P2.4 。。。
//* ROM_CS -> P2。3 。。。
//* SCLK -> P1.7  。。。
//* SDA -> P2.2 。。。
//* RS -> P2.1 。。。
//* RESET -> P2.7 。。。
//* CS -> P2.6 。。。

//#define ROM_IN_H P1OUT|=BIT1;
//#define ROM_IN_L P1OUT&=~BIT1;
//
//#define ROM_OUT_H P1OUT|=BIT2;
//#define ROM_OUT_L P1OUT&=~BIT2;
//
//#define ROM_SCK_H P1OUT|=BIT3;
//#define ROM_SCK_L P1OUT&=~BIT3;
//
//#define ROM_CS_H P1OUT|=BIT5;
//#define ROM_CS_L P1OUT&=~BIT5;
//
//#define SCLK_H P2OUT|=BIT2;
//#define SCLK_L P2OUT&=~BIT2;
//
//#define SDA_H P2OUT|=BIT3;
//#define SDA_L P2OUT&=~BIT3;
//
//#define RS_H P2OUT|=BIT4;
//#define RS_L P2OUT&=~BIT4;
//
//#define RESET_H P2OUT|=BIT1;
//#define RESET_L P2OUT&=~BIT1;
//
//#define CS_H P2OUT|=BIT5;
//#define CS_L P2OUT&=~BIT5;


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define DIN_0()                   P1OUT &=~BIT5
#define DIN_1()                   P1OUT |= BIT5
#define SCLK_0()                  P1OUT &=~BIT7
#define SCLK_1()                  P1OUT |= BIT7
#define CS_0()                    P2OUT &=~BIT2 //CS_PIN=0
#define CS_1()                    P2OUT |= BIT2 //CS_PIN=0
#define RS_0()                    P2OUT &=~BIT0//RS=0
#define RS_1()                    P2OUT |= BIT0//RS=1
#define RST_0()                   P2OUT &=~BIT1
#define RST_1()                   P2OUT |= BIT1

#define Rom_IN_0()                  P2OUT &=~BIT3
#define Rom_IN_1()                  P2OUT |= BIT3
#define Rom_OUT_0()                 P2OUT &=~BIT4 //CS_PIN=0
#define Rom_OUT_1()                 P2OUT |= BIT4 //CS_PIN=0

#define Rom_SCK_0()                 P2OUT &=~BIT5//RS=0
#define Rom_SCK_1()                 P2OUT |= BIT5//RS=1
#define Rom_CS_0()                  P1OUT &=~BIT6
#define Rom_CS_1()                  P1OUT |= BIT6

#define Rom_OUT_BIT P2IN&BIT4


void delay(int n_ms);
void delay_us(int n_us);

void transfer_command_lcd(int data1);
void transfer_data_lcd(int data1);
void initial_lcd();
void lcd_address(uint page,uint column);
void clear_screen();
void display_128x64(const uchar *dp);
void display_graphic_64x64(uchar page,uchar column,const uchar *dp);
void display_graphic_50x50(uchar page,uchar column,const uchar *dp);
void display_graphic_16x16(uchar page,uchar column,const uchar *dp);
void display_graphic_8x16(uchar page,uchar column,const uchar *dp);
void display_graphic_5x8(uchar page,uchar column,const uchar *dp);
void send_command_to_ROM( uchar datu );
static uchar get_data_from_ROM( );
//显示1x1点阵
void display_graphic_1x8(uchar page,uchar column,const uchar *dp);
//void display_graphic_8x16(uchar page,uchar column,const uchar *dp);
void get_and_write_16x16(ulong fontaddr,uchar page,uchar column);
void get_and_write_8x16(ulong fontaddr,uchar page,uchar column);
void get_and_write_5x8(ulong fontaddr,uchar page,uchar column);
void display_GB2312_string(uchar page,uchar column,char *text);
void display_string_5x8(uchar page,uchar column,char *text);
void display_float(unsigned int page, unsigned int column, float num);
void display_double(unsigned int page, unsigned int column, double num);
void display_graphic_60x50(uchar page,uchar column,const uchar *dp);
void display_wave(int16_t* data, int num);
void display_wave_auto(int16_t* data, int num,double freq);
void diplay_Spectrum_diagram(int32_t* data, int num);
void display_float_xxxxx_xx(unsigned int page, unsigned int column, double num);
void display_float_x_xxx(unsigned int page, unsigned int column, double num);
void display_1(int16_t* data1,int32_t* data2, int num,short type);
#endif /* LCD12864_H_ */
