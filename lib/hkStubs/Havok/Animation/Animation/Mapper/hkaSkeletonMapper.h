#pragma once

#include <Havok/Animation/Animation/Animation/hkaAnimationBinding.h>
#include <Havok/Animation/Animation/Mapper/hkaSkeletonMapperData.h>
#include <Havok/Animation/Animation/Rig/hkaSkeleton.h>
#include <Havok/Common/Base/hkBase.h>

class hkaPose;
class hkaAnimationBinding;

/// This run-time class converts a pose from one skeleton (A) to another (B). The poses can be
/// specified by either hkaPose objects or arrays of transforms. It uses mapping data
/// (hkaSkeletonMapperData), which can be created using the hkaSkeletonMapperUtils utility class.
class hkaSkeletonMapper : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaSkeletonMapper)
    HK_DECLARE_REFLECTION()

    explicit hkaSkeletonMapper(const hkaSkeletonMapperData& mapping);
    explicit hkaSkeletonMapper(hkFinishLoadedObjectFlag f) : hkReferencedObject(f), m_mapping(f) {}

    ~hkaSkeletonMapper() override;

    enum ConstraintSource {
        NO_CONSTRAINTS,
        REFERENCE_POSE,
        CURRENT_POSE,
    };

    void mapPose(const hkQsTransform* poseAModelSpace, const hkQsTransform* originalPoseBLocalSpace,
                 hkQsTransform* poseBModelSpaceInOut, ConstraintSource source) const;

    void mapPoseLocalSpace(const hkQsTransform* poseALocalSpace,
                           hkQsTransform* poseBLocalSpaceInOut,
                           hkaAnimationBinding::BlendHint blendHint) const;

    void mapPoseLocalSpace(const hkQsTransform* poseALocalSpace,
                           hkQsTransform* poseBLocalSpaceInOut, const hkInt16* boneToTrackIndicesA,
                           const hkInt16* boneToTrackIndicesB,
                           hkaAnimationBinding::BlendHint blendHint,
                           const hkReal* weightsA = nullptr, hkReal* weightsBOut = nullptr) const;

    void mapPoseLocalSpace(const hkQsTransform* poseALocalSpace,
                           hkQsTransform* poseBLocalSpaceInOut,
                           const hkArray<hkInt16>& partitionIndicesA,
                           hkaAnimationBinding::BlendHint blendHint, bool mapToFullPose = true,
                           const hkReal* weightsA = nullptr, hkReal* weightsBOut = nullptr) const;

    void mapPoseLocalSpace(const hkQsTransform* poseALocalSpace,
                           hkQsTransform* poseBLocalSpaceInOut, const hkInt16* boneToTrackIndicesA,
                           const hkInt16* boneToTrackIndicesB,
                           const hkArray<hkInt16>& partitionIndicesA,
                           hkaAnimationBinding::BlendHint blendHint, bool mapToFullPose = true,
                           const hkReal* weightsA = nullptr, hkReal* weightsBOut = nullptr) const;

    void mapPose(const hkaPose& poseAIn, hkaPose& poseBInOut,
                 ConstraintSource source = NO_CONSTRAINTS) const;

    void mapExtractedMotion(const hkQsTransform& deltaMotionIn,
                            hkQsTransform& deltaMotionOut) const;

    void initializeBindingMaps(const hkaAnimationBinding* binding,
                               hkArray<hkInt16>& srcBoneToTrackIndicesOut,
                               hkArray<hkInt16>& dstBoneToTrackIndicesOut,
                               hkArray<hkInt16>& dstTrackToBoneIndicesOut) const;

    static void combinedPoseFromAdditivePoseAndReferencePose(
        const hkQsTransform* additivePose, const hkQsTransform* referencePose,
        const hkInt16* boneToTrackIndices, hkInt32 startBoneIndex, hkInt32 numBones,
        hkaAnimationBinding::BlendHint additiveHint, hkQsTransform* combinedPoseOut);

    static void additivePoseFromCombinedPoseAndReferencePose(
        const hkQsTransform* combinedPose, const hkQsTransform* referencePose,
        const hkInt16* boneToTrackIndices, hkInt32 startBoneIndex, hkInt32 numBones,
        hkaAnimationBinding::BlendHint additiveHint, hkQsTransform* additivePoseOut);

    static void combineSparsePoseWithFullPose(const hkQsTransform* sparsePose,
                                              const hkQsTransform* fullPose,
                                              const hkInt16* sparsePoseBoneToTrackIndices,
                                              hkInt32 startBoneIndex, hkInt32 numBones,
                                              hkaAnimationBinding::BlendHint additiveHint,
                                              hkQsTransform* sparseMulFull_sparseOut);

public:
    hkaSkeletonMapperData m_mapping;

public:
    // Debug only.
    static void checkMapping(const hkaSkeletonMapperData& mapping);
    static void checkMappingLocalSpace(const hkaSkeletonMapperData& mapping);
    static bool checkTransform(hkaSkeletonMapperData::MappingType type, const hkQsTransform& q);

private:
    static void mapPoseLocalSpaceInternal(
        const hkaSkeletonMapperData& mapping, const hkQsTransform* poseALocalSpaceOriginal,
        hkQsTransform* poseBLocalSpaceInOut, const hkInt16* boneToTrackIndicesA,
        const hkInt16* boneToTrackIndicesB, const hkArray<hkInt16>& partitionIndicesA,
        hkaAnimationBinding::BlendHint blendHint, bool mapToFullPose, const hkReal* weightsA,
        hkReal* weightsBOut);

    static void setMulWithScaling(hkaSkeletonMapperData::MappingType type, hkQsTransform& dst,
                                  const hkQsTransform& t1, const hkQsTransform& t2);
};
