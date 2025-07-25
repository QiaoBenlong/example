#include <msp430.h>
#include "LCD.h"
#include <stdint.h>
#include<math.h>

#define MAX_NUM 99999

// ��ʼ��LCD
void delay(int n_ms)
{
int j,k;
for(j=0;j<n_ms;j++)
for(k=0;k<110;k++);
}
//����ʱ
void delay_us(int n_us)
{
int j,k;
for(j=0;j<n_us;j++)
for(k=0;k<1;k++);
}


//дָ�LCD ģ��
void transfer_command_lcd(int data1)
{
char i;

CS_0();
RS_0();

for(i=0;i<8;i++)
{
    SCLK_0();

//delay_us(10); //��������ʱ
if(data1&0x80) DIN_1();
else DIN_0();
SCLK_1();
//delay_us(10); //��������ʱ
data1=data1<<=1;
}
CS_1();
}
//д���ݵ�LCD ģ��
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
//LCD ģ���ʼ��
void initial_lcd()
{
    RST_0(); //�͵�ƽ��λ
delay(100);
RST_1(); //��λ���
delay(100);
transfer_command_lcd(0xe2); //��λ
delay(5);
transfer_command_lcd(0x2c); //��ѹ����1
delay(50);
transfer_command_lcd(0x2e); //��ѹ����2
delay(50);
transfer_command_lcd(0x2f); //��ѹ����3
delay(5);
transfer_command_lcd(0x23); //�ֵ��Աȶȣ������÷�Χ0x20��0x27
transfer_command_lcd(0x81); //΢���Աȶ�
transfer_command_lcd(0x28); //΢���Աȶȵ�ֵ�������÷�Χ0x00��0x3f
transfer_command_lcd(0xa2); //1/9 ƫѹ�ȣ�bias��
transfer_command_lcd(0xc8); //��ɨ��˳�򣺴��ϵ���
transfer_command_lcd(0xa0); //��ɨ��˳�򣺴�����
transfer_command_lcd(0x40); //��ʼ�У���һ�п�ʼ
transfer_command_lcd(0xaf); //����ʾ
}
void lcd_address(uint page,uint column)
{
column=column-0x01;
transfer_command_lcd(0xb0+page-1); //����ҳ��ַ��ÿ8 ��Ϊһҳ��ȫ����64 �У����ֳ�8 ҳ
transfer_command_lcd(0x10+(column>>4&0x0f)); //�����е�ַ�ĸ�4 λ
transfer_command_lcd(column&0x0f); //�����е�ַ�ĵ�4 λ
}
//ȫ������
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

//��ʾ1x8����
void display_graphic_1x8(uchar page,uchar column,const uchar *dp)
{
    lcd_address(page,column);
    transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
}

//void display_graphic_8x16(uchar page,uchar column,const uchar *dp)
//{
//    int i,j;
//    for(j=0;j<1;j++)
//    {
//    lcd_address(j+1,1);
//    for (i=0;i<8;i++)
//    {
//    transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
//    dp++;
//    }
//    }
//}

//��ʾ128x64 ����ͼ��
void display_128x64(const uchar *dp)
{
uint i,j;
for(j=0;j<8;j++)
{
lcd_address(j+1,1);
for (i=0;i<128;i++)
{
transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
dp++;
}
}
}


//��ʾ64x64 ����ͼ��
void display_graphic_64x64(uchar page,uchar column,const uchar *dp)
{
uint i,j;
for(j=0;j<8;j++)
{
lcd_address(page+j,column);
for (i=0;i<64;i++)
{
transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
dp++;
}
}
}

//��ʾ50x50 ����ͼ��
void display_graphic_50x50(uchar page,uchar column,const uchar *dp)
{
uint i,j;
for(j=0;j<5;j++)
{
lcd_address(page+j,column);
for (i=0;i<50;i++)
{
transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
dp++;
}
}
}

//��ʾ60x50 ����ͼ��
void display_graphic_60x50(uchar page,uchar column,const uchar *dp)
{
uint i,j;
for(j=0;j<4;j++)
{
lcd_address(page+j,column);
for (i=0;i<60;i++)
{
transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
dp++;
}
}
}


//��ʾ16x16 ����ͼ�񡢺��֡���Ƨ�ֻ�16x16 ���������ͼ��
void display_graphic_16x16(uchar page,uchar column,const uchar *dp)
{
uint i,j;
for(j=0;j<2;j++)
{
lcd_address(page+j,column);
for (i=0;i<16;i++)
{
transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
dp++;
}
}
}
//��ʾ8x16 ����ͼ��ASCII, ��8x16 ����������ַ�������ͼ��
void display_graphic_8x16(uchar page,uchar column,const uchar *dp)
{
uint i,j;
for(j=0;j<2;j++)
{
lcd_address(page+j,column);
for (i=0;i<8;i++)
{
transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
dp++;
}
}
}
//��ʾ5X8 ����ͼ��ASCII, ��5x8 ����������ַ�������ͼ��
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
//��ָ�����Ѷ�ֿ�IC
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
//�Ӿ���Ѷ�ֿ�IC ��ȡ���ֻ��ַ����ݣ�1 ���ֽڣ�
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
//��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_16x16(ulong fontaddr,uchar page,uchar column)
{
uchar i,j,disp_data;
Rom_CS_0();
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //��ַ�ĸ�8 λ,��24 λ
send_command_to_ROM((fontaddr&0xff00)>>8); //��ַ����8 λ,��24 λ
send_command_to_ROM(fontaddr&0xff); //��ַ�ĵ�8 λ,��24 λ
for(j=0;j<2;j++)
{
lcd_address(page+j,column);
for(i=0; i<16; i++ )
{
disp_data=get_data_from_ROM();
transfer_data_lcd(disp_data); //д���ݵ�LCD,ÿд��1 �ֽڵ����ݺ��е�ַ�Զ���1
}
}
Rom_CS_1();
}
//��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_8x16(ulong fontaddr,uchar page,uchar column)
{
uchar i,j,disp_data;
Rom_CS_0();
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //��ַ�ĸ�8 λ,��24 λ
send_command_to_ROM((fontaddr&0xff00)>>8); //��ַ����8 λ,��24 λ
send_command_to_ROM(fontaddr&0xff); //��ַ�ĵ�8 λ,��24 λ
for(j=0;j<2;j++)
{
lcd_address(page+j,column);
for(i=0; i<8; i++ )
{
disp_data=get_data_from_ROM();
transfer_data_lcd(disp_data); //д���ݵ�LCD,ÿд��1 �ֽڵ����ݺ��е�ַ�Զ���1
}
}
Rom_CS_1();
}

//��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_5x8(ulong fontaddr,uchar page,uchar column)
{
uchar i,disp_data;
Rom_CS_0();
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //��ַ�ĸ�8 λ,��24 λ
send_command_to_ROM((fontaddr&0xff00)>>8); //��ַ����8 λ,��24 λ
send_command_to_ROM(fontaddr&0xff); //��ַ�ĵ�8 λ,��24 λ
lcd_address(page,column);
for(i=0; i<5; i++ )
{
disp_data=get_data_from_ROM();
transfer_data_lcd(disp_data); //д���ݵ�LCD,ÿд��1 �ֽڵ����ݺ��е�ַ�Զ���1
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
//������壨GB2312�������ھ���Ѷ�ֿ�IC �еĵ�ַ�����¹�ʽ�����㣺
//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
//���ڵ���8 λ��Ƭ���г˷�������⣬���Է�����ȡ��ַ
fontaddr = (text[i]- 0xb0)*94;
fontaddr += (text[i+1]-0xa1)+846;
fontaddr = (ulong)(fontaddr*32);
get_and_write_16x16(fontaddr,page,column); //��ָ����ַ��������д��Һ����ָ����page,column)������
i+=2;
column+=16;
}
else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
{
//������壨GB2312��15x16 ����ַ��ھ���Ѷ�ֿ�IC �еĵ�ַ�����¹�ʽ�����㣺
//Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0
//���ڵ���8 λ��Ƭ���г˷�������⣬���Է�����ȡ��ַ
fontaddr = (text[i]- 0xa1)*94;
fontaddr += (text[i+1]-0xa1);
fontaddr = (ulong)(fontaddr*32);
get_and_write_16x16(fontaddr,page,column); //��ָ����ַ��������д��Һ����ָ����page,column)������
i+=2;
column+=16;
}
else if((text[i]>=0x20) &&(text[i]<=0x7e))
{
fontaddr = (text[i]- 0x20);
fontaddr = (unsigned long)(fontaddr*16);
fontaddr = (unsigned long)(fontaddr+0x3cf80);
get_and_write_8x16(fontaddr,page,column); //��ָ����ַ��������д��Һ����ָ����page,column)������
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
get_and_write_5x8(fontaddr,page,column); //��ָ����ַ��������д��Һ����ָ����page,column)������
i+=1;
column+=6;
}
else
i++;
}
}

// ��ʾС������ʽΪxx.xx
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
            if(i != 0 || temp != 0) // ��λΪ0����ʾ
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
            if(i != 0 || temp != 0) // ��λΪ0����ʾ
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





// ��ʾС������ʽΪxxxxxx.xx
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
//            for(i=0;i<=5;i++) // ��λΪ0����ʾ
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
            for(i=0;i<=4;i++) // ��λΪ0����ʾ
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
}//�жϲ��ζ�Ӧ����

int16_t judge_y_Spectrum_diagram(int32_t data)
{


//    a=64-sqrtf(data)*11/100;

    int16_t a=64-sqrtf(data)*6/100;
    return a;
}//�ж�Ƶ�׶�Ӧ����

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





}//��ȡ��������



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





}//��ȡƵ������


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
