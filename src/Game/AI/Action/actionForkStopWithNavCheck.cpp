#include "Game/AI/Action/actionForkStopWithNavCheck.h"

namespace uking::action {

ForkStopWithNavCheck::ForkStopWithNavCheck(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkStopWithNavCheck::~ForkStopWithNavCheck() = default;

bool ForkStopWithNavCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStopWithNavCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkStopWithNavCheck::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkStopWithNavCheck::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
}

void ForkStopWithNavCheck::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
