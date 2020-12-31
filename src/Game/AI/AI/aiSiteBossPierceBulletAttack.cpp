#include "Game/AI/AI/aiSiteBossPierceBulletAttack.h"

namespace uking::ai {

SiteBossPierceBulletAttack::SiteBossPierceBulletAttack(const InitArg& arg)
    : SiteBossShootNormalArrowRoot(arg) {}

SiteBossPierceBulletAttack::~SiteBossPierceBulletAttack() = default;

bool SiteBossPierceBulletAttack::init_(sead::Heap* heap) {
    return SiteBossShootNormalArrowRoot::init_(heap);
}

void SiteBossPierceBulletAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossShootNormalArrowRoot::enter_(params);
}

void SiteBossPierceBulletAttack::leave_() {
    SiteBossShootNormalArrowRoot::leave_();
}

}  // namespace uking::ai
