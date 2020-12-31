#include "Game/AI/AI/aiWeaponSubTypeSelect.h"

namespace uking::ai {

WeaponSubTypeSelect::WeaponSubTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponSubTypeSelect::~WeaponSubTypeSelect() = default;

void WeaponSubTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponSubTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponSubTypeSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
