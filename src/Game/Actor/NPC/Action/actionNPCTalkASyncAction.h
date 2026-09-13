#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTalkASyncAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTalkASyncAction, ksys::act::ai::Action)
public:
    explicit NPCTalkASyncAction(const InitArg& arg);
    ~NPCTalkASyncAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mDispFrame_d{};
    // dynamic_param at offset 0x28
    bool* mIsChecked_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mMessageId_d{};
};

}  // namespace uking::action
