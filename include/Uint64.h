
#include "arduino/HardwareSerial.h"
#include "stdint.h"

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

  Uint64 &operator=(const int &other) {
    bytes[0] = other;
    bytes[1] = 0;
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
    return *this < other or *this==other;
  }

  bool operator==(const uint16_t &other) {
    return this->bytes[0] == static_cast<uint32_t>(other) &&
           this->bytes[1] == 0;
  }

  bool operator==(const Uint64 &other) {
    return this->bytes[0] == other.bytes[0] && this->bytes[1] == other.bytes[1];
  }

  Uint64 &operator++() { return *this += 1; }

  void ReadUint64(const uint64_t *input_data, uint16_t index) {

    const uint8_t *source = reinterpret_cast<const uint8_t *>(input_data) +
                            (sizeof(input_data[0]) * index);
    uint8_t *dest = reinterpret_cast<uint8_t *>(&this->bytes);

    for (uint8_t i = 0; i < 8; i++) {
      *(dest + i) = pgm_read_byte(source + i);
    }
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
