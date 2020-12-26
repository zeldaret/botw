#include "Game/AI/Action/actionWarpToAnchor.h"

namespace uking::action {

WarpToAnchor::WarpToAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToAnchor::~WarpToAnchor() = default;

bool WarpToAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpToAnchor::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpToAnchor::loadParams_() {
    getDynamicParam(&mDirectionY_d, "DirectionY");
    getDynamicParam(&mDestinationY_d, "DestinationY");
    getDynamicParam(&mDestinationZ_d, "DestinationZ");
    getDynamicParam(&mDestinationX_d, "DestinationX");
}

void WarpToAnchor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
