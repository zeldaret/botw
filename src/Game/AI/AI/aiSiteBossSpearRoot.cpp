#include "Game/AI/AI/aiSiteBossSpearRoot.h"

namespace uking::ai {

SiteBossSpearRoot::SiteBossSpearRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossSpearRoot::~SiteBossSpearRoot() = default;

bool SiteBossSpearRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
}

void SiteBossSpearRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
}

void SiteBossSpearRoot::leave_() {
    SiteBossRoot::leave_();
}

void SiteBossSpearRoot::loadParams_() {
    SiteBossRoot::loadParams_();
    getStaticParam(&mThrowSpearAttackPower_s, "ThrowSpearAttackPower");
    getStaticParam(&mThrowSpearMinDmage_s, "ThrowSpearMinDmage");
    getStaticParam(&mIceSplinterAttackPower_s, "IceSplinterAttackPower");
    getStaticParam(&mIceSplinterMinDamage_s, "IceSplinterMinDamage");
}

}  // namespace uking::ai
