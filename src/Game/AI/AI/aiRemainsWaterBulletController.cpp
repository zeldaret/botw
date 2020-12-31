#include "Game/AI/AI/aiRemainsWaterBulletController.h"

namespace uking::ai {

RemainsWaterBulletController::RemainsWaterBulletController(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RemainsWaterBulletController::~RemainsWaterBulletController() = default;

bool RemainsWaterBulletController::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterBulletController::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsWaterBulletController::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWaterBulletController::loadParams_() {
    getStaticParam(&mInsideAreaRadius_s, "InsideAreaRadius");
    getStaticParam(&mFirstBulletTimer_s, "FirstBulletTimer");
    getStaticParam(&mSecondBulletTimer_s, "SecondBulletTimer");
    getStaticParam(&mNextBulletTimerSuccess_s, "NextBulletTimerSuccess");
    getStaticParam(&mNextBulletTimerFail_s, "NextBulletTimerFail");
    getStaticParam(&mChaseBulletNum_s, "ChaseBulletNum");
    getStaticParam(&mExplodeBulletNum_s, "ExplodeBulletNum");
    getStaticParam(&mChaseBulletActorName_s, "ChaseBulletActorName");
    getStaticParam(&mExplodeBulletActorName_s, "ExplodeBulletActorName");
    getStaticParam(&mInsideAreaCenter_s, "InsideAreaCenter");
    getStaticParam(&mInsideAreaWidth_s, "InsideAreaWidth");
    getAITreeVariable(&mRemainsWaterBattleInfo_a, "RemainsWaterBattleInfo");
}

}  // namespace uking::ai
