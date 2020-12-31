#include "Game/AI/AI/aiStalGiantEnemyReaction.h"

namespace uking::ai {

StalGiantEnemyReaction::StalGiantEnemyReaction(const InitArg& arg) : ForestGiantReaction(arg) {}

StalGiantEnemyReaction::~StalGiantEnemyReaction() = default;

bool StalGiantEnemyReaction::init_(sead::Heap* heap) {
    return ForestGiantReaction::init_(heap);
}

void StalGiantEnemyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ForestGiantReaction::enter_(params);
}

void StalGiantEnemyReaction::leave_() {
    ForestGiantReaction::leave_();
}

void StalGiantEnemyReaction::loadParams_() {
    ForestGiantReaction::loadParams_();
}

}  // namespace uking::ai
