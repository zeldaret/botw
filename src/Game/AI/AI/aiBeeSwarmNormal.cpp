#include "Game/AI/AI/aiBeeSwarmNormal.h"

namespace uking::ai {

BeeSwarmNormal::BeeSwarmNormal(const InitArg& arg) : EnemyNormal(arg) {}

BeeSwarmNormal::~BeeSwarmNormal() = default;

bool BeeSwarmNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void BeeSwarmNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void BeeSwarmNormal::leave_() {
    EnemyNormal::leave_();
}

void BeeSwarmNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

}  // namespace uking::ai
