#include "DDS.h"

static DDS_SweepType_t getSweepParam(DDS_SweepParam_t* param);

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
