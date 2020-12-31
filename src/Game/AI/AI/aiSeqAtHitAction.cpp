#include "Game/AI/AI/aiSeqAtHitAction.h"

namespace uking::ai {

SeqAtHitAction::SeqAtHitAction(const InitArg& arg) : SeqTwoAction(arg) {}

SeqAtHitAction::~SeqAtHitAction() = default;

bool SeqAtHitAction::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void SeqAtHitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void SeqAtHitAction::leave_() {
    SeqTwoAction::leave_();
}

void SeqAtHitAction::loadParams_() {
    SeqTwoAction::loadParams_();
}

}  // namespace uking::ai
