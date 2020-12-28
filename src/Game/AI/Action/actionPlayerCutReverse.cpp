#include "Game/AI/Action/actionPlayerCutReverse.h"

namespace uking::action {

PlayerCutReverse::PlayerCutReverse(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutReverse::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutReverse::leave_() {
    PlayerAction::leave_();
}

void PlayerCutReverse::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
