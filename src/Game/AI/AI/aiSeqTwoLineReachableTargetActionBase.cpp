#include "Game/AI/AI/aiSeqTwoLineReachableTargetActionBase.h"

namespace uking::ai {

SeqTwoLineReachableTargetActionBase::SeqTwoLineReachableTargetActionBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SeqTwoLineReachableTargetActionBase::~SeqTwoLineReachableTargetActionBase() = default;

bool SeqTwoLineReachableTargetActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqTwoLineReachableTargetActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqTwoLineReachableTargetActionBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqTwoLineReachableTargetActionBase::loadParams_() {
    getStaticParam(&mReachableCheckType1_s, "ReachableCheckType1");
    getStaticParam(&mReachableCheckType2_s, "ReachableCheckType2");
}

}  // namespace uking::ai
