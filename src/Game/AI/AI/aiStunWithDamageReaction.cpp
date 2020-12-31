#include "Game/AI/AI/aiStunWithDamageReaction.h"

namespace uking::ai {

StunWithDamageReaction::StunWithDamageReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StunWithDamageReaction::~StunWithDamageReaction() = default;

bool StunWithDamageReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StunWithDamageReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StunWithDamageReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StunWithDamageReaction::loadParams_() {
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mForceEndLifeRatio_s, "ForceEndLifeRatio");
}

}  // namespace uking::ai
