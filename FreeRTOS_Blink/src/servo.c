#include "servo.h"
#include "hardware/pwm.h"

// Constants for servo control
#define SYSTEM_CLOCK 125000000        // Clock speed of the system (can be changed)
#define PWM_FREQUENCY 50              // Servo PWM frequency (50 Hz for hobby servos)
#define CLK_DIV 8.0f                  // Clock divider for PWM
#define PWM_WRAP (SYSTEM_CLOCK / CLK_DIV / PWM_FREQUENCY) 

/**
 * @brief Initializes a servo on the specified GPIO pin.
 * 
 * Sets up the PWM with a 50 Hz frequency and 8x clock division.
 * The servo's initial position is set to 0 degrees (1 ms pulse).
 * 
 * @param gpio_pin GPIO pin connected to the servo signal line.
 */
void Servo_Init(uint gpio_pin) {
    // Set the pin function to PWM
    gpio_set_function(gpio_pin, GPIO_FUNC_PWM); 

    // Get the PWM slice for the given GPIO pin
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin); 

    // Get the default PWM configuration
    pwm_config config = pwm_get_default_config();    

    // Set the PWM wrap (period) and clock divider
    pwm_config_set_wrap(&config, PWM_WRAP);         
    pwm_config_set_clkdiv(&config, CLK_DIV);          

    // Initialize the PWM, but don't start it immediately
    pwm_init(slice_num, &config, false);            

    // Set the servo to 0 degrees (1 ms pulse) initially
    pwm_set_gpio_level(gpio_pin, PWM_WRAP / 20); // 1 ms pulse for 0 degrees
    pwm_set_enabled(slice_num, true); // Start PWM after setting the duty cycle
}

/**
 * @brief Sets the angle of a servo motor.
 * 
 * This function converts an angle (0 to 180 degrees) to the appropriate 
 * PWM pulse width for controlling a hobby servo. The pulse width for 
 * 0 degrees is 1 ms, and for 180 degrees, it is 2 ms.
 * 
 * @param gpio_pin GPIO pin connected to the servo signal line.
 * @param angle Desired angle (0 to 180 degrees). Values outside this range are clamped.
 */
void Servo_SetAngle(uint gpio_pin, uint8_t angle) {
    // Clamp the angle to the 0-180 degree range
    if (angle > 180) angle = 180; 

    // Get the PWM slice for the GPIO pin
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin); 

    // Calculate the duty cycle for 0 degrees (1 ms) and 180 degrees (2 ms)
    uint16_t min_duty = PWM_WRAP / 20;  // 1 ms pulse (1/20th of 20ms period)
    uint16_t max_duty = PWM_WRAP / 10;  // 2 ms pulse (2/20th of 20ms period)

    // Linear interpolation for duty cycle between 1 ms (0 degrees) and 2 ms (180 degrees)
    uint16_t duty_cycle = min_duty + (angle * (max_duty - min_duty) / 180); 

    // Update the duty cycle of the PWM
    pwm_set_gpio_level(gpio_pin, duty_cycle);       
}
