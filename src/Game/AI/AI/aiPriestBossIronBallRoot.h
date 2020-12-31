#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossIronBallRoot : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossIronBallRoot, PriestBossMode)
public:
    explicit PriestBossIronBallRoot(const InitArg& arg);
    ~PriestBossIronBallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const int* mAttackPower_s{};
    // static_param at offset 0x48
    const int* mAttackPowerForPlayer_s{};
    // static_param at offset 0x50
    const int* mAtMinDamage_s{};
    // static_param at offset 0x58
    const int* mMagneLightningTime_s{};
    // map_unit_param at offset 0x60
    sead::SafeString mActorName_m{};
};

}  // namespace uking::ai
