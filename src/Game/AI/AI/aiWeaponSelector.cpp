#include "Game/AI/AI/aiWeaponSelector.h"

namespace uking::ai {

WeaponSelector::WeaponSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool WeaponSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponSelector::loadParams_() {}

}  // namespace uking::ai
