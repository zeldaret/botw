#pragma once

#include "Game/Actor/Action/actionAreaInOutSendMessage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerAreaInOutSendMessage : public AreaInOutSendMessage {
    SEAD_RTTI_OVERRIDE(PlayerAreaInOutSendMessage, AreaInOutSendMessage)
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
