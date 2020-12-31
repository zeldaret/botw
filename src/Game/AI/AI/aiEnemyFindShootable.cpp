#include "Game/AI/AI/aiEnemyFindShootable.h"

namespace uking::ai {

EnemyFindShootable::EnemyFindShootable(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyFindShootable::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFindShootable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyFindShootable::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyFindShootable::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getStaticParam(&mAttOffset_s, "AttOffset");
    getStaticParam(&mCanGrabHeavy_s, "CanGrabHeavy");
    getStaticParam(&mGrabCheckRadius_s, "GrabCheckRadius");
    getStaticParam(&mChaseItemDist_s, "ChaseItemDist");
    getStaticParam(&mChaseItemSpeed_s, "ChaseItemSpeed");
}

}  // namespace uking::ai
