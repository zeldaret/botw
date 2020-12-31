#include "Game/AI/AI/aiIAIAttack.h"

namespace uking::ai {

IAIAttack::IAIAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IAIAttack::~IAIAttack() = default;

bool IAIAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IAIAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void IAIAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void IAIAttack::loadParams_() {
    getStaticParam(&mOffsetLR_s, "OffsetLR");
    getStaticParam(&mCloseDistLR_s, "CloseDistLR");
    getStaticParam(&mClsoeDistFB_s, "ClsoeDistFB");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsAbleSkipNear_s, "IsAbleSkipNear");
    getStaticParam(&mTiredAngle_s, "TiredAngle");
}

}  // namespace uking::ai
