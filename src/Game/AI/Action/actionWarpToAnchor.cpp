#include "Game/AI/Action/actionWarpToAnchor.h"

namespace uking::action {

WarpToAnchor::WarpToAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToAnchor::~WarpToAnchor() = default;

bool WarpToAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToAnchor::loadParams_() {
    getDynamicParam(&mDirectionY_d, "DirectionY");
    getDynamicParam(&mDestinationY_d, "DestinationY");
    getDynamicParam(&mDestinationZ_d, "DestinationZ");
    getDynamicParam(&mDestinationX_d, "DestinationX");
}

}  // namespace uking::action
