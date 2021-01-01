#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoVoiceTrigger : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoVoiceTrigger, ksys::act::ai::Action)
public:
    explicit DemoVoiceTrigger(const InitArg& arg);
    ~DemoVoiceTrigger() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsHideCaption_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mLabel_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mActorInstance_d{};
};

}  // namespace uking::action
