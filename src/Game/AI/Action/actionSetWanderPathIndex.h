#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetWanderPathIndex : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetWanderPathIndex, ksys::act::ai::Action)
public:
    explicit SetWanderPathIndex(const InitArg& arg);
    ~SetWanderPathIndex() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
