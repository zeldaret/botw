#pragma once

#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LandHumEnemyUnarmedBattle : public UnarmedEnemySearch {
    SEAD_RTTI_OVERRIDE(LandHumEnemyUnarmedBattle, UnarmedEnemySearch)
public:
    explicit LandHumEnemyUnarmedBattle(const InitArg& arg);
    ~LandHumEnemyUnarmedBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const int* mEquipItemSearchIdx_s{};
    // static_param at offset 0x70
    const int* mLostTimer_s{};
    // static_param at offset 0x78
    const float* mSearchWeaponDist_s{};
    // static_param at offset 0x80
    const float* mSearchBaseWeaponDist_s{};
    // static_param at offset 0x88
    const float* mSearchObjectDist_s{};
    // static_param at offset 0x90
    const float* mSearchWeaponTargetDist_s{};
    // static_param at offset 0x98
    const float* mSearchBowTargetDist_s{};
    // static_param at offset 0xa0
    const float* mGrabCheckRadius_s{};
    // static_param at offset 0xa8
    const float* mItemChaseableSpd_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mAttOffset_s{};
    // static_param at offset 0xb8
    const bool* mCanGrabHeavy_s{};
    // static_param at offset 0xc0
    const int* mRepathTime_s{};
    // static_param at offset 0xc8
    const float* mExplosivesAvoidDist_s{};
    // static_param at offset 0xd0
    const float* mExplosivesAvoidSpeed_s{};
    // static_param at offset 0xd8
    const float* mExplosivesAvoidAng_s{};
    // static_param at offset 0xe0
    const float* mLostVMin_s{};
    // static_param at offset 0xe8
    const float* mLostVMax_s{};
    // static_param at offset 0xf0
    const float* mLostRange_s{};
    // static_param at offset 0xf8
    const float* mOnCoHitAllowGrabAngle_s{};
    // dynamic_param at offset 0x100
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
