#include "infrared_sensor.h"

// Initialize the infrared sensor GPIO pin
void infrared_sensor_init(uint gpio_pin) {
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_IN); // Set GPIO as input
    gpio_pull_up(gpio_pin);         // Enable pull-up resistor (optional for stability)
}

// Read the state of the infrared sensor
bool infrared_sensor_read(uint gpio_pin) {
    return gpio_get(gpio_pin); // Returns true if HIGH, false if LOW
}