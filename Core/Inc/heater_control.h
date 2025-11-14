
#ifndef HEATER_CONTROL_H
#define HEATER_CONTROL_H

void heater_init(void);
void heater_tick(void);
void heater_set_setpoint(double t_c);
double heater_get_temp(void);
void heater_set_ambient(double t_c);

#endif /* HEATER_CONTROL_H */
