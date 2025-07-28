// #include "UserADC.h"
// #include "ti_msp_dl_config.h"   
// #include <stdint.h>
// #include <stdbool.h>

// /// 累加 N 次后取平均
// #define AVG_COUNT       10

// /// 全局循环缓存，存放每次 5 次采样后的平均值
// volatile uint16_t ADC_recieve0[ADC_RECV_LEN] = {0}; 
// volatile uint16_t ADC_recieve1[ADC_RECV_LEN] = {0};
// volatile uint16_t ADC_recieve2 = 0;

// /// 最大标号
// volatile uint16_t indx0 = 0;
// volatile uint16_t indx1 = 0;

// /// 测量参数
// volatile uint16_t length0 = 0;
// volatile uint16_t length1 = 0;
// volatile float central_freq = 0;
// volatile float    load    = 0;

// /// 中断内部累加器和计数
// static uint32_t sum0, sum1, sum2;
// static uint8_t  sampleCnt;
// static uint8_t  bufIdx;

// /// 交给 TASK 处理的完成标志
// static volatile bool ADC0DataValid;
// static volatile bool ADC1DataValid;


// static float findMaxIndex(volatile uint16_t *arr, int len)
// {
//     int idx = 0;
//     for (int i = 1; i < len; i++) {
//         if (arr[i] > arr[idx]) {
//             idx = i;
//         }
//     }
//     return (float)idx;
// }


// void UserADC_init(void) {
//     sampleCnt = 0;
//     bufIdx    = 0;
//     sum0 = sum1 = sum2 = 0;
//     ADC0DataValid = false;
//     ADC1DataValid = false;
//     NVIC_EnableIRQ(ADC0_INST_INT_IRQN);
//     NVIC_EnableIRQ(ADC1_INST_INT_IRQN);
// }



// void UserADC0_TASK(void)
// {
//     //循环模式下 由于在中断中禁止使能，此处要重新打开
//     DL_ADC12_enableConversions(ADC0_INST);
//     DL_ADC12_startConversion(ADC0_INST);
    
//     while (!ADC0DataValid); 
//     ADC0DataValid = false;

//     if (bufIdx >= ADC_RECV_LEN) {
//         bufIdx = 0;

//         indx0 = findMaxIndex(ADC_recieve0, ADC_RECV_LEN);
//         indx1 = findMaxIndex(ADC_recieve1, ADC_RECV_LEN);

//     }
// }

// void UserADC1_TASK(void)
// {
//     for(int i = 0 ; i < 2 * AVG_COUNT ; i ++){
//         DL_ADC12_startConversion(ADC1_INST);
//         while (!ADC1DataValid); 
//         ADC1DataValid = false;
//     }
//     load = ADC_VAL_TO_LOAD(ADC_recieve2);

// }


// /* ======= 中断服务函数 ======= */
// void ADC0_IRQHandler(void)
// {
//     if (DL_ADC12_getPendingInterrupt(ADC0_INST) == DL_ADC12_IIDX_MEM1_RESULT_LOADED)
//     {
//         // 1) 取2路采样值
//         uint16_t v0 = DL_ADC12_getMemResult(ADC0_INST, ADC0_ADCMEM_0);
//         uint16_t v1 = DL_ADC12_getMemResult(ADC0_INST, ADC0_ADCMEM_1);

//         // 2) 累加
//         sum0 += v0;
//         sum1 += v1;
//         sampleCnt++;

//         // 3) 达到 N 次，计算平均、存缓存、清累加器、标记完成
//         if (sampleCnt >= AVG_COUNT) {
//             ADC_recieve0[bufIdx] = sum0 / AVG_COUNT;
//             ADC_recieve1[bufIdx] = sum1 / AVG_COUNT;

//             sum0 = sum1 = 0;
//             sampleCnt = 0;
//             bufIdx++;

//             // 4) 清中断、重启下一轮转换
//             DL_ADC12_disableConversions(ADC0_INST);
//             ADC0DataValid = true;
//         }
//     }
// }

// // ADC1中断服务函数
// void ADC1_IRQHandler(void) {
//     if (DL_ADC12_getPendingInterrupt(ADC1_INST) == DL_ADC12_IIDX_MEM0_RESULT_LOADED) {
//         uint16_t v2 = DL_ADC12_getMemResult(ADC1_INST, ADC0_ADCMEM_0);
//         sum2 += v2;
//         sampleCnt++;

//         if (sampleCnt >= AVG_COUNT) {
//             ADC_recieve2 = sum2 / (AVG_COUNT);

//             sum2 = 0;
//             sampleCnt = 0;
//         }

//         ADC1DataValid = true;
//         DL_ADC12_enableConversions(ADC1_INST);
//     }
// }

#include "UserADC.h"

// volatile uint16_t ADC0Data = 0;
// volatile uint16_t ADC1Data = 0;
// volatile uint8_t ADC0DataValid = 0;
// volatile uint8_t ADC1DataValid = 0;

// void UserADC_init(void) {
//     NVIC_EnableIRQ(ADC0_INST_INT_IRQN);
//     NVIC_EnableIRQ(ADC1_INST_INT_IRQN);
// }

// void UserADC0_start(void) {
//     // ADC0DataValid = 0;
//     DL_ADC12_startConversion(ADC0_INST);
// }

// void UserADC1_start(void) {
//     ADC1DataValid = 0;
//     DL_ADC12_startConversion(ADC1_INST);
// }

// uint16_t UserADC0_getData(uint32_t timeout) {
//     uint32_t startTime = Tick;
//     while (!ADC0DataValid) {
//         if (Tick - startTime >= timeout) return 0;
//     }
//     return ADC0Data;
// }

// uint16_t UserADC1_getData(uint32_t timeout) {
//     uint32_t startTime = Tick;
//     while (!ADC1DataValid) {
//         if (Tick - startTime >= timeout) return 0;
//     }
//     return ADC1Data;
// }


// // ADC0中断服务函数
// void ADC0_IRQHandler(void) {
//     if (DL_ADC12_getPendingInterrupt(ADC0_INST) == DL_ADC12_IIDX_MEM0_RESULT_LOADED) 
//     {
//         ADC0Data = DL_ADC12_getMemResult(ADC0_INST, ADC0_ADCMEM_0);
//         ADC0DataValid = 1;
//         DL_ADC12_enableConversions(ADC0_INST);
//     }
// }

// // ADC1中断服务函数
// void ADC1_IRQHandler(void) {
//     if (DL_ADC12_getPendingInterrupt(ADC1_INST) == DL_ADC12_IIDX_MEM0_RESULT_LOADED) {
//         ADC1Data = DL_ADC12_getMemResult(ADC1_INST, ADC1_ADCMEM_0);
//         ADC1DataValid = 1;
//         DL_ADC12_enableConversions(ADC1_INST);
//     }
// }

#define RESULT_SIZE (2048)
#define AVG_COUNT     5
volatile bool gCheckADC;
volatile bool gCheckADC1;
volatile uint16_t gAdcResult;
volatile uint16_t gAdcResult1;
volatile uint16_t gAdcResult2;
volatile uint16_t gAdcResult3;
volatile float getADC[RESULT_SIZE]; 
volatile float amp_measured;
volatile float Vol_temp;
volatile int sampleCnt = 0;
volatile int Cnt = 0;
volatile float sum = 0;
volatile float v1 = 0;
volatile float v2 = 0;
// volatile float amp_measured1 = 0;
volatile float sum1 = 0;
volatile float sampleCnt1 = 0;
volatile int Cnt1 = 0;
volatile float amp_length[RESULT_SIZE];

void UserADC_init(void)
{
    NVIC_EnableIRQ(ADC0_INST_INT_IRQN);
    NVIC_EnableIRQ(ADC1_INST_INT_IRQN);
    gCheckADC = false;
    gCheckADC1 = false;
}

void UserTask_ADC(void)
{
    DL_ADC12_startConversion(ADC0_INST);
    while(false == gCheckADC){}
    gAdcResult = DL_ADC12_getMemResult(ADC0_INST,DL_ADC12_MEM_IDX_0);//A25
    Vol_temp = ADC_VAL_TO_VOLTAGE(gAdcResult);
    // amp_length[Cnt] = ADC_VAL_TO_VOLTAGE(gAdcResult);
    // sum += Vol_temp;
    // sampleCnt++;
    // if(sampleCnt >= AVG_COUNT)
    // {
    //     amp_length[Cnt] = sum / (AVG_COUNT);//ad8302 1号 测量种类
    //     sum = 0;
    //     sampleCnt = 0;
        
    // }
  

    gCheckADC = false;
    DL_ADC12_enableConversions(ADC0_INST);

}

void UserTask_ADC1(void)
{
    DL_ADC12_startConversion(ADC1_INST);
    while(false == gCheckADC1){}//waiting....
    gAdcResult1 = DL_ADC12_getMemResult(ADC1_INST,DL_ADC12_MEM_IDX_0);//A15
    gAdcResult2 = DL_ADC12_getMemResult(ADC1_INST,DL_ADC12_MEM_IDX_1);//A16
    gAdcResult3 = DL_ADC12_getMemResult(ADC1_INST,DL_ADC12_MEM_IDX_2);
    v1 = ADC_VAL_TO_VOLTAGE(gAdcResult1);//ad8302 2号 测量线序
    amp_measured = ADC_VAL_TO_VOLTAGE(gAdcResult2);//ad8302 1号 测量线种类
    v2 = ADC_VAL_TO_VOLTAGE(gAdcResult3);
    sum1 += amp_measured;
    sampleCnt1++;
    if(sampleCnt1 >= AVG_COUNT)
    {
        Vol_temp = sum1 / (AVG_COUNT);
        sum1 = 0;
        sampleCnt1 = 0;
        // Cnt1++;
    }
    // if(Cnt1 >= RESULT_SIZE)
    // {
    //     Cnt1 = 0;
    // }
    gCheckADC1 = false;
    DL_ADC12_enableConversions(ADC1_INST);
}


void ADC0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC0_INST)) {
        case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
            gCheckADC = true;
            // freq_record[flag_i] = Sweep[0].now;
            // flag_i++;
            break;
        default:
            break;
    }
}

void ADC1_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC1_INST)) {
        case DL_ADC12_IIDX_MEM2_RESULT_LOADED:
            gCheckADC1 = true;
            break;
        default:
            break;
    }
}