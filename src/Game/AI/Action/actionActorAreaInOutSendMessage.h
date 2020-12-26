#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ActorAreaInOutSendMessage : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(ActorAreaInOutSendMessage, AreaTagAction)
public:
    explicit ActorAreaInOutSendMessage(const InitArg& arg);
    ~ActorAreaInOutSendMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x38
    const int* mBufferNum_s{};
};

}  // namespace uking::action
