#pragma once

#include <Havok/Common/Base/Container/Array/hkArrayUtil.h>
#include <Havok/Common/Base/Container/hkContainerAllocators.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>
#include <type_traits>

/// Base class for hkArray (a std::vector-like container).
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
    HK_FORCE_INLINE hkArrayBase(T* buffer, int size, int capacity);

    HK_FORCE_INLINE ~hkArrayBase();

    hkArrayBase(const hkArrayBase&) = delete;
    auto operator=(const hkArrayBase&) = delete;

    HK_FORCE_INLINE int getSize() const;
    HK_FORCE_INLINE int getCapacity() const;
    HK_FORCE_INLINE int getCapacityAndFlags() const;
    HK_FORCE_INLINE hkBool isEmpty() const;

    HK_FORCE_INLINE T& operator[](int i);
    HK_FORCE_INLINE const T& operator[](int i) const;

    HK_FORCE_INLINE T& back();
    HK_FORCE_INLINE const T& back() const;

    HK_FORCE_INLINE void clear();
    HK_FORCE_INLINE void _clearAndDeallocate(hkMemoryAllocator& allocator);
    HK_FORCE_INLINE void removeAt(int index);
    HK_FORCE_INLINE void removeAtAndCopy(int index);
    HK_FORCE_INLINE void removeAtAndCopy(int index, int numToRemove);

    HK_FORCE_INLINE int indexOf(const T& t, int start = 0, int end = -1) const;
    HK_FORCE_INLINE int lastIndexOf(const T& t) const;

    HK_FORCE_INLINE void popBack(int numElemsToRemove = 1);
    HK_FORCE_INLINE void _pushBack(hkMemoryAllocator& alloc, const T& e);
    HK_FORCE_INLINE void pushBackUnchecked(const T& e);
    HK_FORCE_INLINE hkBool tryPushBack(const T& t);

    HK_FORCE_INLINE hkResult _reserve(hkMemoryAllocator& alloc, int n);
    HK_FORCE_INLINE hkResult _reserveExactly(hkMemoryAllocator& alloc, int n);

    HK_FORCE_INLINE void _setSize(hkMemoryAllocator& alloc, int size);
    HK_FORCE_INLINE void _setSize(hkMemoryAllocator& alloc, int n, const T& fill);
    HK_FORCE_INLINE hkResult _trySetSize(hkMemoryAllocator& alloc, int size);
    HK_FORCE_INLINE void setSizeUnchecked(int size);

    HK_FORCE_INLINE T& _expandOne(hkMemoryAllocator& alloc);
    HK_FORCE_INLINE T* _expandBy(hkMemoryAllocator& alloc, int n);
    HK_FORCE_INLINE T* expandByUnchecked(int n);
    HK_FORCE_INLINE T* _expandAt(hkMemoryAllocator& alloc, int index, int numToInsert);

    void _insertAt(hkMemoryAllocator& alloc, int i, const T* a, int numElems);
    void _insertAt(hkMemoryAllocator& alloc, int i, const T& t);

    void _append(hkMemoryAllocator& alloc, const T* a, int numElems);
    void _spliceInto(hkMemoryAllocator& alloc, int i, int ndel, const T* p, int numElems);

    HK_FORCE_INLINE void removeAllAndCopy(const T& t);

    using iterator = T*;
    using const_iterator = const T*;

    HK_FORCE_INLINE iterator begin();
    HK_FORCE_INLINE iterator end();
    HK_FORCE_INLINE const_iterator begin() const;
    HK_FORCE_INLINE const_iterator end() const;

    static HK_FORCE_INLINE void copy(T* dst, const T* src, int n);

    HK_FORCE_INLINE void setDataAutoFree(T* ptr, int size, int capacity);
    HK_FORCE_INLINE void setDataUserFree(T* ptr, int size, int capacity);
    HK_FORCE_INLINE void _setDataUnchecked(T* ptr, int size, int capacityAndFlags);
    HK_FORCE_INLINE void _optimizeCapacity(hkMemoryAllocator& alloc, int numFreeElemsLeft,
                                           hkBool32 shrinkExact = false);

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
    HK_FORCE_INLINE void pushBack(const T& e);

protected:
    HK_FORCE_INLINE hkArray(const hkArray& other);
};

template <typename T>
inline hkArrayBase<T>::hkArrayBase()
    : m_data(nullptr), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}

template <typename T>
inline hkArrayBase<T>::hkArrayBase(T* buffer, int size, int capacity)
    : m_data(buffer), m_size(size), m_capacityAndFlags(capacity | DONT_DEALLOCATE_FLAG) {}

template <typename T>
inline hkArrayBase<T>::~hkArrayBase() = default;

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
inline T& hkArrayBase<T>::operator[](int i) {
    return m_data[i];
}

template <typename T>
inline const T& hkArrayBase<T>::operator[](int i) const {
    return m_data[i];
}

template <typename T>
inline T& hkArrayBase<T>::back() {
    return m_data[m_size - 1];
}

template <typename T>
inline const T& hkArrayBase<T>::back() const {
    return m_data[m_size - 1];
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

template <typename T>
inline void hkArrayBase<T>::popBack(int numElemsToRemove) {
    hkArrayUtil::destruct(m_data + m_size - numElemsToRemove, numElemsToRemove);
    m_size -= numElemsToRemove;
}

template <typename T>
inline void hkArrayBase<T>::_pushBack(hkMemoryAllocator& alloc, const T& e) {
    if (m_size == getCapacity()) {
        hkArrayUtil::_reserveMore(alloc, this, sizeof(T));
    }
    pushBackUnchecked(e);
}

template <typename T>
inline void hkArrayBase<T>::pushBackUnchecked(const T& e) {
    hkArrayUtil::constructWithCopy<T>(m_data + m_size, 1, e);
    m_size++;
}

template <typename T>
inline hkBool hkArrayBase<T>::tryPushBack(const T& t) {
    if (m_size < getCapacity()) {
        hkArrayUtil::constructWithCopy(m_data + m_size, 1, t);
        m_size++;
        return true;
    }
    return false;
}

template <typename T>
inline typename hkArrayBase<T>::iterator hkArrayBase<T>::begin() {
    return m_data;
}

template <typename T>
inline typename hkArrayBase<T>::iterator hkArrayBase<T>::end() {
    return m_data + m_size;
}

template <typename T>
inline typename hkArrayBase<T>::const_iterator hkArrayBase<T>::begin() const {
    return m_data;
}

template <typename T>
inline typename hkArrayBase<T>::const_iterator hkArrayBase<T>::end() const {
    return m_data + m_size;
}

template <typename T>
inline void hkArrayBase<T>::copy(T* dst, const T* src, int n) {
    for (int i = 0; i < n; ++i) {
        dst[i] = src[i];
    }
}

template <typename T>
inline void hkArrayBase<T>::_setDataUnchecked(T* ptr, int size, int capacityAndFlags) {
    m_data = ptr;
    m_size = size;
    m_capacityAndFlags = capacityAndFlags;
}

template <typename T>
inline void hkArrayBase<T>::setDataAutoFree(T* ptr, int size, int capacity) {
    static_assert(std::is_pod_v<T>, "T must be a POD type");
    _setDataUnchecked(ptr, size, capacity);
}

template <typename T>
inline void hkArrayBase<T>::setDataUserFree(T* ptr, int size, int capacity) {
    static_assert(std::is_pod_v<T>, "T must be a POD type");
    _setDataUnchecked(ptr, size, capacity | DONT_DEALLOCATE_FLAG);
}

template <typename T, typename Allocator>
inline void hkArray<T, Allocator>::clearAndDeallocate() {
    this->_clearAndDeallocate(AllocatorType().get());
}

template <typename T, typename Allocator>
inline void hkArray<T, Allocator>::pushBack(const T& e) {
    this->_pushBack(AllocatorType().get(), e);
}
