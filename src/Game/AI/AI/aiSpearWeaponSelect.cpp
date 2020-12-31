#include "Game/AI/AI/aiSpearWeaponSelect.h"

namespace uking::ai {

SpearWeaponSelect::SpearWeaponSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SpearWeaponSelect::~SpearWeaponSelect() = default;

bool SpearWeaponSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SpearWeaponSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SpearWeaponSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SpearWeaponSelect::loadParams_() {}

}  // namespace uking::ai
