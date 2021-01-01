#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTalk : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTalk, ksys::act::ai::Action)
public:
    explicit NPCTalk(const InitArg& arg);
    ~NPCTalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mIsRemainOpeningDialog_s{};
    // static_param at offset 0x28
    const int* mMinTalkTime_s{};
    // dynamic_param at offset 0x30
    bool* mIsCloseMessageDialog_d{};
    // dynamic_param at offset 0x38
    bool* mIsBecomingSpeaker_d{};
    // dynamic_param at offset 0x40
    bool* mIsOverWriteLabelActorName_d{};
    // dynamic_param at offset 0x48
    sead::SafeString mMessageId_d{};
    // dynamic_param at offset 0x58
    sead::SafeString mASName_d{};
};

}  // namespace uking::action
