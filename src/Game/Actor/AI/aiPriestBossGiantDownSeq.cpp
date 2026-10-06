#include "Game/Actor/AI/aiPriestBossGiantDownSeq.h"

namespace uking::ai {

PriestBossGiantDownSeq::PriestBossGiantDownSeq(const InitArg& arg) : PriestBoss(arg) {}

PriestBossGiantDownSeq::~PriestBossGiantDownSeq() = default;

bool PriestBossGiantDownSeq::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossGiantDownSeq::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossGiantDownSeq::leave_() {
    PriestBoss::leave_();
}

void PriestBossGiantDownSeq::loadParams_() {
    PriestBoss::loadParams_();
    getStaticParam(&mRecoverIfAlreadyDown_s, "RecoverIfAlreadyDown");
    getStaticParam(&mIsUseRecover_s, "IsUseRecover");
    getStaticParam(&mHitGroundASName_s, "HitGroundASName");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
}

}  // namespace uking::ai
