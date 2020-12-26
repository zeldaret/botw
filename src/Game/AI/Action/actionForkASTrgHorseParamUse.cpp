#include "Game/AI/Action/actionForkASTrgHorseParamUse.h"

namespace uking::action {

ForkASTrgHorseParamUse::ForkASTrgHorseParamUse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgHorseParamUse::~ForkASTrgHorseParamUse() = default;

bool ForkASTrgHorseParamUse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgHorseParamUse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgHorseParamUse::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgHorseParamUse::loadParams_() {}

void ForkASTrgHorseParamUse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
