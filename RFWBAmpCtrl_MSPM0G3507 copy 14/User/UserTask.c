#include "UserTask.h"
#include <sys/cdefs.h>
#include "Encoder.h"
#include "math.h"
#define RESULT_SIZE (1024)
//test
// volatile uint16_t SweepTick = 0; //trans
volatile uint16_t UITick = 0;
volatile uint16_t UIInfoTick = UI_INFO_TIME; // INFO界面显示倒计时
volatile uint16_t RGBLEDTick = 0;
volatile uint16_t UARTTick = 0;
volatile float freq = 1E6F;
volatile uint16_t amp = 512;
BTNData_t BTNData = {0};
char sweep_number = 0;
int SWFlag = 0;                     //旋转编码器标志，用于判断是否按下
volatile uint16_t phase_ctrl = 0;
volatile uint16_t amp0 = 1023;
volatile uint16_t amp1 = 1023;
volatile int n = 0;
volatile int index_0 = 0;
volatile int index_1 = 0;
volatile int index_2 = 0;
volatile int index_max = 0;
volatile float threshold = 0;
volatile int index_min = 0;
volatile float length = 0;
volatile float length_raw = 0;
volatile float freq_min_raw = 0;
volatile int Short_flag = 0;        //判断该路是否短路的标志
volatile int DC_AC = 0;               //作为此时是交/直流的标志，D/A为0则为交流，为1则为直流
volatile int Short_flag1 = 0;
volatile int Short_flag2 = 0;
volatile int Short_flag3 = 0;
volatile int Short_flag4 = 0;
volatile float Volt3 = 0;
volatile float R_raw[50];
volatile float Vol_AC_raw[50];
volatile float Ris = 0;
volatile float sum_R = 0;
volatile float sum_AC = 0;
volatile float Vol_final = 0;
volatile float Reduction = 0;
volatile float amp_max = 0;
volatile uint16_t inADCVal, outADCVal =0;//初始ADC取值

/*******************DDS任务移植**********************/
DDS_SingleToneParam_t SingleTone[4] = {0};
DDS_SweepParam_t Sweep[3] = {0};

volatile int flag = 0;
volatile uint16_t SweepTick = 0;
volatile uint16_t TimeTick = 0;
volatile int toggle_flag = 0;   //翻转gpio的标志，用于控制继电器，从而判断类型
volatile float Volt1 = 0;
volatile float Volt2 = 0;
volatile float freq_record[512];
volatile int flag_i;
volatile int type_flag = 0;     //线缆类型的标志，不同类型用不同拟合数据测长度
volatile float smoothed_amp_length[RESULT_SIZE];
volatile int sweep_times = 0;
volatile int function_1_flag = 0;
volatile int index_1_short = 0;
volatile int index_2_short = 0;
volatile int index_min_short = 0;
volatile float length_short = 0;
volatile float length_short_raw = 0;

void UserTask_init(void) {
    initSingleToneParam();
    // initSweepParam();
    // UserADC_init();
    ENC_init();
    DDS_init();
    UART2_init();
    UserADC_init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
    for(int i = 0;i < 100;i++)
    {
        R_raw[i] = 0;
        Vol_AC_raw[i] = 0;
    }
    
    // UI_init();

    // DDS_singleTone(AD9959_CH0, &SingleTone[0]);
    // DDS_singleTone(AD9959_CH1, &SingleTone[1]);
    // DDS_singleTone(AD9959_CH2, &SingleTone[2]);
    // DDS_singleTone(AD9959_CH3, &SingleTone[3]);
    // DDS_update();

    // Tick_delay(3000);

    DDS_initSweep(AD9959_CH0, &Sweep[0]);
    DDS_initSweep(AD9959_CH1, &Sweep[1]);
    // DDS_initSweep(AD9959_CH3, &Sweep[2]);
    DDS_update();
}


/**************************************************UserTask_loop任务执行******************************************************/
void UserTask_loop(void) {
    // UserTask_BTN();
    // initSweepParam();
    // UserTask_ADC();
    UserTask_ADC1();
    // UserADC0_start();
    // inADCVal = UserADC0_getData(50);

    switch (flag)//flag:页面标志
    {



        /*双端测量*/

        case 0://测量线缆类型
            Shift_AC();
            Shift_12();
            if (UITick >= UI_TIME) 
            {
                UITick = 0;
                UI_taskShow2();
            }

            amp0 = 0;
            amp1 = 1023;
            freq = 4E6F;
            
            // UserTask_ENC();
            // BTN_getData(&BTNData);
            // if(BTNData.up)
            // {
            //     amp += 5;
            // }
            // if(BTNData.down)
            // {
            //     amp -= 5;
            // }
            if (toggle_flag == 0)
            {
                Volt1 = amp_measured;//按下前的电压
            }
            else if (toggle_flag == 1)
            {
                Volt2 = amp_measured;//按下后的电压               
            }
            

            initSingleToneParam();
            DDS_singleTone(AD9959_CH0, &SingleTone[0]);
            DDS_singleTone(AD9959_CH1, &SingleTone[1]);
            DDS_update();
            if(print_flag == 1)
            {
                Volt3 = Volt1;
                print_flag = 0;
                Shift_AC();   
                Shift_12();             
                DL_GPIO_setPins(GPIO_RELAY_PORT,GPIO_RELAY_relay1_PIN);
                toggle_flag = !toggle_flag; //toggle_flag为0时是按下前，为1是按下后
                UART2_printf("two.t6.txt=\"loading\"\xff\xff\xff");
                
                DL_TimerG_startCounter(TIMER_0_INST);
                

            }
            if(print_flag == 2)
            {
                TimeTick = 0;
                while(TimeTick <= 500)
                {
                    UserTask_ADC1();
                    UART2_printf("two.t13.txt=\"%.4f\"\xff\xff\xff",Volt1);
                    UART2_printf("two.t14.txt=\"%.4f\"\xff\xff\xff",Volt2);

                }
                TimeTick = 0;
                if((float)(Volt3/Volt2) >= 1.2)
                {
                    UART2_printf("two.t6.txt=\"SFTP\"\xff\xff\xff");
                    // type_flag = 1;                    
                }
                else 
                {
                    UART2_printf("two.t6.txt=\"UTP\"\xff\xff\xff");
                    // type_flag = 2; 
                }

                flag++;
                // Tick_delay(500);
            }

            break;
        case 1://判断线序
            if (UITick >= UI_TIME) 
            {
                UITick = 0;
                UI_taskShow2();
                // UART2_printf("two.t7.txt=\"%.4f\"\xff\xff\xff",R_raw);
            }
            Shift_DC();
            UserTask_ADC();
            DL_GPIO_clearPins(GPIO_RFC_PORT,GPIO_RFC_DOWN_A_PIN);
            DL_GPIO_clearPins(GPIO_RFC_PORT,GPIO_RFC_DOWN_B_PIN);
            DL_GPIO_clearPins(GPIO_RFC_PORT,GPIO_RFC_UP_B_PIN);
            DL_GPIO_setPins(GPIO_RFC_PORT,GPIO_RFC_UP_A_PIN);//给1通直流
            UserTask_ADC1();
            TimeTick = 0;
            while(TimeTick <= 500)
            {
                UserTask_ADC1();
                // UART2_printf("two.t13.txt=\"%.4f\"\xff\xff\xff",v1);
            }
            TimeTick = 0;
            if(v1 >= 3)
            {
                UART2_printf("two.t5.txt=\"直连\"\xff\xff\xff");
            }
            else 
            {
                UART2_printf("two.t5.txt=\"交叉\"\xff\xff\xff");
            }
            flag++;
            // DL_GPIO_setPins(GPIO_RELAY_PORT,GPIO_RELAY_relay3_PIN);
            // R_raw = (float) (51*(float)((3.3-Vol_R)/Vol_R));
            break;

        case 2://电阻测量
            // if (UITick >= UI_TIME) 
            // {
            //     UITick = 0;
            //     UART2_printf("two.t7.txt=\"%.4f\"\xff\xff\xff",Ris);
            // }
            UserTask_ADC();
            Shift_DC();
            // while(TimeTick <= 200)
            // {
            //     UserTask_ADC();
            // }
            // TimeTick = 0;
            // DL_GPIO_setPins(GPIO_RELAY_PORT,GPIO_RELAY_relay3_PIN);
            // while(TimeTick <= 2500)
            // {
            //     for(int i = 0; i < 50; i++)
            //     {
            //         UserTask_ADC();
            //         R_raw[i] = (float) (51*(float)((3.3-Vol_R)/Vol_R));
            //         sum_R += R_raw[i];
            //         UART2_printf("two.t7.txt=\"%.4f\"\xff\xff\xff",Ris);
            //     }
            //     Ris = (float)(0.9851*sum_R/50-0.8538);
            //     sum_R = 0;
            // }
            while(TimeTick <= 200)
            {
                UserTask_ADC();
            }
            TimeTick = 0;
            DL_GPIO_setPins(GPIO_RELAY_PORT,GPIO_RELAY_relay3_PIN);
            while(TimeTick <= 2500)
            {
                for(int i = 0; i < 50; i++)
                {
                    UserTask_ADC();
                    R_raw[i] = (float) (51*(float)((3.3-Vol_R)/Vol_R));
                    sum_R += R_raw[i];
                    
                }
                Ris = (float)(0.9851*sum_R/50-0.8538-0.13);
                sum_R = 0;
            }
            UART2_printf("two.t7.txt=\"%.4f\"\xff\xff\xff",Ris);
            TimeTick = 0;
            flag++;
            break;
        case 3://交流损耗测量
            
            Shift_AC();
            Shift_45();
            if (UITick >= UI_TIME) 
            {
                UserTask_ADC();
                UITick = 0;
                // UART2_printf("two.t9.txt=\"%.4f\"\xff\xff\xff",Vol_AC);
            }

            amp0 = 800;
            amp1 = 800;
            freq = 30E6F;
            initSingleToneParam();
            DDS_singleTone(AD9959_CH0, &SingleTone[0]);
            DDS_singleTone(AD9959_CH1, &SingleTone[1]);
            DDS_update();
            TimeTick = 0;
            while(TimeTick <= 3000)
            {
                for(int i = 0; i < 100; i++)
                {
                    UserTask_ADC();
                    Vol_AC_raw[i] = Vol_AC;
                    sum_AC += Vol_AC_raw[i];
                }
                Vol_final = (float)(sum_AC/100);
                sum_AC = 0;
                 if(Vol_final >= 0.869)
                {
                    Reduction = (float)(-775.99*Vol_final*Vol_final + 1425.3*Vol_final - 654.36);
                }
                else if(Vol_final >= 0.405 && Vol_final < 0.869)
                {
                    Reduction = (float)(31.461*Vol_final - 28.615);
                }
                else if(Vol_final < 0.405)
                {
                    Reduction = (float)(-27813*Vol_final*Vol_final*Vol_final*Vol_final + 21020*Vol_final*Vol_final*Vol_final - 5644.9*Vol_final*Vol_final + 669.53*Vol_final - 55.748);                
                }

                    
            }
            TimeTick = 0;
           
            UART2_printf("two.t8.txt=\"%.2f\"\xff\xff\xff",Reduction);

            // flag++;
            break;

        case 4:
            // if (UITick >= UI_TIME) 
            // {
            //     UserTask_ADC();
            //     UITick = 0;
            //     UART2_printf("two.t9.txt=\"%.4f\"\xff\xff\xff",Vol_AC);
            // }

            flag++;

            break;

        /*单端测量*/

        /***************flag=5678,快速扫频4路，检测是否短路***********/
        case 5://扫12
            Short_flag1 = 0;
            Short_flag2 = 0;
            Short_flag3 = 0;
            Short_flag4 = 0;
            Shift_AC();
            Shift_12();
            if(DDS_start == 0)
            {
                Sweep[0].freq = 0;                      
                Sweep[0].amp = 0;
                Sweep[0].phase = 0;                     
                Sweep[0].start = 0;                      
                Sweep[0].step = 0;           
                Sweep[0].end = 0;   
                Sweep[1].freq = 0;                      
                Sweep[1].amp = 0;
                Sweep[1].phase = 0;                     
                Sweep[1].start = 0;                      
                Sweep[1].step = 0;           
                Sweep[1].end = 0;       
            }
            if (DDS_start == 1)
            {
                DDS_start = 2;
                initSweepParamLog();
                DDS_initSweep(AD9959_CH0, &Sweep[0]);
                DDS_initSweep(AD9959_CH1, &Sweep[1]);
            }
            if (SweepTick >= DDS_SWEEP_TIME)  //(uint8_t)((2000*freq_step)/(freq_end-freq_start))
            {                
                SweepTick = 0;
                // amp0 = 1023;
                    
                DDS_sweep(AD9959_CH0, &Sweep[0]);
                DDS_sweep(AD9959_CH1, &Sweep[1]);
                // DDS_sweep(AD9959_CH3, &Sweep[2]);
                DDS_update();
                sampleCnt = 5;
                while(sampleCnt--)
                {
                    UserTask_ADC();
                    sum += Vol_temp;
                }
                amp_length[Cnt] = (float)(sum/5);
                sum = 0;
                Cnt++;
                if(Cnt >= RESULT_SIZE)
                {
                    Cnt = 0;
                }
                if (end_flag == 1)
                {
                    sweep_times++;
                    // get_length();
                    smooth_amp_length(amp_length, smoothed_amp_length, RESULT_SIZE);
                    for( n = 0; n < RESULT_SIZE; n++ )
                    {
                        amp_length[n] = 0;
                    }
                    end_flag = 0;
                    Cnt = 0;
                }
                if(sweep_times == 2)
                {
                    // DDS_start = 0;
                    DDS_initSweep(AD9959_CH0, &Sweep[0]);
                    DDS_initSweep(AD9959_CH1, &Sweep[1]);
                    // UART2_printf("one.t4.txt=\"%.2f\"\xff\xff\xff",length);
                    sweep_times = 0;
                    if(smoothed_amp_length[5] < 2.4)
                    {
                        Short_flag1 = 1;
                        UART2_printf("one.t5.txt=\"1/2线短路\"\xff\xff\xff");
                    }
                    flag++;
                }
                

                    
            }


            break;

        case 6://扫36
            Shift_AC();
            Shift_36();
            if (DDS_start == 2)
            {
                DDS_start = 3;
                initSweepParamLog();
                DDS_initSweep(AD9959_CH0, &Sweep[0]);
                DDS_initSweep(AD9959_CH1, &Sweep[1]);
            }
            if (SweepTick >= DDS_SWEEP_TIME)  //(uint8_t)((2000*freq_step)/(freq_end-freq_start))
            {                
                SweepTick = 0;
                // amp0 = 1023;
                    
                DDS_sweep(AD9959_CH0, &Sweep[0]);
                DDS_sweep(AD9959_CH1, &Sweep[1]);
                // DDS_sweep(AD9959_CH3, &Sweep[2]);
                DDS_update();
                sampleCnt = 5;
                while(sampleCnt--)
                {
                    UserTask_ADC();
                    sum += Vol_temp;
                }
                amp_length[Cnt] = (float)(sum/5);
                sum = 0;
                Cnt++;
                if(Cnt >= RESULT_SIZE)
                {
                    Cnt = 0;
                }
                if (end_flag == 1)
                {
                    sweep_times++;
                    // get_length();
                    smooth_amp_length(amp_length, smoothed_amp_length, RESULT_SIZE);
                    for( n = 0; n < RESULT_SIZE; n++ )
                    {
                        amp_length[n] = 0;
                    }
                    end_flag = 0;
                    Cnt = 0;
                }
                if(sweep_times == 2)
                {
                    // DDS_start = 0;
                    DDS_initSweep(AD9959_CH0, &Sweep[0]);
                    DDS_initSweep(AD9959_CH1, &Sweep[1]);
                    // UART2_printf("one.t4.txt=\"%.2f\"\xff\xff\xff",length);
                    sweep_times = 0;
                    if(smoothed_amp_length[5] < 2.4)
                    {
                        Short_flag2 = 1;
                        UART2_printf("one.t5.txt=\"3/6线短路\"\xff\xff\xff");
                    }
                    flag++;
                }
                

                    
            }
            break;

        case 7://扫45
            Shift_AC();
            Shift_45();
            if (DDS_start == 3)
            {
                DDS_start = 4;
                /**************扫频参数写入*************/
                initSweepParamLog();
                DDS_initSweep(AD9959_CH0, &Sweep[0]);
                DDS_initSweep(AD9959_CH1, &Sweep[1]);
            }
            if (SweepTick >= DDS_SWEEP_TIME)  //(uint8_t)((2000*freq_step)/(freq_end-freq_start))
            {                
                SweepTick = 0;
                // amp0 = 1023;
                    
                DDS_sweep(AD9959_CH0, &Sweep[0]);
                DDS_sweep(AD9959_CH1, &Sweep[1]);
                // DDS_sweep(AD9959_CH3, &Sweep[2]);
                DDS_update();

                /*******数据写入数组并处理********/
                sampleCnt = 5;
                while(sampleCnt--)
                {
                    UserTask_ADC();
                    sum += Vol_temp;
                }
                amp_length[Cnt] = (float)(sum/5);
                sum = 0;
                Cnt++;
                if(Cnt >= RESULT_SIZE)
                {
                    Cnt = 0;
                }
                if (end_flag == 1)
                {
                    sweep_times++;
                    // get_length();
                    smooth_amp_length(amp_length, smoothed_amp_length, RESULT_SIZE);
                    for( n = 0; n < RESULT_SIZE; n++ )
                    {
                        amp_length[n] = 0;
                    }
                    end_flag = 0;
                    Cnt = 0;
                }
                if(sweep_times == 2)
                {
                    // DDS_start = 0;
                    DDS_initSweep(AD9959_CH0, &Sweep[0]);
                    DDS_initSweep(AD9959_CH1, &Sweep[1]);
                    // UART2_printf("one.t4.txt=\"%.2f\"\xff\xff\xff",length);
                    sweep_times = 0;
                    if(smoothed_amp_length[5] < 2.4)
                    {
                        Short_flag3 = 1;
                        UART2_printf("one.t5.txt=\"4/5线短路\"\xff\xff\xff");
                    }
                    flag++;
                }
                

                    
            }
            break;
        case 8://扫78
            Shift_AC();
            Shift_87();
            if (DDS_start == 4)
            {
                DDS_start = 5;
                /*************扫频参数写入*************/
                initSweepParamLog();
                DDS_initSweep(AD9959_CH0, &Sweep[0]);
                DDS_initSweep(AD9959_CH1, &Sweep[1]);
            }
            if (SweepTick >= DDS_SWEEP_TIME)  //(uint8_t)((2000*freq_step)/(freq_end-freq_start))
            {                
                SweepTick = 0;
                // amp0 = 1023;
                DDS_sweep(AD9959_CH0, &Sweep[0]);
                DDS_sweep(AD9959_CH1, &Sweep[1]);
                // DDS_sweep(AD9959_CH3, &Sweep[2]);
                DDS_update();
                sampleCnt = 5;
                while(sampleCnt--)
                {
                    UserTask_ADC();
                    sum += Vol_temp;
                }
                amp_length[Cnt] = (float)(sum/5);
                sum = 0;
                Cnt++;
                if(Cnt >= RESULT_SIZE)
                {
                    Cnt = 0;
                }
                if (end_flag == 1)
                {
                    sweep_times++;
                    // get_length();
                    smooth_amp_length(amp_length, smoothed_amp_length, RESULT_SIZE);
                    for( n = 0; n < RESULT_SIZE; n++ )
                    {
                        amp_length[n] = 0;
                    }
                    end_flag = 0;
                    Cnt = 0;
                }
                if(sweep_times == 2)
                {
                    // DDS_start = 0;
                    DDS_initSweep(AD9959_CH0, &Sweep[0]);
                    DDS_initSweep(AD9959_CH1, &Sweep[1]);
                    // UART2_printf("one.t4.txt=\"%.2f\"\xff\xff\xff",length);
                    sweep_times = 0;
                    if(smoothed_amp_length[5] < 2.4)
                    {
                        Short_flag4 = 1;
                        UART2_printf("one.t5.txt=\"7/8线短路\"\xff\xff\xff");
                    }
                    if(Short_flag1 == 0 && Short_flag2 == 0 && Short_flag3 == 0 && Short_flag4 == 0)
                    {
                        UART2_printf("one.t5.txt=\"不存在短路\"\xff\xff\xff");
                    }
                    flag = 111;
                }                                    
            }
            break;

            /*判断完短路之后不立即测量短路长度*/

        case 9:
            //开始测量短路长度
                // Shift_12();
                if(Short_flag1 ==1)
                {
                    Shift_12();
                }
                else if(Short_flag2 ==1)
                {
                    Shift_36();
                }
                else if(Short_flag3 ==1)
                {
                    Shift_45();
                }
                else if(Short_flag4 ==1)
                {
                    Shift_87();
                }
                else if(Short_flag1 == 0 && Short_flag2 == 0 && Short_flag3 == 0 && Short_flag4 == 0)
                {
                    UART2_printf("one.t6.txt=\"不存在短路\"\xff\xff\xff");
                    break;
                }
                Shift_AC();
                if(DDS_start == 20)
                {
                    DDS_start = 21;
                    initSweepParam();
                    DDS_initSweep(AD9959_CH0, &Sweep[0]);
                    DDS_initSweep(AD9959_CH1, &Sweep[1]);
                }


                // }
                if (SweepTick >= DDS_SWEEP_TIME)  //(uint8_t)((2000*freq_step)/(freq_end-freq_start))
                {                
                    SweepTick = 0;
                    DDS_sweep(AD9959_CH0, &Sweep[0]);
                    DDS_sweep(AD9959_CH1, &Sweep[1]);
                    // DDS_sweep(AD9959_CH3, &Sweep[2]);
                    DDS_update();

                    sampleCnt = 5;
                    while(sampleCnt--)
                    {
                        UserTask_ADC();
                        sum += Vol_temp;
                    }
                    amp_length[Cnt] = (float)(sum/5);
                    sum = 0;
                    Cnt++;
                    if(Cnt >= RESULT_SIZE)
                    {
                        Cnt = 0;
                    }
                    if (end_flag == 1)
                    {
                        sweep_times++;
                        get_length_short();
                        for( n = 0; n < RESULT_SIZE; n++ )
                        {
                            amp_length[n] = 0;
                        }
                        end_flag = 0;
                        Cnt = 0;
                    }
                    if(sweep_times == 3)
                    {
                        DDS_start = 0;
                        DDS_initSweep(AD9959_CH0, &Sweep[0]);
                        DDS_initSweep(AD9959_CH1, &Sweep[1]);
                        UART2_printf("one.t6.txt=\"%.2f\"\xff\xff\xff",length_short);
                        UART2_printf("one.t10.txt=\"%d\"\xff\xff\xff",index_min_short);
                        sweep_times = 0;
                        flag++;//flag = 10,空状态
                    }   
                }



            break;


/***************flag=4开路长度测量***************/
        case 11:
                Shift_12();
                Shift_AC();
                if(DDS_start == 9)
                {
                    DDS_start = 10;
                    initSweepParam();
                    DDS_initSweep(AD9959_CH0, &Sweep[0]);
                    DDS_initSweep(AD9959_CH1, &Sweep[1]);
                }


                // }
                if (SweepTick >= DDS_SWEEP_TIME)  //(uint8_t)((2000*freq_step)/(freq_end-freq_start))
                {                
                    SweepTick = 0;
                    // amp0 = 1023;
                    
                    DDS_sweep(AD9959_CH0, &Sweep[0]);
                    DDS_sweep(AD9959_CH1, &Sweep[1]);
                    // DDS_sweep(AD9959_CH3, &Sweep[2]);
                    DDS_update();


                    sampleCnt = 5;
                    while(sampleCnt--)
                    {
                        UserTask_ADC();
                        sum += Vol_temp;
                    }
                    amp_length[Cnt] = (float)(sum/5);
                    sum = 0;
                    Cnt++;
                    if(Cnt >= RESULT_SIZE)
                    {
                        Cnt = 0;
                    }
                    if (end_flag == 1)
                    {
                        sweep_times++;
                        get_length();
                        for( n = 0; n < RESULT_SIZE; n++ )
                        {
                            amp_length[n] = 0;
                        }
                        end_flag = 0;
                        Cnt = 0;
                    }
                    if(sweep_times == 3)
                    {
                        DDS_start = 0;
                        DDS_initSweep(AD9959_CH0, &Sweep[0]);
                        DDS_initSweep(AD9959_CH1, &Sweep[1]);
                        UART2_printf("one.t9.txt=\"%d\"\xff\xff\xff",index_min);
                        UART2_printf("one.t4.txt=\"%.2f\"\xff\xff\xff",length);

                        sweep_times = 0;
                        flag++;
                    }                   
                }//扫频测开路长度结束
            
            break;
        case 10:
            break;

        
        default:
            break;
    }

}

void initSingleToneParam(void) {
    // int i;
    // for (i = 0; i < 4; i++) {
    SingleTone[0].freq = freq;
    SingleTone[0].amp = amp0;  // 幅度最大(1023)
    // }
    SingleTone[1].freq = freq;
    SingleTone[1].amp = amp1;  // 幅度最大(1023)
    SingleTone[0].phase = 0x0000; // 相位0度(0)
    SingleTone[1].phase = 0x2000; // 相位180度(8192)
    SingleTone[2].phase = 0x2000; // 相位180度(8192)
    SingleTone[3].phase = 0x3000; // 相位270度(12288)
}

void initSweepParamLog()
{
     //100kHz ~ 50MHz 对数扫频
    Sweep[0].freq = 1;                       // 频率1Hz
    Sweep[0].amp = 1023;                     // 幅度最大(1023)
    Sweep[0].phase = 0;                      // 相位0度(0)
    Sweep[0].start = 1E5F;                      // 起始频率100kHz
    Sweep[0].step = 1.006931669F;            // 步进系数(1000次根号1000)
    Sweep[0].end = 4E6F;                     // 终止频率100MHz
    Sweep[0].type = DDS_SWEEP_FREQ;          // 扫频
    Sweep[0].method = DDS_SWEEP_LOGARITHMIC; // 对数扫描

                    // 100kHz ~ 50MHz 对数扫频
    Sweep[1].freq = 1;                       // 频率1Hz
    Sweep[1].amp = 1023;                     // 幅度最大(1023)
    Sweep[1].phase = 8192;                      // 相位0度(0)
    Sweep[1].start = 1E5F;                      // 起始频率100kHz
    // Sweep[1].step = 1.013911386F;            // 步进系数(1000次根号1000000)
    Sweep[1].step = 1.006931669F;
    Sweep[1].end = 4E6F;                     // 终止频率100MHz
    Sweep[1].type = DDS_SWEEP_FREQ;          // 扫频
    Sweep[1].method = DDS_SWEEP_LOGARITHMIC; // 对数扫描   
}


void initSweepParam(void) {

            //原线性扫频


//    // CH0:1MHz ~ 40MHz 线性扫频   
//     Sweep[0].amp = 1023;                // 幅度最大(1023)
//     Sweep[0].phase = 0;                 // 相位0度(0)
//     Sweep[0].start = freq_start*1000000;   
//     // Sweep[0].start = 10E6F;          
//     Sweep[0].step = freq_step*1000;                // 步进频率100Hz
//     Sweep[0].end = freq_end*1000000;              // 终止频率100kHz
//     Sweep[0].type = DDS_SWEEP_FREQ;     // 扫频
//     Sweep[0].method = DDS_SWEEP_LINEAR; // 线性扫描



//     // CH1:1MHz ~ 40MHz 线性扫频   
//     Sweep[1].amp = 1023;                // 幅度最大(1023)
//     Sweep[1].phase = 8192;                 // 相位180度(8192)
//     Sweep[1].start = freq_start*1000000;              // 起始频率
//     Sweep[1].step = freq_step*1000;                // 步进频率
//     Sweep[1].end = freq_end*1000000;              // 终止频率100kHz
//     Sweep[1].type = DDS_SWEEP_FREQ;     // 扫频
//     Sweep[1].method = DDS_SWEEP_LINEAR; // 线性扫描


    
        // 100kHz ~ 1MHz 对数扫频
    Sweep[0].freq = 1;                       // 频率1Hz
    Sweep[0].amp = 1023;                     // 幅度最大(1023)
    Sweep[0].phase = 0;                      // 相位0度(0)
    Sweep[0].start = 1E5F;                      // 起始频率100kHz
    Sweep[0].step = 1.006931669F;            // 步进系数(1000次根号1000)
    Sweep[0].end = 100E6F;                     // 终止频率100MHz
    Sweep[0].type = DDS_SWEEP_FREQ;          // 扫频
    Sweep[0].method = DDS_SWEEP_LOGARITHMIC; // 对数扫描


        // 100kHz ~ 1MHz 对数扫频
    Sweep[1].freq = 1;                       // 频率1Hz
    Sweep[1].amp = 1023;                     // 幅度最大(1023)
    Sweep[1].phase = 8192;                      // 相位0度(0)
    Sweep[1].start = 1E5F;                      // 起始频率100kHz
    // Sweep[1].step = 1.013911386F;            // 步进系数(1000次根号1000000)
    Sweep[1].step = 1.006931669F;
    Sweep[1].end = 100E6F;                     // 终止频率100MHz
    Sweep[1].type = DDS_SWEEP_FREQ;          // 扫频
    Sweep[1].method = DDS_SWEEP_LOGARITHMIC; // 对数扫描



    // // 1kHz ~ 100kHz 线性扫频
    // Sweep[0].freq = 1E3F;               // 频率1kHz
    // Sweep[0].amp = 1023;                // 幅度最大(1023)
    // Sweep[0].phase = 0;                 // 相位0度(0)
    // Sweep[0].start = 1E3F;              // 起始频率1kHz
    // Sweep[0].step = 100;                // 步进频率100Hz
    // Sweep[0].end = 100E3F;              // 终止频率100kHz
    // Sweep[0].type = DDS_SWEEP_FREQ;     // 扫频
    // Sweep[0].method = DDS_SWEEP_LINEAR; // 线性扫描



    // 1 ~ 1000 线性扫幅
//     Sweep[2].freq = 1E3F;               // 频率1kHz
//     Sweep[2].amp = 1;                   // 幅度1
//     Sweep[2].phase = 0;                 // 相位0度(0)
//     Sweep[2].start = 1;                 // 起始幅度1
//     Sweep[2].step = 10;                  // 步进幅度10
//     Sweep[2].end = 1000;                // 终止幅度1000
//     Sweep[2].type = DDS_SWEEP_AMP;      // 扫幅
//     Sweep[2].method = DDS_SWEEP_LINEAR; // 线性扫描
}


void UserTask_BTN(void)
{
    BTN_getData(&BTNData);
    if(BTNData.left)
    {
        flag=0;
    }
    if(BTNData.right)
    {
        flag=1;
    }

}



void UserTask_ENC(void)
{
    
    // if (ENC_getSW() && SWFlag == 0) 
    // {
    //     SWFlag = 1;
    // }
    // else if (ENC_getSW() && SWFlag == 1 )
    // {
    //     SWFlag = 0;
    // }
    if (ENC_getSW())
    {
        SWFlag = !SWFlag;
    }


    switch (SWFlag)
    {
        case 0:
        if(flag == 0)
        {
            phase_ctrl += (uint16_t)(ENC_getIncVal() * 50);
        }
        else
        {
            freq += (float)ENC_getIncVal() * 1E6F;
        }
            
        break;
        case 1:
        if(flag == 0)
        {
            freq += (float)ENC_getIncVal() * 1E5F;
        }
        else
        {
            phase_ctrl += (uint16_t)(ENC_getIncVal() * 20);
        }
        break;
        default:
        break;

    }


}



// void get_length()
// {
//     if(type_flag == 2 || type_flag == 3 || type_flag == 1)
//     {
//         threshold = 0.9775*amp_length[20];
//     }
//     if(type_flag == 4)
//     {
//         threshold = 0.9965*amp_length[20];
//     }
//     for(index_0 = 3; index_0 < RESULT_SIZE-1; index_0++)
//     {
//         if(amp_length[index_0 - 1] > threshold && amp_length[index_0 + 1] < threshold)
//         {
//             index_1 = index_0;
//             break;
//         }
//     }
//     for(index_0 = 3; index_0 < RESULT_SIZE-1; index_0++)
//     {
//         if(amp_length[index_0 - 1] < threshold && amp_length[index_0 + 1] > threshold)
//         {
//             index_2 = index_0;
//             break;
//         }
//     }
//     for(index_0 = index_1, index_min = index_1; index_0 <= index_2; index_0++)
//     {
//         if(amp_length[index_min] > amp_length[index_0])
//         {
//             index_min = index_0;
//         }
//     }
//     length_raw = (float)(1050/index_min);
//     length = 0.0094*(length_raw*length_raw)+1.414*length_raw-0.9017;
//     if(type_flag == 1)
//     {
//         length = length - 0.46;
//     }
// }


// 修改平滑处理函数
void smooth_amp_length(float input[], float output[], int size) 
{
    // 边界处理
    output[0] = (input[0] + input[1]) / 2.0f;
    output[1] = (input[0] + input[1] + input[2]) / 3.0f;
    
    // 移动平均 (窗口=5)
    for (int i = 2; i < size - 2; i++) {
        output[i] = (input[i-2] + input[i-1] + input[i] + input[i+1] + input[i+2]) / 5.0f;
    }
    
    // 边界处理
    output[size-2] = (input[size-3] + input[size-2] + input[size-1]) / 3.0f;
    output[size-1] = (input[size-2] + input[size-1]) / 2.0f;
}

// 修改get_length函数
void get_length() {
    // 1. 进行平滑处理到新数组
    smooth_amp_length(amp_length, smoothed_amp_length, RESULT_SIZE);
    
    for(index_0 = 10; index_0 < RESULT_SIZE-1; index_0++)
    {
        if(smoothed_amp_length[index_0-1] > 0.94*smoothed_amp_length[5] && smoothed_amp_length[index_0+1] < 0.94*smoothed_amp_length[5])
        {
            index_1 = index_0;
            break;
        }
    }
    for(index_0 = index_1+10; index_0 < RESULT_SIZE-1; index_0++)
    {
        if(smoothed_amp_length[index_0-1] < 0.94*smoothed_amp_length[5] && smoothed_amp_length[index_0+1] > 0.94*smoothed_amp_length[5])
        {
            index_2 = index_0;
            break;
        }
    }
    for(index_0 = index_1, index_min = index_1; index_0 <= index_2; index_0++)
    {
        if(smoothed_amp_length[index_min] > smoothed_amp_length[index_0])
        {
            index_min = index_0;
        }
    
    }
    // freq_min_raw = powf(1000, (float)((index_min) / 2000.0)) * 100000; 
    length_raw = 0.6125*powf(1000,(float)(1-(float)((float)index_min/1000)));
    length = -0.0018*length_raw*length_raw+0.8598*length_raw-0.4267;
}


void get_length_short() {
    // 1. 进行平滑处理到新数组
    smooth_amp_length(amp_length, smoothed_amp_length, RESULT_SIZE);
    for(int i = 0; i < RESULT_SIZE; i++)
    {
        if(smoothed_amp_length[i]>amp_max)
        {
            amp_max = smoothed_amp_length[i];
            index_max = i;
        }
    }
    for(index_0 = 10; index_0 < RESULT_SIZE-1; index_0++)
    {
        if(smoothed_amp_length[index_0-1] > 0.9555* amp_max && smoothed_amp_length[index_0+1] < 0.9555* amp_max)
        {
            index_1_short = index_0;
            break;
        }
    }
    for(index_0 = index_1_short + 10; index_0 < RESULT_SIZE-1; index_0++)
    {
        if(smoothed_amp_length[index_0-1] < 0.9555* amp_max && smoothed_amp_length[index_0+1] > 0.9555* amp_max)
        {
            index_2_short = index_0;

            break;
        }
    }
    if(index_2_short < index_1_short)
    {
        index_2_short = 995;
    }
    for(index_0 = index_1_short, index_min_short = index_1_short; index_0 <= index_2_short; index_0++)
    {
        if(smoothed_amp_length[index_min_short] > smoothed_amp_length[index_0])
        {
            index_min_short = index_0;
        }
    
    }
    // freq_min_raw_short = powf(1000, (float)((index_min_short) / 1000.0)) * 100000; 
    length_short_raw = 0.6125*powf(1000,(float)(1-(float)((float)index_min_short/1000)));
    length_short = -0.0073*length_short_raw*length_short_raw+1.7843*length_short_raw-0.548;

}


void Shift_DC()
{
    DL_GPIO_clearPins(GPIO_RELAY_PORT,GPIO_RELAY_relay2_PIN);
    DC_AC = 1;
}



void Shift_AC()
{
    DL_GPIO_setPins(GPIO_RELAY_PORT,GPIO_RELAY_relay2_PIN);
    DC_AC = 0;
}


void Shift_12()
{
    DL_GPIO_setPins(GPIO_RFC_PORT , GPIO_RFC_UP_B_PIN);             //上片B高
    DL_GPIO_clearPins(GPIO_RFC_PORT , GPIO_RFC_UP_A_PIN);           //上片A低
    DL_GPIO_setPins(GPIO_RFC_PORT , GPIO_RFC_DOWN_B_PIN);           //下片B高
    DL_GPIO_clearPins(GPIO_RFC_PORT , GPIO_RFC_DOWN_A_PIN);         //下片A低
}


void Shift_36()
{
    DL_GPIO_setPins(GPIO_RFC_PORT , GPIO_RFC_UP_B_PIN);             //上片B高
    DL_GPIO_setPins(GPIO_RFC_PORT , GPIO_RFC_UP_A_PIN);             //上片A高
    DL_GPIO_setPins(GPIO_RFC_PORT , GPIO_RFC_DOWN_B_PIN);           //下片B高
    DL_GPIO_setPins(GPIO_RFC_PORT , GPIO_RFC_DOWN_A_PIN);           //下片A高
}


void Shift_45()
{
    DL_GPIO_clearPins(GPIO_RFC_PORT , GPIO_RFC_UP_B_PIN);           //上片B低
    DL_GPIO_clearPins(GPIO_RFC_PORT , GPIO_RFC_UP_A_PIN);           //上片A低
    DL_GPIO_clearPins(GPIO_RFC_PORT , GPIO_RFC_DOWN_B_PIN);         //下片B低
    DL_GPIO_clearPins(GPIO_RFC_PORT , GPIO_RFC_DOWN_A_PIN);         //下片A低
}


void Shift_87()
{
    DL_GPIO_clearPins(GPIO_RFC_PORT , GPIO_RFC_UP_B_PIN);           //上片B低
    DL_GPIO_setPins(GPIO_RFC_PORT , GPIO_RFC_UP_A_PIN);             //上片A高
    DL_GPIO_clearPins(GPIO_RFC_PORT , GPIO_RFC_DOWN_B_PIN);         //下片B低
    DL_GPIO_setPins(GPIO_RFC_PORT , GPIO_RFC_DOWN_A_PIN);           //下片A高
}


void length_measure_init(void)
{
    freq_start = 0;
    freq_end = 0;
    freq_step = 0;
    DDS_start = 1;
}


void TIMER_0_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO:
        
            DL_GPIO_clearPins(GPIO_RELAY_PORT,GPIO_RELAY_relay1_PIN);
            toggle_flag = !toggle_flag;
            print_flag = 2;

            break;
        default:
            break;
    }
}

void TIMER_1_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_1_INST)) {
        case DL_TIMER_IIDX_ZERO:
        
      

            break;
        default:
            break;
    }
}

