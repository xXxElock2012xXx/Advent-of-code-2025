#include "Arduino.h"
#include "Bitset.h"
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
  Serial.println("4b");
  uint16_t result = 0;
  uint32_t start = micros();

  Bitset<(kRowCount * (kRowLength - 1) + 7) / 8> data;
  Bitset<(kRowCount * (kRowLength - 1) + 7) / 8> mirror;

  for (uint8_t i = 0; i < kRowLength - 1; i++) {
    for (uint8_t j = 0; j < kRowLength - 1; j++) {
      const uint8_t value =
          static_cast<const uint8_t>(ReadVal(kInputData[i], j) == '@');
      data.Set(value, (i * (kRowLength - 1)) + j);
    }
  }

  // for (uint8_t i = 0; i < kRowLength - 1; i++) {
  //   for (uint8_t j = 0; j < kRowLength - 1; j++) {
  //     Serial.print(static_cast<int>(data.At((i * (kRowLength - 1)) + j)));
  //   }
  //   Serial.println();
  // }

  // Serial.println();
  uint8_t next = 1;
  while (next) {

    next = 0;
    for (uint8_t i = 0; i < kRowLength - 2; i++) {
      for (uint8_t j = 0; j < kRowLength - 2; j++) {

        if (data.At(((i + 1) * (kRowLength - 1)) + j + 1)) {
          uint8_t neighbour_count = 0;

          for (uint8_t x = 0; x < 3; x++) {
            for (uint8_t y = 0; y < 3; y++) {
              if (data.At(((i + x) * (kRowLength - 1)) + j + y)) {
                neighbour_count++;
              }
            }
          }

          if (neighbour_count <= 4) {
            result++;
            mirror.Set(1, ((i + 1) * (kRowLength - 1)) + j + 1);
            next = 1;
          }
        }
      }
    }

    for (uint8_t i = 0; i < kRowLength - 1; i++) {
      for (uint8_t j = 0; j < kRowLength - 1; j++) {
        if (mirror.At((i * (kRowLength - 1)) + j)){
          data.Set(0, (i * (kRowLength - 1)) + j);
        }
      }
    }
    mirror.Flush();
  }

  uint32_t end = micros() - start;
  Serial.println();
  Serial.print("time: ");
  Serial.print(end);
  Serial.println(" micros");
  Serial.println(result);
}

void loop() { ; }