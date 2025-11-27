#include "Arduino.h"
#include <avr/io.h>
#include <util/delay.h>

void setup() {
  DDRB = DDRB | (1 << DDB7);

  Serial.begin(115200);
}

void loop() {

  Serial.println("pula");
  PORTB = PORTB | (1 << PORTB7);
  _delay_ms(1000);
  PORTB = PORTB & ~(1 << PORTB7);
  _delay_ms(1000);
}