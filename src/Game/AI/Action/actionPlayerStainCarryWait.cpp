#include "Game/AI/Action/actionPlayerStainCarryWait.h"

namespace uking::action {

PlayerStainCarryWait::PlayerStainCarryWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerStainCarryWait::~PlayerStainCarryWait() = default;

bool PlayerStainCarryWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerStainCarryWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerStainCarryWait::leave_() {
    PlayerAction::leave_();
}

void PlayerStainCarryWait::loadParams_() {}

void PlayerStainCarryWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
