#pragma once

#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class UnarmedEnemySearchWeapon : public UnarmedEnemySearch {
    SEAD_RTTI_OVERRIDE(UnarmedEnemySearchWeapon, UnarmedEnemySearch)
public:
    explicit UnarmedEnemySearchWeapon(const InitArg& arg);
    ~UnarmedEnemySearchWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x6b8
    const int* mEquipItemSearchIdx_s{};
    // static_param at offset 0x6c0
    const int* mRepathTime_s{};
    // static_param at offset 0x6c8
    const float* mSearchDist_s{};
    // static_param at offset 0x6d0
    const float* mSearchAng_s{};
    // static_param at offset 0x6d8
    const bool* mIsUseSight_s{};
    // static_param at offset 0x6e0
    const float* mLineReachableWeaponDist_s{};
};

}  // namespace uking::ai
