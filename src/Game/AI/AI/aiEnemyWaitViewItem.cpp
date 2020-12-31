#include "Game/AI/AI/aiEnemyWaitViewItem.h"

namespace uking::ai {

EnemyWaitViewItem::EnemyWaitViewItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyWaitViewItem::~EnemyWaitViewItem() = default;

bool EnemyWaitViewItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyWaitViewItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyWaitViewItem::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyWaitViewItem::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
