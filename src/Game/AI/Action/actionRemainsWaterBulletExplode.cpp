#include "Game/AI/Action/actionRemainsWaterBulletExplode.h"

namespace uking::action {

RemainsWaterBulletExplode::RemainsWaterBulletExplode(const InitArg& arg) : Explode(arg) {}

RemainsWaterBulletExplode::~RemainsWaterBulletExplode() = default;

bool RemainsWaterBulletExplode::init_(sead::Heap* heap) {
    return Explode::init_(heap);
}

void RemainsWaterBulletExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    Explode::enter_(params);
}

void RemainsWaterBulletExplode::leave_() {
    Explode::leave_();
}

void RemainsWaterBulletExplode::loadParams_() {
    Explode::loadParams_();
    getStaticParam(&mMaxDamage_s, "MaxDamage");
    getStaticParam(&mMinDamage_s, "MinDamage");
}

void RemainsWaterBulletExplode::calc_() {
    Explode::calc_();
}

}  // namespace uking::action
