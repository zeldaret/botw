#pragma once

#include <cstddef>
#include <memory>
#include <ore/Types.h>

namespace ore {

class Allocator {
public:
    Allocator() = default;
    virtual ~Allocator() = default;

    void* New(size_t size, size_t alignment = alignof(std::max_align_t)) {
        return AllocImpl(size, alignment);
    }

    template <typename T>
    T* New(size_t alignment = alignof(std::max_align_t)) {
        auto* buffer = AllocImpl(sizeof(T), alignment);
        if (buffer)
            return new (buffer) T;
        return static_cast<T*>(buffer);
    }

    template <typename T>
    void Delete(T* ptr) {
        std::destroy_at(ptr);
        Free(ptr);
    }

    template <typename T>
    void DeleteAndNull(T*& ptr) {
        std::destroy_at(ptr);
        Free(ptr);
        ptr = nullptr;
    }

    void Free(void* ptr) { FreeImpl(ptr); }

    virtual void* AllocImpl(size_t size, size_t alignment) = 0;
    virtual void FreeImpl(void* ptr) = 0;
};

}  // namespace ore
