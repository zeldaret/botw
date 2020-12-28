#include "Game/AI/Action/actionPlayerPickUp.h"

namespace uking::action {

PlayerPickUp::PlayerPickUp(const InitArg& arg) : PlayerAction(arg) {}

PlayerPickUp::~PlayerPickUp() = default;

bool PlayerPickUp::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerPickUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerPickUp::leave_() {
    PlayerAction::leave_();
}

void PlayerPickUp::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
