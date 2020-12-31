#include "Game/AI/AI/aiEnemyFortressWait.h"

namespace uking::ai {

EnemyFortressWait::EnemyFortressWait(const InitArg& arg) : EnemyWaitViewItem(arg) {}

EnemyFortressWait::~EnemyFortressWait() = default;

bool EnemyFortressWait::init_(sead::Heap* heap) {
    return EnemyWaitViewItem::init_(heap);
}

void EnemyFortressWait::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyWaitViewItem::enter_(params);
}

void EnemyFortressWait::leave_() {
    EnemyWaitViewItem::leave_();
}

void EnemyFortressWait::loadParams_() {
    EnemyWaitViewItem::loadParams_();
    // FIXME: CALL sub @ 0x7100392230
    getStaticParam(&mEatPer_s, "EatPer");
    getStaticParam(&mEatItem_s, "EatItem");
    getMapUnitParam(&mFortressEatPer_m, "FortressEatPer");
    getMapUnitParam(&mFortressEatItem_m, "FortressEatItem");
}

}  // namespace uking::ai
