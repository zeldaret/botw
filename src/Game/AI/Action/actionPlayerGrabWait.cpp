#include "Game/AI/Action/actionPlayerGrabWait.h"

namespace uking::action {

PlayerGrabWait::PlayerGrabWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerGrabWait::~PlayerGrabWait() = default;

bool PlayerGrabWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerGrabWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabWait::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabWait::loadParams_() {}

void PlayerGrabWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
