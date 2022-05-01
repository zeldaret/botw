#include "KingSystem/Physics/Rig/physSkeletonMapper.h"
#include <Havok/Animation/Animation/Mapper/hkaSkeletonMapper.h>
#include <Havok/Animation/Animation/Rig/hkaPose.h>

namespace ksys::phys {

SkeletonMapper::SkeletonMapper() = default;

SkeletonMapper::~SkeletonMapper() {
    mModelBoneAccessor.finalize();
    mBoneAccessor.finalize();
}

bool SkeletonMapper::init(hkaSkeletonMapper* skeleton_mapper,
                          hkaSkeletonMapper* model_skeleton_mapper, gsys::Model* model,
                          sead::Heap* heap) {
    if (!model || !skeleton_mapper || !model_skeleton_mapper)
        return false;

    hkaSkeleton* skel_a = skeleton_mapper->m_mapping.m_skeletonA.val();
    if (skel_a != model_skeleton_mapper->m_mapping.m_skeletonB.val())
        return false;

    hkaSkeleton* skel_b = skeleton_mapper->m_mapping.m_skeletonB.val();
    if (skel_b != model_skeleton_mapper->m_mapping.m_skeletonA.val())
        return false;

    const int num_bones_a = skel_a->m_bones.getSize();
    const int num_bones_b = skel_b->m_bones.getSize();
    if (num_bones_a <= 0 || num_bones_b <= 0)
        return false;

    const auto cleanup = [this] {
        mModelBoneAccessor.finalize();
        mBoneAccessor.finalize();
        return false;
    };

    if (num_bones_a <= num_bones_b) {
        mMapperA = model_skeleton_mapper;
        mMapperB = skeleton_mapper;

        if (!mModelBoneAccessor.init(skeleton_mapper->m_mapping.m_skeletonB.val(), model, heap) ||
            !mBoneAccessor.init(skeleton_mapper->m_mapping.m_skeletonA.val(), heap)) {
            return cleanup();
        }
    } else {
        mMapperA = skeleton_mapper;
        mMapperB = model_skeleton_mapper;

        if (!mModelBoneAccessor.init(skeleton_mapper->m_mapping.m_skeletonA.val(), model, heap) ||
            !mBoneAccessor.init(skeleton_mapper->m_mapping.m_skeletonB.val(), heap)) {
            return cleanup();
        }
    }

    return true;
}

void SkeletonMapper::mapPoseA() {
    mBoneAccessor.resetPoseData();
    mMapperA->mapPose(mModelBoneAccessor.getPose()->getSyncedPoseModelSpace().data(),
                      mBoneAccessor.getPose()->getSkeleton()->m_referencePose.data(),
                      mBoneAccessor.getPose()->accessUnsyncedPoseModelSpace().data(),
                      hkaSkeletonMapper::REFERENCE_POSE);
}

void SkeletonMapper::mapPoseB() {
    const auto* original = mModelBoneAccessor.getPose()->getSyncedPoseLocalSpace().data();
    auto* out = mModelBoneAccessor.getPose()->accessUnsyncedPoseModelSpace().data();
    mMapperB->mapPose(mBoneAccessor.getPose()->getSyncedPoseModelSpace().data(), original, out,
                      hkaSkeletonMapper::NO_CONSTRAINTS);
}

}  // namespace ksys::phys
