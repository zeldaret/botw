#pragma once

#include "Game/AI/AI/aiSiteBossRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSpearRoot : public SiteBossRoot {
    SEAD_RTTI_OVERRIDE(SiteBossSpearRoot, SiteBossRoot)
public:
    explicit SiteBossSpearRoot(const InitArg& arg);
    ~SiteBossSpearRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xf8
    const int* mThrowSpearAttackPower_s{};
    // static_param at offset 0x100
    const int* mThrowSpearMinDmage_s{};
    // static_param at offset 0x108
    const int* mIceSplinterAttackPower_s{};
    // static_param at offset 0x110
    const int* mIceSplinterMinDamage_s{};
};

}  // namespace uking::ai
