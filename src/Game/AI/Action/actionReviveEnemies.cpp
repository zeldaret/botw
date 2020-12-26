#include "Game/AI/Action/actionReviveEnemies.h"

namespace uking::action {

ReviveEnemies::ReviveEnemies(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReviveEnemies::~ReviveEnemies() = default;

bool ReviveEnemies::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReviveEnemies::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ReviveEnemies::leave_() {
    ksys::act::ai::Action::leave_();
}

void ReviveEnemies::loadParams_() {}

void ReviveEnemies::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
