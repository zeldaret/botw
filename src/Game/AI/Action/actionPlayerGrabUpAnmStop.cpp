#include "Game/AI/Action/actionPlayerGrabUpAnmStop.h"

namespace uking::action {

PlayerGrabUpAnmStop::PlayerGrabUpAnmStop(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabUpAnmStop::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabUpAnmStop::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabUpAnmStop::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
