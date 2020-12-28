#include "Game/AI/Action/actionPlayerBow.h"

namespace uking::action {

PlayerBow::PlayerBow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerBow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerBow::leave_() {
    PlayerAction::leave_();
}

void PlayerBow::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
