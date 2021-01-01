#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventUnregisterFromDeathCounter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventUnregisterFromDeathCounter, ksys::act::ai::Action)
public:
    explicit EventUnregisterFromDeathCounter(const InitArg& arg);
    ~EventUnregisterFromDeathCounter() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mActorName_d{};
};

}  // namespace uking::action
