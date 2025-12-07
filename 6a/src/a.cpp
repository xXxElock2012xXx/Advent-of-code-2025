#include "Arduino.h"
#include "HardwareSerial.h"
#include <avr/pgmspace.h>
extern "C" {
#include <stdint.h>
}
#include "Uint64.h"
#include <util/delay.h>

// constexpr uint8_t kIdRangesSize = 2 * 4;
// constexpr uint8_t kIdCount = 6;

constexpr uint16_t kIdRangesSize = 2 * 200;
constexpr uint16_t kIdCount = 1000;

namespace {
const uint64_t kIdRanges[kIdRangesSize] PROGMEM = {
#include "problem5-1.h"
};

const uint64_t kIds[kIdCount] PROGMEM = {
#include "problem5-2.h"
};

} // namespace

void setup() {

  uint16_t result = 0;
  Uint64 left;
  Uint64 right;

  Uint64 mirror;

  for (uint16_t i = 0; i < kIdCount; i++) {

    mirror.ReadUint64(kIds, i);

    for (uint16_t j = 0; j < kIdRangesSize - 1; j += 2) {
      // Serial.print(i);
      // Serial.print(" ");
      // Serial.println(j);

      left.ReadUint64(kIdRanges, j);
      right.ReadUint64(kIdRanges, j + 1);

      if (left <= mirror && mirror <= right) {
        result++;
        break;
      }
    }
    Serial.println(i);
  }

  Serial.println(result);
}
