
#include <stdint.h>
static uint32_t g_tick = 0;
uint32_t HAL_GetTick(void) { g_tick += 10; return g_tick; } /* ~10 ms per call */
