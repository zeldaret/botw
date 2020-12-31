#include "Game/AI/AI/aiSimpleEnemyNormal.h"

namespace uking::ai {

SimpleEnemyNormal::SimpleEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

SimpleEnemyNormal::~SimpleEnemyNormal() = default;

bool SimpleEnemyNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void SimpleEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void SimpleEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void SimpleEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

}  // namespace uking::ai
