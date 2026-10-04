#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventFlagOFFAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventFlagOFFAction, ksys::act::ai::Action)
public:
    explicit EventFlagOFFAction(const InitArg& arg);
    ~EventFlagOFFAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mFlagName_d{};
};

}  // namespace uking::action
