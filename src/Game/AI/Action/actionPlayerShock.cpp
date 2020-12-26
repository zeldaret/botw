#include "Game/AI/Action/actionPlayerShock.h"

namespace uking::action {

PlayerShock::PlayerShock(const InitArg& arg) : PlayerAction(arg) {}

PlayerShock::~PlayerShock() = default;

bool PlayerShock::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerShock::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerShock::leave_() {
    PlayerAction::leave_();
}

void PlayerShock::loadParams_() {}

void PlayerShock::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
