#pragma once

#include "Game/Actor/Action/actionAreaInOutSendMessage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyAreaInOutSendMessage : public AreaInOutSendMessage {
    SEAD_RTTI_OVERRIDE(EnemyAreaInOutSendMessage, AreaInOutSendMessage)
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
