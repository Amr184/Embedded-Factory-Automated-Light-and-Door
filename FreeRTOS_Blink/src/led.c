#include "led.h"
#include "pico/stdlib.h"

// Initialize the LED
void LED_Init(uint32_t gpio_pin) {
    gpio_init(gpio_pin);             // Initialize the GPIO pin
    gpio_set_dir(gpio_pin, GPIO_OUT); // Set it as an output pin
}

// Turn the LED ON
void LED_On(uint32_t gpio_pin) {
    gpio_put(gpio_pin, 1); // Set GPIO pin HIGH
}

// Turn the LED OFF
void LED_Off(uint32_t gpio_pin) {
    gpio_put(gpio_pin, 0); // Set GPIO pin LOW
}

// Toggle the LED state
void LED_Toggle(uint32_t gpio_pin) {
    gpio_put(gpio_pin, !gpio_get(gpio_pin)); // Invert current state
}
    