#pragma once

#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class UnarmedEnemyNoiseTarget : public UnarmedEnemySearch {
    SEAD_RTTI_OVERRIDE(UnarmedEnemyNoiseTarget, UnarmedEnemySearch)
public:
    explicit UnarmedEnemyNoiseTarget(const InitArg& arg);
    ~UnarmedEnemyNoiseTarget() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const int* mLostTime_s{};
    // static_param at offset 0x70
    const int* mWeaponIdx_s{};
    // static_param at offset 0x78
    const float* mLostRange_s{};
    // static_param at offset 0x80
    const float* mLostVMin_s{};
    // static_param at offset 0x88
    const float* mLostVMax_s{};
    // static_param at offset 0x90
    const float* mSearchWeaponDist_s{};
    // static_param at offset 0x98
    const float* mSearchBaseWeaponDist_s{};
    // static_param at offset 0xa0
    const float* mAbsorpDist_s{};
    // static_param at offset 0xa8
    const float* mFarDist_s{};
    // static_param at offset 0xb0
    const int* mRepathTime_s{};
    // static_param at offset 0xb8
    const float* mSearchWeaponTargetDist_s{};
    // dynamic_param at offset 0xc0
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
