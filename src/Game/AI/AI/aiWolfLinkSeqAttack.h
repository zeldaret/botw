#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkSeqAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkSeqAttack, ksys::act::ai::Ai)
public:
    explicit WolfLinkSeqAttack(const InitArg& arg);
    ~WolfLinkSeqAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDistBeginAttackAnimation_s{};
    // static_param at offset 0x40
    const float* mAngleReqBeginAttackAnimationMin_s{};
    // static_param at offset 0x48
    const float* mAngleReqBeginAttackAnimationMax_s{};
    // static_param at offset 0x50
    const bool* mPlayOnMissAI_s{};
    // static_param at offset 0x58
    const bool* mChargeChainAttackOnHit_s{};
};

}  // namespace uking::ai
