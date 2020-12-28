#pragma once

#include "Game/AI/Action/actionAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AttackPartBind : public Attack {
    SEAD_RTTI_OVERRIDE(AttackPartBind, Attack)
public:
    explicit AttackPartBind(const InitArg& arg);
    ~AttackPartBind() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd0
    const int* mASSlot_s{};
};

}  // namespace uking::action
