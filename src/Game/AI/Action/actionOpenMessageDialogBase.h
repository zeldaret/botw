#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenMessageDialogBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OpenMessageDialogBase, ksys::act::ai::Action)
public:
    explicit OpenMessageDialogBase(const InitArg& arg);
    ~OpenMessageDialogBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mCloseDialogOption_d{};
    // dynamic_param at offset 0x28
    int* mMessageOpenDelayTime_d{};
    // dynamic_param at offset 0x30
    bool* mIsCloseMessageDialog_d{};
    // dynamic_param at offset 0x38
    bool* mIsBecomingSpeaker_d{};
    // dynamic_param at offset 0x40
    bool* mIsOverWriteLabelActorName_d{};
    // dynamic_param at offset 0x48
    bool* mIsWaitAS_d{};
    // dynamic_param at offset 0x50
    sead::SafeString mMessageId_d{};
};

}  // namespace uking::action
