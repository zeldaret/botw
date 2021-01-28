#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendMessage : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SendMessage, ksys::act::ai::Action)
public:
    explicit SendMessage(const InitArg& arg);
    ~SendMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void doSendMessage() {}

    // static_param at offset 0x20
    const int* mSendTiming_s{};
};

}  // namespace uking::action
