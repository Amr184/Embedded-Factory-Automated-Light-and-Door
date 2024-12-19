#ifndef SERVO_H
#define SERVO_H

#include "hardware/gpio.h"
#include <stdint.h>

/**
 * @brief Initializes a servo on the specified GPIO pin.
 * 
 * Configures the PWM for the servo at 50 Hz with a clock divider. 
 * The servo's initial position is set to 0 degrees (1 ms pulse).
 * 
 * @param gpio_pin GPIO pin connected to the servo signal line.
 */
void Servo_Init(uint gpio_pin);

/**
 * @brief Sets the angle of a servo motor.
 * 
 * Converts an angle (0 to 180 degrees) to the appropriate PWM pulse width 
 * and updates the duty cycle of the PWM signal accordingly. The pulse width 
 * for 0 degrees is 1 ms, and for 180 degrees, it is 2 ms.
 * 
 * @param gpio_pin GPIO pin connected to the servo signal line.
 * @param angle Desired angle (0 to 180 degrees). Values outside this range are clamped.
 */
void Servo_SetAngle(uint gpio_pin, uint8_t angle);

#endif // SERVO_H
