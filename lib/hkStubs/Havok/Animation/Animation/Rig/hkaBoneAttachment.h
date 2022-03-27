#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkaBoneAttachment : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaBoneAttachment)
    HK_DECLARE_REFLECTION()

    inline hkaBoneAttachment() : m_originalSkeletonName(nullptr), m_boneIndex(-1) {}

    HK_FORCE_INLINE explicit hkaBoneAttachment(hkFinishLoadedObjectFlag f)
        : hkReferencedObject(f), m_originalSkeletonName(f), m_attachment(f), m_name(f) {}

    // Optional.
    hkStringPtr m_originalSkeletonName;
    hkMatrix4 m_boneFromAttachment;
    hkRefVariant m_attachment;
    hkStringPtr m_name;
    hkInt16 m_boneIndex;
};
