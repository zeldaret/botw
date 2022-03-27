#pragma once

#include <Havok/Common/Base/Types/hkBaseTypes.h>

#define HK_DECLARE_PLACEMENT_ALLOCATOR()                                                           \
    HK_FORCE_INLINE void* operator new(hk_size_t, void* p) { return p; }                           \
    HK_FORCE_INLINE void operator delete(void*, void*) {}                                          \
    HK_FORCE_INLINE void operator delete(void*, hk_size_t) {}

class hkMemorySnapshot;

template <typename T>
struct hkSizeOfTypeOrVoid {
    enum { val = sizeof(T) };
};

template <>
struct hkSizeOfTypeOrVoid<void> {
    enum { val = 1 };
};

class hkMemoryAllocator {
public:
    HK_DECLARE_PLACEMENT_ALLOCATOR()

    using MemoryWalkCallback = void (*)(void* start, hk_size_t size, bool allocated, int pool,
                                        void* param);

    struct MemoryStatistics {
        static const hkLong INFINITE_SIZE = -1;

        hkLong m_allocated = -1;
        hkLong m_inUse = -1;
        hkLong m_peakInUse = -1;
        hkLong m_available = -1;
        hkLong m_totalAvailable = -1;
        hkLong m_largestBlock = -1;
    };

    struct ExtendedInterface {
        virtual ~ExtendedInterface() = default;

        virtual void garbageCollect() = 0;
        virtual void incrementalGarbageCollect(int numBlocks) = 0;
        virtual hkResult setMemorySoftLimit(hk_size_t maxMemory) = 0;
        virtual hk_size_t getMemorySoftLimit() const = 0;
        virtual bool canAllocTotal(int numBytes) = 0;
        virtual hkResult walkMemory(MemoryWalkCallback callback, void* param) = 0;
        virtual hk_size_t getApproxTotalAllocated() const = 0;
        virtual void setScrubValues(hkUint32 allocValue, hkUint32 freeValue) = 0;
        virtual int addToSnapshot(hkMemorySnapshot& snap, int parentId) = 0;
    };

    virtual ~hkMemoryAllocator();

    virtual void* blockAlloc(int numBytes) = 0;
    virtual void blockFree(void* p, int numBytes) = 0;
    virtual void* bufAlloc(int& reqNumBytesInOut);
    virtual void bufFree(void* p, int numBytes);
    virtual void* bufRealloc(void* pold, int oldNumBytes, int& reqNumBytesInOut);

    virtual void blockAllocBatch(void** ptrsOut, int numPtrs, int blockSize);
    virtual void blockFreeBatch(void** ptrsIn, int numPtrs, int blockSize);

    virtual void getMemoryStatistics(MemoryStatistics& u) const = 0;
    virtual int getAllocatedSize(const void* obj, int nbytes) const = 0;
    virtual void resetPeakMemoryStatistics() {}

    virtual ExtendedInterface* getExtendedInterface() { return nullptr; }

    template <typename TYPE>
    inline TYPE* _bufAlloc(int& reqNumInOut) {
        const int SIZE_ELEM = hkSizeOfTypeOrVoid<TYPE>::val;
        int n = reqNumInOut * SIZE_ELEM;
        void* p = bufAlloc(n);
        reqNumInOut = n / SIZE_ELEM;
        return static_cast<TYPE*>(p);
    }

    template <typename TYPE>
    inline void _bufFree(void* p, int numElem) {
        const int SIZE_ELEM = hkSizeOfTypeOrVoid<TYPE>::val;
        bufFree(p, numElem * SIZE_ELEM);
    }

    template <typename TYPE>
    inline TYPE* _bufRealloc(void* pold, int oldNum, int& reqNumInOut) {
        const int SIZE_ELEM = hkSizeOfTypeOrVoid<TYPE>::val;
        int n = reqNumInOut * SIZE_ELEM;
        void* p = bufRealloc(pold, oldNum * SIZE_ELEM, n);
        reqNumInOut = n / SIZE_ELEM;
        return static_cast<TYPE*>(p);
    }

    template <typename TYPE>
    inline TYPE* _blockAlloc(int n) {
        return static_cast<TYPE*>(blockAlloc(n * hkSizeOfTypeOrVoid<TYPE>::val));
    }

    template <typename TYPE>
    inline void _blockFree(TYPE* p, int n) {
        blockFree(p, n * hkSizeOfTypeOrVoid<TYPE>::val);
    }

    enum MemoryState {
        MEMORY_STATE_OK,
        MEMORY_STATE_OUT_OF_MEMORY,
    };
};
