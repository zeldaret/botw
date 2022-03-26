#pragma once

#include <Havok/Animation/Animation/Rig/hkaSkeleton.h>
#include <Havok/Common/Base/hkBase.h>

class hkaSkeletonMapperData {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaSkeletonMapperData)
    HK_DECLARE_REFLECTION()

    enum MappingType {
        HK_RAGDOLL_MAPPING = 0,
        HK_RETARGETING_MAPPING = 1,
    };

    struct SimpleMapping {
        HK_DECLARE_CLASS_ALLOCATOR(SimpleMapping)
        HK_DECLARE_REFLECTION()

        hkInt16 m_boneA = 0;
        hkInt16 m_boneB = 0;
        hkQsTransform m_aFromBTransform{hkQsTransform::IdentityInitializer()};
    };

    /// Defines a n-to-m mapping between a chain of bones of A and a chain of bones of B.
    struct ChainMapping {
        HK_DECLARE_CLASS_ALLOCATOR(ChainMapping)
        HK_DECLARE_REFLECTION()

        hkInt16 m_startBoneA = 0;
        hkInt16 m_endBoneA = 0;
        hkInt16 m_startBoneB = 0;
        hkInt16 m_endBoneB = 0;
        hkQsTransform m_startAFromBTransform{hkQsTransform::IdentityInitializer()};
        hkQsTransform m_endAFromBTransform{hkQsTransform::IdentityInitializer()};
    };

    /// Defines mapping between the partition and simple/chain mappings
    struct PartitionMappingRange {
        HK_DECLARE_CLASS_ALLOCATOR(PartitionMappingRange)
        HK_DECLARE_REFLECTION()

        int m_startMappingIndex;
        int m_numMappings;
    };

    hkaSkeletonMapperData();
    explicit hkaSkeletonMapperData(hkFinishLoadedObjectFlag f);
    ~hkaSkeletonMapperData();

    hkRefPtr<hkaSkeleton> m_skeletonA;
    hkRefPtr<hkaSkeleton> m_skeletonB;
    hkArray<hkInt16> m_partitionMap;
    hkArray<PartitionMappingRange> m_simpleMappingPartitionRanges;
    hkArray<PartitionMappingRange> m_chainMappingPartitionRanges;
    hkArray<SimpleMapping> m_simpleMappings;
    hkArray<ChainMapping> m_chainMappings;
    hkArray<hkInt16> m_unmappedBones;
    hkQsTransform m_extractedMotionMapping;
    hkBool m_keepUnmappedLocal;
    hkEnum<hkaSkeletonMapperData::MappingType, hkInt32> m_mappingType;
};
