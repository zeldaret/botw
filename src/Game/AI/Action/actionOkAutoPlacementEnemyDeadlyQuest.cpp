#include "Game/AI/Action/actionOkAutoPlacementEnemyDeadlyQuest.h"

namespace uking::action {

OkAutoPlacementEnemyDeadlyQuest::OkAutoPlacementEnemyDeadlyQuest(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OkAutoPlacementEnemyDeadlyQuest::~OkAutoPlacementEnemyDeadlyQuest() = default;

bool OkAutoPlacementEnemyDeadlyQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OkAutoPlacementEnemyDeadlyQuest::loadParams_() {}

}  // namespace uking::action
