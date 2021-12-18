#pragma once

#include <Havok/Common/Base/Memory/Allocator/hkMemoryAllocator.h>
#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>

struct hkContainerHeapAllocator {
    HK_DECLARE_CLASS_ALLOCATOR(hkContainerHeapAllocator)

    struct Allocator : hkMemoryAllocator {
        HK_DECLARE_CLASS_ALLOCATOR(Allocator)

        void* blockAlloc(int numBytes) override;
        void blockFree(void* p, int numBytes) override;
        void* bufAlloc(int& reqNumBytesInOut) override;
        void bufFree(void* p, int numBytes) override;
        void* bufRealloc(void* pold, int oldNumBytes, int& reqNumBytesInOut) override;
        void getMemoryStatistics(MemoryStatistics& u) const override;
        int getAllocatedSize(const void* obj, int nbytes) const override;
    };

    static Allocator s_alloc;
    static hkMemoryAllocator& get() { return s_alloc; }
};
