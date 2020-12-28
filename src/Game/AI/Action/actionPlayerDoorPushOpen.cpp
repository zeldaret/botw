#include "Game/AI/Action/actionPlayerDoorPushOpen.h"

namespace uking::action {

PlayerDoorPushOpen::PlayerDoorPushOpen(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDoorPushOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDoorPushOpen::leave_() {
    PlayerAction::leave_();
}

void PlayerDoorPushOpen::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
