#ifndef __AD9959_H__
#define __AD9959_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"

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

// AD9959引脚操作定义
#define AD9959_SCLK_H   (DL_GPIO_setPins(GPIO_DDS_DDS_SCLK_PORT, GPIO_DDS_DDS_SCLK_PIN))
#define AD9959_SCLK_L   (DL_GPIO_clearPins(GPIO_DDS_DDS_SCLK_PORT, GPIO_DDS_DDS_SCLK_PIN))
#define AD9959_SDIO0_H  (DL_GPIO_setPins(GPIO_DDS_DDS_SDIO0_PORT, GPIO_DDS_DDS_SDIO0_PIN))
#define AD9959_SDIO0_L  (DL_GPIO_clearPins(GPIO_DDS_DDS_SDIO0_PORT, GPIO_DDS_DDS_SDIO0_PIN))
#define AD9959_CS_H     (DL_GPIO_setPins(GPIO_DDS_DDS_CS_PORT, GPIO_DDS_DDS_CS_PIN))
#define AD9959_CS_L     (DL_GPIO_clearPins(GPIO_DDS_DDS_CS_PORT, GPIO_DDS_DDS_CS_PIN))
#define AD9959_UPDATE_H (DL_GPIO_setPins(GPIO_DDS_DDS_UPDATE_PORT, GPIO_DDS_DDS_UPDATE_PIN))
#define AD9959_UPDATE_L (DL_GPIO_clearPins(GPIO_DDS_DDS_UPDATE_PORT, GPIO_DDS_DDS_UPDATE_PIN))
#define AD9959_RST_H    (DL_GPIO_setPins(GPIO_DDS_DDS_RST_PORT, GPIO_DDS_DDS_RST_PIN))
#define AD9959_RST_L    (DL_GPIO_clearPins(GPIO_DDS_DDS_RST_PORT, GPIO_DDS_DDS_RST_PIN))

//AD9959寄存器地址定义
#define CSR_ADD   0x00   //CSR 通道选择寄存器
#define FR1_ADD   0x01   //FR1 功能寄存器1
#define FR2_ADD   0x02   //FR2 功能寄存器2
#define CFR_ADD   0x03   //CFR 通道功能寄存器

#define CFTW0_ADD 0x04   //CTW0 通道频率转换字寄存器
#define CPOW0_ADD 0x05   //CPW0 通道相位转换字寄存器
#define ACR_ADD   0x06   //ACR 幅度控制寄存器

#define LSRR_ADD  0x07   //LSR 线性扫描斜率寄存器
#define RDW_ADD   0x08   //RDW 上升扫描增量寄存器
#define FDW_ADD   0x09   //FDW 下降扫描增量寄存器

#define PROFILE_ADDR_BASE   0x0A   //Profile寄存器,配置文件寄存器起始地址

//CSR[7:4]通道选择启用位
#define AD9959_CH0 0x10
#define AD9959_CH1 0x20
#define AD9959_CH2 0x40
#define AD9959_CH3 0x80

//FR1[9:8] 调制电平选择位
#define LEVEL_MOD_2     0x00 //2电平调制  2阶调制
#define LEVEL_MOD_4     0x01 //4电平调制  4阶调制
#define LEVEL_MOD_8     0x02 //8电平调制  8阶调制
#define LEVEL_MOD_16    0x03 //16电平调制 16阶调制

//CFR[23:22]  幅频相位（AFP）选择位
#define    DISABLE_MOD        0x00    //00    调制已禁用
#define    ASK                0x40    //01    振幅调制，幅移键控
#define    FSK                0x80    //10    频率调制，频移键控
#define    PSK                0xc0    //11    相位调制，相移键控

//（CFR[14]）线性扫描启用 sweep enable                                                                                
#define    SWEEP_ENABLE    0x40    //1    启用
#define    SWEEP_DISABLE    0x00    //0    不启用

void AD9959_delayMicros(uint32_t us);
void AD9959_reset(void);                 //AD9959复位
void AD9959_IOUpdate(void);           //AD9959更新数据
void AD9959_IOInit(void);                //IO口电平状态初始化
void AD9959_init(void);            //IO口初始化

/***********************AD9959基本寄存器操作函数*****************************************/
void AD9959_writeData(uint8_t regAddr, uint8_t regN, uint8_t* regData);//向AD9959写数据
void AD9959_writeDataSlow(uint8_t regAddr, uint8_t regN, uint8_t* regData);
void AD9959_writeCFTW0(float freq);                                        //写CFTW0通道频率转换字寄存器
void AD9959_writeACR(uint16_t amp);                                        //写ACR通道幅度转换字寄存器
void AD9959_writeCPOW0(uint16_t phase);                                    //写CPOW0通道相位转换字寄存器

void AD9959_writeLSRR(uint8_t rsrr, uint8_t fsrr);                //写LSRR线性扫描斜率寄存器
void AD9959_writeRDW(uint32_t r_delta);                                    //写RDW上升增量寄存器
void AD9959_writeFDW(uint32_t f_delta);                                    //写FDW下降增量寄存器

void AD9959_writeProfileFreq(uint8_t profile, uint32_t data);//写Profile寄存器,频率
void AD9959_writeProfileAmp(uint8_t profile, uint16_t data);//写Profile寄存器,幅度
void AD9959_writeProfilePhase(uint8_t profile, uint16_t data);//写Profile寄存器,相位
/********************************************************************************************/


/*****************************点频操作函数***********************************/
void AD9959_setFreq(uint8_t channel, float freq); //写频率
void AD9959_setAmp(uint8_t channel, uint16_t amp); //写幅度
void AD9959_setPhase(uint8_t channel, uint16_t phase); //写相位
/****************************************************************************/

/*****************************调制操作函数  ***********************************/
void AD9959_modulationInit(uint8_t channel, uint8_t modulation, uint8_t sweepEn, uint8_t nLevel);//设置各个通道的调制模式。
void AD9959_setFSK(uint8_t channel, uint32_t* data, uint16_t phase);//设置FSK调制的参数
void AD9959_setASK(uint8_t channel, uint16_t* data, uint32_t freq, uint16_t phase);//设置ASK调制的参数
void AD9959_setPSK(uint8_t channel, uint16_t* data, uint32_t freq);//设置PSK调制的参数

void AD9959_setFreqSweep(uint8_t channel, uint32_t s_data, uint32_t e_data, uint32_t r_delta, uint32_t f_delta, uint8_t rsrr, uint8_t fsrr, uint16_t amp, uint16_t phase);//设置线性扫频的参数
void AD9959_setAmpSweep(uint8_t channel, uint32_t s_Ampli, uint16_t e_Ampli, uint32_t r_delta, uint32_t f_delta, uint8_t rsrr, uint8_t fsrr, uint32_t freq, uint16_t phase);//设置线性扫幅的参数
void AD9959_setPhaseSweep(uint8_t channel, uint16_t s_data, uint16_t e_data, uint16_t r_delta, uint16_t f_delta, uint8_t rsrr, uint8_t fsrr, uint32_t freq, uint16_t amp);//设置线性扫相的参数
/********************************************************************************************/

#endif /* #ifndef __AD9959_H__ */
