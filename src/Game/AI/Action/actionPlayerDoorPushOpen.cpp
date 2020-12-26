#include "Game/AI/Action/actionPlayerDoorPushOpen.h"

namespace uking::action {

PlayerDoorPushOpen::PlayerDoorPushOpen(const InitArg& arg) : PlayerAction(arg) {}

PlayerDoorPushOpen::~PlayerDoorPushOpen() = default;

bool PlayerDoorPushOpen::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerDoorPushOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDoorPushOpen::leave_() {
    PlayerAction::leave_();
}

void PlayerDoorPushOpen::loadParams_() {}

void PlayerDoorPushOpen::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
