#ifndef __RGB_LED_H__
#define __RGB_LED_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"

void HSV2RGB(uint16_t h, uint16_t s, uint16_t v, uint8_t* r, uint8_t* g, uint8_t* b);
void RGBLED_setColor(uint8_t r, uint8_t g, uint8_t b);
void RGBLED_taskRainbow(void);

#endif /* #ifndef __RGB_LED_H__ */
