#pragma once

#include "Game/AI/Action/actionFallAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FallAttackWithAtAttr : public FallAttack {
    SEAD_RTTI_OVERRIDE(FallAttackWithAtAttr, FallAttack)
public:
    explicit FallAttackWithAtAttr(const InitArg& arg);
    ~FallAttackWithAtAttr() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    const int* mAtAttr_s{};
    // static_param at offset 0x90
    const int* mAtAttrNoWeapon_s{};
};

}  // namespace uking::action
