#include "Game/AI/AI/aiPriestBossIAIAttack.h"

namespace uking::ai {

PriestBossIAIAttack::PriestBossIAIAttack(const InitArg& arg) : IAIAttack(arg) {}

PriestBossIAIAttack::~PriestBossIAIAttack() = default;

bool PriestBossIAIAttack::init_(sead::Heap* heap) {
    return IAIAttack::init_(heap);
}

void PriestBossIAIAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    IAIAttack::enter_(params);
}

void PriestBossIAIAttack::leave_() {
    IAIAttack::leave_();
}

void PriestBossIAIAttack::loadParams_() {
    IAIAttack::loadParams_();
}

}  // namespace uking::ai
