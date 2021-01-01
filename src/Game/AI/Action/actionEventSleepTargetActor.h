#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSleepTargetActor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSleepTargetActor, ksys::act::ai::Action)
public:
    explicit EventSleepTargetActor(const InitArg& arg);
    ~EventSleepTargetActor() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mInstanceName_d{};
};

}  // namespace uking::action
