#include "Game/Actor/AI/aiPriestBossCloneBulletRoot.h"

namespace uking::ai {

PriestBossCloneBulletRoot::PriestBossCloneBulletRoot(const InitArg& arg) : PriestBoss(arg) {}

PriestBossCloneBulletRoot::~PriestBossCloneBulletRoot() = default;

bool PriestBossCloneBulletRoot::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossCloneBulletRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossCloneBulletRoot::leave_() {
    PriestBoss::leave_();
}

void PriestBossCloneBulletRoot::loadParams_() {
    PriestBoss::loadParams_();
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
