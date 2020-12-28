#include "Game/AI/Action/actionPlayerEquipNearMasterSword.h"

namespace uking::action {

PlayerEquipNearMasterSword::PlayerEquipNearMasterSword(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerEquipNearMasterSword::~PlayerEquipNearMasterSword() = default;

bool PlayerEquipNearMasterSword::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerEquipNearMasterSword::loadParams_() {}

}  // namespace uking::action
