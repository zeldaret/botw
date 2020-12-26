#include "Game/AI/Action/actionPlayerEquipHaveMasterSword.h"

namespace uking::action {

PlayerEquipHaveMasterSword::PlayerEquipHaveMasterSword(const InitArg& arg) : PlayerAction(arg) {}

PlayerEquipHaveMasterSword::~PlayerEquipHaveMasterSword() = default;

bool PlayerEquipHaveMasterSword::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerEquipHaveMasterSword::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerEquipHaveMasterSword::leave_() {
    PlayerAction::leave_();
}

void PlayerEquipHaveMasterSword::loadParams_() {}

void PlayerEquipHaveMasterSword::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
