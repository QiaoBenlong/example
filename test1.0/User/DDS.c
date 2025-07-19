#include "DDS.h"

static DDS_SweepType_t getSweepParam(DDS_SweepParam_t* param);
DDS_SingleToneParam_t SingleTone[2] = {0};
DDS_SingleToneParam_t Sweep[2] = {0};
DDS_mode_t corrent_mode = DDS_POINT;
DDS_Operating_t corrent_operating = DDS_POINT_FREQ;

volatile float default_point_freq = 1000 ;//点频模式默认频率 1k
volatile float default_sweep_freq = 1000000 ;// 扫频模式默认起始频率1Mhz
volatile float default_sweep_freq_cut = 40000000 ;// 扫频模式默认截止频率40Mhz
volatile float default_point_vpp = 256 ;//点频模式默认幅度 此处设置为125mv 对应1023——500mv

volatile float point_freq = 0;//点频频率
volatile float point_vpp = 0;//点频幅度
volatile float sweep_freq_start = 0;//扫频起始
volatile float sweep_freq_cut = 0;//扫频终止


/**
 * @brief DDS模块初始化
*/
void DDS_init(void) {
    AD9959_init();
}

/**
 * @brief DDS点频输出
 * @param channel 通道(AD9959_CH0 ~ AD9959_CH3)
 * @param param 点频参数指针
 * @note 配置完成后, 调用DDS_update函数生效
*/
void DDS_singleTone(uint8_t channel, DDS_SingleToneParam_t* param) {
    AD9959_setFreq(channel, param->freq);
    AD9959_setAmp(channel, param->amp);
    AD9959_setPhase(channel, param->phase);
}

/**
 * @brief DDS初始化扫描
 * @param channel 通道(AD9959_CH0 ~ AD9959_CH3)
 * @param param 点频参数指针
 * @note 配置完成后, 调用DDS_update函数生效
*/
void DDS_initSweep(uint8_t channel, DDS_SweepParam_t* param) {
    param->now = param->start;
    AD9959_setFreq(channel, param->freq);
    AD9959_setAmp(channel, param->amp);
    AD9959_setPhase(channel, param->phase);
}

/**
 * @brief DDS扫描
 * @details 每次调用后, 扫描步进1步
 * @param channel 通道(AD9959_CH0 ~ AD9959_CH3)
 * @param param 点频参数指针
 * @note 配置完成后, 调用DDS_update函数生效
*/
void DDS_sweep(uint8_t channel, DDS_SweepParam_t* param) {
    switch (getSweepParam(param)) {
        case DDS_SWEEP_FREQ:
            AD9959_setFreq(channel, param->freq);
            break;
        case DDS_SWEEP_AMP:
            AD9959_setAmp(channel, param->amp);
            break;
        case DDS_SWEEP_PHASE:
            AD9959_setPhase(channel, param->phase);
            break;
    }
}

/**
 * @brief 更新DDS参数
*/
void DDS_update(void) {
    AD9959_IOUpdate();
}

/**
 * @brief 获取下一步扫描参数
 * @param param 点频参数指针
 * @return 扫描类型
 * @note 由DDS_sweep函数调用
*/
static DDS_SweepType_t getSweepParam(DDS_SweepParam_t* param) {
    switch (param->method) {
        case DDS_SWEEP_LINEAR:
            param->now += param->step;
            break;
        case DDS_SWEEP_LOGARITHMIC:
            param->now *= param->step;
            break;
    }
    if (param->now > param->end) param->now = param->start;
    switch (param->type) {
        case DDS_SWEEP_FREQ:
            param->freq = param->now;
            break;
        case DDS_SWEEP_AMP:
            param->amp = (uint16_t)(param->now + 0.5F);
            break;
        case DDS_SWEEP_PHASE:
            param->phase = (uint16_t)(param->now + 0.5F);
            break;
    }
    return param->type;
}

void initSingleToneParam(void) {
    SingleTone[0].freq = default_point_freq; // 频率1kHz
    SingleTone[0].amp = 1023;  // 幅度最大(1023)
    SingleTone[0].phase = 0x0000; // 相位0度(0)
}

void initSweepParam(void) {
    Sweep[0].freq = sweep_freq_start; // 频率1kHz
    Sweep[0].amp = 1023;  // 幅度最大(1023)
    Sweep[0].phase = 0x0000; // 相位0度(0)

    Sweep[1].freq = sweep_freq_start; // 频率1kHz
    Sweep[1].amp = 1023;  // 幅度最大(1023)
    Sweep[1].phase = 0x1000; // 相位90度 这里可能需要调参
}


