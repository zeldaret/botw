#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyBaseArrowAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyBaseArrowAttack, ksys::act::ai::Ai)
public:
    explicit EnemyBaseArrowAttack(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mIntervalIntensity_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
