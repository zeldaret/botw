#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TriggerAllPartsSleep : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TriggerAllPartsSleep, ksys::act::ai::Action)
public:
    explicit TriggerAllPartsSleep(const InitArg& arg);
    ~TriggerAllPartsSleep() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
