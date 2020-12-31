#include "Game/AI/AI/aiEnemyLiftShootItem.h"

namespace uking::ai {

EnemyLiftShootItem::EnemyLiftShootItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyLiftShootItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLiftShootItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyLiftShootItem::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyLiftShootItem::loadParams_() {
    getStaticParam(&mShootAngle_s, "ShootAngle");
    getStaticParam(&mShootDist_s, "ShootDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mShootItem_d, "ShootItem");
}

}  // namespace uking::ai
