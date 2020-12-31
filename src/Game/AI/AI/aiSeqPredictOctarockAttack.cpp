#include "Game/AI/AI/aiSeqPredictOctarockAttack.h"

namespace uking::ai {

SeqPredictOctarockAttack::SeqPredictOctarockAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqPredictOctarockAttack::~SeqPredictOctarockAttack() = default;

bool SeqPredictOctarockAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqPredictOctarockAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqPredictOctarockAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqPredictOctarockAttack::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai
