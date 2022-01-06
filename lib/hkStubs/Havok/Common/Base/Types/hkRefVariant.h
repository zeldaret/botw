#pragma once

#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>
#include <Havok/Common/Base/Types/hkRefPtr.h>

class hkRefVariant : public hkRefPtr<hkReferencedObject> {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkRefVariant)

    HK_FORCE_INLINE hkRefVariant() = default;
    // NOLINTNEXTLINE(google-explicit-constructor)
    HK_FORCE_INLINE hkRefVariant(const hkReferencedObject* o);
    HK_FORCE_INLINE hkRefVariant(const hkRefVariant& other);

    // NOLINTNEXTLINE(google-explicit-constructor)
    hkRefVariant(const hkVariant& v);
    hkRefVariant(void* o, const hkClass* k);
    HK_FORCE_INLINE explicit hkRefVariant(hkFinishLoadedObjectFlag f);

    HK_FORCE_INLINE hkRefVariant& operator=(const hkRefVariant& other);
    HK_FORCE_INLINE hkRefVariant& operator=(const hkReferencedObject* o);

    void set(void* o, const hkClass* k);

    HK_FORCE_INLINE operator hkVariant() const;  // NOLINT(google-explicit-constructor)
    const hkClass* getClass() const;
};

inline hkRefVariant::hkRefVariant(const hkReferencedObject* o)
    : hkRefPtr(const_cast<hkReferencedObject*>(o)) {}

inline hkRefVariant::hkRefVariant(const hkRefVariant& other) = default;

inline hkRefVariant::hkRefVariant(hkFinishLoadedObjectFlag f) : hkRefPtr(f) {}

inline hkRefVariant& hkRefVariant::operator=(const hkRefVariant& other) {
    if (this != &other)
        hkRefPtr::operator=(other);
    return *this;
}

inline hkRefVariant& hkRefVariant::operator=(const hkReferencedObject* o) {
    if (val() != o)
        hkRefPtr::operator=(const_cast<hkReferencedObject*>(o));
    return *this;
}

inline hkRefVariant::operator hkVariant() const {
    hkVariant v;
    v.m_object = const_cast<hkReferencedObject*>(val());
    v.m_class = getClass();
    return v;
}
