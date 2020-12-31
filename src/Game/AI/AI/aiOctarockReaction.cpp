#include "Game/AI/AI/aiOctarockReaction.h"

namespace uking::ai {

OctarockReaction::OctarockReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

OctarockReaction::~OctarockReaction() = default;

bool OctarockReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void OctarockReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void OctarockReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void OctarockReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mIsWigBreackByGust_s, "IsWigBreackByGust");
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

}  // namespace uking::ai
