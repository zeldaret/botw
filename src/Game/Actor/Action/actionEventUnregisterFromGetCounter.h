#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventUnregisterFromGetCounter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventUnregisterFromGetCounter, ksys::act::ai::Action)
public:
    explicit EventUnregisterFromGetCounter(const InitArg& arg);
    ~EventUnregisterFromGetCounter() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mActorName_d{};
};

}  // namespace uking::action
