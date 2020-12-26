#include "Game/AI/Action/actionKillUIScreenAction.h"

namespace uking::action {

KillUIScreenAction::KillUIScreenAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KillUIScreenAction::~KillUIScreenAction() = default;

bool KillUIScreenAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KillUIScreenAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KillUIScreenAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void KillUIScreenAction::loadParams_() {
    getDynamicParam(&mScreenName_d, "ScreenName");
}

void KillUIScreenAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
