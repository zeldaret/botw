#pragma once

#include "Game/Actor/Action/actionTurnGiantAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AttackWithAS : public TurnGiantAttack {
    SEAD_RTTI_OVERRIDE(AttackWithAS, TurnGiantAttack)
public:
    explicit AttackWithAS(const InitArg& arg);
    ~AttackWithAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x128
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
