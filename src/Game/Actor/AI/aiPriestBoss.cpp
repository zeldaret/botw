#include "Game/Actor/AI/aiPriestBoss.h"

namespace uking::ai {

PriestBoss::PriestBoss(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBoss::~PriestBoss() = default;

bool PriestBoss::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBoss::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBoss::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBoss::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
