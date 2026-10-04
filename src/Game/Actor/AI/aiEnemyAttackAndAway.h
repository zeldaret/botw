#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyAttackAndAway : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyAttackAndAway, ksys::act::ai::Ai)
public:
    explicit EnemyAttackAndAway(const InitArg& arg);
    ~EnemyAttackAndAway() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mAwayStartDist_s{};
    // static_param at offset 0x48
    const float* mCheckCliffDist_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
