#include "Game/AI/Action/actionResetChemicalStateNeutral.h"

namespace uking::action {

ResetChemicalStateNeutral::ResetChemicalStateNeutral(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ResetChemicalStateNeutral::~ResetChemicalStateNeutral() = default;

bool ResetChemicalStateNeutral::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetChemicalStateNeutral::loadParams_() {}

}  // namespace uking::action
