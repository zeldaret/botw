#pragma once

#include <basis/seadTypes.h>
#include <string_view>

namespace ksys::util {

template <typename CharType = u8>
constexpr u32 calcCrc32(const CharType* data, std::size_t size) {
    u32 crc = 0xFFFFFFFF;
    for (std::size_t i = 0; i < size; ++i) {
        crc ^= u8(data[i]);
        for (std::size_t j = 0; j < 8; ++j) {
            u32 mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
    }
    return ~crc;
}

constexpr u32 calcCrc32(std::string_view str) {
    return calcCrc32<char>(str.data(), str.size());
}

}  // namespace ksys::util
