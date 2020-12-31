#include "Game/AI/AI/aiEquipConditionSelect.h"

namespace uking::ai {

EquipConditionSelect::EquipConditionSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EquipConditionSelect::~EquipConditionSelect() = default;

bool EquipConditionSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EquipConditionSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EquipConditionSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EquipConditionSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
