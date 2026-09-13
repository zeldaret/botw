#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenMessageDialogTrig : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OpenMessageDialogTrig, ksys::act::ai::Action)
public:
    explicit OpenMessageDialogTrig(const InitArg& arg);
    ~OpenMessageDialogTrig() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mCloseDialogOption_d{};
    // dynamic_param at offset 0x28
    bool* mIsBecomingSpeaker_d{};
    // dynamic_param at offset 0x30
    bool* mIsOverWriteLabelActorName_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mMessageId_d{};
};

}  // namespace uking::action
