#include "UserTask.h"
#include "AD9959.h"
#include "DDS.h"
#include "Tick.h"
#include "Volt_Gain.h"

/**
 * 引脚连接方式
 * System Configuration: GPIO组名: GPIO_DDS
 * MSPM0 GPIO引脚 -> AD9959模块引脚
 *
 * DDS_SCLK   -> AD9959_SCLK
 * DDS_SDIO0  -> AD9959_SDIO0
 * DDS_CS     -> AD9959_CS
 * DDS_UPDATE -> AD9959_UPDATE
 * DDS_RST    -> AD9959_RST
 * GND        -> GND
 *
 * AD9959模块其余数据引脚均接GND
*/


volatile uint16_t SweepTick = 0;
volatile float Gain_real[SWEEP_cycles] = {0};
void UserTask_init(void) {
    ENC_init();
    UserADC_init();
    UART2_init();
    UI_init();

    initSingleToneParam();
    initSweepParam();
    DDS_init();
    DDS_update();
    
}

void UserTask_loop(void) {
    ENC_TASK();//先设置编码器增量,根据增量更新参数值，选择工作模式
    if (SweepTick >= DDS_SWEEP_TIME) {
        SweepTick = 0;
        if (corrent_mode == DDS_POINT){
            DDS_singleTone(AD9959_CH0,&SingleTone[0]);
        }
        /*
        if (corrent_mode == DDS_SWEEP){
            for(int i = 0; i < SWEEP_cycles ; i ++){
                DDS_singleTone(AD9959_CH0,&Sweep[0]);
                DDS_singleTone(AD9959_CH1,&Sweep[1]);
                //adc采样并计算增益
                Volt_Gain_taskGetData();
                Gain_real[i] = Gain;
                //更新参数值
                Tick_delay(5);//安全性延时
                Sweep[0].freq = default_sweep_freq + i * 100000;//步长是0.1MHZ
                Sweep[1].freq = default_sweep_freq + i * 100000;//步长是0.1MHZ
                DDS_update();
            }
        }
        */
        DDS_update();
    }
    if (UITick >= UI_TIME) {
        UITick = 0;
        UI_taskShow();
    }    
}


