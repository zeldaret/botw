#include "Game/AI/Action/actionGiantBattleCloseWalk.h"

namespace uking::action {

GiantBattleCloseWalk::GiantBattleCloseWalk(const InitArg& arg) : GiantBattleCloseAction(arg) {}

GiantBattleCloseWalk::~GiantBattleCloseWalk() = default;

bool GiantBattleCloseWalk::init_(sead::Heap* heap) {
    return GiantBattleCloseAction::init_(heap);
}

void GiantBattleCloseWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantBattleCloseAction::enter_(params);
}

void GiantBattleCloseWalk::leave_() {
    GiantBattleCloseAction::leave_();
}

void GiantBattleCloseWalk::loadParams_() {
    GiantBattleCloseAction::loadParams_();
}

void GiantBattleCloseWalk::calc_() {
    GiantBattleCloseAction::calc_();
}

}  // namespace uking::action
