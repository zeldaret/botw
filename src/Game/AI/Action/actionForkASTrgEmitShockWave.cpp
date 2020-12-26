#include "Game/AI/Action/actionForkASTrgEmitShockWave.h"

namespace uking::action {

ForkASTrgEmitShockWave::ForkASTrgEmitShockWave(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgEmitShockWave::~ForkASTrgEmitShockWave() = default;

bool ForkASTrgEmitShockWave::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgEmitShockWave::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgEmitShockWave::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgEmitShockWave::loadParams_() {
    getStaticParam(&mPower_s, "Power");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mEmitIntervalTime_s, "EmitIntervalTime");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mMaxScale_s, "MaxScale");
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
    getStaticParam(&mIsIniviciblePierce_s, "IsIniviciblePierce");
    getStaticParam(&mIsHeavy_s, "IsHeavy");
    getStaticParam(&mShockWaveActorName_s, "ShockWaveActorName");
    getStaticParam(&mShockWavePartsKey_s, "ShockWavePartsKey");
}

void ForkASTrgEmitShockWave::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
