#include "UI.h"

UIPage_t UIPage = PAGE_DATA;
volatile uint16_t UITick = 0;

void UI_init(void) {
    UART2_printf("page info\xFF\xFF\xFF");
}

void UI_taskShow(void) {
    static UIPage_t lastPage = PAGE_INFO;
    if (lastPage != UIPage) {
        lastPage = UIPage;
        switch (UIPage) {
            case PAGE_INFO:
                UART2_printf("page info\xFF\xFF\xFF");
                break;
            case PAGE_DATA:
                UART2_printf("page data\xFF\xFF\xFF");
                break;
        }
    }
    switch (UIPage) {
        case PAGE_INFO:
            break;
        case PAGE_DATA:
            switch (enc_number) {
        case 0:
            UART2_printf("data.point_freq.txt=\"%.1fMHz\"\xFF\xFF\xFF",point_freq/1000000);
            break;
        case 1:
            UART2_printf("data.point_vpp.txt=\"%.1fmv\"\xFF\xFF\xFF",point_vpp/4);
            break;
        case 2:
            UART2_printf("data.star_freq.txt=\"%.1fMHz\"\xFF\xFF\xFF",sweep_freq_start/1000000);
            break;
        case 3:
            UART2_printf("data.cut_freq.txt=\"%.1fMHz\"\xFF\xFF\xFF",sweep_freq_cut/1000000);
            break;
        }
            switch (corrent_mode){
        case DDS_POINT:
            UART2_printf("data.t8.txt=\"点频模式\"\xFF\xFF\xFF");
            break;
        case DDS_SWEEP:
            UART2_printf("data.t8.txt=\"扫频模式\"\xFF\xFF\xFF");
            break;
        }
    break;
    }
}

