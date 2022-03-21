#include <basis/seadRawPrint.h>
#include <heap/seadHeapMgr.h>
#include <prim/seadMemUtil.h>
#include <prim/seadPtrUtil.h>

namespace sead
{
void* MemUtil::copyAlign32(void* dst, const void* src, size_t size)
{
    SEAD_ASSERT_MSG(size % 32 == 0, "size %% 32 == 0  size:%zu", size);
    SEAD_ASSERT_MSG(PtrUtil::isAligned(dst, 32) && PtrUtil::isAligned(src, 32),
                    "pointer must be 32-byte aligned. src:%p -> dst:%p", src, dst);
    return copy(dst, src, size);
}

// TODO: MemUtil::isStack (in platform specific .cpp)

bool MemUtil::isHeap(const void* addr)
{
    return HeapMgr::instance() && HeapMgr::isContainedInAnyHeap(addr);
}

// NON_MATCHING: Clang optimizes the if (ptr) return false; into if (ptr) return ptr;
bool MemUtil::checkFillType(const void* ptr_, size_t size)
{
    const u8* ptr = static_cast<const u8*>(ptr_);
    if (!ptr)
        return false;

    const u8 value = *ptr;
    if (size == 0)
        return value == 0;

    size_t i = 1;
    while (i < size)
    {
        if (value != ptr[i++])
            return false;
    }
    return value == 0;
}

// TODO: MemUtil::dumpMemoryBinary

}  // namespace sead
