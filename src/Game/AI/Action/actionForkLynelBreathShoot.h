#pragma once

#include "Game/AI/Action/actionForkVacuumShootToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkLynelBreathShoot : public ForkVacuumShootToTarget {
    SEAD_RTTI_OVERRIDE(ForkLynelBreathShoot, ForkVacuumShootToTarget)
public:
    explicit ForkLynelBreathShoot(const InitArg& arg);
    ~ForkLynelBreathShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd0
    const int* mEnlargeTime_s{};
    // static_param at offset 0xd8
    const float* mAttackRatio_s{};
    // static_param at offset 0xe0
    const float* mBreathSize_s{};
    // static_param at offset 0xe8
    const float* mRange_s{};
    // static_param at offset 0xf0
    const float* mSpeed_s{};
    // static_param at offset 0xf8
    const sead::Vector3f* mShootDir_s{};
};

}  // namespace uking::action
