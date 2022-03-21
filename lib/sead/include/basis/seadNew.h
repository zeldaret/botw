#ifndef SEAD_NEW_H_
#define SEAD_NEW_H_

#include <cstddef>
#include <new>

#include <basis/seadTypes.h>

namespace sead
{
class Heap;

void AllocFailAssert(Heap* heap, size_t size, u32 alignment);

#ifndef SEAD_DEBUG
inline void AllocFailAssert(Heap*, size_t, u32) {}
#endif
}  // namespace sead

void* operator new(size_t size);
void* operator new[](size_t size);
void* operator new(size_t size, const std::nothrow_t&) noexcept;
void* operator new[](size_t size, const std::nothrow_t&) noexcept;

void* operator new(size_t size, s32 alignment);
void* operator new[](size_t size, s32 alignment);
void* operator new(size_t size, s32 alignment, const std::nothrow_t&) noexcept;
void* operator new[](size_t size, s32 alignment, const std::nothrow_t&) noexcept;

void* operator new(size_t size, sead::Heap* heap, const std::nothrow_t&) noexcept;
void* operator new[](size_t size, sead::Heap* heap, const std::nothrow_t&) noexcept;

void* operator new(size_t size, sead::Heap* heap, s32 alignment = sizeof(void*));
void* operator new[](size_t size, sead::Heap* heap, s32 alignment = sizeof(void*));
void* operator new(size_t size, sead::Heap* heap, s32 alignment, const std::nothrow_t&) noexcept;
void* operator new[](size_t size, sead::Heap* heap, s32 alignment, const std::nothrow_t&) noexcept;

void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
void operator delete(void* ptr, const std::nothrow_t&) noexcept;
void operator delete[](void* ptr, const std::nothrow_t&) noexcept;

void operator delete(void* ptr, s32);
void operator delete[](void* ptr, s32);
void operator delete(void* ptr, s32, const std::nothrow_t&) noexcept;
void operator delete[](void* ptr, s32, const std::nothrow_t&) noexcept;

void operator delete(void* ptr, sead::Heap*, const std::nothrow_t&) noexcept;
void operator delete[](void* ptr, sead::Heap*, const std::nothrow_t&) noexcept;

void operator delete(void* ptr, sead::Heap*, s32);
void operator delete[](void* ptr, sead::Heap*, s32);
void operator delete(void* ptr, sead::Heap*, s32, const std::nothrow_t&) noexcept;
void operator delete[](void* ptr, sead::Heap*, s32, const std::nothrow_t&) noexcept;

namespace sead
{
inline u8* AllocBuffer(size_t size, Heap* heap, s32 alignment)
{
    u8* buffer = new (heap, alignment, std::nothrow) u8[size];
    if (buffer)
        return buffer;

#ifdef SEAD_DEBUG
    sead::AllocFailAssert(heap, size, alignment);
#endif
    return nullptr;
}
}  // namespace sead
#endif  // SEAD_NEW_H_
