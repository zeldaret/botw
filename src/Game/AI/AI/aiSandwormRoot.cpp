#include "Game/AI/AI/aiSandwormRoot.h"

namespace uking::ai {

SandwormRoot::SandwormRoot(const InitArg& arg) : EnemyRoot(arg) {}

SandwormRoot::~SandwormRoot() = default;

bool SandwormRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void SandwormRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void SandwormRoot::leave_() {
    EnemyRoot::leave_();
}

void SandwormRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mSandOffset_s, "SandOffset");
    getStaticParam(&mWeakPointDamageRate_s, "WeakPointDamageRate");
}

}  // namespace uking::ai
