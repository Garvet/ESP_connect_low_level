#include "Additional_functionality.hpp"

uint16_t convert_to_hex(uint8_t byte) {
    static const char name[16] {'0', '1', '2', '3', '4', '5', '6',
        '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    uint16_t result = ((uint16_t)name[(byte>>4)&0xF]) << 8 | ((uint16_t)name[byte&0xF]);
    return result;
}

size_t convert_to_hex(const uint8_t* where, uint8_t* whence, size_t len) {
    for (size_t i = 0; i < len; i++) {
        whence[i * 2]     = (where[i] >> 4) & 0x0F;
        whence[i * 2 + 1] =  where[i]       & 0x0F;
        if(whence[i * 2] < 10) whence[i * 2] += '0';
        else                   whence[i * 2] += 'A' - 10;
        if(whence[i * 2 + 1] < 10) whence[i * 2 + 1] += '0';
        else                       whence[i * 2 + 1] += 'A' - 10;
    }
    return len * 2;
}

size_t convert_to_hex(const uint8_t* where, char* whence, size_t len) {
    return convert_to_hex(where, reinterpret_cast<uint8_t*>(whence), len);
}
size_t convert_to_hex(const uint8_t* where, uint8_t* whence, uint8_t len) {
    return convert_to_hex(where, whence, static_cast<size_t>(len));
}
size_t convert_to_hex(const uint8_t* where, char* whence, uint8_t len) {
    return convert_to_hex(where, reinterpret_cast<uint8_t*>(whence), static_cast<size_t>(len));
}
