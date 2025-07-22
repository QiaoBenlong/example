#include "UI.h"

UIPage_t UIPage = PAGE_INFO;

int GainSetPos = 0; // 增益设定位置(0:小数点后1位; 1:个位; 2:十位)

void UI_init(void)
    {
        UART2_printf("page info\xFF\xFF\xFF");


    }

void UI_taskShow1(void){
    UART2_printf("sweep.t7.txt=\"%.1f\"\xff\xff\xff",data_of_test);
    UART2_printf("sweep.t4.txt=\"%.1f\"\xff\xff\xff",freq_start);
    UART2_printf("sweep.t5.txt=\"%.1f\"\xff\xff\xff",freq_end);
    UART2_printf("sweep.t6.txt=\"%.1f\"\xff\xff\xff",freq_step);

    //UART2_printf("data.t1.txt=\"%.1f\"\xff\xff\xff",freq/1000000);
}

void UI_taskShow2(void)
{
    UART2_printf("data.t1.txt=\"%.1f\"\xff\xff\xff",freq/1000000);

}

void UI_taskShow3(void)
{
    UART2_printf("amp_measure.t0.txt=\"%.4f\"\xff\xff\xff",amp_measured);

}


void UI_taskBTN(void) {
}

void UI_taskENC(void) {
}
