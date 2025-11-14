
#include <stdio.h>
#include <stdint.h>

void HAL_Delay(uint32_t ms) { (void)ms; }
void HAL_GPIO_WritePin(void* port, uint16_t pin, uint32_t val) { (void)port; (void)pin; (void)val; }
uint32_t HAL_GPIO_ReadPin(void* port, uint16_t pin) { (void)port; (void)pin; return 1; }
