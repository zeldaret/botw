#include "Game/AI/Action/actionPlayerBowFall.h"

namespace uking::action {

PlayerBowFall::PlayerBowFall(const InitArg& arg) : PlayerFall(arg) {}

void PlayerBowFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerFall::enter_(params);
}

void PlayerBowFall::leave_() {
    PlayerFall::leave_();
}

void PlayerBowFall::loadParams_() {
    PlayerFall::loadParams_();
}

void PlayerBowFall::calc_() {
    PlayerFall::calc_();
}

}  // namespace uking::action
