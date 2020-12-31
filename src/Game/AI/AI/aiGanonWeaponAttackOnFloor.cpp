#include "Game/AI/AI/aiGanonWeaponAttackOnFloor.h"

namespace uking::ai {

GanonWeaponAttackOnFloor::GanonWeaponAttackOnFloor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonWeaponAttackOnFloor::~GanonWeaponAttackOnFloor() = default;

bool GanonWeaponAttackOnFloor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonWeaponAttackOnFloor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonWeaponAttackOnFloor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonWeaponAttackOnFloor::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
