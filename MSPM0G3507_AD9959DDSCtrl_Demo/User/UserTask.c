#include "UserTask.h"

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

DDS_SingleToneParam_t SingleTone[4] = {0};
DDS_SweepParam_t Sweep[3] = {0};

volatile uint16_t SweepTick = 0;

void UserTask_init(void) {
    initSingleToneParam();
    initSweepParam();

    DDS_init();

    // DDS_singleTone(AD9959_CH0, &SingleTone[0]);
    // DDS_singleTone(AD9959_CH1, &SingleTone[1]);
    // DDS_singleTone(AD9959_CH2, &SingleTone[2]);
    // DDS_singleTone(AD9959_CH3, &SingleTone[3]);
    // DDS_update();

   // Tick_delay(5000);

    DDS_initSweep(AD9959_CH1, &Sweep[0]);
    DDS_initSweep(AD9959_CH2, &Sweep[1]);
    DDS_initSweep(AD9959_CH3, &Sweep[2]);
    DDS_update();
}

void UserTask_loop(void) {
    if (SweepTick >= DDS_SWEEP_TIME) {
        SweepTick = 0;
        DDS_sweep(AD9959_CH1, &Sweep[0]);
        DDS_sweep(AD9959_CH2, &Sweep[1]);
        DDS_sweep(AD9959_CH3, &Sweep[2]);
        DDS_update();
    }
}

void initSingleToneParam(void) {
    int i;
    for (i = 0; i < 4; i++) {
        SingleTone[i].freq = 1000; // 频率1kHz
        SingleTone[i].amp = 1023;  // 幅度最大(1023)
    }
    SingleTone[0].phase = 0x0000; // 相位0度(0)
    SingleTone[1].phase = 0x1000; // 相位90度(4096)
    SingleTone[2].phase = 0x2000; // 相位180度(8192)
    SingleTone[3].phase = 0x3000; // 相位270度(12288)
}

void initSweepParam(void) {

    // CH1:1MHz ~ 40MHz 线性扫频   
    Sweep[0].amp = 1023;                // 幅度最大(1023)
    Sweep[0].phase = 0;                 // 相位0度(0)
    Sweep[0].start = 1E6F;              // 起始频率1kHz
    Sweep[0].step = 100E3F;                // 步进频率100Hz
    Sweep[0].end = 40E6F;              // 终止频率100kHz
    Sweep[0].type = DDS_SWEEP_FREQ;     // 扫频
    Sweep[0].method = DDS_SWEEP_LINEAR; // 线性扫描



    // CH2:1MHz ~ 40MHz 线性扫频   
    Sweep[1].amp = 1023;                // 幅度最大(1023)
    Sweep[1].phase = 4096;                 // 相位90度(4096)
    Sweep[1].start = 1E6F;              // 起始频率1kHz
    Sweep[1].step = 100E3F;                // 步进频率100Hz
    Sweep[1].end = 40E6F;              // 终止频率100kHz
    Sweep[1].type = DDS_SWEEP_FREQ;     // 扫频
    Sweep[1].method = DDS_SWEEP_LINEAR; // 线性扫描


    // // 1Hz ~ 1MHz 对数扫频
    // Sweep[1].freq = 1;                       // 频率1Hz
    // Sweep[1].amp = 1023;                     // 幅度最大(1023)
    // Sweep[1].phase = 0;                      // 相位0度(0)
    // Sweep[1].start = 1;                      // 起始频率1Hz
    // Sweep[1].step = 1.013911386F;            // 步进系数(1000次根号1000000)
    // Sweep[1].end = 1E6F;                     // 终止频率1MHz
    // Sweep[1].type = DDS_SWEEP_FREQ;          // 扫频
    // Sweep[1].method = DDS_SWEEP_LOGARITHMIC; // 对数扫描

    // 1 ~ 1000 线性扫幅
    Sweep[2].freq = 1E3F;               // 频率1kHz
    Sweep[2].amp = 1;                   // 幅度1
    Sweep[2].phase = 0;                 // 相位0度(0)
    Sweep[2].start = 1;                 // 起始幅度1
    Sweep[2].step = 10;                  // 步进幅度10
    Sweep[2].end = 1000;                // 终止幅度1000
    Sweep[2].type = DDS_SWEEP_AMP;      // 扫幅
    Sweep[2].method = DDS_SWEEP_LINEAR; // 线性扫描
}
