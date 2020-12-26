#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendPlayerNoticeMessageBase : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(SendPlayerNoticeMessageBase, OnetimeStopASPlay)
public:
    explicit SendPlayerNoticeMessageBase(const InitArg& arg);
    ~SendPlayerNoticeMessageBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    sead::SafeString mTargetActorName_s{};
};

}  // namespace uking::action
