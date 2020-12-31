#include "Game/AI/AI/aiSeqTwoLineReachableTargetAction.h"

namespace uking::ai {

SeqTwoLineReachableTargetAction::SeqTwoLineReachableTargetAction(const InitArg& arg)
    : SeqTwoLineReachableTargetActionBase(arg) {}

SeqTwoLineReachableTargetAction::~SeqTwoLineReachableTargetAction() = default;

bool SeqTwoLineReachableTargetAction::init_(sead::Heap* heap) {
    return SeqTwoLineReachableTargetActionBase::init_(heap);
}

void SeqTwoLineReachableTargetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoLineReachableTargetActionBase::enter_(params);
}

void SeqTwoLineReachableTargetAction::leave_() {
    SeqTwoLineReachableTargetActionBase::leave_();
}

void SeqTwoLineReachableTargetAction::loadParams_() {
    SeqTwoLineReachableTargetActionBase::loadParams_();
}

}  // namespace uking::ai
