#pragma once

#include <Havok/Common/Base/Memory/Allocator/Lifo/hkLifoAllocator.h>
#include <Havok/Common/Base/Memory/Allocator/hkMemoryAllocator.h>
#include <Havok/Common/Base/Object/hkReferencedObject.h>
#include <Havok/Common/Base/Thread/Thread/hkThreadLocalData.h>
#include <type_traits>

class hkLifoAllocator;

class hkOstream;

class hkMemoryRouter {
public:
    using Stack = hkLifoAllocator;
    using Allocator = hkMemoryAllocator;

    static void replaceInstance(hkMemoryRouter* m);

    static inline hkMemoryRouter& getInstance() { return *getInstancePtr(); }
    static inline hkMemoryRouter* getInstancePtr() { return HK_THREAD_LOCAL_GET(s_memoryRouter); }

    hkMemoryRouter();

    void resetPeakMemoryStatistics();

    /// Small thread local allocation in a stack pattern.
    inline Stack& stack() { return m_stack; }

    /// Temporary allocation, thread local. Often but not always in a stack pattern.
    inline Allocator& temp() { return *m_temp; }
    inline void setTemp(Allocator* a) { m_temp = a; }

    /// Allocation which is likely to persist. Not thread local.
    inline Allocator& heap() { return *m_heap; }
    inline void setHeap(Allocator* a) { m_heap = a; }

    /// Allocation which may break the rules. Not thread local.
    inline Allocator& debug() { return *m_debug; }
    inline void setDebug(Allocator* a) { m_debug = a; }

    inline Allocator& solver() { return *m_solver; }
    inline void setSolver(Allocator* a) { m_solver = a; }

    inline void* getUserData() const { return m_userData; }
    inline void setUserData(void* p) { m_userData = p; }

    inline const hkUint32* getRefObjectLocalStore() const { return &m_refObjLocalStore; }
    inline hkUint32* getRefObjectLocalStore() { return &m_refObjLocalStore; }

    static void* alignedAlloc(Allocator& b, int nbytes, int align);
    static void alignedFree(Allocator& b, void* p);

    static void* easyAlloc(Allocator& b, int nbytes);
    static hk_size_t getEasyAllocSize(Allocator& b, const void* ptr);
    static const void* getEasyAllocStartAddress(Allocator& b, const void* ptr);
    static void easyFree(Allocator& b, void* p);

protected:
    Stack m_stack;

    Allocator* m_temp;
    Allocator* m_heap;
    Allocator* m_debug;
    Allocator* m_solver;

    void* m_userData;
    hkUint32 m_refObjLocalStore;

    static HK_THREAD_LOCAL(hkMemoryRouter*) s_memoryRouter;
};

template <typename TYPE>
HK_FORCE_INLINE TYPE* hkAllocateChunk(int numberOfObjects) {
    return static_cast<TYPE*>(hkMemoryRouter::getInstance().heap().blockAlloc(
        numberOfObjects * hkSizeOfTypeOrVoid<TYPE>::val));
}

template <typename TYPE>
HK_FORCE_INLINE void hkDeallocateChunk(TYPE* ptr, int numberOfObjects) {
    hkMemoryRouter::getInstance().heap().blockFree(static_cast<void*>(ptr),
                                                   numberOfObjects * hkSizeOfTypeOrVoid<TYPE>::val);
}

#define HK_DECLARE_CLASS_ALLOCATOR_IMPL(CLASS_TYPE, ALLOCATOR)                                     \
    /* clang-tidy fails to understand that the operator delete matches the operator new  */        \
    /* NOLINTNEXTLINE(misc-new-delete-overloads) */                                                \
    HK_FORCE_INLINE void* operator new(hk_size_t nbytes) {                                         \
        if constexpr (std::is_base_of_v<hkReferencedObject, CLASS_TYPE>) {                         \
            return hkMemoryRouter::getInstance().ALLOCATOR().blockAlloc(static_cast<int>(nbytes)); \
        } else {                                                                                   \
            return hkMemoryRouter::getInstance().ALLOCATOR().blockAlloc(sizeof(CLASS_TYPE));       \
        }                                                                                          \
    }                                                                                              \
    HK_FORCE_INLINE void operator delete(void* p, hk_size_t nbytes) {                              \
        if constexpr (std::is_base_of_v<hkReferencedObject, CLASS_TYPE>) {                         \
            auto* b = static_cast<hkReferencedObject*>(p);                                         \
            hkMemoryRouter::getInstance().ALLOCATOR().blockFree(                                   \
                p, (b->getMemorySizeAndFlags() == 0xffff) ? static_cast<int>(nbytes) :             \
                                                            b->getMemorySizeAndFlags());           \
        } else {                                                                                   \
            if (p)                                                                                 \
                hkMemoryRouter::getInstance().ALLOCATOR().blockFree(p, sizeof(CLASS_TYPE));        \
        }                                                                                          \
    }                                                                                              \
    HK_FORCE_INLINE void* operator new(hk_size_t, void* p) { return p; }                           \
    HK_FORCE_INLINE void* operator new[](hk_size_t, void* p) { return p; }                         \
    HK_FORCE_INLINE void operator delete(void*, void*) {}                                          \
    HK_FORCE_INLINE void operator delete[](void*, void*) {}

#define HK_DECLARE_CLASS_ALLOCATOR(CLASS_TYPE) HK_DECLARE_CLASS_ALLOCATOR_IMPL(CLASS_TYPE, heap)

#define HK_DECLARE_CLASS_DEBUG_ALLOCATOR(CLASS_TYPE)                                               \
    HK_DECLARE_CLASS_ALLOCATOR_IMPL(CLASS_TYPE, debug)
