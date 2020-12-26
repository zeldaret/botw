#pragma once

#include "Game/AI/Action/actionGolemThrowPartsToTargetBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GolemThrowPartsToTarget : public GolemThrowPartsToTargetBase {
    SEAD_RTTI_OVERRIDE(GolemThrowPartsToTarget, GolemThrowPartsToTargetBase)
public:
    explicit GolemThrowPartsToTarget(const InitArg& arg);
    ~GolemThrowPartsToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x118
    const float* mShootPitchMin_s{};
    // static_param at offset 0x120
    const float* mShootPitchMax_s{};
    // dynamic_param at offset 0x128
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
