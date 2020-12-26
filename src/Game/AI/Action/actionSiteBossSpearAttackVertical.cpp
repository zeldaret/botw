#include "Game/AI/Action/actionSiteBossSpearAttackVertical.h"

namespace uking::action {

SiteBossSpearAttackVertical::SiteBossSpearAttackVertical(const InitArg& arg)
    : SiteBossSpearAttackBase(arg) {}

SiteBossSpearAttackVertical::~SiteBossSpearAttackVertical() = default;

bool SiteBossSpearAttackVertical::init_(sead::Heap* heap) {
    return SiteBossSpearAttackBase::init_(heap);
}

void SiteBossSpearAttackVertical::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossSpearAttackBase::enter_(params);
}

void SiteBossSpearAttackVertical::leave_() {
    SiteBossSpearAttackBase::leave_();
}

void SiteBossSpearAttackVertical::loadParams_() {
    SiteBossSpearAttackBase::loadParams_();
    getStaticParam(&mShockWaveAttackPower_s, "ShockWaveAttackPower");
}

void SiteBossSpearAttackVertical::calc_() {
    SiteBossSpearAttackBase::calc_();
}

}  // namespace uking::action
