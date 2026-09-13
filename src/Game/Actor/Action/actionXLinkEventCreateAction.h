#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class XLinkEventCreateAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(XLinkEventCreateAction, ksys::act::ai::Action)
public:
    explicit XLinkEventCreateAction(const InitArg& arg);
    ~XLinkEventCreateAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mIsTargetDemoSLinkUser_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mELinkKey_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mSLinkKey_d{};
};

}  // namespace uking::action
