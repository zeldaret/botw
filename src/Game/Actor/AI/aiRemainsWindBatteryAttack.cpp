#include "Game/Actor/AI/aiRemainsWindBatteryAttack.h"

namespace uking::ai {

RemainsWindBatteryAttack::RemainsWindBatteryAttack(const InitArg& arg)
    : GuardianCommonBeamAttack(arg) {}

RemainsWindBatteryAttack::~RemainsWindBatteryAttack() = default;

bool RemainsWindBatteryAttack::init_(sead::Heap* heap) {
    return GuardianCommonBeamAttack::init_(heap);
}

void RemainsWindBatteryAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianCommonBeamAttack::enter_(params);
}

void RemainsWindBatteryAttack::leave_() {
    GuardianCommonBeamAttack::leave_();
}

void RemainsWindBatteryAttack::loadParams_() {
    GuardianCommonBeamAttack::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
