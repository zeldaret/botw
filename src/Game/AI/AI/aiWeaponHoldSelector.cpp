#include "Game/AI/AI/aiWeaponHoldSelector.h"

namespace uking::ai {

WeaponHoldSelector::WeaponHoldSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponHoldSelector::~WeaponHoldSelector() = default;

bool WeaponHoldSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponHoldSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponHoldSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponHoldSelector::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
