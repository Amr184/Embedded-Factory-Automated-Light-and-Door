#include "ultrasonic_sensor.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

void ultrasonic_init(uint trig_pin, uint echo_pin) {
    // Initialize the trigger pin as output
    gpio_init(trig_pin);
    gpio_set_dir(trig_pin, GPIO_OUT);
    gpio_put(trig_pin, 0); // Set it LOW initially

    // Initialize the echo pin as input
    gpio_init(echo_pin);
    gpio_set_dir(echo_pin, GPIO_IN);
}

float ultrasonic_measure_distance(uint trig_pin, uint echo_pin) {
    // Send a 10us pulse on the trigger pin
    gpio_put(trig_pin, 1);
    sleep_us(10);
    gpio_put(trig_pin, 0);

    // Measure the pulse duration on the echo pin
    uint16_t pulse_start = 0;
    uint16_t pulse_end = 0;

    // Wait for the echo pin to go HIGH (pulse start)
    while (gpio_get(echo_pin) == 0) {
        pulse_start = time_us_64();
    }

    // Wait for the echo pin to go LOW (pulse end)
    while (gpio_get(echo_pin) == 1) {
        pulse_end = time_us_64();
    }

    // Calculate the pulse duration
    uint16_t pulse_duration = pulse_end - pulse_start; // in microseconds

    // Calculate the distance in cm
    // Speed of sound = 34300 cm/s => Distance = (pulse_duration / 2) * (speed of sound / 1,000,000)
    uint16_t distance = (pulse_duration / 2.0) * 0.0343;

    return distance;
}
