#pragma once

#include "Game/Actor/Area/Action/actionAreaActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaHorseSpeedLimitAction : public AreaActionBase {
    SEAD_RTTI_OVERRIDE(AreaHorseSpeedLimitAction, AreaActionBase)
public:
    explicit AreaHorseSpeedLimitAction(const InitArg& arg);
    ~AreaHorseSpeedLimitAction() override;

    bool init_(sead::Heap* heap) override;

protected:
};

}  // namespace uking::action
