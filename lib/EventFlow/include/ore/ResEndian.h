#pragma once

#ifdef _MSC_VER
#include <stdlib.h>
#endif

#include <cstring>
#include <ore/Types.h>

namespace ore {

[[nodiscard]] inline u8 SwapEndian(u8 x) {
    return x;
}

[[nodiscard]] inline u16 SwapEndian(u16 x) {
#ifdef _MSC_VER
    return _byteswap_ushort(x);
#else
    return __builtin_bswap16(x);
#endif
}

[[nodiscard]] inline u32 SwapEndian(u32 x) {
#ifdef _MSC_VER
    return _byteswap_ulong(x);
#else
    return __builtin_bswap32(x);
#endif
}

[[nodiscard]] inline u64 SwapEndian(u64 x) {
#ifdef _MSC_VER
    return _byteswap_uint64(x);
#else
    return __builtin_bswap64(x);
#endif
}

[[nodiscard]] inline s8 SwapEndian(s8 x) {
    return SwapEndian(u8(x));
}

[[nodiscard]] inline s16 SwapEndian(s16 x) {
    return SwapEndian(u16(x));
}

[[nodiscard]] inline s32 SwapEndian(s32 x) {
    return SwapEndian(u32(x));
}

[[nodiscard]] inline s64 SwapEndian(s64 x) {
    return SwapEndian(u64(x));
}

[[nodiscard]] inline f32 SwapEndian(f32 x) {
    static_assert(sizeof(u32) == sizeof(f32));
    u32 i;
    std::memcpy(&i, &x, sizeof(i));
    i = SwapEndian(i);
    std::memcpy(&x, &i, sizeof(i));
    return x;
}

template <typename T>
inline void SwapEndian(T* value) {
    *value = SwapEndian(*value);
}

struct ResEndian {
    char* base;
    bool is_serializing;
};

}  // namespace ore
