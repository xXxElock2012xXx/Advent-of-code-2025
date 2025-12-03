#include "Arduino.h"
#include "HardwareSerial.h"
#include "avr/pgmspace.h"
#include <avr/io.h>
extern "C" {
#include <stdint.h>
}
#include <util/delay.h>

const uint64_t kInputData[] PROGMEM = {
#include "problem2.h"
};

constexpr int32_t kInputSize PROGMEM =
    sizeof(kInputData) / sizeof(kInputData[0]);

namespace {

class Uint64 {
public:
  Uint64() {
    bytes[1] = 0;
    bytes[0] = 0;
  }
  Uint64(const Uint64 &other) = default;

  Uint64 &operator=(const Uint64 &other) = default;

  Uint64 &operator+=(const Uint64 &other) {

    bytes[0] += other.bytes[0];

    bytes[1] += other.bytes[1] +
                static_cast<uint32_t>(bytes[0] + other.bytes[0] < bytes[0]);
    return *this;
  }

  void Print() const {
    for (int8_t i = 31; i >= 0; i--) {
      Serial.print(static_cast<uint8_t>(
          (bytes[1] & (static_cast<uint32_t>(1) << i)) != 0));
    }

    for (int8_t i = 31; i >= 0; i--) {
      Serial.print(static_cast<uint8_t>(
          (bytes[0] & (static_cast<uint32_t>(1) << i)) != 0));
    }
  }
  uint32_t bytes[2];
};

Uint64 ReadVal(const uint64_t *input_data, uint16_t index) {

  Uint64 retval;
  const uint8_t *source = reinterpret_cast<const uint8_t *>(input_data) +
                          (sizeof(input_data[0]) * index);
  uint8_t *dest = reinterpret_cast<uint8_t *>(&retval);

  for (uint8_t i = 0; i < 8; i++) {
    *(dest + i) = pgm_read_byte(source + i);
  }

  return retval;
}

uint8_t CountDigits(uint64_t n) {
  uint8_t count = 0;
  while (n != 0) {
    count++;
    n /= 10;
  }
  return count;
}

uint64_t Raise(uint64_t base, uint8_t exponent) {
  uint64_t copy = base;
  base = 1;
  while (exponent != 0) {
    base *= copy;
    exponent--;
  }
  return base;
}

uint8_t ProcessNumber(uint64_t n) {
  const uint8_t digit_count = CountDigits(n);
  if (digit_count % 2 == 0) {
    const uint64_t exponent = Raise(10, digit_count / 2);

    if (n % exponent == n / exponent) {
      return 1;
    }
  }
  return 0;
}
} // namespace

void setup() {
  Serial.begin(115200);
  Serial.println("2a");

  uint64_t result = 0;

  for (uint8_t i = 0; i < kInputSize - 1; i += 2) {
    const Uint64 start = ReadVal(kInputData, i);
    // const uint64_t end = ReadVal(kInputData, i + 1);

    // for (uint64_t j = kInputData[i]; j <= kInputData[i + 1]; j++) {

    Serial.print(i);
    Serial.print(" ");
    start.Print();
    // if (ProcessNumber(j) != 0) {
    //   result += j;
    // }
    //   break;
    // }
  }
  // Serial.print(result);
  // Serial.println();
}

void loop() { ; }