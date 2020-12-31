#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeFindPlayer : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WizzrobeFindPlayer, ksys::act::ai::Ai)
public:
    explicit WizzrobeFindPlayer(const InitArg& arg);
    ~WizzrobeFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mHomeTerritoryWidth_s{};
    // static_param at offset 0x40
    const float* mHomeTerritoryHeight_s{};
    // static_param at offset 0x48
    const float* mBattleTerritoryWidth_s{};
    // aitree_variable at offset 0x50
    bool* mIsWizzrobeInBattleAreaFlag_a{};
};

}  // namespace uking::ai
