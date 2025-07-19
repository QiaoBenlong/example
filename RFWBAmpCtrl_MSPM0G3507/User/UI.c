#include "UI.h"

UIPage_t UIPage = PAGE_INFO;
BTNData_t BTNData = {0};
int GainSetPos = 0; // 增益设定位置(0:小数点后1位; 1:个位; 2:十位)

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
            UART2_printf("data.gain.txt=\"%.1fdB\"\xFF\xFF\xFF", GainSet);
            UART2_printf("data.power_in.txt=\"%.1fdBm\"\xFF\xFF\xFF", PowerIn);
            UART2_printf("data.power_out.txt=\"%.1fdBm\"\xFF\xFF\xFF", PowerOut);
            switch (GainSetPos) {
                case 0:
                    UART2_printf("data.pos.val=25\xFF\xFF\xFF");
                    break;
                case 1:
                    UART2_printf("data.pos.val=50\xFF\xFF\xFF");
                    break;
                case 2:
                    UART2_printf("data.pos.val=75\xFF\xFF\xFF");
                    break;
            }
            break;
    }
}

void UI_taskBTN(void) {
    BTN_getData(&BTNData);
    if (BTNData.left) {
        GainSetPos--;
        GainSetPos = CONSTRAIN_ABOVE(GainSetPos, 0);
    }
    if (BTNData.right) {
        GainSetPos++;
        GainSetPos = CONSTRAIN_BELOW(GainSetPos, 2);
    }
}

void UI_taskENC(void) {
    switch (GainSetPos) {
        case 0:
            GainSet += (float)ENC_getIncVal() / 10;
            GainSet = CONSTRAIN(GainSet, GAIN_SET_MIN, GAIN_SET_MAX);
            break;
        case 1:
            GainSet += (float)ENC_getIncVal();
            GainSet = CONSTRAIN(GainSet, GAIN_SET_MIN, GAIN_SET_MAX);
            break;
        case 2:
            GainSet += (float)ENC_getIncVal() * 10;
            GainSet = CONSTRAIN(GainSet, GAIN_SET_MIN, GAIN_SET_MAX);
            break;
    }
    if (ENC_getSW()) {
        GainSet = 20.0F;
    }
}
