#include "Game/AI/AI/aiRangeCheckSeqTwoAction.h"

namespace uking::ai {

RangeCheckSeqTwoAction::RangeCheckSeqTwoAction(const InitArg& arg) : SeqTargetTwoAction(arg) {}

RangeCheckSeqTwoAction::~RangeCheckSeqTwoAction() = default;

bool RangeCheckSeqTwoAction::init_(sead::Heap* heap) {
    return SeqTargetTwoAction::init_(heap);
}

void RangeCheckSeqTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTargetTwoAction::enter_(params);
}

void RangeCheckSeqTwoAction::leave_() {
    SeqTargetTwoAction::leave_();
}

void RangeCheckSeqTwoAction::loadParams_() {
    SeqTargetTwoAction::loadParams_();
    getStaticParam(&mRange_s, "Range");
    getStaticParam(&mCheckFar_s, "CheckFar");
}

}  // namespace uking::ai
