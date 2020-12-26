#include "Game/AI/Action/actionForkNeckOnlyRotateDynPosBasic.h"

namespace uking::action {

ForkNeckOnlyRotateDynPosBasic::ForkNeckOnlyRotateDynPosBasic(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkNeckOnlyRotateDynPosBasic::~ForkNeckOnlyRotateDynPosBasic() = default;

bool ForkNeckOnlyRotateDynPosBasic::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkNeckOnlyRotateDynPosBasic::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkNeckOnlyRotateDynPosBasic::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkNeckOnlyRotateDynPosBasic::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkNeckOnlyRotateDynPosBasic::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
