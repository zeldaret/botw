#include "Game/AI/AI/aiPriestBossGiantStageRotate.h"

namespace uking::ai {

PriestBossGiantStageRotate::PriestBossGiantStageRotate(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossGiantStageRotate::~PriestBossGiantStageRotate() = default;

bool PriestBossGiantStageRotate::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossGiantStageRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossGiantStageRotate::leave_() {
    PriestBossMode::leave_();
}

void PriestBossGiantStageRotate::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mSendCommand_s, "SendCommand");
    getStaticParam(&mSendOnThrowASEvent_s, "SendOnThrowASEvent");
    getStaticParam(&mIsUseStartAction_s, "IsUseStartAction");
}

}  // namespace uking::ai
