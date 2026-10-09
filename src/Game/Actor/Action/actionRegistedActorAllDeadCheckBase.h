#pragma once

#include "Game/Actor/Action/actionRegistedActorSetActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RegistedActorAllDeadCheckBase : public RegistedActorSetActionBase {
    SEAD_RTTI_OVERRIDE(RegistedActorAllDeadCheckBase, RegistedActorSetActionBase)
public:
    explicit RegistedActorAllDeadCheckBase(const InitArg& arg);
    ~RegistedActorAllDeadCheckBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
