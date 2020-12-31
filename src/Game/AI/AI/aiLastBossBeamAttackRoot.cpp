#include "Game/AI/AI/aiLastBossBeamAttackRoot.h"

namespace uking::ai {

LastBossBeamAttackRoot::LastBossBeamAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossBeamAttackRoot::~LastBossBeamAttackRoot() = default;

bool LastBossBeamAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossBeamAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossBeamAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossBeamAttackRoot::loadParams_() {
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mAccel_s, "Accel");
    getStaticParam(&mKeepDistanceRand_s, "KeepDistanceRand");
    getStaticParam(&mRandKeepFrame_s, "RandKeepFrame");
    getStaticParam(&mBrakeStartFrame_s, "BrakeStartFrame");
    getStaticParam(&mMoveYSpeed_s, "MoveYSpeed");
    getStaticParam(&mIsMove_s, "IsMove");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsCreateGuardEffect_s, "IsCreateGuardEffect");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
}

}  // namespace uking::ai
