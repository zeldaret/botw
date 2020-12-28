#include "Game/AI/Action/actionPlayerHoldUpDRC.h"

namespace uking::action {

PlayerHoldUpDRC::PlayerHoldUpDRC(const InitArg& arg) : PlayerAction(arg) {}

PlayerHoldUpDRC::~PlayerHoldUpDRC() = default;

void PlayerHoldUpDRC::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHoldUpDRC::leave_() {
    PlayerAction::leave_();
}

void PlayerHoldUpDRC::loadParams_() {
    getDynamicParam(&mIsContinued_d, "IsContinued");
    getDynamicParam(&mASName_d, "ASName");
}

void PlayerHoldUpDRC::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
