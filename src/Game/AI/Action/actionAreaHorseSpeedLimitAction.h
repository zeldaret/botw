#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaHorseSpeedLimitAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(AreaHorseSpeedLimitAction, AreaTagAction)
public:
    explicit AreaHorseSpeedLimitAction(const InitArg& arg);
    ~AreaHorseSpeedLimitAction() override;

    bool init_(sead::Heap* heap) override;

protected:
};

}  // namespace uking::action
