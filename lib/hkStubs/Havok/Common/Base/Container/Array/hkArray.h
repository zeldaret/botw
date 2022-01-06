#pragma once

#include <Havok/Common/Base/Container/Array/hkArrayUtil.h>
#include <Havok/Common/Base/Container/hkContainerAllocators.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>
#include <type_traits>

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
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    explicit hkArrayBase(hkFinishLoadedObjectFlag f) {}

    HK_FORCE_INLINE ~hkArrayBase();

    hkArrayBase(const hkArrayBase&) = delete;
    auto operator=(const hkArrayBase&) = delete;

    HK_FORCE_INLINE int getSize() const;
    HK_FORCE_INLINE int getCapacity() const;
    HK_FORCE_INLINE int getCapacityAndFlags() const;
    HK_FORCE_INLINE hkBool isEmpty() const;

    HK_FORCE_INLINE void clear();
    HK_FORCE_INLINE void _clearAndDeallocate(hkMemoryAllocator& allocator);

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

    HK_FORCE_INLINE ~hkArray() { clearAndDeallocate(); }

    HK_FORCE_INLINE hkArray& operator=(const hkArrayBase<T>& other);
    HK_FORCE_INLINE hkArray& operator=(const hkArray& other);

    HK_FORCE_INLINE void clearAndDeallocate();

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

template <typename T>
inline int hkArrayBase<T>::getSize() const {
    return m_size;
}

template <typename T>
inline int hkArrayBase<T>::getCapacity() const {
    return m_capacityAndFlags & static_cast<int>(CAPACITY_MASK);
}

template <typename T>
inline int hkArrayBase<T>::getCapacityAndFlags() const {
    return m_capacityAndFlags;
}

template <typename T>
inline hkBool hkArrayBase<T>::isEmpty() const {
    return m_size == 0;
}

template <typename T>
inline void hkArrayBase<T>::clear() {
    hkArrayUtil::destruct(m_data, m_size);
    m_size = 0;
}

template <typename T>
inline void hkArrayBase<T>::_clearAndDeallocate(hkMemoryAllocator& allocator) {
    clear();
    if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0) {
        const int SIZE_ELEM = hkSizeOfTypeOrVoid<T>::val;
        int numBytes = getCapacity() * SIZE_ELEM;
        void* storage = const_cast<std::remove_const_t<T>*>(m_data);
        allocator.bufFree(storage, numBytes);
    }
    m_data = nullptr;
    m_capacityAndFlags = DONT_DEALLOCATE_FLAG;
}

template <typename T, typename Allocator>
inline void hkArray<T, Allocator>::clearAndDeallocate() {
    this->_clearAndDeallocate(AllocatorType().get());
}
