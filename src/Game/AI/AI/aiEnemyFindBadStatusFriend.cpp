#include "Game/AI/AI/aiEnemyFindBadStatusFriend.h"

namespace uking::ai {

EnemyFindBadStatusFriend::EnemyFindBadStatusFriend(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyFindBadStatusFriend::~EnemyFindBadStatusFriend() = default;

bool EnemyFindBadStatusFriend::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFindBadStatusFriend::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyFindBadStatusFriend::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyFindBadStatusFriend::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
