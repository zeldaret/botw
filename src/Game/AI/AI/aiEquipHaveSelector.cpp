#include "Game/AI/AI/aiEquipHaveSelector.h"

namespace uking::ai {

EquipHaveSelector::EquipHaveSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EquipHaveSelector::~EquipHaveSelector() = default;

bool EquipHaveSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EquipHaveSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EquipHaveSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EquipHaveSelector::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
