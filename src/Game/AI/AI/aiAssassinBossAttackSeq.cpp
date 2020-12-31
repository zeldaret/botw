#include "Game/AI/AI/aiAssassinBossAttackSeq.h"

namespace uking::ai {

AssassinBossAttackSeq::AssassinBossAttackSeq(const InitArg& arg) : SeqTwoAction(arg) {}

AssassinBossAttackSeq::~AssassinBossAttackSeq() = default;

bool AssassinBossAttackSeq::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void AssassinBossAttackSeq::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void AssassinBossAttackSeq::leave_() {
    SeqTwoAction::leave_();
}

void AssassinBossAttackSeq::loadParams_() {
    SeqTwoAction::loadParams_();
}

}  // namespace uking::ai
