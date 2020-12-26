#include "Game/AI/Action/actionPlayerGrabStand.h"

namespace uking::action {

PlayerGrabStand::PlayerGrabStand(const InitArg& arg) : PlayerAction(arg) {}

PlayerGrabStand::~PlayerGrabStand() = default;

bool PlayerGrabStand::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerGrabStand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabStand::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabStand::loadParams_() {}

void PlayerGrabStand::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
