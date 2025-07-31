#include "UI.h"

UIPage_t UIPage = PAGE_INFO;

int GainSetPos = 0; // 增益设定位置(0:小数点后1位; 1:个位; 2:十位)

void UI_init(void)
    {
        UART2_printf("page info\xFF\xFF\xFF");


    }

void UI_taskShow1(void){
    // UART2_printf("sweep.t7.txt=\"%.1f\"\xff\xff\xff",data_of_test);
    UART2_printf("sweep.t4.txt=\"%.1f\"\xff\xff\xff",freq_start);
    UART2_printf("sweep.t5.txt=\"%.1f\"\xff\xff\xff",freq_end);
    UART2_printf("sweep.t6.txt=\"%.1f\"\xff\xff\xff",freq_step);
    UART2_printf("sweep.t1.txt=\"%.2f\"\xff\xff\xff",length);

    //UART2_printf("data.t1.txt=\"%.1f\"\xff\xff\xff",freq/1000000);
}

void UI_taskShow2(void)
{
    // UART2_printf("home.t0.txt=\"%.4f\"\xff\xff\xff",v3);
    UART2_printf("two.t14.txt=\"%d\"\xff\xff\xff",toggle_flag);
    UART2_printf("two.t9.txt=\"%.4f\"\xff\xff\xff",Volt1);
    UART2_printf("two.t12.txt=\"%.4f\"\xff\xff\xff",Volt2);
    UART2_printf("two.t13.txt=\"%.4f\"\xff\xff\xff",amp_measured);
}

void UI_taskShow3(void)
{
    UART2_printf("order.t16.txt=\"%.4f\"\xff\xff\xff",v1);
}

void UI_taskShow4(void)
{
    UART2_printf("rfc.t11.txt=\"%.4f\"\xff\xff\xff",v2);

}
// void UI_taskShow3(void)
// {
//     UART2_printf("home.t6.txt=\"%.1f\"\xff\xff\xff",freq/1000000);
    

// }


void UI_taskBTN(void) {
}

void UI_taskENC(void) {
}
