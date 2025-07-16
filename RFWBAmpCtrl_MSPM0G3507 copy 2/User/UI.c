#include "UI.h"

UIPage_t UIPage = PAGE_INFO;
BTNData_t BTNData = {0};
int GainSetPos = 0; // 增益设定位置(0:小数点后1位; 1:个位; 2:十位)

void UI_init(void) {
    UART2_printf("page info\xFF\xFF\xFF");
}

void UI_taskShow(void) {
}

void UI_taskBTN(void) {
}

void UI_taskENC(void) {
}
