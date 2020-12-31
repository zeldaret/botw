#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HiddenOctarockNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(HiddenOctarockNormal, EnemyNormal)
public:
    explicit HiddenOctarockNormal(const InitArg& arg);
    ~HiddenOctarockNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x3d0
    const float* mOptionHitReactionDelay_s{};
    // static_param at offset 0x3d8
    const bool* mIsSitDown_s{};
    // static_param at offset 0x3e0
    const bool* mIsHitGround_s{};
    // static_param at offset 0x3e8
    const bool* mIsReactionByWigHit_s{};
    // static_param at offset 0x3f0
    const bool* mIsHide_s{};
    // static_param at offset 0x3f8
    const bool* mIsIvalidateSight_s{};
    // static_param at offset 0x400
    const bool* mIsSealHearing_s{};
    // map_unit_param at offset 0x408
    const bool* mIsNearCreate_m{};
};

}  // namespace uking::ai
