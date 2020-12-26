#pragma once

#include "Game/AI/Action/actionActorAreaInOutSendMessage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerAreaInOutSendMessage : public ActorAreaInOutSendMessage {
    SEAD_RTTI_OVERRIDE(PlayerAreaInOutSendMessage, ActorAreaInOutSendMessage)
public:
    explicit PlayerAreaInOutSendMessage(const InitArg& arg);
    ~PlayerAreaInOutSendMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x68
    const int* mMessageSet_s{};
};

}  // namespace uking::action
