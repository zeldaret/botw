#include "Game/AI/AI/aiMiniGolemReaction.h"

namespace uking::ai {

MiniGolemReaction::MiniGolemReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

MiniGolemReaction::~MiniGolemReaction() = default;

bool MiniGolemReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void MiniGolemReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void MiniGolemReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void MiniGolemReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai
