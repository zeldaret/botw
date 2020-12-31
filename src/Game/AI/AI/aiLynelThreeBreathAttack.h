#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelThreeBreathAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelThreeBreathAttack, ksys::act::ai::Ai)
public:
    explicit LynelThreeBreathAttack(const InitArg& arg);
    ~LynelThreeBreathAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mNearRange_s{};
    // static_param at offset 0x40
    const float* mFarRange_s{};
    // static_param at offset 0x48
    const bool* mIsCheckXZ_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
