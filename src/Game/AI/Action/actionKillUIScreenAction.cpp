#include "Game/AI/Action/actionKillUIScreenAction.h"

namespace uking::action {

KillUIScreenAction::KillUIScreenAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KillUIScreenAction::~KillUIScreenAction() = default;

bool KillUIScreenAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KillUIScreenAction::loadParams_() {
    getDynamicParam(&mScreenName_d, "ScreenName");
}

}  // namespace uking::action
