#include "Game/AI/Action/actionOkAutoPlacementEnemyDeadlyQuest.h"

namespace uking::action {

OkAutoPlacementEnemyDeadlyQuest::OkAutoPlacementEnemyDeadlyQuest(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OkAutoPlacementEnemyDeadlyQuest::~OkAutoPlacementEnemyDeadlyQuest() = default;

bool OkAutoPlacementEnemyDeadlyQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OkAutoPlacementEnemyDeadlyQuest::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OkAutoPlacementEnemyDeadlyQuest::leave_() {
    ksys::act::ai::Action::leave_();
}

void OkAutoPlacementEnemyDeadlyQuest::loadParams_() {}

void OkAutoPlacementEnemyDeadlyQuest::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
