#include "Game/AI/Action/actionPlayerDemoAirWait.h"

namespace uking::action {

PlayerDemoAirWait::PlayerDemoAirWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerDemoAirWait::~PlayerDemoAirWait() = default;

bool PlayerDemoAirWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerDemoAirWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDemoAirWait::leave_() {
    PlayerAction::leave_();
}

void PlayerDemoAirWait::loadParams_() {}

void PlayerDemoAirWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
