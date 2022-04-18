#pragma once

#include <container/seadBuffer.h>
#include <gsys/gsysModelAccessKey.h>
#include <math/seadVector.h>
#include <prim/seadLongBitFlag.h>
#include "KingSystem/Physics/Rig/physBoneAccessor.h"

namespace gsys {
class Model;
class ModelUnit;
}  // namespace gsys

namespace ksys::phys {

namespace detail {
class ModelSkeleton;
}

class ModelBoneAccessor : public BoneAccessor {
public:
    enum class EnableScale : bool { Yes = true, No = false };

    class ModelBoneFilter {
    public:
        using BoneBitSet = sead::LongBitFlag<1024>;

        /// Returns the number of bones after filtering.
        virtual int filter(BoneBitSet* bones_to_keep, const gsys::ModelUnit& model_unit) = 0;
    };

    ModelBoneAccessor();
    ~ModelBoneAccessor() override;

    bool init(const hkaSkeleton* skeleton, gsys::Model* model, sead::Heap* heap);

    bool init(gsys::Model* model, int model_unit_index, sead::Heap* heap,
              ModelBoneFilter* bone_filter);

    void finalize() override;

    int findBoneIndex(const gsys::BoneAccessKey& key) const;
    const char* getBoneName(int index) const;

    void copyModelPoseToHavok(EnableScale enable_scale) const;
    void copyHavokPoseToModel(EnableScale enable_scale) const;

    static int& getUnkMode();
    static bool& getUnkFlag();

protected:
    struct BoneAccessKey {
        gsys::BoneAccessKeyEx key;
        bool _38;
        bool _39;
    };

    gsys::ModelUnit* getModelUnit(int bone_idx) const;

    gsys::Model* mModel{};
    sead::Buffer<BoneAccessKey> mBoneAccessKeys;
    sead::Vector3f mTranslate = sead::Vector3f::zero;
    detail::ModelSkeleton* mModelSkeleton{};
};

}  // namespace ksys::phys
