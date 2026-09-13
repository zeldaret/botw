#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkChainAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkChainAttack, ksys::act::ai::Ai)
public:
    explicit WolfLinkChainAttack(const InitArg& arg);
    ~WolfLinkChainAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mNumAttacks_s{};
    // static_param at offset 0x40
    const float* mAnimalUnitRate_s{};
    // static_param at offset 0x48
    const float* mBeginEndAnimASPlayRate_s{};
    // static_param at offset 0x50
    const float* mTurnAnimPlayRate_s{};
    // static_param at offset 0x58
    const float* mAttackAnimPlayRate_s{};
    // static_param at offset 0x60
    const float* mAttackAnimMinDistance_s{};
    // static_param at offset 0x68
    const float* mAttackDistanceOffset_s{};
    // static_param at offset 0x70
    const bool* mIsInvincible_s{};
    // static_param at offset 0x78
    const bool* mIsIncrementHitOnMiss_s{};
};

}  // namespace uking::ai
