#pragma once

#include "Game/AI/Action/actionForkTimer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressSimpleAction : public ForkTimer {
    SEAD_RTTI_OVERRIDE(EnemyFortressSimpleAction, ForkTimer)
public:
    explicit EnemyFortressSimpleAction(const InitArg& arg);
    ~EnemyFortressSimpleAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const int* mNoRequestTime_s{};
    // aitree_variable at offset 0x98
    void* mRegistedActorUnit_a{};
};

}  // namespace uking::action
