#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "pico/stdlib.h"

// Function prototypes
void ultrasonic_init(uint trig_pin, uint echo_pin);
float ultrasonic_measure_distance(uint trig_pin, uint echo_pin);

#endif // ULTRASONIC_SENSOR_H
