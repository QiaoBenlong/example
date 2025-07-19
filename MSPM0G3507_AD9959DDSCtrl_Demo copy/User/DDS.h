#ifndef __DDS_H__
#define __DDS_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "AD9959.h"

// 扫描类型
typedef enum DDS_SweepType_t {
    DDS_SWEEP_FREQ, // 扫频
    DDS_SWEEP_AMP,  // 扫幅
    DDS_SWEEP_PHASE // 扫相
} DDS_SweepType_t;

// 扫描方式
typedef enum DDS_SweepMethod_t {
    DDS_SWEEP_LINEAR,     // 线性扫描
    DDS_SWEEP_LOGARITHMIC // 对数扫描
} DDS_SweepMethod_t;

// 点频参数
typedef struct DDS_SingleToneParam_t {
    float freq;     // 频率
    uint16_t amp;   // 幅度
    uint16_t phase; // 相位
} DDS_SingleToneParam_t;

// 扫描参数
typedef struct DDS_SweepParam_t {
    float freq;               // 频率
    uint16_t amp;             // 幅度
    uint16_t phase;           // 相位
    float start;              // 起始值
    float step;               // 步进值
    float end;                // 终止值
    float now;                // 当前值
    DDS_SweepType_t type;     // 扫描类型
    DDS_SweepMethod_t method; // 扫描方式
} DDS_SweepParam_t;

/**
 * @brief DDS模块初始化
*/
void DDS_init(void);

/**
 * @brief DDS点频输出
 * @param channel 通道(AD9959_CH0 ~ AD9959_CH3)
 * @param param 点频参数指针
 * @note 配置完成后, 调用DDS_update函数生效
*/
void DDS_singleTone(uint8_t channel, DDS_SingleToneParam_t* param);

/**
 * @brief DDS初始化扫描
 * @param channel 通道(AD9959_CH0 ~ AD9959_CH3)
 * @param param 点频参数指针
 * @note 配置完成后, 调用DDS_update函数生效
*/
void DDS_initSweep(uint8_t channel, DDS_SweepParam_t* param);

/**
 * @brief DDS扫描
 * @details 每次调用后, 扫描步进1步
 * @param channel 通道(AD9959_CH0 ~ AD9959_CH3)
 * @param param 点频参数指针
 * @note 配置完成后, 调用DDS_update函数生效
*/
void DDS_sweep(uint8_t channel, DDS_SweepParam_t* param);

/**
 * @brief 更新DDS参数
*/
void DDS_update(void);

#endif /* #ifndef __DDS_H__ */
