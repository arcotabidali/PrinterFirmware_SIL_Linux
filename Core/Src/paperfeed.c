
#include "paperfeed.h"
#include <stdio.h>

static double g_rpm = 0.0;
static double g_target_rpm = 0.0;
static double g_load = 0.0; /* arbitrary torque units */

void paperfeed_init(void) {
    g_rpm = 0.0;
    g_target_rpm = 0.0;
    g_load = 0.0;
}

void paperfeed_start(double rpm_target) {
    g_target_rpm = rpm_target;
    printf("[PF] start target=%.1f rpm\n", g_target_rpm);
}

void paperfeed_stop(void) {
    g_target_rpm = 0.0;
    printf("[PF] stop\n");
}

void paperfeed_set_load(double load_torque) {
    g_load = load_torque;
}

void paperfeed_tick(void) {
    double err = g_target_rpm - g_rpm;
    double ctrl = 0.15 * err;
    g_rpm += ctrl - 0.02 * g_load;
    if (g_rpm < 0) g_rpm = 0;
}

double paperfeed_get_rpm(void) {
    return g_rpm;
}
