#include "Game/AI/AI/aiForestGiantReaction.h"

namespace uking::ai {

ForestGiantReaction::ForestGiantReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

ForestGiantReaction::~ForestGiantReaction() = default;

bool ForestGiantReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void ForestGiantReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void ForestGiantReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void ForestGiantReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mRightLegArmorSlot_s, "RightLegArmorSlot");
    getStaticParam(&mLeftLegArmorSlot_s, "LeftLegArmorSlot");
    getStaticParam(&mTgLegL_s, "TgLegL");
    getStaticParam(&mBgLegL_s, "BgLegL");
    getStaticParam(&mTgLegR_s, "TgLegR");
    getStaticParam(&mBgLegR_s, "BgLegR");
    getStaticParam(&mTgArmR_s, "TgArmR");
}

}  // namespace uking::ai
