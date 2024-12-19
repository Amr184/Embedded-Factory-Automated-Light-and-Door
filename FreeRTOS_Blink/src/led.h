#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"  // Include Pico's standard library

// Function prototypes for LED control
void LED_Init(uint32_t gpio_pin);
void LED_On(uint32_t gpio_pin);
void LED_Off(uint32_t gpio_pin);
void LED_Toggle(uint32_t gpio_pin);

#endif // LED_H
