#include "Game/AI/AI/aiPriestBossIronBall.h"

namespace uking::ai {

PriestBossIronBall::PriestBossIronBall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossIronBall::~PriestBossIronBall() = default;

bool PriestBossIronBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossIronBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossIronBall::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossIronBall::loadParams_() {
    getStaticParam(&mIronBallWaitThunderTime_s, "IronBallWaitThunderTime");
    getStaticParam(&mChangeEndAnime_s, "ChangeEndAnime");
    getStaticParam(&mIronBallOffsetY_s, "IronBallOffsetY");
    getStaticParam(&mIronBallRadius_s, "IronBallRadius");
    getStaticParam(&mIronBallAngle_s, "IronBallAngle");
    getStaticParam(&mIronSummonLeftBoneName_s, "IronSummonLeftBoneName");
    getStaticParam(&mIronSummonRightBoneName_s, "IronSummonRightBoneName");
    getStaticParam(&mIronBallAngleOffset_s, "IronBallAngleOffset");
    getStaticParam(&mIsAfterAttack_s, "IsAfterAttack");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
