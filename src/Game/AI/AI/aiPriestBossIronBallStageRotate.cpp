#include "Game/AI/AI/aiPriestBossIronBallStageRotate.h"

namespace uking::ai {

PriestBossIronBallStageRotate::PriestBossIronBallStageRotate(const InitArg& arg)
    : PriestBossIronBall(arg) {}

PriestBossIronBallStageRotate::~PriestBossIronBallStageRotate() = default;

bool PriestBossIronBallStageRotate::init_(sead::Heap* heap) {
    return PriestBossIronBall::init_(heap);
}

void PriestBossIronBallStageRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossIronBall::enter_(params);
}

void PriestBossIronBallStageRotate::leave_() {
    PriestBossIronBall::leave_();
}

void PriestBossIronBallStageRotate::loadParams_() {
    PriestBossIronBall::loadParams_();
    getStaticParam(&mIronBallSummonRadius_s, "IronBallSummonRadius");
    getStaticParam(&mIronBallSummonArchAngle_s, "IronBallSummonArchAngle");
    getStaticParam(&mIronBallSummonOffsetY_s, "IronBallSummonOffsetY");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
