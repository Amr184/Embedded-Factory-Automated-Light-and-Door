#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

// Function prototypes
void Buzzer_Init(uint8_t buzzer_pin);
void Buzzer_On(uint8_t buzzer_pin);
void Buzzer_Off(uint8_t buzzer_pin);
void Buzzer_Beep(uint8_t buzzer_pin, uint32_t duration_ms);

#endif // BUZZER_H
