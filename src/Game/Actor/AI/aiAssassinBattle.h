#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AssassinBattle, ksys::act::ai::Ai)
public:
    explicit AssassinBattle(const InitArg& arg);
    ~AssassinBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mTiredTime_s{};
    // static_param at offset 0x48
    const float* mWarpDist_s{};
    // static_param at offset 0x50
    const float* mBattleBaseDist_s{};
    // static_param at offset 0x58
    const float* mFirstAttackResetDist_s{};
    // static_param at offset 0x60
    const float* mBattleDistOutDist_s{};
    // static_param at offset 0x68
    const float* mFirstAttackAngle_s{};
    // static_param at offset 0x70
    const float* mTiredDist_s{};
    // static_param at offset 0x78
    const float* mFirstAttackDist_s{};
    // static_param at offset 0x80
    const float* mNearTiredOffset_s{};
    // map_unit_param at offset 0x88
    const float* mTerritoryArea_m{};
};

}  // namespace uking::ai
