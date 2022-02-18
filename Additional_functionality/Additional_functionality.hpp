#ifndef ADDITIONAL_FUNCTIONALITY_HPP_
#define ADDITIONAL_FUNCTIONALITY_HPP_

template<typename T, unsigned int N>
constexpr unsigned int array_size(T(&)[N]) noexcept {
    return N;
}

#if defined( linux )
#include "../Arduino/Arduino.h"
#endif // linux

// NUM -> 0x?? ; 0x3C -> ('3' << 8 | 'C')
uint16_t convert_to_hex(uint8_t byte);
// where - NUM[len] ; whence - STR[len * 2]
size_t convert_to_hex(const uint8_t* where, uint8_t* whence, size_t len);
size_t convert_to_hex(const uint8_t* where, char* whence, size_t len);
size_t convert_to_hex(const uint8_t* where, uint8_t* whence, uint8_t len);
size_t convert_to_hex(const uint8_t* where, char* whence, uint8_t len);


#endif // ADDITIONAL_FUNCTIONALITY_HPP_
