#include <math.h>
#include "fft.h"
#include<stdint.h>
#include"BASE.h"
#include"UART.h"
#include "DSPLib.h"

//有关采样和处理过的数据的定义
extern int16_t adcbuff[128];
extern int32_t* adcbuff2;


//const _q15 window[128] ={2911,2962,3050,3175,3337,3535,3769,4038,4342,4680,5051,5454,5888,6352,6845,7366,
//7913,8485,9080,9697,10334,10990,11663,12351,13053,13767,14491,15223,15962,16706,17453,18201,
//18948,19692,20431,21164,21889,22604,23307,23996,24670,25327,25965,26583,27179,27752,28300,28822,
//29317,29783,30219,30624,30997,31337,31643,31914,32150,32350,32514,32641,32731,32767,32767,32767,
//32721,32626,32494,32325,32120,31879,31603,31293,30949,30572,30163,29723,29253,28754,28228,27676,
//27099,26499,25877,25235,24574,23896,23203,22497,21779,21051,20315,19573,18827,18079,17330,16582,
//15837,15097,14364,13640,12927,12226,11539,10868,10214,9579,8965,8373,7805,7262,6745,6256,
//5796,5366,4967,4600,4266,3966,3701,3471,3277,3119,2998,2914,2867,2857,2884,2948};


void fft()
{

msp_mpy_q15_params mpyParams;
msp_fft_q15_params fftParams;

/* Multiply input signal by generated Hamming window */
mpyParams.length = 128;
//msp_mpy_q15(&mpyParams, adcbuff, window, adcbuff);

/* Initialize the fft parameter structure. */
fftParams.length = 128;
fftParams.bitReverse = 1;
fftParams.twiddleTable = msp_cmplx_twiddle_table_128_q15;

/* Perform real FFT with fixed scaling */
MAP_msp_fft_fixed_q15(&fftParams, adcbuff);
}



void Modulo()
{
    int i;
    for(i=0;i<128;i+=2)
    {
        int32_t t = (int32_t)adcbuff[i]*(int32_t)adcbuff[i];
        t += (int32_t)adcbuff[i+1]*(int32_t)adcbuff[i+1];
//        if(t<=4)
//        {
//            t *= 0.5;
//        }
        adcbuff2[i/2] = t;
    }
}





