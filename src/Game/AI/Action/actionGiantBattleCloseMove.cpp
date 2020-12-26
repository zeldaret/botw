#include "Game/AI/Action/actionGiantBattleCloseMove.h"

namespace uking::action {

GiantBattleCloseMove::GiantBattleCloseMove(const InitArg& arg) : GiantBattleCloseAction(arg) {}

GiantBattleCloseMove::~GiantBattleCloseMove() = default;

bool GiantBattleCloseMove::init_(sead::Heap* heap) {
    return GiantBattleCloseAction::init_(heap);
}

void GiantBattleCloseMove::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantBattleCloseAction::enter_(params);
}

void GiantBattleCloseMove::leave_() {
    GiantBattleCloseAction::leave_();
}

void GiantBattleCloseMove::loadParams_() {
    GiantBattleCloseAction::loadParams_();
}

void GiantBattleCloseMove::calc_() {
    GiantBattleCloseAction::calc_();
}

}  // namespace uking::action
