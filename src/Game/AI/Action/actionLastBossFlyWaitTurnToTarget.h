#pragma once

#include "Game/AI/Action/actionLastBossFlyWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossFlyWaitTurnToTarget : public LastBossFlyWait {
    SEAD_RTTI_OVERRIDE(LastBossFlyWaitTurnToTarget, LastBossFlyWait)
public:
    explicit LastBossFlyWaitTurnToTarget(const InitArg& arg);
    ~LastBossFlyWaitTurnToTarget() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xa0
    const float* mTurnStartDiffAng_s{};
    // static_param at offset 0xa8
    const float* mTurnRate_s{};
    // static_param at offset 0xb0
    sead::SafeString mTurnASName_s{};
    // dynamic_param at offset 0xc0
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
