#pragma once

#include <gsys/gsysModelUnit.h>
#include <nn/g3d/ModelObj.h>
#include <nn/gfx/gfx_MemoryPool.h>
#include <nn/gfx/gfx_Types.h>
#include <prim/seadDelegate.h>

namespace agl {
class DrawContext;
}

namespace gsys {

class ModelAutoAnimation;
class ModelDynamicEnvInfo;
class ModelRenderUnitNW;

// XXX: bad name. This doesn't reflect the fact that ModelNW is a ModelUnit, not a Model.
// TODO
class ModelNW : public ModelUnit,
                public nn::g3d::ICalculateWorldCallback,
                public sead::hostio::Node {
    SEAD_RTTI_OVERRIDE(ModelNW, ModelUnit)

public:
    struct BoneCallbackArg;

    using BoneCallback = sead::IDelegate1<BoneCallbackArg*>;
    using BoneCallbackStorage = sead::AnyDelegate1<BoneCallbackArg*>;

    const nn::g3d::SkeletonObj* getSkeletonObj() const { return mModelObj.GetSkeleton(); }

protected:
    virtual void drawDetail(agl::DrawContext* context) const;
    virtual void createRenderUnitNW(int, sead::Heap* heap);

    virtual void calcBounding_();  // NOLINT(bugprone-virtual-near-miss)
    virtual void calcGPUSkinning_();

    void Exec(nn::g3d::ICalculateWorldCallback::CallbackArg& arg,
              nn::g3d::WorldMtxManip& world_mtx_manip) override;

private:
    u8 _168;
    nn::g3d::ModelObj mModelObj;
    u8 _200;
    u8 _201;
    s8 mBufferNum;
    u8 _203;
    u8 _204;
    u8 _205;
    u8 _206;
    u8 _207;
    u32 _208;
    ModelRenderUnitNW** mRenderUnits;
    ModelAutoAnimation* mAutoAnimation;
    ModelDynamicEnvInfo* mDynamicEnvInfo;
    void* _228;
    void* _230;
    void* _238;
    BoneCallbackStorage mBoneCallback;
    void* _260;
    int _268;
    void* _270;
    nn::gfx::MemoryPool mMemoryPool;
};

}  // namespace gsys
