#include "Game/AI/Action/actionPlayerSkin.h"

namespace uking::action {

PlayerSkin::PlayerSkin(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSkin::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSkin::leave_() {
    PlayerAction::leave_();
}

void PlayerSkin::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
}

void PlayerSkin::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
