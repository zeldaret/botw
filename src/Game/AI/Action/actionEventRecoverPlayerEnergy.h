#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventRecoverPlayerEnergy : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventRecoverPlayerEnergy, ksys::act::ai::Action)
public:
    explicit EventRecoverPlayerEnergy(const InitArg& arg);
    ~EventRecoverPlayerEnergy() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
