#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <new>

class hkArrayUtil {
public:
    template <typename T>
    static HK_FORCE_INLINE void construct(T* t, int n);

    template <typename T>
    static HK_FORCE_INLINE void constructWithCopy(T* t, int n, const T& tcopy);

    template <typename T>
    static HK_FORCE_INLINE void constructWithArray(T* t, int n, const T* tcopy);

    template <typename T>
    static HK_FORCE_INLINE void destruct(T* t, int n);

    static hkResult _reserve(hkMemoryAllocator& a, void*, int reqElem, int sizeElem);
    static void _reserveMore(hkMemoryAllocator& a, void* array, int sizeElem);
    static void _reduce(hkMemoryAllocator& a, void* array, int sizeElem, char* inplaceMem,
                        int requestedCapacity);
};

template <typename T>
inline void hkArrayUtil::construct(T* t, int n) {
    for (int i = 0; i < n; ++i) {
        ::new (static_cast<void*>(t + i)) T;
    }
}

template <typename T>
inline void hkArrayUtil::constructWithCopy(T* t, int n, const T& tcopy) {
    for (int i = 0; i < n; ++i) {
        ::new (static_cast<void*>(t + i)) T(tcopy);
    }
}

template <typename T>
inline void hkArrayUtil::constructWithArray(T* t, int n, const T* tcopy) {
    for (int i = 0; i < n; ++i) {
        ::new (static_cast<void*>(t + i)) T(tcopy[i]);
    }
}

template <typename T>
inline void hkArrayUtil::destruct(T* t, int n) {
    for (int i = n - 1; i >= 0; --i) {
        static_cast<T*>(t)[i].~T();
    }
}
