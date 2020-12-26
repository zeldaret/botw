#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTalkToPlayerAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTalkToPlayerAction, ksys::act::ai::Action)
public:
    explicit NPCTalkToPlayerAction(const InitArg& arg);
    ~NPCTalkToPlayerAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString* mMessageId_d{};
    // dynamic_param at offset 0x30
    sead::SafeString* mASKeyName_d{};
};

}  // namespace uking::action
