#include "Game/AI/Action/actionDemoPlayerZoraRide.h"

namespace uking::action {

DemoPlayerZoraRide::DemoPlayerZoraRide(const InitArg& arg) : PlayerAction(arg) {}

DemoPlayerZoraRide::~DemoPlayerZoraRide() = default;

bool DemoPlayerZoraRide::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void DemoPlayerZoraRide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void DemoPlayerZoraRide::leave_() {
    PlayerAction::leave_();
}

void DemoPlayerZoraRide::loadParams_() {}

void DemoPlayerZoraRide::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
