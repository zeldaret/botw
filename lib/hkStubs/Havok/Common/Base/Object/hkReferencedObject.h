#pragma once

#include <Havok/Common/Base/Object/hkBaseObject.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>
#include "Havok/Common/Base/Thread/Atomic/hkAtomicPrimitives.h"

class hkClass;

class hkReferencedObject : public hkBaseObject {
public:
    inline hkReferencedObject();
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    explicit hkReferencedObject(hkFinishLoadedObjectFlag flag) {}

    /// Dummy copy constructor and copy assignment operator.
    inline hkReferencedObject(const hkReferencedObject& other);
    inline hkReferencedObject& operator=(const hkReferencedObject& other);

    ~hkReferencedObject() override = default;

    virtual const hkClass* getClassType() const;

    inline int getReferenceCount() const;
    inline void setReferenceCount(int newRefCount);
    inline void addReference() const;
    inline void removeReference() const;

    inline int getAllocatedSize() const;
    inline int getMemorySizeAndFlags() const;
    inline void setMemorySizeAndFlags(int newMemSizeAndFlags);
    inline void setMemorySizeFlagsAndReferenceCount(int newMemSizeAndFlags, int newRefCount);

protected:
    virtual void deleteThisReferencedObject() const;

private:
    mutable hkUint32 m_memSizeAndRefCount;
};

inline hkReferencedObject::hkReferencedObject() : m_memSizeAndRefCount(0xFFFF0001) {}

inline hkReferencedObject::hkReferencedObject(const hkReferencedObject& other)
    : m_memSizeAndRefCount(0xFFFF0001) {}

inline hkReferencedObject& hkReferencedObject::operator=(const hkReferencedObject& other) {
    return *this;
}

inline int hkReferencedObject::getReferenceCount() const {
    return int(m_memSizeAndRefCount & 0xFFFF);
}

inline void hkReferencedObject::setReferenceCount(int newRefCount) {
    hkAtomic::readModifyWrite(&m_memSizeAndRefCount, [newRefCount](hkUint32 oldVal) {
        return (oldVal & 0xFFFF0000) | (newRefCount & 0xFFFF);
    });
}

inline void hkReferencedObject::addReference() const {
    if (getMemorySizeAndFlags() == 0)
        return;

    hkAtomic::readModifyWrite(&m_memSizeAndRefCount, [](hkUint32 oldVal) {
        return (oldVal & 0xFFFF0000) | (((oldVal & 0xFFFF) + 1) & 0xFFFF);
    });
}

inline void hkReferencedObject::removeReference() const {
    if (getMemorySizeAndFlags() == 0)
        return;

    auto newVal = hkAtomic::readModifyWrite(&m_memSizeAndRefCount, [](hkUint32 oldVal) {
        return (oldVal & 0xFFFF0000) | (((oldVal & 0xFFFF) - 1) & 0xFFFF);
    });

    if ((newVal & 0xFFFF) == 0)
        deleteThisReferencedObject();
}

inline int hkReferencedObject::getAllocatedSize() const {
    return getMemorySizeAndFlags() & 0x7FFF;
}

inline int hkReferencedObject::getMemorySizeAndFlags() const {
    return int((m_memSizeAndRefCount >> 16) & 0xFFFF);
}

inline void hkReferencedObject::setMemorySizeAndFlags(int newMemSizeAndFlags) {
    hkAtomic::readModifyWrite(&m_memSizeAndRefCount, [=](hkUint32 oldVal) {
        return (newMemSizeAndFlags << 16) | (oldVal & 0xFFFF);
    });
}

inline void hkReferencedObject::setMemorySizeFlagsAndReferenceCount(int newMemSizeAndFlags,
                                                                    int newRefCount) {
    const hkUint32 newVal = (newMemSizeAndFlags << 16) | (newRefCount & 0xFFFF);
    hkAtomic::readModifyWrite(&m_memSizeAndRefCount, [=](auto) { return newVal; });
}
