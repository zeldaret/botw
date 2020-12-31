#include "Game/AI/AI/aiSeqOctarockWigReaction.h"

namespace uking::ai {

SeqOctarockWigReaction::SeqOctarockWigReaction(const InitArg& arg) : SeqThreeAction(arg) {}

SeqOctarockWigReaction::~SeqOctarockWigReaction() = default;

bool SeqOctarockWigReaction::init_(sead::Heap* heap) {
    return SeqThreeAction::init_(heap);
}

void SeqOctarockWigReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqThreeAction::enter_(params);
}

void SeqOctarockWigReaction::leave_() {
    SeqThreeAction::leave_();
}

void SeqOctarockWigReaction::loadParams_() {
    SeqThreeAction::loadParams_();
}

}  // namespace uking::ai
