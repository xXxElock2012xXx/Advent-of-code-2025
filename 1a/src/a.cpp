#include "Arduino.h"
#include "HardwareSerial.h"
#include "avr/pgmspace.h"
#include <avr/io.h>
extern "C" {
#include <stdint.h>
}
#include <util/delay.h>

const int16_t kInputData[] PROGMEM = {
#include "problem1.h"
};

constexpr uint32_t kInputSize PROGMEM = 4654;
constexpr int8_t kOverflowValue PROGMEM = 100U;

namespace {

int16_t ReadVal(const int16_t *input_data, uint32_t index) {
  return static_cast<int16_t> pgm_read_word(&input_data[index]);
}
} // namespace

void setup() {
  Serial.begin(115200);
  Serial.println("1a");

  int16_t count = 50;
  uint16_t result = 0;

  for (uint32_t i = 0; i < kInputSize; i++) {
    const int16_t next_val =
        ReadVal(static_cast<const int16_t *>(kInputData), i);
    const int8_t normalized_val =
        static_cast<int8_t>(next_val % kOverflowValue);

    count += normalized_val;
    if (count < 0) {

      count += kOverflowValue;
    }

    count %= kOverflowValue;
    if (count == 0) {
      result++;
    }
  }
  Serial.print("result: ");
  Serial.println(result);
}

void loop() { ; }