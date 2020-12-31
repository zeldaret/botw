#include "Game/AI/AI/aiVacuumedBombDamageSelect.h"

namespace uking::ai {

VacuumedBombDamageSelect::VacuumedBombDamageSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

VacuumedBombDamageSelect::~VacuumedBombDamageSelect() = default;

bool VacuumedBombDamageSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void VacuumedBombDamageSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void VacuumedBombDamageSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void VacuumedBombDamageSelect::loadParams_() {
    getAITreeVariable(&mVacuumedExplodingBomb_a, "VacuumedExplodingBomb");
}

}  // namespace uking::ai
