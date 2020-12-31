#include "Game/AI/AI/aiWeaponEquipedAI.h"

namespace uking::ai {

WeaponEquipedAI::WeaponEquipedAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponEquipedAI::~WeaponEquipedAI() = default;

void WeaponEquipedAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponEquipedAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai
