
#ifndef FIRMWARE_H
#define FIRMWARE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Lifecycle */
void firmware_init(void);
void firmware_step(void);
void firmware_shutdown(void);

/* Paper feed (motor) */
void firmware_cmd_paperfeed_start(double rpm_target);
void firmware_cmd_paperfeed_stop(void);
double firmware_get_motor_rpm(void);
void firmware_set_motor_load(double load_torque);

/* Heater (printhead/ink system) */
void firmware_cmd_heater_setpoint(double temp_c);
double firmware_get_heater_temp(void);
void firmware_set_ambient_temp(double temp_c);

/* Faults / states */
int  firmware_get_fault_code(void); /* 0 = OK */
int  firmware_get_ready(void);      /* 1 = ready */

#ifdef __cplusplus
}
#endif

#endif /* FIRMWARE_H */
