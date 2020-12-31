#include "Game/AI/AI/aiLynelNoticeAttacked.h"

namespace uking::ai {

LynelNoticeAttacked::LynelNoticeAttacked(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelNoticeAttacked::~LynelNoticeAttacked() = default;

bool LynelNoticeAttacked::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelNoticeAttacked::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelNoticeAttacked::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelNoticeAttacked::loadParams_() {
    getStaticParam(&mRepeatMax_s, "RepeatMax");
    getStaticParam(&mRepeatResetTime_s, "RepeatResetTime");
    getStaticParam(&mForceReturnDistFromHomePos_s, "ForceReturnDistFromHomePos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mLynelNoticeAttackRepeatNum_a, "LynelNoticeAttackRepeatNum");
}

}  // namespace uking::ai
