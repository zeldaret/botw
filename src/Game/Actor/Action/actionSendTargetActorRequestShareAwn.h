#pragma once

#include "Game/Actor/Action/actionSendTargetActorMessageBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendTargetActorRequestShareAwn : public SendTargetActorMessageBase {
    SEAD_RTTI_OVERRIDE(SendTargetActorRequestShareAwn, SendTargetActorMessageBase)
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
