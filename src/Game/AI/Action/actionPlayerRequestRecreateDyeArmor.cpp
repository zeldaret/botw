#include "Game/AI/Action/actionPlayerRequestRecreateDyeArmor.h"

namespace uking::action {

PlayerRequestRecreateDyeArmor::PlayerRequestRecreateDyeArmor(const InitArg& arg)
    : PlayerAction(arg) {}

PlayerRequestRecreateDyeArmor::~PlayerRequestRecreateDyeArmor() = default;

bool PlayerRequestRecreateDyeArmor::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerRequestRecreateDyeArmor::loadParams_() {}

}  // namespace uking::action
