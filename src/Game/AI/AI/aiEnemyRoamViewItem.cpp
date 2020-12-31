#include "Game/AI/AI/aiEnemyRoamViewItem.h"

namespace uking::ai {

EnemyRoamViewItem::EnemyRoamViewItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRoamViewItem::~EnemyRoamViewItem() = default;

bool EnemyRoamViewItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRoamViewItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyRoamViewItem::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRoamViewItem::loadParams_() {
    getDynamicParam(&mIsChanged_d, "IsChanged");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
