#pragma once

#include "Game/AI/Action/actionSendMessageToTargetActor.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendTargetActorRequestShareAwn : public SendMessageToTargetActor {
    SEAD_RTTI_OVERRIDE(SendTargetActorRequestShareAwn, SendMessageToTargetActor)
public:
    explicit SendTargetActorRequestShareAwn(const InitArg& arg);
    ~SendTargetActorRequestShareAwn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
