#pragma once

#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>

namespace sead
{
class PtrUtil
{
public:
    // XXX: these probably do not match Nintendo's implementation

    static void* roundUpPow2(const void* ptr, u32 n)
    {
        const uintptr_t result = uintptr_t(ptr) + (n - uintptr_t(ptr) % n) % n;
        return reinterpret_cast<void*>(result);
    }

    static void* roundUpN(const void* ptr, u32 n)
    {
        const uintptr_t result = uintptr_t(ptr) + (n - uintptr_t(ptr) % n) % n;
        return reinterpret_cast<void*>(result);
    }

    static void* roundDownPow2(const void* ptr, u32 n)
    {
        const uintptr_t result = uintptr_t(ptr) - uintptr_t(ptr) % n;
        return reinterpret_cast<void*>(result);
    }

    static void* roundDownN(const void* ptr, u32 n)
    {
        const uintptr_t result = uintptr_t(ptr) - uintptr_t(ptr) % n;
        return reinterpret_cast<void*>(result);
    }

    static void* addOffset(const void* ptr, intptr_t offset)
    {
        return reinterpret_cast<void*>(uintptr_t(ptr) + offset);
    }

    static intptr_t diff(const void* ptr1, const void* ptr2)
    {
        return intptr_t(ptr1) - intptr_t(ptr2);
    }

    static bool isInclude(const void* ptr, const void* begin, const void* end)
    {
        return uintptr_t(begin) <= uintptr_t(ptr) && uintptr_t(ptr) <= uintptr_t(end);
    }

    static bool isAligned(const void* ptr, s32 alignment)
    {
        SEAD_ASSERT(alignment != 0);
        return uintptr_t(ptr) % alignment == 0;
    }
    static bool isAlignedPow2(const void* ptr, u32 n) { return (uintptr_t(ptr) & (n - 1)) == 0; }
    static bool isAlignedN(const void* ptr, s32 n) { return uintptr_t(ptr) % n == 0; }
};
}  // namespace sead
