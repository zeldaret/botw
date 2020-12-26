#pragma once

#include "Game/AI/Action/actionActorAreaInOutSendMessage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyAreaInOutSendMessage : public ActorAreaInOutSendMessage {
    SEAD_RTTI_OVERRIDE(EnemyAreaInOutSendMessage, ActorAreaInOutSendMessage)
public:
    explicit EnemyAreaInOutSendMessage(const InitArg& arg);
    ~EnemyAreaInOutSendMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x68
    const int* mMessageID_s{};
};

}  // namespace uking::action
