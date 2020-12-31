#include "Game/AI/AI/aiSandwormReaction.h"

namespace uking::ai {

SandwormReaction::SandwormReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

SandwormReaction::~SandwormReaction() = default;

bool SandwormReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void SandwormReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void SandwormReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void SandwormReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
}

}  // namespace uking::ai
