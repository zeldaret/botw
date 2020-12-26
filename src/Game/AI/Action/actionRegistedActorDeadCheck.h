#pragma once

#include "Game/AI/Action/actionRegistedActorDeadCheckBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RegistedActorDeadCheck : public RegistedActorDeadCheckBase {
    SEAD_RTTI_OVERRIDE(RegistedActorDeadCheck, RegistedActorDeadCheckBase)
public:
    explicit RegistedActorDeadCheck(const InitArg& arg);
    ~RegistedActorDeadCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
