#include "ldr_sensor.h"
#include "hardware/adc.h"

void LDR_Init(uint adc_pin) {
    adc_init();                // Initialize the ADC module
    adc_gpio_init(adc_pin);    // Initialize the specified GPIO pin for ADC
}

uint16_t LDR_Read(uint adc_pin) {
    // Select the ADC input channel based on the pin
    adc_select_input(adc_pin - 26); // ADC pins start at GPIO 26
    
    // Read and return the ADC value (12-bit resolution: 0-4095)
    return adc_read();
}
