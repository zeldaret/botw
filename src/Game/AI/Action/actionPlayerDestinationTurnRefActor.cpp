#include "Game/AI/Action/actionPlayerDestinationTurnRefActor.h"

namespace uking::action {

PlayerDestinationTurnRefActor::PlayerDestinationTurnRefActor(const InitArg& arg)
    : PlayerAction(arg) {}

PlayerDestinationTurnRefActor::~PlayerDestinationTurnRefActor() = default;

void PlayerDestinationTurnRefActor::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDestinationTurnRefActor::leave_() {
    PlayerAction::leave_();
}

void PlayerDestinationTurnRefActor::loadParams_() {
    getDynamicParam(&mUniqName_d, "UniqName");
}

void PlayerDestinationTurnRefActor::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
