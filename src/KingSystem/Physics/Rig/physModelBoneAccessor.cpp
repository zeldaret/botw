#include "KingSystem/Physics/Rig/physModelBoneAccessor.h"
#include <Havok/Animation/Animation/Rig/hkaSkeleton.h>
#include <Havok/Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <heap/seadExpHeap.h>
#include "KingSystem/Utils/SafeDelete.h"

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

    hkaSkeleton* mHavokSkeleton = nullptr;
    u8* _10 = nullptr;
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

    if (_10)
        util::safeDeleteArray(_10);
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
