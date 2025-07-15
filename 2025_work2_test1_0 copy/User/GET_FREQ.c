#include "GET_FREQ.h"
#include "ti_msp_dl_config.h"    // TI 提供的 SysConfig 生成头
#include <stdbool.h>

/* ===== 文件私有全局变量 ===== */
static volatile uint32_t gCaptureCnt;
static volatile bool     gSynced;
static volatile bool     gCheckCaptures;
static uint32_t          gLoadValue;

/**
 * @brief  TimerG0 Capture 模块初始化
 *         - DOWN counting combined capture 模式
 *         - CC0/CC1 捕获上升/下降沿
 *         - 使能中断，启动计数
 */
void GET_FREQ_Init(void)
{
    SYSCFG_DL_init();

    /* 2) 读取自动重装载值（MAX 计数值，用于计算周期） */
    gLoadValue = DL_TimerG_getLoadValue(CAPTURE_0_INST);
 
    /* 3) 初始化同步 & 事件标志 */
    gSynced        = false;
    gCheckCaptures = false;

    /* 4) 单步调试时立即 halt，防止计数不同步 */
    DL_TimerG_setCoreHaltBehavior(
        CAPTURE_0_INST, DL_TIMER_CORE_HALT_IMMEDIATE);

    /* 5) 使能 TimerG0 Capture 中断，并启动计数 */
    NVIC_EnableIRQ(CAPTURE_0_INST_INT_IRQN);
}

/**
 * @brief  阻塞等待一次新周期捕获完成，并返回周期（ticks）
 */
uint32_t GET_FREQ(void)
{
    /* 清除旧事件，等待下次 CC1 捕获 */
    gCheckCaptures = false;
    DL_TimerG_startCounter(CAPTURE_0_INST);
    while (!gCheckCaptures) {
        __WFE();  /* 低功耗等待，直到中断设置 gCheckCaptures */
    }
    
    /* 重新清标志，准备下一次测量 */
    gCheckCaptures = false;
    
    /* 返回频率（计数刻度差） */
    uint32_t freq = 200000 / (gLoadValue - gCaptureCnt);
    return freq;
} 

/**
 * @brief  TimerG0 Capture 中断服务函数
 * @note   在 SysConfig 中保持此名字不变，或修改 NVIC 对应映射
 */
void CAPTURE_0_INST_IRQHandler(void)
{
    uint32_t pend = DL_TimerG_getPendingInterrupt(CAPTURE_0_INST);

    switch (pend) {
        case DL_TIMERG_IIDX_CC1_DN:
            if (gSynced) {
                /* 已同步，第二次下降沿捕获到周期点 */
                gCaptureCnt   = DL_TimerG_getCaptureCompareValue(
                                    CAPTURE_0_INST, DL_TIMER_CC_1_INDEX);
                gCheckCaptures = true;
                DL_TimerG_startCounter(CAPTURE_0_INST);
            }
            else {
                /* 第一次下降沿，用于与计数器同步 */
                gSynced = true;
            }
            /* 手动装载计数器，规避组合捕获向下计数的 errata */
            DL_TimerG_setTimerCount(CAPTURE_0_INST, gLoadValue);
            break;

        case DL_TIMERG_IIDX_ZERO:
            /* 若计数到 0，则信号丢失，需要重新同步 */
            gSynced = false;
            break;

        default:
            break;
    }
    /* 若需要可调用 DL_TimerG_clearInterrupt() 清 pending 标志 */
}
