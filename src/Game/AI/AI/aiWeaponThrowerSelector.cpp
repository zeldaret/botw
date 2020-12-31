#include "Game/AI/AI/aiWeaponThrowerSelector.h"

namespace uking::ai {

WeaponThrowerSelector::WeaponThrowerSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponThrowerSelector::~WeaponThrowerSelector() = default;

bool WeaponThrowerSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponThrowerSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponThrowerSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponThrowerSelector::loadParams_() {}

}  // namespace uking::ai
