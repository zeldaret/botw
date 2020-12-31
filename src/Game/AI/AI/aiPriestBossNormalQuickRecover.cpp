#include "Game/AI/AI/aiPriestBossNormalQuickRecover.h"

namespace uking::ai {

PriestBossNormalQuickRecover::PriestBossNormalQuickRecover(const InitArg& arg)
    : PriestBossMode(arg) {}

PriestBossNormalQuickRecover::~PriestBossNormalQuickRecover() = default;

bool PriestBossNormalQuickRecover::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossNormalQuickRecover::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossNormalQuickRecover::leave_() {
    PriestBossMode::leave_();
}

void PriestBossNormalQuickRecover::loadParams_() {
    PriestBossMode::loadParams_();
    getDynamicParam(&mIsFromRagdoll_d, "IsFromRagdoll");
}

}  // namespace uking::ai
