#include "Game/AI/AI/aiStalEnemyReaction.h"

namespace uking::ai {

StalEnemyReaction::StalEnemyReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

StalEnemyReaction::~StalEnemyReaction() = default;

bool StalEnemyReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void StalEnemyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void StalEnemyReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void StalEnemyReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
}

}  // namespace uking::ai
