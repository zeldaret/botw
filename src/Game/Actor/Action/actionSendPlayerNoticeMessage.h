#pragma once

#include "Game/Actor/Action/actionSendNoticeMessageBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendPlayerNoticeMessage : public SendNoticeMessageBase {
    SEAD_RTTI_OVERRIDE(SendPlayerNoticeMessage, SendNoticeMessageBase)
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
