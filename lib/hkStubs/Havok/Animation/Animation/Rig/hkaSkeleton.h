#pragma once

#include <Havok/Animation/Animation/Rig/hkaBone.h>
#include <Havok/Common/Base/Types/Geometry/LocalFrame/hkLocalFrame.h>
#include <Havok/Common/Base/hkBase.h>

class hkaSkeleton : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaSkeleton)
    HK_DECLARE_REFLECTION()

    struct LocalFrameOnBone {
        HK_DECLARE_CLASS_ALLOCATOR(LocalFrameOnBone)
        HK_DECLARE_REFLECTION()

        hkRefPtr<hkLocalFrame> m_localFrame;
        hkInt16 m_boneIndex;

        HK_FORCE_INLINE LocalFrameOnBone();
        HK_FORCE_INLINE explicit LocalFrameOnBone(hkFinishLoadedObjectFlag f);
    };

    struct Partition {
        HK_DECLARE_CLASS_ALLOCATOR(Partition)
        HK_DECLARE_REFLECTION()

        Partition() : m_name(nullptr), m_startBoneIndex(-1), m_numBones(-1) {}

        Partition(hkInt16 startIndex, hkInt16 numBones)
            : m_name(nullptr), m_startBoneIndex(startIndex), m_numBones(numBones) {}

        explicit Partition(hkFinishLoadedObjectFlag f) : m_name(f) {}

        Partition(const Partition& partition)
            : m_name(partition.m_name), m_startBoneIndex(partition.m_startBoneIndex),
              m_numBones(partition.m_numBones) {}

        Partition& operator=(const Partition& other) = default;

        hkStringPtr m_name;
        hkInt16 m_startBoneIndex;
        hkInt16 m_numBones;

        HK_FORCE_INLINE void initWithoutName(hkInt16 startBoneIndex, hkInt16 numBones);
        HK_FORCE_INLINE hkBool32 isBonePresentWithinPartition(hkInt16 boneIndex) const;
        HK_FORCE_INLINE hkInt16 getEndBoneIndex() const;
    };

    struct PartitionStartBoneLess {
        HK_FORCE_INLINE hkBool operator()(const Partition& a, const Partition& b) {
            return (a.m_startBoneIndex < b.m_startBoneIndex);
        }
    };

    HK_FORCE_INLINE hkaSkeleton();
    HK_FORCE_INLINE hkaSkeleton(const hkaSkeleton& skel);
    HK_FORCE_INLINE explicit hkaSkeleton(hkFinishLoadedObjectFlag f);

    hkLocalFrame* getLocalFrameForBone(int boneIndex) const;

    hkInt16 getPartitionIndexFromName(const char* partitionName) const;

    hkInt16 getPartitionIndexForBone(hkInt16 boneIndex) const;

    hkStringPtr m_name;
    hkArray<hkInt16> m_parentIndices;
    hkArray<hkaBone> m_bones;
    hkArray<hkQsTransform> m_referencePose;
    hkArray<hkReal> m_referenceFloats;
    hkArray<hkStringPtr> m_floatSlots;
    hkArray<LocalFrameOnBone> m_localFrames;
    hkArray<Partition> m_partitions;
};

inline hkaSkeleton::LocalFrameOnBone::LocalFrameOnBone() = default;

inline hkaSkeleton::LocalFrameOnBone::LocalFrameOnBone(hkFinishLoadedObjectFlag f)
    : m_localFrame(f) {}

inline void hkaSkeleton::Partition::initWithoutName(hkInt16 startBoneIndex, hkInt16 numBones) {
    m_startBoneIndex = startBoneIndex;
    m_numBones = numBones;
}

inline hkBool32 hkaSkeleton::Partition::isBonePresentWithinPartition(hkInt16 boneIndex) const {
    return hkMath::intInRange(boneIndex, m_startBoneIndex, m_startBoneIndex + m_numBones);
}

inline hkInt16 hkaSkeleton::Partition::getEndBoneIndex() const {
    return hkInt16(m_startBoneIndex + m_numBones - 1);
}

inline hkaSkeleton::hkaSkeleton() = default;

inline hkaSkeleton::hkaSkeleton(const hkaSkeleton& skel) : hkReferencedObject(skel) {
    m_name = skel.m_name;
    m_parentIndices = skel.m_parentIndices;
    m_bones = skel.m_bones;
    m_referencePose = skel.m_referencePose;
    m_referenceFloats = skel.m_referenceFloats;
    m_floatSlots = skel.m_floatSlots;
    m_localFrames = skel.m_localFrames;
    m_partitions = skel.m_partitions;
}

inline hkaSkeleton::hkaSkeleton(hkFinishLoadedObjectFlag f)
    : hkReferencedObject(f), m_name(f), m_parentIndices(f), m_bones(f), m_referencePose(f),
      m_referenceFloats(f), m_floatSlots(f), m_localFrames(f), m_partitions(f) {}

inline hkLocalFrame* hkaSkeleton::getLocalFrameForBone(int boneIndex) const {
    for (int i = 0; i < m_localFrames.getSize(); i++) {
        if (m_localFrames[i].m_boneIndex == boneIndex)
            return m_localFrames[i].m_localFrame;
        if (m_localFrames[i].m_boneIndex > boneIndex)
            break;
    }
    return nullptr;
}

inline hkInt16 hkaSkeleton::getPartitionIndexFromName(const char* partitionName) const {
    const int numPartitions = m_partitions.getSize();

    for (hkInt16 i = 0; i < numPartitions; ++i) {
        if (hkString::strCmp(partitionName, m_partitions[i].m_name) == 0)
            return i;
    }
    return -1;
}

inline hkInt16 hkaSkeleton::getPartitionIndexForBone(hkInt16 boneIndex) const {
    const int numPartitions = m_partitions.getSize();

    for (hkInt16 i = 0; i < numPartitions; ++i) {
        if (m_partitions[i].isBonePresentWithinPartition(boneIndex))
            return i;
    }
    return -1;
}
