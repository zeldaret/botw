#include "KingSystem/Physics/Rig/physBoneAccessor.h"
#include <Havok/Animation/Animation/Playback/Utilities/hkaSampleAndCombineUtils.h>
#include <Havok/Animation/Animation/Rig/hkaPose.h>
#include <Havok/Animation/Animation/Rig/hkaSkeleton.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadMemUtil.h>

namespace ksys::phys {

BoneAccessor::BoneAccessor() = default;

BoneAccessor::~BoneAccessor() {
    BoneAccessor::finalize();
}

bool BoneAccessor::init(const hkaSkeleton* skeleton, sead::Heap* heap) {
    static constexpr int Alignment = 0x20;

    mPoseDataSize = sead::Mathu::roundUp(u32(hkaPose::getRequiredMemorySize(skeleton)), Alignment);
    if (mPoseDataSize == 0)
        return false;

    mPoseData = new (heap, Alignment) u8[mPoseDataSize];
    if (!mPoseData)
        return false;

    mPose = new hkaPose(skeleton, mPoseData);
    if (!mPose)
        return false;

    mPose->setToReferencePose();
    return true;
}

void BoneAccessor::finalize() {
    if (!mPose)
        return;

    delete mPose;
    mPose = nullptr;

    delete[] mPoseData;
    mPoseData = nullptr;
}

void BoneAccessor::resetPoseData() {
    sead::MemUtil::fillZero(mPoseData, mPoseDataSize);
}

const hkaSkeleton* BoneAccessor::getSkeleton() const {
    return mPose->getSkeleton();
}

hkaPose* BoneAccessor::getPoseInternal() const {
    return mPose;
}

hkaPose* BoneAccessor::getPose() const {
    return mPose;
}

void BoneAccessor::setScale(float scale) {
    hkaSampleAndCombineUtils::scaleTranslations(
        scale, const_cast<hkQsTransform*>(getSkeleton()->m_referencePose.data()),
        getSkeleton()->m_bones.getSize());
}

BoneAccessor::Indices BoneAccessor::getBoneIndex(const sead::SafeString& name) const {
    const sead::SafeString actual_name = getBoneName(name);

    for (int i = 0, n = getSkeleton()->m_bones.getSize(); i < n; ++i) {
        if (actual_name == getBoneName(getSkeleton()->m_bones[i].m_name.cString()))
            return {0, static_cast<s16>(i)};
    }

    return {-1, -1};
}

void BoneAccessor::setBoneLocalSpace(const BoneAccessor::Indices& index,
                                     const hkQsTransformf& bone) {
    mPose->setBoneLocalSpace(index.havok_index, bone);
}

const hkQsTransformf& BoneAccessor::getBoneLocalSpace(const BoneAccessor::Indices& index) const {
    return mPose->getBoneLocalSpace(index.havok_index);
}

// NON_MATCHING: regalloc
void BoneAccessor::setBoneModelSpace(const BoneAccessor::Indices& index,
                                     const hkQsTransformf& bone_model, Propagate propagate) {
    const auto havok_index = index.havok_index;
    mPose->setBoneModelSpace(havok_index, bone_model, hkaPose::PropagateOrNot(propagate));
}

const hkQsTransformf& BoneAccessor::getBoneModelSpace(const BoneAccessor::Indices& index) const {
    return mPose->getBoneModelSpace(index.havok_index);
}

#ifdef MATCHING_HACK_NX_CLANG
[[gnu::noinline]]
#endif
sead::SafeString
BoneAccessor::getBoneName(const sead::SafeString& name) {
    int substr_index = 0;

    int separator_index = name.rfindIndex(":");
    if (separator_index < 0) {
        substr_index = 0;
    } else if (separator_index < name.calcLength() - 1) {
        substr_index = separator_index + 1;
    }

    return name.cstr() + substr_index;
}

}  // namespace ksys::phys
