
#include "firmware.h"
#include <stdio.h>

int main(void)
{
#ifdef HOST_BUILD
    printf("[SIL] Starting firmware in host mode (Linux) ...\n");
#endif
    firmware_init();
    for (int i = 0; i < 50; ++i) {
        firmware_step();
    }
    firmware_shutdown();
    return 0;
}
