#include "Game/AI/AI/aiSiteBossReaction.h"

namespace uking::ai {

SiteBossReaction::SiteBossReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

SiteBossReaction::~SiteBossReaction() = default;

bool SiteBossReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void SiteBossReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void SiteBossReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void SiteBossReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mIsChangeEffectiveDamage_s, "IsChangeEffectiveDamage");
}

}  // namespace uking::ai
