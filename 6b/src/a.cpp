#include "Arduino.h"
#include "HardwareSerial.h"
#include "ReadPgm.h"
#include <avr/pgmspace.h>
extern "C" {
#include <stdint.h>
}
#include "Uint64.h"
// constexpr uint8_t kNumberCount = 3;
// constexpr uint8_t kCollumnCount = 4;

constexpr uint8_t kNumberCount = 4;
constexpr uint16_t kCollumnCount = 1000;

namespace {
const uint32_t kNumbers[kCollumnCount * kNumberCount] PROGMEM = {
#include "problem6-1.h"
};

const uint8_t kOperations[kCollumnCount] PROGMEM = {
#include "problem6-2.h"
};

} // namespace

void setup() {

  Uint64 result;

  for (uint32_t i = 0; i < kCollumnCount; i++) {

    Uint64 temporary;
    uint8_t operation = 0;

    ReadVal(&kOperations[i], &operation);

    temporary = ReadVal(&kNumbers[i]);

    Serial.print(ReadVal(&kNumbers[i]));
    Serial.print(" ");

    for (uint32_t j = 1; j < kNumberCount; j++) {

      const uint32_t value = ReadVal(&kNumbers[(j * kCollumnCount) + i]);

      if (operation) {
        // plus
        temporary += value;
      } else {
        // multiplication
        temporary *= value;
      }
      Serial.print(value);
      Serial.print(" ");
    }
    Serial.println();

    result += temporary;
  }

  Serial.println();
  result.Print();
  Serial.println();
}
