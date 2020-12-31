#include "Game/AI/AI/aiRememberMesOneActorEnemyRoot.h"

namespace uking::ai {

RememberMesOneActorEnemyRoot::RememberMesOneActorEnemyRoot(const InitArg& arg) : EnemyRoot(arg) {}

RememberMesOneActorEnemyRoot::~RememberMesOneActorEnemyRoot() = default;

bool RememberMesOneActorEnemyRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void RememberMesOneActorEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void RememberMesOneActorEnemyRoot::leave_() {
    EnemyRoot::leave_();
}

void RememberMesOneActorEnemyRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mRememberKey_s, "RememberKey");
}

}  // namespace uking::ai
