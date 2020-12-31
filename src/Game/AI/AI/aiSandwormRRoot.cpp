#include "Game/AI/AI/aiSandwormRRoot.h"

namespace uking::ai {

SandwormRRoot::SandwormRRoot(const InitArg& arg) : EnemyRoot(arg) {}

SandwormRRoot::~SandwormRRoot() = default;

bool SandwormRRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void SandwormRRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void SandwormRRoot::leave_() {
    EnemyRoot::leave_();
}

void SandwormRRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mSandOffset_s, "SandOffset");
    getStaticParam(&mWeakPointDamageRate_s, "WeakPointDamageRate");
    getStaticParam(&mWeakChimicalDamageRate_s, "WeakChimicalDamageRate");
}

}  // namespace uking::ai
