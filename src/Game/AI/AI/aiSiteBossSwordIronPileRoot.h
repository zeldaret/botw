#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSwordIronPileRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSwordIronPileRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossSwordIronPileRoot(const InitArg& arg);
    ~SiteBossSwordIronPileRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFallWaitCount_s{};
    // static_param at offset 0x40
    const float* mFallSpeed_s{};
    // static_param at offset 0x48
    const float* mSlopeRate_s{};
    // map_unit_param at offset 0x50
    const int* mAddAtkPower_m{};
    // map_unit_param at offset 0x58
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x60
    const int* mAttackPowerForPlayer_m{};
    // map_unit_param at offset 0x68
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x70
    sead::SafeString mActorName_m{};
};

}  // namespace uking::ai
