#include "Game/AI/AI/aiPriestBossCloneBulletRoot.h"

namespace uking::ai {

PriestBossCloneBulletRoot::PriestBossCloneBulletRoot(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossCloneBulletRoot::~PriestBossCloneBulletRoot() = default;

bool PriestBossCloneBulletRoot::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossCloneBulletRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossCloneBulletRoot::leave_() {
    PriestBossMode::leave_();
}

void PriestBossCloneBulletRoot::loadParams_() {
    PriestBossMode::loadParams_();
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
