#include "Game/Actor/AI/aiSeqTwoLineReachableTargetAction.h"

namespace uking::ai {

SeqTwoLineReachableTargetAction::SeqTwoLineReachableTargetAction(const InitArg& arg)
    : SeqTwoLineReachableTarget(arg) {}

SeqTwoLineReachableTargetAction::~SeqTwoLineReachableTargetAction() = default;

bool SeqTwoLineReachableTargetAction::init_(sead::Heap* heap) {
    return SeqTwoLineReachableTarget::init_(heap);
}

void SeqTwoLineReachableTargetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoLineReachableTarget::enter_(params);
}

void SeqTwoLineReachableTargetAction::leave_() {
    SeqTwoLineReachableTarget::leave_();
}

void SeqTwoLineReachableTargetAction::loadParams_() {
    SeqTwoLineReachableTarget::loadParams_();
}

}  // namespace uking::ai
