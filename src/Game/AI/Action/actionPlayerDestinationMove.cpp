#include "Game/AI/Action/actionPlayerDestinationMove.h"

namespace uking::action {

PlayerDestinationMove::PlayerDestinationMove(const InitArg& arg) : PlayerGuidedMove(arg) {}

void PlayerDestinationMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerGuidedMove::enter_(params);
}

void PlayerDestinationMove::leave_() {
    PlayerGuidedMove::leave_();
}

void PlayerDestinationMove::loadParams_() {
    PlayerGuidedMove::loadParams_();
    getDynamicParam(&mDestPosX_d, "DestPosX");
    getDynamicParam(&mDestPosY_d, "DestPosY");
    getDynamicParam(&mDestPosZ_d, "DestPosZ");
}

void PlayerDestinationMove::calc_() {
    PlayerGuidedMove::calc_();
}

}  // namespace uking::action
