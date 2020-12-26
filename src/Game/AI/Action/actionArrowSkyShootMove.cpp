#include "Game/AI/Action/actionArrowSkyShootMove.h"

namespace uking::action {

ArrowSkyShootMove::ArrowSkyShootMove(const InitArg& arg) : ArrowShootMove(arg) {}

ArrowSkyShootMove::~ArrowSkyShootMove() = default;

bool ArrowSkyShootMove::init_(sead::Heap* heap) {
    return ArrowShootMove::init_(heap);
}

void ArrowSkyShootMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
}

void ArrowSkyShootMove::leave_() {
    ArrowShootMove::leave_();
}

void ArrowSkyShootMove::loadParams_() {
    ArrowShootMove::loadParams_();
    getStaticParam(&mInterval_s, "Interval");
    getStaticParam(&mSkyShootDist_s, "SkyShootDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getDynamicParam(&mPosOffset_d, "PosOffset");
}

void ArrowSkyShootMove::calc_() {
    ArrowShootMove::calc_();
}

}  // namespace uking::action
