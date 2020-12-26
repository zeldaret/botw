#pragma once

#include "Game/AI/Action/actionSendPlayerNoticeMessageBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendPlayerNoticeMessage : public SendPlayerNoticeMessageBase {
    SEAD_RTTI_OVERRIDE(SendPlayerNoticeMessage, SendPlayerNoticeMessageBase)
public:
    explicit SendPlayerNoticeMessage(const InitArg& arg);
    ~SendPlayerNoticeMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
