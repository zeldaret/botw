#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenGetDemoDialog : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OpenGetDemoDialog, ksys::act::ai::Action)
public:
    explicit OpenGetDemoDialog(const InitArg& arg);
    ~OpenGetDemoDialog() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsInvalidOpenPouch_d{};
    // dynamic_param at offset 0x28
    bool* mUseLastTryGetItemName_d{};
    // dynamic_param at offset 0x30
    bool* mEnableMultiGet_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mTargetActorName_d{};
};

}  // namespace uking::action
