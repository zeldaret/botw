#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelBackStepFromTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelBackStepFromTarget, ksys::act::ai::Ai)
public:
    explicit LynelBackStepFromTarget(const InitArg& arg);
    ~LynelBackStepFromTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mMoveDistMin_s{};
    // static_param at offset 0x40
    const float* mMoveDist_s{};
    // static_param at offset 0x48
    const float* mAddCheckAngle_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
