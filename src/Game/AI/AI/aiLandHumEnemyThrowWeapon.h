#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LandHumEnemyThrowWeapon : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LandHumEnemyThrowWeapon, ksys::act::ai::Ai)
public:
    explicit LandHumEnemyThrowWeapon(const InitArg& arg);
    ~LandHumEnemyThrowWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mThrowWeaponNearDist_s{};
    // static_param at offset 0x48
    const int* mWaitTimeMax_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
