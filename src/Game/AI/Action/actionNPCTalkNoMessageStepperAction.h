#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTalkNoMessageStepperAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTalkNoMessageStepperAction, ksys::act::ai::Action)
public:
    explicit NPCTalkNoMessageStepperAction(const InitArg& arg);
    ~NPCTalkNoMessageStepperAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mMessageId_d{};
};

}  // namespace uking::action
