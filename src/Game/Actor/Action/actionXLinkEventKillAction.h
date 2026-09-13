#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class XLinkEventKillAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(XLinkEventKillAction, ksys::act::ai::Action)
public:
    explicit XLinkEventKillAction(const InitArg& arg);
    ~XLinkEventKillAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mELinkKey_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mSLinkKey_d{};
};

}  // namespace uking::action
