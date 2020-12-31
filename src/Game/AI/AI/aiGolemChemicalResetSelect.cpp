#include "Game/AI/AI/aiGolemChemicalResetSelect.h"

namespace uking::ai {

GolemChemicalResetSelect::GolemChemicalResetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemChemicalResetSelect::~GolemChemicalResetSelect() = default;

bool GolemChemicalResetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemChemicalResetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolemChemicalResetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemChemicalResetSelect::loadParams_() {
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai
