#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include "pico/stdlib.h"

// Function declarations
void infrared_sensor_init(uint gpio_pin);
bool infrared_sensor_read(uint gpio_pin);

#endif // INFRARED_SENSOR_H