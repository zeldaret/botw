#include "Game/AI/Action/actionPowerupRune.h"

namespace uking::action {

PowerupRune::PowerupRune(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PowerupRune::~PowerupRune() = default;

bool PowerupRune::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PowerupRune::loadParams_() {
    getDynamicParam(&mRuneType_d, "RuneType");
}

}  // namespace uking::action
