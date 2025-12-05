#ifndef BITSET_HPP__
#define BITSET_HPP__
#include <stdint.h>
#include <string.h>

template <uint16_t nb> class Bitset {
public:
  Bitset() { Flush(); }

  void Set(const uint8_t value, const uint16_t idx) {
    if (value == 1) {
      memory_[idx / 8] |= static_cast<uint8_t>(1 << (idx % 8));
    } else {
      memory_[idx / 8] &= ~static_cast<uint8_t>(1 << (idx % 8));
    }
  }

  void Flush() { memset(memory_, 0, nb); }

  [[nodiscard]] bool At(const uint16_t idx) const {
    return static_cast<bool>(memory_[idx / 8] &
                             static_cast<uint8_t>(1 << (idx % 8)));
  }

private:
  uint8_t memory_[nb];
};

#endif // BITSET_HPP__