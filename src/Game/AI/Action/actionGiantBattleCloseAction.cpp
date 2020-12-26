#include "Game/AI/Action/actionGiantBattleCloseAction.h"

namespace uking::action {

GiantBattleCloseAction::GiantBattleCloseAction(const InitArg& arg) : BattleCloseMoveAction(arg) {}

GiantBattleCloseAction::~GiantBattleCloseAction() = default;

bool GiantBattleCloseAction::init_(sead::Heap* heap) {
    return BattleCloseMoveAction::init_(heap);
}

void GiantBattleCloseAction::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
}

void GiantBattleCloseAction::leave_() {
    BattleCloseMoveAction::leave_();
}

void GiantBattleCloseAction::loadParams_() {
    BattleCloseMoveActionBase::loadParams_();
    getStaticParam(&mVibrationPower_s, "VibrationPower");
}

void GiantBattleCloseAction::calc_() {
    BattleCloseMoveAction::calc_();
}

}  // namespace uking::action
