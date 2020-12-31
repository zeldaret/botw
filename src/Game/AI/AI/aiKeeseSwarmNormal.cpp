#include "Game/AI/AI/aiKeeseSwarmNormal.h"

namespace uking::ai {

KeeseSwarmNormal::KeeseSwarmNormal(const InitArg& arg) : EnemyNormal(arg) {}

KeeseSwarmNormal::~KeeseSwarmNormal() = default;

bool KeeseSwarmNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void KeeseSwarmNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void KeeseSwarmNormal::leave_() {
    EnemyNormal::leave_();
}

void KeeseSwarmNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

}  // namespace uking::ai
