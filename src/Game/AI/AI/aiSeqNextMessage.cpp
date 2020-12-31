#include "Game/AI/AI/aiSeqNextMessage.h"

namespace uking::ai {

SeqNextMessage::SeqNextMessage(const InitArg& arg) : SeqTwoAction(arg) {}

SeqNextMessage::~SeqNextMessage() = default;

bool SeqNextMessage::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void SeqNextMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void SeqNextMessage::leave_() {
    SeqTwoAction::leave_();
}

void SeqNextMessage::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mDelayTimeMax_s, "DelayTimeMax");
}

}  // namespace uking::ai
