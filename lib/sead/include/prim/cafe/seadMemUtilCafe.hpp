#pragma once

#include <cafe.h>
#include <string.h>

#ifndef SEAD_PRIM_MEM_UTIL_H_
#include <prim/seadMemUtil.h>
#endif

namespace sead
{
inline void* MemUtil::fill(void* ptr, u8 c, size_t size)
{
    return OSBlockSet(ptr, c, size);
}

inline void* MemUtil::fillZero(void* ptr, size_t size)
{
    return OSBlockSet(ptr, 0, size);
}

inline void* MemUtil::copyOverlap(void* dest, const void* src, size_t size)
{
    return OSBlockMove(dest, src, size, 0);
}

inline void* MemUtil::copy(void* dest, const void* src, size_t size)
{
    return OSBlockMove(dest, src, size, 0);
}

inline int MemUtil::compare(const void* ptr1, const void* ptr2, size_t size)
{
    return memcmp(ptr1, ptr2, size);
}
}  // namespace sead
