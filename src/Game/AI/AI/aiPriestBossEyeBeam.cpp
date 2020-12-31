#include "Game/AI/AI/aiPriestBossEyeBeam.h"

namespace uking::ai {

PriestBossEyeBeam::PriestBossEyeBeam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossEyeBeam::~PriestBossEyeBeam() = default;

bool PriestBossEyeBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossEyeBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossEyeBeam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossEyeBeam::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mShotReviseAngleXU_s, "ShotReviseAngleXU");
    getStaticParam(&mShotReviseAngleXD_s, "ShotReviseAngleXD");
    getStaticParam(&mShotReviseAngleY_s, "ShotReviseAngleY");
    getStaticParam(&mIsCreateGuardEffect_s, "IsCreateGuardEffect");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
    getStaticParam(&mShotOffset_s, "ShotOffset");
}

}  // namespace uking::ai
