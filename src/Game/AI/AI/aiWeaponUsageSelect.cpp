#include "Game/AI/AI/aiWeaponUsageSelect.h"

namespace uking::ai {

WeaponUsageSelect::WeaponUsageSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool WeaponUsageSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponUsageSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponUsageSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponUsageSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
