#pragma once

#include "Game/AI/Action/actionChemicalAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChemicalAttackBall : public ChemicalAttack {
    SEAD_RTTI_OVERRIDE(ChemicalAttackBall, ChemicalAttack)
public:
    explicit ChemicalAttackBall(const InitArg& arg);
    ~ChemicalAttackBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    const bool* mIsUseMyRange_s{};
    // static_param at offset 0x88
    const int* mAttackType_s{};
};

}  // namespace uking::action
