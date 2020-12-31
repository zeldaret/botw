#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRandomRepeatSideStep : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRandomRepeatSideStep, ksys::act::ai::Ai)
public:
    explicit EnemyRandomRepeatSideStep(const InitArg& arg);
    ~EnemyRandomRepeatSideStep() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mMinRepeatNum_s{};
    // static_param at offset 0x40
    const int* mMaxRepeatNum_s{};
    // static_param at offset 0x48
    const float* mStepDist_s{};
    // static_param at offset 0x50
    const float* mStepAngle_s{};
    // static_param at offset 0x58
    const int* mWeaponIdx_s{};
    // static_param at offset 0x60
    const float* mBaseDist_s{};
    // static_param at offset 0x68
    const float* mOutDist_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
