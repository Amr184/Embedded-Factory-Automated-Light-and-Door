#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "ultrasonic_sensor.h"
#include "infrared_sensor.h"
#include "servo.h"
#include "ldr_sensor.h"
#include "led.h"
#include "buzzer.h"
#include "hardware/pwm.h"
#include <stdio.h>

// Define GPIO pins
#define BUZZER_PIN 8           // GPIO pin for the buzzer
#define INFRARED_PIN 4         // GPIO pin for the infrared sensor
#define ULTRASONIC_TRIG 2      // GPIO pin for the ultrasonic trigger
#define ULTRASONIC_ECHO 3      // GPIO pin for the ultrasonic echo
#define SERVO_PIN 17           // GPIO pin for the servo motor
#define LDR_PIN 27             // ADC pin for the LDR sensor (GPIO 26)
#define LED_PIN 10             // GPIO pin for the LED

volatile bool object_detected = false; // Flag for object detection

// Function to adjust LED brightness based on LDR value
void adjust_led_brightness(uint16_t ldr_value) {
    if (ldr_value > 4095) ldr_value = 4095; // Clamp LDR value

    // Calculate duty cycle for PWM (0-65535 range)
    uint16_t duty_cycle = (uint16_t)((ldr_value * 65535) / 4095);

    // Set PWM duty cycle for the LED
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    pwm_set_gpio_level(LED_PIN, duty_cycle);
}

// Infrared Sensor Task
void infrared_task(void *params) {
    gpio_init(INFRARED_PIN);
    gpio_set_dir(INFRARED_PIN, GPIO_IN);

    while (1) {
        if (!gpio_get(INFRARED_PIN)) {  // Object detected (low signal)
            Servo_SetAngle(SERVO_PIN, 0);
            Buzzer_On(BUZZER_PIN);
        } else {
           // sleep_ms(1500);
            Servo_SetAngle(SERVO_PIN, 180);
            Buzzer_Off(BUZZER_PIN);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void ultrasonic_task(void *params) {
    ultrasonic_init(ULTRASONIC_TRIG, ULTRASONIC_ECHO);
    LDR_Init(LDR_PIN);

    float distance;
    uint16_t ldr_value;

    while (1) {
        distance = ultrasonic_measure_distance(ULTRASONIC_TRIG, ULTRASONIC_ECHO);

        if (distance <= 14.0) {  // Object detected within 50 cm
            LED_On(LED_PIN);
            ldr_value = LDR_Read(LDR_PIN);  // Pass the ADC pin to LDR_Read
            printf("Distance: %.2f cm, LDR Value: %d\n", distance, ldr_value);

            adjust_led_brightness(ldr_value);
        } else {
            LED_Off(LED_PIN);
            pwm_set_gpio_level(LED_PIN, 0);  // Reset PWM duty cycle to zero
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


// Main Function
int main() {
    stdio_init_all();
    sleep_ms(2000);  // Wait for serial console to initialize

    // Initialize peripherals
    Buzzer_Init(BUZZER_PIN);
    Servo_Init(SERVO_PIN);
    LED_Init(LED_PIN);
    LDR_Init(LDR_PIN);

    // Configure PWM for LED brightness
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    pwm_set_wrap(slice_num, 65535);  // Max PWM wrap value
    pwm_set_gpio_level(LED_PIN, 0);  // Start with LED off
    pwm_set_enabled(slice_num, true);

    // Create tasks
    xTaskCreate(infrared_task, "Infrared Task", 256, NULL, 1, NULL);
    xTaskCreate(ultrasonic_task, "Ultrasonic Task", 256, NULL, 1, NULL);

    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    while (1) {
        // Should never reach here
    }

    return 0;
}
