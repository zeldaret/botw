#include "Game/AI/AI/aiHorseRideChargeAttack.h"

namespace uking::ai {

HorseRideChargeAttack::HorseRideChargeAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideChargeAttack::~HorseRideChargeAttack() = default;

bool HorseRideChargeAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideChargeAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseRideChargeAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideChargeAttack::loadParams_() {
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackableAngle_s, "AttackableAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
