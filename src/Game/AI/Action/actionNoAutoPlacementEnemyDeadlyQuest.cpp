#include "Game/AI/Action/actionNoAutoPlacementEnemyDeadlyQuest.h"

namespace uking::action {

NoAutoPlacementEnemyDeadlyQuest::NoAutoPlacementEnemyDeadlyQuest(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NoAutoPlacementEnemyDeadlyQuest::~NoAutoPlacementEnemyDeadlyQuest() = default;

bool NoAutoPlacementEnemyDeadlyQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NoAutoPlacementEnemyDeadlyQuest::loadParams_() {}

}  // namespace uking::action
