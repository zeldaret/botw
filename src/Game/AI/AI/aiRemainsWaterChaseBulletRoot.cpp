#include "Game/AI/AI/aiRemainsWaterChaseBulletRoot.h"

namespace uking::ai {

RemainsWaterChaseBulletRoot::RemainsWaterChaseBulletRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RemainsWaterChaseBulletRoot::~RemainsWaterChaseBulletRoot() = default;

bool RemainsWaterChaseBulletRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterChaseBulletRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsWaterChaseBulletRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWaterChaseBulletRoot::loadParams_() {
    getStaticParam(&mAtkMinDamage_s, "AtkMinDamage");
    getStaticParam(&mCheckPower_s, "CheckPower");
    getStaticParam(&mHighDamageAddSpd_s, "HighDamageAddSpd");
    getStaticParam(&mLowDamageAddSpd_s, "LowDamageAddSpd");
    getStaticParam(&mShootAddSpd_s, "ShootAddSpd");
    getStaticParam(&mResetASName_s, "ResetASName");
}

}  // namespace uking::ai
