#include "Arduino.h"
#include "HardwareSerial.h"
#include <avr/pgmspace.h>
extern "C" {
#include <stdint.h>
}
#include <util/delay.h>

// constexpr uint8_t kRowLength = 13;
// constexpr uint8_t kRowCount = 12;

constexpr uint8_t kRowLength = 138;
constexpr uint8_t kRowCount = 137;

namespace {
const char kInputData[kRowCount][kRowLength] PROGMEM = {
#include "problem4.h"
};

#define kInputSize (sizeof(kInputData) / sizeof(kInputData[0]))

template <typename type_t>
type_t ReadVal(const type_t *input_data, uint32_t index) {
  return static_cast<type_t>(pgm_read_byte(&input_data[index]));
}

} // namespace

void setup() {
  Serial.begin(115200);
  Serial.println("4a");
  uint16_t result = 0;

  uint32_t start = micros();

  for (uint8_t i = 0; i < kRowLength - 2; i++) {
    for (uint8_t j = 0; j < kRowLength - 2; j++) {

      if (ReadVal(kInputData[i + 1], j + 1) == '@') {
        uint8_t neighbour_count = 0;

        for (uint8_t x = 0; x < 3; x++) {
          for (uint8_t y = 0; y < 3; y++) {
            if (ReadVal(kInputData[i + x], j + y) == '@') {
              neighbour_count++;
            }
          }
        }

        if (neighbour_count <= 4) {
          result++;
        }
      }
    }
  }
  uint32_t end = micros() - start;
  Serial.println();
  Serial.print("time: ");
  Serial.print(end);
  Serial.println(" micros");
  Serial.println(result);
}

void loop() { ; }