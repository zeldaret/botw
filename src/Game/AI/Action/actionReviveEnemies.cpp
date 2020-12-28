#include "Game/AI/Action/actionReviveEnemies.h"

namespace uking::action {

ReviveEnemies::ReviveEnemies(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReviveEnemies::~ReviveEnemies() = default;

bool ReviveEnemies::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReviveEnemies::loadParams_() {}

}  // namespace uking::action
