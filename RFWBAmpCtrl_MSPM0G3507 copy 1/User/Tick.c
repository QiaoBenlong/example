#include "Tick.h"

volatile uint32_t Tick = 0;

// SysTick中断(1ms)
void SysTick_Handler(void) {
    Tick++;
    UITick++;
    RGBLEDTick++;
    UARTTick++;
    SweepTick++;

    if (UIInfoTick) UIInfoTick--;

    // 按键消抖倒计时
    if (!ENC_SW_PRESS && ENCSWTick) ENCSWTick--;
    if (!BTN_LEFT_PRESS && BTNTick.left) BTNTick.left--;
    if (!BTN_DOWN_PRESS && BTNTick.down) BTNTick.down--;
    if (!BTN_RIGHT_PRESS && BTNTick.right) BTNTick.right--;
    if (!BTN_UP_PRESS && BTNTick.up) BTNTick.up--;
    if (!BTN_MID_PRESS && BTNTick.mid) BTNTick.mid--;
}
/**
 * @brief 延时(使用SysTick中断计时)
 * @param t 延时时间(ms)
*/
void Tick_delay(uint32_t t) {
    uint32_t tEnd = Tick + t;
    while (Tick < tEnd);
}