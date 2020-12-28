#include "Game/AI/Action/actionTimeredNeckSpin.h"

namespace uking::action {

TimeredNeckSpin::TimeredNeckSpin(const InitArg& arg) : NeckSpin(arg) {}

TimeredNeckSpin::~TimeredNeckSpin() = default;

void TimeredNeckSpin::enter_(ksys::act::ai::InlineParamPack* params) {
    NeckSpin::enter_(params);
}

void TimeredNeckSpin::leave_() {
    NeckSpin::leave_();
}

void TimeredNeckSpin::loadParams_() {
    NeckSpin::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mSpinSpeedRatio_s, "SpinSpeedRatio");
    getStaticParam(&mInitSpinSpeed_s, "InitSpinSpeed");
}

void TimeredNeckSpin::calc_() {
    NeckSpin::calc_();
}

}  // namespace uking::action
