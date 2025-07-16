/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "UserTask.h"
#include "arm_math.h"
#include "arm_const_structs.h"

/* Number of samples */
#define NUM_SAMPLES 1024
/* Global variables and defines for FFT */
#define IFFTFLAG 0
#define BITREVERSE 1

/* Expected Maximum amplitude and frequency index of FFT */
#define GOLDEN_FFT_MAX_FREQ_INDEX (5)

/* Array with FFT results */
volatile int16_t gFFTOutput[NUM_SAMPLES * 2];
/* Maximum amplitude of FFT */
volatile uint32_t gFFTmaxValue;
/* Index of maximum frequency */
volatile uint32_t gFFTmaxFreqIndex;

int main(void)
{
    SYSCFG_DL_init();

    UserTask_init();

    start_adc();

    arm_cfft_q15(
        &arm_cfft_sR_q15_len1024, (q15_t *) gADCSamples, IFFTFLAG, BITREVERSE);
    arm_cmplx_mag_q15((q15_t *) gADCSamples, (q15_t *) gFFTOutput, NUM_SAMPLES);
    arm_max_q15((q15_t *) gFFTOutput, NUM_SAMPLES, (q15_t *) &gFFTmaxValue,
        (uint32_t *) &gFFTmaxFreqIndex);

    while (1) {
        UserTask_loop();
    }
}

