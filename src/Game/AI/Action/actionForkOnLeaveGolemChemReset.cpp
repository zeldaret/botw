#include "Game/AI/Action/actionForkOnLeaveGolemChemReset.h"

namespace uking::action {

ForkOnLeaveGolemChemReset::ForkOnLeaveGolemChemReset(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkOnLeaveGolemChemReset::~ForkOnLeaveGolemChemReset() = default;

bool ForkOnLeaveGolemChemReset::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOnLeaveGolemChemReset::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkOnLeaveGolemChemReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkOnLeaveGolemChemReset::loadParams_() {
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void ForkOnLeaveGolemChemReset::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
