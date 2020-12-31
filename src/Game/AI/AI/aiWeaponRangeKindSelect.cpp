#include "Game/AI/AI/aiWeaponRangeKindSelect.h"

namespace uking::ai {

WeaponRangeKindSelect::WeaponRangeKindSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool WeaponRangeKindSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponRangeKindSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponRangeKindSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponRangeKindSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
