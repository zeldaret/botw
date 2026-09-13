#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class XLinkEventEnable : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(XLinkEventEnable, ksys::act::ai::Action)
public:
    explicit XLinkEventEnable(const InitArg& arg);
    ~XLinkEventEnable() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mIsEnable_d{};
};

}  // namespace uking::action
