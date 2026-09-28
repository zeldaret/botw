#include "Game/Actor/AI/aiTargetPosRotFromMyPos.h"

namespace uking::ai {

TargetPosRotFromMyPos::TargetPosRotFromMyPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetPosRotFromMyPos::~TargetPosRotFromMyPos() = default;

bool TargetPosRotFromMyPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetPosRotFromMyPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetPosRotFromMyPos::leave_() {
    TargetActorPos::leave_();
}

void TargetPosRotFromMyPos::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mIsRandSign_s, "IsRandSign");
    getStaticParam(&mAngle_s, "Angle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mMinDist_s, "MinDist");
}

}  // namespace uking::ai
