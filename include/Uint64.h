#ifndef UINT64_H__
#define UINT64_H__

#include "ReadPgm.h"
#include "arduino/HardwareSerial.h"
#include "stdint.h"

extern HardwareSerial Serial;

class Uint64 {
public:
  // bytes[1] = msb bytes[0] = lsb
  Uint64() {
    bytes[0] = 0;
    bytes[1] = 0;
  }
  explicit Uint64(const int &other) {
    bytes[0] = other;
    bytes[1] = 0;
  }
  Uint64(const Uint64 &other) = default;

  Uint64 &operator=(const Uint64 &other) = default;

  Uint64 &operator=(const int other) {
    bytes[0] = other;
    bytes[1] = 0;
    return *this;
  };

  Uint64 &operator+=(const Uint64 &other) {
    uint32_t copy = bytes[0];

    bytes[0] += other.bytes[0];

    bytes[1] += other.bytes[1] +
                static_cast<uint32_t>(copy + other.bytes[0] < bytes[0]);
    return *this;
  }

  Uint64 &operator+=(const int &other) {
    uint32_t copy = bytes[0];

    bytes[0] += other;

    bytes[1] += static_cast<uint32_t>(copy + other < bytes[0]);
    return *this;
  }

  Uint64 operator+(const Uint64 &other) {
    Uint64 retval;

    retval.bytes[0] = bytes[0] + other.bytes[0];

    retval.bytes[1] =
        bytes[1] + other.bytes[1] +
        static_cast<uint32_t>(bytes[0] + other.bytes[0] < bytes[0]);

    return retval;
  }

  Uint64 operator+(const int &other) {
    Uint64 retval;

    retval.bytes[0] = bytes[0] + other;

    retval.bytes[1] =
        bytes[1] + static_cast<uint32_t>(bytes[0] + other < bytes[0]);

    return retval;
  }

  bool operator<(const Uint64 &other) {
    return this->bytes[1] < other.bytes[1] or
           (this->bytes[0] < other.bytes[0] &&
            this->bytes[1] == other.bytes[1]);
  }

  bool operator<=(const Uint64 &other) {
    return *this < other or *this == other;
  }

  bool operator==(const uint16_t &other) {
    return this->bytes[0] == static_cast<uint32_t>(other) &&
           this->bytes[1] == 0;
  }

  bool operator==(const Uint64 &other) {
    return this->bytes[0] == other.bytes[0] && this->bytes[1] == other.bytes[1];
  }

  Uint64 &operator++() { return *this += 1; }

  void ReadUint64(const uint64_t *input_data) {
    Serial.println("Fuck uint64");
    ReadVal(input_data, this->bytes);
  }

  void Print() {
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

#endif // UINT64_H__