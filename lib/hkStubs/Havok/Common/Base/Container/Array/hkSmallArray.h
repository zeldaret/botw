#pragma once

#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

template <typename T>
class hkSmallArray {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkSmallArray)

    enum : int {
        CAPACITY_MASK = hkUint16(0x3fff),
        FLAG_MASK = hkUint16(0xC000),
        DONT_DEALLOCATE_FLAG = hkUint16(0x8000),
        LOCKED_FLAG = hkUint16(0x4000),
    };

    HK_FORCE_INLINE hkSmallArray();
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    explicit hkSmallArray(hkFinishLoadedObjectFlag f) {}

    hkSmallArray(const hkSmallArray&) = delete;
    auto operator=(const hkSmallArray&) = delete;

    HK_FORCE_INLINE ~hkSmallArray();

    HK_FORCE_INLINE int getSize() const;
    HK_FORCE_INLINE int getCapacity() const;

    HK_FORCE_INLINE T& operator[](int i);
    HK_FORCE_INLINE const T& operator[](int i) const;

protected:
    void releaseMemory();

    T* m_data;
    hkUint16 m_size;
    hkUint16 m_capacityAndFlags;
};

template <typename T>
inline hkSmallArray<T>::hkSmallArray()
    : m_data(nullptr), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}

template <typename T>
inline hkSmallArray<T>::~hkSmallArray() {
    releaseMemory();
}

template <typename T>
inline int hkSmallArray<T>::getSize() const {
    return m_size;
}

template <typename T>
inline int hkSmallArray<T>::getCapacity() const {
    return m_capacityAndFlags & CAPACITY_MASK;
}

template <typename T>
inline T& hkSmallArray<T>::operator[](int i) {
    return m_data[i];
}

template <typename T>
inline const T& hkSmallArray<T>::operator[](int i) const {
    return m_data[i];
}

template <typename T>
inline void hkSmallArray<T>::releaseMemory() {
    if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
        hkDeallocateChunk(m_data, getCapacity());
}
