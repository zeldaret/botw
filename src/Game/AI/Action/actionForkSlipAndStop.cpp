#include "Game/AI/Action/actionForkSlipAndStop.h"

namespace uking::action {

ForkSlipAndStop::ForkSlipAndStop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSlipAndStop::~ForkSlipAndStop() = default;

bool ForkSlipAndStop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSlipAndStop::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSlipAndStop::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSlipAndStop::loadParams_() {
    getStaticParam(&mPosReduceRatioForSlip_s, "PosReduceRatioForSlip");
    getStaticParam(&mAngReduceRatioForSlip_s, "AngReduceRatioForSlip");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mUseLineCheck_s, "UseLineCheck");
}

void ForkSlipAndStop::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
