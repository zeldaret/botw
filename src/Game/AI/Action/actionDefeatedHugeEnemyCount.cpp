#include "Game/AI/Action/actionDefeatedHugeEnemyCount.h"

namespace uking::action {

DefeatedHugeEnemyCount::DefeatedHugeEnemyCount(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DefeatedHugeEnemyCount::~DefeatedHugeEnemyCount() = default;

bool DefeatedHugeEnemyCount::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DefeatedHugeEnemyCount::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DefeatedHugeEnemyCount::leave_() {
    ksys::act::ai::Action::leave_();
}

void DefeatedHugeEnemyCount::loadParams_() {
    getDynamicParam(&mEnemyType_d, "EnemyType");
}

void DefeatedHugeEnemyCount::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
