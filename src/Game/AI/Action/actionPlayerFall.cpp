#include "Game/AI/Action/actionPlayerFall.h"

namespace uking::action {

PlayerFall::PlayerFall(const InitArg& arg) : PlayerAction(arg) {}

void PlayerFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerFall::leave_() {
    PlayerAction::leave_();
}

void PlayerFall::loadParams_() {
    getStaticParam(&mNoClimbTime_s, "NoClimbTime");
    getStaticParam(&mNoClimbTimeTired_s, "NoClimbTimeTired");
    getStaticParam(&mNoDispDisableAppTime_s, "NoDispDisableAppTime");
}

void PlayerFall::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
