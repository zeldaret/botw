#include "Game/AI/Action/actionBattleDungeonBGMAction.h"

namespace uking::action {

BattleDungeonBGMAction::BattleDungeonBGMAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BattleDungeonBGMAction::~BattleDungeonBGMAction() = default;

bool BattleDungeonBGMAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BattleDungeonBGMAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BattleDungeonBGMAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void BattleDungeonBGMAction::loadParams_() {}

void BattleDungeonBGMAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
