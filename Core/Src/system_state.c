
#include "system_state.h"
#include <stdio.h>

fw_state_t g_fw_state = FW_STATE_INIT;
int g_fault_code = 0;

void system_state_init(void) {
    g_fw_state = FW_STATE_INIT;
    g_fault_code = 0;
}

void system_state_tick(void) {
    switch (g_fw_state) {
        case FW_STATE_INIT:
            g_fw_state = FW_STATE_READY;
            break;
        case FW_STATE_READY:
        case FW_STATE_PRINTING:
        case FW_STATE_FAULT:
        default:
            break;
    }
}
