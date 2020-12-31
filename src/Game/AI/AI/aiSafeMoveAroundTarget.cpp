#include "Game/AI/AI/aiSafeMoveAroundTarget.h"

namespace uking::ai {

SafeMoveAroundTarget::SafeMoveAroundTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SafeMoveAroundTarget::~SafeMoveAroundTarget() = default;

bool SafeMoveAroundTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SafeMoveAroundTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SafeMoveAroundTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SafeMoveAroundTarget::loadParams_() {
    getStaticParam(&mForceTurnTimeBase_s, "ForceTurnTimeBase");
    getStaticParam(&mForceTurnTimeRand_s, "ForceTurnTimeRand");
    getStaticParam(&mForceTurnStopTimeBase_s, "ForceTurnStopTimeBase");
    getStaticParam(&mForceTurnStopTimeRand_s, "ForceTurnStopTimeRand");
    getStaticParam(&mUpdateTargetPosTime_s, "UpdateTargetPosTime");
    getStaticParam(&mUpdateNumCalc_s, "UpdateNumCalc");
    getStaticParam(&mStartRange_s, "StartRange");
    getStaticParam(&mEndRange_s, "EndRange");
    getStaticParam(&mChangeRangeRate_s, "ChangeRangeRate");
    getStaticParam(&mTargetOffsetDegree_s, "TargetOffsetDegree");
    getStaticParam(&mLOSFailOffsetDegree_s, "LOSFailOffsetDegree");
    getStaticParam(&mMinOffsetLength_s, "MinOffsetLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
