#pragma once

#include <Havok/Common/Base/Object/hkReferencedObject.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <utility>

/// Owning reference. Assign to a hkRefPtr as soon as possible.
/// @warning This will NOT automatically destruct the contained object.
template <typename T>
class hkRefNew {
public:
    hkRefNew(T* ptr) : m_ptr(ptr) {}  // NOLINT(google-explicit-constructor)

    hkRefNew(const hkRefNew&) = delete;
    auto operator=(const hkRefNew&) = delete;

    T* release() { return std::exchange(m_ptr, nullptr); }

private:
    T* m_ptr;
};

/// A simple reference counting pointer intended to be used with hkReferencedObjects.
template <typename T>
class hkRefPtr {
public:
    /// Default constructor. Initializes the pointer to nullptr.
    HK_FORCE_INLINE hkRefPtr();
    /// Copy constructor. Increments the reference count.
    HK_FORCE_INLINE hkRefPtr(const hkRefPtr& other);
    HK_FORCE_INLINE hkRefPtr(T* ptr);  // NOLINT(google-explicit-constructor)
    /// "Move" constructor. Steals the reference from ptr.
    HK_FORCE_INLINE hkRefPtr(hkRefNew<T> ptr);  // NOLINT(google-explicit-constructor)

    HK_FORCE_INLINE explicit hkRefPtr(hkFinishLoadedObjectFlag);

    /// Decrements the reference count.
    HK_FORCE_INLINE ~hkRefPtr();

    HK_FORCE_INLINE hkRefPtr& operator=(const hkRefPtr& other);
    HK_FORCE_INLINE hkRefPtr& operator=(T* ptr);
    HK_FORCE_INLINE hkRefPtr& operator=(hkRefNew<T> ptr);

    HK_FORCE_INLINE T* val() const;
    HK_FORCE_INLINE T* operator->() const;
    HK_FORCE_INLINE operator T*() const;  // NOLINT(google-explicit-constructor)

    HK_FORCE_INLINE void setAndDontIncrementRefCount(T* ptr);
    HK_FORCE_INLINE void unsetAndDontDecrementRefCount();

private:
    void addReference() const {
        if (m_ptr)
            m_ptr->addReference();
    }

    void removeReference() const {
        if (m_ptr)
            m_ptr->removeReference();
    }

    T* m_ptr;
};

template <typename T>
inline hkRefPtr<T>::hkRefPtr() : m_ptr(nullptr) {}

template <typename T>
inline hkRefPtr<T>::hkRefPtr(const hkRefPtr& other) {
    other.addReference();
    m_ptr = other.m_ptr;
}

template <typename T>
inline hkRefPtr<T>::hkRefPtr(T* ptr) {
    if (ptr)
        ptr->addReference();
    m_ptr = ptr;
}

template <typename T>
inline hkRefPtr<T>::hkRefPtr(hkRefNew<T> ptr) : m_ptr(ptr.release()) {}

template <typename T>
inline hkRefPtr<T>::hkRefPtr(hkFinishLoadedObjectFlag) {}

template <typename T>
inline hkRefPtr<T>::~hkRefPtr() {
    removeReference();
    m_ptr = nullptr;
}

template <typename T>
// NOLINTNEXTLINE(bugprone-unhandled-self-assignment)
inline hkRefPtr<T>& hkRefPtr<T>::operator=(const hkRefPtr& other) {
    other.addReference();
    removeReference();
    m_ptr = other.m_ptr;
    return *this;
}

template <typename T>
inline hkRefPtr<T>& hkRefPtr<T>::operator=(T* ptr) {
    if (ptr)
        ptr->addReference();
    removeReference();
    m_ptr = ptr;
    return *this;
}

template <typename T>
inline hkRefPtr<T>& hkRefPtr<T>::operator=(hkRefNew<T> ptr) {
    removeReference();
    m_ptr = ptr.release();
    return *this;
}

template <typename T>
inline T* hkRefPtr<T>::val() const {
    return m_ptr;
}

template <typename T>
inline T* hkRefPtr<T>::operator->() const {
    return val();
}

template <typename T>
inline hkRefPtr<T>::operator T*() const {
    return val();
}

template <typename T>
inline void hkRefPtr<T>::setAndDontIncrementRefCount(T* ptr) {
    if (m_ptr && m_ptr != ptr)
        m_ptr->removeReference();
    m_ptr = ptr;
}

template <typename T>
inline void hkRefPtr<T>::unsetAndDontDecrementRefCount() {
    m_ptr = nullptr;
}
