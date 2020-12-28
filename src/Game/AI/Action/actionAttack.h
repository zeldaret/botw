#pragma once

#include "Game/AI/Action/actionAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Attack : public AttackBase {
    SEAD_RTTI_OVERRIDE(Attack, AttackBase)
public:
    explicit Attack(const InitArg& arg);
    ~Attack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
