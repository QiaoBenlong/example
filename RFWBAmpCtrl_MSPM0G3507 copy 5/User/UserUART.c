#include "UserUART.h"
#include "string.h"
#include "stdlib.h"
#include "UserTask.h"

volatile uint8_t RxData[RX_MAX_SIZE] = {'\0'};
volatile uint8_t RxPos = 0;


char temp_str[RX_MAX_SIZE];//调试用的
volatile uint8_t received_data = '0';                //便于调试观察
volatile uint8_t num_str[RX_MAX_SIZE + 1];  // 数字字符数组
volatile uint16_t num_index = 0;            // 数组索引
volatile uint8_t  uart_flag = 0;            // 用于指示接收完成
volatile float data_of_test = 0;            // 用于传输数据的数字
volatile float freq_start = 0;
volatile float freq_end = 0;
volatile float freq_step = 0;
volatile int print_flag = 0;
volatile int order_flag = 0;
volatile int start_flag = 0;

corrent_operating_t corrent_operating = initial; //当前工作状态

void UART2_init(){
    NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
}


int UART0_sendStr(const char* str) {
    int count = 0;
    while (*str) {
        DL_UART_transmitDataBlocking(UART_0_INST, *str);
        str++;
        count++;
    }
    return count;
}

int UART2_sendStr(const char* str) {
    int count = 0;
    while (*str) {
        DL_UART_transmitDataBlocking(UART_2_INST, *str);
        str++;
        count++;
    }
    return count;
}

void UART0_printf(char* fmt, ...) {
    static char buf[256];
    int len;
    va_list args;
    va_start(args, fmt);
    len = vsprintf(buf, fmt, args);
    va_end(args);
    UART0_sendStr(buf);
}

void UART2_printf(char* fmt, ...) {
    static char buf[256];
    int len;
    va_list args;
    va_start(args, fmt);
    len = vsprintf(buf, fmt, args);
    va_end(args);
    UART2_sendStr(buf);
}

// 串口接收中断
void UART0_IRQHandler(void) {
    if (DL_UART_getPendingInterrupt(UART_0_INST) == DL_UART_IIDX_RX) {
        if (RxPos < RX_MAX_SIZE - 1) {
            RxData[RxPos] = DL_UART_receiveData(UART_0_INST);
            RxData[RxPos + 1] = '\0';
            RxPos++;
        }
    }
}

// 接受串口
void UART2_IRQHandler(void) 
{
    if (DL_UART_Main_getPendingInterrupt(UART_2_INST) == DL_UART_MAIN_IIDX_RX)
     {
        received_data = DL_UART_Main_receiveData(UART_2_INST);
        
        if (received_data >= 0x00 && received_data <= 0x09) 
        {
            // 接收到数字0-9
            if (num_index < RX_MAX_SIZE) 
            {
                num_str[num_index++] = '0' + received_data ;
            }
        } 
        else if (received_data == 0x10)
         {
            // 接收到小数点
            if (num_index < RX_MAX_SIZE) 
            {
                num_str[num_index++] = '.';
            }
        } 
        else if (received_data == 0xFF) 
        {
            // 接收到终止符
            num_str[num_index] = '\0'; // 结束字符串
            uart_flag = 1;             // 设置接收完成标志
            data_of_test = atof((const char*)num_str); // 将字符串转换为浮点数// 将字符数组转换为浮点数
            num_index = 0;             // 重置索引
            memset((void*)num_str, 0, sizeof(num_str)); // 清空数组
            uart_flag = 0;             // 重置接收完成标志

        }
        else if (received_data == 0x13)
        {
            //设置起始频率
            freq_start = data_of_test;

        }
        else if (received_data == 0x14)
        {
            //设置终止频率
            freq_end = data_of_test;

        }
        else if (received_data == 0x15)
        {
            //设置步进值
            freq_step = data_of_test;
        }
        else if (received_data == 0x18)
        {
            print_flag = 1;            
        }
        else if (received_data == 0x16)
        {
            flag=1;
        }
        else if (received_data == 0x17)
        {
            flag=0;
        }
        else if (received_data == 0x19)
        {
            flag=2;
        }
        else if (received_data == 0x20)
        {
            start_flag=1;
        }


        // else if (received_data == 0x18)
        // {
        //     flag=2;
        // }
    }
    initSweepParam();
}
