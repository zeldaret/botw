#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NoDeleteCurrentActor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NoDeleteCurrentActor, ksys::act::ai::Action)
public:
    explicit NoDeleteCurrentActor(const InitArg& arg);
    ~NoDeleteCurrentActor() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
