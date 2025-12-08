#include "Arduino.h"
#include "HardwareSerial.h"
#include <avr/pgmspace.h>
extern "C" {
#include <stdint.h>
}
#include "Uint64.h"
#include <util/delay.h>

constexpr uint8_t kNumberCount = 3;
constexpr uint8_t kCollumnCount = 4;
constexpr uint8_t kOerationCount = kCollumnCount;

namespace {
const uint64_t kIdRanges[kCollumnCount * kNumberCount] PROGMEM = {
#include "problem6-example1.h"
};

const uint64_t kIds[kOerationCount] PROGMEM = {
#include "problem6-example2.h"
};


uint64_t ReadVal_main(const uint64_t *input_data, uint16_t index) {

  uint64_t retval;
  const uint8_t *source = reinterpret_cast<const uint8_t *>(input_data) +
                          (sizeof(input_data[0]) * index);
  uint8_t *dest = reinterpret_cast<uint8_t *>(&retval);

  for (uint8_t i = 0; i < 8; i++) {
    *(dest + i) = pgm_read_byte(source + i);
  }

  return retval;
}



} // namespace

void setup() {

  Uint64 result;

  Serial.print("fuck main");
  Serial.print("fuck main");
  result.ReadUint64(&kIdRanges[0]);
  result.Print();
}
