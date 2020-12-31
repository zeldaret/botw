#include "Game/AI/AI/aiASWeaponRoot.h"

namespace uking::ai {

ASWeaponRoot::ASWeaponRoot(const InitArg& arg) : WeaponRootAI(arg) {}

ASWeaponRoot::~ASWeaponRoot() = default;

bool ASWeaponRoot::init_(sead::Heap* heap) {
    return WeaponRootAI::init_(heap);
}

void ASWeaponRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
}

void ASWeaponRoot::leave_() {
    WeaponRootAI::leave_();
}

void ASWeaponRoot::loadParams_() {
    WeaponRootAI::loadParams_();
    getStaticParam(&mEquiped_s, "Equiped");
    getStaticParam(&mUnEquiped_s, "UnEquiped");
    getStaticParam(&mThrown_s, "Thrown");
    getStaticParam(&mStick_s, "Stick");
    getStaticParam(&mCancelStick_s, "CancelStick");
}

}  // namespace uking::ai
