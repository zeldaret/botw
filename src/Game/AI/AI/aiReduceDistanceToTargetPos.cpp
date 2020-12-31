#include "Game/AI/AI/aiReduceDistanceToTargetPos.h"

namespace uking::ai {

ReduceDistanceToTargetPos::ReduceDistanceToTargetPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReduceDistanceToTargetPos::~ReduceDistanceToTargetPos() = default;

bool ReduceDistanceToTargetPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReduceDistanceToTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ReduceDistanceToTargetPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReduceDistanceToTargetPos::loadParams_() {
    getStaticParam(&mDistanceScale_s, "DistanceScale");
    getStaticParam(&mMinReduceDist_s, "MinReduceDist");
    getStaticParam(&mMaxReduceDist_s, "MaxReduceDist");
    getStaticParam(&mMinDist_s, "MinDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
