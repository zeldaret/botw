#include "KingSystem/Physics/Rig/physModelBoneAccessor.h"
#include <Havok/Animation/Animation/Rig/hkaPose.h>
#include <Havok/Animation/Animation/Rig/hkaSkeleton.h>
#include <Havok/Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <heap/seadExpHeap.h>
#include <heap/seadHeapMgr.h>
#include <nn/g3d/ResSkeleton.h>
#include <nn/g3d/SkeletonObj.h>
#include <type_traits>
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

namespace detail {

class ModelSkeleton {
public:
    class Allocator : public hkMallocAllocator {
    public:
        void* blockAlloc(int numBytes) override;
        void blockFree(void* p, int numBytes) override;
        int getAllocatedSize(const void* obj, int nbytes) const override;

        sead::Heap* mHeap{};
    };

    ModelSkeleton() = default;
    virtual ~ModelSkeleton();

    /// Construct a Havok skeleton from a gsys model.
    bool constructFromModel(ModelBoneAccessor::ModelBoneFilter* bone_filter,
                            const gsys::ModelNW& model_unit, sead::Heap* heap);

    /// Construct a Havok skeleton from a gsys model. Fast path, no support for filtering.
    bool constructFromModel(const gsys::ModelNW& model_unit, sead::Heap* heap);

    hkaSkeleton* mHavokSkeleton = nullptr;
    u8* mSkeletonStorage = nullptr;
    void* _18;
    Allocator mHavokAllocator;
};

void* ModelSkeleton::Allocator::blockAlloc(int numBytes) {
    return mHeap->alloc(numBytes, m_align);
}

void ModelSkeleton::Allocator::blockFree(void* p, int numBytes) {
    mHeap->free(p);
}

int ModelSkeleton::Allocator::getAllocatedSize(const void* obj, int nbytes) const {
    return static_cast<int>(
        sead::DynamicCast<sead::ExpHeap>(mHeap)->getAllocatedSize(const_cast<void*>(obj)));
}

ModelSkeleton::~ModelSkeleton() {
    if (mHavokSkeleton) {
        mHavokSkeleton->m_bones._clearAndDeallocate(mHavokAllocator);
        mHavokSkeleton->m_referencePose._clearAndDeallocate(mHavokAllocator);
        mHavokSkeleton->m_parentIndices._clearAndDeallocate(mHavokAllocator);
        mHavokSkeleton = nullptr;
    }

    if (mSkeletonStorage)
        util::safeDeleteArray(mSkeletonStorage);
}

bool ModelSkeleton::constructFromModel(const gsys::ModelNW& model_unit, sead::Heap* heap) {
    mHavokAllocator.mHeap = heap ? heap : sead::HeapMgr::instance()->getCurrentHeap();

    const nn::g3d::ResSkeleton* skel = model_unit.getSkeletonObj()->GetRes();
    const int num_bones = model_unit.getBoneNum();

    if (num_bones <= 1)
        return false;

    mSkeletonStorage = new (heap, 0x10) u8[sizeof(hkaSkeleton)];
    mHavokSkeleton = new (mSkeletonStorage) hkaSkeleton;

    if (!mHavokSkeleton->m_bones._reserveExactly(mHavokAllocator, num_bones).isSuccess())
        return false;

    if (!mHavokSkeleton->m_parentIndices._reserveExactly(mHavokAllocator, num_bones).isSuccess())
        return false;

    if (!mHavokSkeleton->m_referencePose._reserveExactly(mHavokAllocator, num_bones).isSuccess())
        return false;

    mHavokSkeleton->m_bones._setSize(mHavokAllocator, num_bones);
    mHavokSkeleton->m_parentIndices._setSize(mHavokAllocator, num_bones);
    mHavokSkeleton->m_referencePose._setSize(mHavokAllocator, num_bones);

    for (int i = 0; i < num_bones; ++i) {
        const auto& bone = *skel->GetBone(i);
        mHavokSkeleton->m_bones[i].m_name.setPointerAligned(bone.GetName());
        mHavokSkeleton->m_parentIndices[i] = s16(bone.GetParentIndex());
        if (i == mHavokSkeleton->m_parentIndices[i])
            mHavokSkeleton->m_parentIndices[i] = -1;
    }

    return true;
}

bool ModelSkeleton::constructFromModel(ModelBoneAccessor::ModelBoneFilter* bone_filter,
                                       const gsys::ModelNW& model_unit, sead::Heap* heap) {
    if (bone_filter == nullptr)
        return constructFromModel(model_unit, heap);

    mHavokAllocator.mHeap = heap ? heap : sead::HeapMgr::instance()->getCurrentHeap();

    const nn::g3d::ResSkeleton* skel = model_unit.getSkeletonObj()->GetRes();

    ModelBoneAccessor::ModelBoneFilter::BoneBitSet bones_to_keep;
    const int num_bones = bone_filter->filter(&bones_to_keep, model_unit);

    if (num_bones <= 1)
        return false;

    mSkeletonStorage = new (heap, 0x10) u8[sizeof(hkaSkeleton)];
    mHavokSkeleton = new (mSkeletonStorage) hkaSkeleton;

    if (!mHavokSkeleton->m_bones._reserveExactly(mHavokAllocator, num_bones).isSuccess())
        return false;

    if (!mHavokSkeleton->m_parentIndices._reserveExactly(mHavokAllocator, num_bones).isSuccess())
        return false;

    if (!mHavokSkeleton->m_referencePose._reserveExactly(mHavokAllocator, num_bones).isSuccess())
        return false;

    mHavokSkeleton->m_bones._setSize(mHavokAllocator, num_bones);
    mHavokSkeleton->m_parentIndices._setSize(mHavokAllocator, num_bones);
    mHavokSkeleton->m_referencePose._setSize(mHavokAllocator, num_bones);

    const int num_model_bones = model_unit.getBoneNum();
    int havok_bone_index = 0;

    for (int i = 0; i < num_model_bones; ++i) {
        if (bones_to_keep.isOffBit(i))
            continue;

        const auto& bone = *skel->GetBone(i);
        mHavokSkeleton->m_bones[havok_bone_index].m_name.setPointerAligned(bone.GetName());

        int orig_parent_index = bone.GetParentIndex();
        if (orig_parent_index < num_model_bones) {
            mHavokSkeleton->m_parentIndices[havok_bone_index] =
                s16(bones_to_keep.countRightOnBit(orig_parent_index) - 1);
        } else {
            mHavokSkeleton->m_parentIndices[havok_bone_index] = -1;
        }

        ++havok_bone_index;
    }

    return true;
}

}  // namespace detail

static int sModelBoneAccessorUnkMode;
static bool sModelBoneAccessorUnkFlag;

ModelBoneAccessor::ModelBoneAccessor() = default;

ModelBoneAccessor::~ModelBoneAccessor() {
    ModelBoneAccessor::finalize();
}

bool ModelBoneAccessor::init(const hkaSkeleton* skeleton, gsys::Model* model, sead::Heap* heap) {
    if (!skeleton || !model)
        return false;

    if (!BoneAccessor::init(skeleton, heap))
        return false;

    const int num_bones = skeleton->m_bones.getSize();

    if (num_bones > 0)
        mBoneAccessKeys.allocBufferAssert(num_bones, heap);

    for (int i = 0; i < num_bones; ++i) {
        sead::SafeString bone_name = skeleton->m_bones[i].m_name.cString();
        int separator_index = bone_name.rfindIndex(":");
        if (separator_index >= 0 && separator_index < bone_name.calcLength() - 1)
            bone_name = bone_name.cstr() + separator_index + 1;

        mBoneAccessKeys[i].key.search(model, bone_name);
        mBoneAccessKeys[i]._38 = true;
        mBoneAccessKeys[i]._39 = true;
    }

    mModel = model;
    return true;
}

bool ModelBoneAccessor::init(gsys::Model* model, int model_unit_index, sead::Heap* heap,
                             ModelBoneAccessor::ModelBoneFilter* bone_filter) {
    if (!model)
        return false;

    if (model_unit_index >= model->getUnits().size())
        return false;

    const gsys::ModelUnit* unit = model->getUnits()[model_unit_index]->mModelUnit;

    const auto* nw_unit = sead::DynamicCast<const gsys::ModelNW>(unit);
    if (!nw_unit)
        return false;

    mModelSkeleton = new (heap) detail::ModelSkeleton;
    if (!mModelSkeleton)
        return false;

    if (!mModelSkeleton->constructFromModel(bone_filter, *nw_unit, heap)) {
        delete mModelSkeleton;
        mModelSkeleton = nullptr;
        return false;
    }

    return init(mModelSkeleton->mHavokSkeleton, model, heap);
}

void ModelBoneAccessor::finalize() {
    mBoneAccessKeys.freeBuffer();
    BoneAccessor::finalize();
    if (mModelSkeleton)
        util::safeDelete(mModelSkeleton);
}

int ModelBoneAccessor::findBoneIndex(const gsys::BoneAccessKey& key) const {
    for (int i = 0, n = mBoneAccessKeys.size(); i < n; ++i) {
        if (key == mBoneAccessKeys[i].key.getKey())
            return i;
    }
    return -1;
}

const char* ModelBoneAccessor::getBoneName(int index) const {
    if (index < 0 || index >= getSkeleton()->m_bones.getSize())
        return nullptr;
    return getSkeleton()->m_bones[index].m_name.cString();
}

// NON_MATCHING: two loop induction variables (bone_idx) swapped
void ModelBoneAccessor::copyModelPoseToHavok(EnableScale enable_scale) const {
    auto& hk_bones = getPose()->accessUnsyncedPoseLocalSpace();

    switch (getUnkMode()) {
    case 2:
        enable_scale = EnableScale::Yes;
        break;
    case 1:
        enable_scale = EnableScale::No;
        break;
    }

    for (int bone_idx = 0, n = mBoneAccessKeys.getSize(); bone_idx < n; ++bone_idx) {
        if (!mBoneAccessKeys[bone_idx].key.isValid())
            continue;

        if (!mBoneAccessKeys[bone_idx]._38)
            continue;

        const auto key = mBoneAccessKeys[bone_idx].key.getKey();
        auto* unit = getModelUnit(bone_idx);

        sead::Vector3f scale;
        sead::Matrix34f transform;
        unit->getBoneLocalMatrix(&transform, &scale, key.bone_index);

        if (util::isMatrixInvalid(transform))
            continue;

        if ((!bool(enable_scale) || getUnkFlag()) &&
            !scale.equals(sead::Vector3f::ones, sead::Mathf::epsilon())) {
            if (getUnkFlag()) {
                // leftover debug code
                static_cast<void>(getModelUnit(bone_idx)->getName().include("Link"));
            }

            if (!bool(enable_scale))
                scale = {1, 1, 1};
        }

        toHkQsTransform(&hk_bones[bone_idx], transform,
                        bone_idx == 0 ? sead::Vector3f::ones : scale);

        if (mModel->getScale().x != 1)
            hk_bones[bone_idx].m_translation.mul(mModel->getScale().x);
    }
}

void ModelBoneAccessor::copyHavokPoseToModel(EnableScale enable_scale) const {
    const auto& hk_bones = getPoseInternal()->getSyncedPoseLocalSpace();

    bool not_first_bone = false;

    for (int bone_idx = 0, n = mBoneAccessKeys.getSize(); bone_idx < n; ++bone_idx) {
        if (!mBoneAccessKeys[bone_idx]._39)
            continue;

        if (!mBoneAccessKeys[bone_idx].key.isValid())
            continue;

        sead::Vector3f translate;
        translate = sead::Vector3f::zero;
        if (!not_first_bone)
            translate += mTranslate;

        hkTransform hk_transform;
        const_cast<hkQsTransformf&>(hk_bones[bone_idx]).fastRenormalize();
        hk_bones[bone_idx].copyToTransform(hk_transform);

        sead::Vector3f scale = toVec3(hk_bones[bone_idx].getScale());
        sead::Matrix34f transform;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                transform(i, j) = hk_transform.getRotation().getColumn(j)(i);
            }
            transform(i, 3) = translate.e[i] + hk_transform.getTranslation()(i);
        }

        const float model_scale = mModel->getScale().x;
        if (model_scale != 1 && model_scale > 0) {
            for (int i = 0; i < 3; ++i)
                transform(i, 3) *= 1 / model_scale;
        }

        if (!util::isMatrixInvalid(transform)) {
            if ((!bool(enable_scale) || getUnkFlag()) &&
                !scale.equals(sead::Vector3f::ones, sead::Mathf::epsilon())) {
                if (getUnkFlag()) {
                    // leftover debug code
                    static_cast<void>(getModelUnit(bone_idx)->getName().include("Link"));
                }

                if (!bool(enable_scale))
                    scale = {1, 1, 1};
            }

            mModel->setBoneLocalMatrix(mBoneAccessKeys[bone_idx].key.getKey(), transform, scale);
        }

        not_first_bone = true;
    }
}

int& ModelBoneAccessor::getUnkMode() {
    return sModelBoneAccessorUnkMode;
}

bool& ModelBoneAccessor::getUnkFlag() {
    return sModelBoneAccessorUnkFlag;
}

gsys::ModelUnit* ModelBoneAccessor::getModelUnit(int bone_idx) const {
    const auto key = mBoneAccessKeys[bone_idx].key.getKey();
    return mModel->getUnits()[key.model_unit_index]->mModelUnit;
}

}  // namespace ksys::phys
