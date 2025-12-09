#ifndef READ_PGM__
#define READ_PGM__

#include <avr/pgmspace.h>
#include <stdint.h>

#include "arduino/HardwareSerial.h"

template <typename type_t, typename type_t2>
void ReadVal(const type_t *input_data, type_t2 *destination) {

  const uint8_t *source = reinterpret_cast<const uint8_t *>(input_data);

  uint8_t *dest = reinterpret_cast<uint8_t *>(destination);

  for (uint8_t i = 0; i < static_cast<uint8_t>(sizeof(type_t)); i++) {
    *(dest + i) = pgm_read_byte(source + i);
  }
}

template <typename type_t> 
uint32_t ReadVal(const type_t *input_data) {

  const uint8_t *source = reinterpret_cast<const uint8_t *>(input_data);

  uint32_t retval = 0;

  uint8_t *dest = reinterpret_cast<uint8_t *>(&retval);

  for (uint8_t i = 0; i < static_cast<uint8_t>(sizeof(type_t)); i++) {
    *(dest + i) = pgm_read_byte(source + i);
  }
  return retval;
}

#endif // READ_PGM__
