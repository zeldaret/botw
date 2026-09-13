#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventCancelGet : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventCancelGet, ksys::act::ai::Action)
public:
    explicit EventCancelGet(const InitArg& arg);
    ~EventCancelGet() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
