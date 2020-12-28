#include "Game/AI/Action/actionPlayerSitStart.h"

namespace uking::action {

PlayerSitStart::PlayerSitStart(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSitStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSitStart::leave_() {
    PlayerAction::leave_();
}

void PlayerSitStart::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
