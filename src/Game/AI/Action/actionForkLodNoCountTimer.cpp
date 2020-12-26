#include "Game/AI/Action/actionForkLodNoCountTimer.h"

namespace uking::action {

ForkLodNoCountTimer::ForkLodNoCountTimer(const InitArg& arg) : Fork(arg) {}

ForkLodNoCountTimer::~ForkLodNoCountTimer() = default;

bool ForkLodNoCountTimer::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkLodNoCountTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkLodNoCountTimer::leave_() {
    Fork::leave_();
}

void ForkLodNoCountTimer::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
    getStaticParam(&mWaitFrameRand_s, "WaitFrameRand");
    getStaticParam(&mCamDist_s, "CamDist");
    getStaticParam(&mIsTrgStart_s, "IsTrgStart");
}

void ForkLodNoCountTimer::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
