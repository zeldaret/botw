#pragma once

#include "Game/Actor/Action/actionSendMessage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendTargetActorMessageBase : public SendMessage {
    SEAD_RTTI_OVERRIDE(SendTargetActorMessageBase, SendMessage)
public:
    explicit SendTargetActorMessageBase(const InitArg& arg);
    ~SendTargetActorMessageBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x28
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
