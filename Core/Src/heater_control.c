
#include "heater_control.h"
#include <stdio.h>

static double g_temp = 25.0;
static double g_ambient = 25.0;
static double g_setpoint = 40.0;

void heater_init(void) {
    g_temp = 25.0;
    g_ambient = 25.0;
    g_setpoint = 40.0;
}

void heater_set_setpoint(double t_c) {
    g_setpoint = t_c;
    printf("[HTR] setpoint=%.1f C\n", g_setpoint);
}

void heater_set_ambient(double t_c) {
    g_ambient = t_c;
}

void heater_tick(void) {
    double err = g_setpoint - g_temp;
    /* make the heater a bit more aggressive so the SIL model reaches test setpoints */
    double heat = 0.3 * err;
    double cool = 0.05 * (g_temp - g_ambient);
    g_temp += heat - cool;
}

double heater_get_temp(void) {
    return g_temp;
}
