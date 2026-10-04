#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSetSwarmMaterialAnimByDist : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkSetSwarmMaterialAnimByDist, ksys::act::ai::Action)
public:
    explicit ForkSetSwarmMaterialAnimByDist(const InitArg& arg);
    ~ForkSetSwarmMaterialAnimByDist() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mApplyMaterialAnimNumPerFrame_s{};
    // static_param at offset 0x28
    const int* mSetState_s{};
    // static_param at offset 0x30
    const float* mApplyMaterialAnimDist_s{};
    // static_param at offset 0x38
    const float* mMaterialAnimFrame_s{};
    // static_param at offset 0x40
    sead::SafeString mMaterialAnimName_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
