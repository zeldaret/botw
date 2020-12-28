#include "Game/AI/Action/actionPlayerStainWait.h"

namespace uking::action {

PlayerStainWait::PlayerStainWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerStainWait::~PlayerStainWait() = default;

bool PlayerStainWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerStainWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerStainWait::leave_() {
    PlayerAction::leave_();
}

void PlayerStainWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
