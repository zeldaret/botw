#include "Game/AI/Action/actionPlayerDoorPullOpen.h"

namespace uking::action {

PlayerDoorPullOpen::PlayerDoorPullOpen(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDoorPullOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDoorPullOpen::leave_() {
    PlayerAction::leave_();
}

void PlayerDoorPullOpen::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
