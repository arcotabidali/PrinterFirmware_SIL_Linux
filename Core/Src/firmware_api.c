
#include "firmware.h"
#include "system_state.h"
#include "paperfeed.h"
#include "heater_control.h"
#include <stdio.h>

/* Print a message when the shared object is loaded via dlopen/CDLL. */
__attribute__((constructor))
static void lib_init(void) {
    /* Keep this lightweight: do not call heavy initialization here because
       tests call firmware_init() explicitly. */
    printf("[SIL] Starting firmware in host mode (Linux) ...\n");
}

/* Print a message when the shared object is unloaded (dlclose / process exit). */
__attribute__((destructor))
static void lib_fini(void) {
    /* Keep this lightweight and avoid calling firmware_shutdown() here to
       prevent double-shutdown when tests call firmware_shutdown() themselves. */
    printf("[SIL] Shutting down firmware (shared object unload) ...\n");
}

void firmware_init(void) {
    system_state_init();
    paperfeed_init();
    heater_init();
    g_fw_state = FW_STATE_READY;
}

void firmware_step(void) {
    system_state_tick();
    paperfeed_tick();
    heater_tick();
}

void firmware_shutdown(void) {
    /* no-op for demo */
}

/* Paper feed */
void firmware_cmd_paperfeed_start(double rpm_target) { paperfeed_start(rpm_target); }
void firmware_cmd_paperfeed_stop(void)               { paperfeed_stop();           }
double firmware_get_motor_rpm(void)                  { return paperfeed_get_rpm(); }
void firmware_set_motor_load(double load_torque)     { paperfeed_set_load(load_torque); }

/* Heater */
void firmware_cmd_heater_setpoint(double temp_c) { heater_set_setpoint(temp_c); }
double firmware_get_heater_temp(void)            { return heater_get_temp();    }
void firmware_set_ambient_temp(double temp_c)    { heater_set_ambient(temp_c);  }

/* Faults / states (trivial in demo) */
int firmware_get_fault_code(void) { return g_fault_code; }
int firmware_get_ready(void)      { return g_fw_state == FW_STATE_READY ? 1 : 0; }
