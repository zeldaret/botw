#include "Game/AI/Action/actionResetChemicalStateNeutral.h"

namespace uking::action {

ResetChemicalStateNeutral::ResetChemicalStateNeutral(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ResetChemicalStateNeutral::~ResetChemicalStateNeutral() = default;

bool ResetChemicalStateNeutral::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetChemicalStateNeutral::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ResetChemicalStateNeutral::leave_() {
    ksys::act::ai::Action::leave_();
}

void ResetChemicalStateNeutral::loadParams_() {}

void ResetChemicalStateNeutral::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
