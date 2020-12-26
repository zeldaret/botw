#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PunchAttack : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(PunchAttack, ActionWithAS)
public:
    explicit PunchAttack(const InitArg& arg);
    ~PunchAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mAttackIntensity_s{};
    // static_param at offset 0x38
    const bool* mIsGuardPierce_s{};
    // static_param at offset 0x40
    const bool* mIsForceGuardBreak_s{};
    // static_param at offset 0x48
    const bool* mIsIniviciblePierce_s{};
    // static_param at offset 0x50
    const bool* mIsImpulseLarge_s{};
    // static_param at offset 0x58
    const bool* mIsHeavy_s{};
    // static_param at offset 0x60
    const bool* mIsHammer_s{};
    // static_param at offset 0x68
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
