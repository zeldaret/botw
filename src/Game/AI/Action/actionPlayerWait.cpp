#include "Game/AI/Action/actionPlayerWait.h"

namespace uking::action {

PlayerWait::PlayerWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerWait::~PlayerWait() = default;

bool PlayerWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWait::leave_() {
    PlayerAction::leave_();
}

void PlayerWait::loadParams_() {}

void PlayerWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
