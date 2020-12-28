#include "Game/AI/Action/actionPlayerGrabReady.h"

namespace uking::action {

PlayerGrabReady::PlayerGrabReady(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabReady::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabReady::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabReady::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
