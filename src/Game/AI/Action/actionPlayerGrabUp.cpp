#include "Game/AI/Action/actionPlayerGrabUp.h"

namespace uking::action {

PlayerGrabUp::PlayerGrabUp(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabUp::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabUp::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
