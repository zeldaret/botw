#include "Game/AI/AI/aiGanonReaction.h"

namespace uking::ai {

GanonReaction::GanonReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

GanonReaction::~GanonReaction() = default;

bool GanonReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void GanonReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void GanonReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void GanonReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
}

}  // namespace uking::ai
