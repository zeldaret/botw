#pragma once

#include <Havok/Common/Base/Container/hkContainerAllocators.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

/// Base class for hkArray (a std::vector-like container).
// FIXME: incomplete
template <typename T>
class hkArrayBase {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkArrayBase<T>)

    enum : unsigned int {
        CAPACITY_MASK = 0x3FFFFFFF,
        FLAG_MASK = 0xC0000000,
        DONT_DEALLOCATE_FLAG = 0x80000000,
    };

    HK_FORCE_INLINE hkArrayBase();
    explicit hkArrayBase(hkFinishLoadedObjectFlag f) {}

    HK_FORCE_INLINE ~hkArrayBase();

    hkArrayBase(const hkArrayBase&) = delete;
    auto operator=(const hkArrayBase&) = delete;

protected:
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
};

/// A dynamically resizable array, similar to std::vector.
// FIXME: incomplete
template <typename T, typename Allocator = hkContainerHeapAllocator>
class hkArray : public hkArrayBase<T> {
public:
    using AllocatorType = Allocator;

    HK_FORCE_INLINE hkArray() = default;
    explicit hkArray(hkFinishLoadedObjectFlag f) : hkArrayBase<T>(f) {}

    HK_FORCE_INLINE ~hkArray();

    HK_FORCE_INLINE hkArray& operator=(const hkArrayBase<T>& other);
    HK_FORCE_INLINE hkArray& operator=(const hkArray& other);

protected:
    HK_FORCE_INLINE hkArray(const hkArray& other);
};

template <typename T>
inline hkArrayBase<T>::hkArrayBase()
    : m_data(nullptr), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}

template <typename T>
inline hkArrayBase<T>::~hkArrayBase() {
    // Assert non-POD element destruction
}
