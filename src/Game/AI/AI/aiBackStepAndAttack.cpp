#include "Game/AI/AI/aiBackStepAndAttack.h"

namespace uking::ai {

BackStepAndAttack::BackStepAndAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BackStepAndAttack::~BackStepAndAttack() = default;

bool BackStepAndAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BackStepAndAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BackStepAndAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BackStepAndAttack::loadParams_() {
    getStaticParam(&mBackStepMax_s, "BackStepMax");
    getStaticParam(&mTurnRepeatMax_s, "TurnRepeatMax");
    getStaticParam(&mBackStepMinDist_s, "BackStepMinDist");
    getStaticParam(&mBackStepDist_s, "BackStepDist");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mNoBackStepRange_s, "NoBackStepRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
