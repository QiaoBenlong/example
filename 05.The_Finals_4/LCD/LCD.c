#include <msp430.h>
#include "LCD.h"
#include <stdint.h>
#include<math.h>

#define MAX_NUM 99999

// 初始化LCD
void delay(int n_ms)
{
int j,k;
for(j=0;j<n_ms;j++)
for(k=0;k<110;k++);
}
//短延时
void delay_us(int n_us)
{
int j,k;
for(j=0;j<n_us;j++)
for(k=0;k<1;k++);
}


//写指令到LCD 模块
void transfer_command_lcd(int data1)
{
char i;

CS_0();
RS_0();

for(i=0;i<8;i++)
{
    SCLK_0();

//delay_us(10); //加少量延时
if(data1&0x80) DIN_1();
else DIN_0();
SCLK_1();
//delay_us(10); //加少量延时
data1=data1<<=1;
}
CS_1();
}
//写数据到LCD 模块
void transfer_data_lcd(int data1)
{
char i;
CS_0();
RS_1();
for(i=0;i<8;i++)
{
    SCLK_0();
if(data1&0x80) DIN_1();
else DIN_0();
SCLK_1();
data1=data1<<=1;
}
CS_1();
}
//LCD 模块初始化
void initial_lcd()
{
    RST_0(); //低电平复位
delay(100);
RST_1(); //复位完毕
delay(100);
transfer_command_lcd(0xe2); //软复位
delay(5);
transfer_command_lcd(0x2c); //升压步聚1
delay(50);
transfer_command_lcd(0x2e); //升压步聚2
delay(50);
transfer_command_lcd(0x2f); //升压步聚3
delay(5);
transfer_command_lcd(0x23); //粗调对比度，可设置范围0x20～0x27
transfer_command_lcd(0x81); //微调对比度
transfer_command_lcd(0x28); //微调对比度的值，可设置范围0x00～0x3f
transfer_command_lcd(0xa2); //1/9 偏压比（bias）
transfer_command_lcd(0xc8); //行扫描顺序：从上到下
transfer_command_lcd(0xa0); //列扫描顺序：从左到右
transfer_command_lcd(0x40); //起始行：第一行开始
transfer_command_lcd(0xaf); //开显示
}
void lcd_address(uint page,uint column)
{
column=column-0x01;
transfer_command_lcd(0xb0+page-1); //设置页地址，每8 行为一页，全屏共64 行，被分成8 页
transfer_command_lcd(0x10+(column>>4&0x0f)); //设置列地址的高4 位
transfer_command_lcd(column&0x0f); //设置列地址的低4 位
}
//全屏清屏
void clear_screen()
{
unsigned char i,j;
for(i=0;i<9;i++)
{
transfer_command_lcd(0xb0+i);
transfer_command_lcd(0x10);
transfer_command_lcd(0x00);
for(j=0;j<132;j++)
{
transfer_data_lcd(0x00);
}
}
}

//显示1x8点阵
void display_graphic_1x8(uchar page,uchar column,const uchar *dp)
{
    lcd_address(page,column);
    transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
}

//void display_graphic_8x16(uchar page,uchar column,const uchar *dp)
//{
//    int i,j;
//    for(j=0;j<1;j++)
//    {
//    lcd_address(j+1,1);
//    for (i=0;i<8;i++)
//    {
//    transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
//    dp++;
//    }
//    }
//}

//显示128x64 点阵图像
void display_128x64(const uchar *dp)
{
uint i,j;
for(j=0;j<8;j++)
{
lcd_address(j+1,1);
for (i=0;i<128;i++)
{
transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
dp++;
}
}
}


//显示64x64 点阵图像
void display_graphic_64x64(uchar page,uchar column,const uchar *dp)
{
uint i,j;
for(j=0;j<8;j++)
{
lcd_address(page+j,column);
for (i=0;i<64;i++)
{
transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
dp++;
}
}
}

//显示50x50 点阵图像
void display_graphic_50x50(uchar page,uchar column,const uchar *dp)
{
uint i,j;
for(j=0;j<5;j++)
{
lcd_address(page+j,column);
for (i=0;i<50;i++)
{
transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
dp++;
}
}
}

//显示60x50 点阵图像
void display_graphic_60x50(uchar page,uchar column,const uchar *dp)
{
uint i,j;
for(j=0;j<4;j++)
{
lcd_address(page+j,column);
for (i=0;i<60;i++)
{
transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
dp++;
}
}
}


//显示16x16 点阵图像、汉字、生僻字或16x16 点阵的其他图标
void display_graphic_16x16(uchar page,uchar column,const uchar *dp)
{
uint i,j;
for(j=0;j<2;j++)
{
lcd_address(page+j,column);
for (i=0;i<16;i++)
{
transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
dp++;
}
}
}
//显示8x16 点阵图像、ASCII, 或8x16 点阵的自造字符、其他图标
void display_graphic_8x16(uchar page,uchar column,const uchar *dp)
{
uint i,j;
for(j=0;j<2;j++)
{
lcd_address(page+j,column);
for (i=0;i<8;i++)
{
transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
dp++;
}
}
}
//显示5X8 点阵图像、ASCII, 或5x8 点阵的自造字符、其他图标
void display_graphic_5x8(uchar page,uchar column,const uchar *dp)
{
uint i;
lcd_address(page,column);
for (i=0;i<6;i++)
{
transfer_data_lcd(*dp);
dp++;
}
}
//送指令到晶联讯字库IC
void send_command_to_ROM( uchar datu )
{
uchar i;
for(i=0;i<8;i++ )
{
    Rom_SCK_0();
delay_us(10);
if(datu&0x80)  Rom_IN_1();
        else Rom_IN_0();
datu = datu<<1;
Rom_SCK_1();
delay_us(10);
}
}
//从晶联讯字库IC 中取汉字或字符数据（1 个字节）
static uchar get_data_from_ROM( )
{
uchar i;
uchar ret_data=0;
for(i=0;i<8;i++)
{

Rom_OUT_1();
Rom_SCK_0();
//delay_us(1);
ret_data=ret_data<<1;
if( Rom_OUT_BIT )
ret_data=ret_data+1;
else
ret_data=ret_data+0;
Rom_SCK_1();
//delay_us(1);
}
return(ret_data);
}
//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_16x16(ulong fontaddr,uchar page,uchar column)
{
uchar i,j,disp_data;
Rom_CS_0();
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //地址的高8 位,共24 位
send_command_to_ROM((fontaddr&0xff00)>>8); //地址的中8 位,共24 位
send_command_to_ROM(fontaddr&0xff); //地址的低8 位,共24 位
for(j=0;j<2;j++)
{
lcd_address(page+j,column);
for(i=0; i<16; i++ )
{
disp_data=get_data_from_ROM();
transfer_data_lcd(disp_data); //写数据到LCD,每写完1 字节的数据后列地址自动加1
}
}
Rom_CS_1();
}
//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_8x16(ulong fontaddr,uchar page,uchar column)
{
uchar i,j,disp_data;
Rom_CS_0();
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //地址的高8 位,共24 位
send_command_to_ROM((fontaddr&0xff00)>>8); //地址的中8 位,共24 位
send_command_to_ROM(fontaddr&0xff); //地址的低8 位,共24 位
for(j=0;j<2;j++)
{
lcd_address(page+j,column);
for(i=0; i<8; i++ )
{
disp_data=get_data_from_ROM();
transfer_data_lcd(disp_data); //写数据到LCD,每写完1 字节的数据后列地址自动加1
}
}
Rom_CS_1();
}

//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_5x8(ulong fontaddr,uchar page,uchar column)
{
uchar i,disp_data;
Rom_CS_0();
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //地址的高8 位,共24 位
send_command_to_ROM((fontaddr&0xff00)>>8); //地址的中8 位,共24 位
send_command_to_ROM(fontaddr&0xff); //地址的低8 位,共24 位
lcd_address(page,column);
for(i=0; i<5; i++ )
{
disp_data=get_data_from_ROM();
transfer_data_lcd(disp_data); //写数据到LCD,每写完1 字节的数据后列地址自动加1
}
Rom_CS_1();
}

//****************************************************************
ulong fontaddr=0;
void display_GB2312_string(uchar page,uchar column,char *text)
{
uchar i= 0;
while((text[i]>0x00))
{
if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
{
//国标简体（GB2312）汉字在晶联讯字库IC 中的地址由以下公式来计算：
//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
//由于担心8 位单片机有乘法溢出问题，所以分三部取地址
fontaddr = (text[i]- 0xb0)*94;
fontaddr += (text[i+1]-0xa1)+846;
fontaddr = (ulong)(fontaddr*32);
get_and_write_16x16(fontaddr,page,column); //从指定地址读出数据写到液晶屏指定（page,column)座标中
i+=2;
column+=16;
}
else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
{
//国标简体（GB2312）15x16 点的字符在晶联讯字库IC 中的地址由以下公式来计算：
//Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0
//由于担心8 位单片机有乘法溢出问题，所以分三部取地址
fontaddr = (text[i]- 0xa1)*94;
fontaddr += (text[i+1]-0xa1);
fontaddr = (ulong)(fontaddr*32);
get_and_write_16x16(fontaddr,page,column); //从指定地址读出数据写到液晶屏指定（page,column)座标中
i+=2;
column+=16;
}
else if((text[i]>=0x20) &&(text[i]<=0x7e))
{
fontaddr = (text[i]- 0x20);
fontaddr = (unsigned long)(fontaddr*16);
fontaddr = (unsigned long)(fontaddr+0x3cf80);
get_and_write_8x16(fontaddr,page,column); //从指定地址读出数据写到液晶屏指定（page,column)座标中
i+=1;
column+=8;
}
else
i++;
}
}
void display_string_5x8(uchar page,uchar column,char *text)
{
unsigned char i= 0;
while((text[i]>0x00))
{
if((text[i]>=0x20) &&(text[i]<=0x7e))
{
fontaddr = (text[i]- 0x20);
fontaddr = (unsigned long)(fontaddr*8);
fontaddr = (unsigned long)(fontaddr+0x3bfc0);
get_and_write_5x8(fontaddr,page,column); //从指定地址读出数据写到液晶屏指定（page,column)座标中
i+=1;
column+=6;
}
else
i++;
}
}

// 显示小数，格式为xx.xx
void display_float(unsigned int page, unsigned int column, float num)
{
    int temp,i;
    for(i=0;i<5;i++)
    {
        if(i == 2)
        {
            display_GB2312_string(page,i*8 + 1 + column,".");
        }
        else
        {
            temp = num / 10;
            num = (num - temp*10) * 10;
            if(i != 0 || temp != 0) // 首位为0则不显示
            {
                switch (temp)
                {
                case 0: display_GB2312_string(page,i*8 + 1 + column,"0");break;
                case 1: display_GB2312_string(page,i*8 + 1 + column,"1");break;
                case 2: display_GB2312_string(page,i*8 + 1 + column,"2");break;
                case 3: display_GB2312_string(page,i*8 + 1 + column,"3");break;
                case 4: display_GB2312_string(page,i*8 + 1 + column,"4");break;
                case 5: display_GB2312_string(page,i*8 + 1 + column,"5");break;
                case 6: display_GB2312_string(page,i*8 + 1 + column,"6");break;
                case 7: display_GB2312_string(page,i*8 + 1 + column,"7");break;
                case 8: display_GB2312_string(page,i*8 + 1 + column,"8");break;
                case 9: display_GB2312_string(page,i*8 + 1 + column,"9");break;
                }
            }
        }

    }
}

void display_double(unsigned int page, unsigned int column, double num)
{
    int temp,i;
    for(i=0;i<5;i++)
    {
        if(i == 2)
        {
            display_GB2312_string(page,i*8 + 1 + column,".");
        }
        else
        {
            temp = num / 10;
            num = (num - temp*10) * 10;
            if(i != 0 || temp != 0) // 首位为0则不显示
            {
                switch (temp)
                {
                case 0: display_GB2312_string(page,i*8 + 1 + column,"0");break;
                case 1: display_GB2312_string(page,i*8 + 1 + column,"1");break;
                case 2: display_GB2312_string(page,i*8 + 1 + column,"2");break;
                case 3: display_GB2312_string(page,i*8 + 1 + column,"3");break;
                case 4: display_GB2312_string(page,i*8 + 1 + column,"4");break;
                case 5: display_GB2312_string(page,i*8 + 1 + column,"5");break;
                case 6: display_GB2312_string(page,i*8 + 1 + column,"6");break;
                case 7: display_GB2312_string(page,i*8 + 1 + column,"7");break;
                case 8: display_GB2312_string(page,i*8 + 1 + column,"8");break;
                case 9: display_GB2312_string(page,i*8 + 1 + column,"9");break;
                }
            }
        }

    }
}





// 显示小数，格式为xxxxxx.xx
//void display_float_xxxxxx_xx(unsigned int page, unsigned int column, double num)
//{
//    int64_t temp,i;
//    int64_t n=(int64_t)(num)%9999999;
//    char text[10];
//
//    for(i=0;i<9;i++)
//    {
//        if(i == 6)
//        {
//            text[6]='.';
//        }
//        else if(i==0)
//        {
//            for(i=0;i<=5;i++) // 首位为0则不显示
//            {
//                temp=n%10;
//                n/=10;
//                text[5-i]=(char)('0'+temp);
//            }
//            i--;
//        }
//        else if(i==7)
//        {
//            for(i=7;i<9;i++)
//            {
//                num=num*10;
//                temp=(int64_t)num%10;
//                text[i]=(char)('0'+temp);
//            }
//        }
//
//    }
//
//
//    display_GB2312_string(page,column,text);
//}


void display_float_xxxxx_xx(unsigned int page, unsigned int column, double num)
{
    int64_t temp,i;
    int64_t n=(int64_t)(num)%MAX_NUM;
    char text[9];
    text[8]=0;

    for(i=0;i<8;i++)
    {
        if(i == 5)
        {
            text[5]='.';
        }
        else if(i==0)
        {
            for(i=0;i<=4;i++) // 首位为0则不显示
            {
                temp=n%10;
                n/=10;
                text[4-i]=(char)('0'+temp);
            }
            i--;
        }
        else if(i==6)
        {
            for(i=6;i<8;i++)
            {
                num=num*10;
                temp=(int64_t)num%10;
                text[i]=(char)('0'+temp);
            }
        }

    }


    display_GB2312_string(page,column,text);
}

void display_float_x_xxx(unsigned int page, unsigned int column, double num)
{
    int64_t temp,i;
    int64_t n=(int64_t)(num)%10;
    char text[5];

    for(i=0;i<4;i++)
    {
        if(i == 1)
        {
            text[1]='.';
        }
        else if(i==0)
        {
            temp=n%10;
            text[0]=(char)('0'+temp);
        }
        else if(i==2)
        {
            for(i=2;i<4;i++)
            {
                num=num*10;
                temp=(int64_t)num%10;
                text[i]=(char)('0'+temp);
            }
        }

    }


    display_GB2312_string(page,column,text);
}



int16_t judge_y(int16_t data)
{
//    int16_t a=(56-get_unit(56,data));
    int16_t a=64-data*6/100;
    return a;
}//判断波形对应坐标

int16_t judge_y_Spectrum_diagram(int32_t data)
{


//    a=64-sqrtf(data)*11/100;

    int16_t a=64-sqrtf(data)*6/100;
    return a;
}//判断频谱对应坐标

uchar judge_data(int page,int16_t y)
{
    uchar arr=0;

    if(8*page-y>=0)
        y=8*page-y;
    else if(y>8)
        return BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT6+BIT7;

//    else
//        y=8*page-y;

    switch (y)
    {
//        case 0: arr |= BIT1+BIT2+BIT3+BIT4+BIT5+BIT6+BIT0;break;
//        case 1: arr |= BIT1+BIT2+BIT3+BIT4+BIT5+BIT0+BIT7;break;
//        case 2: arr |= BIT0+BIT1+BIT3+BIT4+BIT2+BIT6+BIT7;break;
//        case 3: arr |= BIT1+BIT2+BIT0+BIT3+BIT5+BIT6+BIT7;break;
//        case 4: arr |= BIT1+BIT2+BIT4+BIT0+BIT5+BIT6+BIT7;break;
//        case 5: arr |= BIT1+BIT5+BIT3+BIT4+BIT0+BIT6+BIT7;break;
//        case 6: arr |= BIT6+BIT2+BIT3+BIT4+BIT5+BIT0+BIT7;break;
//        case 7: arr |= BIT7+BIT2+BIT3+BIT4+BIT5+BIT6+BIT1;break;
//        default:arr |= BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT6+BIT7;break;

        case 0: arr |= BIT1+BIT2+BIT3+BIT4+BIT5+BIT0;break;
        case 1: arr |= BIT1+BIT2+BIT3+BIT4+BIT0+BIT7;break;
        case 2: arr |= BIT0+BIT1+BIT3+BIT2+BIT6+BIT7;break;
        case 3: arr |= BIT1+BIT2+BIT0+BIT5+BIT6+BIT7;break;
        case 4: arr |= BIT1+BIT4+BIT0+BIT5+BIT6+BIT7;break;
        case 5: arr |= BIT5+BIT3+BIT4+BIT0+BIT6+BIT7;break;
        case 6: arr |= BIT6+BIT2+BIT3+BIT4+BIT5+BIT7;break;
        case 7: arr |= BIT7+BIT2+BIT3+BIT4+BIT5+BIT6;break;
        default:arr |= BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT6+BIT7;break;
    }
    return arr;





}//获取波形数据



uchar judge_data_Spectrum_diagram(int page,int16_t y)
{
    uchar arr=0;

    if(8*page-y>=0)
        y=8*page-y;
    else if(y>8)
        return BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT6+BIT7;

//    else
//        y=8*page-y;

    switch (y)
        {
            case 0: arr |= BIT1+BIT2+BIT3+BIT4+BIT5+BIT0;break;
            case 1: arr |= BIT1+BIT2+BIT3+BIT4+BIT0;break;
            case 2: arr |= BIT0+BIT1+BIT3+BIT2;break;
            case 3: arr |= BIT1+BIT2+BIT0;break;
            case 4: arr |= BIT1+BIT0;break;
            case 5: arr |= BIT0;break;
            case 6: arr = 0;break;
            case 7: arr |= BIT0;break;
            default:
            {
//               if(a==page)
//                   arr = 0;
//               else
                   //arr |= BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT6+BIT7;break;
                arr =0;break;
            }
            break;
        }

    return arr;





}//获取频谱数据


//int16_t* data, int num
void display_wave(int16_t* data, int num)
{
    int i,j;
    int16_t y;
    uchar arr;
    for(j=9;j<=128;j++)
    {
        y=judge_y(data[j-1]);

//        {
//            arr=judge_data(1,y);
//            arr &= ~BIT0;
//            arr &= ~BIT1;
//            arr &= ~BIT2;
//            arr &= ~BIT3;
//            display_graphic_1x8(1,j,&arr);
//        }

        for(i=0;i<64;i+=8)
        {
            arr=judge_data(i/8+1,y);
            display_graphic_1x8(i/8+1,j,&arr);
        }
    }
}

void display_1(int16_t* data1,int32_t* data2,int num,short type)
{
    int i,j;
    int16_t y;
    uchar arr=0xff;
    int ret=0;

    if(type==1)
    {
        for(j=9;j<=128;j++)
            {
                y=judge_y(data1[j-1]);

        //        {
        //            arr=judge_data(1,y);
        //            arr &= ~BIT0;
        //            arr &= ~BIT1;
        //            arr &= ~BIT2;
        //            arr &= ~BIT3;
        //            display_graphic_1x8(1,j,&arr);
        //        }

                for(i=0;i<64;i+=8)
                {
                    arr=judge_data(i/8+1,y);
                    display_graphic_1x8(i/8+1,j,&arr);
                }
            }
    }

    else if(type==2)
    {
        for(i=0;i<64;i+=8)
            {
                display_graphic_1x8(i/8+1,7,&arr);
            }

            for(j=8;j<=128&&ret<num;j++)
            {
                if(j%2==0)
                {
                    y=judge_y_Spectrum_diagram(data2[ret++]);
                    for(i=0;i<64;i+=8)
                    {
                        arr=judge_data_Spectrum_diagram(i/8+1,y);
                        display_graphic_1x8(i/8+1,j,&arr);
                    }
                }
                else
                {
                    arr=0xff;
                    for(i=0;i<64;i+=8)
                    {
                        display_graphic_1x8(i/8+1,j,&arr);
                    }

                }
            }
    }
}

//void diplay_Spectrum_diagram(int32_t* data, int num)
//{
//    int i,j;
//    int16_t y;
//    uchar arr;
//    int ret=0;
//
//    arr=0xff;
//    for(i=0;i<64;i+=8)
//    {
//        display_graphic_1x8(i/8+1,7,&arr);
//    }
//
//    for(j=8;j<=128&&ret<num;j++)
//    {
//        if(j%2==0)
//        {
//            y=judge_y_Spectrum_diagram(data[ret++]);
//            for(i=0;i<64;i+=8)
//            {
//
//                arr=judge_data_Spectrum_diagram(i/8+1,y);
//                display_graphic_1x8(i/8+1,j,&arr);
//            }
//        }
//        else
//        {
//            arr=0xff;
//            for(i=0;i<64;i+=8)
//            {
//                display_graphic_1x8(i/8+1,j,&arr);
//            }
//
//        }
//    }
//}

//void diplay_Spectrum_diagram(int32_t* data, int num)
//{
//    int i,j;
//    int16_t y;
//    uchar arr;
//    int ret=0;
//
//    for(j=8;j<=128&&ret<num;j++)
//    {
//
//        y=judge_y_Spectrum_diagram(data[ret++]);
//        for(i=0;i<64;i+=8)
//        {
//
//            arr=judge_data_Spectrum_diagram(i/8+1,y);
//            display_graphic_1x8(i/8+1,j,&arr);
//        }
//
//    }
//}
