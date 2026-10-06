#include "Game/Actor/Action/actionForkEmitShockWave.h"

namespace uking::action {

ForkEmitShockWave::ForkEmitShockWave(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkEmitShockWave::~ForkEmitShockWave() = default;

bool ForkEmitShockWave::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkEmitShockWave::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkEmitShockWave::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkEmitShockWave::loadParams_() {
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

void ForkEmitShockWave::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
