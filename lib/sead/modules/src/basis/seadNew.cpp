#include <cstdlib>

#include <basis/seadNew.h>
#include <heap/seadHeap.h>
#include <heap/seadHeapMgr.h>

namespace sead
{
namespace system
{
void* NewImpl(Heap* heap, size_t size, s32 alignment, bool abortOnFailure)
{
    if (!HeapMgr::sInstancePtr)
    {
        SEAD_WARN("alloced[%zu] before sead system initialize", size);
        return malloc(size);
    }

    if (!heap)
    {
        heap = sead::HeapMgr::sInstancePtr->getCurrentHeap();
        if (!heap)
        {
            SEAD_ASSERT_MSG(false, "Current heap is null. Cannot alloc.");
            return nullptr;
        }
    }

    void* result = heap->tryAlloc(size, alignment);
    if (!result && abortOnFailure)
    {
        SEAD_ASSERT_MSG(
            false, "alloc failed. size: %zu, allocatable size: %zu, alignment: %d, heap: %s", size,
            heap->getMaxAllocatableSize(alignment), alignment, heap->getName().cstr());
        return nullptr;
    }
    return result;
}

void DeleteImpl(void* ptr)
{
    if (!sead::HeapMgr::sInstancePtr)
    {
        SEAD_WARN("free[0x%p] before sead system initialize", ptr);
        free(ptr);
        return;
    }

    if (!ptr)
        return;

    Heap* containHeap = sead::HeapMgr::sInstancePtr->findContainHeap(ptr);
    if (containHeap)
        containHeap->free(ptr);
    else
        SEAD_ASSERT_MSG(false, "delete bad pointer [0x%p]", ptr);
}
}  // namespace system

#ifdef SEAD_DEBUG
void AllocFailAssert(Heap* heap, size_t size, u32 alignment)
{
    if (!heap)
    {
        heap = HeapMgr::instance()->getCurrentHeap();
        SEAD_ASSERT_MSG(heap, "Current heap is null. Cannot alloc.");
    }

    SEAD_ASSERT_MSG(false,
                    "alloc failed. size: %zu, allocatable size: %zu, alignment: %u, heap: %s", size,
                    heap->getMaxAllocatableSize(alignment), alignment, heap->getName().cstr());
}
#endif
}  // namespace sead

// operator new(size_t)

void* operator new(size_t size)
{
    return sead::system::NewImpl(nullptr, size, 8, true);
}

void* operator new[](size_t size)
{
    return sead::system::NewImpl(nullptr, size, 8, true);
}

void* operator new(size_t size, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(nullptr, size, 8, false);
}

void* operator new[](size_t size, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(nullptr, size, 8, false);
}

// operator new(size_t, s32 alignment)

void* operator new(size_t size, s32 alignment)
{
    return sead::system::NewImpl(nullptr, size, alignment, true);
}

void* operator new[](size_t size, s32 alignment)
{
    return sead::system::NewImpl(nullptr, size, alignment, true);
}

void* operator new(size_t size, s32 alignment, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(nullptr, size, alignment, false);
}

void* operator new[](size_t size, s32 alignment, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(nullptr, size, alignment, false);
}

// operator new(size_t, sead::Heap*, s32 alignment)

void* operator new(size_t size, sead::Heap* heap, s32 alignment)
{
    return sead::system::NewImpl(heap, size, alignment, true);
}

void* operator new[](size_t size, sead::Heap* heap, s32 alignment)
{
    return sead::system::NewImpl(heap, size, alignment, true);
}

void* operator new(size_t size, sead::Heap* heap, s32 alignment, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(heap, size, alignment, false);
}

void* operator new[](size_t size, sead::Heap* heap, s32 alignment, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(heap, size, alignment, false);
}

// operator new(size_t, sead::Heap*, const std::nothrow_t&)

void* operator new(size_t size, sead::Heap* heap, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(heap, size, 8, false);
}

void* operator new[](size_t size, sead::Heap* heap, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(heap, size, 8, false);
}

// operator delete(void*)

void operator delete(void* ptr) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete(void* ptr, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

// operator delete(void*, s32)

void operator delete(void* ptr, s32)
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, s32)
{
    sead::system::DeleteImpl(ptr);
}

void operator delete(void* ptr, s32, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, s32, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

// operator delete(void*, sead::Heap*, const std::nothrow_t&)

void operator delete(void* ptr, sead::Heap*, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, sead::Heap*, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

// operator delete(void*, sead::Heap*, s32)

void operator delete(void* ptr, sead::Heap*, s32)
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, sead::Heap*, s32)
{
    sead::system::DeleteImpl(ptr);
}

void operator delete(void* ptr, sead::Heap*, s32, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, sead::Heap*, s32, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}
