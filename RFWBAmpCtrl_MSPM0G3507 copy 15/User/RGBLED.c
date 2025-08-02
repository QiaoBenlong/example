#include "RGBLED.h"

uint16_t ColorHue = 0, ColorSaturation = 100, ColorValue = 20;

/**
 * @brief 将HSV颜色空间转换为RGB颜色空间
 * @param h HSV颜色空间的H：色调。单位°，范围0-360。（Hue 调整颜色，0°-红色，120°-绿色，240°-蓝色，以此类推）
 * @param s HSV颜色空间的S：饱和度。单位%，范围0-100。（Saturation 饱和度高，颜色深而艳；饱和度低，颜色浅而发白）
 * @param v HSV颜色空间的V：明度。单位%，范围0-100。（Value 控制明暗，明度越高亮度越亮，越低亮度越低）
 * @param r RGB-R值的指针
 * @param g RGB-G值的指针
 * @param b RGB-B值的指针
 */
void HSV2RGB(uint16_t h, uint16_t s, uint16_t v, uint8_t* r, uint8_t* g, uint8_t* b) {
    h %= 360; // h -> [0,360]
    uint16_t rgbMax = v * 2.55F;
    uint16_t rgbMin = rgbMax * (100 - s) / 100.0F;

    uint16_t i = h / 60;
    uint16_t diff = h % 60;

    // RGB adjustment amount by hue
    uint16_t rgbAdj = (rgbMax - rgbMin) * diff / 60;

    switch (i) {
        case 0:
            *r = (uint8_t)rgbMax;
            *g = (uint8_t)(rgbMin + rgbAdj);
            *b = (uint8_t)rgbMin;
            break;
        case 1:
            *r = (uint8_t)(rgbMax - rgbAdj);
            *g = (uint8_t)rgbMax;
            *b = (uint8_t)rgbMin;
            break;
        case 2:
            *r = (uint8_t)rgbMin;
            *g = (uint8_t)rgbMax;
            *b = (uint8_t)(rgbMin + rgbAdj);
            break;
        case 3:
            *r = (uint8_t)rgbMin;
            *g = (uint8_t)(rgbMax - rgbAdj);
            *b = (uint8_t)rgbMax;
            break;
        case 4:
            *r = (uint8_t)(rgbMin + rgbAdj);
            *g = (uint8_t)rgbMin;
            *b = (uint8_t)rgbMax;
            break;
        default:
            *r = (uint8_t)rgbMax;
            *g = (uint8_t)rgbMin;
            *b = (uint8_t)(rgbMax - rgbAdj);
            break;
    }
}

void RGBLED_setColor(uint8_t r, uint8_t g, uint8_t b) {
    DL_TimerG_setCaptureCompareValue(PWM_LED_RG_INST, (uint32_t)r << 2, GPIO_PWM_LED_RG_C1_IDX);
    DL_TimerG_setCaptureCompareValue(PWM_LED_RG_INST, (uint32_t)g << 2, GPIO_PWM_LED_RG_C0_IDX);
    DL_TimerG_setCaptureCompareValue(PWM_LED_B_INST, (uint32_t)b << 2, GPIO_PWM_LED_B_C1_IDX);
}

void RGBLED_taskRainbow(void) {
    uint8_t r, g, b;
    HSV2RGB(ColorHue, ColorSaturation, ColorValue, &r, &g, &b);
    RGBLED_setColor(r, g, b);
    ColorHue++;
    if (ColorHue >= 360) ColorHue = 0;
}
