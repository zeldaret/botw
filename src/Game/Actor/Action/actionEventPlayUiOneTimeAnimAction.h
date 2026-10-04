#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventPlayUiOneTimeAnimAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventPlayUiOneTimeAnimAction, ksys::act::ai::Action)
public:
    explicit EventPlayUiOneTimeAnimAction(const InitArg& arg);
    ~EventPlayUiOneTimeAnimAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mClipIndex_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mScreenName_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mAnimName_d{};
};

}  // namespace uking::action
