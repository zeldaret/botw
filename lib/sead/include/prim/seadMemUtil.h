#ifndef SEAD_MEM_UTIL_H_
#define SEAD_MEM_UTIL_H_

#include <basis/seadTypes.h>

namespace sead
{
class MemUtil
{
public:
    static void* fill(void* ptr, u8 c, size_t size);
    static void* fillZero(void* ptr, size_t size);
    static void* copyOverlap(void* dest, const void* src, size_t size);
    static void* copy(void* dest, const void* src, size_t size);
    static void* copyAlign32(void* dest, const void* src, size_t size);
    static int compare(const void* ptr1, const void* ptr2, size_t size);

    static bool isStack(const void* addr);
    static bool isHeap(const void* addr);

    /// Checks whether a region of memory is filled with 0.
    static bool checkFillType(const void* ptr, size_t size);

    static void dumpMemoryBinary(const void* ptr, u32 size_front, u32 size_back, bool is_align);
};
}  // namespace sead

#define SEAD_PRIM_MEM_UTIL_H_
#ifdef cafe
#include <prim/cafe/seadMemUtilCafe.hpp>
#elif NNSDK
#include <prim/nin/seadMemUtilNin.hpp>
#else
#error "Unknown platform"
#endif  // cafe
#undef SEAD_PRIM_MEM_UTIL_H_

#endif  // SEAD_MEM_UTIL_H_
