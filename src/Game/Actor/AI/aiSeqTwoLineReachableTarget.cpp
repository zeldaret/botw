#include "Game/Actor/AI/aiSeqTwoLineReachableTarget.h"

namespace uking::ai {

SeqTwoLineReachableTarget::SeqTwoLineReachableTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqTwoLineReachableTarget::~SeqTwoLineReachableTarget() = default;

bool SeqTwoLineReachableTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqTwoLineReachableTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqTwoLineReachableTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqTwoLineReachableTarget::loadParams_() {
    getStaticParam(&mReachableCheckType1_s, "ReachableCheckType1");
    getStaticParam(&mReachableCheckType2_s, "ReachableCheckType2");
}

}  // namespace uking::ai
