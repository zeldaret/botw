#include "Game/AI/Action/actionPlayerSpAttack.h"

namespace uking::action {

PlayerSpAttack::PlayerSpAttack(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSpAttack::leave_() {
    PlayerAction::leave_();
}

void PlayerSpAttack::loadParams_() {
    getStaticParam(&mSwordSearchFrame_s, "SwordSearchFrame");
    getStaticParam(&mSwordSearchAngle_s, "SwordSearchAngle");
}

void PlayerSpAttack::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
