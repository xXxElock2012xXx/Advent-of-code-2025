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

constexpr int8_t kOverflowValue PROGMEM = 100U;
constexpr int32_t kInputSize PROGMEM = sizeof(kInputData) / sizeof(int16_t);

namespace {

int16_t ReadVal(const int16_t *input_data, uint32_t index) {
  return static_cast<int16_t> pgm_read_word(&input_data[index]);
}
} // namespace

void setup() {
  Serial.begin(115200);
  Serial.println("1b");

  int16_t count = 50;
  uint32_t result = 0;

  for (uint32_t i = 0; i < kInputSize; i++) {
    const int16_t next_val =
        ReadVal(static_cast<const int16_t *>(kInputData), i);
    const int8_t normalized_val =
        static_cast<int8_t>(next_val % kOverflowValue);
    const int8_t ticks = abs(next_val / kOverflowValue);
    result += ticks;

    Serial.print(" nextval normalized val ticks");
    Serial.print(next_val);
    Serial.print(" ");
    Serial.print(normalized_val);
    Serial.print(" ");
    Serial.println(ticks);

    const int16_t old_count = count; 
    count += normalized_val;
    if (count < 0) {
      if (old_count != 0){
        result++;

      }
      count += kOverflowValue;
      Serial.print("count < 0 : ");
      Serial.println(count - kOverflowValue);
    }

    if (count > kOverflowValue) {
      result++;
      Serial.print("count > koverflow : ");
      Serial.println(count);
    }

    count %= kOverflowValue;
    if (count == 0) {
      result++;
    }
    Serial.println(count);
  }
  Serial.print("result: ");
  Serial.println(result);
}

void loop() { ; }