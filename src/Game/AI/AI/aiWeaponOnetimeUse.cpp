#include "Game/AI/AI/aiWeaponOnetimeUse.h"

namespace uking::ai {

WeaponOnetimeUse::WeaponOnetimeUse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponOnetimeUse::~WeaponOnetimeUse() = default;

bool WeaponOnetimeUse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponOnetimeUse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponOnetimeUse::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponOnetimeUse::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
