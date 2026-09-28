#include "Game/Actor/AI/aiTargetPosDynParamRotFromMyPos.h"

namespace uking::ai {

TargetPosDynParamRotFromMyPos::TargetPosDynParamRotFromMyPos(const InitArg& arg)
    : TargetActorPos(arg) {}

TargetPosDynParamRotFromMyPos::~TargetPosDynParamRotFromMyPos() = default;

bool TargetPosDynParamRotFromMyPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetPosDynParamRotFromMyPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetPosDynParamRotFromMyPos::leave_() {
    TargetActorPos::leave_();
}

void TargetPosDynParamRotFromMyPos::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mMinDist_s, "MinDist");
    getDynamicParam(&mAngle_d, "Angle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
