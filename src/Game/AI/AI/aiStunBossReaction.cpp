#include "Game/AI/AI/aiStunBossReaction.h"

namespace uking::ai {

StunBossReaction::StunBossReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StunBossReaction::~StunBossReaction() = default;

bool StunBossReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StunBossReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StunBossReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StunBossReaction::loadParams_() {}

}  // namespace uking::ai
