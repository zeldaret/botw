#include "Game/AI/AI/aiLynelRoot.h"

namespace uking::ai {

LynelRoot::LynelRoot(const InitArg& arg) : EnemyRoot(arg) {}

LynelRoot::~LynelRoot() = default;

bool LynelRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void LynelRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void LynelRoot::leave_() {
    EnemyRoot::leave_();
}

void LynelRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mBowIdx_s, "BowIdx");
    getStaticParam(&mBoneStandAddRatio_s, "BoneStandAddRatio");
    getStaticParam(&mRoarFlameActorName_s, "RoarFlameActorName");
    getStaticParam(&mRoarFlamePartsKey_s, "RoarFlamePartsKey");
    getStaticParam(&mBreathActorName_s, "BreathActorName");
    getStaticParam(&mBreathPartsKey0_s, "BreathPartsKey0");
    getStaticParam(&mBreathPartsKey1_s, "BreathPartsKey1");
    getStaticParam(&mBreathPartsKey2_s, "BreathPartsKey2");
    getStaticParam(&mStandBoneName_s, "StandBoneName");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
    getAITreeVariable(&mLynelAreaAlarmPoint_a, "LynelAreaAlarmPoint");
    getAITreeVariable(&mLynelBodyControlUnit_a, "LynelBodyControlUnit");
    getAITreeVariable(&mLynelMoveParam_a, "LynelMoveParam");
    // FIXME: CALL sub_710070F83C @ 0x710070f83c
}

}  // namespace uking::ai
