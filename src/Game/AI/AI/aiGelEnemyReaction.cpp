#include "Game/AI/AI/aiGelEnemyReaction.h"

namespace uking::ai {

GelEnemyReaction::GelEnemyReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

GelEnemyReaction::~GelEnemyReaction() = default;

bool GelEnemyReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void GelEnemyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void GelEnemyReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void GelEnemyReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
}

}  // namespace uking::ai
