#include "Arduino.h"
#include "HardwareSerial.h"
#include "avr/pgmspace.h"
#include <avr/io.h>
extern "C" {
#include <stdint.h>
}
#include <util/delay.h>

// #define kRowCount 4
// #define kRowSize 16

#define kRowCount 200
#define kRowSize 101

namespace {
const int8_t kInputData[kRowCount][kRowSize] PROGMEM = {
#include "problem3.h"
};

#define kInputSize (sizeof(kInputData) / sizeof(kInputData[0]))

int8_t ReadVal(const int8_t *input_data, uint32_t index) {
  return static_cast<int8_t> pgm_read_byte(&input_data[index]);
}

int8_t FindBiggestLeftDigit(const char *row) {
  for (char i = '9'; i > '0'; i--) {
    // biggest digit can't be the last one
    for (int8_t j = 0; j < kRowSize - 2; j++) {
      if (row[j] == i) {
        return j;
      }
    }
  }
  return -1;
}

int8_t FindBiggestDigit(const char *row, const uint8_t end) {
  for (char i = '9'; i > '0'; i--) {
    // biggest digit can't be the last one
    for (int8_t j = 0; j < end - 1; j++) {
      if (row[j] == i) {
        return j;
      }
    }
  }
  return -1;
}

int8_t Search(const char *row, char digit) {

  for (int8_t j = 0; j < kRowSize - 1; j++) {
    if (row[j] == digit) {
      return j;
    }
  }
  return -1;
}

} // namespace

void setup() {
  Serial.begin(115200);
  Serial.println("3a");

  uint32_t result = 0;

  char row[kRowSize];

  for (const int8_t *romrow : kInputData) {
    for (int8_t j = 0; j < kRowSize; j++) {
      row[j] = static_cast<char>(ReadVal(romrow, j));
      Serial.print(row[j]);
    }
    uint8_t left_digit = FindBiggestLeftDigit(row);
    uint8_t right_digit =
        FindBiggestDigit(&row[left_digit + 1], kRowSize - left_digit - 1);
    Serial.print(" ");
    Serial.print(row[left_digit]);
    Serial.print(row[right_digit + left_digit + 1]);
    const uint8_t joltage = ((row[left_digit] - '0') * 10) +
                            row[right_digit + left_digit + 1] - '0';
    Serial.print(" ");
    Serial.println(joltage);
    result += joltage;
  }

  Serial.print(" ");
  Serial.println(result);
}

void loop() { ; }