#include "Game/AI/Action/actionPlayerRequestRecreateDyeArmor.h"

namespace uking::action {

PlayerRequestRecreateDyeArmor::PlayerRequestRecreateDyeArmor(const InitArg& arg)
    : PlayerAction(arg) {}

PlayerRequestRecreateDyeArmor::~PlayerRequestRecreateDyeArmor() = default;

bool PlayerRequestRecreateDyeArmor::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerRequestRecreateDyeArmor::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerRequestRecreateDyeArmor::leave_() {
    PlayerAction::leave_();
}

void PlayerRequestRecreateDyeArmor::loadParams_() {}

void PlayerRequestRecreateDyeArmor::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
