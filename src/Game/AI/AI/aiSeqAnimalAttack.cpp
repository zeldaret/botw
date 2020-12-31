#include "Game/AI/AI/aiSeqAnimalAttack.h"

namespace uking::ai {

SeqAnimalAttack::SeqAnimalAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqAnimalAttack::~SeqAnimalAttack() = default;

bool SeqAnimalAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqAnimalAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqAnimalAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqAnimalAttack::loadParams_() {
    getStaticParam(&mIsUseAfterAttackState_s, "IsUseAfterAttackState");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
