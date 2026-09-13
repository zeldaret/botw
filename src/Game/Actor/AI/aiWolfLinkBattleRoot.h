#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkBattleRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkBattleRoot, ksys::act::ai::Ai)
public:
    explicit WolfLinkBattleRoot(const InitArg& arg);
    ~WolfLinkBattleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAttackIntiationRange_s{};
    // static_param at offset 0x40
    const float* mChanceToBarkOnAttackFail_s{};
    // static_param at offset 0x48
    const bool* mUseChainAttack_s{};
    // dynamic_param at offset 0x50
    float* mKeepTargetRange_d{};
};

}  // namespace uking::ai
