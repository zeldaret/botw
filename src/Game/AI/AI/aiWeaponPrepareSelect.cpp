#include "Game/AI/AI/aiWeaponPrepareSelect.h"

namespace uking::ai {

WeaponPrepareSelect::WeaponPrepareSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponPrepareSelect::~WeaponPrepareSelect() = default;

bool WeaponPrepareSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponPrepareSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponPrepareSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponPrepareSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
