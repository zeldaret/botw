#include "Game/AI/Action/actionPlayerMasterSwordEquip.h"

namespace uking::action {

PlayerMasterSwordEquip::PlayerMasterSwordEquip(const InitArg& arg) : PlayerAction(arg) {}

PlayerMasterSwordEquip::~PlayerMasterSwordEquip() = default;

bool PlayerMasterSwordEquip::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerMasterSwordEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerMasterSwordEquip::leave_() {
    PlayerAction::leave_();
}

void PlayerMasterSwordEquip::loadParams_() {}

void PlayerMasterSwordEquip::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
