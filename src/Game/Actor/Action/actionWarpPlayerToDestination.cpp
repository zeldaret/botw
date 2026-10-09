#include "Game/Actor/Action/actionWarpPlayerToDestination.h"

namespace uking::action {

WarpPlayerToDestination::WarpPlayerToDestination(const InitArg& arg) : DestPlayerWarpBase(arg) {}

WarpPlayerToDestination::~WarpPlayerToDestination() = default;

bool WarpPlayerToDestination::init_(sead::Heap* heap) {
    return DestPlayerWarpBase::init_(heap);
}

void WarpPlayerToDestination::enter_(ksys::act::ai::InlineParamPack* params) {
    DestPlayerWarpBase::enter_(params);
}

void WarpPlayerToDestination::leave_() {
    DestPlayerWarpBase::leave_();
}

void WarpPlayerToDestination::loadParams_() {
    DestPlayerWarpBase::loadParams_();
    getDynamicParam(&mDestinationX_d, "DestinationX");
    getDynamicParam(&mDestinationY_d, "DestinationY");
    getDynamicParam(&mDestinationZ_d, "DestinationZ");
    getDynamicParam(&mDirectionY_d, "DirectionY");
}

void WarpPlayerToDestination::calc_() {
    DestPlayerWarpBase::calc_();
}

}  // namespace uking::action
