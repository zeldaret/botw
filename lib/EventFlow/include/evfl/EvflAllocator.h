#pragma once

#include <ore/Allocator.h>

namespace evfl {

struct AllocateArg {
    void* (*alloc)(size_t size, size_t alignment, void* userdata);
    void (*free)(void* ptr, void* userdata);
    void* alloc_userdata;
    void* free_userdata;
};

class EvflAllocator : public ore::Allocator {
public:
    EvflAllocator() = default;
    explicit EvflAllocator(AllocateArg arg) : m_arg(arg) {}

    void* AllocImpl(size_t size, size_t alignment) override {
        return m_arg.alloc(size, alignment, m_arg.alloc_userdata);
    }

    void FreeImpl(void* ptr) override { m_arg.free(ptr, m_arg.free_userdata); }

    AllocateArg GetArg() const { return m_arg; }

private:
    AllocateArg m_arg;
};

}  // namespace evfl
