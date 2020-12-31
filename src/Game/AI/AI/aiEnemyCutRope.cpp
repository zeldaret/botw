#include "Game/AI/AI/aiEnemyCutRope.h"

namespace uking::ai {

EnemyCutRope::EnemyCutRope(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyCutRope::~EnemyCutRope() = default;

bool EnemyCutRope::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyCutRope::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyCutRope::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyCutRope::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCutDist_s, "CutDist");
    getStaticParam(&mCutAngle_s, "CutAngle");
    getStaticParam(&mCutFlyAttack_s, "CutFlyAttack");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    // FIXME: CALL sub_71002A5BB0 @ 0x71002a5bb0
}

}  // namespace uking::ai
