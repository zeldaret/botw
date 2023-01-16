#pragma once

#include <hostio/seadHostIONode.h>
#include "KingSystem/Physics/Rig/physBoneAccessor.h"
#include "KingSystem/Physics/Rig/physModelBoneAccessor.h"

class hkaSkeletonMapper;

namespace ksys::phys {

class SkeletonMapper : public sead::hostio::Node {
public:
    SkeletonMapper();
    virtual ~SkeletonMapper();

    bool init(hkaSkeletonMapper* skeleton_mapper, hkaSkeletonMapper* model_skeleton_mapper,
              gsys::Model* model, sead::Heap* heap);

    void mapPoseA();
    void mapPoseB();

    BoneAccessor& getBoneAccessor() { return mBoneAccessor; }
    ModelBoneAccessor& getModelBoneAccessor() { return mModelBoneAccessor; }

private:
    BoneAccessor mBoneAccessor;
    ModelBoneAccessor mModelBoneAccessor;
    hkaSkeletonMapper* mMapperA{};
    hkaSkeletonMapper* mMapperB{};
};

}  // namespace ksys::phys
