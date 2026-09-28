#include "Game/Actor/Area/Action/actionAreaHorseSpeedLimitAction.h"

namespace uking::action {

AreaHorseSpeedLimitAction::AreaHorseSpeedLimitAction(const InitArg& arg) : AreaActionBase(arg) {}

AreaHorseSpeedLimitAction::~AreaHorseSpeedLimitAction() = default;

bool AreaHorseSpeedLimitAction::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

}  // namespace uking::action
