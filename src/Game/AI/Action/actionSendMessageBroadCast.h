#pragma once

#include "Game/AI/Action/actionSendMessage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendMessageBroadCast : public SendMessage {
    SEAD_RTTI_OVERRIDE(SendMessageBroadCast, SendMessage)
public:
    explicit SendMessageBroadCast(const InitArg& arg);
    ~SendMessageBroadCast() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    const int* mMsgType_s{};
};

}  // namespace uking::action
