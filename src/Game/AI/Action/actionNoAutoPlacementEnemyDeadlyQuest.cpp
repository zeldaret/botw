#include "Game/AI/Action/actionNoAutoPlacementEnemyDeadlyQuest.h"

namespace uking::action {

NoAutoPlacementEnemyDeadlyQuest::NoAutoPlacementEnemyDeadlyQuest(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NoAutoPlacementEnemyDeadlyQuest::~NoAutoPlacementEnemyDeadlyQuest() = default;

bool NoAutoPlacementEnemyDeadlyQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NoAutoPlacementEnemyDeadlyQuest::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NoAutoPlacementEnemyDeadlyQuest::leave_() {
    ksys::act::ai::Action::leave_();
}

void NoAutoPlacementEnemyDeadlyQuest::loadParams_() {}

void NoAutoPlacementEnemyDeadlyQuest::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
