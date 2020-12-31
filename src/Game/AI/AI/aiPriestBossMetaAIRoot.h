#pragma once

#include "Game/AI/AI/aiPriestBossMeta.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossMetaAIRoot : public PriestBossMeta {
    SEAD_RTTI_OVERRIDE(PriestBossMetaAIRoot, PriestBossMeta)
public:
    explicit PriestBossMetaAIRoot(const InitArg& arg);
    ~PriestBossMetaAIRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const int* mLife_s{};
    // static_param at offset 0x58
    const float* mPlayerRecoverFromFallFrames_s{};
    // static_param at offset 0x60
    sead::SafeString mBowActorName_s{};
    // static_param at offset 0x70
    sead::SafeString mArrowActorName_s{};
    // static_param at offset 0x80
    sead::SafeString mWeaponActorName_s{};
    // static_param at offset 0x90
    sead::SafeString mThunderActorName_s{};
    // map_unit_param at offset 0xa0
    const int* mPriestBossStartPhase_m{};
    // map_unit_param at offset 0xa8
    sead::SafeString mUniqueNameMessageLabel_m{};
};

}  // namespace uking::ai
