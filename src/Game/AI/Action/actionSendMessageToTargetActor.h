#pragma once

#include "Game/AI/Action/actionSendMessage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendMessageToTargetActor : public SendMessage {
    SEAD_RTTI_OVERRIDE(SendMessageToTargetActor, SendMessage)
public:
    explicit SendMessageToTargetActor(const InitArg& arg);
    ~SendMessageToTargetActor() override;

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
