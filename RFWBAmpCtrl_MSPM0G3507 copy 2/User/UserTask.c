#include "UserTask.h"
#include <sys/cdefs.h>
//test
volatile uint16_t SweepTick = 0; //trans
volatile uint16_t UITick = 0;
volatile uint16_t UIInfoTick = UI_INFO_TIME; // INFO界面显示倒计时
volatile uint16_t RGBLEDTick = 0;
volatile uint16_t UARTTick = 0;

char sweep_number = 0;

/*******************USER任务******************/
void UserTask_init(void) {
    UserADC_init();
    ENC_init();    
    UI_init();
/****DDS模块初始化***/
    DDS_init();//初始化AD9959
    initSingleToneParam();//初始化点频
    initSweepParam();//初始化扫频
    DDS_update();//DDS刷新
    //AD_init();
}



void get_length(){
    sweep_number = 0 ;
    volatile float sweep_step = 0;
    // DL_GPIO_setPins(GPIO_REALY_PORT, GPIO_REALY_PIN_0_PIN);
    // DL_GPIO_clearPins(GPIO_REALY_PORT, GPIO_REALY_PIN_1_PIN);
    // DL_GPIO_clearPins(GPIO_REALY_PORT, GPIO_REALY_PIN_2_PIN);

    while (sweep_number <= 2) {
    //更新扫频参数
        if (sweep_number == 0) {
            sweep_step = 12.0e5f;         
            sweep[0].freq = 4.0e6f;      
            sweep[1].freq = 4.0e6f;
        }
        else {
            static const float pow10_neg[4] = {1.0f, 0.1f, 0.01f, 0.001f};
            sweep[0].freq += (float)(indx0 - 1) * sweep_step;
            sweep[1].freq += (float)(indx1 - 1) * sweep_step;
            sweep_step = 2.0e6f * pow10_neg[sweep_number];
        }
        DDS_update();
    //进行扫频循环
        for(int i = 0 ; i < ADC_RECV_LEN ; i ++){
            DDS_singleTone(AD9959_CH0, &sweep[0]);
            DDS_singleTone(AD9959_CH1, &sweep[1]);
            DDS_update();
            Tick_delay(100);
            UserADC0_TASK();
            sweep[0].freq += sweep_step;
            sweep[1].freq += sweep_step;
        }
        sweep[0].freq -= 10*sweep_step;
        sweep[1].freq -= 10*sweep_step;
        
        //求解谐振频率和线缆长度
        if (sweep_number == 2 ){
            central_freq = sweep[0].freq + (float)(indx0) * sweep_step;
            length0 = FREQ_TO_LENGTH(central_freq);
            length1 = FREQ_TO_LENGTH(central_freq);
            corrent_operating = finish  ;//认为结束了工作
            }

        sweep_number ++;
    }
}



void UserTask_loop(void) {
    //AD_loop();
    // if (SweepTick >= DDS_SWEEP_TIME) {
    //     SweepTick = 0;
    //     switch (corrent_operating) {
    //         case waiting_length:
    //             get_length();
    //             break;
    //         // case waiting_load:
    //         //     get_load();
    //         //     break;
    //         default:
    //             break;
    //     }
    // }   
    get_length();
}





// /*******************DDS任务移植**********************/
// DDS_SingleToneParam_t SingleTone[4] = {0};
// DDS_SweepParam_t Sweep[3] = {0};

// volatile uint16_t SweepTick = 0;

// void AD_init(void) {
//     initSingleToneParam();
//     initSweepParam();

//     DDS_init();

//     DDS_singleTone(AD9959_CH0, &SingleTone[0]);
//     DDS_singleTone(AD9959_CH1, &SingleTone[1]);
//     DDS_singleTone(AD9959_CH2, &SingleTone[2]);
//     DDS_singleTone(AD9959_CH3, &SingleTone[3]);
//     DDS_update();

//     Tick_delay(5000);

//     DDS_initSweep(AD9959_CH1, &Sweep[0]);
//     DDS_initSweep(AD9959_CH2, &Sweep[1]);
//     DDS_initSweep(AD9959_CH3, &Sweep[2]);
//     DDS_update();
// }

// void AD_loop(void) {
//     if (SweepTick >= DDS_SWEEP_TIME) {
//         SweepTick = 0;
//         DDS_sweep(AD9959_CH1, &Sweep[0]);
//         DDS_sweep(AD9959_CH2, &Sweep[1]);
//         DDS_sweep(AD9959_CH3, &Sweep[2]);
//         DDS_update();
//     }
// }

// void initSingleToneParam(void) {
//     int i;
//     for (i = 0; i < 4; i++) {
//         SingleTone[i].freq = 1000; // 频率1kHz
//         SingleTone[i].amp = 1023;  // 幅度最大(1023)
//     }
//     SingleTone[0].phase = 0x0000; // 相位0度(0)
//     SingleTone[1].phase = 0x1000; // 相位90度(4096)
//     SingleTone[2].phase = 0x2000; // 相位180度(8192)
//     SingleTone[3].phase = 0x3000; // 相位270度(12288)
// }

// void initSweepParam(void) {

//     // 1kHz ~ 100kHz 线性扫频
//     Sweep[0].freq = 1E3F;               // 频率1kHz
//     Sweep[0].amp = 1023;                // 幅度最大(1023)
//     Sweep[0].phase = 0;                 // 相位0度(0)
//     Sweep[0].start = 1E3F;              // 起始频率1kHz
//     Sweep[0].step = 100;                // 步进频率100Hz
//     Sweep[0].end = 100E3F;              // 终止频率100kHz
//     Sweep[0].type = DDS_SWEEP_FREQ;     // 扫频
//     Sweep[0].method = DDS_SWEEP_LINEAR; // 线性扫描

//     // 1Hz ~ 1MHz 对数扫频
//     Sweep[1].freq = 1;                       // 频率1Hz
//     Sweep[1].amp = 1023;                     // 幅度最大(1023)
//     Sweep[1].phase = 0;                      // 相位0度(0)
//     Sweep[1].start = 1;                      // 起始频率1Hz
//     Sweep[1].step = 1.013911386F;            // 步进系数(1000次根号1000000)
//     Sweep[1].end = 1E6F;                     // 终止频率1MHz
//     Sweep[1].type = DDS_SWEEP_FREQ;          // 扫频
//     Sweep[1].method = DDS_SWEEP_LOGARITHMIC; // 对数扫描

//     // 1 ~ 1000 线性扫幅
//     Sweep[2].freq = 1E3F;               // 频率1kHz
//     Sweep[2].amp = 1;                   // 幅度1
//     Sweep[2].phase = 0;                 // 相位0度(0)
//     Sweep[2].start = 1;                 // 起始幅度1
//     Sweep[2].step = 10;                  // 步进幅度10
//     Sweep[2].end = 1000;                // 终止幅度1000
//     Sweep[2].type = DDS_SWEEP_AMP;      // 扫幅
//     Sweep[2].method = DDS_SWEEP_LINEAR; // 线性扫描
// }
