#include "Game/AI/AI/aiPrevASSkipSeq.h"

namespace uking::ai {

PrevASSkipSeq::PrevASSkipSeq(const InitArg& arg) : SeqTwoAction(arg) {}

PrevASSkipSeq::~PrevASSkipSeq() = default;

bool PrevASSkipSeq::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void PrevASSkipSeq::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void PrevASSkipSeq::leave_() {
    SeqTwoAction::leave_();
}

void PrevASSkipSeq::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mPrevASName_s, "PrevASName");
}

}  // namespace uking::ai
