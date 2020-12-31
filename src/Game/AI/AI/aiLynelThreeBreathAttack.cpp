#include "Game/AI/AI/aiLynelThreeBreathAttack.h"

namespace uking::ai {

LynelThreeBreathAttack::LynelThreeBreathAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelThreeBreathAttack::~LynelThreeBreathAttack() = default;

bool LynelThreeBreathAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelThreeBreathAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelThreeBreathAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelThreeBreathAttack::loadParams_() {
    getStaticParam(&mNearRange_s, "NearRange");
    getStaticParam(&mFarRange_s, "FarRange");
    getStaticParam(&mIsCheckXZ_s, "IsCheckXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
