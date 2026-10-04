#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventDisableMiniGameTime : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventDisableMiniGameTime, ksys::act::ai::Action)
public:
    explicit EventDisableMiniGameTime(const InitArg& arg);
    ~EventDisableMiniGameTime() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
