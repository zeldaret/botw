#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestIronBallAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestIronBallAttack, ksys::act::ai::Ai)
public:
    explicit PriestIronBallAttack(const InitArg& arg);
    ~PriestIronBallAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSpeed_s{};
    // static_param at offset 0x40
    const float* mShootPitchMin_s{};
    // static_param at offset 0x48
    const float* mShootPitchMax_s{};
    // static_param at offset 0x50
    const float* mNoise_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
