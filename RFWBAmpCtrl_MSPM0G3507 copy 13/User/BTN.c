#include "BTN.h"

BTNTick_t BTNTick = {0};

void BTN_getData(BTNData_t* data) {
    if (BTN_LEFT_PRESS && !BTNTick.left) {
        BTNTick.left = BTN_DEBOUNCE_TIME;
        data->left = 1;
    }
    else {
        data->left = 0;
    }
    if (BTN_DOWN_PRESS && !BTNTick.down) {
        BTNTick.down = BTN_DEBOUNCE_TIME;
        data->down = 1;
    }
    else {
        data->down = 0;
    }
    if (BTN_RIGHT_PRESS && !BTNTick.right) {
        BTNTick.right = BTN_DEBOUNCE_TIME;
        data->right = 1;
    }
    else {
        data->right = 0;
    }
    if (BTN_UP_PRESS && !BTNTick.up) {
        BTNTick.up = BTN_DEBOUNCE_TIME;
        data->up = 1;
    }
    else {
        data->up = 0;
    }
    if (BTN_MID_PRESS && !BTNTick.mid) {
        BTNTick.mid = BTN_DEBOUNCE_TIME;
        data->mid = 1;
    }
    else {
        data->mid = 0;
    }
}
