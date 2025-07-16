#include "UI.h"

UIPage_t UIPage = PAGE_INFO;
// BTNData_t BTNData = {0};
// int GainSetPos = 0; // 增益设定位置(0:小数点后1位; 1:个位; 2:十位)

// void UI_init(void) {
//     UART2_printf("page info\xFF\xFF\xFF");
// }

// void UI_taskShow(void) {
// }

// void UI_taskBTN(void) {
// }

// void UI_taskENC(void) {
// }



/*trans*/
// volatile uint16_t UITick = 0;
const char* load_type_str[] = { "Open", "Res", "Cap" };

void UI_init(void) {
    UART2_printf("page info\xFF\xFF\xFF");
}

void UI_taskShow(void) {
    static UIPage_t lastPage = PAGE_INFO;
    if (lastPage != UIPage) {
        lastPage = UIPage;

        switch (UIPage) {
            case PAGE_INFO:
                UART2_printf("page data\xFF\xFF\xFF");
                UART2_printf("data.t5.txt=\"XXXX\"\xFF\xFF\xFF");
                break;
            case PAGE_DATA:
                UART2_printf("page data\xFF\xFF\xFF");
                break;
        }
    }
    switch (UIPage) {
        case PAGE_INFO:
            switch (corrent_operating) {
                case initial:
                    UART2_printf("data.t4.txt=\"正在检测\"\xFF\xFF\xFF");
                    UART2_printf("data.t5.txt=\"XXXX\"\xFF\xFF\xFF");
                    UART2_printf("data.t6.txt=\"开路\"\xFF\xFF\xFF");
                    UART2_printf("data.t7.txt=\"开路\"\xFF\xFF\xFF");
                    break;
                case waiting_length:
                    UART2_printf("data.t4.txt=\"正在检测\"\xFF\xFF\xFF");
                    break;
                case waiting_load:
                    UART2_printf("data.t4.txt=\"正在检测\"\xFF\xFF\xFF");
                    break;
                case finish:
                    UART2_printf("data.t4.txt=\"结果保持\"\xFF\xFF\xFF");
                    UART2_printf("data.t5.txt=\"%d\"\xFF\xFF\xFF", length0);
                    // UART2_printf("data.t6.txt=\"%s\"\xFF\xFF\xFF", load_type_str[loaded]);
                    // UART2_printf("data.t7.txt=\"%.1f\"\xFF\xFF\xFF", load);
                    break;
            }
        case PAGE_DATA:
            break;
    }
}

void UI()
{
    
    UART2_printf("info.t5.txt=\"%d\"\xff\xff\xff",length0);
}


//DL_UART_Main_transmitData(UART2_INST, length0);