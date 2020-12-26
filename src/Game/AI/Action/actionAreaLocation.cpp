#include "Game/AI/Action/actionAreaLocation.h"

namespace uking::action {

AreaLocation::AreaLocation(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AreaLocation::~AreaLocation() = default;

bool AreaLocation::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AreaLocation::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AreaLocation::leave_() {
    ksys::act::ai::Action::leave_();
}

void AreaLocation::loadParams_() {
    getMapUnitParam(&mLocationPriority_m, "LocationPriority");
    getMapUnitParam(&mMessageID_m, "MessageID");
}

void AreaLocation::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
