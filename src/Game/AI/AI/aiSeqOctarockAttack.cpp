#include "Game/AI/AI/aiSeqOctarockAttack.h"

namespace uking::ai {

SeqOctarockAttack::SeqOctarockAttack(const InitArg& arg) : SeqThreeAction(arg) {}

SeqOctarockAttack::~SeqOctarockAttack() = default;

bool SeqOctarockAttack::init_(sead::Heap* heap) {
    return SeqThreeAction::init_(heap);
}

void SeqOctarockAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqThreeAction::enter_(params);
}

void SeqOctarockAttack::leave_() {
    SeqThreeAction::leave_();
}

void SeqOctarockAttack::loadParams_() {
    SeqThreeAction::loadParams_();
}

}  // namespace uking::ai
