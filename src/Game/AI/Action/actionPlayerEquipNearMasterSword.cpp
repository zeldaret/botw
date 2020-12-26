#include "Game/AI/Action/actionPlayerEquipNearMasterSword.h"

namespace uking::action {

PlayerEquipNearMasterSword::PlayerEquipNearMasterSword(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerEquipNearMasterSword::~PlayerEquipNearMasterSword() = default;

bool PlayerEquipNearMasterSword::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerEquipNearMasterSword::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayerEquipNearMasterSword::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerEquipNearMasterSword::loadParams_() {}

void PlayerEquipNearMasterSword::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
