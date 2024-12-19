#include "buzzer.h"
#include "pico/stdlib.h"

// Initialize the buzzer
void Buzzer_Init(uint8_t buzzer_pin) {
    gpio_init(buzzer_pin);
    gpio_set_dir(buzzer_pin, GPIO_OUT);
    gpio_put(buzzer_pin, 0); // Ensure the buzzer is off initially
}

// Turn the buzzer on
void Buzzer_On(uint8_t buzzer_pin) {
    gpio_put(buzzer_pin, 1);
}

// Turn the buzzer off
void Buzzer_Off(uint8_t buzzer_pin) {
    gpio_put(buzzer_pin, 0);
}

// Beep the buzzer for a specific duration (in milliseconds)
void Buzzer_Beep(uint8_t buzzer_pin, uint32_t duration_ms) {
    Buzzer_On(buzzer_pin);
    sleep_ms(duration_ms);
    Buzzer_Off(buzzer_pin);
}
