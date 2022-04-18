#include "KingSystem/Physics/Rig/physModelBoneAccessor.h"
#include <Havok/Animation/Animation/Rig/hkaSkeleton.h>
#include <Havok/Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <heap/seadExpHeap.h>
#include <heap/seadHeapMgr.h>
#include <nn/g3d/ResSkeleton.h>
#include <nn/g3d/SkeletonObj.h>
#include <type_traits>
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

ModelBoneAccessor::ModelBoneAccessor() = default;

ModelBoneAccessor::~ModelBoneAccessor() {
    ModelBoneAccessor::finalize();
}

bool ModelBoneAccessor::init(const hkaSkeleton* skeleton, const gsys::Model* model,
                             sead::Heap* heap) {
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

bool ModelBoneAccessor::init(const gsys::Model* model, int model_unit_index, sead::Heap* heap,
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

}  // namespace ksys::phys
