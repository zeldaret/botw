#include "Game/Actor/AI/aiPriestBossNormalQuickRecover.h"

namespace uking::ai {

PriestBossNormalQuickRecover::PriestBossNormalQuickRecover(const InitArg& arg) : PriestBoss(arg) {}

PriestBossNormalQuickRecover::~PriestBossNormalQuickRecover() = default;

bool PriestBossNormalQuickRecover::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossNormalQuickRecover::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossNormalQuickRecover::leave_() {
    PriestBoss::leave_();
}

void PriestBossNormalQuickRecover::loadParams_() {
    PriestBoss::loadParams_();
    getDynamicParam(&mIsFromRagdoll_d, "IsFromRagdoll");
}

}  // namespace uking::ai
