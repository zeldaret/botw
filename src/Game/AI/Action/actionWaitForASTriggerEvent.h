#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaitForASTriggerEvent : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaitForASTriggerEvent, ksys::act::ai::Action)
public:
    explicit WaitForASTriggerEvent(const InitArg& arg);
    ~WaitForASTriggerEvent() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mEventType_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mUniqueName_d{};
};

}  // namespace uking::action
