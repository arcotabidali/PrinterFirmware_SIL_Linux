
#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

typedef enum {
    FW_STATE_INIT = 0,
    FW_STATE_READY,
    FW_STATE_PRINTING,
    FW_STATE_FAULT
} fw_state_t;

extern fw_state_t g_fw_state;
extern int g_fault_code; /* 0=OK */

void system_state_init(void);
void system_state_tick(void);

#endif /* SYSTEM_STATE_H */
