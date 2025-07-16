#include "adc.h"

volatile bool gCheckADC;
uint16_t gADCSamples[ADC_SAMPLE_SIZE];

void adc_init(void)
{
    /* Configure DMA source, destination and size */
    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,
        (uint32_t) DL_ADC12_getFIFOAddress(ADC12_0_INST));

    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &gADCSamples[0]);
    DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, ADC_FIFO_SAMPLES);

    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);

    /* Setup interrupts on device */
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);

    gCheckADC = false;
}

void start_adc(void)
{
    DL_ADC12_startConversion(ADC12_0_INST);

    while (false == gCheckADC) {
    }
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_DMA_DONE:
            gCheckADC = true;
            break;
        default:
            break;
    }
}
