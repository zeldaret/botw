#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventRecoverPlayerCondition : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventRecoverPlayerCondition, ksys::act::ai::Action)
public:
    explicit EventRecoverPlayerCondition(const InitArg& arg);
    ~EventRecoverPlayerCondition() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
