#include "Game/Actor/AI/aiPriestBossGiantStageRotate.h"

namespace uking::ai {

PriestBossGiantStageRotate::PriestBossGiantStageRotate(const InitArg& arg) : PriestBoss(arg) {}

PriestBossGiantStageRotate::~PriestBossGiantStageRotate() = default;

bool PriestBossGiantStageRotate::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossGiantStageRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossGiantStageRotate::leave_() {
    PriestBoss::leave_();
}

void PriestBossGiantStageRotate::loadParams_() {
    PriestBoss::loadParams_();
    getStaticParam(&mSendCommand_s, "SendCommand");
    getStaticParam(&mSendOnThrowASEvent_s, "SendOnThrowASEvent");
    getStaticParam(&mIsUseStartAction_s, "IsUseStartAction");
}

}  // namespace uking::ai
