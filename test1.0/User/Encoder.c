#include "Encoder.h"
#include "Tick.h"

volatile uint8_t ENCSWTick = 0;
volatile int ENCVal = 0;
volatile int outset = 0;//增量
volatile uint16_t enc_number = 0;//按键次数
volatile float step_size = 0;//步长

void ENC_init(void) {
    NVIC_EnableIRQ(GPIO_ENC_INT_IRQN);
}

int ENC_getIncVal(void) {
    int val = ENCVal;
    ENCVal = 0;
    return val;
}

uint8_t ENC_getSW(void) {
    if (ENC_SW_PRESS && !ENCSWTick) {
        ENCSWTick = ENC_SW_DEBOUNCE_TIME;
        return 1;
    }
    else {
        return 0;
    }
}
//用于检测按键次数与清除编码器增量
void ENC_TASK(){
    outset += ENC_getIncVal();
    //当切换模式的时候 outset会清零，此处在
    switch (corrent_operating){
        case DDS_POINT_FREQ:
            step_size = (float)(100000 * outset);
            point_freq  = default_point_freq + step_size ;//更新频率
            //SingleTone[0].freq = point_freq ; // 频率步长是100khz
            break;
        case DDS_POINT_VPP:
            step_size = (float)(40 * outset);
            point_vpp  = default_point_vpp + step_size ;//更新幅度
            //SingleTone[0].amp = point_vpp  ; // 幅度步长是10mv
            break;
        case DDS_SWEEP_START:
            step_size = (float)(100000 * outset);
            sweep_freq_start  = default_sweep_freq + step_size ; //更新步长
            //Sweep[0].freq = sweep_freq_start;                    // 频率1MHz
            break;
        case DDS_SWEEP_END:
            step_size = (float)(100000 * outset);
            sweep_freq_cut  = default_sweep_freq_cut + step_size ;//更新步长
            break;
    }
}

// GPIO中断
void GROUP1_IRQHandler(void) {
    if (DL_GPIO_getPendingInterrupt(GPIO_ENC_ENC_A_PORT) == GPIO_ENC_ENC_A_IIDX) {
        if (DL_GPIO_readPins(GPIO_ENC_ENC_B_PORT, GPIO_ENC_ENC_B_PIN)) {
            ENCVal--;
        }
        else {
            ENCVal++;
        }
    }
}
