#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RequestEvent : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RequestEvent, ksys::act::ai::Action)
public:
    explicit RequestEvent(const InitArg& arg);
    ~RequestEvent() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsSelfEvent_s{};
    // static_param at offset 0x28
    const bool* mIsAddEntrySelfName_s{};
    // static_param at offset 0x30
    const bool* mIsLoadEvent_s{};
    // static_param at offset 0x38
    const bool* mIsPauseOtherActors_s{};
    // static_param at offset 0x40
    const bool* mIsWaitRun_s{};
    // static_param at offset 0x48
    sead::SafeString mEventName_s{};
    // static_param at offset 0x58
    sead::SafeString mEntryPointName_s{};
};

}  // namespace uking::action
