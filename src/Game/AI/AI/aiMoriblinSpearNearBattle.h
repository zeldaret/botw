#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MoriblinSpearNearBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MoriblinSpearNearBattle, ksys::act::ai::Ai)
public:
    explicit MoriblinSpearNearBattle(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mBackWalkPer_s{};
    // static_param at offset 0x40
    const int* mBackStepPer_s{};
    // static_param at offset 0x48
    const float* mNearDist_s{};
    // static_param at offset 0x50
    const int* mWeaponIdx_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
