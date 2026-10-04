#include "Game/Actor/Area/Action/actionAreaHorseSpeedLimitAction.h"

namespace uking::action {

AreaHorseSpeedLimitAction::AreaHorseSpeedLimitAction(const InitArg& arg) : AreaTagAction(arg) {}

AreaHorseSpeedLimitAction::~AreaHorseSpeedLimitAction() = default;

bool AreaHorseSpeedLimitAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

}  // namespace uking::action
