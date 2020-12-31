#include "Game/AI/AI/aiAmbushableWeaponShoot.h"

namespace uking::ai {

AmbushableWeaponShoot::AmbushableWeaponShoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AmbushableWeaponShoot::~AmbushableWeaponShoot() = default;

bool AmbushableWeaponShoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AmbushableWeaponShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AmbushableWeaponShoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AmbushableWeaponShoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
