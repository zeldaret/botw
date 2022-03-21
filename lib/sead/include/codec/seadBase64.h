#pragma once

#include <basis/seadTypes.h>

namespace sead
{
class Base64
{
public:
    static void encode(char* dst, const void* src, size_t length, bool url_safe);
    static bool decode(void* dst, size_t dst_size, const char* src, size_t src_size,
                       size_t* decoded_size);
};
}  // namespace sead
