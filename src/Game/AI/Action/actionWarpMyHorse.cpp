#include "Game/AI/Action/actionWarpMyHorse.h"

namespace uking::action {

WarpMyHorse::WarpMyHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpMyHorse::~WarpMyHorse() = default;

bool WarpMyHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpMyHorse::loadParams_() {
    getDynamicParam(&mPositionX_d, "PositionX");
    getDynamicParam(&mPositionY_d, "PositionY");
    getDynamicParam(&mPositionZ_d, "PositionZ");
    getDynamicParam(&mDirection_d, "Direction");
}

}  // namespace uking::action
