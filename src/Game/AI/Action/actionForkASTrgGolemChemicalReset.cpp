#include "Game/AI/Action/actionForkASTrgGolemChemicalReset.h"

namespace uking::action {

ForkASTrgGolemChemicalReset::ForkASTrgGolemChemicalReset(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkASTrgGolemChemicalReset::~ForkASTrgGolemChemicalReset() = default;

bool ForkASTrgGolemChemicalReset::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgGolemChemicalReset::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgGolemChemicalReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgGolemChemicalReset::loadParams_() {
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void ForkASTrgGolemChemicalReset::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
