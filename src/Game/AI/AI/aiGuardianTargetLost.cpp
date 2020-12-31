#include "Game/AI/AI/aiGuardianTargetLost.h"

namespace uking::ai {

GuardianTargetLost::GuardianTargetLost(const InitArg& arg) : GuardianAI(arg) {}

GuardianTargetLost::~GuardianTargetLost() = default;

bool GuardianTargetLost::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianTargetLost::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
}

void GuardianTargetLost::leave_() {
    GuardianAI::leave_();
}

void GuardianTargetLost::loadParams_() {
    GuardianAI::loadParams_();
    getStaticParam(&mLostCountMax_s, "LostCountMax");
    getStaticParam(&mMoveRange_s, "MoveRange");
    getStaticParam(&mBackOffset_s, "BackOffset");
    getStaticParam(&mAirThreshold_s, "AirThreshold");
}

}  // namespace uking::ai
