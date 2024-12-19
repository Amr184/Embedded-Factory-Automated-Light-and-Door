#ifndef LDR_SENSOR_H
#define LDR_SENSOR_H

#include "pico/stdlib.h"

// Initializes the LDR sensor on the specified ADC pin
void LDR_Init(uint adc_pin);

// Reads the analog value from the LDR sensor
uint16_t LDR_Read(uint adc_pin);

#endif // LDR_SENSOR_H
