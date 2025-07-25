#include "UI.h"

#define SINE_SAMPLES 64
// const uint8_t sineTable[128] = {
//     50,  53,  56,  59,  62,  65,  68,  70,  73,  75,  77,  79,  81,  82,  84,  85,
//     86,  87,  87,  88,  88,  88,  87,  86,  85,  84,  83,  81,  79,  77,  75,  73,
//     70,  68,  65,  62,  59,  56,  53,  50,  47,  44,  41,  38,  35,  32,  30,  27,
//     25,  23,  21,  19,  18,  16,  15,  14,  13,  12,  12,  11,  11,  11,  12,  12,
//     13,  14,  15,  16,  18,  19,  21,  23,  25,  27,  30,  32,  35,  38,  41,  44,
//     47,  50,  53,  56,  59,  62,  65,  68,  70,  73,  75,  77,  79,  81,  82,  84,
//     85,  86,  87,  87,  88,  88,  88,  87,  86,  85,  84,  83,  81,  79,  77,  75,
//     72,  70,  67,  64,  61,  58,  55,  52,  49,  46,  43,  40,  37,  34,  32,  30
// };


// UIPage_t UIPage = PAGE_INFO;

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
    // UART2_printf("sweep.t12.txt=\"%.4f\"\xff\xff\xff",amp_dc1);
    // UART2_printf("sweep.t11.txt=\"%.4f\"\xff\xff\xff",amp_dc2);   
    
    //UART2_printf("data.t1.txt=\"%.1f\"\xff\xff\xff",freq/1000000);
}

void UI_taskShow2(void)
{
    UART2_printf("data.t1.txt=\"%.1f\"\xff\xff\xff",freq/1000000);
    UART2_printf("data.t2.txt=\"%.4f\"\xff\xff\xff",v_final-20);
    UART2_printf("data.t9.txt=\"%.1f\"\xff\xff\xff",Phase[10]);
    UART2_printf("data.t7.txt=\"%.4f\"\xff\xff\xff",amp_measured1);
    // UART2_printf("data.t4.txt=\"%.4f\"\xff\xff\xff",amp_dc2);   

}

void UI_taskShow3(void)
{
    UART2_printf("amp_measure.t0.txt=\"%.4f\"\xff\xff\xff",amp_measured1);
}

void UI_taskShow4(void)
{
    UART2_printf("curve.t1.txt=\"%.1f\"\xff\xff\xff",v_final-20);
    UART2_printf("curve.t9.txt=\"%.1f\"\xff\xff\xff",Phase[10]);
    for(int i = 0;i < 511; i++)
    {
        UART2_printf("add s0.id,0,%d\xff\xff\xff",(int)((AMP_FINAL[i]-6)*20));
        UART2_printf("add s0.id,1,%d\xff\xff\xff",(int)(Phase[i]));
    }
}

void UI_taskShow5(void)
{
    // UART2_printf(char *fmt, ...)


}


void UI_taskBTN(void) {
}

void UI_taskENC(void) {
}
