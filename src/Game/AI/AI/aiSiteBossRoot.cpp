#include "Game/AI/AI/aiSiteBossRoot.h"

namespace uking::ai {

SiteBossRoot::SiteBossRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossRoot::~SiteBossRoot() = default;

bool SiteBossRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossRoot::loadParams_() {
    getStaticParam(&mOffFlagIndexAtClipping_s, "OffFlagIndexAtClipping");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mForceRecoverHitMax_s, "ForceRecoverHitMax");
    getStaticParam(&mForceRecoverDamageMax_s, "ForceRecoverDamageMax");
    getStaticParam(&mAddForceRecoverHitNum_s, "AddForceRecoverHitNum");
    getStaticParam(&mAddForceRecoverDamage_s, "AddForceRecoverDamage");
    getStaticParam(&mBlownOffAtWeakPointHitNum_s, "BlownOffAtWeakPointHitNum");
    getStaticParam(&mDemoPlayHPRate_s, "DemoPlayHPRate");
    getStaticParam(&mWeakPointDamageRate_s, "WeakPointDamageRate");
    getStaticParam(&mIsRemainBoss_s, "IsRemainBoss");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mNormalEntryName_s, "NormalEntryName");
    getStaticParam(&mAtDownEntryName_s, "AtDownEntryName");
    getStaticParam(&mIsPlayed_DemoFlagName_s, "IsPlayed_DemoFlagName");
    getMapUnitParam(&mUniqueNameMessageLabel_m, "UniqueNameMessageLabel");
}

}  // namespace uking::ai
