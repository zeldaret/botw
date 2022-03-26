#pragma once

#include <Havok/Animation/Animation/Animation/hkaAnimation.h>
#include <Havok/Animation/Animation/Rig/hkaSkeleton.h>
#include <Havok/Common/Base/hkBase.h>

class hkaAnimationBinding : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaAnimationBinding)
    HK_DECLARE_REFLECTION()

    enum BlendHint {
        NORMAL = 0,
        ADDITIVE_DEPRECATED = 1,
        ADDITIVE = 2,
    };

    HK_FORCE_INLINE hkaAnimationBinding();
    HK_FORCE_INLINE hkaAnimationBinding(const hkaAnimationBinding& other);
    HK_FORCE_INLINE explicit hkaAnimationBinding(hkFinishLoadedObjectFlag flag);

    hkInt16 findTrackIndexFromBoneIndex(hkInt16 boneIndex) const;
    hkInt16 findTrackIndexFromSlotIndex(hkInt16 slotIndex) const;

    static hkInt16 findTrackIndexFromBoneIndex(hkInt16 boneIndex, hkInt32 numTracks,
                                               const hkInt16* trackToBoneIndices);

    bool isMonotonic() const;

    void setIdentity();

    hkStringPtr m_originalSkeletonName;
    hkRefPtr<hkaAnimation> m_animation;
    hkArray<hkInt16> m_transformTrackToBoneIndices;
    hkArray<hkInt16> m_floatTrackToFloatSlotIndices;
    hkArray<hkInt16> m_partitionIndices;
    hkEnum<BlendHint, hkInt8> m_blendHint;
};

inline hkaAnimationBinding::hkaAnimationBinding() : m_blendHint(NORMAL) {}

inline hkaAnimationBinding::hkaAnimationBinding(const hkaAnimationBinding& other)
    : hkReferencedObject(other), m_originalSkeletonName(other.m_originalSkeletonName),
      m_animation(other.m_animation), m_blendHint(other.m_blendHint) {
    m_transformTrackToBoneIndices = other.m_transformTrackToBoneIndices;
    m_floatTrackToFloatSlotIndices = other.m_floatTrackToFloatSlotIndices;
    m_partitionIndices = other.m_partitionIndices;
}

inline hkaAnimationBinding::hkaAnimationBinding(hkFinishLoadedObjectFlag flag)
    : hkReferencedObject(flag), m_originalSkeletonName(flag), m_animation(flag),
      m_transformTrackToBoneIndices(flag), m_floatTrackToFloatSlotIndices(flag),
      m_partitionIndices(flag) {}
