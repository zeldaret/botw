#pragma once

#include "Game/AI/Action/actionRegistedActorActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RegistedActorBroadCastMessage : public RegistedActorActionBase {
    SEAD_RTTI_OVERRIDE(RegistedActorBroadCastMessage, RegistedActorActionBase)
public:
    explicit RegistedActorBroadCastMessage(const InitArg& arg);
    ~RegistedActorBroadCastMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
