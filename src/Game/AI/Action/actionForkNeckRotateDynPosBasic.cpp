#include "Game/AI/Action/actionForkNeckRotateDynPosBasic.h"

namespace uking::action {

ForkNeckRotateDynPosBasic::ForkNeckRotateDynPosBasic(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkNeckRotateDynPosBasic::~ForkNeckRotateDynPosBasic() = default;

bool ForkNeckRotateDynPosBasic::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkNeckRotateDynPosBasic::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkNeckRotateDynPosBasic::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkNeckRotateDynPosBasic::loadParams_() {
    getStaticParam(&mUseSimpleOffset_s, "UseSimpleOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkNeckRotateDynPosBasic::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
