#include "Game/AI/AI/aiTargetPosRotFromMyPos.h"

namespace uking::ai {

TargetPosRotFromMyPos::TargetPosRotFromMyPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetPosRotFromMyPos::~TargetPosRotFromMyPos() = default;

bool TargetPosRotFromMyPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPosRotFromMyPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPosRotFromMyPos::leave_() {
    TargetPosAI::leave_();
}

void TargetPosRotFromMyPos::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mIsRandSign_s, "IsRandSign");
    getStaticParam(&mAngle_s, "Angle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mMinDist_s, "MinDist");
}

}  // namespace uking::ai
