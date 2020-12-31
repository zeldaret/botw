#include "Game/AI/AI/aiLinkageEnemyNormal.h"

namespace uking::ai {

LinkageEnemyNormal::LinkageEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

LinkageEnemyNormal::~LinkageEnemyNormal() = default;

bool LinkageEnemyNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void LinkageEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void LinkageEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void LinkageEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

}  // namespace uking::ai
