#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "ti_msp_dl_config.h"

#define ADC_SAMPLE_SIZE (1024)
/* When FIFO is enabled 2 samples are compacted in a single word */
#define ADC_FIFO_SAMPLES (ADC_SAMPLE_SIZE >> 1)

extern uint16_t gADCSamples[ADC_SAMPLE_SIZE];

void adc_init(void);
void start_adc(void);

#endif /* ADC_H_ */
