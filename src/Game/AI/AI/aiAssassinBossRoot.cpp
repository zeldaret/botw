#include "Game/AI/AI/aiAssassinBossRoot.h"

namespace uking::ai {

AssassinBossRoot::AssassinBossRoot(const InitArg& arg) : AssassinBossRootBase(arg) {}

AssassinBossRoot::~AssassinBossRoot() = default;

bool AssassinBossRoot::init_(sead::Heap* heap) {
    return AssassinBossRootBase::init_(heap);
}

void AssassinBossRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinBossRootBase::enter_(params);
}

void AssassinBossRoot::leave_() {
    AssassinBossRootBase::leave_();
}

void AssassinBossRoot::loadParams_() {
    AssassinBossRootBase::loadParams_();
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mBattleAvoidNum_s, "BattleAvoidNum");
}

}  // namespace uking::ai
