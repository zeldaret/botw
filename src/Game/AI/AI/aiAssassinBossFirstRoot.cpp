#include "Game/AI/AI/aiAssassinBossFirstRoot.h"

namespace uking::ai {

AssassinBossFirstRoot::AssassinBossFirstRoot(const InitArg& arg) : AssassinBossRootBase(arg) {}

AssassinBossFirstRoot::~AssassinBossFirstRoot() = default;

bool AssassinBossFirstRoot::init_(sead::Heap* heap) {
    return AssassinBossRootBase::init_(heap);
}

void AssassinBossFirstRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinBossRootBase::enter_(params);
}

void AssassinBossFirstRoot::leave_() {
    AssassinBossRootBase::leave_();
}

void AssassinBossFirstRoot::loadParams_() {
    AssassinBossRootBase::loadParams_();
}

}  // namespace uking::ai
