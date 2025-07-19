#include "UserTask.h"
#include "AD9959.h"
#include "DDS.h"
#include "Tick.h"
#include "UserADC.h" 
#include "UserUART.h"


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
loaded_t loaded = Open; //当前工作状态
char sweep_number = 0;
// float freq = 0;
volatile uint16_t UITick = 0;

void get_length(){
    sweep_number = 0 ;
    volatile float sweep_step = 0;
    DL_GPIO_setPins(GPIO_REALY_PORT, GPIO_REALY_PIN_0_PIN);
    DL_GPIO_clearPins(GPIO_REALY_PORT, GPIO_REALY_PIN_1_PIN);
    DL_GPIO_clearPins(GPIO_REALY_PORT, GPIO_REALY_PIN_2_PIN);

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

void get_load(){
        DL_GPIO_setPins(GPIO_REALY_PORT, GPIO_REALY_PIN_1_PIN);
        DL_GPIO_clearPins(GPIO_REALY_PORT, GPIO_REALY_PIN_2_PIN);
        DL_GPIO_clearPins(GPIO_REALY_PORT, GPIO_REALY_PIN_0_PIN);

        Tick_delay(10);

        UserADC1_TASK();
        if (load >= 10 && load <= 40){
            loaded = Res;
        }
        else {
        DL_GPIO_setPins(GPIO_REALY_PORT, GPIO_REALY_PIN_2_PIN);
        DL_GPIO_clearPins(GPIO_REALY_PORT, GPIO_REALY_PIN_1_PIN);

        Tick_delay(10);
        
            loaded = Cap;
            freq = GET_FREQ();
            load = 1.44 / (2010 * 10e-10 * freq) - 631;

        }
        corrent_operating = finish  ;//认为结束了工作
    }


void UserTask_init(void) {
    //其他外设的初始化
    ENC_init();
    UserADC_init();
    UART2_init();
    UI_init();
    GET_FREQ_Init();
    //DDS模块的初始化
    DDS_init();
    initSingleToneParam();
    initSweepParam();
    DDS_update();
}

void UserTask_loop(void) {

    if (UITick >= UI_TIME) {
        UITick = 0;
        UI_taskShow();
    }   

    if (SweepTick >= DDS_SWEEP_TIME) {
        SweepTick = 0;
        switch (corrent_operating) {
            case waiting_length:
                get_length();
                break;
            case waiting_load:
                get_load();
                break;
            default:
                break;
        }
    }   

}


