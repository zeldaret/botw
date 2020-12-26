#include "Game/AI/Action/actionRemainsFireDroneRailStop.h"

namespace uking::action {

RemainsFireDroneRailStop::RemainsFireDroneRailStop(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsFireDroneRailStop::~RemainsFireDroneRailStop() = default;

bool RemainsFireDroneRailStop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsFireDroneRailStop::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsFireDroneRailStop::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsFireDroneRailStop::loadParams_() {
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
    getDynamicParam(&mDynStopPos_d, "DynStopPos");
}

void RemainsFireDroneRailStop::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
