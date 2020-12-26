#include "Game/AI/Action/actionRemainsWaterBulletShooter.h"

namespace uking::action {

RemainsWaterBulletShooter::RemainsWaterBulletShooter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsWaterBulletShooter::~RemainsWaterBulletShooter() = default;

bool RemainsWaterBulletShooter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsWaterBulletShooter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsWaterBulletShooter::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsWaterBulletShooter::loadParams_() {
    getStaticParam(&mBulletType_s, "BulletType");
    getStaticParam(&mReloadCounter_s, "ReloadCounter");
    getStaticParam(&mOffsetAngle_s, "OffsetAngle");
    getStaticParam(&mUseRandRot_s, "UseRandRot");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mBaseShootParam_s, "BaseShootParam");
    getStaticParam(&mOffsetYParam_s, "OffsetYParam");
    getAITreeVariable(&mRemainsWaterBattleInfo_a, "RemainsWaterBattleInfo");
}

void RemainsWaterBulletShooter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
