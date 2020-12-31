#include "Game/AI/AI/aiLynelTackleMove.h"

namespace uking::ai {

LynelTackleMove::LynelTackleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelTackleMove::~LynelTackleMove() = default;

bool LynelTackleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelTackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelTackleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelTackleMove::loadParams_() {
    getStaticParam(&mThroughDist_s, "ThroughDist");
    getStaticParam(&mCloseEndAngle_s, "CloseEndAngle");
    getStaticParam(&mCloseEndDist_s, "CloseEndDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
