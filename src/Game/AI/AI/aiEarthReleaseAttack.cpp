#include "Game/AI/AI/aiEarthReleaseAttack.h"

namespace uking::ai {

EarthReleaseAttack::EarthReleaseAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EarthReleaseAttack::~EarthReleaseAttack() = default;

bool EarthReleaseAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EarthReleaseAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EarthReleaseAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EarthReleaseAttack::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mRange_s, "Range");
    getStaticParam(&mScale_s, "Scale");
    getStaticParam(&mUseAfterAction_s, "UseAfterAction");
    getStaticParam(&mEarthReleaseActorName_s, "EarthReleaseActorName");
    getStaticParam(&mEarthReleasePartsName_s, "EarthReleasePartsName");
}

}  // namespace uking::ai
