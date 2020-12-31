#include "Game/AI/AI/aiDeadlyBlowWeaponRoot.h"

namespace uking::ai {

DeadlyBlowWeaponRoot::DeadlyBlowWeaponRoot(const InitArg& arg) : WeaponRootAI(arg) {}

DeadlyBlowWeaponRoot::~DeadlyBlowWeaponRoot() = default;

bool DeadlyBlowWeaponRoot::init_(sead::Heap* heap) {
    return WeaponRootAI::init_(heap);
}

void DeadlyBlowWeaponRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
}

void DeadlyBlowWeaponRoot::leave_() {
    WeaponRootAI::leave_();
}

void DeadlyBlowWeaponRoot::loadParams_() {
    WeaponRootAI::loadParams_();
}

}  // namespace uking::ai
