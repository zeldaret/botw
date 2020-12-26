#include "Game/AI/Action/actionPlayerDemoWait.h"

namespace uking::action {

PlayerDemoWait::PlayerDemoWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerDemoWait::~PlayerDemoWait() = default;

bool PlayerDemoWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerDemoWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDemoWait::leave_() {
    PlayerAction::leave_();
}

void PlayerDemoWait::loadParams_() {}

void PlayerDemoWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
