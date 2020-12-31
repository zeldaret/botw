#include "Game/AI/AI/aiNormalHumanEquipableShield.h"

namespace uking::ai {

NormalHumanEquipableShield::NormalHumanEquipableShield(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

NormalHumanEquipableShield::~NormalHumanEquipableShield() = default;

bool NormalHumanEquipableShield::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NormalHumanEquipableShield::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NormalHumanEquipableShield::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NormalHumanEquipableShield::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
