#include "Game/Actor/AI/aiVacuumEnemyRoot.h"

namespace uking::ai {

VacuumEnemyRoot::VacuumEnemyRoot(const InitArg& arg) : EnemyRoot(arg) {}

VacuumEnemyRoot::~VacuumEnemyRoot() = default;

bool VacuumEnemyRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void VacuumEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void VacuumEnemyRoot::leave_() {
    EnemyRoot::leave_();
}

void VacuumEnemyRoot::loadParams_() {
    EnemyRoot::loadParams_();
}

}  // namespace uking::ai
