#include "Game/AI/Action/actionPlayerDoorPullOpen.h"

namespace uking::action {

PlayerDoorPullOpen::PlayerDoorPullOpen(const InitArg& arg) : PlayerAction(arg) {}

PlayerDoorPullOpen::~PlayerDoorPullOpen() = default;

bool PlayerDoorPullOpen::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerDoorPullOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDoorPullOpen::leave_() {
    PlayerAction::leave_();
}

void PlayerDoorPullOpen::loadParams_() {}

void PlayerDoorPullOpen::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
