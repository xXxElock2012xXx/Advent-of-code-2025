#include "Arduino.h"
#include "Bitset.h"
#include "HardwareSerial.h"
#include <avr/pgmspace.h>
extern "C" {
#include <stdint.h>
}
#include <util/delay.h>

// constexpr uint8_t kRowLength = 12;
// constexpr uint8_t kRowCount = 12;

constexpr uint8_t kRowLength = 137;
constexpr uint8_t kRowCount = 137;

namespace {
const char kInputData[kRowCount][kRowLength + 1] PROGMEM = {
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

  Bitset<(kRowCount * kRowLength + 7) / 8> data;
  Bitset<(kRowCount * kRowLength + 7) / 8> mirror;

  for (uint8_t i = 0; i < kRowLength; i++) {
    for (uint8_t j = 0; j < kRowLength; j++) {
      if (ReadVal(kInputData[i], j) == '@') {
        data.FillBit((i * kRowLength) + j);
      }
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

    // uint8_t decompressed[3][kRowLength];

    // for (uint8_t k = 0; k < 3; k++) {
    //   for (uint8_t l = 0; l < kRowLength; l++) {
    //     if (data.At((k * (kRowLength)) + l)) {
    //       decompressed[k][l] = 1;
    //     } else {
    //       decompressed[k][l] = 0;
    //     }
    //   }
    // }

    for (uint8_t i = 0; i < kRowLength - 2; i++) {
      const uint16_t new_i = (static_cast<uint16_t>(i + 1)) * kRowLength;

      for (uint8_t j = 0; j < kRowLength - 2; j++) {
        const uint16_t index = new_i + j + 1;

        if (data.At(index)) {
          uint8_t neighbour_count = 0;

          for (uint8_t x = 0; x < 3; x++) {
            for (uint8_t y = 0; y < 3; y++) {
              if (data.At(((i + x) * kRowLength) + j + y)) {
                neighbour_count++;
              }
            }
          }

          if (neighbour_count <= 4) {
            result++;
            mirror.ClearBit(index);

            next = 1;
          } else {
            mirror.FillBit(index);
          }
        }
      }
    }

    data.Swap(mirror);
  }

  uint32_t end = micros() - start;
  Serial.println();
  Serial.print("time: ");
  Serial.print(end);
  Serial.println(" micros");
  Serial.println(result);
}

void loop() { ; }