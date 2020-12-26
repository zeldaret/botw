#include "Game/AI/Action/actionWarpPlayerToDestination.h"

namespace uking::action {

WarpPlayerToDestination::WarpPlayerToDestination(const InitArg& arg) : WarpPlayerBase(arg) {}

WarpPlayerToDestination::~WarpPlayerToDestination() = default;

bool WarpPlayerToDestination::init_(sead::Heap* heap) {
    return WarpPlayerBase::init_(heap);
}

void WarpPlayerToDestination::enter_(ksys::act::ai::InlineParamPack* params) {
    WarpPlayerBase::enter_(params);
}

void WarpPlayerToDestination::leave_() {
    WarpPlayerBase::leave_();
}

void WarpPlayerToDestination::loadParams_() {
    WarpPlayerBase::loadParams_();
    getDynamicParam(&mDestinationX_d, "DestinationX");
    getDynamicParam(&mDestinationY_d, "DestinationY");
    getDynamicParam(&mDestinationZ_d, "DestinationZ");
    getDynamicParam(&mDirectionY_d, "DirectionY");
}

void WarpPlayerToDestination::calc_() {
    WarpPlayerBase::calc_();
}

}  // namespace uking::action
