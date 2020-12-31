#include "Game/AI/AI/aiRemainsWindBatteryAttack.h"

namespace uking::ai {

RemainsWindBatteryAttack::RemainsWindBatteryAttack(const InitArg& arg)
    : GuardianBeamAttackBase(arg) {}

RemainsWindBatteryAttack::~RemainsWindBatteryAttack() = default;

bool RemainsWindBatteryAttack::init_(sead::Heap* heap) {
    return GuardianBeamAttackBase::init_(heap);
}

void RemainsWindBatteryAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianBeamAttackBase::enter_(params);
}

void RemainsWindBatteryAttack::leave_() {
    GuardianBeamAttackBase::leave_();
}

void RemainsWindBatteryAttack::loadParams_() {
    GuardianBeamAttackBase::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
