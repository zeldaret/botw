#pragma once

#include "Game/AI/Action/actionSendMessage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendMessage4YunBoCannon : public SendMessage {
    SEAD_RTTI_OVERRIDE(SendMessage4YunBoCannon, SendMessage)
public:
    explicit SendMessage4YunBoCannon(const InitArg& arg);
    ~SendMessage4YunBoCannon() override;

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
