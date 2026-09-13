#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BokoblinArrowAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BokoblinArrowAttack, ksys::act::ai::Ai)
public:
    explicit BokoblinArrowAttack(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mBackWalkStartDist_s{};
    // static_param at offset 0x48
    const float* mBackWalkEndDist_s{};
    // static_param at offset 0x50
    const float* mCliffCheckDist_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
