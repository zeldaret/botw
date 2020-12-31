#include "Game/AI/AI/aiWeaponTrueFormSelect.h"

namespace uking::ai {

WeaponTrueFormSelect::WeaponTrueFormSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponTrueFormSelect::~WeaponTrueFormSelect() = default;

bool WeaponTrueFormSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponTrueFormSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponTrueFormSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponTrueFormSelect::loadParams_() {}

}  // namespace uking::ai
